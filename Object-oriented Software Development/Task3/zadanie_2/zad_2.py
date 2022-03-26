from typing import Protocol

"""
Przed refactorem
"""

class ReportPrinterBefore:

    def __init__(self) -> None:
        pass

    def get_data(self) -> str:
        pass

    def format_document(self) -> None:
        pass

    def print_report(self) -> None:
        pass


"""
Po refactorze
"""

class ReportPrinter:

    def __init__(self) -> None:
        pass

    def print_report(self) -> None:
        pass


class DocumentFormatter:

    def __init__(self) -> None:
        pass

    def format_document(self) -> None:
        pass


class PrinterData:

    def __init__(self) -> None:
        pass

    def get_data(self) -> str:
        pass


class Printer:
    def __init__(
        self,
        report_printer: ReportPrinter,
        document_formatter: DocumentFormatter,
        printer_data: PrinterData,
    ) -> None:
        self._report_printer = report_printer
        self._document_formatter = document_formatter
        self._printer_data = printer_data

"""
* Interfejsy i ich implementacja zostały tu pominięte w celu uproszczenia, 
    w ładnym rozwiązaniu klasa Printer powinna przyjmować interfejsy w konstruktorze.

Ile klas docelowo powstanie z takiej jednej klasy? 
- W tym wypadku 3 + 1 dodatkowa, która komponuje te 3 klasy

Dlaczego akurat tyle? 
- Kwestia dobrego wyczucia.

Czy refaktoryzacja klasy naruszającej SRP oznacza automatycznie, że każda metoda powinna trafić do osobnej klasy?
- Nie, kilka metod może trafić do tej samej nowej klasy.
"""