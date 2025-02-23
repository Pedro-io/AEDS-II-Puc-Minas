import java.util.Locale;
import java.util.Scanner;

public class q1 {

  public static void processarRegistro(int id, double preco, String tempo, String cidade) {
    System.out.printf("Registro lido: %d %.2f %s %s\n", id, preco, tempo, cidade);
  }

  public static void main(String[] args) {
    //Cria e configura o Scanner para interpretar números no formato 
    //americano, onde o separador decimal é o ponto ('.').
    Scanner scanner = new Scanner(System.in);
    scanner.useLocale(Locale.US); 

    int id;
    double preco;
    String tempo;
    String cidade;

    
    id = scanner.nextInt();
    //Ler o n registros
    while(id != 0) {
      preco = scanner.nextDouble();
      tempo = scanner.next();
      cidade = scanner.nextLine().trim();
      processarRegistro(id, preco, tempo, cidade);
      id = scanner.nextInt();
    }

    scanner.close();
  }
}
    

