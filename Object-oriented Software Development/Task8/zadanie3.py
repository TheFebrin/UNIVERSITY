from abc import ABC, abstractmethod


class IDataAccessStrategy(ABC):

    @abstractmethod
    def connect_to_data(self) -> None:
        raise NotImplementedError

    @abstractmethod
    def download_data(self) -> None:
        raise NotImplementedError

    @abstractmethod
    def transform_data(self) -> None:
        raise NotImplementedError

    @abstractmethod
    def close_connection_to_data(self) -> None:
        raise NotImplementedError


class DataAccessHandler:

    def __init__(self, strategy: IDataAccessStrategy) -> None:
        self._strategy = strategy

    def execute(self) -> None:
        self._strategy.connect_to_data()
        self._strategy.download_data()
        self._strategy.transform_data()
        self._strategy.close_connection_to_data()


class DataBaseDataStrategy(IDataAccessStrategy):

    def __init__(self) -> None:
        self._state = {}  # Could be a specific object

    def _column_sum(self) -> int:
        print(f'[{type(self).__name__}] _column_sum.')
        return 0

    def connect_to_data(self) -> None:
        print(f'[{type(self).__name__}] connect_to_database.')

    def download_data(self) -> None:
        print(f'[{type(self).__name__}] download_data.')

    def transform_data(self) -> None:
        print(f'[{type(self).__name__}] transform_data.')
        self._state['column_sum'] = self._column_sum()

    def close_connection_to_data(self) -> None:
        print(f'[{type(self).__name__}] close_connection_to_data.')


class XMLDataStrategy(IDataAccessStrategy):

    def __init__(self) -> None:
        self._state = {}  # Could be a specific object
    
    def _find_longest_node(self) -> str:
        print(f'[{type(self).__name__}] _find_longest_node.')
        return 'abc'

    def connect_to_data(self) -> None:
        print(f'[{type(self).__name__}] connect_to_data.')

    def download_data(self) -> None:
        print(f'[{type(self).__name__}] download_data.')

    def transform_data(self) -> None:
        print(f'[{type(self).__name__}] transform_data.')
        self._state['longest_node'] = self._find_longest_node()

    def close_connection_to_data(self) -> None:
        print(f'[{type(self).__name__}] close_connection_to_data.')


def main() -> None:
    data_base_data = DataAccessHandler(strategy=DataBaseDataStrategy())
    xml_data =DataAccessHandler(strategy=XMLDataStrategy())

    data_base_data.execute()
    xml_data.execute()

if __name__ == '__main__':
    main()