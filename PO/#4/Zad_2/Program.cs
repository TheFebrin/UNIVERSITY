using System;
using System.Collections;

namespace Zad_2
{
    public class Primes : IEnumerator
    {
        private int licznik;
        private int SIZE = Int16.MaxValue;

        private bool PrimeCheck(int n)  
        {
            if (n < 2) return false;

            for (int i = 2; i*i <= n; i++)
            {
                if (n % i == 0) return false;
            }

            return true;
        }

        public Primes()
        {
            licznik = 1;
        }

        public bool MoveNext()
        {
            licznik++;
            while (!PrimeCheck(licznik)) licznik++;
            return licznik < SIZE;
        }

        public void Reset()
        {
            licznik = 1;
        }

        public object Current
        {
            get
            {
                return licznik;
            }
        }


    }


    class PrimeCollection : IEnumerable
    {
        public IEnumerator GetEnumerator()
        {
            return new Primes();
        }
    }


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
