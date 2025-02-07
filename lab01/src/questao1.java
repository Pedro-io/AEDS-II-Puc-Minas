import java.util.*;

public class questao1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String texto = sc.nextLine();
        System.out.println(contaMaiusculaIterativo(texto));
        System.out.println(contaMaiusculaRecursivo(texto));

     
    }

    public static int contaMaiusculaIterativo(String texto) {
            
        int cont = 0;

        for (int i = 0; i < texto.length(); i++) {
            if (Character.isUpperCase(texto.charAt(i))) {
                cont++;
            }
        }
        return cont;
    }


    public static int contaMaiusculaRecursivo(String texto) {
        
        
        
        return contaMaiusculaRecursivo(texto, 0);
    }
}