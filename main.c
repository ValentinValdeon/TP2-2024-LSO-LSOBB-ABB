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

void gotoxy(int x, int y)
{
    printf("%c[%d;%df", 0x1B, y, x);
}


int compararEstructuras(Prestador LSO[], int *cantLSO,Prestador LSOBT[], int *cantLSOBT)
{

    FILE* fp = fopen("Operaciones-Prestadores.txt", "r");
    Prestador p, pAux;
    long dniX=0;
    int operacion, i;
    initLSOMasInfi(LSO);

    (*cantLSO)=0;
    (*cantLSOBT)=0;

    // Alta - Baja - Evocacion - SumaAlta - SumaBaja - SumaEvo - Maximo


    int altaLS=0, bajaLS=0, evoLS=0, maxAltaLS=0, maxBajaLS=0, maxEvoLSF=0, maxEvoLSE=0;
    float sumaAltaLS=0, sumaBajaLS=0, sumaEvoLSF=0, sumaEvoLSE=0;

    int altaLSBT=0, bajaLSBT=0, evoLSBT=0, maxAltaLSBT=0, maxBajaLSBT=0, maxEvoLSBTF=0, maxEvoLSBTE=0;
    float sumaAltaLSBT=0, sumaBajaLSBT=0, sumaEvoLSBTF=0, sumaEvoLSBTE=0;

    int cantAltaLSO=0,cantAltaLSOBT=0;
    int cantBajaLSO=0,cantBajaLSOBT=0;
    int cantEvoELSO=0,cantEvoELSOBT=0;
    int cantEvoFLSO=0,cantEvoFLSOBT=0;

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
                    //ALTA LSO
                    if(altaLSO(p, LSO, cantLSO, &altaLS)==1)
                    {
                        // Suma para sacar la media
                        sumaAltaLS = sumaAltaLS + altaLS;

                        // Calcular el maximo costo
                        if(altaLS>maxAltaLS) maxAltaLS = altaLS;

                        cantAltaLSO++;
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
                    //Incializar nuevamente
                    altaLS = 0;
                    altaLSBT = 0;

                }
                else
                {
                    //BAJA LSO
                    if(bajaLSO(p, LSO, cantLSO, &bajaLS)==1)
                    {
                        // Suma para sacar la media
                        sumaBajaLS = sumaBajaLS + bajaLS;

                        // Calcular el maximo costo
                        if(bajaLS>maxBajaLS) maxBajaLS = bajaLS;

                        cantBajaLSO++;
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
                    //Incializar nuevamente
                    bajaLS = 0;
                    bajaLSBT = 0;
                }

            }
            else
            {
                if(operacion==3)
                {
                    fscanf(fp, "%ld", &(dniX));

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
                    //Inicializar nuevamente
                    evoLS=0;
                    evoLSBT = 0;
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
        gotoxy(0,10);
        gotoxy(25,10);
        gotoxy(55,10);
        gotoxy(85,10);
        gotoxy(100,10);
        gotoxy(0,11);
        gotoxy(25,11);
        gotoxy(55,11);
        gotoxy(85,11);
        gotoxy(100,11);
        gotoxy(0,13);
    }

    return 1;
}

int main()
{
    Prestador LSO[MAX_prestadoresLSO];
    Prestador LSOBT[MAX_prestadoresLSBB];
    int i;
    int opcion, cantLSO = 0, cantLSOBT = 0;

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
            compararEstructuras(LSO,&cantLSO,LSOBT,&cantLSOBT);
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
            system("cls");
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
            system("cls");
            break;
        case 4:
            break;
        }
    }
    while (opcion!=5);
    return 0;
}
