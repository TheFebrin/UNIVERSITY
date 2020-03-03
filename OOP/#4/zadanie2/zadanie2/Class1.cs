using System;
using System.Collections;

namespace Zadanie2
{
    public class Primes : IEnumerator
    {
        private int licznik;

        private bool PrimeCheck(int n)
        {
            if (n < 2) return false;

            for (int i = 2; i < n - 1; i++)
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
            return licznik < 100000;
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
}