import java.io.*;
import java.util.*;

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
 
    public Show(String var1, String var2, String var3, String var4, String var5, String var6, String var7, int var8, String var9, String var10, String var11) {
       this.show_id = var1;
       this.tipo = var2;
       this.titulo = var3;
       this.diretor = var4;
       this.elenco = var5;
       this.pais = var6;
       this.dataAdicionado = var7;
       this.anoLancamento = var8;
       this.classificacao = var9;
       this.duracao = var10;
       this.categorias = var11;
    }
 
    public Show clone() {
       return new Show(this.show_id, this.tipo, this.titulo, this.diretor, this.elenco, this.pais, this.dataAdicionado, this.anoLancamento, this.classificacao, this.duracao, this.categorias);
    }
 
    public void imprimir() {
       System.out.print("=> " + this.show_id + " ## " + this.titulo + " ## " + this.tipo + " ## " + this.diretor + " ## [" + this.elenco + "] ## " + this.pais + " ## " + this.dataAdicionado + " ## " + this.anoLancamento + " ## " + this.classificacao + " ## " + this.duracao + " ## [" + this.categorias + "] ##\n");
    }
 
    public void ler(String var1) {
       String[] var2 = new String[20];
       int var3 = 0;
       boolean var4 = false;
       String var5 = "";
 
       for(int var6 = 0; var6 < var1.length(); ++var6) {
          char var7 = var1.charAt(var6);
          if (var7 == '"') {
             var4 = !var4;
          } else if (var7 == ',' && !var4) {
             var2[var3++] = var5.trim();
             var5 = "";
          } else {
             var5 = var5 + var7;
          }
       }
 
       var2[var3] = var5.trim();
       this.show_id = this.getOrNaN(var2, 0);
       this.tipo = this.getOrNaN(var2, 1);
       this.titulo = this.getOrNaN(var2, 2);
       this.diretor = this.getOrNaN(var2, 3);
       this.elenco = this.ordenarEUnir(this.getOrNaN(var2, 4));
       this.pais = this.getOrNaN(var2, 5);
       this.dataAdicionado = var2[6] != null && !var2[6].equals("") ? var2[6] : "NaN";
 
       try {
          this.anoLancamento = Integer.parseInt(this.getOrNaN(var2, 7));
       } catch (Exception var8) {
          this.anoLancamento = 0;
       }
 
       this.classificacao = this.getOrNaN(var2, 8);
       this.duracao = this.getOrNaN(var2, 9);
       this.categorias = this.ordenarEUnir(this.getOrNaN(var2, 10));
    }
 
    private String getOrNaN(String[] var1, int var2) {
       return var2 < var1.length && var1[var2] != null && !var1[var2].equals("") ? var1[var2] : "NaN";
    }
 
    private String ordenarEUnir(String var1) {
       if (var1.equals("NaN")) {
          return "NaN";
       } else {
          String[] var2 = new String[20];
          int var3 = 0;
          String var4 = "";
 
          int var5;
          for(var5 = 0; var5 < var1.length(); ++var5) {
             if (var1.charAt(var5) == ',') {
                var2[var3++] = var4.trim();
                var4 = "";
             } else {
                var4 = var4 + var1.charAt(var5);
             }
          }
 
          var2[var3++] = var4.trim();
 
          int var6;
          for(var5 = 0; var5 < var3 - 1; ++var5) {
             for(var6 = var5 + 1; var6 < var3; ++var6) {
                if (var2[var5].compareTo(var2[var6]) > 0) {
                   String var7 = var2[var5];
                   var2[var5] = var2[var6];
                   var2[var6] = var7;
                }
             }
          }
 
          String var8 = "";
 
          for(var6 = 0; var6 < var3; ++var6) {
             var8 = var8 + var2[var6];
             if (var6 < var3 - 1) {
                var8 = var8 + ", ";
             }
          }
 
          return var8;
       }
    }
 
    public String getShow_id() {
       return this.show_id;
    }
 
    public String getTitulo() {
       return this.titulo;
    }
 }
 



 public class Q5{

    public static void main(String[] args) throws Exception {
        long inicioTempo = System.currentTimeMillis(); // Começa a contar o tempo
        int comparacoes = 0; // Contador de comparações

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
                }
            }
            idBuscado = entrada.nextLine();
        }

        // Ordena os shows encontrados
        Show tmp;
        for(int i = 0; i < totalInseridos -1; i++){
            int menor = i; 
            for(int j = (i +1); j< totalInseridos; j++ ){

                if(vetorInseridos[menor].getTitulo().compareTo(vetorInseridos[j].getTitulo()) > 0){
                    menor = j;
                }
            }
            tmp = vetorInseridos[i];
            vetorInseridos[i] = vetorInseridos[menor];
            vetorInseridos[menor] = tmp;

        }

        // Printando os resultados
        for(int i = 0; i < totalInseridos; i ++){
            vetorInseridos[i].imprimir();
        }

        entrada.close();
        leitorArquivo.close();

        long fimTempo = System.currentTimeMillis(); // Termina a contagem de tempo
        double tempoExecucao = (fimTempo - inicioTempo) / 1000.0; // tempo em segundos

        // Criar o arquivo de log
        FileWriter log = new FileWriter("MATRICULA_sequencial.txt");
        log.write("793406" + "\t" + tempoExecucao + "\t" + comparacoes);
        log.close();
    }
 }