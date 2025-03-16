import java.util.*;

public class q8 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String entrada = sc.nextLine();

        while (!EhFIM(entrada)) {

            int resultado = somaRecursiva(entrada, entrada.length());
            System.out.println(resultado);
            entrada = sc.nextLine();
        }

    }

    public static int somaRecursiva(String entrada, int tamanho) {
        if (tamanho == 0) { // Caso base: squando não há mais caracteres para somar
            return 0;
        }

        // Converte o último caractere para um número e soma recursivamente
        int ultimoDigito = Character.getNumericValue(entrada.charAt(tamanho - 1));
        return ultimoDigito + somaRecursiva(entrada, tamanho - 1);
    }

    public static boolean EhFIM(String entrada) {
        return (entrada.length() == 3 && entrada.charAt(0) == 'F' && entrada.charAt(1) == 'I'
                && entrada.charAt(2) == 'M');
    }

}
