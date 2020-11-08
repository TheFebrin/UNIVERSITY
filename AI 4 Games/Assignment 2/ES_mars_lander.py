import sys
import math
import numpy as np
import time

class ES:
    def __init__(
        self,
        eval_f,
        population_size, chromosome_len=20, K=0.9,
        tau0=None, tau1=None,
        n_mutations=1
    ):
        '''
        Args:
            population_size : int
                Number of cars in the population
            chromosome_len : int
                Length of the list, which is our answer for the problem
            K : int
                Kind of learning rate parameter
        '''

        self.eval_f = eval_f
        self.population_size: int = population_size
        self.d: int = chromosome_len
        self.K: float = K
        self.tau0: float = tau0
        self.tau1: float = tau1
        self._best_individual = None
        self._best_cost = -1e8
        self.n_mutations = n_mutations

        assert population_size % 2 == 0, 'Population size must be even.'

        if self.tau0 is None:
            self.tau0 = K / np.sqrt(2 * np.sqrt(self.d))

        if self.tau1 is None:
            self.tau1 = K / np.sqrt(2 * self.d)

        self.population_angles = np.random.uniform(
            low=-15,
            high=15,
            size=(self.population_size, self.d)
        )
        # 1 - increase thrust | 0 - nothing | -1 - decrease thrust
        # self.population_thrust = np.random.randint(
        #     low=-1,
        #     high=2,
        #     size=(self.population_size, self.d)
        # )
        n_zeros = self.population_size // 5000
        self.population_thrust1 = np.zeros((self.population_size, n_zeros))
        self.population_thrust2 = np.ones((self.population_size, self.d - n_zeros))
        self.population_thrust = np.hstack((self.population_thrust1, self.population_thrust2))

        self.population = np.stack((self.population_angles, self.population_thrust), axis=2)

        self.sigmas_angles = np.random.uniform(
            low=0,
            high=8,
            size=(self.population_size, self.d)
        )
        self.sigmas_thrust = np.random.uniform(
            low=0,
            high=1,
            size=(self.population_size, self.d)
        )
        self.sigmas = np.stack((self.sigmas_angles, self.sigmas_thrust), axis=2)

        self.cost = self.eval_f(self.population)

    def parents_selection(self) -> np.ndarray:
        """ Roulette method """
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


    def replacement_and_crossover(self, ids) -> None:
        self.population = self.population[ids]

#         parents_ids = np.arange(self.population_size)
#         np.random.shuffle(parents_ids)

#         p1 = self.population[parents_ids[self.population_size // 2]]
#         p2 = self.population[self.population_size // 2:]

#         r = np.random.rand(self.population_size // 2)[:, np.newaxis, np.newaxis]
#         children1 = r * p1 + (1 - r) * p2
#         children2 = (1 - r) * p1 + r * p2

#         self.population = np.vstack((children1, children2))
#         self.population[:, :, 1] = np.round(self.population[:, :, 1]).astype(np.int)


    def mutation(self) -> None:
        ''' ES algorithm based mutation '''

        E = np.random.normal(0, self.tau1, size=self.sigmas.shape)
        eps_o = np.random.normal(0, self.tau0)
        self.sigmas *= np.exp(E + eps_o)
        self.sigmas = self.sigmas.clip(-15, 15)

        # muatation for angles
        self.population += np.random.normal(0, 1, size=self.sigmas.shape) * self.sigmas
        self.population[:, :, 0] = self.population[:, :, 0].clip(-15, 15)
        self.population[:, :, 1] = self.population[:, :, 1].clip(-1, 1)

        self.population[:, :, 1] = np.round(self.population[:, :, 1]).astype(np.int)
        # mutation for power
        # random_indices = np.random.randint(0, self.d, size=(self.n_mutations, self.population_size))
        # self.population[:, :, 1][np.arange(self.population_size), random_indices] = np.random.randint(-1, 2, size=self.population_size)


    def run(self, timeout, start_time) -> None:
        n_iters = 0
        while time.time() - start_time <= timeout:
            best_cost_index = self.cost.argmax()
            best_current_individual = self.population[best_cost_index]
            if self.cost[best_cost_index] > self._best_cost:
                self._best_cost = self.cost[best_cost_index]
                self._best_individual = best_current_individual

            parents_ids = self.parents_selection()
            self.replacement_and_crossover(ids=parents_ids)
            self.mutation()
            self.population[self.cost.argmin()] = best_current_individual  # elitism
            self.cost = self.eval_f(self.population)
            n_iters += 1

        print(f'n_iters: {n_iters}', file=sys.stderr)


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


def next_state(
    x: float, y: float, h_speed: float, v_speed: float, fuel: int, angle: int, power: int,
    new_angle: int, new_power: int
):
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


# def ccw(A, B, C) -> bool:
#     return (C[1] - A[1]) * (B[0] - A[0]) > (B[1] - A[1]) * (C[0] - A[0])

# def intersect(A, B) -> bool:
#     """ Return: True if intersect. """
#     for i in range(len(SURFACE) - 1):
#         C = SURFACE[i]
#         D = SURFACE[i + 1]

#         if ccw(A,C,D) != ccw(B,C,D) and ccw(A,B,C) != ccw(A,B,D):
#             return True
#     return False


#  Faster intersection
def intersect(point: tuple, point_surface: dict) -> bool:
    """ Return: True if point intersects with surface. """
    x, y = point
    surface_y = point_surface[int(x)]

    return y <= surface_y


def simmulate(
    genotype: np.ndarray,
    x: int, y: int,
    h_speed: int, v_speed: int,
    fuel: int, angle: int, power: int,
    point_surface: list,
    l: int, r: int, h: int
):
    x_start, y_start = x, y
    cords = [(x, y)]

    broke = False
#     print(f'x: {x:.1f}, y: {y:.1f}, speed: {(h_speed, v_speed)}, fuel: {fuel}, angle: {angle}, power: {power}')
    for new_angle, new_power in genotype:
        x2, y2, h_speed2, v_speed2, fuel2, angle2, power2 = next_state(
            x=x, y=y, h_speed=h_speed, v_speed=v_speed, fuel=fuel, angle=angle, power=power,
            new_angle=new_angle, new_power=new_power
        )
        if fuel <= 0 or x2 < 0 or x2 > 6999 or y2 > 2800 or intersect(point=(x2, y2), point_surface=point_surface):
#             print('INTERSECTION')
            broke = True
            break

        x, y, h_speed, v_speed, fuel, angle, power = x2, y2, h_speed2, v_speed2, fuel2, angle2, power2
        cords.append((x, y))
#         print(f'x: {x:.1f}, y: {y:.1f}, speed: {(h_speed, v_speed)}, fuel: {fuel}, angle: {angle}, power: {power}')


    max_dist_x = 0
    max_dist_y = 0
    close_x = 0
    if l <= x <= r:
        close_x = 0
        max_dist_x = 0
    else:
        close_x = min(abs(x - l), abs(x - r)) ** 2
        max_dist_x = min(abs(x_start - l), abs(x_start - r)) ** 2

    close_y = (y - h) ** 2
    max_dist_y = (y_start - h) ** 2

    max_dist = np.sqrt(max_dist_x + max_dist_y)
    act_dist = np.sqrt(close_x + close_y)
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

    return score, cords


def objective_function(
    population: np.ndarray, point_surface: dict,
    l_start: int, r_start: int, h_start: int,
    x_start: float, y_start: float,
    h_speed_start: float, v_speed_start: float,
    fuel_start: int, angle_start: float, power_start: int,
):
    costs = []
    for p in population:
        cost = simmulate(
            genotype=p,
            x=x_start, y=y_start,
            h_speed=h_speed_start, v_speed=v_speed_start,
            fuel=fuel_start, angle=angle_start, power=power_start,
            point_surface=point_surface,
            l=l_start, r=r_start, h=h_start
        )[0]
        costs.append(cost)
    return np.array(costs)


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

    CHROMOSOME_LEN = 100
    model = ES(
        eval_f=lambda x: objective_function(
            population=x, point_surface=point_surface,
            l_start=l_start, r_start=r_start, h_start=h_start,
            x_start=x_start, y_start=y_start,
            h_speed_start=h_speed_start, v_speed_start=v_speed_start,
            fuel_start=fuel_start, angle_start=angle_start, power_start=power_start,
        ),
        population_size=30, chromosome_len=CHROMOSOME_LEN, K=2, n_mutations=5
    ) 

    model.run(timeout=0.98, start_time=start_time)

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

        da, dp = genotype[i]
        print(f'change angle: {da} | change power: {dp}', file=sys.stderr)
        print(f'beg angle: {angle_start} | beg power: {power_start}', file=sys.stderr)
        angle_start += da
        power_start += dp

        power_start = max(0, power_start)
        power_start = min(4, power_start)

        angle_start = max(-90, angle_start)
        angle_start = min(90, angle_start)

        print(f'Angle: {angle_start} | power: {power_start}', file=sys.stderr)
        print(int(round(angle_start)), int(round(power_start)))
        x, y, hs, vs, f, r, p = map(int, input().split())
