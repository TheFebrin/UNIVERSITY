using System;

namespace zad2

{
    public class Pair<K, V> where K:IComparable
    {
        public K first;
        public V second;

        public Pair (K k, V v)
        {
            first = k;
            second = v;
        }

    }
    
    public class Vertex<K,V> where K:IComparable
    {
        public Vertex<K,V> prev;
        public Vertex<K,V> next;
        public Pair<K, V> rec;

        public Vertex(Pair<K,V> r)
        {
            prev = null;
            next = null;
            rec = r;
        }
    }

    public class Dict<K,V> where K:IComparable
    {
        protected Vertex<K,V> first;
        protected Vertex<K,V> last;
        protected int size;

        public Dict()
        {
            first = null;
            last = null;
            size = 0;
        }

        public int Size() => size;
        public bool IsEmpty()
        {
            if (size == 0)
                return true;
            return false;
        }

        public void Add(K k, V v)
        {
            Vertex<K,V> ver = new Vertex<K,V>(new Pair<K, V>(k,v));
            if (this.IsEmpty())
            {
                first = ver;
                last = ver;
            }
            else
            {
                first.prev = ver;
                ver.next = first;
                first = ver;
            }
            size++;
        }

        public V Find(K k)
        {
            return this.Findver(k).rec.second;
        }

        private Vertex<K,V> Findver(K k)
        {
            Vertex<K, V> ver = first;
            while (k.CompareTo(ver.rec.first)!=0)
            {
                ver = ver.next;
            }
            return ver;
        }

        public void Remove(K k)
        {
            Vertex<K, V> ver = Findver(k);
            ver.prev.next = ver.next;
            ver.next.prev = ver.prev;
            size--;
        }
         

    }

    class Program
    {
        static void Main()
        {
            Dict<string, int> dict = new Dict<string, int>();
            dict.Add("2+2", 4);
            dict.Add("4-1", 3);
            dict.Add("math", 42);
            Console.WriteLine("Rozmiar slownika: " + dict.Size());
            Console.WriteLine("Szukam:D 2+2: " + dict.Find("2+2"));
            Console.WriteLine("Szukam 4-1 : " + dict.Find("4-1"));
            dict.Remove("4-1");
            Console.WriteLine("Size usunieciu :  " + dict.Size());
        }
    }
}