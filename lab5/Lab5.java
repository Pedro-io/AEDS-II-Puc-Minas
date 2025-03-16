package lab5;

public class Lab5 {
    public static void main(String[] args) {

    }
}

class Data {
    int dia, mes, ano;

    public Data(int dia, int mes, int ano) {

        this.dia = dia;
        this.mes = mes;
        this.ano = ano;
    }

}

class Duracao{
    int hora, minuto; 

    public Duracao(int hora, int minuto){
        this.hora = hora;
        this.minuto = minuto;   

    }

}


class Passagem{
    double valor; 
    String destino; 

    public Passagem(double valor, String destino){
        this.valor = valor;
        this.destino = destino; 
    }

    public void exibirPassagem(String destino){

        System.out.println("Esta passagem é para: " + destino);
    }
}