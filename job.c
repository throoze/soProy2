#ifndef STD
#define STD
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FALSE 0
#define TRUE 1
#endif

#ifndef ALM
#define ALM
#include "almacenamiento.h"
#endif


#include "job.h"
#include  <signal.h>

int numero;
int padre;
int hablar;

void manejadorSilencio(){
  hablar = (hablar + 1)/2;
}

void manejadorMuerte(){
	exit(0);
}

void manejadorLectura(){	
  printf("leyendo***********\n");
  char *principal =  (char *) malloc(sizeof(char *));
  int bitsEnt;
  read(0, bitsEnt, 12);
  kill(padre, SIGUSR2);
  read(0, principal, bitsEnt);

  DIR *dirp;
  struct dirent *direntp;
  struct stat statbuf;
  mode_t mode;

  if ((dirp = opendir(principal))==NULL) {
    fprintf(stderr,"No se puede abrir el directorio %s: %s\n", principal,
  	    strerror(errno));
    exit(1);
  }

  int sumTam  = 0;
  int numArchi = 0;
  PilaString *directorios = newPilaString();
 
  while ((direntp=readdir(dirp)) != NULL) {
    char *aux = (char *) malloc((strlen(principal) + strlen(direntp->d_name) + 2) * sizeof(char));
    fflush(stdout);
    sprintf(aux, "%s/%s", principal , direntp->d_name);
    if (stat(aux, &statbuf) == -1) {
      fprintf(stderr, " No se pudo aplicar stat sobre el archivo %s: %s \n", aux, strerror(errno));
      exit(1);
    }
    mode = statbuf.st_mode;
    if ( S_ISDIR(mode)) {
      pushPilaString(directorios, aux);
			
    } else  if (S_ISREG(mode)) {
      numArchi++;
      sumTam = sumTam + (((int) statbuf.st_size)/((int) statbuf.st_blksize));
    }
    free(aux);
  }
  closedir(dirp);
  printf("terminoooooooo-------\n");
  while(!hablar){		
    pause();
  }
  kill(padre,SIGUSR1);
  write(numero);
  pause();
  write(directorios->size);
  pause();
  while (!esVaciaPilaString(directorios)){
    char *aux = popPilaString(directorios);
    write(sizeof(aux));
    pause();
    write(aux);
  }
  pause();
  write(numArchi);
  pause();
  write(sumTam);
	
}

void main(int argc, char **argv){

  numero = atoi(argv[1]);
  padre = getppid();
  signal(SIGUSR1 ,manejadorLectura);
  signal(SIGUSR2 ,manejadorSilencio);
	signal(SIGCONT,manejadorMuerte);

  ListaStr *prueba = newListaStr();
  addLS(prueba,"conejo");
  addLS(prueba,"gatubela");
  addLS(prueba,"arbol");
  addLS(prueba,"reticulo");
  addLS(prueba,"acorde");
  addLS(prueba,"distante");
  //LSprint(prueba);
  char **prueba2 = LSToArray(prueba);

  printf("\n \n");
  
  int it;
  for(it = 0; it < 6; it++){
    printf("%s\n", prueba2[it]);
    fflush(stdout);
  }
    ordena(prueba2);
    printf("ya ordenooooooooooooooo\n\n");
    it = 0;
    //for(it = 0; it < 6; it++){
      printf("%s\n", prueba2[0]);
      fflush(stdout);
      //}


while (TRUE){
  pause();
  printf("esto pasa luego de q termina\n");
 }
}








