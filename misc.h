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
 * Archivo: misc.h
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

/**
 * Verifica que el String 'str' represente efectivamente un número del tipo
 * unsigned long.
 * str: String a verificar.
 * retorna: 1 en caso de que 'str' represente en efecto un numero del tipo
 *          unsigned long; y 0 en caso contrario.
 */
int strIsUL(char *str);


/**
 *
 *
 *
 */
void merge2(char **a, int a1, int a2);

/**
 * Llamada al ordenamiento por mezcla de dos arreglos de igual tamano
 * Parametros: a y b  son los arreglos a ordenar, basados en el criterio del 
 * arreglo a
 * sin retorno
 */
void mergeSort2(char **a, int a1, int a2);



void ordena(char **a);
