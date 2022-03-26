from typing import Protocol

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


class ReportComposer:
    def __init__(
        self,
        report_printer: ReportPrinter,
        document_formatter: DocumentFormatter,
        printer_data: PrinterData,
    ) -> None:
        self._report_printer = report_printer
        self._document_formatter = document_formatter
        self._printer_data = printer_data


def main() -> None:
    report_composer = ReportComposer(
        report_printer=ReportPrinter(),
        document_formatter=DocumentFormatter(),
        printer_data=PrinterData(),
    )
