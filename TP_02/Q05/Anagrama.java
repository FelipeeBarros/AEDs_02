import java.util.Scanner;

public class Anagrama {

    // Conta a frequência de letras de 'a' a 'z', ignorando maiúsculas/minúsculas e caracteres não alfabéticos
    public static int[] contar(String s) {
        int[] freq = new int[26];
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);

            // ignorar espaços e hífens
            if (c == ' ' || c == '-') continue;

            // transformar maiúscula em minúscula
            if (c >= 'A' && c <= 'Z') c = (char)(c + 32);

            // contar apenas letras minúsculas
            if (c >= 'a' && c <= 'z') freq[c - 'a']++;
        }
        return freq;
    }

    // Compara se dois vetores de frequência são iguais
    public static boolean iguais(int[] a, int[] b) {
        for (int i = 0; i < a.length; i++) {
            if (a[i] != b[i]) return false;
        }
        return true;
    }

    // Verifica se duas strings são anagramas
    public static boolean ehAnagrama(String a, String b) {
        int[] fa = contar(a);
        int[] fb = contar(b);
        return iguais(fa, fb);
    }

    // Remove espaços do início e do fim da string (trim manual)
    public static String trim(String s) {
        int ini = 0;
        int fim = s.length() - 1;

        while (ini < s.length() && s.charAt(ini) == ' ') ini++;
        while (fim >= 0 && s.charAt(fim) == ' ') fim--;

        String nova = "";
        for (int i = ini; i <= fim; i++) nova += s.charAt(i);

        return nova;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (true) {
            String linha = sc.nextLine();

            // Condição de parada
            if (linha.equals("FIM")) break;

            // Encontrar o separador '-' manualmente
            int pos = -1;
            for (int i = 0; i < linha.length(); i++) {
                if (linha.charAt(i) == '-') {
                    pos = i;
                    break;
                }
            }

            // separar em duas strings
            String s1 = "";
            String s2 = "";
            if (pos != -1) {
                for (int i = 0; i < pos; i++) s1 += linha.charAt(i);
                for (int i = pos + 1; i < linha.length(); i++) s2 += linha.charAt(i);
            }

            // remover espaços extras nas pontas (trim manual)
            s1 = trim(s1);
            s2 = trim(s2);

            // imprimir resultado
            if (ehAnagrama(s1, s2)) {
                System.out.println("SIM");
            } else {
                System.out.println("N" + "\u00c3" + "O");
            }
        }

        sc.close();
    }
}
