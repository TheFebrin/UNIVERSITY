class MCTS(object):
    """docstring for MCTS"""

    def __init__(self, player, board, time):
        super(MCTS, self).__init__()
        self.move = player
        self.board = board
        self.time = time
        self.node_no = 1
        self.wins = 0
        self.loses = 0
        self.visited = {}
        self.not_leaf = set()

    def monte_carlo_tree_search(root):
        act_node = root
        is_leaf[root] = True

        while resources_left(time):

            if act_node in not_leaf:
                # we chose the best son
                pass
            else:  # leaf
                if visited[act_node]:  # generate all sonz
                    generate_sons(act_node)
                    not_leaf.add(act_node)
                else:  # not visited leaf - rollout
                    visited[act_node] = True
                    rollout(act_node)
                    backtrack(act_node)

        return best_child(root)

    def traverse(node):
        while fully_expanded(node):
            node = best_uct(node)
        return pick_univisted(node.children) or node  # in case no children are present / node is terminal

    def rollout(node):
        while non_terminal(node):
            node = rollout_policy(node)
        return result(node)

    def generate_sons(node):
        pass

    def backtrack(node, result):
        if is_root(node):
            return
        node.stats = update_stats(node, result)
        backpropagate(node.parent)

    def best_child(node):
        pick child with highest number of visits
