import java.util.*;

public class q16 {

    // Função recursiva para reverter a palavra
    public static String PalavraReversa(String palavra) {
        // Caso base: se a palavra tiver 1 caractere ou menos, retorne ela mesma
        if (palavra.length() <= 1) {
            return palavra;
        }
        // Passo recursivo: pega o último caractere e concatena com o reverso do restante
        char ultimoChar = palavra.charAt(palavra.length() - 1);
        String restoDaString = palavra.substring(0, palavra.length() - 1);
        return ultimoChar + PalavraReversa(restoDaString);
    }

    // Função recursiva para verificar se a palavra é igual à sua reversa
    public static String VerificaString(String palavra, String palavraReversa, int index) {
        // Caso base: se chegamos ao final da string, elas são iguais
        if (index == palavra.length()) {
            return "SIM";
        }
        // Caso base: se os caracteres forem diferentes, não é palíndromo
        if (palavra.charAt(index) != palavraReversa.charAt(index)) {
            return "NAO";
        }
        // Passo recursivo: avança para o próximo caractere
        return VerificaString(palavra, palavraReversa, index + 1);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String palavra;
        while (!(palavra = scanner.nextLine()).equals("FIM")) {
            // Remove espaços em branco e converte para minúsculas
            palavra = palavra.trim().toLowerCase();
            // Reverte a palavra
            String palavraReversa = PalavraReversa(palavra);
            // Verifica se a palavra é igual à sua reversa
            String resultado = VerificaString(palavra, palavraReversa, 0);
            System.out.println(resultado);
        }

        scanner.close();
    }
} 
    

