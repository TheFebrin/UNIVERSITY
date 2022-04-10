from abc import ABC, abstractmethod
from typing import List, Any, Generator
from datetime import datetime
from contextlib import contextmanager


class Plane:
    pass


class PoolLimitExceeded(Exception):
    pass


class ReleasedObjectFromAnotherPool(Exception):
    pass


class NotAvailable(Exception):
    pass


class IAirport(ABC):

    @abstractmethod
    def acquire_plane(self) -> Plane:
        raise NotImplemented

    @abstractmethod
    def release_plane(self, plane: Plane) -> None:
        raise NotImplemented


class Airport(IAirport):
    
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



class AirportProxy(IAirport):

    def __init__(self, airport: IAirport) -> None:
        self._airport = airport

    def _is_available(self) -> bool:
        current_hour: int = datetime.now().hour
        return 8 <= current_hour <= 22

    def acquire_plane(self) -> Plane:
        if self._is_available():
            return self._airport.acquire_plane()
        else:
            raise NotAvailable('Only available between 8 and 22.')

    def release_plane(self, plane: Plane) -> None:
        if self._is_available():
            return self._airport.release_plane(plane=plane)
        else:
            raise NotAvailable('Only available between 8 and 22.')
        

class AirportLoggerProxy(IAirport):

    def __init__(self, airport: IAirport) -> None:
        self._airport = airport

    @contextmanager
    def _log_info(self, method: str, params: List[Any]) -> Generator[None, None, None]:
        print(f'[{datetime.now()}] BEGIN {method} {params}')
        yield
        print(f'[{datetime.now()}] FINISHED {method} {params}')

    def acquire_plane(self) -> Plane:
        with self._log_info(method='acquire_plane', params=[]):
            plane =  self._airport.acquire_plane()
            print(f'[acquire_plane] Returning: {plane}')
            return plane

    def release_plane(self, plane: Plane) -> None:
        with self._log_info(method='release_plane', params=[plane]):
            return self._airport.release_plane(plane=plane)



def main() -> None:
    # airport: IAirport = AirportProxy(airport=Airport(pool_capacity=10))
    # plane: Plane = airport.acquire_plane()

    airport2: IAirport = AirportLoggerProxy(airport=Airport(pool_capacity=10))
    plane2: Plane = airport2.acquire_plane()


if __name__ == '__main__':
    main()