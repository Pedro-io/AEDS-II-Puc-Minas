import java.io.*;
import java.text.*;
import java.util.*;

/*
 * CLASSE SHOW PARA O TP, O CÓDIGO DA QUESTÃO VAI COMEÇAR DEPOIS DESTA CLASSE
 * VAMOS MANTER ESTE PADRÃO PARA AS PRÓXIMAS QUESTÕES
 * OS MÉTODOS DE ORDENAÇÃO OU QUALQUER QUE SEJA A ALTERAÇÃO IRÃO FICAR ABAIXO DA CLASSE SHOW
 */
class Show {
    private String show_id, tipo, titulo, diretor, pais, classificacao, duracao, categorias;
    private String[] elenco;
    private String dataAdicionado;
    private int anoLancamento;

    public Show() {
        this.show_id = "NaN";
        this.tipo = "NaN";
        this.titulo = "NaN";
        this.diretor = "NaN";
        this.pais = "NaN";
        this.classificacao = "NaN";
        this.duracao = "NaN";
        this.categorias = "NaN";
        this.elenco = new String[0];
        this.dataAdicionado = "NaN";
        this.anoLancamento = 0;
    }

    public Show clone() {
        Show copia = new Show();
        copia.show_id = this.show_id;
        copia.tipo = this.tipo;
        copia.titulo = this.titulo;
        copia.diretor = this.diretor;
        copia.pais = this.pais;
        copia.classificacao = this.classificacao;
        copia.duracao = this.duracao;
        copia.categorias = this.categorias;
        copia.elenco = Arrays.copyOf(this.elenco, this.elenco.length);
        copia.dataAdicionado = this.dataAdicionado;
        copia.anoLancamento = this.anoLancamento;
        return copia;
    }

    public void ler(String linha) {
        List<String> campos = new ArrayList<>();
        boolean aspas = false;
        StringBuilder atual = new StringBuilder();
        for (int i = 0; i < linha.length(); i++) {
            char c = linha.charAt(i);
            if (c == '"') {
                aspas = !aspas;
            } else if (c == ',' && !aspas) {
                campos.add(atual.toString().trim());
                atual = new StringBuilder();
            } else {
                atual.append(c);
            }
        }
        campos.add(atual.toString().trim());
        while (campos.size() < 12) campos.add("");

        this.show_id = trataCampo(campos.get(0));
        this.tipo = trataCampo(campos.get(1));
        this.titulo = trataCampo(campos.get(2));
        this.diretor = trataCampo(campos.get(3));
        this.elenco = processarLista(trataCampo(campos.get(4)));
        this.pais = trataCampo(campos.get(5));
        this.dataAdicionado = campos.get(6).isEmpty() ? "NaN" : campos.get(6);
        try {
            this.anoLancamento = Integer.parseInt(trataCampo(campos.get(7)));
        } catch (Exception e) {
            this.anoLancamento = 0;
        }
        this.classificacao = trataCampo(campos.get(8));
        this.duracao = trataCampo(campos.get(9));
        this.categorias = trataCampo(campos.get(10));
    }

    private String trataCampo(String campo) {
        if (campo == null || campo.isEmpty()) return "NaN";
        campo = campo.trim();
        if (campo.startsWith("\"") && campo.endsWith("\"")) {
            campo = campo.substring(1, campo.length() - 1);
        }
        return campo;
    }

    private String[] processarLista(String campo) {
        if (campo.equals("NaN")) return new String[0];
        String[] partes = campo.split(",");
        for (int i = 0; i < partes.length; i++) partes[i] = partes[i].trim();
        Arrays.sort(partes);
        return partes;
    }

    public void imprimir() {
        System.out.print("=> " + this.show_id + " ## " + this.titulo + " ## " + this.tipo + " ## " + this.diretor + " ## [");
        if (elenco.length > 0) {
            for (int i = 0; i < elenco.length; i++) {
                System.out.print(elenco[i]);
                if (i < elenco.length - 1) System.out.print(", ");
            }
        } else {
            System.out.print("NaN");
        }
        System.out.print("] ## " + this.pais + " ## " + this.dataAdicionado + " ## " + this.anoLancamento + " ## " + this.classificacao + " ## " + this.duracao + " ## [" + this.categorias + "] ##\n");
    }

    public String getShow_id() { return show_id; }
    public String getTitulo() { return titulo; }
}

/***************************************************************************************
 **************************************************************************************
 **************************************************************************************
 **************************************************************************************
 * O CÓDIGO PARA A QUESTÃO COMEÇA AQUI ***********************************************
 */

class Pilha {
    private Show[] array;
    private int topo;

    public Pilha(int capacidade) {
        array = new Show[capacidade];
        topo = 0;
    }

    public void empilhar(Show x) {
        if (topo >= array.length) {
            array = Arrays.copyOf(array, array.length * 2);
        }
        array[topo++] = x;
    }

    public Show desempilhar() {
        return topo > 0 ? array[--topo] : null;
    }

    public void mostrar() {
        for (int i = topo - 1; i >= 0; i--) {
            array[i].imprimir();
        }
    }
}

public class Q9 {
    public static Show buscar(Show[] base, int total, String id) {
        for (int i = 0; i < total; i++) {
            if (base[i].getShow_id().equals(id)) return base[i];
        }
        return null;
    }

    public static void main(String[] args) throws Exception {
        Scanner entrada = new Scanner(System.in);
        BufferedReader leitor = new BufferedReader(new FileReader("/tmp/disneyplus.csv"));
        Show[] base = new Show[10000];
        int total = 0;

        leitor.readLine(); // ignora cabeçalho
        String linhaArquivo;
        while ((linhaArquivo = leitor.readLine()) != null) {
            Show s = new Show();
            s.ler(linhaArquivo);
            base[total++] = s;
        }

        Pilha pilha = new Pilha(100);
        String id = entrada.nextLine();
        while (!id.equals("FIM")) {
            Show s = buscar(base, total, id);
            if (s != null) pilha.empilhar(s.clone());
            id = entrada.nextLine();
        }

        int n = Integer.parseInt(entrada.nextLine());
        for (int i = 0; i < n; i++) {
            String comando = entrada.nextLine();
            if (comando.startsWith("I ")) {
                String novoId = comando.split(" ")[1];
                Show s = buscar(base, total, novoId);
                if (s != null) pilha.empilhar(s.clone());
            } else if (comando.equals("R")) {
                Show removido = pilha.desempilhar();
                if (removido != null) System.out.println("(R) " + removido.getTitulo());
            }
        }

        pilha.mostrar();
        entrada.close();
        leitor.close();
    }
}
