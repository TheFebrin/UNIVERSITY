package zad2;

public class Main
{

    public static void main(String[] args)
    {
        new Zmienna("x", 4);
        new Zmienna("y", 10);

        Wyrazenie w = new Dodaj   // 4*10 + 10 - 5  = 45
                (new Pomnoz
                        (new Zmienna("x"), new Stala(10)),

                new Odejmij
                        (new Zmienna("y"), new Stala(5)));

        System.out.println(w.oblicz());

        System.out.println("Koniec");

    }
}
