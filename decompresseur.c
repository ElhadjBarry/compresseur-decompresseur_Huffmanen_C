#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"conversions.h"


int main(int argc,char* argv[]){


 

  
  FILE* f=fopen(argv[1],"r");

if (f == NULL){printf("probéme de lecture");}      





// TODO 2:déclaration des variables globales 
 



 
 
 int c;
 int traitement_1=0,traitement_2=0;
 char *lecture=malloc(8*sizeof(char));
 char *buf=malloc(8*sizeof(char));
 int car_vide_lecture=8;
 int car_vide_buf=8;
 int taille_fichier=-1,nbr_car_fichier=-1;
 int car_lu=0;
 int nbnoeud=0;
 int pr[502];
 int  fg[502];
 int  fd[502];
 char car[256];
 


 
/**
 * \TODO 3: recuperation de taille_f et nbr_car_fichier :
 * la taille du fichier est sur codé sur 1 octet
 * et le nombre de carcatère différents dans le fichier est sur 4 octets
 */

  //-------------------------------------3----------------------------------

 
 
 char *taille_b=malloc(32*sizeof(char));
 char *nbr_car_b=malloc(8*sizeof(char)); 
 
     
		  
 taille_b=buffeur(2,c,f);
 printf("cc je suis la\n");
 taille_fichier=btoi(taille_b);
 nbr_car_b=buffeur(1,c,f);
 nbr_car_fichier=btoi(nbr_car_b);
 free(taille_b);
 free(nbr_car_b);     
 printf("taille de fichier %i\n",taille_fichier); 
 printf("nombre de caractéres diff %i\n",nbr_car_fichier);
 
 
/**
 * \TODO 4:décodage du tableau d'occurence 
 * et création du tableau proba[] 
 */
 
 //-------------------------------------4----------------------------------
 
 nbnoeud=(nbr_car_fichier*2)-1;
 float proba[nbnoeud];


 char* occ=malloc(32*sizeof(char));

 for(int i=0;i<nbr_car_fichier;i++)
  { c=fgetc(f);
    car[i]=c;
    strcpy(occ,buffeur(4,c,f));
    printf("nbr_occ = %i ",btoi(occ)); 
    proba[i]=(float)btoi(occ)/taille_fichier;
    printf("car[%i]= %c  proba[%i]=%f \n",i,car[i],i,proba[i]);}


/**
 * \TODO 5: Reconstitution de l'arbre
 * avec le même algorithme vu en TD
 */

 //-------------------------------------5----------------------------------
 
 for(int i=0;i<nbnoeud;i++) {pr[i]= -1;fg[i]= -1;fd[i]= -1;}

 for(int nvn=nbr_car_fichier;nvn<nbnoeud;nvn++)
  { int s=-1,r=-1;
  for(int n=0;n<nvn;n++)
    {if(pr[n] == -1 )
	{ if( s == -1 ) {s=n;}
	  else if( r == -1 ) {r=n;}
	  else if (proba[n]<proba[s]){r=s;s=n;}
	  else if (proba[n]<proba[r]) r=n;}}
 pr[s]=nvn;
 pr[r]=nvn;
 fg[nvn]=s;
 fd[nvn]=r;
 proba[nvn]=proba[s]+proba[r];
 printf("%i      %i      %i    %i      %f \n",nvn,pr[nvn],fg[nvn],fd[nvn],proba[nvn]);}
  
 
 /**
 * \TODO 6: Reconstitution du contenue du fichier d'origine
 */

  //-------------------------------------6----------------------------------

 
 
 while(  car_lu != taille_fichier ){

  if (car_vide_lecture == 8)
    { lecture=buffeur(1,c,f);// printf("%s \n",lecture);
      if ( lecture != "********") car_vide_lecture=0;
    else if (lecture == NULL){printf("fichier incorrect\n");
      return -1;}}

  int compteur_lecture=0,compteur_buf=8-car_vide_buf;

 while ( (compteur_buf != 8) && (car_vide_lecture!=8) )
  {buf[compteur_buf] = lecture[compteur_lecture];
  compteur_buf++;
  lecture[compteur_lecture]='*';
  compteur_lecture++;
  car_vide_lecture++;
  car_vide_buf--;}
 
 if ((compteur_lecture != 0) && (compteur_lecture != 8) ) decalage(lecture,compteur_lecture);
 int i=0,k=nbnoeud-1;
 while ( (fd[k] != -1) && (fg[k] != -1) ) 
   { if(buf[i]== '1'){k=fd[k]; i++; car_vide_buf++;}
     else if (buf[i]== '0'){k=fg[k]; i++; car_vide_buf++;}}

 printf("%c",car[k]);
 car_lu++;
 if (i != 0 && i != 8) decalage(buf,i);}

 printf("\n");
  
 return 0;}

		    
		  


              	  	  

	 
              
