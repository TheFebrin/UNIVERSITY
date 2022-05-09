from __future__ import annotations

from abc import ABC, abstractmethod
from multiprocessing.connection import wait


class IState(ABC):

    @abstractmethod
    def execute(self) -> IState:
        raise NotImplementedError


class WaitingForUserState(IState):

    def __init__(self, wait: bool) -> None:
        self._wait = wait
        
    def __repr__(self) -> str:
        return type(self).__name__

    def execute(self) -> IState:
        if self._wait:
            print(f'[{type(self).__name__}] Waiting for user ...')
            return WaitingForUserState(wait=True)
        else:
            return TicketSelectionState()


class TicketSelectionState(IState):

    def __repr__(self) -> str:
        return type(self).__name__

    def execute(self) -> IState:
        return PayForTicketState()


class PayForTicketState(IState):
    
    def __repr__(self) -> str:
        return type(self).__name__

    def execute(self) -> IState:
        return PaymentSummaryState(user_paid=True)


class PaymentSummaryState(IState):

    def __init__(self, user_paid: bool) -> None:
        self._user_paid = user_paid

    def __repr__(self) -> str:
        return type(self).__name__

    def execute(self) -> IState:
        if self._user_paid:
            return FinalizeState()
        else:
            return TicketSelectionState()
        

class FinalizeState(IState):

    def __repr__(self) -> str:
        return type(self).__name__

    def execute(self) -> IState:
        return WaitingForUserState(wait=True)


class StateMachine:

    def __init__(self, beg_state: IState) -> None:
        self._state = beg_state

    def __repr__(self) -> str:
        return type(self).__name__

    def step(self) -> None:
        print(f'[{type(self).__name__}] Started transition from state: {self._state}')
        self._state = self._state.execute()
        print(f'[{type(self).__name__}] Now in state: {self._state}')


def main() -> None:
    state_machine = StateMachine(beg_state=WaitingForUserState(wait=False))
    # .step should be triggered by some domain events
    state_machine.step()
    state_machine.step()
    state_machine.step()
    state_machine.step()
    state_machine.step()
    state_machine.step()
    state_machine.step()


if __name__ == '__main__':
    main()  