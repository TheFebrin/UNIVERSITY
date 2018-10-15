package zad2;
import java.util.HashMap;


public class Zmienna extends Wyrazenie
{
    public String zmienna;
    public static HashMap<String, Double> zbior = new HashMap<String, Double>();
    public Zmienna(String klucz, double wartosc) {
        zbior.put(klucz, wartosc);
    }
    public Zmienna(String klucz) {
        zmienna=klucz;
    }
    public double oblicz() {
        return zbior.get(zmienna);
    }
}
