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
        
        String resp ="";
        String letras = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" +
                            "abcdefghijklmnopqrstuvwxyz" +
                            "ÁÀÃÂÄÉÈÊËÍÌÎÏÓÒÕÔÖÚÙÛÜÇ" +
                           "áàãâäéèêëíìîïóòõôöúùûüç";
        for(int i = 0; i <= entrada.length(); i++){
            for(int j = 0; j <= letras.length(); j++){

                if(entrada.charAt(i) == letras.charAt(j)){
                    resp += letras.charAt(j + 3);
                }

            }
            
        }


        return resp;
    }
}