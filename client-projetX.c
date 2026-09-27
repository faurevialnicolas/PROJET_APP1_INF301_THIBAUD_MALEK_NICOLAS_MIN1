#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>


int main() {
    // Affiche les échanges avec le serveur (false pour désactiver)
    show_messages(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr");

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer("login 12505063 FAURE-VIAL");
    envoyer("load projetX");
    
    char reponse[MAXREP];
    
    envoyer_recevoir("help",reponse);
    
    int i=0;
    int key= 'C' - reponse[0];
    while (reponse[i]!='\0'){
    if (reponse[i] >= 'a' && reponse[i] <= 'z') {
        reponse[i] = 'a' + (reponse[i]- 'a' + key) % 26;
    } 
    else if (reponse[i] >= 'A' && reponse[i] <= 'Z') {
        reponse[i] = 'A' + (reponse[i] - 'A' + key) % 26;
    } 
    else {
        reponse[i] = reponse[i];
    }
    i++;
    }
    printf("reponse du serveur %s", reponse);
    printf ("Fin d'envoi des messages.\n");
    printf ("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}
