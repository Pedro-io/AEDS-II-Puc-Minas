import java.io.*;
import java.util.*;

public class Q3 {

    public Q3() {
    }


    public static void main(String[] args) throws Exception {
        long inicioTempo = System.currentTimeMillis(); // Começa a contar o tempo
        int comparacoes = 0; // Contador de comparações

<<<<<<< HEAD
        Scanner entrada = new Scanner(System.in); // Scanner para ler entrada do teclado
        //Scanner leitorArquivo = new Scanner(new File("/tmp/disneyplus.csv")); // Scanner para ler o arquivo CSV
        Scanner leitorArquivo = new Scanner(new File("disneyplus.csv")); // Scanner para ler o arquivo CSV

        Show[] listaShows = new Show[10000]; // Vetor para armazenar os objetos Show
        Show[] entradaShows = new Show[10000]; // Vetor para armazenar os shows que possuem o id da entrada
        int totalShows = 0; // Contador de quantos shows foram lidos
        String nomeFilme = ""; // Armazena o nome do filme 
        String linhaLida;
        Show showAtual;
        
        // Lê a primeira linha (cabeçalho) do arquivo e ignora
        for(String linhaIgnorada = leitorArquivo.nextLine(); leitorArquivo.hasNextLine(); listaShows[totalShows++] = showAtual) {
            linhaLida = leitorArquivo.nextLine(); // Lê uma linha do arquivo
            showAtual = new Show(); // Cria novo objeto Show
            showAtual.ler(linhaLida); // Preenche os dados do show a partir da linha CSV
        }

        // Enquanto o id for diferente de "FIM"
        for(String idBuscado = entrada.nextLine(); !idBuscado.equals("FIM"); idBuscado = entrada.nextLine()) {
            for(int i = 0; i < totalShows; ++i) {
                if (listaShows[i].getShow_id().equals(idBuscado)) {
                    entradaShows[i] = listaShows[i];
                   // System.out.println(listaShows[i].getTitulo());
                }

            }
        }


        for( String linhaIgnorada = entrada.nextLine(); !nomeFilme.equals("FIM"); nomeFilme = entrada.nextLine()) {
            
            for(int i = 0; i < totalShows; ++i) {

                System.out.println(listaShows[i].getTitulo());

                if (listaShows[i].getTitulo().equals(nomeFilme)) {
                    listaShows[i].imprimir();
                }
                else{
                    nomeFilme = "FIM"; 
=======
        Scanner entrada = new Scanner(System.in);
        Scanner leitorArquivo = new Scanner(new File("/tmp/disneyplus.csv"));
        Show[] todosShows = new Show[10000];
        Show[] vetorInseridos = new Show[1000]; // Vetor que receberá os inseridos
        int totalShows = 0;
        int totalInseridos = 0;

        // Ler todos shows
        while (leitorArquivo.hasNextLine()) {
            String linha = leitorArquivo.nextLine();
            Show show = new Show();
            show.ler(linha);
            todosShows[totalShows++] = show;
        }

        //Inserção dos registros
        String idBuscado = entrada.nextLine();
        while (!idBuscado.equals("FIM")) {
            for (int i = 0; i < totalShows; i++) {
                comparacoes++;
                if (todosShows[i].getShow_id().equals(idBuscado)) {
                    vetorInseridos[totalInseridos++] = todosShows[i];
>>>>>>> 9159708a9443f46a7dc8335863af9fcc485aed46
                }
            }
            idBuscado = entrada.nextLine();
        }

        // Pesquisas por título
        String tituloPesquisado = "";
      //  System.out.println("NAO");
        while (!tituloPesquisado.equals("FIM")) {
            boolean encontrado = false;

            for (int i = 0; i < totalInseridos; i++) {
                comparacoes++;
                if (!encontrado && vetorInseridos[i].getTitulo().equals(tituloPesquisado)) {
                    encontrado = true;
                }
            }

            if (encontrado) {
                System.out.println("SIM");
            } else {
                System.out.println("NAO");
            }

            tituloPesquisado = entrada.nextLine();
        }

        entrada.close();
        leitorArquivo.close();

        long fimTempo = System.currentTimeMillis(); // Termina a contagem de tempo
        double tempoExecucao = (fimTempo - inicioTempo) / 1000.0; // tempo em segundos

        // Criar o arquivo de log
        FileWriter log = new FileWriter("matricula_sequencial.txt");
        log.write("793406" + "\t" + tempoExecucao + "\t" + comparacoes);
        log.close();
    }
}


class Show {
    private String show_id;
    private String tipo;
    private String titulo;
    private String diretor;
    private String elenco;
    private String pais;
    private String dataAdicionado;
    private int anoLancamento;
    private String classificacao;
    private String duracao;
    private String categorias;

    // Construtor padrão, inicializa com valores default
    public Show() {
        this.show_id = "NaN";
        this.tipo = "NaN";
        this.titulo = "NaN";
        this.diretor = "NaN";
        this.elenco = "NaN";
        this.pais = "NaN";
        this.dataAdicionado = "March 1, 1900";
        this.anoLancamento = 0;
        this.classificacao = "NaN";
        this.duracao = "NaN";
        this.categorias = "NaN";
    }

    // Construtor com parâmetros
    public Show(String id, String tipo, String titulo, String diretor, String elenco, String pais, String data, int ano, String classificacao, String duracao, String categorias) {
        this.show_id = id;
        this.tipo = tipo;
        this.titulo = titulo;
        this.diretor = diretor;
        this.elenco = elenco;
        this.pais = pais;
        this.dataAdicionado = data;
        this.anoLancamento = ano;
        this.classificacao = classificacao;
        this.duracao = duracao;
        this.categorias = categorias;
    }

    // Método para clonar um objeto Show
    public Show clone() {
        return new Show(this.show_id, this.tipo, this.titulo, this.diretor, this.elenco, this.pais, this.dataAdicionado, this.anoLancamento, this.classificacao, this.duracao, this.categorias);
    }

    // Imprime os atributos do objeto Show no formato solicitado
    public void imprimir() {
        System.out.print("=> " + this.show_id + " ## " + this.titulo + " ## " + this.tipo + " ## " + this.diretor + " ## [" + this.elenco + "] ## " + this.pais + " ## " + this.dataAdicionado + " ## " + this.anoLancamento + " ## " + this.classificacao + " ## " + this.duracao + " ## [" + this.categorias + "]##\n");
    }

    // Lê uma linha CSV e preenche os atributos do objeto
    public void ler(String linha) {
        String[] campos = new String[20];
        int indice = 0;
        boolean entreAspas = false;
        String campoAtual = "";

        // Separação de campos, considerando aspas
        for(int i = 0; i < linha.length(); ++i) {
            char caractere = linha.charAt(i);
            if (caractere == '"') {
                entreAspas = !entreAspas;
            } else if (caractere == ',' && !entreAspas) {
                campos[indice++] = campoAtual.trim();
                campoAtual = "";
            } else {
                campoAtual += caractere;
            }
        }

        campos[indice] = campoAtual.trim();

        // Atribuição dos campos aos atributos da classe
        this.show_id = getOrNaN(campos, 0);
        this.tipo = getOrNaN(campos, 1);
        this.titulo = getOrNaN(campos, 2);
        this.diretor = getOrNaN(campos, 3);
        this.elenco = ordenarEUnir(getOrNaN(campos, 4));
        this.pais = getOrNaN(campos, 5);
        this.dataAdicionado = (campos[6] != null && !campos[6].equals("")) ? campos[6] : "NaN";

        try {
            this.anoLancamento = Integer.parseInt(getOrNaN(campos, 7));
        } catch (Exception e) {
            this.anoLancamento = 0;
        }

        this.classificacao = getOrNaN(campos, 8);
        this.duracao = getOrNaN(campos, 9);
        this.categorias = ordenarEUnir(getOrNaN(campos, 10));
    }

    // Retorna o campo se estiver preenchido, senão retorna "NaN"
    private String getOrNaN(String[] campos, int indice) {
        return (indice < campos.length && campos[indice] != null && !campos[indice].equals("")) ? campos[indice] : "NaN";
    }

    // Ordena os elementos separados por vírgula em ordem alfabética e os junta em uma string
    private String ordenarEUnir(String campo) {
        if (campo.equals("NaN")) {
            return "NaN";
        } else {
            String[] itens = new String[20];
            int qtd = 0;
            String temp = "";

            for(int i = 0; i < campo.length(); ++i) {
                if (campo.charAt(i) == ',') {
                    itens[qtd++] = temp.trim();
                    temp = "";
                } else {
                    temp += campo.charAt(i);
                }
            }

            itens[qtd++] = temp.trim();

            // Ordena os itens
            for(int i = 0; i < qtd - 1; ++i) {
                for(int j = i + 1; j < qtd; ++j) {
                    if (itens[i].compareTo(itens[j]) > 0) {
                        String aux = itens[i];
                        itens[i] = itens[j];
                        itens[j] = aux;
                    }
                }
            }

            // Junta os itens em uma única string
            String resultado = "";
            for(int i = 0; i < qtd; ++i) {
                resultado += itens[i];
                if (i < qtd - 1) {
                    resultado += ", ";
                }
            }

            return resultado;
        }
    }

    // Retorna o ID do show
    public String getShow_id() {
        return this.show_id;
    }


    public String getTitulo(){
        return this.titulo; 
    }
}
