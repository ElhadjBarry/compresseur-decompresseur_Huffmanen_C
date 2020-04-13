#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"conversions.h"
#include<math.h> //pour le pow(²) et -lm à la fin de la compilation pour le lien 

float F [256];
int nbrdif=0;
int cpt=0;
 int calculfrequence(char* test){
   for(int i=0;i<256;i++){F[i]=0;}
   int cp=0;
      
   char buffer[2];
  FILE* fd=fopen(test,"r");
    if(fd){
      while(fread(buffer,1,1,fd)){
	F[(unsigned char)buffer[0]]++;
	printf("%c\n",buffer[0]);
	cp=cp+1;
      } printf("nbr char= %i\n",cp);  //le nombre totale de char 

   
      if(cp==0){
	  printf("le fichier est vide\n");  // tester si le fichier est vide
	  return 0;}

      
    }
    else{
      printf("le fichier n'existe pas \n"); //tester si le fichier n'xiste pas 
	return -1;
	}
     
  
    for(int i=0;i<256;i++){
      F[i]=F[i]/cp;
      if(F[i]!=0){
	nbrdif++;
	printf("la frequence de %i %c est %f\n",i, i, F[i]);}
     
      
    }
    cpt=cp;
    printf("le nbr de char dif =%i\n",nbrdif);

    return 1;

    
 }

typedef struct noeud{
  int pere;
  int fg;int fd;
  float freq;
}noeud;

noeud arbre[511];

 int cp=256;
void affiche(){
  for(int j=0;j<511;j++){
    arbre[j].pere=-1;
  arbre[j].fg=-1;
  arbre[j].fd=-1;
  arbre[j].freq=0;
  }
  for(int i=0;i<256;i++){
    if(F[i]!=0){
      arbre[i].freq=F[i];
    }
     if(arbre[i].freq!=0){
   printf("je suis la %f\n",(arbre[i].freq));
    }
  }
  printf("je suis apres la la \n");
   if(nbrdif>1){  //le cas ou on a un seul char dans le fichier
     //Recherche des deux elements de l'arbre dont les frequences, les frequences sont minimals 
     //qui n'ont pas de pere et creer un nouveau pere 

  int imin1;float fmin1=1;int imin2;float fmin2=1;
   
  do{
    imin1 = -1; fmin1=1; imin2 = -1; fmin2=1;
    
    for(int i=0;i<511;i++){
      if((arbre[i].freq<fmin1) && (arbre[i].freq!=0 && arbre[i].pere ==-1)){
		imin1=i;
		fmin1 = arbre[i].freq;
	}
     }
    for(int i=0;i<511;i++){
	if((arbre[i].freq<fmin2 && arbre[i].pere ==-1) && (imin1!=i) && (arbre[i].freq!=0))
	{
		imin2=i;
		fmin2 = arbre[i].freq;
	}
    }
    if (imin1 != -1 && imin2 != -1) {
      arbre[cp].freq=arbre[imin1].freq+arbre[imin2].freq ;
      arbre[imin1].pere=cp;    arbre[imin2].pere=cp;
      arbre[cp].fg=imin1;
      arbre[cp].fd=imin2;
      printf("cc %i\n",imin2);
      cp++;
    }
    
  } while(arbre[cp-1].freq!=1);
    } 
  for(int k=0;k<511;k++){
    if(arbre[k].freq>0){printf("salut barry la frequence a l'indice %i est %f\n",k,arbre[k].freq);}
  }
  
}

char* codes[256];


void parcours(int i,char *code){
  
  if(arbre[i].fg!=-1){
    char* morceauxg=(char*)malloc((strlen(code)+1)*sizeof(char));
    char* morceauxd=(char*)malloc((strlen(code)+1)*sizeof(char));
    
    for(int j=0;j<strlen(code);j++){
      morceauxg[j]=code[j];
      morceauxd[j]=code[j];
    }
      morceauxd[strlen(code)]='0';
      morceauxd[strlen(code)+1]='\0';
      morceauxg[strlen(code)]='1';
      morceauxg[strlen(code)+1]='\0';
      parcours(arbre[i].fg,morceauxd);
      parcours(arbre[i].fd,morceauxg); 
  }
  else{

    
    if(nbrdif==1){
      int x=0;
	while ((x<256) && (F[x]==0)) {
          
	    x++;}
      
      char* morceaux=(char*)malloc((2)*sizeof(char));
    morceaux[0]='1';
    morceaux[1]='\0';
      codes[x]=(char*)malloc((2)*sizeof(char));
      strcpy(codes[x],morceaux);
     
 printf("%c : %s\n", x, morceaux);

    }

    
  else{
     // Allouer la mémoire pour cette chaine dans codes
    codes[i]=(char*)malloc((strlen(code)+1)*sizeof(char));
    strcpy(codes[i],code); // Recopier code dans codes
   
    printf("%c : %s\n", i, code);
   }
  }
}




char buffer[263];

void creat_file(char *test){
   for(int z=0;z<263;z++){buffer[z]=0;}
  int i=0;
  FILE* fichier=NULL;
  char *Test=malloc(sizeof(char)*strlen(test)+5);
  strcpy(Test,test);
  for(i=0;test[i]!='.';i++){printf("%c",test[i]);}
  Test[i]=0;
  strcat(Test,".hcf");
  fichier=fopen(Test,"w");
  printf("\n je suis");
  

    
  
      

   if(fichier!=NULL){
     printf("le fichier compresser est tres bien creer\n");
     int nbrchar=0;
     fprintf(fichier,"%i%c",cpt,nbrdif);
             for(int j=0;j<256;j++){
	       if(F[j]!=0){
		 // nbrchar=F[j]*cpt;
		 fprintf(fichier,"%c",j);
		for(int x=0;x<strlen(codes[j]);x++){
		  nbrchar++;
		  
		}
		fprintf(fichier,"%i%s",nbrchar,codes[j]);
	       }
	       nbrchar=0;
	     }
	       
   }else{printf("le fichier compresser n'est pas bien construit \n");}
  
  
  
   
   char buff[2];
   FILE* fd=fopen(test,"r+");
   if(fd){
     printf("le fichier est tres bien ouvert\n");
    int j=0;
    int i=0;
     while(fread(buff,1,1,fd))
       {
	 printf("je lit les char\n");
	 strcat(buffer,codes[(unsigned char)buff[0]]);
	 printf("normalement ok pour strcat \n");
	 if(strlen(buffer)>7)
	   {
	     i=0; 
	     j=0; 
	     while(i<8)
	       {
		 if(buffer[i]=='1'){j=j+pow(2,7-i);}
		 i++;
	       }
	     printf("%c : %i",(unsigned char)j, (unsigned char)j);
	     fprintf(fichier,"%c",(unsigned char)j);
	     for(int k=0;k<256;k++){
	       buffer[k]=buffer[k+8];
             }
	      
	   }

	 
	 
       }

     
     i=0;
     j=0;
     printf("je lit le dernier char\n");
       while(i<8)
	       {
		 if(buffer[i]=='1'){j=j+pow(2,7-i);}
		 i++;
	       }  
	     printf("%c : %i\n",(unsigned char)j, (unsigned char)j);
        	     fprintf(fichier,"%c",(unsigned char)j);
     
   }else{
     printf("il ya un probleme dans le fichier source il ne veut pas ouvrir");}

      
}



   



int main(int argc,char** argv){
  if( (calculfrequence(argv[1]))==1){
   affiche();
   parcours(cp-1,"");
   creat_file(argv[1]);}
  
  return 0;
}
