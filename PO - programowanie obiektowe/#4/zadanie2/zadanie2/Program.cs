using System;

namespace Zadanie2
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            PrimeCollection pc = new PrimeCollection();
            foreach (int p in pc)
                System.Console.WriteLine(p);
        }
    }
}