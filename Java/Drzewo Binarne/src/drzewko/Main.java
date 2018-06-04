package drzewko;

public class Main {

    public static void main(String[] args)
    {
	 BST<Integer> drzewo=new BST<Integer>();

	 drzewo.insert(2);
	 drzewo.insert(3);
	 drzewo.insert(6);
	 drzewo.insert(4);
	 drzewo.insert(1);
	 drzewo.insert(5);


	 System.out.println("Drzewo: "+drzewo+"\n");

	 drzewo.remove(4);
	 System.out.println("Drzewo po usunieciu 4: "+drzewo+"\n");



	 System.out.println("Szukanie liczby 5: "+drzewo.search(5));
	 System.out.println("Szukanie liczby 4: "+drzewo.search(4));
	 System.out.println("Najwieksza liczba w drzewie to: "+drzewo.max());
	 System.out.println("Najmniejsza liczba w drzewie to: "+drzewo.min()+"\n\n");

	 BST<String> drzewo2 = new BST<String>();

	 drzewo2.insert("Kacper");
	 drzewo2.insert("Adam");
	 drzewo2.insert("Bartek");
	 drzewo2.insert("Zuzia");
	 drzewo2.insert("Eustachy");
	 drzewo2.insert("Wojtek");

	 System.out.println("Drzewo2: "+drzewo2+"\n");

	 drzewo2.remove("Bartek");

	 System.out.println("Drzewo2 po usunieciu Bartka: "+drzewo2+"\n");

	 System.out.println("Szukanie Adama: "+drzewo2.search("Adam"));
	 System.out.println("Szukanie Bartka: "+drzewo2.search("Bartek"));

	 System.out.println("Najwiekszy: "+drzewo2.max());
	 System.out.println("Najmniejszy: "+drzewo2.min());


    }
}
