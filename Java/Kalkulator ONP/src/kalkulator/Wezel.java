package kalkulator;


public class Wezel<T>
{
    public Wezel<T> next;

    public Wezel<T> previous;

    public T in;




    public Wezel(T in)
    {
        this.next=null;
        this.previous=null;
        this.in=in;
    }
}