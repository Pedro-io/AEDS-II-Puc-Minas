import java.util.*;
import java.io.*;


public class Agenda {
    public static void main(String[] args) throws Exception {

        Arvore agenda = new Arvore();
        String letras = "NGTDJQWBFHLORUXACEIKMPSVYZ";
    
        for(int i = 0; i < letras.length(); i++ ){
            agenda.inserir(letras.charAt(i));
        }
    agenda.caminhar();
    }


    private No inserirContato(int x, No i) throws Exception {
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
 
    
}

class Arvore{

    private No raiz;

    public Arvore(){
        this.raiz = null;
    }

    public void inserir(char letra) throws Exception {
        raiz = inserir(letra, raiz);
    }

    private No inserir(char letra, No i) throws Exception {
        if (i == null) {
            i = new No(letra);
        } else if (letra < i.elemento) {
            i.esq = inserir(letra, i.esq);
        } else if (letra > i.elemento) {
            i.dir = inserir(letra, i.dir);
        } else {
            throw new Exception("Erro!");
        }
        return i;
    }

    public void caminhar() {
        caminhar(raiz);
        System.out.println();
    }

    private void caminhar(No i) {
        if (i != null) {
            caminhar(i.esq);
            System.out.print(i.elemento + " ");
            caminhar(i.dir);
        }
    }

    public No getRaiz() {
        return raiz;
    }

    public void setRaiz(No raiz) {
        this.raiz = raiz;
    }

}

class No{
    
    char elemento;
    No esq, dir, primeiro, ultimo;

    public No(
        char elemento
    ){
        this.elemento = elemento;
        this.esq = null;
        this.primeiro = null;
        this.ultimo = null; 
        this.esq = this.dir = null;
    }

    public char getElemento() {
        return elemento;
    }

    public void setElemento(char elemento) {
        this.elemento = elemento;
    }

    public No getEsq() {
        return esq;
    }

    public void setEsq(No esq) {
        this.esq = esq;
    }

    public No getDir() {
        return dir;
    }

    public void setDir(No dir) {
        this.dir = dir;
    }

    public No getPrimeiro() {
        return primeiro;
    }

    public void setPrimeiro(No primeiro) {
        this.primeiro = primeiro;
    }

    public No getUltimo() {
        return ultimo;
    }

    public void setUltimo(No ultimo) {
        this.ultimo = ultimo;
    }    
}

class Contato{

    private Contato prox;
    private String nome, telefone, email, cpf ;
    
    public Contato(
        String nome,
        String telefone,
        String email,
        String cpf
    ){
        this.nome = nome;
        this.telefone = telefone;
        this.email = email;
        this.cpf = cpf; 
        this.prox = null;
    }

    public Contato getProx() {
        return prox;
    }

    public void setProx(Contato prox) {
        this.prox = prox;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getTelefone() {
        return telefone;
    }

    public void setTelefone(String telefone) {
        this.telefone = telefone;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getCpf() {
        return cpf;
    }

    public void setCpf(String cpf) {
        this.cpf = cpf;
    }
}