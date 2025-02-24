import java.util.*;

public class q03 {

        

        public static void main(String[] args) {

                Scanner sc = new Scanner(System.in);

                String entrada = sc.nextLine();

                while (!EhFIM(entrada)) {

                        String resp = Criptografa(entrada);

                        System.out.println(resp);

                        entrada = sc.nextLine();

                }

                sc.close();

        }

        public static boolean EhFIM(String entrada) {
                return (entrada.length() == 3 && entrada.charAt(0) == 'F' && entrada.charAt(1) == 'I'
                                && entrada.charAt(2) == 'M');
        }

        

        public static String Criptografa(String entrada) {

                int valorDeslocado;
                char charDeslocado;
                String resp = "";

                for (int i = 0; i < entrada.length(); i++) {

                        valorDeslocado = (int) entrada.charAt(i);
                        valorDeslocado = valorDeslocado + 3;
                        charDeslocado = (char) valorDeslocado;
                        resp += charDeslocado;

                }

                return resp;
        }

}