import java.util.*;

public class q03 {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

<<<<<<< HEAD

        String entrada = sc.nextLine(); 
=======
        String entrada = sc.nextLine();
>>>>>>> ce4e92b258f9a7cc19725e4cd8cef0a5b73864d1

        String resp = Criptografa(entrada);

        System.out.println(resp);

        sc.close();

    }

    public static String Criptografa(String entrada) {

        String resp = "";

        
<<<<<<< HEAD
        int valorDeslocado;
        char charDeslocado;
        String resp = "";

        
        for(int i = 0; i < entrada.length(); i++){

            valorDeslocado = (int) entrada.charAt(i);
            valorDeslocado = valorDeslocado + 3; 
            charDeslocado = (char) valorDeslocado;
            resp += charDeslocado;



        }

        return resp;
=======

        return resp; 

>>>>>>> ce4e92b258f9a7cc19725e4cd8cef0a5b73864d1
    }
}