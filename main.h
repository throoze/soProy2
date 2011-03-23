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
 * Archivo: main.h
 * Descripción: Programa principal que gestiona los trabajos del proyecto 2 
 *              (HEADER).
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


/* Variables globales: */
unsigned long nc = 1; // Nivel de concurrencia

pid_t *jobs;          // Contenedor de los pid's de los 
                      // procesos hijos.

PilaString *pendDirs; // Pila que contiene los nombres de
                      // los directorios pendientes por
                      // revisar.

ListaStr *ansDirs;    // Pila que contiene los nombres de
                      // Los directorios que se han explo-
                      // rado.

ListaInt *ansBlocks;  // Contiene la cantidad de bloques
                      // asociados a los archivos conta-
                      // bilizados por la posición que o-
                      // cupan.

int numRegFiles;      // Contador de archivos regulares.

int numDirs;          // Contador de directorios explorados.

int *busyJobs;        // Indicador de trabajos (procesos) 
                      // ocupados.

char **dirAsig;       // Directorios asignados a cada hijo.x

int  numBusy;         // Numero de trabajos ocupados.

int  numLazy;         // Numero de trabajos desocupados.

int pipeW[2];         // Contenedor del pipe que va a
                      // ESCRIBIR en los procesos hijos.

int **pipesR;         // Contenedor de los pipes que van a
                      // LEER de los procesos hijos.

int numChild;         // Número del hijo leido.

int numRegs;          // Número de archivos regulares encontrados.

int numDirects;       // Número de directorios encontrados.

int tamBlks;          // Tamaño en bloques de los archivos regulares
                      // en el directorio leido.

int tamStr;           // Número de bytes a leer a continuación.

Ans * buffer;         // Estructura de buffer de lectura.

/**
 * Procesa los argumentos entrados por linea de comandos.
 * Recibe argumentos apuntadores para que los argumentos sean pasados
 * por referencia.
 * ARGUMENTOS:
 * argc: Numero de argumentos ingresados por linea de comandos.
 * argv: Arreglo de strings que contiene los argumentos pasados por linea
 *       de comandos.
 * i: Numero del argumento siendo procesado.
 * nc: Nivel de concurrencia.
 * startDir: Directorio donde se iniciará la contabilización de los bloques.
 * startDirName: Nombre del directorio donde se iniciará la contabilización
 *               de los bloques.
 * out: File Descriptor de la salida del programa.
 */
void procArg(int argc, char **argv, int *i, unsigned long *nc, DIR **startDir,char **startDirName, int *out);

/**
 * Primera leida sobre el directorio donde se calculara el espacio ocupado por
 * los archivos regulares. Contabiliza los archivos regulares y el espacio que
 * éstos ocupan, y almacena los subdirectorios para ser leidos luego concu-
 * rrentemente por procesos hijos del proceso maestro.
 * ARGUMENTOS:
 * startDir: Directorio donde se iniciará la contabilización de los bloques.
 * startDirName: Nombre del directorio donde se iniciará la contabilización
 *               de los bloques.
 * pendDirs: pila de strings que contiene los nombres de los directorios que no
 *           se han contabilizado.
 * ansDirs: Lista de los nombres de los directorios que han sido contabilizados.
 * ansBlocks: Lista de enteros que contien la cantidad de bloques ocupados por
 *            los archivos regulares contenidos en los directorios contabiliza-
 *            dos hasta el momento. Están en el mismo orden que los directorios
 *            a los que corresponden en ansDirs.
 * numRegFiles: Numero de archivos regulares contabilizados hasta el momento.
 * numDirs: Numero de directorios contabilizados hasta el momento.
 * totalBlocks: Numero total de bloques contabilizados hasta el momento.
 */
void firstPass(DIR *startDir,char *startDirName,ListaStr *ansDirs,ListaInt *ansBlocks,int *numRegFiles,int *numDirs, int *totalBlocks);

/**
 * Devuelve el índice del primer proceso libre, ó -1 en caso de que todos los
 * procesos estén ocupados.
 * busyJobs: arreglo que indica el estado de los procesos.
 * nc: numero de procesos que se están manejando.
 * retorna: el índice del primer proceso libre; -1 en caso de que todos los 
 *          procesos estén ocupados.
 */
int lazyJob(int busyJobs[], int nc);
