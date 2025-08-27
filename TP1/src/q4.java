import java.util.*;

public class q4 {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String entrada = sc.nextLine();
        Random gerador = new Random();
        gerador.setSeed(4);

        while (!EhFIM(entrada)) {
            char l1 = ((char) ('a' + (Math.abs(gerador.nextInt()) % 26)));
            char l2 = ((char) ('a' + (Math.abs(gerador.nextInt()) % 26)));
            char[] caracteres = entrada.toCharArray();
            for (int i = 0; i < entrada.length(); i++) {
                if (entrada.charAt(i) == l1) {
                    caracteres[i] = l2;
                }
            }
            System.out.println(new String(caracteres));
            entrada = sc.nextLine();
        }
        sc.close();
    }
    
    public static boolean EhFIM(String entrada) {
        return (entrada.length() == 3 && entrada.charAt(0) == 'F' && entrada.charAt(1) == 'I'
                && entrada.charAt(2) == 'M');
    }

}
