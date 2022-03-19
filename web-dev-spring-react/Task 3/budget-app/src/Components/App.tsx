import React from 'react';
import {
  RecoilRoot,
  atom,
  selector,
  useRecoilState,
  useRecoilValue,
} from 'recoil';

// CSS
import './App.css';
// import styles from './App.module.css';

// material-ui
import { Box, Grid } from '@mui/material';
import Paper from "@mui/material/Paper";

// Components
import BudgetCard from './BudgetCard';
import AddIncomeOrExpense from './AddIncomeOrExpense'

function App() {
  return (
    <RecoilRoot>
        <Box className="App" >
          <Grid  
            container
            direction="row"
            justifyContent="center"
            alignItems="center"  
            spacing={2}
          >
            <Grid item xs={3} >
              <AddIncomeOrExpense/>
            </Grid>
            <Grid item xs={4}>
              <BudgetCard/>
            </Grid>
            <Grid item xs={3}>
              <AddIncomeOrExpense/>
            </Grid>
     
          </Grid>
        </Box>
    </RecoilRoot>
  );
}

export default App;
