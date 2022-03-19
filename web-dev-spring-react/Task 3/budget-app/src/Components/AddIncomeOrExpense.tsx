import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import Box from '@material-ui/core/Box';
import Card from '@material-ui/core/Card';
import CardContent from '@material-ui/core/CardContent';
import Divider from '@material-ui/core/Divider';
import InputBase from '@material-ui/core/InputBase';
import AttachMoneyIcon from '@mui/icons-material/AttachMoney';
import { Button } from '@mui/material';

const useStyles = makeStyles(({ palette }) => ({
  card: {
    borderRadius: 12,
    textAlign: 'center',
  },
  heading: {
    fontSize: 18,
    fontWeight: 'bold',
    letterSpacing: '0.5px',
    marginTop: 8,
    marginBottom: 0,
  },
  button: {
    // fontSize: 12,
    // color: palette.grey[500],
    // fontWeight: 500,
    fontFamily:
      '-apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif, "Apple Color Emoji", "Segoe UI Emoji", "Segoe UI Symbol"',
    margin: 0,
  },
}));

const AddIncomeOrExpense = () => {
  const styles = useStyles();

  return (
    <Card className={styles.card}>
      <CardContent>
        <InputBase  className={styles.heading} placeholder={'Add expense'} />
      </CardContent>
      <Divider light />
      <Box >
        <Button className={styles.button}>Button</Button>
      </Box>
    </Card>
  )
};

export default AddIncomeOrExpense;