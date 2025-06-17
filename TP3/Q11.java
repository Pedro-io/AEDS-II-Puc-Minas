import java.util.Scanner;

/*
 * CLASSE CELULA PARA MATRIZ DINÂMICA
 */
class Celula {
    int elemento;
    Celula sup, inf, esq, dir;

    public Celula() {
        this(0);
    }

    public Celula(int x) {
        elemento = x;
        sup = inf = esq = dir = null;
    }
}

/*
 * CLASSE MATRIZ DINÂMICA DO TP
 */
class Matriz {
    private Celula inicio;
    private int linhas, colunas;

    public Matriz(int l, int c) {
        this.linhas = l;
        this.colunas = c;
        if (l <= 0 || c <= 0) return;

        // Alocar primeira linha
        inicio = new Celula();
        Celula atual = inicio;

        // Criar a primeira linha
        for (int j = 1; j < c; j++) {
            atual.dir = new Celula();
            atual.dir.esq = atual;
            atual = atual.dir;
        }

        // Criar as demais linhas
        Celula linhaAcima = inicio;
        for (int i = 1; i < l; i++) {
            Celula novaLinha = new Celula();
            linhaAcima.inf = novaLinha;
            novaLinha.sup = linhaAcima;

            atual = novaLinha;
            Celula acima = linhaAcima.dir;

            for (int j = 1; j < c; j++) {
                atual.dir = new Celula();
                atual.dir.esq = atual;

                if (acima != null) {
                    acima.inf = atual.dir;
                    atual.dir.sup = acima;
                    acima = acima.dir;
                }

                atual = atual.dir;
            }

            linhaAcima = linhaAcima.inf;
        }
    }

    public void preencher(Scanner sc) {
        Celula linha = inicio;
        for (int i = 0; i < linhas; i++, linha = linha.inf) {
            Celula coluna = linha;
            for (int j = 0; j < colunas; j++, coluna = coluna.dir) {
                coluna.elemento = sc.nextInt();
            }
        }
    }

    public void mostrarDiagonalPrincipal() {
        Celula atual = inicio;
        for (int i = 0; i < Math.min(linhas, colunas); i++) {
            System.out.print(atual.elemento + " ");
            atual = atual.inf != null ? atual.inf.dir : null;
        }
        System.out.println();
    }

    public void mostrarDiagonalSecundaria() {
        Celula atual = inicio;
        for (int i = 1; i < colunas; i++) atual = atual.dir;

        for (int i = 0; i < Math.min(linhas, colunas); i++) {
            System.out.print(atual.elemento + " ");
            atual = atual.inf != null ? atual.inf.esq : null;
        }
        System.out.println();
    }

    public Matriz soma(Matriz outra) {
        if (this.linhas != outra.linhas || this.colunas != outra.colunas) return null;

        Matriz resp = new Matriz(this.linhas, this.colunas);
        Celula l1 = this.inicio, l2 = outra.inicio, lr = resp.inicio;
        for (int i = 0; i < linhas; i++, l1 = l1.inf, l2 = l2.inf, lr = lr.inf) {
            Celula c1 = l1, c2 = l2, cr = lr;
            for (int j = 0; j < colunas; j++, c1 = c1.dir, c2 = c2.dir, cr = cr.dir) {
                cr.elemento = c1.elemento + c2.elemento;
            }
        }
        return resp;
    }

    public Matriz multiplicacao(Matriz outra) {
        if (this.colunas != outra.linhas) return null;

        Matriz resp = new Matriz(this.linhas, outra.colunas);
        Celula lA = this.inicio;
        Celula lR = resp.inicio;

        for (int i = 0; i < this.linhas; i++, lA = lA.inf, lR = lR.inf) {
            Celula cR = lR;
            for (int j = 0; j < outra.colunas; j++, cR = cR.dir) {
                int soma = 0;
                Celula cA = lA;
                Celula lB = outra.inicio;
                for (int k = 0; k < this.colunas; k++, cA = cA.dir, lB = lB.inf) {
                    Celula cB = lB;
                    for (int t = 0; t < j; t++) cB = cB.dir;
                    soma += cA.elemento * cB.elemento;
                }
                cR.elemento = soma;
            }
        }
        return resp;
    }

    public void mostrar() {
        Celula linha = inicio;
        for (int i = 0; i < linhas; i++, linha = linha.inf) {
            Celula coluna = linha;
            for (int j = 0; j < colunas; j++, coluna = coluna.dir) {
                System.out.print(coluna.elemento + " ");
            }
            System.out.println();
        }
    }
}

/*
 * PROGRAMA PRINCIPAL DO TP
 */
public class Q11 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int casos = sc.nextInt();

        for (int t = 0; t < casos; t++) {
            int l1 = sc.nextInt();
            int c1 = sc.nextInt();
            Matriz m1 = new Matriz(l1, c1);
            m1.preencher(sc);

            int l2 = sc.nextInt();
            int c2 = sc.nextInt();
            Matriz m2 = new Matriz(l2, c2);
            m2.preencher(sc);

            m1.mostrarDiagonalPrincipal();
            m1.mostrarDiagonalSecundaria();

            Matriz soma = m1.soma(m2);
            if (soma != null) soma.mostrar();

            Matriz mult = m1.multiplicacao(m2);
            if (mult != null) mult.mostrar();
        }
        sc.close();
    }
}
