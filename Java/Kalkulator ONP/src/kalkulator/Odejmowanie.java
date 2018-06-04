package kalkulator;


public class Odejmowanie extends Operator2Arg
{
    public Odejmowanie ()
    {
        super();
    }

    public double obliczWartosc () {
        return argument[0]-argument[1];
    }

}
