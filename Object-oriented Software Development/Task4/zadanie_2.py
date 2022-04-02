from abc import ABC
from typing import List
from dataclasses import dataclass

class IShape(ABC):
    pass


@dataclass
class Square(IShape):
    side: int


@dataclass
class Rectangle(IShape):
    width: int
    height: int


class IShapeFactoryWorker(ABC):
    def can_create(self, shape: str) -> bool:
        raise NotImplementedError

    def create(self, *parameters: int) -> IShape:
        raise NotImplementedError


class RectangleFactoryWorker(IShapeFactoryWorker):
    
    def can_create(self, shape: str) -> bool:
        return shape == "Rectangle"

    def create(self, *parameters: int) -> IShape:
        width, height = parameters
        return Rectangle(width=width, height=height)


class SquareFactoryWorker(IShapeFactoryWorker):
    
    def can_create(self, shape: str) -> bool:
        return shape == "Square"

    def create(self, *parameters: int) -> IShape:
        return Square(side=parameters[0])      


class ShapeFactory:

    def __init__(self) -> None:
        self._workers: List[IShapeFactoryWorker] = [
            SquareFactoryWorker()
        ]

    def register_worker(self, worker: IShapeFactoryWorker) -> None:
        self._workers.append(worker)

    def create_shape(self, shape_name: str, *parameters: int) -> IShape:
        for worker in self._workers:
            if worker.can_create(shape=shape_name):
                return worker.create(*parameters)
        raise RuntimeError(f'No worker for shape_name = {shape_name}')


def main() -> None:
    # klient
    factory: ShapeFactory = ShapeFactory()
    shape: IShape = factory.create_shape('Square', 5)
    print(shape)

    # rozszerzenie
    factory.register_worker(worker=RectangleFactoryWorker())
    rect: IShape = factory.create_shape('Rectangle', 3, 5)
    print(rect)

if __name__ == '__main__':
    """
    ❯ mypy zadanie_2.py --strict
    Success: no issues found in 1 source file

    ❯ python3 zadanie_2.py
    Square(side=5)
    Rectangle(width=3, height=5)
    """
    main()