package drzewko;

public class BST <T extends Comparable<T>> implements Dict<T>
{
    private class Node <T extends Comparable<T>> //klasa node
    {
        public Node<T> left, right, parent;
        public T data;


        public Node(T data)  //konstruktor node
        {
            left=null;
            right=null;
            parent=null;
            this.data=data;
        }

        public String toString()  //wypisywanie wezlow
        {
            String lewy="";
            if(this.left!=null) lewy=this.left.toString();

            String prawy="";
            if(this.right!=null) prawy=this.right.toString();

            return lewy+" "+this.data.toString()+" "+prawy;

        }


    }


    private Node<T> root;
    int size;


    public BST() //konstruktor drzewa
    {
        root=null;
        size=0;
    }

    public int size() //zwraca rozmiar
    {
        return size;

    }

    public void clear() //czysci drzewo
    {
        root=null; size=0;
    }



    public boolean search(T data)
    {
        Node<T> srch=root;

        while (srch!=null && srch.data!=data)
        {
            if(srch.data.compareTo(data)<0)
            {
                srch=srch.right;
            }
            else srch=srch.left;
        }
        if(srch==null) return false; else return true;
    }

    public Node<T> findNode(T data) throws IllegalArgumentException
    {
        Node<T>  x=root;

        while (x.data.compareTo(data)!=0 && x!=null)
        {
            if(x.data.compareTo(data)<0)
            {
                x=x.right;
            }
            else x=x.left;
        }
        if(x!=null) return x;
        else throw new IllegalArgumentException("NIE ZNALEZIONO W DRZEWIE");
    }

    public T min()
    {
        Node<T> x=root;
        while (x.left!=null)
        {
            x=x.left;
        }
        return x.data;
    }

    public T max()
    {
        Node<T> x=root;
        while(x.right!=null)
        {
            x=x.right;
        }
        return x.data;
    }
    public Node<T> next(Node<T> delete)  //najmiejszy od nastepnego wiekszego
    {
        Node<T> x=delete.right;
        while (x.left!=null)
        {
            x=x.left;
        }
        return x;
    }


    public void insert (T data) throws NullPointerException
    {
        if(data==null) throw new NullPointerException("BLAD, DODANO WARTOSC NULL");

        if(root==null)
        {
            root=new Node<T>(data);
            size=1;
        }
        else
        {
            size++;
            Node<T> sparent=null;
            Node<T> son=root;

            while (son!=null)
            {
                sparent=son;
                if(data.compareTo(son.data)>0)
                {
                    son=son.right;
                }
                else  son=son.left;
            }
            if(sparent.data.compareTo(data)>0)
            {
             Node<T> n=new Node<T>(data);
             n.parent=sparent;
             sparent.left=n;
            }
            else
            {
                Node<T>n=new Node<T>(data);
                n.parent=sparent;
                sparent.right=n;
            }
        }
    }


    public void remove(T data)
    {

        if(search(data)) {

            Node<T> delete = findNode(data); size--;

            if (delete.left == null && delete.right != null)   //prawy
            {
                if (delete.data.compareTo(delete.parent.data) > 0)
                {
                    delete.parent.right = delete.right;
                } else
                    delete.parent.left = delete.right;

                delete.right.parent = delete.parent;


            }


            else if (delete.right == null && delete.left != null)   //lewy
            {
                if (delete.data.compareTo(delete.parent.data) > 0)
                {
                    delete.parent.right = delete.right;
                } else
                    delete.parent.left = delete.left;

                delete.left.parent = delete.parent;


            }


            else if (delete.right == null && delete.left == null)  //null
            {
                if (delete.data.compareTo(delete.parent.data) > 0)   // jezeli delete.parent.data jest wieksze leksykalnie
                {
                    delete.parent.right = null;
                }
                else delete.parent.left = null;
            }

            else
                {
                Node<T> next = next(delete);

                delete.data = next.data;

                if (next == delete.right)
                {
                    delete.right = next.right;
                }
                else next.parent.left = next.right;
                }
        }
        else throw new IllegalArgumentException("NIE MOZNA USUNAC CZEGOS CZEGO NIE MA W DRZEWIE");
    }

    public String toString () {
        if(root!=null)
        {
            return root.toString();
        }
        else return "EMPTY";
    }
}

