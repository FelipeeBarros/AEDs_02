public class Game {
    public Game prox;
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
        this.prox = null;
        this.id = -1;
        this.name = "";
        this.releaseDate = "";
        this.estimatedOwners = -1;
        this.price = 0;
        this.supportedLanguages = null;
        this.metacriticScore = -1;
        this.userScore = 0;
        this.achievements = -1;
        this.publishers = null;
        this.developers = null;
        this.categories = null;
        this.genres = null;
        this.tags = null;
    }

    public Game(Game prox, int id, String name, String releaseData, int estimatedOwners, float price,
            String[] supportedLanguages, int metacriticScore,
            float userScore, int achievements, String[] publishers, String[] developers, String[] categories,
            String[] genres, String[] tags) {
        this.prox = prox;
        this.id = -1;
        this.name = "";
        this.releaseDate = "";
        this.estimatedOwners = -1;
        this.price = 0;
        this.supportedLanguages = null;
        this.metacriticScore = -1;
        this.userScore = 0;
        this.achievements = -1;
        this.publishers = null;
        this.developers = null;
        this.categories = null;
        this.genres = null;
        this.tags = null;
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
    // Id
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    // Name
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    // Release date
    public String getReleaseDate() {
        return releaseDate;
    }

    public void setReleaseDate(String releaseDate) {
        this.releaseDate = releaseDate;
    }

    // Estimated Owners
    public int getEstimatedOwners() {
        return estimatedOwners;
    }

    public void setEstimatedOwners(int estimatedOwners) {
        this.estimatedOwners = estimatedOwners;
    }

    // Price
    public float getPrice() {
        return price;
    }

    public void setPrice(float price) {
        this.price = price;
    }

    // Supported languages
    public String[] getSupportedLanguages() {
        return supportedLanguages;
    }

    public void setSupportedLanguages(String[] supportedLanguages) {
        this.supportedLanguages = supportedLanguages;
    }

    // Metacritic score
    public int getMetacriticScore() {
        return metacriticScore;
    }

    public void setMetacriticScore(int metacriticScore) {
        this.metacriticScore = metacriticScore;
    }

    // User score
    public float getUserScore() {
        return userScore;
    }

    public void setUserScore(float userScore) {
        this.userScore = userScore;
    }

    // Achievments
    public int getAchievements() {
        return achievements;
    }

    public void setAchievements(int achievements) {
        this.achievements = achievements;
    }

    // Publishers
    public String[] getPublishers() {
        return publishers;
    }

    public void setPublishers(String[] publishers) {
        this.publishers = publishers;
    }

    // Developers
    public String[] getDevelopers() {
        return developers;
    }

    public void setDevelopers(String[] developers) {
        this.developers = developers;
    }

    // Categories
    public String[] getCategories() {
        return categories;
    }

    public void setCategories(String[] categories) {
        this.categories = categories;
    }

    // Genres
    public String[] getGenres() {
        return genres;
    }

    public void setGenres(String[] genres) {
        this.genres = genres;
    }

    // Tags
    public String[] getTags() {
        return tags;
    }

    public void setTags(String[] tags) {
        this.tags = tags;
    }

    // Função split
    public static String[] split(String linha, char separador) {
        if (linha == null || linha.length() == 0) {
            return new String[0];
        }

        int partes = 1;
        boolean colchete = false;
        boolean aspas = false;

        // Conta partes considerando colchetes E aspas
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

            // Controle de aspas
            if (c == '"' && !colchete) {
                aspas = !aspas;
            } // Controle de colchetes
            else if (c == '[' && !aspas) {
                colchete = true;
                subString[j++] = c;
            } else if (c == ']' && !aspas) {
                colchete = false;
                subString[j++] = c;
            } // Se for separador e nao estiver dentro de colchetes ou aspas
            else if (c == separador && !colchete && !aspas) {
                resultado[k++] = new String(subString, 0, j);
                j = 0;
            } else {
                subString[j++] = c;
            }
        }

        resultado[k] = new String(subString, 0, j);

        return resultado;
    }

    // Minha função trim
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

    // Caractere para inteiro
    public static int toInt(String string) {
        int result = 0;
        int sinal = 1;
        int i = 0;

        if (string.charAt(0) == '-') {
            sinal = -1;
            i = 1;
        }

        // Converte cada caractere
        for (int j = i; j < string.length(); j++) {
            char c = string.charAt(j);
            if (c >= '0' && c <= '9') {
                result = result * 10 + (c - '0');
            } else {
                // Caractere inválido, retorna -1
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

    // MMM dd, yyyy para dd/MM/yyyy
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

        int diaInt = toInt(dia);
        String diaFormatado = String.format("%02d", diaInt);

        String result = diaFormatado + "/" + mes + "/" + ano;

        return result;
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

        // Casos especiais
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

        string = trim(string);

        if (string.length() >= 2 && string.charAt(0) == '"' && string.charAt(string.length() - 1) == '"') {
            string = string.substring(1, string.length() - 1);
        }

        string = trim(string);

        if (string.length() >= 2 && string.charAt(0) == '[' && string.charAt(string.length() - 1) == ']') {
            string = string.substring(1, string.length() - 1);
        }

        string = trim(string);

        if (string.length() == 0) {
            return new String[0];
        }

        String[] partes = split(string, ',');

        for (int i = 0; i < partes.length; i++) {
            if (partes[i] == null) {
                partes[i] = "";
                continue;
            }
            String s = trim(partes[i]);
            if (s.length() >= 2 && s.charAt(0) == '\'' && s.charAt(s.length() - 1) == '\'') {
                s = s.substring(1, s.length() - 1);
            }
            if (s.length() >= 2 && s.charAt(0) == '"' && s.charAt(s.length() - 1) == '"') {
                s = s.substring(1, s.length() - 1);
            }
            s = s.replace("'", "");
            s = s.replace("\"", "");
            partes[i] = trim(s);
        }

        return trimArray(partes);
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
        System.out.print(" ##");
        System.out.println();
    }
}