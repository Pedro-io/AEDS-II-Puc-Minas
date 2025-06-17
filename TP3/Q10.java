import java.io.BufferedReader;
import java.io.FileReader;
import java.io.PrintWriter;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Locale;
import java.util.Scanner;

/*
 * CLASSE SHOW PARA O TP, O CÓDIGO DA QUESTÃO VAI COMEÇAR DEPOIS DESTA CLASSE
 */
class Show {
    private String show_id, tipo, titulo, diretor, pais, classificacao, duracao, categorias, descricao;
    private String[] elenco;
    private String dataAdicionado;
    private int anoLancamento;

    public Show() {
        show_id = tipo = titulo = diretor = pais = classificacao = duracao = categorias = descricao = "NaN";
        dataAdicionado = "NaN";
        elenco = new String[0];
        anoLancamento = 0;
    }

    public void ler(String linha) {
        String[] campos = new String[12];
        boolean aspas = false;
        String temp = "";
        int campo = 0;
        for (int i = 0; i < linha.length(); i++) {
            char c = linha.charAt(i);
            if (c == '\"') aspas = !aspas;
            else if (c == ',' && !aspas) {
                campos[campo++] = temp;
                temp = "";
            } else temp += c;
        }
        campos[campo] = temp;

        show_id = tratarCampo(campos, 0);
        tipo = tratarCampo(campos, 1);
        titulo = tratarCampo(campos, 2);
        diretor = tratarCampo(campos, 3);
        pais = tratarCampo(campos, 5);
        classificacao = tratarCampo(campos, 8);
        duracao = tratarCampo(campos, 9);
        categorias = tratarCampo(campos, 10);
        descricao = tratarCampo(campos, 11);

        elenco = tratarCampo(campos, 4).equals("NaN") ? new String[0] : tratarCampo(campos, 4).split(", ");
        ordenar(elenco);

        dataAdicionado = tratarCampo(campos, 6);
        try {
            anoLancamento = Integer.parseInt(tratarCampo(campos, 7));
        } catch (Exception e) {
            anoLancamento = 0;
        }
    }

    private String tratarCampo(String[] campos, int i) {
        if (i >= campos.length || campos[i] == null || campos[i].trim().isEmpty()) return "NaN";
        return campos[i].replace("\"", "").trim();
    }

    private void ordenar(String[] arr) {
        for (int i = 0; i < arr.length - 1; i++) {
            for (int j = 0; j < arr.length - 1 - i; j++) {
                if (arr[j].compareTo(arr[j + 1]) > 0) {
                    String tmp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = tmp;
                }
            }
        }
    }

    public String getShow_id() { return show_id; }
    public String getTitulo() { return titulo; }
    public String getDataAdicionado() { return dataAdicionado; }

    public String formatar() {
        String elencoStr = (elenco.length == 0) ? "NaN" : String.join(", ", elenco);
        String data = dataAdicionado.equals("NaN") ? "NaN" : dataAdicionado;
        return "=> " + show_id + " ## " + titulo + " ## " + tipo + " ## " + diretor + " ## [" + elencoStr + "] ## " +
                pais + " ## " + data + " ## " + anoLancamento + " ## " + classificacao + " ## " + duracao + " ## [" + categorias + "] ##";
    }
}

/***************************************************************************************
 * O CÓDIGO DA QUESTÃO COMEÇA AQUI
 ***************************************************************************************/
public class Q10 {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        BufferedReader br = new BufferedReader(new FileReader("/tmp/disneyplus.csv"));

        Show[] base = new Show[10000];
        int total = 0;
        br.readLine(); // pular cabeçalho
        String linha;
        while ((linha = br.readLine()) != null) {
            Show s = new Show();
            s.ler(linha);
            base[total++] = s;
        }
        br.close();

        Show[] selecionados = new Show[1000];
        int n = 0;
        linha = sc.nextLine();
        while (!linha.equals("FIM")) {
            for (int i = 0; i < total; i++) {
                if (base[i].getShow_id().equals(linha)) {
                    selecionados[n++] = base[i];
                    break;
                }
            }
            linha = sc.nextLine();
        }

        long inicio = System.nanoTime();
        ordenarPorData(selecionados, n);
        long fim = System.nanoTime();

        for (int i = 0; i < n; i++) {
            System.out.println(selecionados[i].formatar());
        }

        double tempo = (fim - inicio) / 1e9;
        PrintWriter log = new PrintWriter("matricula_quicksort3.txt");
        log.printf("802311\t%.6f\t0\n", tempo); // Comparações não contadas
        log.close();
        sc.close();
    }

    public static void ordenarPorData(Show[] array, int tamanho) {
        for (int i = 0; i < tamanho - 1; i++) {
            for (int j = 0; j < tamanho - 1 - i; j++) {
                if (compararDatas(array[j], array[j + 1]) > 0) {
                    Show tmp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = tmp;
                }
            }
        }
    }

    public static int compararDatas(Show s1, Show s2) {
        try {
            if (s1.getDataAdicionado().equals("NaN") && s2.getDataAdicionado().equals("NaN")) return 0;
            if (s1.getDataAdicionado().equals("NaN")) return 1;
            if (s2.getDataAdicionado().equals("NaN")) return -1;

            SimpleDateFormat sdf = new SimpleDateFormat("MMMM d, yyyy", Locale.ENGLISH);
            java.util.Date d1 = sdf.parse(s1.getDataAdicionado());
            java.util.Date d2 = sdf.parse(s2.getDataAdicionado());

            int cmp = d1.compareTo(d2);
            if (cmp != 0) return cmp;
            return s1.getTitulo().compareTo(s2.getTitulo());
        } catch (ParseException e) {
            return 0;
        }
    }
}
