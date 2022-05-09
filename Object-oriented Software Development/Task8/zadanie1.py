from abc import ABC, abstractmethod
from collections import deque
from typing import Deque, Optional
from concurrent.futures import ThreadPoolExecutor
from threading import Lock


class Receiver:

    def download_ftp(self, filename: str) -> None:
        """ Some business logic here """
        print(f'[{type(self).__name__}] Working on download_ftp.')

    def download_html(self, filename: str) -> None:
        """ Some business logic here """
        print(f'[{type(self).__name__}] Working on download_html.')

    def create_empty_file(self, filename: str) -> None:
        """ Some business logic here """
        print(f'[{type(self).__name__}] Working on create_empty_file.')

    def fill_file_random(self, filename: str) -> None:
        """ Some business logic here """
        print(f'[{type(self).__name__}] Working on fill_file_random.')
        
    def copy_file(self, filename_from: str, filename_to: str) -> None:
        """ Some business logic here """
        print(f'[{type(self).__name__}] Working on copy_file.')


class ICommand(ABC):

    @abstractmethod
    def execute(self) -> None:
        raise NotImplementedError


class DownloadFTPCommand(ICommand):
    
    def __init__(self, receiver: Receiver, filename: str) -> None:
        self._receiver = receiver
        self._filename = filename

    def execute(self) -> None:
        self._receiver.download_ftp(filename=self._filename)


class DownloadHTTPCommand(ICommand):

    def __init__(self, receiver: Receiver, filename: str) -> None:
        self._receiver = receiver
        self._filename = filename
        
    def execute(self) -> None:
        self._receiver.download_html(filename=self._filename)


class CreateRandomFileCommand(ICommand):

    def __init__(self, receiver: Receiver, filename: str) -> None:
        self._receiver = receiver
        self._filename = filename
        
    def execute(self) -> None:
        self._receiver.create_empty_file(filename=self._filename)
        self._receiver.fill_file_random(filename=self._filename)


class CopyFileCommand(ICommand):

    def __init__(
        self, receiver: Receiver, 
        filename: str,
        new_filename: str
    ) -> None:
        self._receiver = receiver
        self._filename = filename
        self._new_filename = new_filename
        
    def execute(self) -> None:
        self._receiver.copy_file(
            filename_from=self._filename, 
            filename_to=self._new_filename
        )



class Invoker:

    def __init__(self) -> None:
        self._commands_queue: Deque[ICommand] = deque()
        self._pool = ThreadPoolExecutor(max_workers=6)
        self._lock: Lock = Lock()

    def add_command(self, command: ICommand) -> None:
        with self._lock:
            self._commands_queue.append(command)

    def execute_command(self) -> None:
        cmd: Optional[ICommand] = None
        with self._lock:
            if len(self._commands_queue) > 0:
                cmd = self._commands_queue.popleft()
       
        if cmd is not None:
           self._pool.submit(cmd.execute)

    def execute_all_commands(self) -> None:
        while len(self._commands_queue) > 0:
            self.execute_command()


def main() -> None:
    invoker = Invoker()    
    receiver = Receiver()

    invoker.add_command(DownloadFTPCommand(receiver=receiver, filename='abc'))
    invoker.add_command(DownloadHTTPCommand(receiver=receiver, filename='abc'))
    invoker.add_command(CreateRandomFileCommand(receiver=receiver, filename='abc'))
    invoker.add_command(CopyFileCommand(receiver=receiver, filename='abc', new_filename='abc2'))

    invoker.execute_all_commands()


if __name__ == '__main__':
    main()