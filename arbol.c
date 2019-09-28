#include <C:\Users\FRANCO\Desktop\ORGA\Orga\arbol.h>
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
Crea la ra�z de A.
Si A no es vac�o, finaliza indicando ARB_OPERACION_INVALIDA.
**/
void crear_raiz(tArbol a, tElemento e){
    tNodo root = (tNodo) malloc(sizeof (struct nodo));
    if(root==NULL)exit(ARB_ERROR_MEMORIA);
    tLista children = (tLista) malloc(sizeof (struct celda));
    if(children==NULL)exit(ARB_ERROR_MEMORIA);//LST o ARB preguntar

    root->elemento=e;
    root->padre=NULL;

    crear_lista(&children);
    root->hijos=children;

    a->raiz=root;
}

/**
 Inserta y retorna un nuevo nodo en A.
 El nuevo nodo se agrega en A como hijo de NP, hermano izquierdo de NH, y cuyo r�tulo es E.
 Si NH es NULL, el nuevo nodo se agrega como �ltimo hijo de NP.
 Si NH no corresponde a un nodo hijo de NP, finaliza indicando ARB_POSICION_INVALIDA.
 NP direcciona al nodo padre, mientras NH al nodo hermano derecho del nuevo nodo a insertar.
**/
tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e){
    //Creacion del nodo
    tNodo nuevo = (tNodo) malloc(sizeof (struct nodo));
    if(nuevo==NULL)exit(ARB_ERROR_MEMORIA);
    tLista children = (tLista) malloc(sizeof (struct celda));
    if(children==NULL)exit(ARB_ERROR_MEMORIA);//LST o ARB preguntar
    nuevo->elemento=e;
    nuevo->padre=np;
    crear_lista(&children);
    nuevo->hijos=children;

    //Insercion en el arbol
    tLista hermanos = (np->hijos);
    tPosicion hermano = l_primera(hermanos);
    if(nh==NULL){
        l_insertar(hermanos,l_fin(hermanos),nuevo);
    }else{
        while((l_recuperar(hermanos,hermano)!=nh) && (hermano!=l_fin(hermanos)))
            hermano=l_siguiente(hermanos,hermano);
        if(hermano==l_fin(hermanos))exit(ARB_POSICION_INVALIDA);
        l_insertar(hermanos,hermano,nuevo);
    }

    return nuevo;
}

/**
 Elimina el nodo N de A.
 El elemento almacenado en el �rbol es eliminado mediante la funci�n fEliminar parametrizada.
 Si N es la ra�z de A, y tiene un s�lo hijo, este pasa a ser la nueva ra�z del �rbol.
 Si N es la ra�z de A, y a su vez tiene m�s de un hijo, finaliza retornando ARB_OPERACION_INVALIDA.
 Si N no es la ra�z de A y tiene hijos, estos pasan a ser hijos del padre de N, en el mismo orden y a partir de la posici�n que ocupa N en la lista de hijos de su padre.
**/
void a_eliminar(tArbol a, tNodo n, void (*fEliminar)(tElemento)){
    if(n==(a->raiz)){
        if(l_longitud((n->hijos))!=1)exit(ARB_OPERACION_INVALIDA);//Si no tiene hijos que hacer

        tNodo hijo = l_recuperar((n->hijos),l_primera((n->hijos)));
        fEliminar((n->elemento));
        l_destruir(&(n->hijos),fEliminar);
        if(n!=NULL)free(n);
        n=NULL;

        a->raiz=hijo;
    }else{
        tNodo padre = (n->padre);
        tNodo hermanos = (padre->hijos);
        tLista hijos = (n->hijos);
    }
}

