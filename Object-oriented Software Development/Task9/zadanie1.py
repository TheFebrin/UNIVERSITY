from typing import Generic, Sequence, TypeVar, Tuple, Dict, Callable, Type
from abc import ABC, ABCMeta, abstractmethod
import inspect


T = TypeVar('T')
From = TypeVar('From')
To = TypeVar('To')


class TypeNotRegisteredError(Exception):
    pass


class RegisterPolicy(ABC, Generic[T]):
    
    def __call__(self) -> T:
        raise NotImplementedError


class RegisterSingletonPolicy(RegisterPolicy[T], Generic[T]):

    def __init__(self, obj_instance: T) -> None:
        self._obj = obj_instance

    def __call__(self) -> T:
        return self._obj


class RegisterTransientPolicy(RegisterPolicy[T], Generic[T]):

    def __init__(self, obj_class: Type[T]) -> None:
        self._obj = obj_class

    def __call__(self) -> T:
        return self._obj()


class SimpleContainer(Generic[T]):

    _registered_types: Dict[Type[T], RegisterPolicy[T]] = {}

    @classmethod
    def register_type(cls, t: Type[T], singleton: bool) -> None:
        """
        If singleton is True then lifetime policy is singleton,
        transient otherwise.
        """
        if isinstance(t, Sequence):
            assert len(t) == 2, f'This should be a types pair: {t}'
            _from, _to = t
            if singleton:
                cls._registered_types[_from] = RegisterSingletonPolicy(_to())
            else:
                cls._registered_types[_from] = RegisterTransientPolicy(_to)
        elif isinstance(t, type):
            if singleton:
                cls._registered_types[t] = RegisterSingletonPolicy(t())
            else:
                cls._registered_types[t] = RegisterTransientPolicy(t)
        else:
            raise RuntimeError(f'Unknown generic type: {t}')

    @classmethod
    def resolve(cls, t: Type[T]) -> T:
        if t in cls._registered_types:
            return cls._registered_types[t]()
        else:
            if inspect.isabstract(t):
                raise TypeNotRegisteredError(f'Abstract type: {t} not registered. Can not resolve.')
            else:
                return t()

           
class IFoo(ABC):

    @abstractmethod
    def foo(self) -> None:
        pass


class Foo(IFoo):
    
    def foo(self) -> None:
        pass


class Bar(IFoo):
    
    def foo(self) -> None:
        pass




