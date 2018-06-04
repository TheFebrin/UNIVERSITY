import drzewa.*;

/**
 * project created by Dawid Dieu
 * 11/6/2017
 */
public class Test
{


    public static void main(String[] args) //test

    {

        Zmienna x= new Zmienna("x",-1.1618);
        Zmienna y= new Zmienna("y",2.0);

            /*DODAWANIE*/
        Wyrazenie w = new Dodawanie(new Stala(7), new Stala(5));
        System.out.println(w+" = "+w.oblicz());

            /*MNOZENIE*/
        w=new Dodawanie(new Stala(2),new Mnozenie(x,new Stala(7)));
        System.out.println(w+" = "+w.oblicz());

            /*DZIELENIE*/
        w=new Dzielenie
                (new Odejmowanie
                        (new Mnozenie
                                (new Stala(3),new Stala(11)), new Stala(1)),

                        new Dodawanie(new Stala(7),new Stala(5)));

        System.out.println(w+" = "+w.oblicz());

        /*ARC TAN*/
        w=new Arctan(new Dzielenie(
                new Mnozenie(new Dodawanie(new Stala(13),x),x),new Stala(2)));

        System.out.println(w+" = "+w.oblicz());


        /*POWER * LOG*/

        w=new Dodawanie(
                new Potegowanie(new Stala(2),new Stala(5)), new Mnozenie(
                        x,new Logarytmowanie(new Stala(2),y)));
        System.out.println(w+" = "+w.oblicz());

    }
}
