import React from 'react';
import { useRecoilValue } from 'recoil';
import styles from './BudgetCard.module.css';
import recordsState, { Type } from './Interfaces';

const BudgetCard = () => {
  const records = useRecoilValue(recordsState);

  const income = records.reduce(
    (prev, curr) => curr.type === Type.Income ? prev + curr.value : prev,
    0
  )

  const expenses = records.reduce(
    (prev, curr) => curr.type === Type.Expense ? prev + curr.value : prev,
    0
  )
  
  return (
    <div className={styles.BudgetCard}>
      <div className={styles.CardContent}>
        <span >Balance</span>
        <h3 >{income - expenses} $</h3>
      </div>

      <div className={styles.BottomContainer}>
        <div className='Income'>
          <p >Income</p>
          <p >{income}</p>
        </div>
        <div className='Expenses'>
          <p >Expenses</p>
          <p >{expenses}</p>
        </div>
      </div>
    </div>
  )
};

export default BudgetCard;