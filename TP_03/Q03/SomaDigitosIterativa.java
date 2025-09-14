import java.util.Scanner;

public class SomaDigitosIterativa {

    public static int somaIterativa(int valor) {
        int soma = 0;
        while (valor > 0) {
            soma += valor % 10;
            valor /= 10;
        }
        return soma;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String entrada;

        entrada = sc.nextLine();

        while (!(entrada.length() == 3 &&
                 entrada.charAt(0) == 'F' &&
                 entrada.charAt(1) == 'I' &&
                 entrada.charAt(2) == 'M')) {

            int numero = 0;
            for (int i = 0; i < entrada.length(); i++) {
                char c = entrada.charAt(i);
                numero = numero * 10 + (c - '0');
            }

            System.out.println(somaIterativa(numero));

            entrada = sc.nextLine();
        }

        sc.close();
    }
}
