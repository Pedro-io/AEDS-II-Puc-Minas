import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class q9 {

    public static void main(String[] args) {

        FileOutputStream fos2 = new FileOutputStream(FileDescriptor.out);
        PrintStream ps2 = new PrintStream(fos2, true, StandardCharsets.ISO_8859_1);
        System.setOut(ps2);
        Scanner sc = new Scanner(System.in);

        String entrada = sc.nextLine();

        while (!EhFIM(entrada)) {

            String[] entradasSeparadas = separarPalavras(entrada);

            String ordenada1 = Ordenar(entradasSeparadas[0]);
            String ordenada2 = Ordenar(entradasSeparadas[1]);
            if (isAnagrama(ordenada1, ordenada2)) {
                System.out.println("SIM");
            }

            else {
                System.out.println("NÃO");
            }

            entrada = sc.nextLine();
        }

        sc.close();
    }

    public static boolean EhFIM(String entrada) {
        return (entrada.length() == 3 && entrada.charAt(0) == 'F' && entrada.charAt(1) == 'I'
                && entrada.charAt(2) == 'M');
    }

    public static String Ordenar(String entrada) {
        entrada = entrada.toLowerCase();
        char[] caracteres = entrada.toCharArray();
        int n = caracteres.length;

        // Algoritmo de seleção
        for (int i = 0; i < n - 1; i++) {
            int menorIndice = i;
            for (int j = i + 1; j < n; j++) {
                if (caracteres[j] < caracteres[menorIndice]) {
                    menorIndice = j;
                }
            }

            // Troca
            char aux = caracteres[i];
            caracteres[i] = caracteres[menorIndice];
            caracteres[menorIndice] = aux;
        }

        return new String(caracteres);
    }

    public static boolean isAnagrama(String palavra1, String palavra2) {
        // se as duas strings não tem o mesmo tamanho, não é anagrama
        if (palavra1.length() != palavra2.length()) {
            return false;
        }

        for (int i = 0; i < palavra1.length(); i++) {
            if (palavra1.charAt(i) != palavra2.charAt(i)) {
                return false;
            }
        }

        return true;

    }

    public static String[] separarPalavras(String entrada) {
        int pos = -1;

        for (int i = 0; i < entrada.length() - 2; i++) {
            if (entrada.charAt(i) == ' ' && entrada.charAt(i + 1) == '-' && entrada.charAt(i + 2) == ' ') {
                pos = i;
            }
        }

        if (pos == -1) {
            return null;
        }

        String palavra1 = "";
        String palavra2 = "";

        for (int i = 0; i < pos; i++) {
            palavra1 += entrada.charAt(i);
        }

        for (int i = pos + 3; i < entrada.length(); i++) {
            palavra2 += entrada.charAt(i);
        }

        return new String[] { palavra1, palavra2 };
    }

}
