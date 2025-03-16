import java.util.*;

public class q4 {

    public static void main(String[] args) {

        

        Scanner sc = new Scanner(System.in);

        String entrada = sc.nextLine(); // Lê a entrada

        // Gera os caracteres aleatorios
        Random gerador = new Random();
        gerador.setSeed(4);
        char l1 = (char) ('a' + (Math.abs(gerador.nextInt()) % 26));
        char l2 = (char) ('a' + (Math.abs(gerador.nextInt()) % 26));

        // While: Enquando a entrada for diferente de fim...
        while (!EhFIM(entrada)) {

            char[] caracteres = entrada.toCharArray(); // Transforma a entrada em um array

            for (int i = 0; i < entrada.length(); i++) {

                if (entrada.charAt(i) == l1) { // se a entrada for diferente de l1

                    caracteres[i] = l2;// troca por l2
                }
            }

            System.out.println(new String(caracteres)); // printa a saida convertendo para string
            entrada = sc.nextLine(); // le a proxima

        }

        sc.close();
    }

    public static boolean EhFIM(String entrada) {
        return (entrada.length() == 3 && entrada.charAt(0) == 'F' && entrada.charAt(1) == 'I'
                && entrada.charAt(2) == 'M');
    }

}
