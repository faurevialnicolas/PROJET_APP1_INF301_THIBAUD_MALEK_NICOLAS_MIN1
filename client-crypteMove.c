#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

void deplacer_a_la_fin(char source[], char dest[]){
    int i=0;
    char x = source[0];
    while(dest[i]!='\0'){i++;}
    dest[i]=x;
    dest[i+1]='\0';

    int k =0;
    while(source[k]!='\0'){
        if(source[k+1]!='\0'){
            char tmp=source[k];
            source[k]=source[k+1];
            source[k+1]=tmp;
        }
        else{
            source[k]='\0';
        }
        k++;
    }
}
void mettre_a_la_fin_de_la_meme_chaine(char s[]){
    int k =0;
    while(s[k]!='\0'){
        if(s[k+1]!='\0'){
            char tmp=s[k];
            s[k]=s[k+1];
            s[k+1]=tmp;
        }
        k++;
    }
}
void crypte(char s[], char dest[]){
    while (s[0]!='\0'){
        char c=s[0];
        unsigned int x=c%8;
        deplacer_a_la_fin(s,dest);
        for(unsigned int i=0; i<x; i++){
            if(strlen(s)>=x){
            mettre_a_la_fin_de_la_meme_chaine(s);
            }
        }
    
    }
}
int main() {
    // Affiche les échanges avec le serveur (false pour désactiver)
    show_messages(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr");

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer("login 12505063 FAURE-VIAL");
    envoyer("load crypteMove");
    
    char TXT[MAXREP];
    char ENC[MAXREP];
    envoyer_recevoir("help",TXT);
    envoyer("start");
    crypte(TXT,ENC);
    envoyer(ENC);
    printf ("Fin d'envoi des messages.\n");
    printf ("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}
