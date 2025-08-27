class Celula{
    public int elemento;
    public Celula prox;

    public Celula(int elemento){
        this.elemento = elemento;
    }

    public Celula(int elemento, Celula prox){
        this.elemento = elemento;
        this.prox = prox;
    }
}

public class Lista {
    private Celula primeiro;
    private Celula ultimo;
    
    public Lista(){
        primeiro = new Celula(-1);
        ultimo = primeiro;
    }

    public void mostrar(){
        for(Celula i = primeiro.prox; i!= null; i = i.prox){
            System.out.println(i.elemento);
        }
    }

    public boolean pesquisar(int elemento){
        boolean resp = false;
        for(Celula i = primeiro.prox; i != null; i = i.prox){
            if(i.elemento == elemento){
                resp = true;
                i = ultimo;
            }
        }
        return resp;
    }

    public void InserirInicio(int elemento){
        Celula i = new Celula(elemento);
        if(primeiro.prox != null){
            i.prox = primeiro.prox.prox;
            primeiro.prox = i;
        }
        else{
            primeiro.prox = i;
        }
    }
}
