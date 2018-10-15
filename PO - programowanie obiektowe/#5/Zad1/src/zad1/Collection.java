package zad1;

public class Collection<T extends Comparable<? super T>>
{
    class List
    {
        List previous;
        List next;
        T value;

        List(List previous, T value)
        {
            this.previous = previous;
            this.value = value;
        }
    }

    private List start;
    private List end;

    public Collection()
    {
        start = null;
        end = null;
    }

    public void add(T value)
    {
        if (start == null)
        {
            List l = new List(null, value);
            l.next = null;
            start = l;
            end = l;
        }
        else
        {
            List l = start;

            while ((l != null) && (value.compareTo(l.value) > 0))
                l = l.next;

            if (l == start)
            {
                List n = new List(null, value);
                n.next = start;
                start.previous = n;
                start = n;
            }
            else if (l == null)
            {
                List n = new List(end, value);
                end.next = n;
                end = n;
            }
            else
            {
                l = l.previous;
                List n = new List(l, value);
                l.next.previous = n;
                n.next = l.next;
                l.next = n;
            }
        }
    }

    public void writeAll()
    {
        List l = start;

        while (l != null)
        {
            System.out.print(l.value + " ");
            l = l.next;
        }
    }

    public T removeSmallest()
    {
        T removed;

        if (start != null)
        {
            removed = start.value;

            if (start.next == null)
            {
                start = null;
                end = null;
            }
            else
            {
                start = start.next;
                start.previous = null;
            }
        }
        else
        {
            System.err.println("Empty list!");
            return null;
        }
        return removed;
    }
}