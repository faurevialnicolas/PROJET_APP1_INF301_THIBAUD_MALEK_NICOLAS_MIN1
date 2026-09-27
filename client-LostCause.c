#include "client.h"
#include <stdio.h>
#include <string.h>

// Déchiffrement de CrypteSeq
void decrypter_crypte_seq(const char *enc, char *dest) {
    char seq[MAXREP] = "";
    int seq_len = 0;
    int dest_len = 0;

    for (int i = 0; enc[i] != '\0'; i++) {
        char e = enc[i];
        int pos = -1;

        for (int j = 0; j < seq_len; j++) {
            if (seq[j] == e) {
                pos = j;
                break;
            }
        }

        if (pos == -1) {
            seq[seq_len++] = e;
            seq[seq_len] = '\0';
            dest[dest_len++] = e;
        } else {
            int pos_c = (pos + 1) % seq_len;
            char c = seq[pos_c];
            dest[dest_len++] = c;

            for (int j = pos_c; j < seq_len - 1; j++) {
                seq[j] = seq[j + 1];
            }
            seq[seq_len - 1] = c;
        }
    }
    dest[dest_len] = '\0';
}


// Déchiffrement de CrypteAssoc 
void decrypter_crypte_assoc(const char *enc, char *dest) {
    char seq[MAXREP] = "";
    char assoc[MAXREP] = "";
    int seq_len = 0;
    int dest_len = 0;

    for (int i = 0; enc[i] != '\0'; i++) {
        char e = enc[i];
        int k = -1;

        // Chercher e dans la table des associations
        for (int j = 0; j < seq_len; j++) {
            if (assoc[j] == e) {
                k = j;
                break;
            }
        }

        if (k == -1) {
            // Première rencontre : le caractère est associé à lui-même
            seq[seq_len] = e;
            assoc[seq_len] = e;
            seq_len++;
            seq[seq_len] = '\0';
            assoc[seq_len] = '\0';

            dest[dest_len++] = e;
        } else {
            // k est l'indice du prédécesseur (pos_pred). 
            // Le pos d'origine est donc (k + 1) % seq_len.
            int pos = (k + 1) % seq_len;
            char original = seq[pos];
            dest[dest_len++] = original;

            int pos_pred = k;

            // Inverser l'échange effectué lors du chiffrement
            char temp = assoc[pos];
            assoc[pos] = assoc[pos_pred];
            assoc[pos_pred] = temp;

            // Déplacer l'élément à la fin de la séquence et des associations
            char saved_c = seq[pos];
            char saved_assoc = assoc[pos];

            for (int j = pos; j < seq_len - 1; j++) {
                seq[j] = seq[j + 1];
                assoc[j] = assoc[j + 1];
            }
            seq[seq_len - 1] = saved_c;
            assoc[seq_len - 1] = saved_assoc;
        }
    }
    dest[dest_len] = '\0';
}

int main() {
    char reponse[MAXREP];
    char message[MAXREP];

    show_messages(true);

    connexion("im2ag-appolab.u-ga.fr");

    envoyer_recevoir("login 12505063 FAURE-VIAL", reponse);
    envoyer_recevoir("load LostCause", reponse);

    // 1. Demande de l'aide 
    envoyer_recevoir("aide", reponse);
    decrypter_crypte_seq(reponse, message);
    printf("\nAide:\n%s\n", message);

    // 2. Démarrage de l'exercice 
    envoyer_recevoir("depart", reponse);
    decrypter_crypte_assoc(reponse, message);
    printf("Message:\n%s\n", message);

    // 3. Envoi d'un message "tout va bien"
    envoyer_recevoir("tout va bien", reponse);

    

    printf ("Fin d'envoi des messages.\n");
    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}