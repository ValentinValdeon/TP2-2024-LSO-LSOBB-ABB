#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct nodo{
    Prestador p;
    struct nodo *hijoDer;
    struct nodo *hijoIzq;
} Nodo;

typedef struct Pila {
    Nodo* nodo;
    struct Pila* siguiente;
} Pila;

Pila* crearNodoPila(Nodo* nodo) {
    Pila* nuevoNodo = (Pila*)malloc(sizeof(Pila));
    nuevoNodo->nodo = nodo;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

void apilar(Pila** cima, Nodo* nodo) {
    Pila* nuevoNodo = crearNodoPila(nodo);
    nuevoNodo->siguiente = *cima;
    *cima = nuevoNodo;
}

Nodo* desapilar(Pila** cima) {
    if (*cima == NULL) {
        return NULL;
    }
    Pila* temporal = *cima;
    *cima = (*cima)->siguiente;
    Nodo* nodoDesapilado = temporal->nodo;
    free(temporal);
    return nodoDesapilado;
}

Nodo* verCima(Pila* cima) {
    if (cima == NULL) {
        return NULL;
    }
    return cima->nodo;
}

#endif // PILA_H_INCLUDED
