using System;


namespace Test
{


    public class BigNum
    {

        private static int SIZE = 10000;

        int[] liczba = new int[SIZE];

        public BigNum(int n)
        {
            for (int i = 0; i < SIZE; i++)
                liczba[i] = 0;
            
            int index = 0;
            while (n > 0)
            {
                liczba[index] = n % 10;
                n /= 10;
                index++;
            }


        }

        public BigNum()
        {
            for (int i = 0; i < SIZE; i++)
                liczba[i] = 0;
        }

        public void Wypisz()
        {
            int index = SIZE-1;
            while (index >= 0 && liczba[index] == 0)
            {
                index--;
            }

            for (int i = index; i >= 0; i--)
            {
                Console.Write(liczba[i]);
            }
            Console.WriteLine();
        }


        public BigNum Dodaj(BigNum n)
        {
            BigNum ww = new BigNum();
            int index = 0;

            while (index < SIZE)
            {
                ww.liczba[index] += liczba[index] + n.liczba[index];

                if (ww.liczba[index] > 9)
                {
                    ww.liczba[index] %= 10;
                    ww.liczba[index + 1] += 1;
                }

                index++;
            }
            return ww;
        }

        public BigNum Odejmij(BigNum n)
        {
            BigNum ww = new BigNum();
            int index = 0;
            while (index < SIZE-1)
            {

                if (n.liczba[index] > liczba[index])
                {
                    liczba[index] += 10;
                    liczba[index + 1]--;
                }
                ww.liczba[index] = liczba[index] - n.liczba[index];

                index++;
            }
            return ww;
        }

        public BigNum Pomnoz(BigNum n)
        {
            BigNum ww = new BigNum();

            int tmp = 0;
            int start = 0;
            while (n.liczba[start] != 0)
            {
                int index = 0;
                while (index + start < SIZE)
                {
                    ww.liczba[index + start] += liczba[index] * n.liczba[start];
                    ww.liczba[index + start] += tmp;
                    tmp = 0;

                    if (ww.liczba[index + start] > 9)
                    {
                        tmp = ww.liczba[index + start];
                        ww.liczba[index + start] = tmp % 10;
                        tmp /= 10;
                    }
                    index++;
                }
                start++;
            }

            return ww;
        }

        public bool CzyMniejsze(BigNum n)
        {
            for (int i = SIZE - 1; i >= 0; i--)
            {
                if (liczba[i] < n.liczba[i]) return true;
                if (liczba[i] > n.liczba[i]) return false;
            }

            return true;
        }

        public void Dodaj1()
        {
            int index = 0;
            liczba[index]++;
            while (liczba[index] > 9)
            {
                liczba[index] %= 10;
                liczba[index + 1]++;
                index++;
            }
        }

        public BigNum Podziel(BigNum n, BigNum m)
        {
            int index = SIZE-1;
            BigNum tmp = new BigNum(0);

            while(tmp.Pomnoz(m).CzyMniejsze(n))
            {
                //tmp.Pomnoz(m).Wypisz();
                //n.Wypisz();
                //Console.WriteLine("Wynik: "+tmp.Pomnoz(m).CzyMniejsze(n));
                //Console.WriteLine();
                tmp.Dodaj1();
            }

            return tmp;
        }

    }


    class MainClass
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");

            Console.Write("n1:  ");
            BigNum n1 = new BigNum(888888888);
            n1.Wypisz();

            Console.Write("n2:  ");
            BigNum n2 = new BigNum(999999999);
            n2.Wypisz();

            Console.Write("n3 = n1 + n2:  ");
            BigNum n3 = n1.Dodaj(n2);
            n3.Wypisz();

            Console.Write("n4 = n3 - n1:  ");
            BigNum n4 = n3.Odejmij(n1);
            n4.Wypisz();

            Console.Write("n5 = n3 * n2:  ");
            BigNum n5 = n3.Pomnoz(n2);
            n5.Wypisz();

            Console.Write("n7 = n3 ^2 :  ");
            BigNum n7 = n3.Pomnoz(n3);
            n7.Wypisz();

            Console.Write("n8 = n7 / n5 :  ");
            BigNum n8 = n7.Podziel(n7, n5);
            n8.Wypisz();


        }
    }
}
