import java.io.*;
import java.util.*;

public class Questao1 {

    static int comparacao = 0;
    static int movimentacao = 0;
    static long tempoInicio;

    // Ordenação com MergeSort
    public static void mergesort(Game[] array) {
        Game[] jogos = new Game[array.length];
        mergesortRec(array, jogos, 0, array.length - 1);
    }

    // Recursão do MergeSort
    private static void mergesortRec(Game[] array, Game[] jogos, int esq, int dir) {
        if (esq < dir) {
            int meio = (esq + dir) / 2;
            mergesortRec(array, jogos, esq, meio);
            mergesortRec(array, jogos, meio + 1, dir);
            intercalar(array, jogos, esq, meio, dir);
        }
    }

    // Intercala as partes
    private static void intercalar(Game[] array, Game[] jogos, int esq, int meio, int dir) {
        for (int i = esq; i <= dir; i++) {
            jogos[i] = array[i];
            movimentacao++;
        }

        int i = esq;
        int j = meio + 1;
        int k = esq;

        while (i <= meio && j <= dir) {
            if (compare(jogos[i], jogos[j]) <= 0) {
                array[k++] = jogos[i++];
                movimentacao++;
            } else {
                array[k++] = jogos[j++];
                movimentacao++;
            }
        }

        while (i <= meio) {
            array[k++] = jogos[i++];
            movimentacao++;
        }
    }

    // Compara por nome
    private static int compare(Game a, Game b) {
        comparacao++;
        return a.getName().compareTo(b.getName());
    }

    // Pesquisa binaria pelo nome
    private static boolean pesquisar(Game[] array, String nome) {
        int esq = 0;
        int dir = array.length - 1;

        while (esq <= dir) {
            int meio = (esq + dir) / 2;
            comparacao++;
            int comparacaoNome = nome.compareTo(array[meio].getName());

            if (comparacaoNome == 0) {
                return true;
            } else if (comparacaoNome < 0) {
                dir = meio - 1;
            } else {
                esq = meio + 1;
            }
        }

        return false;
    }

    private static void gerarLog(int compPesquisa) {
        try {
            PrintWriter writer = new PrintWriter("1526815_binaria.txt", "UTF-8");
            long tempoExecucao = System.currentTimeMillis() - tempoInicio;
            writer.println("1526815\t" + tempoExecucao + "\t" + compPesquisa);
            writer.close();
        } catch (FileNotFoundException | UnsupportedEncodingException e) {
            System.out.println("Erro ao criar arquivo de log: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        Celula primeiro = null;
        Celula ultimo = null;
        int n = 0;

        // Ler CSV e carregar na lista
        try {
            Scanner ler = new Scanner(new File("/tmp/games.csv"));
            //Scanner ler = new Scanner(new File("C:/Users/felip/OneDrive/Desktop/PUC-MINAS/CIENCIA_DA_COMPUTACAO/TERCEIRO_PERIODO/AEDS_II/TP05_FelipeBarros_1526815/games.csv"));
            if (ler.hasNextLine()) {
                ler.nextLine(); // Pular cabeçalho
            }

            while (ler.hasNextLine()) {
                String linha = ler.nextLine();
                Game game = new Game();
                game.ler(linha);

                Celula nova = new Celula(game);

                if (primeiro == null) {
                    primeiro = nova;
                    ultimo = nova;
                } else {
                    ultimo.prox = nova;
                    ultimo = nova;
                }
                n++;
            }
            ler.close();
        } catch (FileNotFoundException e) {
            System.out.println("Arquivo nao encontrado");
            return;
        }

        Scanner sc = new Scanner(System.in);
        List<Game> jogos = new ArrayList<>();

        // Ler IDs
        boolean ehFim = false;
        while (sc.hasNextLine() && !ehFim) {
            String linha = Game.trim(sc.nextLine());

            if (Game.equals(linha, "FIM")) {
                ehFim = true;
            } else {
                int id = Game.toInt(linha);
                boolean encontrado = false;
                Celula i = primeiro;
                while (i != null && !encontrado) {
                    if (i.game.getId() == id) {
                        jogos.add(i.game);
                        encontrado = true;
                    }
                    i = i.prox;
                }
            }
        }

        // Converter lista para array
        Game[] array = jogos.toArray(new Game[0]);

        // Ordenar com Mergesort
        tempoInicio = System.currentTimeMillis();
        mergesort(array);

        // Pesquisa binaria
        int compPesquisa = 0;
        ehFim = false; // Reutilizando a flag
        while (sc.hasNextLine() && !ehFim) {
            String nome = Game.trim(sc.nextLine());

            if (Game.equals(nome, "FIM")) {
                ehFim = true;
            } else {
                comparacao = 0;
                boolean encontrado = pesquisar(array, nome);
                compPesquisa += comparacao;

                if (encontrado) {
                    System.out.println(" SIM");
                } else {
                    System.out.println(" NAO");
                }
            }
        }

        sc.close();
        gerarLog(compPesquisa);
    }
}

class Game {

    private int id;
    private String name;
    private String releaseDate;
    private int estimatedOwners;
    private float price;
    private String[] supportedLanguages;
    private int metacriticScore;
    private float userScore;
    private int achievements;
    private String[] publishers;
    private String[] developers;
    private String[] categories;
    private String[] genres;
    private String[] tags;

    public Game() {
        this(-1, "", "", -1, 0, null, -1, 0, -1, null, null, null, null, null);
    }

    public Game(int id, String name, String releaseDate, int estimatedOwners, float price,
            String[] supportedLanguages, int metacriticScore, float userScore,
            int achievements, String[] publishers, String[] developers,
            String[] categories, String[] genres, String[] tags) {

        this.id = id;
        this.name = name;
        this.releaseDate = releaseDate;
        this.estimatedOwners = estimatedOwners;
        this.price = price;
        this.supportedLanguages = supportedLanguages;
        this.metacriticScore = metacriticScore;
        this.userScore = userScore;
        this.achievements = achievements;
        this.publishers = publishers;
        this.developers = developers;
        this.categories = categories;
        this.genres = genres;
        this.tags = tags;
    }

    public void ler(String linha) {
        String[] colunas = split(linha, ',');

        String[] colunasComp = new String[14];
        for (int i = 0; i < 14; i++) {
            if (i < colunas.length) {
                colunasComp[i] = colunas[i];
            } else {
                colunasComp[i] = "";
            }
        }

        this.id = toInt(trim(colunasComp[0]));
        this.name = trim(colunasComp[1]);
        this.releaseDate = toDate(trim(colunasComp[2]));
        this.estimatedOwners = toInt(trim(colunasComp[3]));
        this.price = toFloat(trim(colunasComp[4]));
        this.supportedLanguages = splitArray(colunasComp[5]);
        this.metacriticScore = toInt(trim(colunasComp[6]));
        this.userScore = toFloat(trim(colunasComp[7]));
        this.achievements = toInt(trim(colunasComp[8]));
        this.publishers = splitArray(colunasComp[9]);
        this.developers = splitArray(colunasComp[10]);
        this.categories = splitArray(colunasComp[11]);
        this.genres = splitArray(colunasComp[12]);
        this.tags = splitArray(colunasComp[13]);
    }

    // Gets e Sets
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getReleaseDate() {
        return releaseDate;
    }

    public void setReleaseDate(String releaseDate) {
        this.releaseDate = releaseDate;
    }

    public int getEstimatedOwners() {
        return estimatedOwners;
    }

    public void setEstimatedOwners(int estimatedOwners) {
        this.estimatedOwners = estimatedOwners;
    }

    public float getPrice() {
        return price;
    }

    public void setPrice(float price) {
        this.price = price;
    }

    public String[] getSupportedLanguages() {
        return supportedLanguages;
    }

    public void setSupportedLanguages(String[] supportedLanguages) {
        this.supportedLanguages = supportedLanguages;
    }

    public int getMetacriticScore() {
        return metacriticScore;
    }

    public void setMetacriticScore(int metacriticScore) {
        this.metacriticScore = metacriticScore;
    }

    public float getUserScore() {
        return userScore;
    }

    public void setUserScore(float userScore) {
        this.userScore = userScore;
    }

    public int getAchievements() {
        return achievements;
    }

    public void setAchievements(int achievements) {
        this.achievements = achievements;
    }

    public String[] getPublishers() {
        return publishers;
    }

public void setPublishers(String[] publishers) {
        this.publishers = publishers;
    }

    public String[] getDevelopers() {
        return developers;
    }

    public void setDevelopers(String[] developers) {
        this.developers = developers;
    }

    public String[] getCategories() {
        return categories;
    }

    public void setCategories(String[] categories) {
        this.categories = categories;
    }

    public String[] getGenres() {
        return genres;
    }

    public void setGenres(String[] genres) {
        this.genres = genres;
    }

    public String[] getTags() {
        return tags;
    }

    public void setTags(String[] tags) {
        this.tags = tags;
    }
    
    public void imprimir() {
        System.out.print("=> " + this.id + " ## " + this.name + " ## " + this.releaseDate + " ## ");
        System.out.print(this.estimatedOwners + " ## " + this.price + " ## ");
        imprimirArray(supportedLanguages);
        System.out.print(" ## " + this.metacriticScore + " ## " + this.userScore + " ## ");
        System.out.print(this.achievements + " ## ");
        imprimirArray(publishers);
        System.out.print(" ## ");
        imprimirArray(developers);
        System.out.print(" ## ");
        imprimirArray(categories);
        System.out.print(" ## ");
        imprimirArray(genres);
        System.out.print(" ## ");
        imprimirArray(tags);
        System.out.print(" ## ");
        System.out.println();
    }

    public static String[] split(String linha, char separador) {
        if (linha == null || linha.length() == 0) {
            return new String[0];
        }

        int partes = 1;
        boolean colchete = false;
        boolean aspas = false;

        for (int i = 0; i < linha.length(); i++) {
            char c = linha.charAt(i);

            if (c == '"' && !colchete) {
                aspas = !aspas;
            } else if (c == '[' && !aspas) {
                colchete = true;
            } else if (c == ']' && !aspas) {
                colchete = false;
            } else if (c == separador && !colchete && !aspas) {
                partes++;
            }
        }

        String[] resultado = new String[partes];
        char[] subString = new char[linha.length()];
        int j = 0;
        int k = 0;
        colchete = false;
        aspas = false;

        for (int i = 0; i < linha.length(); i++) {
            char c = linha.charAt(i);

            if (c == '"' && !colchete) {
                aspas = !aspas;
            } else if (c == '[' && !aspas) {
                colchete = true;
                subString[j++] = c;
            } else if (c == ']' && !aspas) {
                colchete = false;
                subString[j++] = c;
            } else if (c == separador && !colchete && !aspas) {
                resultado[k++] = new String(subString, 0, j);
                j = 0;
            } else {
                subString[j++] = c;
            }
        }

        resultado[k] = new String(subString, 0, j);
        return resultado;
    }

    public static String trim(String string) {
        if (string == null) {
            return "";
        }

        int start = 0;
        int end = string.length() - 1;

        while (start <= end && string.charAt(start) == ' ') {
            start++;
        }
        while (end >= start && string.charAt(end) == ' ') {
            end--;
        }

        if (start > end) {
            return "";
        }

        char[] subStr = new char[end - start + 1];
        for (int i = start; i <= end; i++) {
            subStr[i - start] = string.charAt(i);
        }
        return new String(subStr);
    }

    public static String[] trimArray(String[] string) {
        String[] result = new String[string.length];
        for (int i = 0; i < string.length; i++) {
            result[i] = trim(string[i]);
        }
        return result;
    }

    public static int toInt(String string) {
        if (string == null || string.length() == 0) {
            return -1;
        }

        int result = 0;
        int sinal = 1;
        int i = 0;

        if (string.charAt(0) == '-') {
            sinal = -1;
            i = 1;
        }

        for (int j = i; j < string.length(); j++) {
            char c = string.charAt(j);
            if (c >= '0' && c <= '9') {
                result = result * 10 + (c - '0');
            } else {
                return -1;
            }
        }

        return result * sinal;
    }

    public static String replace(String string, char sai, char entra) {
        if (string == null) {
            return "01";
        }

        char[] subStr = new char[string.length()];

        for (int i = 0; i < string.length(); i++) {
            if (string.charAt(i) == sai) {
                subStr[i] = entra;
            } else {
                subStr[i] = string.charAt(i);
            }
        }

        return new String(subStr);
    }

    public static String toDate(String string) {
        if (string == null) {
            return "01/01/2025";
        }

        String[] data = split(string, ' ');

        if (data.length < 3) {
            for (int i = 0; i < data.length; i++) {
                String parte = trim(data[i]);
                int ano = toInt(parte);
                if (ano >= 1970 && ano <= 2030) {
                    return "01/01/" + ano;
                }
            }
            return "01/01/2025";
        }

        String mes = trim(data[0]);
        String dia = trim(replace(data[1], ',', ' '));
        String ano = trim(data[2]);

        switch (mes) {
            case "Jan":
                mes = "01";
                break;
            case "Feb":
                mes = "02";
                break;
            case "Mar":
                mes = "03";
                break;
            case "Apr":
                mes = "04";
                break;
            case "May":
                mes = "05";
                break;
            case "Jun":
                mes = "06";
                break;
            case "Jul":
                mes = "07";
                break;
            case "Aug":
                mes = "08";
                break;
            case "Sep":
                mes = "09";
                break;
            case "Oct":
                mes = "10";
                break;
            case "Nov":
                mes = "11";
                break;
            case "Dec":
                mes = "12";
                break;
            default:
                mes = "01";
        }

        return dia + '/' + mes + '/' + ano;
    }

    public static boolean equals(String str1, String str2) {
        int i = 0;
        while (i < str1.length() && i < str2.length()) {
            if (str1.charAt(i) != str2.charAt(i)) {
                return false;
            }
            i++;
        }
        return (i == str1.length() && i == str2.length());
    }

    public static float toFloat(String string) {
        if (string == null) {
            return -1.0f;
        }

        if (equals(string, "Free to Play")) {
            return 0.0f;
        }
        if (equals(string, "tbd")) {
            return -1.0f;
        }

        float inteiro = 0.0f;
        float decimal = 0.0f;
        int sinal = 1;
        boolean ponto = false;
        int casas = 1;

        for (int i = 0; i < string.length(); i++) {
            char c = string.charAt(i);

            if (c == '-') {
                sinal = -1;
            } else if (c == '.') {
                ponto = true;
            } else if (c >= '0' && c <= '9') {
                if (!ponto) {
                    inteiro = inteiro * 10 + (c - '0');
                } else {
                    decimal = decimal * 10 + (c - '0');
                    casas *= 10;
                }
            }
        }

        return (inteiro + (decimal / casas)) * sinal;
    }

    public static String[] splitArray(String string) {
        if (string == null) {
            return new String[0];
        }

        int start = 0;
        int end = string.length();

        if ((string.length() >= 2) && (string.charAt(0) == '[') && (string.charAt(string.length() - 1) == ']')) {
            start = 1;
            end = string.length() - 1;
        }

        char[] subStr = new char[end - start];
        for (int i = start; i < end; i++) {
            subStr[i - start] = string.charAt(i);
        }

        String str = new String(subStr);
        str = trim(str);

        String[] partes = split(str, ',');
        String[] resultado = trimArray(partes);

        for (int i = 0; i < resultado.length; i++) {
            resultado[i] = resultado[i].replace("'", "");
        }

        return resultado;
    }

    public static void imprimirArray(String[] array) {
        if (array == null || array.length == 0) {
            System.out.print("[]");
            return;
        }

        System.out.print("[");
        for (int i = 0; i < array.length; i++) {
            System.out.print(array[i]);
            if (i < array.length - 1) {
                System.out.print(", ");
            }
        }
        System.out.print("]");
    }
}

class Celula {

    public Game game;
    public Celula prox;

    public Celula() {
        this.game = null;
        this.prox = null;
    }

    public Celula(Game game) {
        this.game = game;
        this.prox = null;
    }

    public Celula(Game game, Celula prox) {
        this.game = game;
        this.prox = prox;
    }
}