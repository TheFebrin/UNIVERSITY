import React, { useState } from 'react';
import { atom, selector, useRecoilState, useRecoilValue, useSetRecoilState } from 'recoil';
import styles from './DisplayList.module.css';
import { TiDelete } from 'react-icons/ti';
import recordsState, { IRecord, Type } from './Interfaces';

interface IElement {
    record: IRecord
}

function removeItemAtIndex(arr: IRecord[], index: number): IRecord[] {
    return [...arr.slice(0, index), ...arr.slice(index + 1)];
  }

const Element = (props: IElement) => {
    const [records, setRecords] = useRecoilState(recordsState);

    const handleDeleteElement = () => {
        const index = records.findIndex((listItem) => listItem.id === props.record.id);
        const newRecords = removeItemAtIndex(records, index);
        setRecords(newRecords);
	};

    const backgroundColor = props.record.type === Type.Income ? "rgb(20, 191, 134)" : "rgb(191, 20, 20)"; 
    return (
        <li id={props.record.id} className={styles.Container} style={{background: backgroundColor}}>
            <div className={styles.Paragraph}>{props.record.value}$</div>
            <div className={styles.Paragraph}>{props.record.name}</div>
            <TiDelete size='1em' onClick={handleDeleteElement} />
        </li>
    );
}

const DisplayList = () => {
  const records = useRecoilValue(recordsState);

  return (
    <div className={styles.DisplayList}>
        {records.map((record) => (
            <Element record={record}/>
        ))}
    </div>
  )
};

export default DisplayList;