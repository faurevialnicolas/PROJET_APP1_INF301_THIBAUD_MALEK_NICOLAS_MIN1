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
    envoyer("load planB");
    char reponse[MAXREP];
    envoyer_recevoir("help",reponse);
    int cle = -'C' + reponse[0];
    char message[20]="hasta la revolucion";
    int i =0;
    while (message[i]!='\0'){
        if ('a'<=message[i] && 'z'>=message[i]){
            message[i]=message[i]- cle;
            if (message[i]<'a'){
                message[i]+=26;
            }
            if (message[i]>'z'){
                message[i]-=26;
            }
        }
        i++;
    }
    envoyer("depart");
    envoyer(message);
    
  
    
    
   
    printf ("Fin d'envoi des messages.\n");
    printf ("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}
