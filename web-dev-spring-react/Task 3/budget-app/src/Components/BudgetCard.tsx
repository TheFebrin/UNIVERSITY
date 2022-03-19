import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import Box from '@material-ui/core/Box';
import Card from '@material-ui/core/Card';
import CardContent from '@material-ui/core/CardContent';
import Divider from '@material-ui/core/Divider';
import AttachMoneyIcon from '@mui/icons-material/AttachMoney';

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
  subheader: {
    fontSize: 14,
    color: palette.grey[500],
    marginBottom: '0.875em',
  },
  statLabel: {
    fontSize: 12,
    color: palette.grey[500],
    fontWeight: 500,
    fontFamily:
      '-apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif, "Apple Color Emoji", "Segoe UI Emoji", "Segoe UI Symbol"',
    margin: 0,
  },
  statValue: {
    fontSize: 20,
    fontWeight: 'bold',
    marginBottom: 4,
    letterSpacing: '1px',
  },
}));

const BudgetCard = () => {
  const styles = useStyles();

  return (
    <Card className={styles.card}>
      <CardContent>
        <span className={styles.subheader}>Balance</span>
        <h3 className={styles.heading}>1230 $</h3>
      </CardContent>

      <Divider light />
      <Box sx={{ flexDirection: 'row', display: 'inline-flex' }} >
        <Box p={1} className='Income'>
          <p className={styles.statLabel}>Income</p>
          <p className={styles.statValue}>6941</p>
        </Box>
        <Box p={1} className='Expenses'>
          <p className={styles.statLabel}>Expenses</p>
          <p className={styles.statValue}>12</p>
        </Box>
      </Box>
    </Card>
  )
};

export default BudgetCard;