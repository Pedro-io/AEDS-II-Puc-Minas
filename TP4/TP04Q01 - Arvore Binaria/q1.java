import java.io.File;
import java.io.PrintWriter;
import java.util.Scanner;

class Shows {
    private String show_id;
    private String type;
    private String title;
    private String director;
    private String cast;
    private String country;
    private String data_added;
    private String release_date;
    private String rating;
    private String duration;
    private String listed_in;

    public Shows() {
    }

    public Shows(String show_id, String type, String title, String director, String cast, String country,
            String data_added, String release_date, String rating, String duration, String listed_in) {
        this.show_id = show_id;
        this.type = type;
        this.title = title;
        this.director = director;
        this.cast = cast;
        this.country = country;
        this.data_added = data_added;
        this.release_date = release_date;
        this.rating = rating;
        this.duration = duration;
        this.listed_in = listed_in;

    }

    public String getShow_id() {
        return show_id;
    }

    public void setShow_id(String show_id) {
        this.show_id = show_id;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getDirector() {
        return director;
    }

    public void setDirector(String director) {
        this.director = director;
    }

    public String getCast() {
        return cast;
    }

    public void setCast(String cast) {
        this.cast = cast;
    }

    public String getCountry() {
        return country;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    public String getData_added() {
        return data_added;
    }

    public void setData_added(String data_added) {
        this.data_added = data_added;
    }

    public String getRelease_date() {
        return release_date;
    }

    public void setRelease_date(String release_date) {
        this.release_date = release_date;
    }

    public String getRating() {
        return rating;
    }

    public void setRating(String rating) {
        this.rating = rating;
    }

    public String getDuration() {
        return duration;
    }

    public void setDuration(String duration) {
        this.duration = duration;
    }

    public String getListed_in() {
        return listed_in;
    }

    public void setListed_in(String listed_in) {
        this.listed_in = listed_in;
    }

    // Função que interpreta uma linha do CSV e separa os dados nos atributos.
    public static Shows ler(String linha) {
        Shows show = new Shows();
        String[] campos = new String[11];

        int campo = 0, i = 0, aspas = 0;
        String campoAtual = "";

        while (i < linha.length()) {
            char c = linha.charAt(i);

            if (c == '"') {
                aspas++;

            } else if (c == ',' && aspas % 2 == 0) {
                if (campoAtual.length() == 0) {
                    campos[campo] = "NaN";
                } else {
                    campos[campo] = campoAtual;
                }
                campo++;
                campoAtual = "";

            } else {
                campoAtual += c;
            }
            i++;
        }

        if (campo < 11) {
            if (campoAtual.length() == 0) {
                campos[campo] = "NaN";
            } else {
                campos[campo] = campoAtual;
            }
        }

        for (int j = campo + 1; j < 11; j++) {
            campos[j] = "NaN";
        }

        // Preenche os atributos do objeto Shows com os valores lidos.
        show.setShow_id(campos[0]);
        show.setType(campos[1]);
        show.setTitle(campos[2]);
        show.setDirector(campos[3]);
        show.setCast(campos[4]);
        show.setCountry(campos[5]);
        show.setData_added(campos[6]);
        show.setRelease_date(campos[7]);
        show.setRating(campos[8]);
        show.setDuration(campos[9]);
        show.setListed_in(campos[10]);

        return show;
    }

    // Transforma uma String em uma Lista, separando seus valores.

    public static ListaString transformarEmLista(String s) throws Exception {
        int n = 1;
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == ',') {
                n++;
            }
        }

        ListaString lista = new ListaString(n);

        int i = 0;
        while (i < s.length()) {
            String nome = "";

            while (i < s.length() && (s.charAt(i) == ' ' || s.charAt(i) == '"')) {
                i++;
            }

            while (i < s.length() && s.charAt(i) != ',') {
                if (s.charAt(i) != '"') {
                    nome += s.charAt(i);
                }
                i++;
            }

            lista.inserirFim(nome);

            if (i < s.length() && s.charAt(i) == ',')
                i++;
        }

        return lista;
    }

    // Metódo para imprimir os atributos da linha no formato pedido.

    public void imprimir() throws Exception {

        ListaString listaCast = Shows.transformarEmLista(cast);
        listaCast.ordenar();

        ListaString listaListed_in = Shows.transformarEmLista(listed_in);
        listaListed_in.ordenar();

        System.out.print("=> " + show_id + " ## " + title + " ## " + type + " ## " + director + " ## [");
        listaCast.mostrar();
        System.out.print("] ## " + country + " ## " + data_added + " ## " + release_date + " ## " + rating + " ## "
                + duration + " ## [");
        listaListed_in.mostrar();
        System.out.println("] ##");
    }

}

class ListaString {
    private String[] array;
    public int n;

    public ListaString() {

    }

    public ListaString(int tamanho) {
        array = new String[tamanho];
        n = 0;
    }

    // Metódo para inserção de uma String no fim da lista.

    public void inserirFim(String s) throws Exception {
        if (n >= array.length) {
            throw new Exception("Erro");
        }
        array[n] = s;
        n++;
    }

    // Metódo que ordena os elementos de uma ListaString em ordem alfabética.

    public void ordenar() {
        String temp;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (comparar(array[i], array[j]) > 0) {
                    temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
        }
    }

    // Metódo que compara duas strings em ordem lexicográfica.

    public int comparar(String x, String y) {
        int resp = 0;
        for (int i = 0; i < x.length() && i < y.length(); i++) {
            resp = x.charAt(i) - y.charAt(i);
            if (resp != 0) {
                return resp;
            }

        }
        resp = x.length() - y.length();
        return resp;
    }

    // Metódo que mostra os elementos da Lista.

    public void mostrar() {
        for (int i = 0; i < n; i++) {
            System.out.print(array[i]);
            if (i < n - 1) {
                System.out.print(", ");
            }
        }
    }

}

class No {
    Shows show;
    No esq;
    No dir;

    No(Shows show) {
        this(show, null, null);
    }

    No(Shows show, No esq, No dir) {
        this.show = show;
        this.esq = esq;
        this.dir = dir;
    }
}

class Arvore {
    static No raiz;
    public static int comparacoes = 0; // Adiciona contador de comparações

    Arvore() {
        raiz = null;
    }

    public void inserir(Shows s) throws Exception {
        raiz = inserir(s, raiz);
    }

    public static No inserir(Shows s, No i) throws Exception {
        if (i == null) {
            i = new No(s);
        } else if (s.getTitle().compareTo(i.show.getTitle()) < 0) {
            comparacoes++;
            i.esq = inserir(s, i.esq);
        } else if (s.getTitle().compareTo(i.show.getTitle()) > 0) {
            comparacoes++;
            i.dir = inserir(s, i.dir);
        } else {
            comparacoes++;
            throw new Exception("Erro");
        }
        return i;
    }

    public static boolean pesquisar(String s) {
        System.out.print("=>raiz ");
        boolean resultado = pesquisar(s, raiz);
        System.out.println(resultado ? "SIM" : "NAO");
        return resultado;
    }

    public static boolean pesquisar(String s, No i) {
        boolean resp;

        if (i == null) {
            comparacoes++;
            resp = false;
        } else if (i.show.getTitle().equals(s)) {
            comparacoes++;
            resp = true;
        } else if (s.compareTo(i.show.getTitle()) < 0) {
            comparacoes++;
            System.out.print("esq ");
            resp = pesquisar(s, i.esq);
        } else {
            comparacoes++;
            System.out.print("dir ");
            resp = pesquisar(s, i.dir);
        }

        return resp;
    }
}

public class q1 {

    public static Shows buscar(String caminhoArquivo, String idBuscado) throws Exception {
        Scanner sc = new Scanner(new File(caminhoArquivo), "UTF-8");
        Shows saida = null;
        boolean encontrado = false;

        while (sc.hasNextLine() && !encontrado) {
            String linha = sc.nextLine();
            Shows show = Shows.ler(linha);
            if (show.getShow_id().equals(idBuscado)) {
                saida = show;
                encontrado = true;
            }
        }

        sc.close();
        return saida;
    }

    public static void main(String[] args) throws Exception {
        long inicio = System.nanoTime(); // Início da contagem do tempo

        String file = "/tmp/disneyplus.csv";
        Scanner sc = new Scanner(System.in);
        Arvore arvore = new Arvore();

        String entrada = sc.nextLine();

        while (!entrada.equals("FIM")) {
            Shows input = buscar(file, entrada);
            if (input != null) {
                arvore.inserir(input);
            entrada = sc.nextLine();
            }
        }

        String chave = sc.nextLine();
        while (!chave.equals("FIM")) {
            Arvore.pesquisar(chave);
            chave = sc.nextLine();
        }

        sc.close();

        long fim = System.nanoTime(); // Fim da contagem do tempo
        double tempo = (fim - inicio) / 1e6; // tempo em milissegundos

        // Escreve o tempo e comparações em um arquivo de log
        PrintWriter log = new PrintWriter("793406_arvoreBinaria.txt");
        log.printf("793406\t%.3f\t%d\n", tempo, Arvore.comparacoes);
        log.close();
    }
}