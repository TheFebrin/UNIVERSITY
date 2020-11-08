import sys
import math
import numpy as np
import time


class Node:
    def __init__(self, action, parent) -> None:
        self._current_action: tuple = action  # pair[int, int]  angle and power
        self._children = {}  # dict[action, Node]
        self._score = -1e18
        self._visited = 0
        self._parent = parent

    def _backpropagate(self, score: float) -> float:
        individual_score = 0
        iters = 0
        while self._parent is not None:
            self._visited += 1
            self._score = max(self._score, score)
            iters += 1
            individual_score += self._score
            self = self._parent

        assert iters > 0, 'ITERS == 0 !!!!!'
        return individual_score / iters

    def rollout(
        self,
        genotype: np.ndarray,
        x: int, y: int,
        h_speed: int, v_speed: int,
        fuel: int, angle: int, power: int,
        point_surface: list,
        l: int, r: int, h: int
    ) -> float:
        x_start, y_start = x, y
        cords = [(x, y)]
        broke = False

        act_node: Node = self
        for new_angle, new_power in genotype:
            x2, y2, h_speed2, v_speed2, fuel2, angle2, power2 = next_state(
                x=x, y=y, h_speed=h_speed, v_speed=v_speed, fuel=fuel, angle=angle, power=power,
                new_angle=new_angle, new_power=new_power
            )
            if fuel <= 0 or x2 < 0 or x2 > 6999 or y2 > 2800 or intersect(point=(x2, y2), point_surface=point_surface):
                broke = True
                break
            x, y, h_speed, v_speed, fuel, angle, power = x2, y2, h_speed2, v_speed2, fuel2, angle2, power2

            if (new_angle, new_power) in self._children:
                act_node = self._children[(new_angle, new_power)]
            else:
                self._children[(new_angle, new_power)] = Node(action=(new_angle, new_power), parent=self)
                act_node = self._children[(new_angle, new_power)]

        max_dist_x, close_x = 0, 0
        if not l <= x <= r:
            close_x = min(abs(x - l), abs(x - r)) ** 2
            max_dist_x = min(abs(x_start - l), abs(x_start - r)) ** 2

        max_dist = np.sqrt(max_dist_x + (y_start - h) ** 2)
        act_dist = np.sqrt(close_x + (y - h) ** 2)
        dist_score = (1 - act_dist / max_dist) * 100

        assert -90 <= angle <= 90
        angle_score = (1 - abs(angle) / 90) * 100

        if v_speed <= 40:
            vertical_score = 100
        else:
            broke = True
            vertical_score = -(v_speed - 40)

        if h_speed < 20:
            horizontal_score = 100
        else:
            broke = True
            horizontal_score = -(h_speed - 20)

        score = dist_score * 10 + angle_score + vertical_score * 5 + horizontal_score
        if broke or abs(angle) >= 0.49:
            score -= 100000

        return act_node._backpropagate(score=score)



class Node:
    def __init__(self, action, parent) -> None:
        self._current_action: tuple = action  # pair[int, int]  angle and power
        self._children = {}  # dict[action, Node]
        self._score = -1e18
        self._visited = 0
        self._parent = parent

    def _backpropagate(self, score: float) -> float:
        individual_score = 0
        iters = 0
        while self._parent is not None:
            self._visited += 1
            self._score = max(self._score, score)
            iters += 1
            individual_score += self._score
            self = self._parent

        assert iters > 0, 'ITERS == 0 !!!!!'
        return individual_score / iters

    def rollout(
        self,
        genotype: np.ndarray,
        x: int, y: int,
        h_speed: int, v_speed: int,
        fuel: int, angle: int, power: int,
        point_surface: list,
        l: int, r: int, h: int
    ) -> float:
        x_start, y_start = x, y
        cords = [(x, y)]
        broke = False

        act_node: Node = self
        for new_angle, new_power in genotype:
            x2, y2, h_speed2, v_speed2, fuel2, angle2, power2 = next_state(
                x=x, y=y, h_speed=h_speed, v_speed=v_speed, fuel=fuel, angle=angle, power=power,
                new_angle=new_angle, new_power=new_power
            )
            if fuel <= 0 or x2 < 0 or x2 > 6999 or y2 > 2800 or intersect(point=(x2, y2), point_surface=point_surface):
                broke = True
                break
            x, y, h_speed, v_speed, fuel, angle, power = x2, y2, h_speed2, v_speed2, fuel2, angle2, power2

            new_angle, new_power = int(round(new_angle)),  int(round(new_power))
            if (new_angle, new_power) in self._children:
                act_node = self._children[(new_angle, new_power)]
            else:
                self._children[(new_angle, new_power)] = Node(action=(new_angle, new_power), parent=self)
                act_node = self._children[(new_angle, new_power)]

        max_dist_x, close_x = 0, 0
        if not l <= x <= r:
            close_x = min(abs(x - l), abs(x - r)) ** 2
            max_dist_x = min(abs(x_start - l), abs(x_start - r)) ** 2

        max_dist = np.sqrt(max_dist_x + (y_start - h) ** 2)
        act_dist = np.sqrt(close_x + (y - h) ** 2)
        dist_score = (1 - act_dist / max_dist) * 100

        assert -90 <= angle <= 90
        angle_score = (1 - abs(angle) / 90) * 100

        if v_speed <= 40:
            vertical_score = 100
        else:
            broke = True
            vertical_score = -(v_speed - 40)

        if h_speed < 20:
            horizontal_score = 100
        else:
            broke = True
            horizontal_score = -(h_speed - 20)

        score = dist_score * 5 + angle_score + vertical_score * 5 + horizontal_score
        if broke:
            score -= 1000000000

        return act_node._backpropagate(score=score)



class RHEA:
    def __init__(self, N, chromosome_len=20, n_mutations=5):
        '''
        Args:
            N : int
                Number of cars in the population
            chromosome_len : int
                Length of the list, which is our answer for the problem
        '''

        self._N: int = N
        self._d: int = chromosome_len
        self.n_mutations: int = n_mutations
        self._best_individual = None
        self._best_cost = -1e18
        self._scores = np.ones(N)
        self.node = Node(action=None, parent=None)
        self.cost_history = []  # List[Tuple[min, mean, max]]
        self.population_std = []

        assert N % 2 == 0, 'Population size must be even.'

        self.population_angles = np.random.uniform(
            low=-15,
            high=15,
            size=(self._N, self._d)
        )
        # 1 - increase thrust | 0 - nothing | -1 - decrease thrust
        self.population_thrust = np.random.randint(
            low=1,
            high=2,
            size=(self._N, self._d)
        )
        self.population = np.stack((self.population_angles, self.population_thrust), axis=2)

    def _parents_selection(self) -> np.ndarray:
        """ Roulette method """
        fitness_values = self._scores.copy()
        fitness_values = fitness_values - fitness_values.min()
        if fitness_values.sum() > 0:
            fitness_values = fitness_values / fitness_values.sum()
        else:
            fitness_values = np.ones(len(self.population)) / len(self.population)

        ids = np.random.choice(
            np.arange(self._N),
            size=self._N,
            replace=True,
            p=fitness_values
        )
        return ids

    def _replacement_and_crossover(self, ids) -> None:
        self.population = self.population[ids]

        parents_ids = np.arange(self._N)
        np.random.shuffle(parents_ids)

        p1 = self.population[parents_ids[self._N // 2]]
        p2 = self.population[self._N // 2:]

        r = np.random.rand(self._N // 2)[:, np.newaxis, np.newaxis]
        children1 = r * p1 + (1 - r) * p2
        children2 = (1 - r) * p1 + r * p2

        self.population = np.vstack((children1, children2))
        self.population[:, :, 1] = np.round(self.population[:, :, 1]).astype(np.int)

    def _mutation(self) -> None:
        random_indices = np.random.randint(0, self._d, size=(self.n_mutations, self._N))

        self.population[:, :, 0][np.arange(self._N), random_indices] = np.random.uniform(-15, 15, size=self._N)
        self.population[:, :, 1][np.arange(self._N), random_indices] = np.random.randint(-1, 2, size=self._N)

    def run(self) -> None:
        n_iters = 0
        best_cost_index = self._scores.argmax()
        best_current_individual = self.population[best_cost_index]
        if self._scores[best_cost_index] > self._best_cost:
            self._best_cost = self._scores[best_cost_index]
            self._best_individual = best_current_individual

        parents_ids = self._parents_selection()
        self._replacement_and_crossover(ids=parents_ids)
        self._mutation()
        self.population[self._scores.argmin()] = best_current_individual  # elitism

    def population_rollout(
        self,
        x: int, y: int,
        h_speed: int, v_speed: int,
        fuel: int, angle: int, power: int,
        point_surface: list,
        l: int, r: int, h: int
    ):
        scores = []
        for individual in self.population:
            individual_score = self.node.rollout(
                genotype=individual,
                x=x, y=y,
                h_speed=h_speed, v_speed=v_speed,
                fuel=fuel, angle=angle, power=power,
                point_surface=point_surface,
                l=l, r=r, h=h
            )
            scores.append(individual_score)
        self._scores = np.array(scores)

    def change_node(self):
        best_node = None
        best_score = -1e18
        best_action = None
        for action, node in  self.node._children.items():
            if node._score > best_score:
                best_score = node._score
                best_node = node
                best_action = node._current_action

        assert best_node is not None, 'NEW ROOT IS NONE!'
        self.node = best_node
        return best_action



def create_point_surface(surface) -> dict:
    n = len(surface)

    points_surface = {}
    for i in range(n - 1):
        x1, y1 = surface[i]
        x2, y2 = surface[i + 1]
        a = (y1 - y2) / (x1 - x2)
        b = y1 - a * x1
        assert b == y2 - a * x2
        for x in range(x1, x2):
            points_surface[x] = a * x + b

    return points_surface

def next_state(x: float, y: float, h_speed: float, v_speed: float, fuel: int, angle: int, power: int, new_angle: int, new_power: int):
    GRAVITY = -3.711

    assert -1 <= new_power <= 1, f'Wrong new_power: {power}'
    power += new_power
    power = max(0, power)
    power = min(4, power)
    assert power in [0, 1, 2, 3, 4], f'Wrong power: {power}'
    fuel -= power

    assert -15 <= new_angle <= 15, f'Wrong new_angle: {new_angle}'
    angle += new_angle
    angle = max(-90, angle)
    angle = min(90, angle)
    assert -90 <= angle <= 90, f'Wrong angle: {angle}'

    angle_radians = (angle * math.pi) / 180.0
    a_h = -math.sin(angle_radians) * power
    a_v = math.cos(angle_radians) * power + GRAVITY

    x += h_speed + a_h / 2.0
    y += v_speed + a_v / 2.0

    h_speed += a_h
    v_speed += a_v

    return x, y, h_speed, v_speed, fuel, angle, power

#  Faster intersection
def intersect(point: tuple, point_surface: dict) -> bool:
    """ Return: True if point intersects with surface. """
    x, y = point
    surface_y = point_surface[int(x)]

    return y <= surface_y

def find_borders(SURFACE):
    for i in range(len(SURFACE) - 1):
        if SURFACE[i][1] == SURFACE[i + 1][1]:
            return SURFACE[i][0], SURFACE[i + 1][0], SURFACE[i + 1][1]

    return None


SURFACE_POINTS = []

if __name__ == '__main__':
    n = int(input())  # the number of points used to draw the surface of Mars.
    for i in range(n):
        # land_x: X coordinate of a surface point. (0 to 6999)
        # land_y: Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        land_x, land_y = map(int, input().split())
        SURFACE_POINTS.append((land_x, land_y))

    start_time = time.time()
    SURFACE_POINTS.sort()

    SURFACE = np.array(SURFACE_POINTS)
    point_surface = create_point_surface(surface=SURFACE)

    x, y, hs, vs, f, r, p = map(int, input().split())

    l_start, r_start, h_start = find_borders(SURFACE)
    x_start, y_start = x, y
    h_speed_start, v_speed_start = hs, vs
    fuel_start, angle_start, power_start, = f, r, p

    CHROMOSOME_LEN = 50
    model = RHEA(N=20, chromosome_len=CHROMOSOME_LEN, n_mutations=2)
    iters = 0
    while time.time() - start_time <= 0.95:
        model.population_rollout(
            x=x_start, y=y_start,
            h_speed=h_speed_start, v_speed=v_speed_start,
            fuel=fuel_start, angle=angle_start, power=power_start,
            point_surface=point_surface,
            l=l_start, r=r_start, h=h_start
        )
        model.run()
        iters += 1
    act_ans = model.change_node()
    print(f'BEG ITERS: {iters}', file=sys.stderr)

    genotype = model._best_individual
    print('BEST COST: ', model._best_cost, file=sys.stderr)
    print(list(genotype[:, 0].ravel()), file=sys.stderr)
    print(list(genotype[:, 1].ravel()), file=sys.stderr)

    for i in range(CHROMOSOME_LEN):
        """
        hs: the horizontal speed (in m/s), can be negative.
        vs: the vertical speed (in m/s), can be negative.
        f: the quantity of remaining fuel in liters.
        r: the rotation angle in degrees (-90 to 90).
        p: the thrust power (0 to 4)
        """

        da, dp = act_ans
        print(f'change angle: {da} | change power: {dp}', file=sys.stderr)
        angle_start += da
        power_start += dp

        power_start = max(0, power_start)
        power_start = min(4, power_start)

        angle_start = max(-90, angle_start)
        angle_start = min(90, angle_start)
        print(angle_start, power_start)

        x, y, hs, vs, f, r, p = map(int, input().split())

        start_time = time.time()
        iters = 0
        while time.time() - start_time <= 0.09:
            model.population_rollout(
                x=x_start, y=y_start,
                h_speed=h_speed_start, v_speed=v_speed_start,
                fuel=fuel_start, angle=angle_start, power=power_start,
                point_surface=point_surface,
                l=l_start, r=r_start, h=h_start
            )
            model.run()
            iters += 1
        act_ans = model.change_node()
        print(f'BEG ITERS: {iters}', file=sys.stderr)
        print('BEST COST: ', model._best_cost, file=sys.stderr)
