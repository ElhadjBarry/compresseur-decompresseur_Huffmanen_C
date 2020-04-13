#include"conversions.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
 * \file conversions.c
 * \author Barry Elhadj
 * \brief fonctions servant a la manipulation des données lors de la décompression.
 */


/**
 * \fn char* ctob(int a)
 * \brief renvoie la conversion en  binaire                  
 * dans une chaine de caractére du caractère passé en paramétre
 * avec Vi C s[0..n] -->s[i]={0,1} ;s étant la chaine renvoyée en résultat.
 * \param a le code ASCII du caractére a convertir.
 * \return  code binaire de la valeur passé en paramétre.
 */


char*  ctob(int a) {
  char *s=(char *)malloc(9*sizeof(char));
  int i=7;
  s[8]='\0';
  while( i >= 0) {
    if(a%2 == 0)
      s[i]='0';
    else
      s[i]='1';
    i--;
    a/=2;
  }
  return s;} 

/**
 * \fn btoi(const char* s)
 * \brief revoie la conversions de 4 octets représntés dans une chaîne de caractères s en un entier.
 * \param s chaine de 32 caractéres. 
 * \return  l'entier correspondant.
 */



int btoi(const char* s){ int t =0;
  for(int i=0;i<=31;i++){
    if (s[i]=='0') t=t*2+ 0;
      else if (s[i]=='1') t=t*2+1;}
  return t; } 


/**
 * \fn buffeur(int j,int c,FILE* f)
 * \brief renvoie j octets représentés dans une chaine de carctères a partir de la position de c dans le fichier f.		     
 * \param j nombre d'octets a  récupérer.
 * \param c carctére courant dans le fichier.
 * \param f fichier courant.
 * \return nombre demandé d'octet dans une chaine de caractères.
 */



char* buffeur(int j,int c,FILE* f){int i=0;
  char* s=(char* )malloc(j*8*sizeof(char));
  while(i < j ) {
    c=fgetc(f);
    s = strcat(s,ctob(c));
    i++;
  } 

  return s;
}   


/**
 * \fn decalage(char* s,int i)
 * \brief effectue un décalage de gauche à droite de i caractères.
 * \param s la chaine sur laquelle le décalage sera fait.
 * \param i nombre de positions du quel chaque caractère sera décalé.
 * \return la chaine après le décalage.
 */


void decalage (char* s,int i){
  int l=0;
  
  
  for(int x=i;x<8;x++){
    s[l]=s[x];
      s[x]='*';
    l++;}
}


