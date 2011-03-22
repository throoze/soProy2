#ifndef STD
#define STD
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#define FALSE 0
#define TRUE 1
#endif

#ifndef EDG
#define EDG
#include <limits.h>
#endif

#ifndef DIRE
#define DIRE
#include <dirent.h>
#endif

#ifndef USEPROC
#define USEPROC
#include <unistd.h>
#endif

#ifndef FCNTL
#define FCNTL
#include <fcntl.h>
#endif

#ifndef TYPE
#define TYPE
#include <sys/types.h>
#endif

#ifndef STATS
#define STATS
#include <sys/stat.h>
#endif

#ifndef ALM
#define ALM
#include "almacenamiento.h"
#endif

#ifndef MSC
#define MSC
#include "misc.h"
#endif

#ifndef RWPIPE
#define RWPIPE
#define READ 0
#define WRITE 1
#endif

#ifndef SGNL
#define SGNL
#include <signal.h>
#endif
#include "job.h"

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
  perror("leyendo***********\n");
  int totalBytes = 0;
  int bitsEnt;
  read(0,&bitsEnt,sizeof(int));
  char *principal =  (char *) malloc(bitsEnt * sizeof(char));
  //kill(padre, SIGUSR2);
  kill(padre,SIGCONT);
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
	int numDir = 0;
 

	PilaString *pila = newPilaString();
	ListaInt * ocup = newListaInt();

 
  /* Itera por el inodo del directorio*/
	direntp=readdir(dirp);
	direntp=readdir(dirp);
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
			pushPilaString(pila, aux);
			add(ocup,strlen(aux));
		  totalBytes += (sizeof(int)) + (strlen(aux) + 1);
			numDir++;

    } else  if (S_ISREG(mode)) {
      numArchi++;
      sumTam = sumTam + (((int) statbuf.st_size)/((int) statbuf.st_blksize));
    }
    free(aux);
  }
  closedir(dirp);
  printf("terminoooooooo-------\n");

  char *directorios = (char *)  malloc(totalBytes);
  while (!esVaciaPilaString(pila)){
	sprintf(directorios, "%s%s!", directorios, popPilaString(pila));
  }
	
   

  /* crea la estructura de retorno */
  Ans *respuesta = (Ans *) malloc(sizeof(Ans));
  respuesta->numChild = numero;
  respuesta->numRegs = numArchi;
  respuesta->tamBlks = sumTam;
  respuesta->tamStr = totalBytes;
	respuesta->lengths =malloc(respuesta->numDirects);
	respuesta->lengths = liToArray(ocup);
  respuesta->directories = malloc(strlen(directorios));


  /* Escribe la respuesta al padre */
  write(1,respuesta, sizeof(respuesta));

}


int main(int argc, char **argv){
  numero = atoi(argv[1]);
  fprintf(stderr,"Estoy en el hijo %d!\n",numero);
  padre = getppid();
  signal(SIGUSR2 ,manejadorSilencio);
  signal(SIGCONT,manejadorMuerte);
	signal(SIGUSR1 ,manejadorLectura);

  while (TRUE){
		perror( "me pauso\n");
    pause();
    perror("esto pasa luego de q termina\n");
  }
  return 0;
}








