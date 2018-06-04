package zad2;

public class Podziel extends Operator
{

    public Podziel(Wyrazenie w1, Wyrazenie w2) {
        super(w1,w2);
    }
    public double oblicz() {
        return w1.oblicz()/w2.oblicz();
    }
}
