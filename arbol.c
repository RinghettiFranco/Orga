#include <C:\Users\fede\Documents\GitHub\Orga\arbol.h>
#include <C:\Users\fede\Documents\GitHub\Orga\lista.h>


#include <stdlib.h>

typedef struct nodo * tNodo;
typedef struct arbol * tArbol;

void (*fElim)(tElemento) = NULL;

void fNoEliminar(){}

void fSiEliminar(tElemento n){
    fElim(((tNodo) n)->elemento);
    ((tNodo)n)->padre=NULL;
    l_destruir(&(((tNodo)n)->hijos),fElim);
    free(n);
    n=NULL;
}
int nietos(tLista l){
    int i=0;
    tPosicion actual = l_primera(l);
    tNodo n = NULL;
    tLista h = NULL;
    while(actual!=l_fin(l) && i==0){
        n = l_recuperar(l,actual);
        h = (n->hijos);
        i+=l_longitud(h);
        actual = l_siguiente(l,actual);
    }
    return i;
}


void vaciar(tNodo n,void (*fEliminar)(tElemento)){
    tLista sons = (n->hijos);
    if(nietos(sons)>0){
        tPosicion actual = l_primera(sons);
        while(actual!=l_fin(sons)){
            vaciar(l_recuperar(sons,actual),fEliminar);
            actual = l_siguiente(sons,actual);
        }
    }
    l_destruir(&(n->hijos),fEliminar);
    (n->padre)=NULL;
    fElim((n->elemento));
    free(n);
    n=NULL;
}


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
    if(a==NULL)exit(ARB_POSICION_INVALIDA);
    if((a->raiz)!=NULL)exit(ARB_OPERACION_INVALIDA);
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
    if(a==NULL)exit(ARB_OPERACION_INVALIDA);
    if(np==NULL)exit(ARB_OPERACION_INVALIDA);
    if(nh==NULL)exit(ARB_OPERACION_INVALIDA);
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
    if(a==NULL)exit(ARB_OPERACION_INVALIDA);
    if(n==NULL)exit(ARB_OPERACION_INVALIDA);
    if(n==(a->raiz)){
        if(l_longitud((n->hijos))>1)exit(ARB_OPERACION_INVALIDA);//Si no tiene hijos que hacer

        if(l_longitud((n->hijos))==1){
            tNodo hijo = l_recuperar((n->hijos),l_primera((n->hijos)));
            fEliminar((n->elemento));
            l_destruir(&(n->hijos),&fNoEliminar);
            if(n!=NULL)free(n);
            n=NULL;
            a->raiz=hijo;
        }else{
            fEliminar((n->elemento));
            l_destruir(&(n->hijos),fEliminar);
            if(n!=NULL)free(n);
            n=NULL;
        }
    }else{
        tNodo father = (n->padre);
        tLista brothers = (father->hijos);
        tLista sons = (n->hijos);

        tPosicion posN = l_primera(brothers);
        while(posN!=l_fin(brothers) && n!=l_recuperar(brothers,posN))posN=l_siguiente(brothers,posN);
        tPosicion rBro = l_siguiente(brothers,posN);

        tPosicion actual = l_primera(sons);
        while(actual!=l_fin(brothers)){
            tNodo n = l_recuperar(sons,actual);
            l_insertar(brothers,rBro,n);
            (n->padre)=father;
        }

        l_eliminar(brothers,posN,&fNoEliminar);

        fEliminar((n->elemento));
        l_destruir(&(n->hijos),&fNoEliminar);
        (n->padre)=NULL;
        free(n);
        n=NULL;
    }
}

/**
 Destruye el �rbol A, eliminando cada uno de sus nodos.
 Los elementos almacenados en el �rbol son eliminados mediante la funci�n fEliminar parametrizada.
**/
void a_destruir(tArbol * a, void (*fEliminar)(tElemento)){
    fElim = fEliminar;
    vaciar(((*a)->raiz),fSiEliminar);
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

 void llenar (tArbol sa,tNodo nuevo, tNodo viejo){
tLista hijosviejo=viejo->hijos;
tPosicion actual=l_primera(hijosviejo);
while(actual!= l_fin(hijosviejo))
    {tNodo hv=l_recuperar(hijosviejo,actual);
     a_insertar(sa,nuevo,l_recuperar(nuevo->hijos,l_fin(nuevo->hijos)),hv->elemento);
     tNodo hijoNuevo=l_recuperar(nuevo->hijos,l_ultima(nuevo->hijos));
     llenar(sa,hijoNuevo,hv);
    }

}


/**
 Inicializa un nuevo �rbol en *SA.
 El nuevo �rbol en *SA se compone de los nodos del sub�rbol de A a partir de N.
 El subarbol de A a partir de N debe ser eliminado de A.
**/
void a_sub_arbol(tArbol a, tNodo n, tArbol * sa){
crear_arbol(sa);
crear_raiz(*sa,n->elemento);
tNodo rNueva= a_raiz(*sa);
llenar(*sa,n,rNueva);
vaciar(n,fSiEliminar);
}






