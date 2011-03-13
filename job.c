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


int main(int argc, char **argv){
  DIR *dirp;
  struct dirent *direntp;
  struct stat statbuf;
  int suma = 0;

  printf("%s\n",argv[1]);
  if ((dirp = opendir(argv[1]))==NULL) {
    fprintf(stderr,"No se puede abrir el directorio %s: %s\n", argv[1],
  	    strerror(errno));
    exit(1);
  }

  int sumTam  = 0;
  int numArchi = 0;
  PilaString *directorios = newPilaString();
 
  while ((direntp=readdir(dirp)) != NULL) {
    char aux[50];
    fflush(stdout);
    sprintf(aux, "%s/%s", argv[1] , direntp->d_name);
    if (stat(aux, &statbuf) == -1) {
      fprintf(stderr, " No se pudo aplicar stat sobre el archivo %s: %s \n", aux, strerror(errno));
      exit(1);
    }
    if (statbuf.st_mode & S_IFDIR) {
      printf("%s es un directorio\n", aux);
      pushPilaString(directorios, aux);
      imprimePilaString(directorios);
  }
    else
          printf("%s no es un directorio\n", aux);
  }
  closedir(dirp);
  imprimePilaString(directorios);
  exit(0);
}








