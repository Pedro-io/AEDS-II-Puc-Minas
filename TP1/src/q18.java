import java.util.*;

public class q18 {
    public static String PalavraReversa(String palavra) {
        // Remove espaços em branco e converte para minúsculas
        palavra = palavra.trim().toLowerCase();
    
        if (palavra.length() <= 1) {
            return palavra;
        }
    
                char ultimoChar = palavra.charAt(palavra.length() - 1); // Último caractere
        String restoDaString = palavra.substring(0, palavra.length() - 1); // Restante da string
    
        return ultimoChar + PalavraReversa(restoDaString); // Concatena e chama recursivamente
    }

    public static String VerificaString(String palavra, String palavraReversa) {
       
        if(palavra.length() != palavraReversa.length()){
            return "NAO";
        }

        if(palavra.length() == 0){
            return "SIM";
        }
        

        if(palavra.charAt(0) != palavraReversa.charAt(0))
        {
            return "NAO";
        }
       
    
        return VerificaString(palavra.substring(1), palavraReversa.substring(1)); 
    

    }

    
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


}
