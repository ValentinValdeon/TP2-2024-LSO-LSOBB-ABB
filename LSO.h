#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED

#include "Prestadores.h"
#include <string.h>
#define MAX_prestadores 111
#define MasInfinito 99999999

typedef struct {
    Prestador prestador[MAX_prestadores];
    int contador;
} LSO;

void initLSO(LSO *lso) {
    lso->contador = 0;
    lso->prestador[0].dni = MasInfinito;
}

int localizarLSO(LSO *lista, int *pos, long dni_x) {
    if (lista->contador == 0) {
        return 0;
    }
    while (lista->prestador[(*pos)].dni< dni_x) {
        (*pos)++;
    }
    if (lista->prestador[(*pos)].dni == dni_x) {
        return 1;
    } else {
        return 0;
    }
}


int altaLSO(LSO *lista, Prestador prestador) {
    int pos = 0, i = 0;


    if (prestador.dni >= MasInfinito || lista->contador >= MAX_prestadores - 1) {
        return 2;
    }

    if (!(localizarLSO(lista, &pos, prestador.dni))) {
        for (i = (lista->contador+1); i >= pos; i--) {
            lista->prestador[i] = lista->prestador[i - 1];
        }
        lista->prestador[pos] = prestador;

        lista->contador++;

        //lista->prestador[lista->contador].dni = MasInfinito;
        return 1;
    } else {
        return 0;
    }
}

int bajaLSO(LSO *lista, long dni_x) {
    int pos = 0, resp = 0, i = 0;
    if (localizarLSO(lista, &pos, dni_x)) {
        printf("Prestador N %d \n", pos + 1);
        printf("DNI: %ld \n", lista->prestador[pos].dni);
        printf("Nombre y Apellido: %s\n", lista->prestador[pos].nombre_y_apellido);
        printf("Servicios: %s\n", lista->prestador[pos].servicios);
        printf("Domicilio: %s\n", lista->prestador[pos].domicilio);
        printf("Email: %s\n", lista->prestador[pos].mail);
        printf("Telefono: %s\n", lista->prestador[pos].telefono);
        printf("Desea eliminar este prestador? \n 1)Si\n 0)No\n Ingrese:");
        scanf("%d", &resp);
        if (resp == 1) {
            for (i = pos; i < lista->contador; i++) {
                lista->prestador[i] = lista->prestador[i + 1];
            }
            lista->contador--;
            //lista->prestador[lista->contador].dni = MasInfinito;
            return 1;
        } else {
            return 0;
        }
    }else{
        return 2;
    }
}

int modificarLSO(LSO *lista, long dni_x) {
    int pos = 0, fin = 0;
    char nombre_y_apellidoAux[80], serviciosAux[120], domicilioAux[80], mailAux[50], telefonoAux[30];

    if (localizarLSO(lista, &pos, dni_x)) {
        printf("*********Prestador N: %d \n", pos + 1);
        printf("***DNI: %ld \n", lista->prestador[pos].dni);
        printf("<1>Nombre y Apellido: %s\n", lista->prestador[pos].nombre_y_apellido);
        printf("<2>Servicios: %s\n", lista->prestador[pos].servicios);
        printf("<3>Domicilio: %s\n", lista->prestador[pos].domicilio);
        printf("<4>Email: %s\n", lista->prestador[pos].mail);
        printf("<5>Telefono: %s\n", lista->prestador[pos].telefono);
        printf("<6>Terminar modificaciones \n");
        printf("Que desea modificar <1-6> \n");
        scanf("%d", &fin);
        fflush(stdin);

        switch (fin) {
            case 1:
                system("cls");
                printf("Ingrese el nuevo nombre y apellido\n");
                scanf("%[^\n]s", nombre_y_apellidoAux);
                strcpy(lista->prestador[pos].nombre_y_apellido, nombre_y_apellidoAux);
                break;
            case 2:
                system("cls");
                printf("Ingrese el nuevo Servicio\n");
                scanf("%[^\n]s", serviciosAux);
                strcpy(lista->prestador[pos].servicios, serviciosAux);
                break;
            case 3:
                system("cls");
                printf("Ingrese el nuevo Domicilio\n");
                scanf("%[^\n]s", domicilioAux);
                strcpy(lista->prestador[pos].domicilio, domicilioAux);
                break;
            case 4:
                system("cls");
                printf("Ingrese el nuevo Email\n");
                scanf("%[^\n]s", mailAux);
                strcpy(lista->prestador[pos].mail, mailAux);
                break;
            case 5:
                system("cls");
                printf("Ingrese el nuevo Telefono\n");
                scanf("%[^\n]s", telefonoAux);
                strcpy(lista->prestador[pos].telefono, telefonoAux);
                break;
            case 6:
                system("cls");
                break;
            default:
                system("cls");
                printf("-------------------Opcion Incorrecta--------------------\n");
                printf("------Presione cualquier tecla para volver al menu------");
                getchar();
                break;
        }
        return 1;
    }
    return 0;
}

Prestador evocarLSO(LSO *lista, long dni_x, int *exito) {
    int pos = 0;
    *exito = localizarLSO(lista, &pos, dni_x);
    if (*exito) {
        return lista->prestador[pos];
    }
}


#endif // LSO_H_INCLUDED
