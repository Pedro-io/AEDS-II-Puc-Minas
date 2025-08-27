import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class q03 {
    public static void main(String[] args) {
        // Força saída em UTF-8
        FileOutputStream fos2 = new FileOutputStream(FileDescriptor.out);
        PrintStream ps2 = new PrintStream(fos2, true, StandardCharsets.UTF_8);
        System.setOut(ps2);

        Scanner sc = new Scanner(System.in, StandardCharsets.UTF_8);
        String entrada = sc.nextLine();

        while (!EhFIM(entrada)) {
            String resp = Criptografa(entrada);
            System.out.println(resp);
            entrada = sc.nextLine();
        }

        sc.close();
    }

    public static boolean EhFIM(String entrada) {
        return (entrada.length() == 3 &&
                entrada.charAt(0) == 'F' &&
                entrada.charAt(1) == 'I' &&
                entrada.charAt(2) == 'M');
    }

    public static String Criptografa(String entrada) {
        StringBuilder resp = new StringBuilder();
        for (int i = 0; i < entrada.length(); i++) {
            char c = entrada.charAt(i);
            if (c >= 32 && c <= 126) {
                c = (char) (c + 3);
            }
            resp.append(c);
        }
        return resp.toString();
    }
}
