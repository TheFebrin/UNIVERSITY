using System;


namespace Zad_1_dll
{
    public class EmptyClass
    {
        class MainClass
        {
            public static void Main(string[] args)
            {
                Lista<int> lis = new Lista<int>();
                Console.WriteLine(lis.IsEmpty());
                for (int i = 5; i < 8; i++)
                {
                    lis.AddFirst(i);
                    lis.AddLast(i + 42);
                }
                Console.WriteLine(lis.RemoveFirst());
                Console.WriteLine(lis.RemoveFirst());
                Console.WriteLine(lis.RemoveLast());
                Console.WriteLine(lis.RemoveFirst());
                Console.WriteLine(lis.RemoveLast());
                Console.WriteLine(lis.RemoveLast());
            }
        }
    }
}
