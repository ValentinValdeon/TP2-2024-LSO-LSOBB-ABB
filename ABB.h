#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include "Pila.h"


typedef struct ArbolABB{

   Nodo* raiz;
   Nodo* cursor;
   Nodo* padre;
   int cant;
} ArbolABB;

void initializeABB(ArbolABB *a){
    a->raiz=NULL;
    a->padre=NULL;
    a->cursor=NULL;
    a->cant=0;
}
void liberarABB(Nodo* nodo) {
    if (nodo == NULL) {
        return;
    }
    liberarABB(nodo->hijoIzq);
    liberarABB(nodo->hijoDer);
    free(nodo);
}

int localizacionABB(ArbolABB* arbol, long dni_x, float *costosL){
    float costosAux = 0.0;
    (*arbol).cursor = arbol->raiz;
    (*arbol).padre = arbol->raiz;

    while((arbol->cursor != NULL) && (  arbol->cursor->p.dni != dni_x)) {

        if(arbol->cursor->p.dni > dni_x ){
            (*arbol).padre = arbol->cursor;
            (*arbol).cursor = arbol->cursor->hijoIzq;
        }  else {
            (*arbol).padre = arbol->cursor;
            (*arbol).cursor = arbol->cursor->hijoDer;
        }
        costosAux += 2;

    }

    if(arbol->cursor != NULL){
        costosAux += 1 ;
        (*costosL) = costosAux;
        return 1;
    } else {

        (*costosL) = costosAux;
        return 0;
    }

}

int altaABB(ArbolABB *arbol,int *cant , Prestador p, float *costosA){

    float costosAux = 0.0, costos = 0.0;
    Nodo *auxiliar = (Nodo*)malloc(sizeof(Nodo));
    if (auxiliar == NULL){
        return 2; //Memoria insuficiente
    }else {


        if(localizacionABB(arbol, p.dni, &costos) == 0){

            auxiliar->p = p;
            auxiliar->hijoDer = NULL;
            auxiliar->hijoIzq = NULL;


   (*cant)++;
            arbol->cant++;


            if(arbol->raiz == NULL){

                arbol->raiz = auxiliar;


                costosAux +=0.5;
                (*costosA) = costosAux;

                return 1;
            }
            else if(arbol->padre->p.dni > auxiliar->p.dni ){
                arbol->padre->hijoIzq = auxiliar;
            } else {
                arbol->padre->hijoDer = auxiliar;
            }

            costosAux += 0.5;
            (*costosA)=costosAux;

            return 1;
        } else{
            free((void*)auxiliar);
            return 0;
        }
    }

}

int bajaABB(ArbolABB* arbol,int *cant,Prestador p,  float *costosB){


    int resp = 0;
    float costosAux =0.0, costos = 0.0;
    if(localizacionABB(arbol, p.dni, &costos) == 1){
            if(compararPrestador(p,arbol->cursor->p))
            {

                resp=1;
            }else{
                resp=0;
            }

              (*cant)--;
            arbol->cant--;
        }
        if (resp == 1){//CASO 1: NODO SIN HIJOS
        if ((arbol->cursor->hijoIzq == NULL) && (arbol->cursor->hijoDer == NULL)){
            if (arbol->cursor == arbol->raiz){
                free((void*)arbol->raiz);
                arbol->raiz = NULL;

            }else if(arbol->cursor->p.dni > arbol->padre->p.dni){
                arbol->padre->hijoDer = NULL ;
                free((void*)arbol->cursor);
                }
                else{
                    arbol->padre->hijoIzq = NULL ;
                    free((void*)arbol->cursor);
                }
            costosAux += 0.5;
        }else if ((arbol->cursor->hijoIzq == NULL) && (arbol->cursor->hijoDer != NULL) ){//CASO 2: TIENE UN HIJO DERECHO
            if(arbol->cursor == arbol->raiz){
                arbol->raiz = arbol->cursor->hijoDer;
                free((void*)arbol->cursor);
            }
            else if(arbol->cursor->p.dni > arbol->padre->p.dni){
                arbol->padre->hijoDer = arbol->cursor->hijoDer;
                free((void*)arbol->cursor);
                }
            else {
                arbol->padre->hijoIzq = arbol->cursor->hijoDer;
                free((void*)arbol->cursor);
            }
            //en este caso tambien hay una sola modificacion de punteros
            costosAux += 0.5;
        }else if ((arbol->cursor->hijoIzq!= NULL) && (arbol->cursor->hijoDer == NULL)) {//CASO 3: TIENE UN HIJO IZQUIERDO
            if(arbol->cursor == arbol->raiz){
                arbol->raiz = arbol->cursor->hijoIzq;
                free((void*)arbol->cursor);
            } else if(arbol->cursor->p.dni > arbol->padre->p.dni){
                arbol->padre->hijoDer = arbol->cursor->hijoIzq;
                free((void*)arbol->cursor);
            }
            else {
                    arbol->padre->hijoIzq = arbol->cursor->hijoIzq;
                    free((void*)arbol->cursor);
            }
            costosAux += 0.5;
        }else if ((arbol->cursor->hijoIzq != NULL) && (arbol->cursor->hijoDer != NULL)){ //CASO 4: TIENE HIJO IZQUIERDO Y DERECHO

            Nodo* aux = arbol->cursor;
            Nodo* auxPadre = aux;
            aux = aux->hijoIzq;
            while (aux->hijoDer !=NULL){
                auxPadre = aux;
                aux = aux->hijoDer;
            }
            if (auxPadre != arbol->cursor){
                auxPadre->hijoDer = aux->hijoIzq;
            }else{
                auxPadre->hijoIzq = aux->hijoIzq;
            }

            if (arbol->cursor == arbol->raiz){
                arbol->raiz->p = aux->p;
            }
            else {
                arbol->cursor->p = aux->p;
            }

            costosAux +=1.5 ;
            free((void*)aux);
            aux = NULL;
        }
            (*costosB) = costosAux;


            return 1; //lo encontro
        }else{
            return 0;
        }  //no lo encontro
    }

int evocacionABB(ArbolABB* arbol,long dni_x, Prestador *p, float* costos){
    float costosAux=0.0;
    if(localizacionABB(arbol, dni_x, &costosAux) == 1){
        p->dni = arbol->cursor->p.dni;
        strcpy(arbol->cursor->p.nombre_y_apellido, p->nombre_y_apellido);
        strcpy(arbol->cursor->p.mail, p->mail);
        strcpy(arbol->cursor->p.domicilio, p->domicilio);
        strcpy(arbol->cursor->p.servicios, p->servicios);
        strcpy(arbol->cursor->p.telefono, p->telefono);
        (*costos) = costosAux;
        return 1;
    } else {
        (*costos)=costosAux;
        return 0;
    }
}




void imprimirNodo(Nodo* a) {
    if (a == NULL) {
        return;
    }

    MostrarPrestador(a->p);

    if (a->hijoIzq != NULL) {
        printf("\n---------------------------------------------------------------");
        printf("\nEl DNI de su hijo izquierdo es: %ld", a->hijoIzq->p.dni);
    } else {
        printf("\n---------------------------------------------------------------");
        printf("\nNo tiene hijo izquierdo.");
    }

    if (a->hijoDer != NULL) {
        printf("\n---------------------------------------------------------------");
        printf("\nEl DNI de su hijo derecho es: %ld", a->hijoDer->p.dni);
    } else {
        printf("\n---------------------------------------------------------------");
        printf("\nNo tiene hijo derecho.");
    }

    printf("\n---------------------------------------------------------------");
    getchar();
}


void preOrdenIterativo(Nodo* raiz) {
    if (raiz == NULL) {
        return;
    }

    Pila* pila = NULL;
    apilar(&pila, raiz);

    while (pila != NULL) {
        Nodo* actual = desapilar(&pila);


        imprimirNodo(actual);

        //  hijo derecho para que se procese después del izquierdo
        if (actual->hijoDer != NULL) {
            apilar(&pila, actual->hijoDer);
        }

        //  hijo izquierdo
        if (actual->hijoIzq != NULL) {
            apilar(&pila, actual->hijoIzq);
        }
    }
}




#endif // ABB_H_INCLUDED
