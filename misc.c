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
 * Archivo: misc.c
 * Descripción: Librería con funciones útiles miscelaneas.
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

int strIsUL(char *str) {
  char *p = str;
  unsigned long integer = strtoul(str,&p,10);
  errno = 0;
  if (errno != 0) {
    // Falló la conversión, hay overflow.
    perror("Numero demasiado grande. Overflow.\n");
    return FALSE;
  } else if (str == p){
    // Falló la conversión, no se empezó a parsear el string.
    return FALSE;
  } else if (*p != 0) {
    // Falló la conversión, no todos los caracteres son números.
    return FALSE;
  }
  return TRUE;
}
