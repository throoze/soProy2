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

#ifndef DIRE
#define DIRE
#include <dirent.h>
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

#ifndef USO
/* Mensaje de USO que se mostrará como ayuda al usarse la opción "-h" 
 * Basado en el enunciado del proyecto.
 */
#define USO "   UsoDisco:\tCalcula de forma concurrente el espacio en disco utilizado por\n\t\tlos archivos regulares a partir de un directorio.\n   USO:\n\tSintaxis:\n\n\t\tUsoDisco [-h] | [-n <i>] [-d <directorio>] [<archivoSalida>]\n\n\tOpciones:\n\n\t-h\t\t---> Muestra este mensaje de ayuda y termina. No debe\n\t\t\t     usarse junto con otras opciones.\n\t-n <i>\t\t---> Nivel de concurrencia solicitado. El parametro <i>\n\t\t\t     representa el numero de procesos a crear. Por de-\n\t\t\t     fecto secrea un solo proceso.\n\t-d <directorio>\t---> Especifica un directorio desde donde se calcula el\n\t\t\t     espacio utilizado. Por defecto se hace el calculo\n\t\t\t     desde el directorio actual.\n\t<archivoSalida> ---> Archivo que contendra la lista de directorios junto\n\t\t\t     con el espacio en bloques ocupado por los archivos\n\t\t\t     regulares en cada directorio. El valor por defecto\n\t\t\t     es la salida estandar.\n"
#endif
