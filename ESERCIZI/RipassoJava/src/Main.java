import java.util.Scanner;
import static utility.Tools.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String[] opzioni = {"MENU", "Inserisci nuova frase", "Mostra lunghezza della frase", "Verifica presenza parola", "Sostituisci parola", "Conta vocali e consonanti", "Inverti frase", "Estrai porzione di frase", "Esci"};
        String frase = "";
        boolean continua = true;
        int scelta;

        do {

            try {

                switch (scelta = Menu(opzioni, sc)) {

                    case 1 -> {
                        System.out.print("Inserisci una nuova frase: ");
                        frase = sc.nextLine();
                        System.out.println("Frase aggiornata!");
                    }

                    case 2 -> {
                        if (!frase.isEmpty()) {
                            System.out.println("Lunghezza frase: " + frase.length());
                        } else {
                            System.out.println("Nessuna frase inserita.");
                        }
                    }

                    case 3 -> {
                        if (!frase.isEmpty()) {
                            System.out.print("Inserisci la parola da cercare: ");
                            String parola = sc.nextLine();

                            boolean trovata = frase.toLowerCase().contains(parola.toLowerCase());
                            if(trovata) {
                                System.out.println("Parola trovata.");
                            } else {
                                System.out.println("Parola non trovata.");
                            }

                            // Versione più breve dell if
                            // System.out.println(trovata ? "Parola trovata." : "Parola non trovata.");

                        } else {
                            System.out.println("Nessuna frase inserita.");
                        }
                    }

                    case 4 -> {
                        if (!frase.isEmpty()) {
                            System.out.print("Inserisci la parola da sostituire: ");
                            String daSostituire = sc.nextLine();

                            System.out.print("Inserisci la nuova parola: ");
                            String nuova = sc.nextLine();

                            frase = frase.replaceAll(daSostituire, nuova);
                            System.out.println("Parola sostituita.");

                        } else {
                            System.out.println("Nessuna frase inserita.");
                        }
                    }

                    case 5 -> {
                        if (!frase.isEmpty()) {
                            int vocali = 0, consonanti = 0;
                            String fraseMinuscola = frase.toLowerCase();

                            for (char c : fraseMinuscola.toCharArray()) {
                                if (Character.isLetter(c)) {
                                    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                                        vocali++;
                                    } else {
                                        consonanti++;
                                    }
                                }
                            }

                            System.out.println("Numero vocali: " + vocali);
                            System.out.println("Numero consonanti: " + consonanti);
                        } else {
                            System.out.println("Nessuna frase inserita.");
                        }
                    }

                    case 6 -> {
                        if (!frase.isEmpty()) {
                            String invertita = new StringBuilder(frase).reverse().toString();
                            System.out.println("Frase invertita: " + invertita);
                        } else {
                            System.out.println("Nessuna frase inserita.");
                        }
                    }

                    case 7 -> {
                        if (!frase.isEmpty()) {
                            try {
                                System.out.print("Inserisci indice iniziale: ");
                                int inizio = Integer.parseInt(sc.nextLine());

                                System.out.print("Inserisci indice finale: ");
                                int fine = Integer.parseInt(sc.nextLine());

                                if (inizio >= 0 && fine <= frase.length() && inizio < fine) {
                                    String porzione = frase.substring(inizio, fine);
                                    System.out.println("Porzione estratta: " + porzione);
                                } else {
                                    System.out.println("Indici non validi.");
                                }
                            } catch (Exception e) {
                                System.out.println("Errore durante l'estrazione della sottostringa.");
                            }
                        } else {
                            System.out.println("Nessuna frase inserita.");
                        }
                    }

                    case 8 -> {
                        continua = false;
                        System.out.println("Uscita dal programma...");
                    }
                }
            } catch (Exception e) {
                System.out.println("Errore, input non valido.");
            }

        } while (continua);

        System.out.println("Fine programma.");

        sc.close();
    }
}
