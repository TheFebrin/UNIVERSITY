import pandas as pd
import numpy as np
import graphviz


def entropy(counts):
    s = sum(counts)
    counts = counts / s
    return -np.sum(counts * np.log2(counts + 1e-100))

def gini(counts):
    s = sum(counts)
    counts = counts / s
    return 1 - np.sum(counts * counts)

def mean_err_rate(counts):
    counts = counts / sum(counts)
    return 1 - max(counts)
    
    
class AbstractSplit:
    """Split the examples in a tree node according to a criterion.
    """
    def __init__(self, attr):
        self.attr = attr

    def __call__(self, x):
        """Return the subtree corresponding to x."""
        raise NotImplementedError

    def build_subtrees(self, df, subtree_kwargs):
        """Recuisively build the subtrees."""
        raise NotImplementedError

    def iter_subtrees(self):
        """Return an iterator over subtrees."""
        raise NotImplementedError

    def add_to_graphviz(self, dot):
        """Add the split to the graphviz vizluzation."""
        raise NotImplementedError

    def __str__(self):
        return f"{self.__class__.__name__}: {self.attr}"
        
        
        
class CategoricalMultivalueSplit(AbstractSplit):
    def build_subtrees(self, df, subtree_kwargs):
        self.subtrees = {}
        for group_name, group_df in df.groupby(self.attr):
            child = Tree(group_df, **subtree_kwargs)
            self.subtrees[group_name] = child

    def __call__(self, x):
        # Return the subtree for the given example
        attr = self.attr
        assert(attr in x)
        if x[attr] in self.subtrees:
            return self.subtrees[x[attr]]
        
        return None

    def iter_subtrees(self):
        return self.subtrees.values()
    
    def add_to_graphviz(self, dot, parent, print_info):
        for split_name, child in self.subtrees.items():
            child.add_to_graphviz(dot, print_info)
            dot.edge(f'{id(parent)}', f'{id(child)}',
                     label=f'{split_name}')
            
            

def get_categorical_split_and_purity(df, parent_purity, purity_fun, attr,
                                     normalize_by_split_entropy=False):
    """Return a multivariate split and its purity.
    Args:
        df: a dataframe
        parent_purity: purity of the parent node
        purity_fun: function to compute the purity
        attr: attribute over whihc to split the dataframe
        normalize_by_split_entropy: if True, divide the purity gain by the split
            entropy (to compute https://en.wikipedia.org/wiki/Information_gain_ratio)
    
    Returns:
        pair of (split, purity_gain)
    """
    split = CategoricalMultivalueSplit(attr)
    # Compute the purity after the split
    # parent purity - weighted sum of children purity
    
    children_purity = 0
    for group_name, group_df in df.groupby(attr):
        children_purity += purity_fun(group_df['target'].value_counts()) * len(group_df)
        
    children_purity /= len(df)
    purity_gain = parent_purity - children_purity
    
    if normalize_by_split_entropy:
        purity_gain /= entropy(df[attr].value_counts())
        
    return split, purity_gain



def get_split(df, criterion='infogain', nattrs=None):
    # Implement termination criteria:
    # 1. Node is pure
    target_value_counts = df['target'].value_counts()
    if len(target_value_counts) == 1:
        return None
    # 2. No split is possible
    #    First get alist of attributes that can be split
    possible_splits = [c for c in df.columns if c != 'target' and len(df[c].value_counts()) > 1]
    if nattrs is not None:
        np.random.shuffle(possible_splits)
        possible_splits = possible_splits[:nattrs]
        
    #    Terminate early if none are possivle
    if not possible_splits:
        return None
    
    # Get the base purity measure and the purity function
    if criterion in ['infogain', 'infogain_ratio']:
        purity_fun = entropy
    elif criterion in ['mean_err_rate']:    
        purity_fun = mean_err_rate
    elif criterion in ['gini']:
        purity_fun = gini
    else:
        raise Exception("Unknown criterion: " + criterion)
    base_purity = purity_fun(target_value_counts)

    best_purity_gain = -1
    best_split = None

    # Random Forest support
    # Randomize the split by restricting the number of attributes
    
    for attr in possible_splits:
        if np.issubdtype(df[attr].dtype, np.number):
            # Handling of numerical attributes will be defined later, in a manner 
            # similar to categorical ones
            split_sel_fun = get_numrical_split_and_purity
        else:
            split_sel_fun = get_categorical_split_and_purity
        
        split, purity_gain = split_sel_fun(df, base_purity, purity_fun, attr,
                                            normalize_by_split_entropy=criterion.endswith('ratio'))
        
        if purity_gain > best_purity_gain:
            best_purity_gain = purity_gain
            best_split = split
    return best_split



class Tree:
    def __init__(self, df, **kwargs):
        super().__init__()
        # Assert that threre are no missing values, 
        # TODO: remove this for bonus problem #XXX
        assert not df.isnull().values.any()
        
        # We need to let subrees know about all targets to properly color nodes
        if 'all_targets' not in kwargs:
            kwargs['all_targets'] = sorted(df['target'].unique())
        # Save keyword arguments to build subtrees
        kwargs_orig = dict(kwargs)
        
        # Get kwargs we know about, remaning ones are for splitting
        self.all_targets = kwargs.pop('all_targets')
        
        # Save debug info for visualization
        self.counts = df['target'].value_counts()
        self.info = {
            'num_samples': len(df),
            'entropy': entropy(self.counts),
            'gini': gini(self.counts),
        }
        
        self.split = get_split(df, **kwargs)
        if self.split:
            #print('!!S', self.split)
            self.split.build_subtrees(df, kwargs_orig)
    
    def get_target_distribution(self, sample):
        # TODO: descend into subtrees and return the leaf target distribution
        if self.split is not None:
            subtree = self.split(sample)
            if subtree is not None:
                return subtree.get_target_distribution(sample)
            else:
                return self.counts / self.info['num_samples']
        else:
            return self.counts / self.info['num_samples']
        
        
    def classify(self, sample):
        # TODO: classify the sample by descending into the appropriate subtrees.
        if self.split is not None:
            subtree = self.split(sample)
            if subtree is not None:
                return subtree.classify(sample)
            else:
                return self.counts.idxmax()
        else:
            return self.counts.idxmax()
                
    def draw(self, print_info=True):
        dot = graphviz.Digraph()
        self.add_to_graphviz(dot, print_info)
        return dot

    def add_to_graphviz(self, dot, print_info):
        freqs = self.counts / self.counts.sum()
        freqs = dict(freqs)
        colors = []
        freqs_info = []
        for i, c in enumerate(self.all_targets):
            freq = freqs.get(c, 0.0)
            if freq > 0:
                colors.append(f"{i%9 + 1};{freq}")
                freqs_info.append(f'{c}:{freq:.2f}')
        colors = ':'.join(colors)
        labels = [' '.join(freqs_info)]
        if print_info:
            for k,v in self.info.items():
                labels.append(f'{k} = {v}')
        if self.split:
            labels.append(f'split by: {self.split.attr}')
        dot.node(f'{id(self)}',
                 label='\n'.join(labels), 
                 shape='box',
                 style='striped',
                 fillcolor=colors,
                 colorscheme='set19')
        if self.split:
            self.split.add_to_graphviz(dot, self, print_info)
            
        
    def upper_confidenct_interval(self, f, N, z=0.5):
        return (f + ((z ** 2) / (2 * N)) \
                + z * ((f / N - (f ** 2) / N + z ** 2 / (4 * (N ** 2))) ** 0.5))  \
                / (1 + (z ** 2) / N)

    def prune_with_confidence_interval(self):
        if self.split:
            for w in self.split.iter_subtrees():
                w.prune_with_confidence_interval()
        
        N = self.info['num_samples']
        parent_error = self.counts / np.sum(self.counts)
        parent_error = sorted(list(parent_error), reverse=True)
        parent_error = np.sum(parent_error[1:])
        parent_error = self.upper_confidenct_interval(parent_error, N)
        self.info['confidence_error'] = parent_error
        
        if self.split:
            children_error = 0
            for w in self.split.iter_subtrees():
                child_error = (w.info['num_samples'] / N) * w.info['confidence_error']
                children_error += child_error
     
        
            if children_error > parent_error:
                self.split = None
                self.info['splitted'] = True
                
                

                
class NumericalSplit(AbstractSplit):
    def __init__(self, attr, th):
        super(NumericalSplit, self).__init__(attr)
        self.th = th
    
    def build_subtrees(self, df, subtree_kwargs):
        self.subtrees = (
            Tree(df[df[self.attr] <= self.th], **subtree_kwargs),
            Tree(df[df[self.attr] > self.th], **subtree_kwargs))

    def __call__(self, x):
        if x[self.attr] <= self.th:
            return self.subtrees[0]
        else:
            return self.subtrees[1]
    
    def __str__(self):
        return f"NumericalSplit: {self.attr} <= {self.th}"

    def iter_subtrees(self):
        return self.subtrees
    
    def add_to_graphviz(self, dot, parent, print_info):
        self.subtrees[0].add_to_graphviz(dot, print_info)
        dot.edge(f'{id(parent)}', f'{id(self.subtrees[0])}',
                 label=f'<= {self.th:.2f}')
        self.subtrees[1].add_to_graphviz(dot, print_info)
        dot.edge(f'{id(parent)}', f'{id(self.subtrees[1])}',
                 label=f'> {self.th:.2f}')
        
        
        
        
        
def get_numrical_split_and_purity(df, parent_purity, purity_fun, attr,
                                  normalize_by_split_entropy=False):
    """Find best split thereshold and compute the average purity after a split.
    Args:
        df: a dataframe
        parent_purity: purity of the parent node
        purity_fun: function to compute the purity
        attr: attribute over whihc to split the dataframe
        normalize_by_split_entropy: if True, divide the purity gain by the split
            entropy (to compute https://en.wikipedia.org/wiki/Information_gain_ratio)
    
    Returns:
        pair of (split, purity_gain)
    """
    attr_df = df[[attr, 'target']].sort_values(attr)
    targets = attr_df['target']
    values = attr_df[attr]
    # Start with a split that puts all the samples into the right subtree
    right_counts = targets.value_counts()
    left_counts = right_counts * 0

    best_split = None
    best_purity_gain = -1
    N = len(attr_df)
    for row_i in range(N - 1):
        # Update the counts of targets in the left and right subtree and compute
        # the purity of the slipt for all possible thresholds!
        # Return the best split found.

        # Remember that the attribute may have duplicate values and all samples
        # with the same attribute value must end in the same subtree!
                
        row_target = targets.iloc[row_i]
        right_counts[row_target] -= 1
        left_counts[row_target] -= 1
        
        if attr_df.iloc[row_i][0] != attr_df.iloc[row_i + 1][0]:
            children_purity = (row_i + 1) * purity_fun(left_counts) \
                                + (N - row_i - 1) * purity_fun(right_counts)
            children_purity /= N
            purity = parent_purity - children_purity

            if purity > best_purity_gain:
                best_purity_gain = purity
                attr_mean = (attr_df.iloc[row_i][0] + attr_df.iloc[row_i + 1][0]) / 2
                best_split = NumericalSplit(attr, attr_mean)

    if normalize_by_split_entropy:
        best_purity_gain /= entropy(targets.value_counts())
    return best_split, best_purity_gain