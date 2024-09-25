#ifndef LSOBB_H_INCLUDED
#define LSOBB_H_INCLUDED
#include <math.h>
#define MAX_prestadoresLSBB 110

///TRISECCION, LIM IZQ IN, LIM DER EXC, SEG IZQ
int localizarLSOBT(long dniX, Prestador P[], int *pos, int cant, int *celdasConsul)
{
    (*pos)=0;

    if(cant == 0)//lista vacia
    {
        return 0;
    }

    int li, ls, m;
    li = 0;
    ls = cant;

    m = (li + ls )/ 2;

    while(li<ls && P[m].dni != dniX)
    {
        (*celdasConsul)++;
        if (dniX > P[m].dni)
        {
            li = m+1;
        }
        else
        {
            ls = m;
        }
        m = (li + ls )/2;
    }

    (*pos) = m;
    if(li<ls)
    {
        (*celdasConsul)++;
        return 1;
    }
    else
    {
        return 0;
    }
}

int altaLSOBT(Prestador p, Prestador P[], int *cant, int *cor)
{
    int pos, celdasConsul=0;
    int cantaux;
    if((*cant)==MAX_prestadoresLSBB)//lista llena
    {
        return 2;
    }
    if(localizarLSOBT(p.dni,P,&pos,*cant,&celdasConsul)==0)
    {
        if (pos < MAX_prestadoresLSBB-1)
        {
            cantaux = (*cant);
            while (cantaux > pos)
            {
                P[cantaux] = P[cantaux - 1];
                cantaux--;
                (*cor)++;
            }
            P[pos] = p;
            (*cant)++;
            return 1;
        }
    }
    else
    {
        return 0;
    }
    return 0;
}

int bajaLSOBT(Prestador p, Prestador P[],int *cant, int *cor)
{
    int pos, celdasConsul=0;
    if(localizarLSOBT(p.dni,P,&pos,*cant,&celdasConsul)==1 && compararPrestador(p,P[pos]))
    {
        while(pos<(*cant)-1)
        {
            P[pos] = P[pos + 1];
            pos++;
            (*cor)++;
        }
        (*cant)--;
        return 1;
    }
    else
        return 0;
}

int evocacionLSOBT(int cant, Prestador P[], long dniX, Prestador *pAux, int *celdasConsul)
{
    int pos = 0;

    if(localizarLSOBT(dniX,P,&pos,cant,celdasConsul))
    {
        *pAux = P[pos];
        return 1;
    }

    return 0;
}



#endif // LSOBB_H_INCLUDED
