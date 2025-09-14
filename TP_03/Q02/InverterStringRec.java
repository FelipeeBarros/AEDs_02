import java.util.Scanner;

public class InverterStringRec {

    public static String inverter(String s, int i) { // Função recursiva para inverter string
        if (i < 0) {
            return "";
        }
        return s.charAt(i) + inverter(s, i - 1);
    }

    public static boolean ehFIM(String s, int i) {
        if (s.length() != 3) return false;
        if (i == 3) return true; 
        char[] fim = {'F', 'I', 'M'};
        if (s.charAt(i) != fim[i]) return false;
        return ehFIM(s, i + 1);
    }

    public static void processar(Scanner sc) { // Processamento recursivo
        if (!sc.hasNextLine()) return; 

        String linha = sc.nextLine();

        if (ehFIM(linha, 0)) return;

        System.out.println(inverter(linha, linha.length() - 1));

        processar(sc); // chamada recursiva
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        processar(sc);
        sc.close();
    }
}