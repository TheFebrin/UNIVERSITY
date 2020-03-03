using System;

namespace Zad4
{
    public class List
    {
        public List previous;
        public List next;
        public string wyrazenie;

        public List(List previous, List next, string s)
        {
            this.previous = previous;
            this.next = next;
            this.wyrazenie = s;
        }
    }

    public class Dictionary
    {
        public List start;
        public List end;
        public int records;

        public Dictionary()
        {
            records = 0;
            start = null;
            end = start;
        }

        public void Add(string exp)
        {
            if (start == null) //lista jest pusta, to tworze nowa
            {
                List l = new List(null, null, exp);
                start = l;
                end = l;
            }
            else   //juz istnieje, to dopisuje do niej 
            {
                List l = new List(end, null, exp);
                end.next = l;
                end = l;
            }

            records++;
        }


        private bool IsAnyA(string s)
        {
            if (s == null) return false;
            return s.Contains("A");
        }

        private string GetNthExpression(int n)
        {
            List l = start;
            int index = 1;

            while (index != n)
            {
                index++;
                l = l.next;
            }
            return l.wyrazenie;
        }

        public string CreateRandom()
        {
            string s = "A";
            Random random = new Random();
            int counter = 1;

            while (IsAnyA(s))
            {
                Console.WriteLine(counter++ + ". krok: " + s);

                int a = random.Next(1, records);  //losowa liczba
                int index = s.IndexOf("A", StringComparison.Ordinal);     //znajduje pierwsze duze A

                s = s.Substring(0, index) + GetNthExpression(a) + s.Substring(index + 1);
            }
        
            return s;
        }
    }



    static class MainClass
    {
        static void Main(string[] args)
        {
            Dictionary s = new Dictionary();
            s.Add("aAa");
            s.Add("aAc");
            s.Add("dd");
            s.Add("AA");
            s.Add("");

            while (true)
            {
                int a;
                a = Console.Read();
                Console.WriteLine("Wynik: " + s.CreateRandom());
                Console.WriteLine();
            }
        }
    }
}