from abc import ABC, abstractmethod
"""
W taki sposób zaprojektowane klasy Rectangle i Square nie spełniają LSP.

W podklasie Kwadrat musimy zawsze ustawiać Height = Width, czyli ograniczamy klasę Rectangle.

LSP mówi, że jeżeli A jest podklasą B, to wszystkie obiekty typu B można zastąpić obiektami typu A.
Widzimy tutaj trudność w projektowaniu, każdy kwadrat jest prostokątem, lecz nie działa to na odwrót.

Potencjalnym rozwiązaniem mogłoby być odwrócenie relacji, tzn. teraz klasa Rectangle będzie dziedziczyć
z klasy Square i ją rozszerzać. Jest to jednak trochę dziwne. Prostokąt nie jest przecież Kwadratem.

Wprowadźmy zatem trzecią klasę Polygon, z której dziedziczyć będą Square oraz Rectangle.
Interfejs Rectangle nie wymusza implementacji setterów, wymusza jedynie gettery.
Dzięki temu LSP jest spełnione, ponieważ Square nie jest już podklasą Rectangle.
"""

class Polygon(ABC):

    @property
    @abstractmethod
    def width(self) -> int:
        pass

    @property
    @abstractmethod
    def height(self) -> int:
        pass


class Rectangle(Polygon):
    def __init__(self, width: int, height: int) -> None:
        self._width = width
        self._height = height

    @property
    def width(self) -> int:
        return self._width

    @width.setter
    def width(self, value: int) -> None:
        self._width = value

    @property
    def height(self) -> int:
        return self._height

    @height.setter
    def height(self, value: int) -> None:
        self._height = value


class Square(Polygon):
    def __init__(self, width: int) -> None:
        self._width = width
        
    @property
    def width(self) -> int:
        return self._width

    @width.setter
    def width(self, value: int) -> None:
        self._width = value

    @property
    def height(self) -> int:
        return self._width


class AreaCalculator:
    def __init__(self) -> None:
        pass
    
    def calculate_area(self, polygon: Polygon) -> int:
        return polygon.width * polygon.height


def main() -> None:
    w: int = 4
    h: int = 5

    square: Polygon = Square(width=w)
    rect: Polygon = Rectangle(width=w, height=h)

    calc: AreaCalculator = AreaCalculator()

    print(f'Square area: {calc.calculate_area(polygon=square)}')
    print(f'Rectangle area: {calc.calculate_area(polygon=rect)}')

    print(f'Is square an instance of Rectangle?: {isinstance(square, Rectangle)}')


if __name__ == '__main__':
    main()