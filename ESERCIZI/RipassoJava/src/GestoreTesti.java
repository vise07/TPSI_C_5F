public class GestoreTesti {
    public int[] contaVocaliConsonanti(String frase) {
        int vocali = 0, consonanti = 0;
        for (char c : frase.toCharArray()) {
            if (Character.isLetter(c)) {
                if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                    vocali++;
                } else {
                    consonanti++;
                }
            }
        }
        return new int[]{vocali, consonanti};
    }
}
