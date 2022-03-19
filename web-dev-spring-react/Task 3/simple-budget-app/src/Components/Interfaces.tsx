import { atom } from "recoil";

export enum Type {
    Income = "Income",
    Expense = "Expense",
}

export interface IRecord {
    id: string;
    name: string;
    value: number;
    type: Type
}

const recordsState = atom({
    key: 'recordsState',
    default: [] as IRecord[],
});

export default recordsState;