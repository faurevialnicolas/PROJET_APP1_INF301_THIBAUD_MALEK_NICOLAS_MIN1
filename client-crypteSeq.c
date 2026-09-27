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

void decrypte(char ENC[], char TXT[]){
    int lenc = strlen(ENC);
    int ltxt= 0;
    for(int i= lenc -1; i>=0; i--){
        char c =ENC[i];
        int x = c %8;

        if (x<= ltxt){
            char tmp[MAXREP];
            int k=0;
            for (int j = ltxt - x;j<ltxt; j++){
                tmp[k++]= TXT[j];
            }
            for(int j =0; j< ltxt-x; j++){
                tmp[k++]=TXT[j];
            }
            tmp[k]='\0';
            strcpy(TXT,tmp);
        }
        for (int j = ltxt; j>=0;j--){
            TXT[j+1]= TXT[j];
        }
        TXT[0]= c;
        ltxt++;
    }
}

int trouver_caractere(char seq[], char c) {
    for (int i = 0; seq[i] != '\0'; i++) {
        if (seq[i] == c) {
            return i;
        }
    }
    return -1;
}

void crypte_seq(char input[], char output[]) {
    char seq[MAXREP] = ""; 
    int seq_len = 0;
    int out_idx = 0;

    for (int i = 0; input[i] !='\0'; i++) {
        char c = input[i];
        int idx = trouver_caractere(seq, c);

        if (idx ==-1) {
            seq[seq_len++]= c;
            seq[seq_len]='\0';
            output[out_idx++]=c;
        } else {
            char d;
            if (idx==0) {
                d = seq[seq_len-1];
            } else {
                d = seq[idx-1];
            }
            output[out_idx++] = d;

            for (int j=idx; j<seq_len-1; j++) {
                seq[j] = seq[j+1];
            }
            seq[seq_len-1] = c;
        }
    }
    output[out_idx] = '\0';
}

void decrypte_seq(char input[], char output[]) {
    char *ptr = input;
    
    int newlines = 0;
    while (*ptr != '\0') {
        if (*ptr == '\n') {
            newlines++;
            if (newlines == 2) {
                ptr++;
                break;
            }
        }
        ptr++;
    }
    if (newlines < 2) {
        ptr = input;
    }
    char seq[MAXREP] = ""; 
    int seq_len = 0;
    int out_idx = 0;

    for (int i = 0; ptr[i] != '\0'; i++) {
        char val = ptr[i];
        int d_idx = trouver_caractere(seq, val);

        if (d_idx == -1) {
            seq[seq_len++] = val;
            seq[seq_len] = '\0';
            output[out_idx++] = val;
        } else {
            int c_idx;
            if (d_idx == seq_len - 1) {
                c_idx = 0;
            } else {
                c_idx = d_idx + 1;
            }
            char c = seq[c_idx];
            output[out_idx++] = c;

            for (int j = c_idx; j < seq_len - 1; j++) {
                seq[j] = seq[j + 1];
            }
            seq[seq_len - 1] = c;
        }
    }
    output[out_idx] = '\0';
}
void enlever_deux_premieres_lignes(char str[]) {
    int newlines = 0;
    int idx = -1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            newlines++;
            if (newlines == 2) {
                idx = i + 1;
                break;
            }
        }
    }
    if (idx != -1) {
        int i = 0;
        while (str[idx] != '\0') {
            str[i++] = str[idx++];
        }
        str[i] = '\0';
    } else {
        str[0] = '\0';
    }
}
int main() {
    // Affiche les échanges avec le serveur (false pour désactiver)
    show_messages(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr");

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer("login 12505063 FAURE-VIAL");
    envoyer("load crypteSeq");
    
    char TXT[MAXREP];
    char ENC[MAXREP];
    char code[MAXREP];
    char pom[MAXREP];
    char debug[MAXREP];
    char rep[MAXREP];
    char gplusdenom[MAXREP];
    envoyer_recevoir("start",TXT);
    decrypte(TXT,ENC);
    printf("%s", ENC);
    crypte_seq(ENC,code);
    envoyer_recevoir(code,pom);
    decrypte_seq(pom,gplusdenom);
    decrypte(pom,debug);
    printf("%s",debug);
    crypte_seq(pom,rep);
    envoyer(rep);
    enlever_deux_premieres_lignes(gplusdenom);
    printf("%s",gplusdenom);
    printf ("Fin d'envoi des messages.\n");
    printf ("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}
