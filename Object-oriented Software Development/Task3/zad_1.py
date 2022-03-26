from typing import Protocol

"""
Cztery wybranye zasady projektowych GRASP zilustrować przykładowym kompilującym się kodem.
Umieć uzasadnić, że zaproponowany kod rzeczywiście ilu- struje wybrane reguły.

* Creator 
    Klient otrzymuje od nas DeviceFactory, dzięki której może produkować różne obiekty typu Device.
    
* Low Coupling
    Używamy typowania strukturalnego (duck typing) przy użyciu Protocol, redukuje to znacząco Coupling, 
    ponieważ nie mamy tutaj jawnego implementowania interfejsu. Widzimy, że metoda test_device nie widzi
    żadnych szczegółow implementacyjnych. Nie potrzebny jej jest import zewnętrznego interfejsu, bo w miejscu
    w którym działa widzi odpowiedni protokół.

* High Cohesion
    Logika wewnątrz klas jest spójna.

* Protected Variations (Law of Demeter)
    Użytkownik funkcji test_device otrzymuje fabryke obiektów Device. 
    Typ Device jest stabilny i dobrze zaprojektowany dla użycia przez klienta.
    Zauważmy również, że dzięki temu ten użytkownik nie ma pojęcia, że ma do czynienia z obiektem typu SmartFridge,
    a tym bardziej nie wie nic o metodzie fridge_specific_function.

"""

class Device(Protocol):
    def connect(self) -> None:
        ...

    def disconnect(self) -> None:
        ...

    def beep(self) -> None:
        ...


class DeviceFactory(Protocol):

    def __call__(self) -> Device:
        ...


# Może być w oddzielnym pliku np. smart_fridge.py
class SmartFridge:
    def __init__(self, ip: str) -> None:
        self._ip = ip

    def connect(self) -> None:
        print('Connected!')

    def disconnect(self) -> None:
        print('Disconnected!')

    def beep(self) -> None:
        print(f'[{self._ip}] Beep!')

    def fridge_specific_function(self) -> None:
        pass


# Może być w oddzielnym pliku np. smart_fridge.py
class SmartFridgeFactory:
    def __init__(self, ip: str) -> None:
        self._ip = ip

    def __call__(self) -> SmartFridge:
        return SmartFridge(
            ip=self._ip
        )


def test_device(
    device_factory: DeviceFactory,
) -> None:
    device: Device = device_factory()

    device.connect()
    device.beep()
    device.disconnect()


def main() -> None:
    """
    Funkcja main może być w oddzielnym pliku, w którym wstrzykujemy odpowiednie implementacje klas.
    """
    test_device(
        device_factory = SmartFridgeFactory(ip='0.0.0.1')
    )

if __name__ == '__main__':
    main()
