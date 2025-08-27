class Carro {
    String placa, modelo, tipo, chassi;

    public void ler(String linha) {
        String[] partes = linha.split(",");
        placa = partes[0];
        modelo = partes[1];
        tipo = partes[2];
        chassi = partes[3];
    }

    public void imprimir() {
        System.out.println(placa + " " + modelo + " " + tipo + " " + chassi);
    }
}

class No {
    Carro elemento;
    No esq, dir;

    public No(Carro c) {
        this.elemento = c;
        this.esq = this.dir = null;
    }
}

class Arvore {
    private No raiz;

    public void inserir(Carro carro) throws Exception {
        raiz = inserir(carro, raiz);
    }

    private No inserir(Carro carro, No i) throws Exception {
        if (i == null) {
            return new No(carro);
        } else if (carro.placa.compareTo(i.elemento.placa) < 0) {
            i.esq = inserir(carro, i.esq);
        } else if (carro.placa.compareTo(i.elemento.placa) > 0) {
            i.dir = inserir(carro, i.dir);
        } else {
            throw new Exception("Erro: placa duplicada");
        }
        return i;
    }

    public boolean buscar(String placa) {
        return buscar(placa, raiz, 0);
    }

    private boolean buscar(String placa, No i, int nivel) {
        if (i == null) {
            System.out.println("PLACA NAO ENCONTRADA");
            return false;
        } else if (placa.equals(i.elemento.placa)) {
            System.out.print(i.elemento.placa + " " + i.elemento.modelo + " " + i.elemento.tipo + " " + i.elemento.chassi);
            System.out.println(" (Nivel " + nivel + ")");
            return true;
        } else if (placa.compareTo(i.elemento.placa) < 0) {
            return buscar(placa, i.esq, nivel + 1);
        } else {
            return buscar(placa, i.dir, nivel + 1);
        }
    }
}

public class PesquisaPlaca {
    public static void main(String[] args) throws Exception {
        Arvore arvore = new Arvore();
        java.util.Scanner sc = new java.util.Scanner(System.in);

        // Inserção dos veículos
        while (true) {
            String linha = sc.nextLine();
            if (linha.equals("FIM")) break;
            Carro carro = new Carro();
            carro.ler(linha);
            arvore.inserir(carro);
        }

        // Buscas
        while (true) {
            String placaBusca = sc.nextLine();
            if (placaBusca.equals("FIM_BUSCA")) break;
            arvore.buscar(placaBusca);
        }

        sc.close();
    }
}
