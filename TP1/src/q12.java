import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class q12 {

    public static boolean EhFIM(String entrada) {
        return (entrada.length() == 3 && entrada.charAt(0) == 'F' && entrada.charAt(1) == 'I'
                && entrada.charAt(2) == 'M');
    }

    public static String validaSenha(String entrada){

        String resultado = "NAO"; 
        int contadorEsp = 0, contadorMai = 0, contadorNum = 0, contadorMin = 0;

        if(entrada.length() > 8){

            resultado = "SIM";
        } 

        for(int i = 0; i < entrada.length(); i++){
            
            int codChar = (int) entrada.charAt(i);
            

            if((33 <= codChar && codChar <= 43) || (58 <= codChar && codChar <= 64) || (91 <= codChar && codChar <= 96) || (123 <= codChar && codChar <= 126) ){
                
                contadorEsp++;
            }

            if(65 <= codChar && codChar <= 90){

                contadorMai++;
            }

            if(97 <= codChar && codChar <= 122){

                contadorMin++;
            }

            if(48 <= codChar && codChar <= 57){

                contadorNum++;
            }
        }

        if( contadorEsp >= 1){

            resultado = "SIM";
        }

        if( contadorMai >= 1){

            resultado = "SIM";
        }

        if( contadorMin >= 1){

            resultado = "SIM";
        }
        if( contadorNum >= 1){

            resultado = "SIM";
        }

        return resultado;

    } 
    

    public static void main(String[] args) {
        
        FileOutputStream fos2 = new FileOutputStream(FileDescriptor.out);
        PrintStream ps2 = new PrintStream(fos2, true, StandardCharsets.ISO_8859_1);
        System.setOut(ps2);
        Scanner sc = new Scanner(System.in);

        String entrada = sc.nextLine();
        while (!EhFIM(entrada)) {

            System.out.println(validaSenha(entrada));

            entrada = sc.nextLine();
        }

        sc.close();
    }


    
    
}
