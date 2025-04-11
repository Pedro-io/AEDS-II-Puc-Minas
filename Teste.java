public class Teste {
    public static void main(String[] args) {
        String[] array = new String[10];
        for (int i = 0; i < array.length; i++) {
            array[i] = "";
        }

        for (String s : array) {
            System.err.println(s);
        }
    }
}
