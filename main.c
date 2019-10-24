#include <stdio.h>
#include <stdlib.h>
#include <C:\Users\fede.000\Documents\GitHub\Orga\lista.h>
#include <C:\Users\fede.000\Documents\GitHub\Orga\arbol.h>

typedef struct celda* tLista;
typedef struct celda* tPosicion;
typedef void * tElemento;

typedef struct nodo * tNodo;
typedef struct arbol * tArbol;

void eliminarEnteros(tElemento e){
    free(e);
    e=NULL;
}

void mostrarhijos(tArbol arbol, tLista hijos, tNodo nodo){
tElemento enodo=(tElemento) nodo->elemento;
printf("Lista de hijos del nodo %i: \n",*(int*)enodo);
printf("[ ");
tPosicion pos=l_primera(hijos);
while(pos!= l_fin(hijos)){
        tNodo node=(tNodo)l_recuperar(hijos,pos);
        tElemento d=a_recuperar(arbol,node);
        printf("%i ",*(int*)d);
        pos=l_siguiente(hijos,pos);
        }


printf("] \n");
}













int main(){
tArbol arbol;
int i1,i2,i3,i4,i5,i6,i7;
i1=1;
i2=2;
i3=3;
i4=4;
i5=5;
i6=6;
i7=7;



printf("***************************** \n Test del TDA Arbol: \n *****************************\n Crearemos un arbol de enteros\n\n\n");

printf("Creamos un arbol y una raiz, la cual sera seteada con el elemento 1:\n " );


crear_arbol(&arbol);
crear_raiz(arbol,&i1);
printf("Recuperamos el elemento contenido en la raiz: \n");

tNodo padre=a_raiz(arbol);

printf("El elemento contenido es el [%i] \n\n", *(int*)padre->elemento);
printf("***************************** \n Se inserta como hijo de la raiz al 3: \n\n");
printf("***************************** \n La lista de hijos de la raiz ahora es : \n\n");
tLista hijos=a_hijos(arbol,padre);
a_insertar(arbol,a_raiz(arbol),NULL,&i3);
mostrarhijos(arbol,hijos,padre);

printf("***************************** \n Se inserta al 4 como hijo mas a la derecha de la raiz : \n\n");
a_insertar(arbol,a_raiz(arbol),NULL,&i4);
mostrarhijos(arbol,hijos,padre);
//recupero la primera posicion de los hijos de la raiz

tNodo prim=l_recuperar(hijos,l_primera(hijos));

printf("***************************** \n Se inserta al 2 como hijo mas a la izquerda de la raiz : \n\n");
a_insertar(arbol,a_raiz(arbol),prim,&i2);
mostrarhijos(arbol,hijos,padre);

printf("***************************** \n Se insertan dos hijos al 3, el 5 y el 6 : \n\n");

a_insertar(arbol,prim,NULL,&i5);
a_insertar(arbol,prim,NULL,&i6);
a_insertar(arbol,prim,NULL,&i7);
mostrarhijos(arbol,a_hijos(arbol,prim),prim);

printf("***************************** \n");
printf("Se procede a eliminar el nodo con el elemento 3,\n ");
printf("subiendo sus hijos a la lista donde se encontraba ");
printf("el 3 con el mismo orden y en el lugar de 3\n");
a_eliminar(arbol,prim,&eliminarEnteros);

mostrarhijos(arbol,a_hijos(arbol,padre),padre);
printf("***************************** \n");
printf("Destruimos el Arbol \n");
a_destruir(&arbol,&eliminarEnteros);

printf("***************************** \n");
printf("Creamos un nuevo arbol \n ");
crear_arbol(&arbol);
int i11=11;
crear_raiz(arbol,&i11);
printf("Recuperamos el elemento contenido en la raiz: \n");
tNodo nuevopadre=a_raiz(arbol);
printf("El elemento contenido es el [%i] \n\n", *(int*)nuevopadre->elemento);
tLista nuevoshijos=a_hijos(arbol,nuevopadre);
int i13=13;
int i14=14;
int i12=12;
int i15=15;
int i16=16;
a_insertar(arbol,a_raiz(arbol),NULL,&i12);
a_insertar(arbol,a_raiz(arbol),NULL,&i13);
a_insertar(arbol,a_raiz(arbol),NULL,&i14);
mostrarhijos(arbol,a_hijos(arbol,a_raiz(arbol)),a_raiz(arbol));


tNodo nuevoprim=l_recuperar(nuevoshijos,l_siguiente((nuevoshijos),l_primera(nuevoshijos)));




printf("***************************** \n Se insertan dos hijos al 13, el 15 y el 16 : \n\n");

a_insertar(arbol,nuevoprim,NULL,&i15);
a_insertar(arbol,nuevoprim,NULL,&i16);

mostrarhijos(arbol,a_hijos(arbol,nuevoprim),nuevoprim);

tLista hijostrece= a_hijos(arbol,nuevoprim);
tNodo n15=l_recuperar(hijostrece,l_primera(hijostrece));
int i17=17;

printf("***************************** \n Se inserta el 17 como hijo del 15 : \n\n");
a_insertar(arbol,n15,NULL,&i17);
tLista hijos15= a_hijos(arbol,n15);
mostrarhijos(arbol,hijos15,n15);



printf("----------------------------- \n Se hace el testeo del subArbol, donde la raiz del arbol nuevo\n ");
printf("sera la que contiene al elemento 13 \n\n\n");
printf("Probando el arbol nuevo \n");
tArbol nuevoArbol;
a_sub_arbol(arbol,nuevoprim,&nuevoArbol);

printf("Recuperamos el elemento contenido en la raiz: \n");
tNodo nuevoRaiz=a_raiz(nuevoArbol);

printf("El elemento contenido es el [%i] \n\n", *(int*)nuevoRaiz->elemento);

tLista listaNuevo=a_hijos(nuevoArbol,nuevoRaiz);
mostrarhijos(nuevoArbol,listaNuevo,nuevoRaiz);

tPosicion primeroNuevo = l_primera(listaNuevo);
tNodo primero = l_recuperar(listaNuevo,primeroNuevo);
tLista hijosNuevo = a_hijos(nuevoArbol,primero);
mostrarhijos(nuevoArbol,hijosNuevo,primero);


mostrarhijos(arbol,a_hijos(arbol,a_raiz(arbol)),a_raiz(arbol));



/**
printf("Tratamos de crear una nueva raiz en el subarbol, deberia tirar error 10.");
crear_raiz(nuevoArbol,i17);
**/

/**
printf("Tratamos de eliminar la raiz con mas de un hijo, deberia tirar error 10.");
a_eliminar(nuevoArbol,a_raiz(nuevoArbol),&eliminarEnteros);
**/
return 0;
}



