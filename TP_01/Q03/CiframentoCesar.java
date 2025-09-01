import java.util.Scanner;

class CiframentoCesar {
    // Método que aplica cifra de César com deslocamento 3
    public static String cifra(String s) {
        String criptografado = "";

        for (int i = 0; i < s.length(); i++) {
            char original = s.charAt(i);
            char alterado;

            if (original >= 32 && original <= 126) { 
                alterado = (char) (original + 3);
            } else {
                alterado = original;
            }

            criptografado += alterado;
        }
        return criptografado;
    }

    public static boolean verificarFim(String texto) {
        return texto.length() == 3 &&
                texto.charAt(0) == 'F' &&
                texto.charAt(1) == 'I' &&
                texto.charAt(2) == 'M';
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        String linha = sc.nextLine();
        
        while (!verificarFim(linha)) {
            System.out.println(cifra(linha));
            linha = sc.nextLine(); 
        }
        
        sc.close();
    }
}
