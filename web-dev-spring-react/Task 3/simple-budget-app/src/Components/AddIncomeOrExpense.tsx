import React, { useState } from 'react';
import { atom, selector, useRecoilState, useRecoilValue, useSetRecoilState } from 'recoil';
import styles from './AddIncomeOrExpense.module.css';
import recordsState, { IRecord, Type } from './Interfaces';
import { v4 as uuidv4 } from 'uuid';


interface AddIncomeOrExpenseProps {
  type: Type
}

const AddIncomeOrExpense = (props: AddIncomeOrExpenseProps) => {
  const setRecord = useSetRecoilState(recordsState);

  const [name, setName] = useState<string>("");
  const [value, setValue] = useState<number>(0);

  const onChangeName = (e: React.ChangeEvent<HTMLInputElement>): void => {
    setName(e.target.value); 
  };

  const onChangeValue = (e: React.ChangeEvent<HTMLInputElement>): void => {
    if(e.target.value === "") {
      setValue(0);
    }
    else {
      setValue(parseInt(e.target.value));
    }
  };

  const onClick = (): void => {
    if (value > 0 && name.length > 0) {
      setRecord((oldRecord) => [
        ...oldRecord,
        {
          id: uuidv4(),
          name: name,
          value: value,
          type: props.type
        },
      ]);
      setName('');
      setValue(0);
    }
  };
  
  const title = props.type === Type.Income ? "Add Income" : "Add Expense";
  const backgroundColor = props.type === Type.Income ? "#007D54" : "#A92828";
  return (
    <div className={styles.AddIncomeOrExpense} style={{background: backgroundColor}}>
        <h3>{title}</h3>
        <p>Name</p>
        <input className={styles.Input} type="text" value={name} onChange={onChangeName} />
        <p>Value</p>
        <input className={styles.Input} type="text" pattern="[0-9]*" value={value} onChange={onChangeValue} />
        <button className={styles.Button} onClick={onClick}>Save</button>
    </div>
  )
};

export default AddIncomeOrExpense;