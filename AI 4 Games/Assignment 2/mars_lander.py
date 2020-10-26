import sys
import math
import numpy as np


class ES:
    def __init__(self, population_size, chromosome_len, K=0.9, tau0=None, tau1=None):
        '''
        Args:
            population_size : int
                Number of cars in the population
            chromosome_len : int
                Length of the list, which is our answer for the problem
            K : int
                Kind of learning rate parameter
        '''

        self.n_sensors = n_sensors
        self.population_size = population_size
        self.d = chromosome_len
        self.K = K
        self.tau0 = tau0
        self.tau1 = tau1

        if self.tau0 is None:
            self.tau0 = K / np.sqrt(2 * np.sqrt(self.d))

        if self.tau1 is None:
            self.tau1 = K / np.sqrt(2 * self.d)

        self.population = np.random.uniform(
            low=0,
            high=1,
            size=(self.population_size, self.d)
        )
        self.sigmas = np.random.uniform(
            low=0,
            high=0.05,
            size=(self.population_size, self.d)
        )
        self.training_data = np.random.uniform(
            low=0,
            high=1,
            size=(self.population_size, self.d)
        )

        self.cost = np.ones(self.population_size)
        self.cost_history = []
        self.population_history = []
        self.sigmas_history = []
        self.best_sigmas_history = []

    def parents_selection(self):
        fitness_values = self.cost
        fitness_values = fitness_values - fitness_values.min()
        if fitness_values.sum() > 0:
            fitness_values = fitness_values / fitness_values.sum()
        else:
            fitness_values = np.ones(len(self.population)) / len(self.population)

        ids = np.random.choice(
            np.arange(self.population_size),
            size=self.population_size,
            replace=True,
            p=fitness_values
        )
        return ids

    def crossover(self, parent1_id, parent2_id, parents, parent_sigmas):
        """
        TODO
        """
        pass


    def mutation1(self):
        ''' ES algorithm based mutation '''
        X = self.population
        Sigmas = self.sigmas

        E = np.random.normal(0, self.tau1, size=Sigmas.shape)
        eps_o = np.random.normal(0, self.tau0)
        Sigmas *= np.exp(E + eps_o)

        self.population = X + np.random.normal(0, 1, size=Sigmas.shape) * Sigmas
        self.sigmas = Sigmas

    def mutation2(self):
        ''' Adding Gaussian Noise '''
        self.population += np.random.normal(0, 0.1, size=self.population.shape)


    def select_new_population(self, n_gen, mutation=2):
        '''
        Args:
            crossover : int
                1: crossover1, (learning third neural network)
                2: crossover2, children get random genes from parent
        '''
        if not self.evolve or n_gen == 1:
            return self.population

        ids = self.parents_selection()
        parents = self.population[ids]
        self.training_data = self.training_data[ids]
        parent_sigmas = self.sigmas[ids]

        assert(len(self.population) == len(parents) == self.population_size)

        children, children_sigmas = [], []
        desc = 'Creating offspring...'
        r = self.population_size if crossover == 1 \
            else self.population_size // 2

        for i in tqdm(range(r), position=0, leave=True, desc=desc):
            parents_ids = random.sample(range(len(parents)), 2)
            # Neural networks crossover
            if crossover == 1:
                child = self.crossover1(
                    parents_ids[0],
                    parents_ids[1],
                    parents,
                    parent_sigmas
                )
                children.append(child)
                child_sigmas = (
                    parent_sigmas[parents_ids[0]] + parent_sigmas[parents_ids[1]]
                ) / 2
                children_sigmas.append(child_sigmas)

            # Simple toin coss over genotypes
            elif crossover == 2:
                siblings = self.crossover2(
                    parents_ids[0],
                    parents_ids[1],
                    parents,
                    parent_sigmas
                )
                children.append(siblings[0])
                children.append(siblings[1])
                children_sigmas.append(siblings[2])
                children_sigmas.append(siblings[3])

            else:
                raise ValueError('Wrong crossover type!')

        children = np.array(children)
        self.population = children
        self.sigmas = np.array(children_sigmas)

        if mutation == 1:
            self.mutation1() # ES mutation
        elif mutation == 2:
            self.mutation2()  # adding noise
        else:
            raise ValueError('Wrong mutation type!')

        # self.population_history.append(self.population)
        self.cost_history.append(
            (self.cost.min(), self.cost.mean(), self.cost.max())
        )
        self.sigmas_history.append(
            self.sigmas.mean(axis=0)  # mean of sigmas in population
        )
        best_indi = self.cost.argmax()
        self.best_sigmas_history.append(
            self.population[best_indi]  # sigmas of best individual
        )
        return self.population

    def plot_cost(self):
        self.cost_history = np.array(self.cost_history)
        plt.figure(figsize=(15, 5))
        plt.plot(self.cost_history)
        maxi_id = self.cost_history[:, 0].argmax()
        maxi_val = self.cost_history[:, 0][maxi_id]
        plt.title(f'POPULATION SIZE: {self.population_size}  |  CHROMOSOME LEN: {self.d}  |  BEST_ITER: {maxi_id}  |  MAX: {maxi_val :.3f}')
        plt.legend(['Min', 'Mean', 'Max'], loc='upper right')
        plt.savefig('plots/cost.png')

    def plot_sigmas(self, sigmas, mode=''):
        plt.figure(figsize=(15, 5))
        plt.title('Sigmas')
        plt.plot(sigmas)
        plt.savefig(f'plots/sigma_{mode}.png')


SURFACE_POINTS = []



if __name__ == '__main__':
    n = int(input())  # the number of points used to draw the surface of Mars.
    for i in range(n):
        # land_x: X coordinate of a surface point. (0 to 6999)
        # land_y: Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        land_x, land_y = map(int, input().split())
        SURFACE_POINTS.append((land_x, land_y))

    SURFACE_POINTS.sort()
    while True:
        """
        hs: the horizontal speed (in m/s), can be negative.
        vs: the vertical speed (in m/s), can be negative.
        f: the quantity of remaining fuel in liters.
        r: the rotation angle in degrees (-90 to 90).
        p: the thrust power (0 to 4)
        """
        x, y, hs, vs, f, r, p = map(int, input().split())

        # To debug: print("Debug messages...", file=sys.stderr, flush=True)

        # R P. R is the desired rotation angle. P is the desired thrust power.
        print("-20 3")
        print(123)
