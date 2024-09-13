#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED


typedef struct {
    Prestador prestador[MAX_prestadores];
    int contador;
} LSO;

void initLSO(LSO *lso) {
    lso->contador = 0;
    lso->prestador[0].dni = MasInfinito;
}

int localizarLSO(LSO *lista, int *pos, long dni_x, int *costos) {
    if (lista->contador == 0) {
        return 0;
    }
    while (lista->prestador[(*pos)].dni< dni_x) {
        (*pos)++;
        (*costos)++;
    }

    if(lista->contador != 0 && (*pos) < lista->contador) (*costos)++;//Este celda es sumada ya que en el while no se contempla sumar la ultima celda consultada

    if (lista->prestador[(*pos)].dni == dni_x) {
        return 1;
    } else {
        return 0;
    }
}


int altaLSO(LSO *lista, Prestador prestador, int *corrimientos) {
    int pos = 0, i = 0;


    if (prestador.dni >= MasInfinito || lista->contador >= MAX_prestadores - 1) {
        return 2;
    }

    if (!(localizarLSO(lista, &pos, prestador.dni))) {
        for (i = (lista->contador+1); i >= pos; i--) {
            lista->prestador[i] = lista->prestador[i - 1];
            (*corrimientos)++;
        }
        lista->prestador[pos] = prestador;

        lista->contador++;

        //lista->prestador[lista->contador].dni = MasInfinito;
        return 1;
    } else {
        return 0;
    }
}

int bajaLSO(LSO *lista, Prestador p, int *corrimientos) {
    int pos = 0, i = 0;
    if (localizarLSO(lista, &pos, p.dni) && compararPrestador(p,lista->prestador[pos])) {
        for (i = pos; i < lista->contador; i++){
            lista->prestador[i] = lista->prestador[i + 1];
            (*corrimientos)++;
        }
        lista->contador--;
        return 1;
    }else{
        return 2;
    }
}

Prestador evocarLSO(LSO *lista, long dni_x, int *exito) {
    int pos = 0;
    *exito = localizarLSO(lista, &pos, dni_x);
    if (*exito) {
        return lista->prestador[pos];
    }
}


#endif // LSO_H_INCLUDED
