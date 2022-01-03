#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define m 100

typedef struct {
    int matricula;
    char nombre[30];
    char apellido[30];
    int edad;
    int marcadebaja;
} alumnos;


int menu();

int cargararchivoalumnos(alumnos vectorAlumnos[]);

int buscaralumno (alumnos vectorAlumnos[] , int finalumnos,int que);

int cargaralumnos (alumnos vectorAlumnos[], int finalumnos, int inicioalumnos);

int graboElArchivoalumnos(alumnos vectorAlumnos[], int finalumnos);

int controldealumnos(int numero, alumnos vectorAlumnos[], int finalumnos);

void ordenardatos (alumnos vectorAlumnos[], int finalumnos);
void mostraralumnos (alumnos vectorAlumnos[], int finalumnos);


int main()
{
  int opcion;
  int finalumnos=0;

alumnos vectorAlumnos[100];
finalumnos = cargararchivoalumnos(vectorAlumnos);

do {
        opcion = menu();

        switch (opcion)
        {
            case 1:
                    finalumnos = cargaralumnos(vectorAlumnos, finalumnos, finalumnos);
                    break;

            case 2: ordenardatos (vectorAlumnos,finalumnos);
                    buscaralumno (vectorAlumnos,finalumnos, 2);
                    break;

            case 3: ordenardatos (vectorAlumnos,finalumnos);
                    buscaralumno (vectorAlumnos,finalumnos, 3); // 3)	Modificaciones :
                    // Se deberá verificar la existencia del registro y que la marca de baja tenga el valor cero, si no enviar el mensaje “Esa Matricula no existe”

                                                                // No es distinto de las anteriores opciones del menú (?


                   break;

            case 4:
                   mostraralumnos (vectorAlumnos,finalumnos);
                   break;

            case 5: ordenardatos (vectorAlumnos,finalumnos);
                    buscaralumno (vectorAlumnos,finalumnos, 5);

                   break;
        }
   } while (opcion!=6);

graboElArchivoalumnos (vectorAlumnos, finalumnos);

return 0;
}


int menu()
{
    int opcion;

    system("cls");

    printf("1 - Altas o Ingresos\n");
    printf("2 - Bajas Logicas\n");
    printf("3 - Modificaciones\n");
    printf("4 - Consulta General\n");
    printf("5 - Consulta por matricula\n");
    printf("6 - Finalizar\n\n");

    printf("Ingrese su opcion: ");
    scanf("%i",&opcion);

    return opcion;

}


int cargararchivoalumnos (alumnos vectorAlumnos[])

{FILE *arch;
 arch = fopen("alumnos.bin","rb");

if (arch==NULL)
{
 arch=fopen("alumnos.bin","wb");
 printf("\n\n\nCreo de cero la lista de Alumnos...\n\n\n");
 system("pause");

return 0;
}

alumnos ralumnos;
int i=0;

fread(&ralumnos, sizeof(ralumnos), 1, arch);

    while(!feof(arch))
{
 vectorAlumnos[i] = ralumnos;
 i++;

 if (i >= m)  i=0;
 fread(&ralumnos, sizeof(ralumnos), 1, arch);
}
    fclose(arch);

   return i;
}


int cargaralumnos(alumnos vectorAlumnos[], int finalumnos, int inicioalumnos)
{
    char sino;
    int i=inicioalumnos,errorcodigoalumnos;

    do{
    do
    {printf("\nIngrese el numero de MATRICULA del Alumno: ");

     fflush(stdin);
     scanf("%i",&vectorAlumnos[i].matricula);

     errorcodigoalumnos = controldealumnos (vectorAlumnos[i].matricula, vectorAlumnos, finalumnos);

      if( errorcodigoalumnos == 0)
         {
          printf("\nYA EXISTE un Alumno con ese numero de MATRICULA\n\n");
          system("pause");
         }

     }while (errorcodigoalumnos == 0);

        printf("\nIngrese el APELLIDO del Alumno: ");
        fflush(stdin);
        gets(vectorAlumnos[i].apellido);

        printf ("\nIngrese el NOMBRE del Alumno: ");
        fflush(stdin);
        gets(vectorAlumnos[i].nombre);

        printf ("\nIngrese la EDAD del Alumno: ");
        scanf("%i", &vectorAlumnos[i].edad);

        vectorAlumnos[i].marcadebaja = 0;

        printf("\n Quiere seguir cargando (s/n): ");
        fflush(stdin);
        scanf("%c", &sino);

        i++;

        if(i >= m)
        i=0;

    }while (sino != 'n');

   return i;
}


int buscaralumno (alumnos vectorAlumnos[], int finalumnos,int que)
{int i,central,bajo,alto;
int valorcentral;
int clave;

system("cls");

bajo = 0;
alto = finalumnos;

printf("Ingrese el 'Numero de Matricula' del Alumno: ");
scanf("%i",&clave);

   while (bajo<=alto)

   {central = (bajo+alto)/2;
    valorcentral = vectorAlumnos[central].matricula;

    if (clave==valorcentral){

    if (que==2)
    {
      if (vectorAlumnos[central].marcadebaja==0)
      {
       vectorAlumnos[central].marcadebaja=1;
       printf ("\nSe ha dado de baja al Alumno: %s %s\n\n",vectorAlumnos[central].apellido,vectorAlumnos[central].nombre);
       system("pause");
      }
    }

    if (que==3){
     if (vectorAlumnos[central].marcadebaja==0)
        {
          printf ("\nEl registro existe (?\n\n");
          system("pause");
        }
     else{
        printf("\n\nEl alumno con esa MATRICULA se ha dado de baja\n\n");
        system("pause");}

    }

    if (que==5){
            if (vectorAlumnos[central].marcadebaja==0)
            {
             printf ("\n\nMATRICULA \t  APELLIDO \t NOMBRE \t EDAD \t ESTADO\n\n");
             printf ("%i \t\t %s \t %s \t %i \t %i\n\n\n",vectorAlumnos[central].matricula, vectorAlumnos[central].apellido, vectorAlumnos[central].nombre, vectorAlumnos[central].edad, vectorAlumnos[central].marcadebaja);
             system("pause");
           }
    else{
        printf("\n\nEl alumno con esa MATRICULA se ha dado de baja\n\n");
        system("pause");}
    }

    return 0;
    }

    else

    if (clave<valorcentral)
        alto = central -1;
    else
        bajo = central +1;
   }

   printf ("\nEsa MATRICULA no existe\n\n");

   system("pause");

    return 0;
}


int graboElArchivoalumnos(alumnos vectorAlumnos[], int finalumnos)
{
    FILE *arch;
    arch = fopen("alumnos.bin", "wb");

    if (arch == NULL)
    {
        printf("\n\n ERROR");
    }

    alumnos ralumnos;

    int i=0;

    for(i=0; i<finalumnos; i++)
    {
        ralumnos=vectorAlumnos[i];
        fwrite(&ralumnos, sizeof(ralumnos), 1, arch);
    }

    fclose(arch);
}


int controldealumnos(int numero, alumnos vectorAlumnos[], int finalumnos)
{
    int i;

    for(i=0; i<finalumnos; i++)
    {
        if(vectorAlumnos[i].matricula == numero)
        {
            return 0;
        }
    }

    return -20;
}


void ordenardatos (alumnos vectorAlumnos[], int finalumnos)
{alumnos aux;

for (int i=0; i<finalumnos; i++)

{   for (int j=0;j<finalumnos;j++)
   {
     if (vectorAlumnos[j].matricula> vectorAlumnos[j+1].matricula)
     {
       aux=vectorAlumnos[j+1];
       vectorAlumnos[j+1]=vectorAlumnos[j];
       vectorAlumnos[j]=aux;
      }
    }
}
return 0;
}


void mostraralumnos (alumnos vectorAlumnos[], int finalumnos)
{
    printf ("\nA continuacion los datos generales...\n\n");
    system ("pause");

    system("cls");
    printf ("MATRICULA \t  APELLIDO \t NOMBRE \t EDAD \t ESTADO\n\n");
    for (int i=0;i<finalumnos;i++)
    {
        if (vectorAlumnos[i].marcadebaja==0)
        printf ("%i \t\t %s \t %s \t %i \t %i\n",vectorAlumnos[i].matricula, vectorAlumnos[i].apellido, vectorAlumnos[i].nombre, vectorAlumnos[i].edad, vectorAlumnos[i].marcadebaja);
    }
    printf ("\n\n");
    system ("pause");

    return 0;
}
