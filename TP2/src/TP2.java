import java.io.*;
import java.util.*;

class Show {

    private String show_id;
    private String type;
    private String title;
    private String director;
    private String cast;
    private String country;
    private String date_added;
    private int release_year;
    private String rating;
    private String duration;
    private String listed_in;

    public Show() {
        show_id = "NaN";
        type = "NaN";
        title = "NaN";
        director = "NaN";
        cast = "NaN";
        country = "NaN";
        date_added = "March 1, 1900";
        release_year = 0;
        rating = "NaN";
        duration = "NaN";
        listed_in = "NaN";
    }

    public Show(String show_id, String type, String title, String director, String cast,
                String country, String date_added, int release_year, String rating,
                String duration, String listed_in) {
        this.show_id = show_id;
        this.type = type;
        this.title = title;
        this.director = director;
        this.cast = cast;
        this.country = country;
        this.date_added = date_added;
        this.release_year = release_year;
        this.rating = rating;
        this.duration = duration;
        this.listed_in = listed_in;
    }

    public Show clone() {
        return new Show(show_id, type, title, director, cast, country,
                date_added, release_year, rating, duration, listed_in);
    }

    public void imprimir() {
        System.out.print("=> " + show_id + " ## " + title + " ## " + type + " ## " +
                director + " ## [" + cast + "] ## " + country + " ## " + date_added + " ## " + release_year +
                " ## " + rating + " ## " + duration + " ## [" + listed_in + "]##\n");
    }

    public void ler(String linha) {
        String[] campos = new String[20];
        int campoIndex = 0;
        boolean entreAspas = false;
        String campoAtual = "";

        for (int i = 0; i < linha.length(); i++) {
            char c = linha.charAt(i);
            if (c == '"') {
                entreAspas = !entreAspas;
            } else if (c == ',' && !entreAspas) {
                campos[campoIndex++] = campoAtual.trim();
                campoAtual = "";
            } else {
                campoAtual += c;
            }
        }
        campos[campoIndex] = campoAtual.trim();

        show_id = getOrNaN(campos, 0);
        type = getOrNaN(campos, 1);
        title = getOrNaN(campos, 2);
        director = getOrNaN(campos, 3);
        cast = sortAndJoin(getOrNaN(campos, 4));
        country = getOrNaN(campos, 5);
        if (campos[6] == null || campos[6].equals("")) {
    date_added = "NaN";
} else {
    date_added = campos[6];
}
        try {
            release_year = Integer.parseInt(getOrNaN(campos, 7));
        } catch (Exception e) {
            release_year = 0;
        }
        rating = getOrNaN(campos, 8);
        duration = getOrNaN(campos, 9);
        listed_in = sortAndJoin(getOrNaN(campos, 10));
    }

    private String getOrNaN(String[] campos, int i) {
        return (i >= campos.length || campos[i] == null || campos[i].equals("")) ? "NaN" : campos[i];
    }

    private String sortAndJoin(String campo) {
        if (campo.equals("NaN")) return "NaN";
        String[] arr = new String[20];
        int index = 0;
        String temp = "";
        for (int i = 0; i < campo.length(); i++) {
            if (campo.charAt(i) == ',') {
                arr[index++] = temp.trim();
                temp = "";
            } else {
                temp += campo.charAt(i);
            }
        }
        arr[index++] = temp.trim();
        for (int i = 0; i < index - 1; i++) {
            for (int j = i + 1; j < index; j++) {
                if (arr[i].compareTo(arr[j]) > 0) {
                    String aux = arr[i];
                    arr[i] = arr[j];
                    arr[j] = aux;
                }
            }
        }
        String resultado = "";
        for (int i = 0; i < index; i++) {
            resultado += arr[i];
            if (i < index - 1) resultado += ", ";
        }
        return resultado;
    }

    public Object getShow_id() {
        return this.show_id;

    }
}

public class TP2 {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(System.in);
        Scanner sc = new Scanner(new File("/tmp/disneyplus.csv"));

        Show[] base = new Show[10000];
        int count = 0;

        String header = sc.nextLine(); // pula cabeçalho
        while (sc.hasNextLine()) {
            String linha = sc.nextLine();
            Show s = new Show();
            s.ler(linha);
            base[count++] = s;
        }

        String entrada = in.nextLine();
        while (!entrada.equals("FIM")) {
            for (int i = 0; i < count; i++) {
                if (base[i].getShow_id().equals(entrada)) {
                    base[i].imprimir();
                    break;
                }
            }
            entrada = in.nextLine();
        }

        in.close();
        sc.close();
    }
}
