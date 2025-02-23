import java.util.*;


public class q03 {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);


        String entrada = sc.nextLine(); 

        String resp = Criptografa(entrada);

        System.out.println(resp); 

        sc.close();

    }


    public static String Criptografa(String entrada){
        
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
    }
}