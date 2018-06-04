package kalkulator;

public class Lista<T>
{
    Wezel<T> first;
    Wezel<T>last;

    public Lista(T in)
    {
        Wezel<T> w= new Wezel<T>(in);
        this.first=w;
        this.last=w;
    }


    public void Beggining(T in)
    {
        Wezel<T> w1= new Wezel<T>(in);
        w1.next=first;
        first.previous=w1;
        first=w1;

    }

    public void End(Wezel<T> w1)
    {
        last.next=w1;
        w1.previous=last;
        last=w1;
    }

    public boolean Empty()
    {
        if(first==null) return true;
        else return false;
    }

    public T Get()
    {
        Wezel<T> w=first;
        first=first.next;
        first.previous=null;
        return w.in;
    }

    public T GetInput()
    {
        return first.in;
    }
}