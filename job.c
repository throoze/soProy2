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
  fprintf(stderr,"leyendo***********\n");
  int totalBytes = 0;
  int bitsEnt;
  read(0,&bitsEnt,sizeof(int));
  char *principal =  (char *) malloc(bitsEnt * sizeof(char));
  fprintf(stderr,"Soy el HIJO %d; leidos %d bytes\n",numero,bitsEnt);
  fflush(stderr);
  //kill(padre, SIGUSR2);
  kill(padre,SIGCONT);
  read(0, principal, bitsEnt);
  fprintf(stderr,"leido, dir: \"%s\"\n", principal);
  fflush(stderr);
  
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

  fprintf(stderr,"HIJO %d: Voy a iterar!!!\n",numero);
  fflush(stderr);
  /* Itera por el inodo del directorio*/
  while ((direntp=readdir(dirp)) != NULL) {
    if (strcmp(direntp->d_name,".") != 0 && strcmp(direntp->d_name,"..") != 0) {
      char *aux = (char *) malloc((strlen(principal) + strlen(direntp->d_name) + 3) * sizeof(char));
      fflush(stdout);
      sprintf(aux, "%s/%s", principal , direntp->d_name);
      if (stat(aux, &statbuf) == -1) {
        fprintf(stderr, " No se pudo aplicar stat sobre el archivo %s: %s \n", aux, strerror(errno));
        exit(1);
      }
      mode = statbuf.st_mode;
      if ( S_ISDIR(mode)) {
        sprintf(aux, "%s/",aux);
        pushPilaString(pila, aux);
        add(ocup,strlen(aux));
        totalBytes += strlen(aux);
        numDir++;

      } else  if (S_ISREG(mode)) {
        numArchi++;
        sumTam = sumTam + ((((int) statbuf.st_size)/((int) statbuf.st_blksize)) + ((((int) statbuf.st_size)%((int) statbuf.st_blksize)) != 0 ? 1 : 0));
      }
      free(aux);
    }
  }
  closedir(dirp);
  printf("terminoooooooo-------\n");
  totalBytes++;
  char *directorios = (char *)  malloc(totalBytes);
  while (!esVaciaPilaString(pila)){
	sprintf(directorios, "%s%s!", directorios, popPilaString(pila));
  }
	
   

  /* crea la estructura de retorno */
  Ans *respuesta = (Ans *) malloc(sizeof(Ans));
  respuesta->numChild = numero;
  respuesta->numRegs = numArchi;
  respuesta->numDirects = numDir;
  respuesta->tamBlks = sumTam;
  respuesta->tamStr = totalBytes;
  respuesta->lengths = malloc(respuesta->numDirects);
  respuesta->lengths = liToArray(ocup);
  respuesta->directories = malloc(strlen(directorios));

  fprintf(stderr,"HIJO %d: Voy a escribir!!!\n",numero);
  fflush(stderr);
  /* Escribe la respuesta al padre */
  int tam = (5*sizeof(int))+(numDir*sizeof(int))+((totalBytes+1)*sizeof(char));
  char * answer = (char *) malloc(tam);
  register int i;
  register int j = 0;
  for (i = 0; i < sizeof(int); i++) {
    answer[j] = ((char *)numero)[i];
    j++;
  }
  for (i = 0; i < sizeof(int); i++) {
    answer[j] = ((char *)numArchi)[i];
    j++;
  }
  for (i = 0; i < sizeof(int); i++) {
    answer[j] = ((char *)numDir)[i];
    j++;
  }
  for (i = 0; i < sizeof(int); i++) {
    answer[j] = ((char *)sumTam)[i];
    j++;
  }
  for (i = 0; i < sizeof(int); i++) {
    answer[j] = ((char *)totalBytes)[i];
    j++;
  }
  for (i = 0; i < (numDir * sizeof(int)); i++) {
    answer[j] = ((char *)(respuesta->lengths))[i];
    j++;
  }
  for (i = 0; i < (totalBytes * sizeof(char)); i++) {
    answer[j] = directorios[i];
    j++;
  }
  
  write(1,answer,(strlen(answer)+1));
  perror(strcat("HIJO numero ",num));
}


int main(int argc, char **argv){
  num = argv[1];
  numero = atoi(argv[1]);
  perror("hijoooo\n");
  fprintf(stderr,"Estoy en el hijo %d!\n",numero);
  fflush(stderr);
  padre = getppid();
  signal(SIGUSR2 ,manejadorSilencio);
  signal(SIGCONT,manejadorMuerte);
  signal(SIGUSR1 ,manejadorLectura);

  while (TRUE){
    fprintf(stderr,"me pauso\n");
    fflush(stderr);
    pause();
    fprintf(stderr,"esto pasa luego de q termina el HIJO = %d\n",numero);
    fflush(stderr);
  }
  return 0;
}
