import java.util.*;

public class q20 {
    public static boolean ehVogal(String str) {
        // Caso Base: se a string estiver vazia, consideramos que é composta por vogais
        if (str.length() == 0) {
            return true;
        }
    
        // Verifica se o primeiro caractere é uma vogal
        String vogal = "aeiouAEIOU";
        char primeiroChar = str.charAt(0);
    
        // Se o primeiro caractere não for uma vogal, retorna false
        if (vogal.indexOf(primeiroChar) == -1) {
            return false;
        }
    
        // Caso Recursivo: chama a função com o restante da string
        return ehVogal(str.substring(1));
    }
    
    public static boolean ehConsoante(String str) { // verifica se é consoante

        

        if(str.length() == 0){ //caso base 
            return true;
        }
        
        String consonant = "bcdfghjklmnpqrstvwxyzçBCDFGHJKLMNPQRSTVWXYZÇ"; // Conjunto de consoantes
        char primeiroChar = str.charAt(0);

        if(consonant.indexOf(primeiroChar) == -1){
            return false;
        }

        return ehConsoante(str.substring(1));


    }

    // Verifica se é inteiro
    public static boolean ehInteiro(String str) {
        

        if(str.length() == 0)
        {
            return true;
        }

        String inteiros = "1234567890"; // Conjunto de números
        char primeiroChar = str.charAt(0);

        if (inteiros.indexOf(primeiroChar) == -1) 
        {
            return false;
        }

        return ehInteiro(str.substring(1));

    }

    // Verifica se é Real
    public static boolean ehReal(String str) {
        

        if(str.length() == 0){
            return true;
        }

        String real = "1234567890.,"; // Conjunto de características que compõem um número real
        char primeiroChar = str.charAt(0);

        if(real.indexOf(primeiroChar) == -1){
            return false;
        }
        return ehReal(str.substring(1));
    }

    public static boolean EhFIM(String entrada) {
        return (entrada.length() == 3 && entrada.charAt(0) == 'F' && entrada.charAt(1) == 'I'
                && entrada.charAt(2) == 'M');
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        String entrada = sc.nextLine();

        while (!EhFIM(entrada)) {

            // Chama os métodos e imprime "sim" ou "nao"
            if (ehVogal(entrada)) {
                System.out.print("SIM ");
            } else {
                System.out.print("NAO ");
            }

            if (ehConsoante(entrada)) {
                System.out.print("SIM ");
            } else {
                System.out.print("NAO ");
            }

            if (ehInteiro(entrada)) {
                System.out.print("SIM ");
            } else {
                System.out.print("NAO ");
            }

            if (ehReal(entrada)) {
                System.out.print("SIM");
            } else {
                System.out.print("NAO");
            }
            System.out.println();
            entrada = sc.nextLine();

        }

        sc.close();
    }
}
