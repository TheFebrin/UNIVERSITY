using System;

namespace Lista_leniwa
{
    public class List
    {
        public int id;
        public int value;
        public List next;
    }

    public class ListaLeniwa
    {
        public List start;
        public List act;
        public int dlugoscListy;

        public ListaLeniwa()
        {
            start = new List();
            act = start;
            dlugoscListy = 0;
        }


        public void Wypisz()
        {
            List lista = start.next;

            while (lista != null)
            {
                Console.Write(lista.value + " ");
                lista = lista.next;
            }
            Console.WriteLine();
            Console.WriteLine();
        }

        public void Dodaj(int nowy)
        {
            List nowaLista = new List();

            nowaLista.value = nowy;
            nowaLista.id = dlugoscListy;
            act.next = nowaLista;
            act = nowaLista;

            dlugoscListy++;
        }

    

        public virtual int element(int i, ListaLeniwa lista)
        {
            List temp = start;
            Random losuj = new Random();

            if (lista.size() >= i)
            {
                for (int j = 0; j < i; j++) temp = temp.next;
                return temp.value;
            }
            else
            {
                int rozmiar = i - lista.size();
                while (rozmiar > 0)
                {
                    lista.Dodaj(losuj.Next(100));
                    temp = temp.next;
                    rozmiar--;
                }
                return temp.value;
            }

        }

        public int size()
        {
            int ile = 0;
            List temp = start;

            while (temp.next != null)
            {
                ile++;
                temp = temp.next;
            }

            return ile;
        }
    }


    public class ListaPierwszych : ListaLeniwa
    {

        public int elementP(int KolejnaPierwsza, ListaLeniwa listaPierwszych)
        {
            List lista = start;
            KolejnaPierwsza--;

            if (listaPierwszych.size() >= KolejnaPierwsza)
            {
                for (int j = 0; j < KolejnaPierwsza; j++) lista = lista.next;
                return lista.value;
            }
            else
            {
                int SIZE = 10000;
                bool[] Pierwsze = new bool[SIZE];
                for (int i = 0; i < SIZE; i++) Pierwsze[i] = true;

                for (int i = 2; i < SIZE; i++)
                {
                    if (Pierwsze[i])
                        for (int j = i * i; j < SIZE; j += i)
                                Pierwsze[j] = false;

                }

                int index = 2;


                    for (index = 2; index < SIZE; index++)
                    {
                        if (Pierwsze[index] == true)
                        {
                            listaPierwszych.Dodaj(index);
                            lista = lista.next;
                            KolejnaPierwsza--;
                        }
                        if (KolejnaPierwsza < 0) break;
                    }
                   

                return lista.value;
            }
        }
    }


    class MainClass
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Hello World!\n");

            ListaLeniwa zwyklaLista = new ListaLeniwa();
            ListaPierwszych pierwsze = new ListaPierwszych();

            zwyklaLista.Dodaj(11);
            zwyklaLista.Dodaj(12);
            zwyklaLista.Dodaj(13);
            zwyklaLista.Dodaj(14);
            zwyklaLista.Dodaj(15);

            Console.Write("Lista: ");
            zwyklaLista.Wypisz();
            Console.WriteLine("Rozmiar listy to: " + zwyklaLista.size());
            zwyklaLista.element(20, zwyklaLista);
            Console.Write("Nowa lista: ");
            zwyklaLista.Wypisz();

          
            Console.WriteLine("10 pierwsza: " + pierwsze.elementP(10, pierwsze));
            pierwsze.Wypisz();




        }
    }
}
