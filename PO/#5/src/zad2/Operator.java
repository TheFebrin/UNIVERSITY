package zad2;

public abstract class Operator extends Wyrazenie{
    public Wyrazenie w1;
    public Wyrazenie w2;

    public Operator(Wyrazenie w1, Wyrazenie w2) {
        this.w1=w1;
        this.w2=w2;
    }
}