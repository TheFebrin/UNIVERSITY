package drzewko;

interface Dict <T extends Comparable<T>>
{
 public boolean search(T data);
 public T min();
 public T max();

 public void insert(T data);
 public void remove (T data);

}
