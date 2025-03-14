package lab6;

import java.util.Scanner;

public class lab6 {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        String tipo = sc.next();

        if(tipo.charAt(0) == 'E' || tipo.charAt(0) == 'D'){

            int elem = sc.nextInt();
        }
        
        if(tipo.charAt(0) == 'E' || tipo.charAt(0) == 'D'){

            int elem = sc.nextInt();
        }



    }
}

class PilhaLinear{


    private int n;
    private int[] array; 
    
    
    public PilhaLinear(int max){
        this.n = 0;
        this.array = new int[max];
    }

    
    public void empilhar (int elem) throws Exception{

        if(n >= array.length){
            throw new Exception("overflow");
        }

        array[n++] = elem;

    }

    public int remover()throws Exception{
        if(n == 0){
            throw new Exception("underflow");
        }       
        
        return --n;   

    }

    public boolean pesquisar(int elem){

        boolean resp = false;
        for(int i = 0; i < n; i++){

            if(elem == array[i]){
                resp = true; 
            }
        }

        return resp; 
    }

    public void mostrar(){
        for(int i = n; i >=0 ; i--){
            System.out.print(array[i]);
        }

        System.out.println();
    } 






}

