#include <C:\Users\fede\Documents\GitHub\Orga\lista.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct celda* tLista;
typedef struct celda* tPosicion;
typedef void * tElemento;

void mostrar(tLista l){

    if(l==NULL){
        printf("La lista no existe.");
        exit(0);
    }

    int cant=l_longitud(l);
    tPosicion p =l_primera(l);
    printf("L = {");
    for(int i=0;i<cant;i++){
        tElemento e = l_recuperar(l,p);
        printf("%i",*(int*)e);
        p = l_siguiente(l,p);
        if((i+1)!=cant)printf("-");
    }
    printf("} - Cantidad de elementos: %i \n",cant);
}

void eliminarEnteros(tElemento e){
    free(e);
    e=NULL;
}

void casos_simples(tLista lista){
    printf("Funcionamiento basico (Situaciones que no llevan a errores.) \n");
    printf("\n");

    /**Inserto elementos.**/
    printf("PRUEBA INSERCION: \n");
    int value1,value2,value3;
    tElemento e;

    printf("Inserto un 1 en la lista vacia => \n");
    value1=1;e=&value1;
    l_insertar(lista,l_primera(lista),e);
    mostrar(lista);
    e=NULL;

    printf("Inserto un 3 luego del 1 => \n");
    value3=3;e=&value3;
    l_insertar(lista,l_fin(lista),e);
    mostrar(lista);
    e=NULL;

    printf("Inserto un 2 luego del 1 => \n");
    value2=2;e=&value2;
    l_insertar(lista,l_ultima(lista),e);
    mostrar(lista);
    e=NULL;
    printf("\n");

    /**Elimino los elementos.**/
    printf("PRUEBA ELIMINACION: \n");
    printf("Elimino el 3 => \n");
    l_eliminar(lista,l_ultima(lista),&eliminarEnteros);
    mostrar(lista);

    printf("Elimino el 2 => \n");
    l_eliminar(lista,l_siguiente(lista,l_primera(lista)),&eliminarEnteros);
    mostrar(lista);

    printf("Elimino el 1 => \n");
    l_eliminar(lista,l_primera(lista),&eliminarEnteros);
    mostrar(lista);
    printf("\n");

    /**Retorno de los elementos.**/
    printf("PRUEBA DE RETORNOS VALIDOS: \n");
    printf("Regenero la lista tal que L={1-2-3} con 3 elementos. \n");

    value1=1;e=&value1;
    l_insertar(lista,l_primera(lista),e);
    e=NULL;
    value3=3;e=&value3;
    l_insertar(lista,l_fin(lista),e);
    e=NULL;
    value2=2;e=&value2;
    l_insertar(lista,l_ultima(lista),e);
    mostrar(lista);
    e=NULL;

    printf("Retorno el primero: ");
    printf("%i \n",*(int*)l_recuperar(lista,l_primera(lista)));

    printf("Retorno el ultimo: ");
    printf("%i \n",*(int*)l_recuperar(lista,l_ultima(lista)));

    tPosicion segundo = l_siguiente(lista,l_primera(lista));

    printf("Retorno el siguiente al primero: ");
    printf("%i \n",*(int*)l_recuperar(lista,segundo));

    printf("Retorno el siguiente al segundo: ");
    printf("%i \n",*(int*)l_recuperar(lista,l_siguiente(lista,segundo)));

    printf("Retorno el anterior al segundo: ");
    printf("%i \n",*(int*)l_recuperar(lista,l_anterior(lista,segundo)));

    printf("Retorno el anterior al ultimo: ");
    printf("%i \n",*(int*)l_recuperar(lista,l_anterior(lista,l_ultima(lista))));
    printf("\n");

    /**Destruccion de la lista**/
    printf("PRUEBA DE DESTRUCCION DE LA LISTA: \n");
    printf("Se destruira la lista L \n");
    l_destruir(&lista,&eliminarEnteros);
    mostrar(lista);
}

void casos_particulares(tLista lista){
    printf("Funcionamiento particular (Situaciones que  llevan a errores o a casos especiales.) \n");
    printf("\n");

    printf("Para verificar que la funcion eliminar si recibe fin(L) llega a situacion de LST_POSICION_INVALIDA presione 1. \n");
    printf("Para verificar que la funcion recuperar si recibe fin(L) llega a situacion de LST_POSICION_INVALIDA presione 2. \n");
    printf("Para verificar que al solicitar el siguiente de fin(L) se llega a situacion de LST_NO_EXISTE_SIGUIENTE presione 3. \n");
    printf("Para verificar que al solicitar el anterior de fin(L) se llega a situacion de LST_NO_EXISTE_ANTERIOR presione 4. \n");
    printf("Para verificar que al tratar de insertar un elemento NULL se llega a situacion de LST_ELEMENTO_NULO presione 5. \n");
    printf("Para verificar que cualquier operacion que reciba una posicion nula llega a una situacion de LST_POSICION_INVALIDA presione 6. \n");
    printf("Para verificar que cualquier operacion que reciba una lista nula llega a una situacion de LST_POSICION_INVALIDA presione 7. \n");
    printf("Para verificar que solicitar el primero de una lista vacia es fin(L) presione 8. \n");
    printf("Para verificar que solicitar el ultimo de una lista vacia es fin(L) presione 9. \n");

    printf("\n");
    printf("(NOTESE: para simplificar, 6 y 7 solo se verificaran sobre la operacion insertar, el resto se comporta igual.) \n");
    printf("\n");

    int choice;
    printf("Eleccion: ");
    scanf("%i",&choice);
    printf("\n");



    int value; tElemento e;
    if(choice==1){
        printf("Verificar que la funcion eliminar si recibe fin(L) llega a situacion de LST_POSICION_INVALIDA. \n");
            l_eliminar(lista,l_fin(lista),&eliminarEnteros);
    }
    else if (choice==2)
        {printf("Verificar que la funcion recuperar si recibe fin(L) llega a situacion de LST_POSICION_INVALIDA. \n");
        l_recuperar(lista,l_fin(lista));
     }
    else if (choice==3)
    {
        printf("Verificar que al solicitar el siguiente de fin(L) se llega a situacion de LST_NO_EXISTE_SIGUIENTE. \n");
            l_siguiente(lista,l_fin(lista));
    }
    else if (choice==4)
    {printf("Verificar que al solicitar el anterior de primera se llega a situacion de LST_NO_EXISTE_SIGUIENTE. \n");
            value=1;e=&value;
            l_insertar(lista,l_primera(lista),e);
            l_anterior(lista,l_primera(lista));
    }
    else if(choice==5)
    {
        printf("Verificar que al tratar de insertar un elemento NULL se llega a situacion de LST_ELEMENTO_NULO. \n");
            e=NULL;
            l_insertar(lista,l_primera(lista),e);
    }
    else if(choice==6)
    {
    printf("Verificar que cualquier operacion que reciba una posicion nula llega a una situacion de LST_POSICION_INVALIDA. \n");
    value=1;e=&value;
    tPosicion p=NULL;
    l_insertar(lista,p,e);
    }
    else if(choice==7)
    { printf("Verificar que cualquier operacion que reciba una lista nula llega a una situacion de LST_POSICION_INVALIDA. \n");
            value=1;e=&value;
            tLista ex=NULL;
            l_insertar(ex,l_primera(lista),e);
    }
    else if(choice==8)
    {
        printf("Verificar que solicitar el primero de una lista vacia es fin(L)=NULL. \n");
            mostrar(lista);
            if(l_primera(lista)==lista)printf("El primero de la lista es FIN(L).");
    }
   else if(choice==9)
    {
        printf("Verificar que solicitar el ultimo de una lista vacia es fin(L)=NULL. \n");
            mostrar(lista);
            if(l_primera(lista)==lista)printf("El ultimo de la lista es FIN(L).");
    }




}

// \n

int main(){
    printf("Lista de enteros: TEST. \n");


    /**Creo la lista y la muestro.**/
    tLista lista;
    crear_lista(&lista);
    printf("Se creo la lista. \n");
    mostrar(lista);
    printf("\n");

    printf("Para chequear el funcionamiento basico presione 1. \n");
    printf("Para chequear el funcionamiento casos de prueba particulares presione 2. \n");
    printf("Para saltear el proceso presione enter. \n");
    int choice;
    printf("Eleccion: ");
    scanf("%d",&choice);
    printf("\n");
    if(choice==1){
        casos_simples(lista);
    }else{
        if(choice==2)casos_particulares(lista);
    }

}
