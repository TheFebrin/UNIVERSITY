using System;


namespace Zad_1_dll
{
    class MainClass
    {
        public class Vertex<T>
    {
        public Vertex<T> prev;
        public Vertex<T> next;
        public T value;

        public Vertex(T a)
        {
            prev = null;
            next = null;
            value = a;
        }
    }

    public class Lista<T>
    {
        protected Vertex<T> first;
        protected Vertex<T> last;
        protected int size;

        public Lista()
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

        public void AddFirst(T a)
        {
            Vertex<T> v = new Vertex<T>(a);
            if (this.IsEmpty())
            {
                first = v;
                last = v;
            }
            else
            {
                first.prev = v;
                v.next = first;
                first = v;
            }
            size++;
        }
        public void AddLast(T a)
        {
            Vertex<T> v = new Vertex<T>(a);
            if (this.IsEmpty())
            {
                first = v;
                last = v;
            }
            else
            {
                last.next = v;
                v.prev = last;
                last = v;
            }
            size++;
        }

        public T RemoveFirst()
        {
            if (this.Size() == 1)
            {
                T a = first.value;
                first = null;
                last = null;
                size = 0;
                return a;
            }
            else
            {
                Vertex<T> v = first;
                first = first.next;
                first.prev = null;
                size--;
                return v.value;
            }
        }
        public T RemoveLast()
        {
            if (this.Size() == 1)
            {
                T a = last.value;
                first = null;
                last = null;
                size = 0;
                return a;
            }
            Vertex<T> v = last;
            last = last.prev;
            last.next = null;
            size--;
            return v.value;
        }
    }

        public static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
   
    }
}
