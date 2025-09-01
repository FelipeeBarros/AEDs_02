import java.util.Random;
import java.util.Scanner;

public class AlteracaoAleatoria {

    public static String substituirCaracteres(String texto, char caractereOriginal, char caractereSubstituto) {
        StringBuilder resultado = new StringBuilder();

        for (int i = 0; i < texto.length(); i++) {
            char caractereAtual = texto.charAt(i);
            if (caractereAtual == caractereOriginal) {
                resultado.append(caractereSubstituto);
            } else {
                resultado.append(caractereAtual);
            }
        }

        return resultado.toString();
    }

    public static boolean verificarFim(String texto) {
        return texto.length() == 3 &&
                texto.charAt(0) == 'F' &&
                texto.charAt(1) == 'I' &&
                texto.charAt(2) == 'M';
    }

    public static void main(String[] args) { 
        Random geradorAleatorio = new Random();
        geradorAleatorio.setSeed(4);
        Scanner leitor = new Scanner(System.in);

        String entrada = leitor.nextLine();

        while (!verificarFim(entrada)) {
            char letraParaSubstituir = (char) ('a' + Math.abs(geradorAleatorio.nextInt()) % 26);
            char letraSubstituta = (char) ('a' + Math.abs(geradorAleatorio.nextInt()) % 26);

            String textoModificado = substituirCaracteres(entrada, letraParaSubstituir, letraSubstituta);
            System.out.println(textoModificado);

            entrada = leitor.nextLine();
        }

        leitor.close();
    }
}