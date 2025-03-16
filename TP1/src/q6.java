import java.util.Scanner;

public class q6 {

    public static boolean ehVogal(String str) { // verifica se é vogal

        String vogal = "aeiouAEIOU";
        int cont = 0;
        boolean ehVogal = false; // Resposta final

        for (int i = 0; i < str.length(); i++) { // Lê a string
            for (int j = 0; j < vogal.length(); j++) { // Lê para cada letra da string o conjunto de vogal
                if (str.charAt(i) == vogal.charAt(j)) { // Se igual entra no contador
                    cont++;
                }
            }
        }

        if (cont == str.length()) { // Se o contador for igual ao tamanho da string então são todas vogais
            ehVogal = true;
        }

        return ehVogal;
    }

    public static boolean ehConsoante(String str) { // verifica se é consoante

        String consonant = "bcdfghjklmnpqrstvwxyzçBCDFGHJKLMNPQRSTVWXYZÇ"; // Conjunto de consoantes
        int cont = 0; // Contador de quai letras são vogais
        boolean ehConsoante = false; // Resposta

        for (int i = 0; i < str.length(); i++) { // Lê toda string
            for (int j = 0; j < consonant.length(); j++) { // Lê o conjunto
                if (str.charAt(i) == consonant.charAt(j)) { // Se a letra pertencer ao conjunto entra no contador
                    cont++;
                }
            }
        }

        if (cont == str.length()) { // Se contador igual ao tamanho da string, então, todas consoantes
            ehConsoante = true;
        }

        return ehConsoante;
    }

    // Verifica se é inteiro
    public static boolean ehInteiro(String str) {
        String integer = "1234567890"; // Conjunto de números
        boolean ehInteiro = true; // Resposta
        boolean found = false; // Auxiliar

        for (int i = 0; i < str.length(); i++) { // Lê toda a string
            found = false; // Sempre que inicia uma nova letra coloca como false

            for (int j = 0; j < integer.length(); j++) { // Lê todo o conjunto
                if (str.charAt(i) == integer.charAt(j)) { // Se a letra for igual ao conjunto então achou um número
                    found = true;
                    break;
                }
            }

            if (!found) { // Se permancer falsa -> resposta fica falsa
                ehInteiro = false;
            }
        }

        return ehInteiro;
    }

    // Verifica se é Real
    public static boolean ehReal(String str) {
        String real = "1234567890.,"; // Conjunto de características que compõem um número real
        boolean ehReal = true; // Resposta
        boolean found = false; // Auxiliar
        int cont = 0;

        for (int i = 0; i < str.length(); i++) { // Lê toda a string
            found = false; // Auxiliar é colocada como falsa toda vez que lê uma nova letra

            for (int j = 0; j < real.length(); j++) { // Lê o conjunto
                if (str.charAt(i) == real.charAt(j)) { // Se a letra tiver algo igual no conjunto
                    found = true; // A auxiliar se transforma em verdadeira
                    break;
                }
            }

            if (!found) { // Se permance como falsa -> resposta fica falsa
                ehReal = false;
            }

            if (str.charAt(i) == ',' || str.charAt(i) == '.') { // Se tiver mais de um ponto ou virgula dá erro
                cont++; // Se existir mais de 1 cont é pq tem mais de uma: , ou .
            }
        }

        if (cont > 1) { // Verificação
            ehReal = false; // Resposta
        }

        return ehReal;
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