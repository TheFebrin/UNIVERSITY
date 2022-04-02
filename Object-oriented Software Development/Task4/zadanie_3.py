from abc import ABC
import pytest
from typing import List

class Plane:
    pass


class PoolLimitExceeded(Exception):
    pass

class ReleasedObjectFromAnotherPool(Exception):
    pass

class Airport:
    
    def __init__(self, pool_capacity: int) -> None:
        assert pool_capacity > 0, 'pool_capacity has to be > 0'
        self._pool_capacity = pool_capacity
    
        self._planes_ready_to_acquire: List[Plane] = []
        self._planes_acquired: List[Plane] = []

    def acquire_plane(self) -> Plane:
        if len(self._planes_acquired) == self._pool_capacity:
            raise PoolLimitExceeded('Pool limit exceeded.')

        if len(self._planes_ready_to_acquire) == 0:
            plane = Plane()
        else:
            plane = self._planes_ready_to_acquire.pop()

        self._planes_acquired.append(plane)
        return plane

    def release_plane(self, plane: Plane) -> None:
        if plane not in self._planes_acquired:
            raise ReleasedObjectFromAnotherPool()

        self._planes_ready_to_acquire.append(plane)
        self._planes_acquired.remove(plane)


def test_pool_capacity_too_small() -> None:
    with pytest.raises(AssertionError):
        airport_pool = Airport(pool_capacity=0)


def test_pool_capacity_full() -> None:
    airport_pool = Airport(pool_capacity=1)
    plane_1 = airport_pool.acquire_plane()

    with pytest.raises(PoolLimitExceeded):
        airport_pool.acquire_plane()


def test_pool_acquire_and_release() -> None:
    airport_pool = Airport(pool_capacity=1)
    plane_1 = airport_pool.acquire_plane()
    airport_pool.release_plane(plane=plane_1)
    plane_2 = airport_pool.acquire_plane()
    assert plane_1 is plane_2


def test_plane_from_other_pool() -> None:
    airport_pool = Airport(pool_capacity=1)
    other_plane = Plane()
    with pytest.raises(ReleasedObjectFromAnotherPool):
        airport_pool.release_plane(other_plane)
    

"""
# Testy typów 
❯ mypy zadanie_3.py --strict
Success: no issues found in 1 source file


# Testy jednostkowe
❯ pytest -vvvl -x -s zadanie_3.py
================================================= test session starts ==================================================                                                                                            

zadanie_3.py::test_pool_capacity_too_small PASSED
zadanie_3.py::test_pool_capacity_full PASSED
zadanie_3.py::test_pool_acquire_and_release PASSED
zadanie_3.py::test_plane_from_other_pool PASSED
"""
