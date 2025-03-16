
import java.util.Scanner;

public class q10 {

    public static void main(String[] args) {
        
        Scanner sc = new Scanner(System.in);

        String entrada = sc.nextLine();

        while(!EhFIM(entrada)){

            System.out.println(contarPalavras(entrada));

            entrada = sc.nextLine();
        }
        

        sc.close();
    }

    public static int contarPalavras(String entrada){


        int  numPalavras = 1;

        for(int i = 1; i < entrada.length(); i++){
           

            if(entrada.charAt(i) == ' '){
                
                numPalavras += 1;
            }
            


        }
        return numPalavras;

    }

    public static boolean EhFIM(String entrada) {
        return (entrada.length() == 3 && entrada.charAt(0) == 'F' && entrada.charAt(1) == 'I'
                && entrada.charAt(2) == 'M');
    }

    
}
