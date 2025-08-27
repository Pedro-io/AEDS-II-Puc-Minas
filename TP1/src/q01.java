import java.util.*;

public class q01 {
    public static void main(String[] args) throws Exception {

        Scanner scanner = new Scanner(System.in);//SCANNER PARA AS ENTRADAS 

        String palavra = scanner.nextLine(); // LENDO A PRIMEIRA LINHA 
        
        while (palavra.equals("FIM") == false) { 
            // EQUANTO A STRING LIDA FOR DIFERENTE DE FIM VAMOS:
            

            String palavraReversa = PalavraReversa(palavra); // UTILIZAR A FUNÇÃO CRIADA PARA REVERTER A PALAVRA 
            String resultado = VerificaString(palavra, palavraReversa); // VERIFICAMOS SE A PALAVRA REVERSA É A MESMA QUE A PALAVRA PADRÃO, TEMOS "SIM" E "NÃO" COMO RETORNO 
            System.out.println(resultado); // PRINTA O RESULTADO

            palavra = scanner.nextLine(); // LE A PROXIMA PALAVRA 
        }
        

        scanner.close();   // FECHA O SCANNER 

    }

    public static String PalavraReversa(String palavra) {   
        palavra = palavra.trim(); // remove espaços em branco
        palavra = palavra.toLowerCase(); // deixa tudo em mauisculo 

        String palavraReversa = ""; // declara uma variavel String vazia para inserir a palavra reversa 
        for (int i = palavra.length() - 1 ; i >= 0; i--) { // para cada caracter da palavra de tamanho n 
            palavraReversa += palavra.charAt(i);// insira na posição n(i) da palavra reversa  
        }

        return palavraReversa;// retorna a palavra 
    }

    public static String VerificaString(String palavra, String palavraReversa) {

        for (int i = 0; i < palavra.length(); i++) {
            if (palavra.charAt(i) != palavraReversa.charAt(i)) {
                return "NAO"; // Se encontrar uma diferença, não é palíndromo
            }
        }
    
        return "SIM"; // Se chegou até aqui, todos os caracteres corresponderam, é palíndromo
    

    }

}
