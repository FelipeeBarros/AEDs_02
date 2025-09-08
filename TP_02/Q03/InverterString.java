import java.util.Scanner;

public class InverterString {

    public static String inverter(String s) {
        int n = s.length();
        char[] resultado = new char[n];
        for (int i = 0; i < n; i++) {
            resultado[i] = s.charAt(n - 1 - i);
        }
        return new String(resultado);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String linha;

        linha = sc.nextLine();
        while (!(linha.length() == 3 &&
                linha.charAt(0) == 'F' &&
                linha.charAt(1) == 'I' &&
                linha.charAt(2) == 'M')) {

            System.out.println(inverter(linha));
            linha = sc.nextLine();
        }
        sc.close();
    }
}
