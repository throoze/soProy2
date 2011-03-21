/*
 * Universidad Simón Bolívar
 * Departamento de Computación y Tecnología de la Información
 * CI-3825  --  Sistemas Operativos I
 * Prof.: Yudith Cardinale
 * Proyecto 2: Comunicación entre procesos
 * Grupo 26
 * Autores: Victor De Ponte, 05-38087
 *	   	Isaac Lopez, 07-41120
 *
 * Archivo: main.c
 * Descripción: Programa principal que gestiona los trabajos del proyecto 2.
 */

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

#ifndef USO
/* Mensaje de USO que se mostrará como ayuda al usarse la opción "-h" 
 * Basado en el enunciado del proyecto.
 */
#define USO "   UsoDisco:\tCalcula de forma concurrente el espacio en disco utilizado por\n\t\tlos archivos regulares a partir de un directorio.\n   USO:\n\tSintaxis:\n\n\t\tUsoDisco [-h] | [-n <i>] [-d <directorio>] [<archivoSalida>]\n\n\tOpciones:\n\n\t-h\t\t---> Muestra este mensaje de ayuda y termina. No debe\n\t\t\t     usarse junto con otras opciones.\n\t-n <i>\t\t---> Nivel de concurrencia solicitado. El parametro <i>\n\t\t\t     representa el numero de procesos a crear. Por de-\n\t\t\t     fecto secrea un solo proceso.\n\t-d <directorio>\t---> Especifica un directorio desde donde se calcula el\n\t\t\t     espacio utilizado. Por defecto se hace el calculo\n\t\t\t     desde el directorio actual.\n\t<archivoSalida> ---> Archivo que contendra la lista de directorios junto\n\t\t\t     con el espacio en bloques ocupado por los archivos\n\t\t\t     regulares en cada directorio. El valor por defecto\n\t\t\t     es la salida estandar.\n"
#endif

#include "main.h"

void sigusr1Handler() {
    
}

void sigusr2Handler() {
    int childPid, childStatus;
    childPid = wait(&childStatus);
    //printf("El hijo %d termino en menos de %d segundos...\n",childPid,delay);
    exit(0);
}

void procArg(int argc, char **argv, int *i, unsigned long *nc, DIR **startDir,char **startDirName, int *out){
  if (strcmp(argv[*i],"-h") == 0) {
    if (argc == 2) {
      printf(USO);
      exit(0);
    } else {
      fprintf(stderr,"\nUsoDisco:\nERROR: La opción '-h' no debe usarse junto con otras opciones.\n");
      printf(USO);
      exit(1);
    }
  } else if (strcmp(argv[*i],"-n") == 0) {
    if ((*i+1) < argc) {
      if (strIsUL(argv[*i+1])) {
	*i = *i + 1;
	char *p = argv[*i];
	*nc = strtoul(argv[*i],&p,10);
      } else {
	fprintf(stderr,"\nUsoDisco:\nERROR: Se esperaba un numero despues de la opcion '-n'.\n");
	printf(USO);
	exit(1);
      }
    } else {
      printf("\nUsoDisco:\nERROR: Se esperaba un argumento despues de la opcion '-n'.\n");
      printf(USO);
      exit(1);
    }
  } else if (strcmp(argv[*i],"-d") == 0) {
    if ((*i+1) < argc) {
      closedir(*startDir);
      *startDirName = (char *) malloc((strlen(argv[*i+1]) + 2) * sizeof(char));
      strcpy(*startDirName,argv[*i+1]);

      if ( argv[*i+1][strlen(argv[*i+1])-1] != '/') {
	sprintf(*startDirName, "%s/", *startDirName);
      }
      if ( (*startDir = opendir(*startDirName)) == NULL) {
	char aux[53 + strlen(*startDirName)];
	sprintf(aux,"\nUsoDisco:\nERROR: Problema abriendo el directorio %s\n\t", *startDirName);
	perror(aux);
	printf(USO);
	exit(1);
      }
      *i = *i + 1;
    } else {
      fprintf(stderr,"\nUsoDisco:\nERROR: Se esperaba un argumento despues de la opcion '-d'.\n");
      printf(USO);
      exit(1);
    }
  } else {
    if ( (*out = open(argv[*i], O_RDWR | O_CREAT,600)) < 0) {
      char aux[60 + strlen(argv[*i])];
      sprintf(aux,"\nUsoDisco:\nERROR: Problema abriendo o creando el archivo \"%s\"\n\t", argv[*i]);
      perror(aux);
      printf(USO);
      exit(1);
    }
  }
}

void firstPass(DIR *startDir,char *startDirName,PilaString *pendDirs,ListaStr *ansDirs,ListaInt *ansBlocks,int *numRegFiles,int *numDirs, int *totalBlocks){
  struct dirent *direntp;
  while ((direntp=readdir(startDir)) != NULL) {
    if (strcmp(direntp->d_name,".") != 0 && strcmp(direntp->d_name,"..") != 0) {
      int result;
      struct stat statBuf;
      mode_t mode;

      char *fileName = (char *) malloc((strlen(startDirName) + strlen(direntp->d_name) + 2) * sizeof(char));
      sprintf(fileName,"%s%s",startDirName,direntp->d_name);

      result=stat(fileName, &statBuf);

      if (result==-1) {
        char msg[] = "\nUsoDisco:\nERROR: Problema al obtener los stats del archivo ";
        sprintf(msg,"%s%s%s\n",msg,startDirName,direntp->d_name);
        perror(msg);
        free(fileName);
        exit(-1);
      }

      mode=statBuf.st_mode;
      if (S_ISDIR(mode)) {
        /* Lo añado a la pila de directorios por explorar y lo contabilizo*/
        sprintf(fileName,"%s/", fileName);
        pushPilaString(pendDirs,fileName);
        *numDirs = *numDirs + 1;
        //printf("El archivo \"%s\" Es directorio y tiene %d bytes y %d links\n",fileName, (int) statBuf.st_size,(int) statBuf.st_nlink);
      } else if (S_ISREG(mode)) {
        /* Lo contabilizo y contabilizo su peso*/
        *numRegFiles = *numRegFiles + 1;
        *totalBlocks = *totalBlocks + (((int) statBuf.st_size)/((int) statBuf.st_blksize));
        //*totalBlocks = *totalBlocks + ((int) statBuf.st_blocks);
        //printf("El archivo \"%s\" Es Regular y tiene %d bytes y %d links\n",fileName,(int) statBuf.st_size,(int) statBuf.st_nlink);
      }
    }
  }
	//printf("*****************%d\n",*totalBlocks);
  addLS(ansDirs, startDirName);
  add(ansBlocks, *totalBlocks);
  *numDirs = *numDirs + 1;
}

int lazyJob(int busyJobs[], int nc){
  register int i;
  for (i = 0; i < nc; i++) {
    if (busyJobs[i] == FALSE) {
      return i;
    }
  }
  return -1;
}

int main (int argc, char **argv) {
  /* Procesamiento de la entrada por linea de comandos */
  if (argc > 6) {
    fprintf(stderr,"\nUsoDisco:\nERROR: Demasiados argumentos.\n");
    printf(USO);
    exit(1);
  }

  /* Valores por default */
  unsigned long nc = 1;     // Nivel de concurrencia
  DIR *startDir;            // Directorio inicial
  char *startDirName = "./";
  if ( (startDir = opendir(startDirName)) == NULL) {
    perror("\nUsoDisco:\nERROR: Problema abriendo el directorio \"./\" (directorio por defecto)\n\t");
    printf(USO);
    exit(1);
  }
  int out = 1;              // Archivo de salida (stdout)

  if (argc != 1) {
    int i;
    for (i = 1; i < argc; i++){
      procArg(argc,argv,&i,&nc,&startDir,&startDirName,&out);
    }
  }
  /* Fin del Procesamiento de la entrada por linea de comandos */

  printf("El nombre del directorio de inicio es: %s\n", startDirName);

  /* Otras variables e inicializaciones */
  PilaString *pendDirs = newPilaString(); // Pila que contiene los nombres de
                                          // los directorios pendientes por
                                          // revisar.
  ListaStr *ansDirs = newListaStr();      // Pila que contiene los nombres de
                                          // Los directorios que se han explo-
                                          // rado.
  ListaInt *ansBlocks = newListaInt();    // Contiene la cantidad de bloques
                                          // asociados a los archivos conta-
                                          // bilizados por la posición que o-
                                          // cupan
  int numRegFiles = 0;                    // Contador de archivos regulares.
  int numDirs = 0;                        // Contador de directorios explorados.
  int totalBlocks = 0;                    // Contador de bloques.
  pid_t jobs[nc];                         // Contenedor de los pid's de los 
                                          // procesos hijos.
  int busyJobs[nc];                       // Indicador de trabajos (procesos) 
                                          // ocupados.  
  int numBusy = 0;                        // Numero de trabajos ocupados.
  int numLazy = nc;                       // Numero de trabajos desocupados.
  int pipeR[2];                           // Contenedor del pipes que va a
                                          // LEER de los procesos hijos.
  int pipeW[2];                           // Contenedor del pipe que va a
                                          // ESCRIBIR en los procesos hijos.
  register int i;                         // Contador para los ciclos.
  for (i = 0; i < nc; i++) {
    busyJobs[i] = FALSE;
  }

  firstPass(startDir,startDirName,pendDirs,ansDirs,ansBlocks,&numRegFiles,&numDirs,&totalBlocks);

  /* Crear los pipes para la comunicación entre padre e hijos */
  pipe(pipeR);
  pipe(pipeW);

  /* Redirección de la entrada estandar del padre al pipe */
  close(pipeR[WRITE]);
  dup2(pipeR[READ],0);
  close(pipeR[READ]);

  /* Crear los procesos hijos */
  for (i = 0; i < nc; i++) {
    if ((jobs[i]=fork())==0){
      /* Redireccion de la entrada al pipe */
      close(pipeW[WRITE]);
      dup2(pipeW[READ],0);
      close(pipeW[READ]);
      /* Redireccion de la salida al pipe */
      close(pipeR[READ]);
      dup2(pipeR[WRITE],1);
      close(pipeR[WRITE]);
      char numProc[12];
      sprintf(numProc,"%d",i);
      execlp("./job","job",numProc,NULL);
    }
  }

  /* Instalo el manejador para SIGUSR2 */

  /* Asigna las tareas: */
  while (numLazy > 0){
    if (!esVaciaPilaString(pendDirs)) {
      int child = lazyJob(busyJobs,nc);
      kill(jobs[child],SIGUSR1);
      char numBytes[12];
      char *directory = popPilaString(pendDirs);
      int tam = sizeof(directory);
      sprintf(numBytes,"%d",tam);
      write(pipeW[WRITE],numBytes,tam);
      busyJobs[child] = TRUE;
      numBusy++;
      numLazy--;
      pause();
    }
  }

  /* COSAS QUE FALTAN: */
  ///////////////////////
  /* -COORDINAR LA ASIGNACION DE TRABAJOS */ 
  /* -PASAR LAS LISTAS A ARREGLOS */
  /* -ORDENARLOS POR EL NOMBRE DEL DIRECTORIO */
  /* -ESCRIBIR LA SALIDA */

  char string[] = "Wepale!!!! estoy escribiendo fino!!!\n";
  write(out,string,strlen(string));


  printf("\npendDirs:\n");
  imprimePilaString(pendDirs);
  printf("\nansBlocks:\n");
  li_print(ansBlocks);
  printf("\nansDirs:\n");
  LSprint(ansDirs);

  /* LIBERACION DE MEMORIA USADA Y CIERRE DE FICHEROS ABIERTOS*/
  cleanPila(pendDirs);
  li_liberar(ansBlocks);
  LSLiberar(ansDirs);
  closedir(startDir);
  if (out != 1) {
    close(out);
  }

  printf("\nDespues de liberar:\n");
  printf("\n\npendDirs:\n");
  imprimePilaString(pendDirs);
  printf("\n\nansBlocks:\n");
  li_print(ansBlocks);
  printf("\n\nansDirs:\n");
  LSprint(ansDirs);

  /* SUMARIO */
  printf("\n\nSUMARIO:\n\n\tNumero de procesos creados:\t\t\t%lu\n\tNumero de directorios examinados:\t\t%d\n\tNumero de archivos regulares contabilizados:\t%d\n", nc,numDirs,numRegFiles);
  fflush(stdout);
  return 0;
}
