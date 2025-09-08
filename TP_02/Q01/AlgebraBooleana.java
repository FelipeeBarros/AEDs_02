import java.util.Scanner;

public class AlgebraBooleana {

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        String[] entrada = new String[1000];
        int qtd = 0;
        while(sc.hasNextLine()){
            entrada[qtd++] = sc.nextLine();
        }

        for(int idx = 0; idx < qtd; idx++){
            String linha = entrada[idx];
            if(linha.charAt(0) == '0') break;

            int nVar = linha.charAt(0) - '0';
            int[] vals = capturaValores(linha, nVar);

            int posExpr = 2;
            for(int i = 0; i < nVar; i++){
                while(linha.charAt(posExpr) == ' ') posExpr++;
                posExpr++;
            }

            String expr = substituir(linha, vals, posExpr);

            while(expr.length() > 1){
                int[] sub = localizarSubExpr(expr);
                if(sub[0] == 0 && sub[1] == 0) break;

                int res = calcularSubExpr(expr, sub[0], sub[1]);
                expr = reinserirResultado(expr, sub[0], sub[1], res);
            }

            if(expr.length() > 0 && expr.charAt(0) == '1'){
                System.out.println(1);
            } else {
                System.out.println(0);
            }
        }
    }

    /**
     * Calcula o valor da subexpressão encontrada entre ps e pe
     */
    public static int calcularSubExpr(String expr, int ps, int pe){
        char op = expr.charAt(ps - 1);
        int resultado = (op == 'd') ? 1 : 0;

        int i = ps + 1;
        while(i < pe){
            char c = expr.charAt(i);
            if(c == '0' || c == '1'){
                int val = c - '0';
                if(op == 'r') resultado = disj(resultado, val);
                else if(op == 'd') resultado = conj(resultado, val);
            }
            i++;
        }

        if(op == 't') resultado = neg(expr.charAt(ps + 1) - '0');

        return resultado;
    }

    /**
     * Substitui a subexpressão pelo resultado
     */
    public static String reinserirResultado(String expr, int ps, int pe, int res){
        int inicio = (expr.charAt(ps - 1) == 'r') ? ps - 2 : ps - 3;
        String nova = "";
        for(int i = 0; i < inicio; i++){
            nova += expr.charAt(i);
        }
        nova += intParaChar(res);
        for(int i = pe + 1; i < expr.length(); i++){
            nova += expr.charAt(i);
        }
        return nova;
    }

    /**
     * Localiza a última subexpressão entre parênteses
     */
    public static int[] localizarSubExpr(String expr){
        int[] pos = new int[2];
        for(int i = 0; i < expr.length(); i++){
            if(expr.charAt(i) == ')'){
                pos[1] = i;
                int j = i;
                while(expr.charAt(j) != '(') j--;
                pos[0] = j;
                break;
            }
        }
        return pos;
    }

    /**
     * Substitui variáveis pelos seus valores
     */
    public static String substituir(String linha, int[] vals, int posInicio){
        String resultado = "";
        for(int i = posInicio; i < linha.length(); i++){
            char c = linha.charAt(i);
            if(c != ' '){
                if(c >= 'A' && c <= 'Z') resultado += vals[c - 'A'];
                else resultado += c;
            }
        }
        return resultado;
    }

    /**
     * Captura os valores das variáveis da linha de entrada
     */
    public static int[] capturaValores(String linha, int nVar){
        int[] var = new int[nVar];
        int p = 2;
        for(int i = 0; i < nVar; i++){
            while(linha.charAt(p) == ' ') p++;
            var[i] = linha.charAt(p) - '0';
            p++;
        }
        return var;
    }

    /**
     * Operação OR entre dois valores
     */
    public static int disj(int x, int y){
        return (x != 0 || y != 0) ? 1 : 0;
    }

    /**
     * Operação AND entre dois valores
     */
    public static int conj(int x, int y){
        return (x != 0 && y != 0) ? 1 : 0;
    }

    /**
     * Operação NOT
     */
    public static int neg(int x){
        return x ^ 1;
    }

    /**
     * Converte inteiro em caractere
     */
    public static char intParaChar(int x){
        return (x == 1) ? '1' : '0';
    }
}
