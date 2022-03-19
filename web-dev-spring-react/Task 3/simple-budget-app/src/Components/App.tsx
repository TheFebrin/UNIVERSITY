import React from 'react';
import {
  RecoilRoot,
  atom,
  selector,
  useRecoilState,
  useRecoilValue,
} from 'recoil';


// CSS
import styles from './App.module.css';
// import styles from './App.module.css';

// Components
import BudgetCard from './BudgetCard';
import AddIncomeOrExpense from './AddIncomeOrExpense'
import DisplayList from './DisplayList';
import { Type } from './Interfaces';

function App() {
  return (
    <RecoilRoot>
        <div className={styles.App} >
          <div className={styles.TopPanel}>
            <AddIncomeOrExpense type={Type.Income}/>
            <BudgetCard/>
            <AddIncomeOrExpense type={Type.Expense}/>
          </div>
          <div className={styles.BotPanel}>
            <DisplayList/>
          </div>
        </div>
    </RecoilRoot>
  );
}

export default App;
