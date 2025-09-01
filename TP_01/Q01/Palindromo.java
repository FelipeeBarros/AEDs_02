import java.util.Scanner;

public class Palindromo { 
    public static boolean ehPalindromo(String texto) { 
        int inverso = texto.length() - 1; // pega a ultima posicao do texto
        for (int i = 0; i < texto.length() / 2; i++) { // repeticao ate a metade do texto
            if (texto.charAt(i) != texto.charAt(inverso)) { // comparacao
                return false;
            }
            inverso--;
        }
        return true;
    }

    public static void main(String[] args) {

        String entrada;
        String result;
        Scanner ler = new Scanner(System.in);
        entrada = ler.nextLine();
        while (!entrada.equals("FIM")) {
            if (ehPalindromo(entrada) == true) {
                result = "SIM";
            } else {
                result = "NAO";
            }
            System.out.println(result);
            entrada = ler.nextLine();
        }
    }
}