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
          String var7;
          for(var5 = 0; var5 < var3 - 1; ++var5) {
             for(var6 = var5 + 1; var6 < var3; ++var6) {
                if (var2[var5].compareTo(var2[var6]) > 0) {
                   var7 = var2[var5];
                   var2[var5] = var2[var6];
                   var2[var6] = var7;
                }
             }
          }
 
          var7 = "";
 
          for(var6 = 0; var6 < var3; ++var6) {
             var7 = var7 + var2[var6];
             if (var6 < var3 - 1) {
                var7 = var7 + ", ";
             }
          }
 
          return var7;
       }
    }
 
    public String getShow_id() {
       return this.show_id;
    }
 
    public String getTitulo() {
       return this.titulo;
    }
 
    public String getTipo() {
       return this.tipo;
    }
 
    public String getDirector() {
       return this.diretor;
    }

    public String getDataAdicionado(){
        return  this.dataAdicionado;
    }
 }
 
 class q18 {

    public static int comparacoes = 0;
    public static int movimentacoes = 0;

    public static void main(String[] args) throws Exception {
        long inicio = System.currentTimeMillis();
        Scanner sc = new Scanner(System.in);
        Scanner leitor = new Scanner(new File("/tmp/disneyplus.csv"));

        Show[] base = new Show[10000];
        Show[] inseridos = new Show[1000];
        int totalBase = 0;
        int totalInseridos = 0;

        // Ler base de dados
        while (leitor.hasNextLine()) {
            String linha = leitor.nextLine();
            Show s = new Show();
            s.ler(linha);
            base[totalBase++] = s;
        }

        // Ler IDs
        String entrada = sc.nextLine();
        while (!entrada.equals("FIM")) {
            for (int i = 0; i < totalBase; i++) {
                comparacoes++;
                if (base[i].getShow_id().equals(entrada)) {
                    inseridos[totalInseridos++] = base[i];
                    break;
                }
            }
            entrada = sc.nextLine();
        }

        // Ordenar por date_added e desempate por title
        quickSort(inseridos, 0, totalInseridos - 1);

        // Imprimir os 10 primeiros
        for (int i = 0; i < 10 && i < totalInseridos; i++) {
            inseridos[i].imprimir();
        }

        // Log
        long fim = System.currentTimeMillis();
        double tempo = (fim - inicio) / 1000.0;
        FileWriter fw = new FileWriter("matricula_quicksort.txt");
        fw.write("793406\t" + comparacoes + "\t" + movimentacoes + "\t" + String.format(Locale.US, "%.6f", tempo));
        fw.close();

        sc.close();
        leitor.close();
    }

    public static int compare(Show a, Show b) {
        comparacoes++;
        int cmpData = compararData(a.getDataAdicionado(), b.getDataAdicionado());
        if (cmpData == 0) {
            comparacoes++;
            return a.getTitulo().compareTo(b.getTitulo());
        }
        return cmpData;
    }

    public static int compararData(String data1, String data2) {
        int[] d1 = extrairData(data1);
        int[] d2 = extrairData(data2);

        if (d1[2] != d2[2]) return d1[2] - d2[2]; // ano
        if (d1[1] != d2[1]) return d1[1] - d2[1]; // mês
        return d1[0] - d2[0];                     // dia
    }

    public static int[] extrairData(String data) {
        int[] valores = {1, 1, 1900};
        if (data == null || data.equals("NaN")) return valores;

        String[] partes = data.split(" ");
        if (partes.length < 3) return valores;

        try {
            valores[0] = Integer.parseInt(partes[1].replace(",", ""));
            valores[1] = mesParaNumero(partes[0]);
            valores[2] = Integer.parseInt(partes[2]);
        } catch (Exception e) {
            // Ignora valores inválidos
        }

        return valores;
    }

    public static int mesParaNumero(String mes) {
        switch (mes.toLowerCase()) {
            case "january": return 1;
            case "february": return 2;
            case "march": return 3;
            case "april": return 4;
            case "may": return 5;
            case "june": return 6;
            case "july": return 7;
            case "august": return 8;
            case "september": return 9;
            case "october": return 10;
            case "november": return 11;
            case "december": return 12;
            default: return 1;
        }
    }

    public static void quickSort(Show[] array, int esq, int dir) {
        int i = esq, j = dir;
        Show pivo = array[(esq + dir) / 2];

        while (i <= j) {
            while (compare(array[i], pivo) < 0) i++;
            while (compare(array[j], pivo) > 0) j--;

            if (i <= j) {
                Show temp = array[i];
                array[i] = array[j];
                array[j] = temp;
                movimentacoes += 3;
                i++;
                j--;
            }
        }

        if (esq < j) quickSort(array, esq, j);
        if (i < dir) quickSort(array, i, dir);
    }
}