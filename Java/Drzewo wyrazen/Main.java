import drzewa.*;
public class Main
{


public static void main(String[] args) //test

        {

            Zmienna x= new Zmienna("x",-1.1618);

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



        }
}
