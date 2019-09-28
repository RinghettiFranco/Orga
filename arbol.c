#include <C:\Users\fede\Documents\GitHub\Orga\arbol.h>
#include <C:\Users\fede\Documents\GitHub\Orga\lista.h>
#include <stdlib.h>
typedef struct nodo * tNodo;
typedef struct arbol * tArbol;

/**
Inicializa un �rbol vac�o.
Una referencia al �rbol creado es referenciado en *A.
**/
 void crear_arbol(tArbol * a){
*a=(tArbol) malloc(sizeof(struct arbol));
if((*a)==NULL) exit (ARB_ERROR_MEMORIA);
(*a)->raiz=NULL;


}


/**
Recupera y retorna el elemento del nodo N.
*/
 tElemento a_recuperar(tArbol a, tNodo n){
if(a==NULL) exit(ARB_ERROR_MEMORIA);

return n->elemento;
}

/**
Recupera y retorna el nodo correspondiente a la ra�z de A.
**/
 tNodo a_raiz(tArbol a){
 if(a==NULL) exit(ARB_ERROR_MEMORIA);
 return (a->raiz);
 }

/**
 Obtiene y retorna una lista con los nodos hijos de N en A.
**/
 tLista a_hijos(tArbol a, tNodo n)
 {if(a==NULL) exit(ARB_ERROR_MEMORIA);
  if(n==NULL) exit(ARB_ERROR_MEMORIA);
  return (n->hijos);
 }

/**
 Inicializa un nuevo �rbol en *SA.
 El nuevo �rbol en *SA se compone de los nodos del sub�rbol de A a partir de N.
 El subarbol de A a partir de N debe ser eliminado de A.
**/
void a_sub_arbol(tArbol a, tNodo n, tArbol * sa){
if(a==NULL) exit(ARB_ERROR_MEMORIA);
if(n==NULL) exit(ARB_ERROR_MEMORIA);
if(*sa==NULL) exit(ARB_ERROR_MEMORIA);

*sa=(tArbol) malloc(sizeof(struct arbol));

}




