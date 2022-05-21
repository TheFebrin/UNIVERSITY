import pytest
from zadanie1 import SimpleContainer, T, IFoo, Foo, Bar, TypeNotRegisteredError



class TestSimpleContainer:

    def test_not_registered_abstract(self) -> None:
        simple_container = SimpleContainer[T]()
        with pytest.raises(TypeNotRegisteredError):
            simple_container.resolve(t=IFoo)

    def test_not_registered_concrete(self) -> None:
        simple_container = SimpleContainer[T]()
        f: Foo = simple_container.resolve(t=Foo)
        assert isinstance(f, Foo)

    def test_register_type_singleton(self) -> None:
        simple_container = SimpleContainer[T]()
        simple_container.register_type(t=Bar, singleton=True)

        b1: Bar = simple_container.resolve(t=Bar)
        b2: Bar = simple_container.resolve(t=Bar)
        assert b1 == b2
        assert isinstance(b1, Bar)

    def test_register_type_transient(self) -> None:
        simple_container = SimpleContainer[T]()
        simple_container.register_type(t=Bar, singleton=False)

        b1: Bar = simple_container.resolve(t=Bar)
        b2: Bar = simple_container.resolve(t=Bar)
        assert b1 != b2
        assert isinstance(b1, Bar)
        assert isinstance(b2, Bar)

    @pytest.mark.parametrize('to_class', [Foo, Bar])
    def test_register_types_transient(self, to_class) -> None:
        simple_container = SimpleContainer[T]()
        simple_container.register_type(t=[IFoo, to_class], singleton=False)
        f: IFoo = simple_container.resolve(t=IFoo)
        assert isinstance(f, to_class) 

        