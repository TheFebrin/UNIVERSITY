from __future__ import annotations
import time
from typing import Dict, Optional
from concurrent.futures import ThreadPoolExecutor
from multiprocessing import Pool, Process
import threading
from threading import Lock
from collections import Counter
import mock
from mock import patch



class ProcessSingleton:
    """ jedna instancja dla całego procesu """
    
    _instance: Optional[ProcessSingleton] = None
    _lock: Lock = Lock()

    @classmethod
    def instance(cls) -> ProcessSingleton:
        # Podwojne sprawdzenie i blokada
        if cls._instance is None:
            with cls._lock:
                if cls._instance is None:
                    cls._instance = cls()
        return cls._instance


class ThreadSingleton:
    """ jedna instancja dla każdego wątka """

    _instance_per_thread: Dict[int, ThreadSingleton] = {}
    
    @classmethod
    def instance(cls) -> ThreadSingleton:
        thread_id = threading.get_ident()
        if thread_id not in cls._instance_per_thread:
            cls._instance_per_thread[thread_id] = cls()
                    
        return cls._instance_per_thread[thread_id]

    @classmethod
    def get_n_instances_created(cls) -> int:
        return len(cls._instance_per_thread)


class TimeSingleton:
    """ jedna instancja na co najwyej 5 sekund """
    
    INSTANCE_CREATION_TIMEOUT: float = 5.0
    _instance: Optional[TimeSingleton] = None
    _last_instance_created: float = time.time()

    _lock: Lock = Lock()


    @classmethod
    def _create_new_instance(cls) -> bool:
        should_create: bool = time.time() - TimeSingleton._last_instance_created >= TimeSingleton.INSTANCE_CREATION_TIMEOUT
        return cls._instance is None or should_create

    @classmethod
    def instance(cls) -> TimeSingleton:
        # Podwojne sprawdzenie i blokada
        if cls._create_new_instance():
            with cls._lock:
                if cls._create_new_instance():
                    cls._instance = cls()
                    cls._last_instance_created = time.time()
        return cls._instance



def test_process_singleton() -> None:
    futures = []
    n_objects = 100
    with ThreadPoolExecutor(max_workers=32) as executor:
        for i in range(n_objects):
            futures.append(executor.submit(ProcessSingleton.instance))

    # Wszystkie wątki powinny mieć ten sam obiekt
    objects = [future.result() for future in futures]
    for obj in objects:
        assert obj == objects[0]
        assert objects.count(obj) == n_objects


def test_thread_singleton() -> None:
    # Obiekty tworzone przez ten wątek powinny być takie same
    obj1 = ThreadSingleton.instance()
    obj2 = ThreadSingleton.instance()
    assert obj1 is obj2

    futures = []
    n_threads = 32
    with ThreadPoolExecutor(max_workers=32) as executor:
        for i in range(100):
            futures.append(executor.submit(ThreadSingleton.instance))
    
    objects = [future.result() for future in futures]
    # obiekty powinny być inne niz ten ktory stworzylismy wyzej
    for obj in objects:
        assert obj != obj1


@patch('time.time', side_effect=range(1000))  # kazde wywołanie time.time zwiększa czas o 1s
def test_time_singleton(patched_time_time: mock.mock.MagicMock) -> None:
    futures = []
    n_objects = 100
    with ThreadPoolExecutor(max_workers=32) as executor:
        for i in range(n_objects):
            futures.append(executor.submit(TimeSingleton.instance))

    objects = [future.result() for future in futures]
    # wszystkich roznych obiektow powinno byc tyle ile wątków 
    #   podzielić na to co ile zezwalamy na tworzenie nowego obiektu
    assert len(Counter(objects)) == n_objects // TimeSingleton.INSTANCE_CREATION_TIMEOUT


"""
# Testy jednostkowe

❯ pytest -vvvl -s zadanie_1.py
================================================================== test session starts ===================================================================                                                                                                                                     

zadanie_1.py::test_process_singleton PASSED
zadanie_1.py::test_thread_singleton PASSED
zadanie_1.py::test_time_singleton PASSED
"""