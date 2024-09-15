#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED

#define MasInfinito 99999999
#define MAX_prestadoresLSO 111
///RETURNS-> 1:True, 0:False, 2:lista llena o vacia o paso el +infinito, 3:elmento existente

typedef struct {
    Prestador prestador[MAX_prestadoresLSO];
    int contador;
} LSO;

void initLSOMasInfi(Prestador P[]) {
    P[0].dni = MasInfinito;
}

int localizarLSO(long dniX, Prestador P[], int *pos, int cant,int *celdasConsul)
{
    (*pos) = 0;
    if(cant == 0)//lista vacia
    {
        return 0;
    }
    while(dniX > P[(*pos)].dni)
    {
        (*celdasConsul)++;
        (*pos) ++;
    }

    if(cant!=0 && (*pos) < cant) (*celdasConsul)++; //Este celda es sumada ya que en el while no se contempla sumar la ultima celda consultada

    if((*pos)<cant && dniX == P[(*pos)].dni) return 1;
    else return 0;
}

int altaLSO(Prestador p, Prestador P[], int *cant, int *cor)
{
    int pos=0, i;
    int celdasConsul=0;

    if(p.dni >= MasInfinito ||(*cant)==MAX_prestadoresLSO-1)//lista llena o dni fuera del lim
    {
        return 2;
    }
    else
    {
        if(localizarLSO(p.dni, P, &pos, *cant, &celdasConsul))
        {
            if(compararPrestador(p,P[pos])) return 3; // La nupla está repetida
            else return 2;
        }
        else
        {
            for(i=(*cant+1); i>=pos; i--)
            {
                P[i]=P[i-1];
                (*cor)++;
            }

            P[pos]=p;
            (*cant)++;
            return 1;
        }
    }
}

int bajaLSO(Prestador p, Prestador P[],int *cant, int *cor)
{
    int pos=0, i;
    int celdasConsul=0;

    if(p.dni >= MasInfinito ||(*cant)==0)//lista vacia o dni fuera del lim
    {
        return 2;
    }
    else
    {
        if(localizarLSO(p.dni, P, &pos, *cant, &celdasConsul) && compararPrestador(p,P[pos]))
        {
            for(i=pos ; i<(*cant); i++)
            {
                P[i]=P[i+1];

                (*cor)++;
            }
            (*cant)--;
            return 1;
        }
        else return 0;
    }

}

int evocacionLSO(int cant, Prestador P[], long dniX, Prestador *p, int *celdasConsul)
{
    int pos = cant-1;

    if(dniX >= MasInfinito || cant == 0)//lista vacia o dni fuera del lim
    {
        return 2;
    }
    else
    {
       if(localizarLSO(dniX,P,&pos,cant,celdasConsul))
        {
            *p = P[pos];
            return 1;
        }
    }
    return 0;
}
#endif // LSO_H_INCLUDED
