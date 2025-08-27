class Main {

    public static void main(String[] args) {
        EstruturaDoidona estrutura = new EstruturaDoidona();

        estrutura.inserir(15);
        estrutura.inserir(25);
        estrutura.inserir(35);
        estrutura.inserir(45); // colisões forçadas para ver funcionamento

        System.out.println("\n--- Mostrar ---");
        estrutura.mostrar();

        System.out.println("\n--- Pesquisar ---");
        System.out.println("35 está presente? " + estrutura.pesquisar(35));
        System.out.println("99 está presente? " + estrutura.pesquisar(99));

        System.out.println("\n--- Remover ---");
        estrutura.remover(25);
        estrutura.remover(99); // não existe
        estrutura.mostrar();
    }
}

// Classe principal da estrutura
class EstruturaDoidona {
    private final int TAM_T1 = 5;
    private final int TAM_T3 = 3;

    EntradaT1[] T1 = new EntradaT1[TAM_T1];

    EstruturaDoidona() {
        for (int i = 0; i < TAM_T1; i++) {
            T1[i] = new EntradaT1();
        }
    }

    int hashT1(int chave) {
        return chave % TAM_T1;
    }

    int hashT2(int chave) {
        return chave % 3; // retorna 0, 1 ou 2
    }

    int hashT3(int chave) {
        return chave % TAM_T3;
    }

    public void inserir(int chave) {
        int posT1 = hashT1(chave);

        if (T1[posT1].chave == null) {
            T1[posT1].chave = chave;
        } else {
            int posT2 = hashT2(chave);

            if (posT2 == 0) {
                // Verifica se T3 não foi criada para esta posição 
                if (T1[posT1].T3 == null) {
                    T1[posT1].T3 = new EntradaT3[TAM_T3];
                    for (int i = 0; i < TAM_T3; i++) {
                        T1[posT1].T3[i] = new EntradaT3();
                    }
                }
                
                int posT3 = hashT3(chave);
                if (T1[posT1].T3[posT3].chave == null) {
                    T1[posT1].T3[posT3].chave = chave;
                } else {
                    T1[posT1].T3[posT3].raiz = inserirNaArvore(T1[posT1].T3[posT3].raiz, chave);
                }

            } else if (posT2 == 1) {
                T1[posT1].lista = inserirNaLista(T1[posT1].lista, chave);

            } else if (posT2 == 2) {
                T1[posT1].raiz = inserirNaArvore(T1[posT1].raiz, chave);
            }
        }
    }

    public boolean pesquisar(int chave) {
        int posT1 = hashT1(chave);
        if (T1[posT1].chave != null && T1[posT1].chave == chave) {
            return true;
        }

        int posT2 = hashT2(chave);

        if (posT2 == 0 && T1[posT1].T3 != null) {
            int posT3 = hashT3(chave);
            if (T1[posT1].T3[posT3].chave != null && T1[posT1].T3[posT3].chave == chave) {
                return true;
            }
            return buscarNaArvore(T1[posT1].T3[posT3].raiz, chave);
        } else if (posT2 == 1) {
            return buscarNaLista(T1[posT1].lista, chave);
        } else if (posT2 == 2) {
            return buscarNaArvore(T1[posT1].raiz, chave);
        }

        return false;
    }

    public void mostrar() {
        for (int i = 0; i < TAM_T1; i++) {
            System.out.print("T1[" + i + "]: ");
            if (T1[i].chave != null)
                System.out.print(T1[i].chave + " ");
            if (T1[i].lista != null) {
                System.out.print("Lista: ");
                mostrarLista(T1[i].lista);
            }
            if (T1[i].raiz != null) {
                System.out.print("Árvore: ");
                mostrarArvore(T1[i].raiz);
            }
            if (T1[i].T3 != null) {
                System.out.print(" T3: ");
                for (int j = 0; j < TAM_T3; j++) {
                    if (T1[i].T3[j].chave != null)
                        System.out.print("[" + j + "]:" + T1[i].T3[j].chave + " ");
                    if (T1[i].T3[j].raiz != null) {
                        System.out.print("{Árvore em T3[" + j + "]: ");
                        mostrarArvore(T1[i].T3[j].raiz);
                        System.out.print("} ");
                    }
                }
            }
            System.out.println();
        }
    }

    public void remover(int chave) {
        if (!pesquisar(chave)) {
            System.out.println("Chave " + chave + " não encontrada para remoção.");
            return;
        }

        int posT1 = hashT1(chave);
        if (T1[posT1].chave != null && T1[posT1].chave == chave) {
            T1[posT1].chave = null;
            return;
        }

        int posT2 = hashT2(chave);
        if (posT2 == 0 && T1[posT1].T3 != null) {
            int posT3 = hashT3(chave);
            if (T1[posT1].T3[posT3].chave != null && T1[posT1].T3[posT3].chave == chave) {
                T1[posT1].T3[posT3].chave = null;
            } else {
                T1[posT1].T3[posT3].raiz = removerDaArvore(T1[posT1].T3[posT3].raiz, chave);
            }
        } else if (posT2 == 1) {
            T1[posT1].lista = removerDaLista(T1[posT1].lista, chave);
        } else if (posT2 == 2) {
            T1[posT1].raiz = removerDaArvore(T1[posT1].raiz, chave);
        }
    }

    // Métodos auxiliares de árvore
    No inserirNaArvore(No raiz, int chave) {
        if (raiz == null) return new No(chave);
        if (chave < raiz.valor) raiz.esq = inserirNaArvore(raiz.esq, chave);
        else if (chave > raiz.valor) raiz.dir = inserirNaArvore(raiz.dir, chave);
        return raiz;
    }

    boolean buscarNaArvore(No raiz, int chave) {
        if (raiz == null) return false;
        if (raiz.valor == chave) return true;
        if (chave < raiz.valor) return buscarNaArvore(raiz.esq, chave);
        else return buscarNaArvore(raiz.dir, chave);
    }

    void mostrarArvore(No raiz) {
        if (raiz != null) {
            mostrarArvore(raiz.esq);
            System.out.print(raiz.valor + " ");
            mostrarArvore(raiz.dir);
        }
    }

    No removerDaArvore(No raiz, int chave) {
        if (raiz == null) return null;
        if (chave < raiz.valor) raiz.esq = removerDaArvore(raiz.esq, chave);
        else if (chave > raiz.valor) raiz.dir = removerDaArvore(raiz.dir, chave);
        else {
            if (raiz.esq == null) return raiz.dir;
            if (raiz.dir == null) return raiz.esq;
            No temp = menorValor(raiz.dir);
            raiz.valor = temp.valor;
            raiz.dir = removerDaArvore(raiz.dir, temp.valor);
        }
        return raiz;
    }

    No menorValor(No no) {
        while (no.esq != null) no = no.esq;
        return no;
    }

    // Métodos auxiliares de lista
    Celula inserirNaLista(Celula lista, int chave) {
        Celula nova = new Celula(chave);
        nova.prox = lista;
        return nova;
    }

    boolean buscarNaLista(Celula lista, int chave) {
        while (lista != null) {
            if (lista.valor == chave) return true;
            lista = lista.prox;
        }
        return false;
    }

    void mostrarLista(Celula lista) {
        while (lista != null) {
            System.out.print(lista.valor + " ");
            lista = lista.prox;
        }
    }

    Celula removerDaLista(Celula lista, int chave) {
        if (lista == null) return null;
        if (lista.valor == chave) return lista.prox;
        lista.prox = removerDaLista(lista.prox, chave);
        return lista;
    }
}

// Célula de lista
class Celula {
    int valor;
    Celula prox;

    Celula(int v) {
        valor = v;
        prox = null;
    }
}

// Nó da árvore
class No {
    int valor;
    No esq, dir;

    No(int v) {
        valor = v;
        esq = dir = null;
    }
}

// Entrada da T3 (hash + árvore)
class EntradaT3 {
    Integer chave;
    No raiz;
}

// Entrada da T1 (pode ter lista, árvore, ou T3)
class EntradaT1 {
    Integer chave;
    Celula lista;
    No raiz;
    EntradaT3[] T3;
}
