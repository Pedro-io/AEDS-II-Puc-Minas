import java.util.*;

public class q11 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String entrada;

        entrada = scanner.nextLine();
        while (!EhFIM(entrada)) {

            int resultado = substringMaisLongaSemRepeticao(entrada);
            System.out.println(resultado);
            entrada = scanner.nextLine();
        }

        scanner.close();
    }

    public static int substringMaisLongaSemRepeticao(String s) {
        int n = s.length();
        int comprimentoMaximo = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                // Verifica se a substring de i a j não tem repetição
                if (semRepeticao(s, i, j)) {
                    comprimentoMaximo = Math.max(comprimentoMaximo, j - i + 1);
                }
            }
        }

        return comprimentoMaximo;
    }

    // Método auxiliar para verificar se uma substring não tem caracteres repetidos
    public static boolean semRepeticao(String s, int inicio, int fim) {
        for (int i = inicio; i <= fim; i++) {
            for (int j = i + 1; j <= fim; j++) {
                if (s.charAt(i) == s.charAt(j)) {
                    return false; // Encontrou repetição
                }
            }
        }
        return true; // Não encontrou repetição
    }

    public static boolean EhFIM(String entrada) {
        return (entrada.length() == 3 && entrada.charAt(0) == 'F' && entrada.charAt(1) == 'I'
                && entrada.charAt(2) == 'M');
    }

   
}