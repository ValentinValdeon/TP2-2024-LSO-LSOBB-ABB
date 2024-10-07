#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <ctype.h>
#include "Prestadores.h"
#include "LSO.h"
#include "LSOBB.h"
#include "ABB.h"
#include <string.h>

///Analisis de resultados
// Lista secuencial ordenada con terminacion por contenido
// Costos maximos ->    Evocacion Exitosa= 98         Evocacion Fracaso= 83         Alta= 108      Baja= 97
// Costos Medios  ->    Evocacion Exitosa= 36.79      Evocacion Fracaso= 31.89      Alta= 27.71    Baja= 30.59

// Lista secuencial ordenada con busqueda por triseccion
// Costos maximos ->    Evocacion Exitosa= 7          Evocacion Fracaso= 7          Alta= 107      Baja= 96
// Costos Medios  ->    Evocacion Exitosa= 5.32       Evocacion Fracaso= 5.76       Alta= 26.71    Baja= 29.59

// Arbol binario de busqueda
// Costos maximos ->    Evocacion Exitosa= 13.00      Evocacion Fracaso= 26.00      Alta= 0.50     Baja= 1.50
// Costos Medios  ->    Evocacion Exitosa= 6.14       Evocacion Fracaso= 6.44       Alta= 0.50     Baja= 0.83

/*
Lista secuencial ordenada con terminación por contenido
Desventajas: Tiene los costos máximos más altos para evocación exitosa y de fracaso. Esto sugiere que este método es el más ineficiente en términos de la cantidad máxima de celdas consultadas cuando se realizan búsquedas exitosas o fracasadas.
Ventajas: Los costos medios de las altas (27.71) y bajas (30.59) no son excesivamente altos, aunque siguen siendo mayores en comparación con otras estructuras.


Lista secuencial ordenada con búsqueda por trisección
Ventajas: Los costos máximos y medios para evocaciones exitosas y fracasadas son extremadamente bajos. Esto sugiere que la búsqueda por trisección es mucho más eficiente para búsquedas que las otras estructuras.
Desventajas: Aunque la eficiencia de búsqueda es excelente, los costos máximos para operaciones de alta (107) y baja (96) son bastante altos, lo que puede indicar que esta estructura no es la más eficiente para la inserción o eliminación de elementos.


Árbol binario de búsqueda
Ventajas: Es mucho mas eficiente para las operaciones de alta y baja. Esto hace que el árbol binario de búsqueda sea una buena opción para mantener la estructura actualizada con inserciones y eliminaciones frecuentes.
Desventajas: Aunque los costos para las búsquedas no son los más bajos (como por ejemplo, la búsqueda por trisección es más eficiente), el árbol binario de búsqueda sigue siendo razonablemente eficiente para la búsqueda con costos relativamente bajos tanto en evocaciones exitosas como evocaciones fracasadas.

Viendo las 3 estructuras con sus resultados podemos decir que: para evocaciones la mejor es la LSOBT ya que posee costos muy bajos de localizacion,
la mejor en altas y bajas seria el ABB teniendo costos infimos a comparacion de las otras 2
Dejandonos con la peor de las 3 que es la LSO (terminacion por contenido) esta posee los costos mas altos en todas las operaciones.
*/

void gotoxy(int x, int y)
{
    printf("%c[%d;%df", 0x1B, y, x);
}


int compararEstructuras(Prestador LSO[], int *cantLSO,Prestador LSOBT[], ArbolABB *ABB , int *cantLSOBT, int *cantABB)
{

    FILE* fp = fopen("Operaciones-Prestadores.txt", "r");
    Prestador p, pAux;
    long dniX=0;
    int operacion, i, LSOfallos=0;


    (*cantLSO)=0;
    (*cantLSOBT)=0;
    (*cantABB)=0;
    // Alta - Baja - Evocacion - SumaAlta - SumaBaja - SumaEvo - Maximo


    int altaLS=0, bajaLS=0, evoLS=0, maxAltaLS=0, maxBajaLS=0, maxEvoLSF=0, maxEvoLSE=0;
    float sumaAltaLS=0, sumaBajaLS=0, sumaEvoLSF=0, sumaEvoLSE=0;

    int altaLSBT=0, bajaLSBT=0, evoLSBT=0, maxAltaLSBT=0, maxBajaLSBT=0, maxEvoLSBTF=0, maxEvoLSBTE=0;
    float sumaAltaLSBT=0, sumaBajaLSBT=0, sumaEvoLSBTF=0, sumaEvoLSBTE=0;

    float altaAB=0.0, bajaAB=0.0, evoABB=0.0, maxAltaABB=0.0, maxBajaABB=0.0, maxEvoABBF=0.0, maxEvoABBE=0.0;
    float sumaAltaABB=0, sumaBajaABB=0, sumaEvoABBF=0, sumaEvoABBE=0;

    int cantAltaLSO=0,cantAltaLSOBT=0,cantAltaABB=0;
    int cantBajaLSO=0,cantBajaLSOBT=0,cantBajaABB=0;
    int cantEvoELSO=0,cantEvoELSOBT=0,cantEvoEABB=0;
    int cantEvoFLSO=0,cantEvoFLSOBT=0,cantEvoFABB=0;

    if(fp==NULL)
    {
        printf("No se encontro el archivo");
        return -1;
    }
    else
    {

        while(!feof(fp))
        {
            fscanf(fp, "%d", &operacion);

            if(operacion==1 || operacion==2)
            {
                fscanf(fp," %ld", &(p.dni));

                fscanf(fp," %[^\n]", p.nombre_y_apellido);
                fscanf(fp," %[^\n]", p.servicios);
                fscanf(fp," %[^\n]", p.domicilio);
                fscanf(fp," %[^\n]", p.mail);
                fscanf(fp," %[^\n]", p.telefono);

                for(i=0; i<81; i++)
                {
                    p.nombre_y_apellido[i] = toupper(p.nombre_y_apellido[i]);
                }
                for(i=0; i<121; i++)
                {
                    p.servicios[i] = toupper(p.servicios[i]);
                }
                for(i=0; i<81; i++)
                {
                    p.domicilio[i] = toupper(p.domicilio[i]);
                }
                for(i=0; i<51; i++)
                {
                    p.mail[i] = toupper(p.mail[i]);
                }
                for(i=0; i<31; i++)
                {
                    p.telefono[i] = toupper(p.telefono[i]);
                }

                if(operacion==1)
                {
                    if(p.dni>MasInfinito){//este es el control para que cuando supere el +inf no realice ninguna de las operaciones de LSO

                        LSOfallos++;

                    }else{
                    //ALTA LSO
                        if(altaLSO(p, LSO, cantLSO, &altaLS)==1)
                        {
                            // Suma para sacar la media
                            sumaAltaLS = sumaAltaLS + altaLS;

                            // Calcular el maximo costo
                            if(altaLS>maxAltaLS) maxAltaLS = altaLS;

                            cantAltaLSO++;
                        }
                    }

                    //ALTA LSOBT
                    if(altaLSOBT(p, LSOBT, cantLSOBT, &altaLSBT)==1)
                    {
                        // Suma para sacar la media
                        sumaAltaLSBT = sumaAltaLSBT + altaLSBT;

                        // Calcular el maximo costo
                        if(altaLSBT>maxAltaLSBT) maxAltaLSBT = altaLSBT;

                        cantAltaLSOBT++;
                    }


                     //ALTA ABB
                    if(altaABB(ABB,cantABB, p, &altaAB)==1)
                    {
                        // Suma para sacar la media
                        sumaAltaABB = sumaAltaABB + altaAB;

                        // Calcular el maximo costo
                        if(altaAB>maxAltaABB) maxAltaABB = altaAB;

                        cantAltaABB++;
                    }

                    //Incializar nuevamente

                    altaLS = 0;
                    altaLSBT = 0;
                    altaAB = 0;

                }
                else
                {
                    if(p.dni>MasInfinito){

                        LSOfallos++;

                    }else{
                        //BAJA LSO
                        if(bajaLSO(p, LSO, cantLSO, &bajaLS)==1)
                        {
                            // Suma para sacar la media
                            sumaBajaLS = sumaBajaLS + bajaLS;

                            // Calcular el maximo costo
                            if(bajaLS>maxBajaLS) maxBajaLS = bajaLS;

                            cantBajaLSO++;
                        }
                    }
                    //BAJA LSOBT
                    if(bajaLSOBT(p, LSOBT, cantLSOBT, &bajaLSBT)==1)
                    {
                        // Suma para sacar la media
                        sumaBajaLSBT = sumaBajaLSBT + bajaLSBT;

                        // Calcular el maximo costo
                        if(bajaLSBT>maxBajaLSBT) maxBajaLSBT = bajaLSBT;

                        cantBajaLSOBT++;
                    }


                        //BAJA ABB
                    if(bajaABB(ABB, cantABB,p, &bajaAB)==1)
                    {
                        // Suma para sacar la media
                        sumaBajaABB = sumaBajaABB + bajaAB;

                        // Calcular el maximo costo
                        if(bajaAB>maxBajaABB) maxBajaABB = bajaAB;

                        cantBajaABB++;
                    }
                    //Incializar nuevamente
                    bajaLS = 0;
                    bajaLSBT = 0;
                    bajaAB = 0;
                }

            }
            else
            {
                if(operacion==3)
                {
                    fscanf(fp, "%ld", &(dniX));

                    if(p.dni>MasInfinito){

                        LSOfallos++;

                    }else{
                        //EVOCACIONES LSO
                        if(evocacionLSO(*cantLSO, LSO, dniX, &p, &evoLS)==1)
                        {
                            // Suma para sacar la media
                            sumaEvoLSE = sumaEvoLSE + evoLS;

                            // Calcular el maximo costo
                            if(evoLS>maxEvoLSE) maxEvoLSE = evoLS;

                            cantEvoELSO++;
                        }
                        else
                        {

                            // Suma para sacar la media
                            sumaEvoLSF = sumaEvoLSF + evoLS;

                            // Calcular el maximo costo
                            if(evoLS>maxEvoLSF) maxEvoLSF = evoLS;

                            cantEvoFLSO++;
                        }
                    }
                    //EVOCACIONES LSOBT
                    if(evocacionLSOBT(*cantLSOBT, LSOBT, dniX, &pAux, &evoLSBT)==1)
                    {
                        // Suma para sacar la media
                        sumaEvoLSBTE = sumaEvoLSBTE + evoLSBT;

                        // Calcular el maximo costo
                        if(evoLSBT>maxEvoLSBTE) maxEvoLSBTE = evoLSBT;

                        cantEvoELSOBT++;
                    }
                    else
                    {

                        // Suma para sacar la media
                        sumaEvoLSBTF = sumaEvoLSBTF + evoLSBT;

                        // Calcular el maximo costo
                        if(evoLSBT>maxEvoLSBTF) maxEvoLSBTF = evoLSBT;

                        cantEvoFLSOBT++;
                    }

                      //EVOCACIONES ABB
                    if(evocacionABB(ABB,  dniX, &p, &evoABB)==1)


                    {
                        // Suma para sacar la media
                        sumaEvoABBE = sumaEvoABBE + evoABB;

                        // Calcular el maximo costo
                        if(evoABB>maxEvoABBE) maxEvoABBE = evoABB;

                        cantEvoEABB++;
                    }
                    else
                    {

                        // Suma para sacar la media
                        sumaEvoABBF = sumaEvoABBF + evoABB;

                        // Calcular el maximo costo
                        if(evoABB>maxEvoABBF) maxEvoABBF = evoABB;

                        cantEvoFABB++;
                    }

                    //Inicializar nuevamente
                    evoLS=0;
                    evoLSBT = 0;
                    evoABB = 0;
                }
            }
        }

        fclose(fp);
        printf("// Lista secuencial ordenada con terminacion por contenido");

        gotoxy(0,2);
        printf("// Costos maximos ->");

        gotoxy(25,2);
        printf("Evocacion Exitosa= %d", maxEvoLSE);

        gotoxy(55,2);;
        printf("Evocacion Fracaso= %d", maxEvoLSF);

        gotoxy(85,2);
        printf("Alta= %d", maxAltaLS);

        gotoxy(100,2);
        printf("Baja= %d", maxBajaLS);

        gotoxy(0,3);
        printf("// Costos Medios  ->");

        gotoxy(25,3);
        if(cantEvoELSO!=0) printf("Evocacion Exitosa= %.2f", sumaEvoLSE/cantEvoELSO);
        else printf("Evocacion Exitosa= 0");

        gotoxy(55,3);
        if(cantEvoFLSO) printf("Evocacion Fracaso= %.2f", sumaEvoLSF/cantEvoFLSO);
        else printf("Evocacion Fracaso= 0");

        gotoxy(85,3);
        if(cantAltaLSO!=0) printf("Alta= %.2f", sumaAltaLS/cantAltaLSO);
        else printf("Alta= 0");

        gotoxy(100,3);
        if(cantBajaLSO!=0) printf("Baja= %.2f", sumaBajaLS/cantBajaLSO);
        else printf("Baja= 0");

        gotoxy(0,5);
        printf("// Lista secuencial ordenada con busqueda por triseccion");

        gotoxy(0,6);
        printf("// Costos maximos ->");

        gotoxy(25,6);
        printf("Evocacion Exitosa= %d", maxEvoLSBTE);

        gotoxy(55,6);
        printf("Evocacion Fracaso= %d", maxEvoLSBTF);

        gotoxy(85,6);
        printf("Alta= %d", maxAltaLSBT);

        gotoxy(100,6);
        printf("Baja= %d", maxBajaLSBT);

        gotoxy(0,7);
        printf("// Costos Medios  ->");

        gotoxy(25,7);
        if(cantEvoELSOBT!=0) printf("Evocacion Exitosa= %.2f", sumaEvoLSBTE/cantEvoELSOBT);
        else printf("Evocacion Exitosa= 0");

        gotoxy(55,7);
        if(cantEvoFLSOBT!=0) printf("Evocacion Fracaso= %.2f", sumaEvoLSBTF/cantEvoFLSOBT);
        else printf("Evocacion Fracaso= 0");

        gotoxy(85,7);
        if(cantAltaLSOBT!=0) printf("Alta= %.2f", sumaAltaLSBT/cantAltaLSOBT);
        else printf("Alta= 0");

        gotoxy(100,7);
        if(cantBajaLSOBT!=0) printf("Baja= %.2f", sumaBajaLSBT/cantBajaLSOBT);
        else printf("Baja= 0");

        gotoxy(0,9);
        printf("// Arbol binario de busqueda");

        gotoxy(0,10);
        printf("// Costos maximos ->");

        gotoxy(25,10);
        printf("Evocacion Exitosa= %0.2f", maxEvoABBE);

        gotoxy(55,10);
        printf("Evocacion Fracaso= %0.2f", maxEvoABBF);

        gotoxy(85,10);
        printf("Alta= %0.2f", maxAltaABB);

        gotoxy(100,10);
        printf("Baja= %0.2f", maxBajaABB);

        gotoxy(0,11);
        printf("// Costos Medios  ->");

        gotoxy(25,11);
        if(cantEvoEABB!=0) printf("Evocacion Exitosa= %.2f", sumaEvoABBE/cantEvoEABB);
        else printf("Evocacion Exitosa= 0");

        gotoxy(55,11);
        if(cantEvoFABB!=0) printf("Evocacion Fracaso= %.2f", sumaEvoABBF/cantEvoFABB);
        else printf("Evocacion Fracaso= 0");

        gotoxy(85,11);
        if(cantAltaABB!=0) printf("Alta= %.2f", sumaAltaABB/cantAltaABB);
        else printf("Alta= 0");

        gotoxy(100,11);
        if(cantBajaABB!=0) printf("Baja= %.2f", sumaBajaABB/cantBajaABB);
        else printf("Baja= 0");

        gotoxy(0,13);

        if(LSOfallos>0)
        printf("No se pudo cargar %d prestador/es a LSO. DNI debe ser menor a %d " ,LSOfallos , MasInfinito);


        gotoxy(0,15);
    }
    return 1;
}

int main()
{
    Prestador LSO[MAX_prestadoresLSO];
    Prestador LSOBT[MAX_prestadoresLSBB];
    ArbolABB ABB;
    initLSOMasInfi(LSO);
    initializeABB(&ABB);
    int i;
    int opcion, cantLSO = 0, cantLSOBT = 0 , cantABB=0;

    do
    {
        printf("Seleccione una opcion\n");
        printf("1- Comparar estructuras\n");
        printf("2- Mostrar lista secuencial ordenada con terminacion por contenido\n");
        printf("3- Mostrar lista secuencial ordenada con busqueda por triseccion\n");
        printf("4- Mostrar arbol binario de busqueda\n");
        printf("5- Salir\n");
        printf("Opcion: ");
        scanf("%d",&opcion);
        fflush(stdin);

        system("cls");
        switch (opcion)
        {
        case 1:
            compararEstructuras(LSO,&cantLSO,LSOBT,&ABB,&cantLSOBT,&cantABB);
            system("pause");
            system("cls");
            break;
        case 2:
            if(cantLSO==0)
            {
                printf("Lista vacia\n");
                system("pause");
            }
            for (i= 0; i < cantLSO; ++i)
            {
                MostrarPrestador(LSO[i]);
                if ((i+1)%3==0)
                {
                    system("pause");
                }
            }
            printf("Total de %d prestadores\n", cantLSO);
            //system("pause");
            //system("cls");
            break;
        case 3:
            if(cantLSOBT==0)
            {
                printf("Lista vacia\n");
                system("pause");
            }
            for (i= 0; i < cantLSOBT; ++i)
            {
                MostrarPrestador(LSOBT[i]);
                if ((i+1)%3==0)
                {
                    system("pause");
                }
            }
            printf("Total de %d prestadores\n", cantLSOBT);
            //system("pause");
            //system("cls");
            break;
        case 4:


        if(ABB.raiz==NULL){
        printf("Arbol vacio\n");
        system("pause");
           } else{
               preOrdenIterativo(ABB.raiz);

                 printf("Total de %d prestadores\n", ABB.cant);
               system("pause");}

            break;
        }
        //system("cls");
    }
    while (opcion!=5);
    return 0;
}
