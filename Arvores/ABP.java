public class ABP {
    private No raiz;

    public ABP() {
        raiz = null;
    }

    public void caminhar() {
        caminhar(raiz);
        System.out.println();
    }

    public void caminharPre() {
        caminharPre(raiz);
        System.out.println();
    }

    public void caminharPos() {
        caminharPos(raiz);
        System.out.println();
    }


    private void caminhar(No i) {
        if (i != null) {
            caminhar(i.esq);
            System.out.print(i.elemento + " ");
            caminhar(i.dir);
        }
    }

    private void caminharPre(No i) {
        if (i != null) {
            System.out.print(i.elemento + " ");
            caminharPre(i.esq);
            caminharPre(i.dir);
        }
    }

    private void caminharPos(No i) {
        if (i != null) {
        caminharPos(i.esq);
        caminharPos(i.dir);
        System.out.print(i.elemento + " ");
        }
        }
    public void inserir(int x) throws Exception {
        raiz = inserir(x, raiz);
    }

    private No inserir(int x, No i) throws Exception {
        if (i == null) {
            i = new No(x);
        } else if (x < i.elemento) {
            i.esq = inserir(x, i.esq);
        } else if (x > i.elemento) {
            i.dir = inserir(x, i.dir);
        } else {
            throw new Exception("Erro!");
        }
        return i;
    }

    public boolean pesquisar(int x) {
        return pesquisar(x, raiz);
    }

    private boolean pesquisar(int x, No i) {
        boolean resp;
        if (i == null) {
            resp = false;
        } else if (x == i.elemento) {
            resp = true;
        } else if (x < i.elemento) {
            resp = pesquisar(x, i.esq);
        } else {
            resp = pesquisar(x, i.dir);
        }
        return resp;
    }

    public int getAltura(){
        return getAltura(raiz);
    }

    private int getAltura(No i){
        int h = -1; 
        if(i == null){
            int hesq = getAltura(i.esq);
            int hdir = getAltura(i.dir);
            int hmax = hesq > hdir ? hesq : hdir;
            h = hmax + 1; 
        }
        return h; 
    }



}
