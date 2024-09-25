#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Estructura para un nodo de la pila
typedef struct NodoP {
    Prestador prestador;
    struct Nodo* siguiente;
} NodoP;

// Función para crear un nuevo nodo
NodoP* crearNodo(Prestador prestador) {
    NodoP* nuevoNodo = (NodoP*)malloc(sizeof(NodoP));
    if (nuevoNodo == NULL) {
        printf("Error de memoria\n");
        exit(1);
    }
    nuevoNodo->prestador = prestador;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

// Función para apilar (push) un elemento
void push(NodoP** tope, Prestador prestador) {
    NodoP* nuevoNodo = crearNodo(prestador);
    nuevoNodo->siguiente = *tope;  // El nuevo nodo apunta al antiguo tope
    *tope = nuevoNodo;  // El nuevo nodo se convierte en el tope
}

// Función para desapilar (pop) un elemento
Prestador pop(NodoP** tope) {
    if (*tope == NULL) {
        printf("Pila vacía\n");
        return;
    }
    NodoP* temp = *tope;  // Almacena el nodo a eliminar
    Prestador prestador = temp->prestador;
    *tope = (*tope)->siguiente;  // El tope apunta al siguiente nodo
    free(temp);  // Libera la memoria del nodo eliminado
    return prestador;
}

// Función para ver el tope de la pila sin desapilarlo
Prestador peek(NodoP* tope) {
    if (tope == NULL) {
        printf("Pila vacía\n");
        return;
    }
    return tope->prestador;
}



#endif // PILA_H_INCLUDED
