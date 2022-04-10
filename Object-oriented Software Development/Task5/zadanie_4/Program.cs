using System;
using System.Collections;

class Program
 {
     class ComparerAdapter<T> : IComparer
     {
        private readonly Comparison<T> _cmp;

        public ComparerAdapter(Comparison<T> cmp)
        {
            this._cmp = cmp;
        }
         public int Compare(object? a, object? b)
         {
            if(a == null || b == null)
            {
                throw new ArgumentNullException();
            }
            return this._cmp((T)a, (T)b);
         }
     }

     /* this is the Comparison<int> to be converted */
     static int IntComparer( int x, int y )
     {
         return x.CompareTo( y );
     }
 
     static void Main( string[] args )
     {
         ArrayList a = new ArrayList() { 1, 5, 3, 3, 2, 4, 3 };
 
         /* the ArrayList's Sort method accepts ONLY an IComparer */
         IComparer comparerAdapter = new ComparerAdapter<int>(IntComparer);
         a.Sort(comparerAdapter);
        
         foreach(var x in a) {
             Console.Write(x);
             Console.Write(' ');
         }
     }
 }