package zad1;

public class Main <T extends Comparable>
{


    public static void main(String[] args)
    {
        Collection c = new Collection<Integer>();
        c.add(4);
        c.add(3);
        c.add(2);
        c.add(0);
        System.out.print("Kolekcja: ");
        c.writeAll();
        System.out.println();
        System.out.println("Usuwam najmniejszy: " + c.removeSmallest());
        System.out.println("Usuwam najmniejszy: " + c.removeSmallest());
        System.out.print("Kolekcja: ");
        c.writeAll();



    }
}
