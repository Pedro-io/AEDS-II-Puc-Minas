import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Scanner;

public class q14 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Lê o número inteiro n
        int n = scanner.nextInt();

        // Cria um arquivo temporário
        File arquivo = new File("dados.txt");

        try (RandomAccessFile raf = new RandomAccessFile(arquivo, "rw")) {
            // Salva os n números reais no arquivo
            for (int i = 0; i < n; i++) {
                double valor = scanner.nextDouble();
                raf.writeDouble(valor);
            }

            // Fecha o arquivo após a escrita
            raf.close();

            // Reabre o arquivo para leitura de trás para frente
            try (RandomAccessFile rafLeitura = new RandomAccessFile(arquivo, "r")) {
                // Posiciona o ponteiro no final do arquivo
                long posicao = rafLeitura.length();

                // Lê os valores de trás para frente
                while (posicao > 0) {
                    posicao -= 8; // Cada double ocupa 8 bytes
                    rafLeitura.seek(posicao);
                    double valor = rafLeitura.readDouble();
                    System.out.println(valor);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            // Exclui o arquivo temporário após o uso
            arquivo.delete();
        }

        scanner.close();
    }
}
