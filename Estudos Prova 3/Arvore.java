

public class Arvore{
    private No raiz;
    public static void main(String[] args) throws Exception {
        Arvore arv = new Arvore();
        int elementos[] = {5,3,7,2,1,4,6};
        System.out.print("Elementos inseridos: ");
        for(int i = 0; i < elementos.length;i++){
            System.out.printf("%d ", elementos[i]);
            arv.inserir(elementos[i]);
        }
        System.out.println();
        System.out.printf("Caminhar Central: ");
        arv.caminharCentral();
        System.out.println();
        System.out.println(arv.pesquisar(5));
        System.out.println(arv.pesquisar(4));
        System.out.println(arv.pesquisar(10));
        System.out.println("Menor: " + arv.getMenor());
        System.out.println("Maior: "+ arv.getMaior());
    }


    // Métodos de inserção
    public void inserir(int elemento)throws Exception{
        raiz = inserir(elemento, raiz);
    }

    public No inserir(int elemento, No i)throws Exception{
        if(i == null){
            i = new No(elemento);
        }
        else if(elemento < i.elemento){
            i.esq = inserir(elemento, i.esq);
        }
        else if(elemento > i.elemento){
            i.dir = inserir(elemento, i.dir);
        }
        else{// Caso o elemento que estamos tentando inserir já exista na arvore
            throw new Exception("Erro");
        }
        return i;
    }

    //Métodos de caminhamento
    public void caminharCentral(){
        caminharCentral(raiz);
    }
    public void caminharCentral(No i){
        if(i!=null){
            caminharCentral(i.esq);
            System.out.printf("%d ", i.elemento);
            caminharCentral(i.dir);
        }
    }

    public void caminharPre(){
        caminharPre(raiz);
    }

    public void caminharPre(No i){
        if(i!=null){
            System.out.printf("%d ",i.elemento);
            caminharPre(i.esq);
            caminharPre(i.dir);
        }
    }
    //Métodos para pesquisar 
    public boolean pesquisar(int elemento)throws Exception{
        return pesquisar(elemento, raiz);
    }

    public boolean pesquisar(int elemento, No i) throws Exception{
        boolean resp;
        if(i ==null){
            resp = false;
        }
        else if(elemento < i.elemento){
            resp = pesquisar(elemento, i.esq);
        }
        else if(elemento > i.elemento){
            resp = pesquisar(elemento, i.dir);
        }
        else{
            resp = true;
        }
        return resp;
    }
    // Métodos para encontrar o maior e o menor
    public int getMaior(){
        return getMaior(raiz);
    }

    public int getMaior(No raiz){
        int maior = -1;
        if(raiz != null){
            for(No i = raiz; i != null; i = i.dir){
            maior = i.elemento;
            }
        }
        return maior;
    }
    public int getMenor(){
        return getMenor(raiz);
    }
    public int getMenor(No raiz){
        int menor = -1;
        if (raiz != null){
            for(No i = raiz; i != null; i = i.esq){
                menor = i.elemento;
            }
        } 
        return menor;
    }

    public No remover(int elemento, No i) throws Exception{
        if(i==null){
            throw new Exception("erro");
        }
        else if (elemento < i.elemento){
            i.esq = remover(elemento, i.esq);
        }
        else if(elemento > i.elemento){
            i.dir = remover(elemento, i.dir);
        }
        else if(i.dir == null){
            i = i.esq;
        }
        else if(i.esq == null){
            i = i.dir;
        }
        else{
            i.esq = maiorEsq(i, i.esq);
        }
        return i;
    }

    public No maiorEsq(No i, No j){
        if(j.dir == null){
            i.elemento = j.elemento;
            j = j.esq;
        }
        else{
            j.dir = maiorEsq(i, j.dir);
        }
        return j;
    }

}

class No{
    public int elemento;
    public No esq, dir;

    public No(int elemento){
        this.elemento = elemento;
        this.dir = null;
        this.esq = null;
    }

    public No(
            int elemento,
            No dir,
            No esq
        ){
        this.elemento = elemento;
        this.dir = dir;
        this.esq = esq;
    }
}