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
    private int release_date;
    private String rating;
    private String duration;
    private String listed_in;

    public Shows() {
    }

    public Shows(String show_id, String type, String title, String director, String cast, String country,
            String data_added, int release_date, String rating, String duration, String listed_in) {
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

    public int getRelease_date() {
        return release_date;
    }

    public void setRelease_date(int release_date) {
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

    // Metódo para ler uma linha do CSV e separar seus atributos.

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

        // Atribui os campos lidos aos respectivos atributos da Classe Shows.
        show.setShow_id(campos[0]);
        show.setType(campos[1]);
        show.setTitle(campos[2]);
        show.setDirector(campos[3]);
        show.setCast(campos[4]);
        show.setCountry(campos[5]);
        show.setData_added(campos[6]);
        show.setRelease_date(Integer.parseInt(campos[7]));
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

class No1 {
    int chave;
    No1 esq, dir;
    No2 raiz;

    No1(int chave) {
        this(chave, null, null, null);
    }

    No1(int chave, No1 esq, No1 dir, No2 raiz) {
        this.chave = chave;
        this.esq = esq;
        this.dir = dir;
        this.raiz = raiz;
    }
}

class No2 {
    String chave;
    No2 esq, dir;
    Shows show;

    No2(String chave) {
        this(chave, null, null, null);
    }

    No2(String chave, No2 esq, No2 dir, Shows show) {
        this.chave = chave;
        this.esq = esq;
        this.dir = dir;
        this.show = show;
    }
}

class Arvore {
    static No1 raiz;
    public static int comparacoes = 0; // Adiciona contador de comparações

    Arvore() {
        raiz = null;
    }

     // Inserção na árvore primária (por releaseYear % 15)
    public static void inserirNo1(int x) throws Exception {
        raiz = inserirNo1(x, raiz);
    }

    public static No1 inserirNo1(int x, No1 i) throws Exception {
        if (i == null) {
            return new No1(x);
        } else if (x < i.chave) {
            i.esq = inserirNo1(x, i.esq);
        } else if (x > i.chave) {
            i.dir = inserirNo1(x, i.dir);
        } else {
            throw new Exception("Erro: chave duplicada na árvore 1");
        }
        return i;
    }

    // Inserção de Shows: navega na árvore 1 e insere na árvore 2 correspondente
    public void inserirShow(Shows s) throws Exception {
        int chave = s.getRelease_date() % 15;
        inserirShow(s, raiz, chave);
    }

    public void inserirShow(Shows s, No1 i, int chave) throws Exception {
        if (i == null) {
            throw new Exception("Erro: chave da árvore 1 não encontrada");
        } else if (chave < i.chave) {
            inserirShow(s, i.esq, chave);
        } else if (chave > i.chave) {
            inserirShow(s, i.dir, chave);
        } else {
            i.raiz = inserirNo2(i.raiz, s);
        }
    }

    // Inserção na árvore secundária (por título)
    public No2 inserirNo2(No2 i, Shows s) throws Exception {
        if (i == null) {
            return new No2(s.getTitle(), null, null, s);
        } else if (s.getTitle().compareTo(i.show.getTitle()) < 0) {
            comparacoes++;
            i.esq = inserirNo2(i.esq, s);
        } else if (s.getTitle().compareTo(i.show.getTitle()) > 0) {
            comparacoes++;
            i.dir = inserirNo2(i.dir, s);
        } else {
            comparacoes++;
            throw new Exception("Erro: título duplicado");
        }
        return i;
    }

    public static boolean mostrar(String title) {
        System.out.print("raiz ");
        boolean encontrado = caminharPre(raiz, title);
        System.out.println(encontrado ? "SIM" : "NAO");
        return encontrado;
    }

    public static boolean caminharPre(No1 i, String title) {
        boolean resp = false;

        if (i != null && !resp) {
            // Primeiro tenta encontrar na árvore 2
            if (pesquisarArvore2(title, i.raiz)) {
                resp = true;
            }

            // Caminha para a esquerda, só se ainda não encontrou
            if (!resp) {
                System.out.print("ESQ ");
                resp = caminharPre(i.esq, title);
            }

            // Caminha para a direita, só se ainda não encontrou
            if (!resp) {
                System.out.print("DIR ");
                resp = caminharPre(i.dir, title);
            }
        }

        return resp;
    }

    public static boolean pesquisarArvore2(String s, No2 i) {
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
            resp = pesquisarArvore2(s, i.esq);
        } else {
            comparacoes++;
            System.out.print("dir ");
            resp = pesquisarArvore2(s, i.dir);
        }

        return resp;
    }

}

public class q2 {

    // Método para buscar o registro referente a um 'id' no csv.
    public static Shows procurarID(String caminhoArquivo, String idBuscado) throws Exception {
        Scanner sc = new Scanner(new File(caminhoArquivo), "UTF-8");
        if (sc.hasNextLine()) sc.nextLine();
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
        //String file = "C://Users//Ligia//OneDrive//Documentos//TP3//disneyplus.csv";

        Arvore arvore = new Arvore();

        int[] chaves  = {7, 3, 11, 1, 5, 9, 13, 0, 2, 4, 6, 8, 10, 12, 14};
        for (int i = 0; i < chaves.length; i++) {
            Arvore.inserirNo1(chaves[i]);
        }

        Scanner sc = new Scanner(System.in);
        String entrada = sc.nextLine();

        while (!entrada.equals("FIM")) {
            Shows input = procurarID(file, entrada);
            if (input != null) {
                arvore.inserirShow(input);
            } else {
                System.err.println("ID não encontrado ou inválido: " + entrada);
            }
            entrada = sc.nextLine();
        }

        String chave = sc.nextLine();
        while (!chave.equals("FIM")) {
            Arvore.mostrar(chave);
            chave = sc.nextLine();
        }

        sc.close();

        long fim = System.nanoTime(); // Fim da contagem do tempo
        double tempo = (fim - inicio) / 1e6; // tempo em milissegundos

        // Escreve o tempo e comparações em um arquivo de log
        PrintWriter log = new PrintWriter("793406_arvoreArvore.txt");
        log.printf("793406\t%.3f\t%d\n", tempo, Arvore.comparacoes);
        log.close();
    }
}