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
 * Archivo: almacenamiento.h
 * Descripción: Librería que define estructuras de almacenamiento de datos.
 *              (HEADER)
 */

#ifndef STD
#define STD
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#define TRUE 1
#define FALSE 0
#endif

#ifndef EDG
#define EDG
#include <limits.h>
#endif


/* Estructura para la comunicación entre procesos */
typedef struct ans Ans;

struct ans {
  int numChild;
  int numRegs;
  int numDirects;
  int tamBlks;
  int tamStr;
	int *lengths;
	char * directories;

};

/*----------------------------------------------------------------------------*/

/* Definicion del tipo PilaString */

/**
 * Estructura de pila convencional. Almacena Strings mediante apuntadores.
 */

typedef struct stack StackString;

struct stack {
  char *palabra ;
  StackString *sig;
};

typedef struct {
  StackString *head;
  int size;
} PilaString;

/* FIN tipo PilaString */

/* INICIO de operaciones referentes al tipo PilaString*/

/**
 * Crea un nuevo stack de Strings, reservando la memoria para ello
 * 
 * retorna: Un nuevo apuntador a StackString vacio. 
 */
StackString *newStackString();

/**
 * Crea una nueva pila vacia, reservando la memoria para ello
 * 
 * retorna: Un nuevo apuntador a PilaString vacia.
 */
PilaString *newPilaString();

/**
 * Inserta un nuevo elemento elem la PilaString pila.
 *
 * *pila: apuntador a la pila en donde se desea insertar el elemento.
 *
 * elem: String que se desea insertar en la pila.
 *
 * retorna: void.
 */
void pushPilaString(PilaString *pila, char* elem);

/**
 * Elimina el primer elemento de la PilaString pila.
 *
 * *pila: apuntador a la pila de la cual se desea obtener el elemento.
 *
 * retorna: el string almacenado en stack obtenido.
 */
char* popPilaString(PilaString *pila);

/**
 * Verifica si la PilaString pila esta vacia, es decir, no contiene elementos.
 *
 * *pila: apuntador a la pila en cuestion.
 *
 * retorna: 1 si la pila esta vacia 0 en caso contrario.
 */
int esVaciaPilaString(PilaString *pila);


/**
 *Imprime la pila mostrando cada uno de sus elementos y si tamano total.
 *
 **pila: pila a imprimir
 */
void imprimePilaString(PilaString *pila);

/**
 *Vacia la PilaString pila
 */
void cleanPila(PilaString *pila);

/*FIN de operaciones referentes al tipo PilaString */

/*Definición del tipo ListaInt.*/

/**
 * Clasica lista de elementos. Es una lista de apuntadores que almacena int.
 */
typedef struct cajitaInt CajitaInt;

struct cajitaInt {
  int data;
  int pos;
  CajitaInt *sig,*ant;
};

typedef struct {
  CajitaInt *head,*tail;
  int size;
} ListaInt;
/*FIN del tipo ListaInt.*/

/*INICIO Funciones y Procedimientos referentes al tipo ListaInt*/

/**
 * Crea una nueva Cajita, reservando la memoria necesaria para ello.
 * 
 * retorna: Un nuevo apuntador a Cajita vacía.
 */
CajitaInt *newCajitaInt();

/**
 * Crea una nueva lista vacía, reservando la memoria necesaria para ello.
 * 
 * retorna: un nuevo apuntador a una lista vacía.
 */
ListaInt *newListaInt();


/**
 * Inserta el elemento 'elem' en la Lista '*list'
 * 
 * *list: apuntador a la Lista donde se desea hacer la inserción.
 * 
 * elem: elemento a insertar en la Lista.
 * 
 * retorna: Un entero que indica el estado de la inserción; 0 si fue realizada 
 *          con éxito, 1 en caso contrario.
 */
int add(ListaInt *list, int elem);

/**
 * Elimina el elemento 'elem' en la Lista '*list'
 * 
 * *list: apuntador a la Lista donde se desea hacer la eliminación.
 * 
 * elem: elemento a eliminar de la Lista.
 */
void delete(ListaInt *list,  int elem);


/**
 * Devuelve el elemento en la posición pos.
 * retorna en la variable 'ans' el elemento almacenado en la posición 'posi'.
 * de no existir un elemento en esa posicion, asigna NULL a 'ans'.
 * list: lista a consultar.
 * posi: posición del elemento solicitado.
 * ans: apuntador a la salida de esta funcion.
 */
void get_li(ListaInt *list, int posi, int *ans);


/**
 * Devuelve un arreglo de enteros conteniendo los elementos de la lista 'list'
 * en el mismo orden en que estaban almacenados.
 * list: Lista a transformar en arreglo.
 * retorna: un arreglo de enteros que contiene los elementos de 'lista' en el
 *          mismo orden en que estaban almacenados.
 */
int *liToArray(ListaInt *list);

/**
 * Dice si un elemento 'elem' está actualmente o no en la Lista '*list'.
 * 
 * *list: apuntador a la Lista donde se desea hacer la búsqueda.
 * 
 * elem: elemento a buscar en la Lista.
 * 
 * retorna: Un entero que indica el estado de la búsqueda; 1 si se encontró el
 *          elemento, 1 en caso contrario.
 */

int isIn(ListaInt *list, int elem);


/**
 * Imprime en la salida estándar la ListaInt 'lista'.
 * 
 * lista: ListaInt a imprimir.
 */
void li_print(ListaInt *lista);

/**
 * Devuelve el primer elemento de la lista, y lo elimina de ésta.
 * list: Lista a consultar.
 * retorna: el primer elemento de la lista, o INT_MIN en caso de que sea
 *          una lista vacía.
 */
int getFirstLI(ListaInt *list);

/**
 * Devuelve el último elemento de la lista, y lo elimina de ésta.
 * list: Lista a consultar.
 * retorna: el último elemento de la lista, o INT_MIN en caso de que sea
 *          una lista vacía.
 */
int getLastLI(ListaInt *list);

/**
 * Se encarga de devolver una ListaInt a su estado original vacía, liberando la
 * memoria consumida por ésta.
 * 
 * lote: Un apuntador a la ListaInt que se desea liberar.
 * 
 * retorna: 0 si se completó la limpieza con éxito, 1 en caso contrario.
 */
int li_liberar(ListaInt *lista);

/*FIN Funciones y Procedimientos referentes al tipo ListaInt*/

/*----------------------------------------------------------------------------*/


/*Definición del tipo ListaStr.*/

/**
 * Clasica lista de elementos. Es una lista de apuntadores que almacena char *.
 * (String)
 */
typedef struct cajaStr CajaStr;

struct cajaStr {
  char *data;
  int pos;
  CajaStr *sig,*ant;
};

typedef struct {
  CajaStr *head,*tail;
  int size;
} ListaStr;
/*FIN del tipo ListaStr.*/

/*INICIO Funciones y Procedimientos referentes al tipo ListaStr*/
/**
 * Crea una nueva CajaStr, reservando la memoria necesaria para ello.
 * 
 * retorna: Un nuevo apuntador a CajaStr vacía.
 */
CajaStr *newCajaStr();

/**
 * Crea una nueva lista vacía, reservando la memoria necesaria para ello.
 * 
 * retorna: un nuevo apuntador a una lista vacía.
 */
ListaStr *newListaStr();


/**
 * Inserta el elemento 'elem' en la Lista '*list'
 * 
 * *list: apuntador a la Lista donde se desea hacer la inserción.
 * 
 * elem: elemento a insertar en la Lista.
 * 
 * retorna: Un entero que indica el estado de la inserción; 0 si fue realizada 
 *          con éxito, 1 en caso contrario.
 */
int addLS(ListaStr *list, char *elem);

/**
 * Elimina el elemento 'elem' en la Lista '*list'
 * 
 * *list: apuntador a la Lista donde se desea hacer la eliminación.
 * 
 * elem: elemento a eliminar de la Lista.
 */
void deleteLS(ListaStr *list,  char *elem);


/**
 * Devuelve el elemento en la posición pos.
 * retorna en la variable 'ans' el elemento almacenado en la posición 'posi'.
 * de no existir un elemento en esa posicion, asigna NULL a 'ans'.
 * list: lista a consultar.
 * posi: posición del elemento solicitado.
 * ans: apuntador a la salida de esta funcion.
 */
void getLS(ListaStr *list, int posi, char *ans);


/**
 * Devuelve un arreglo de String conteniendo los elementos de la lista 'list'
 * en el mismo orden en que estaban almacenados.
 * list: Lista a transformar en arreglo.
 * retorna: un arreglo de String que contiene los elementos de 'lista' en el
 *          mismo orden en que estaban almacenados.
 */
char **LSToArray(ListaStr *list);

/**
 * Dice si un elemento 'elem' está actualmente o no en la Lista '*list'.
 * 
 * *list: apuntador a la Lista donde se desea hacer la búsqueda.
 * 
 * elem: elemento a buscar en la Lista.
 * 
 * retorna: Un entero que indica el estado de la búsqueda; 1 si se encontró el
 *          elemento, 1 en caso contrario.
 */

int isInLS(ListaStr *list, char *elem);


/**
 * Imprime en la salida estándar la ListaInt 'lista'.
 * 
 * lista: ListaInt a imprimir.
 */
void LSprint(ListaStr *lista);

/**
 * Devuelve el primer elemento de la lista, y lo elimina de ésta.
 * list: Lista a consultar.
 * retorna: el primer elemento de la lista, o NULL en caso de que sea
 *          una lista vacía.
 */
char *getFirstLS(ListaStr *list);

/**
 * Devuelve el último elemento de la lista, y lo elimina de ésta.
 * list: Lista a consultar.
 * retorna: el último elemento de la lista, o NULL en caso de que sea
 *          una lista vacía.
 */
char *getLastLS(ListaStr *list);


/**
 * Se encarga de devolver una ListaInt a su estado original vacía, liberando la
 * memoria consumida por ésta.
 * 
 * lote: Un apuntador a la ListaInt que se desea liberar.
 * 
 * retorna: 0 si se completó la limpieza con éxito, 1 en caso contrario.
 */
int LSLiberar(ListaStr *lista);



/*FIN Funciones y Procedimientos referentes al tipo ListaStr*/

/*----------------------------------------------------------------------------*/

/*FIN DEL ARCHIVO (EOF)*/
