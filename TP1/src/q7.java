
import java.util.Scanner;

public class q7 {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        String entrada = sc.nextLine();

        while(!EhFIM(entrada)){

            System.out.println(PalavraReversa(entrada));

            entrada = sc.nextLine();
        }

        sc.close();

        
    }
    
    public static String PalavraReversa(String palavra) {
        /* 
                função para reverter a palavra
                parametros: 
                String palavra: string de entrada do usuário que vai ser revertida

                return : String com o reverso da entrada
           */      

        String palavraReversa = ""; // declara uma variavel String vazia para inserir a palavra reversa 
        for (int i = palavra.length() - 1 ; i >= 0; i--) { // para cada caracter da palavra de tamanho n 
            palavraReversa += palavra.charAt(i);// insira na posição n(i) da palavra reversa  
        }

        return palavraReversa;// retorna a palavra 
    }

    public static boolean EhFIM(String entrada) {
        return (entrada.length() == 3 && entrada.charAt(0) == 'F' && entrada.charAt(1) == 'I'
                && entrada.charAt(2) == 'M');
    }
}
