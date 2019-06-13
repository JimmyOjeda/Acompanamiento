#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int mes;
	int dia;
	int anyo;
}fecha;

typedef struct{
   	int id;
   	char titulo[20];
   	char prioridad[5];
   	fecha fechaInicio;
   	fecha fechaFin;
}act;

typedef struct{
	int index;
	act actividad[10];
}lista;

int createActivity(lista *list,act p);
int updateActivity(lista *list,int auxForNotRepeat);
int deleteActivity(lista *list,int auxForNotRepeat);
int findById(lista *list,int idToFind);
void printList(lista list);
char* dateInicioToString(fecha *d);
char* dateFinToString(fecha *d);
char* activityToString(act *acti);
char* listToString(lista *list);

int main()
{
	//Se declaran las actividades
	fecha fecha1I = {10,21,2019};
	fecha fecha1F = {10,21,2019};
	act actividad1 = {1,"Actividad1","Alta",fecha1I,fecha1F};

	fecha fecha2I = {10,21,2019};
	fecha fecha2F = {10,21,2019};
	act actividad2 = {2,"Actividad2","Alta",fecha2I,fecha2F};

	fecha fecha3I = {10,21,2019};
	fecha fecha3F = {10,21,2019};
	act actividad3 = {3,"Actividad3","Alta",fecha3I,fecha3F};

	fecha fecha4I = {10,21,2019};
	fecha fecha4F = {10,21,2019};
	act actividad4 = {4,"Actividad4","Alta",fecha4I,fecha4F};

	fecha fecha5I = {10,21,2019};
	fecha fecha5F = {10,21,2019};
	act actividad5 = {5,"Actividad5","Alta",fecha5I,fecha5F};

	fecha fecha6I = {10,21,2019};
	fecha fecha6F = {10,21,2019};
	act actividad6 = {6,"Actividad6","Alta",fecha6I,fecha6F};

	fecha fecha7I = {10,21,2019};
	fecha fecha7F = {10,21,2019};
	act actividad7 = {7,"Actividad7","Alta",fecha7I,fecha7F};

	fecha fecha8I = {10,21,2019};
	fecha fecha8F = {10,21,2019};
	act actividad8 = {8,"Actividad8","Alta",fecha8I,fecha8F};

	fecha fecha9I = {10,21,2019};
	fecha fecha9F = {10,21,2019};
	act actividad9 = {9,"Actividad9","Alta",fecha9I,fecha9F};

	fecha fecha10I = {10,21,2019};
	fecha fecha10F = {10,21,2019};
	act actividad10 = {10,"Actividad10","Alta",fecha10I,fecha10F};

	//Se declara el struct de tipo lista llamado list
	lista list;

	//Se generan las 10 actividades ya declaradas
	createActivity(&list,actividad1);
	createActivity(&list,actividad2);
	createActivity(&list,actividad3);
	createActivity(&list,actividad4);
	createActivity(&list,actividad5);
	createActivity(&list,actividad6);
	createActivity(&list,actividad7);
	createActivity(&list,actividad8);
	createActivity(&list,actividad9);
	createActivity(&list,actividad10);


	//Se ejecuta un menu
	int opcion=0;
	printf("Todas las actividades (10) se generaron exitosamente\n");
	while (opcion!=4){
		int i;
		printf("\nIngresa una opcion del menu \n");
		printf("Opcion 1. Mostrar actividades \n");
		printf("Opcion 2. Modificar actividad \n");
		printf("Opcion 3. Eliminar actividades \n");
		printf("Opcion 4. Salir \n");
		scanf("%d",&opcion);
		if (opcion == 1){
			system("cls");
			printList(list);
		}else if (opcion == 2){
			system("cls");
			int idToFind;
			printf("Ingresa el id de la actividad a actualizar:\n");
			scanf("%d",&idToFind);
			int auxForNotRepeat=findById(&list,idToFind);
			if (updateActivity(&list,auxForNotRepeat)==1){
				printf("La actividad se actualizo con exito \n");
			}
		}else if (opcion == 3){
			system("cls");
			int idToFind;
			printf("Ingresa el id de la actividad a eliminar: \n");
			scanf("%d",&idToFind);
			int auxForNotRepeat=findById(&list,idToFind);
			if (deleteActivity(&list,auxForNotRepeat)==1){
                printf("La actividad con este id es la actividad %d \n",auxForNotRepeat+1);
                printf("Procedo a eliminar la actividad \n");
				printf("La actividad se elimino con exito \n");
			}else{
                printf("No se encontro una actividad con ese id \n");
			}
		}
	}
	return 0;
}

int createActivity(lista *list,act p){
	list->actividad[list->index] = p;
	list->index++;
}

int updateActivity(lista *list,int auxForNotRepeat){
	int flagUpdate=0;
	if (auxForNotRepeat!=-1){
		printf("---Vamos a actualizar la actividad %d--- \n",auxForNotRepeat+1);
		printf("Ingresa el nuevo titulo de la actividad: \n");
		char newTittle[20];
		scanf("%s",newTittle);
		strcpy(list->actividad[auxForNotRepeat].titulo,newTittle);
		printf("Ingresa la nueva prioridad de la actividad: \n");
		char newPriority[5];
		scanf("%s",newPriority);
		strcpy(list->actividad[auxForNotRepeat].prioridad,newPriority);

		flagUpdate=1;
	}
	return flagUpdate;
}

int deleteActivity(lista *list,int auxForNotRepeat){
	int flagDelete=0,i;
	if (auxForNotRepeat!=-1){
		for (i=auxForNotRepeat;i<list->index;i++){
            list->actividad[i] = list->actividad[+1] ;
		}
		flagDelete=1;
	}
	return flagDelete;
}

int findById(lista *list,int idToFind){
	int i,idFound=-1;
	for (i=0;i<10;i++){
		if (list->actividad[i].id==idToFind){
			idFound=i;
			break;
		}
	}
	return idFound;
}

void printList(lista list){
	char outputFromList[8000]=" ";
	strcpy(outputFromList,listToString(&list));
	printf("%s",outputFromList);
}

char* dateInicioToString(fecha *d){
	char output[10]=" ";
	char auxDia[3];
	char auxMes[3];
	char auxAnyo[3];

	//Se hace una string con la fecha de inicio
	char sentenceStart[10]=" ";
	sprintf(auxDia,"%d",d->dia);
	strcat(sentenceStart,auxDia);
	strcat(sentenceStart,"/");
	sprintf(auxMes,"%d",d->mes);
	strcat(sentenceStart,auxMes);
	strcat(sentenceStart,"/");
	sprintf(auxAnyo,"%d",d->anyo);
	strcat(sentenceStart,auxAnyo);
	strcat(output,sentenceStart);

	return output;
}

char* dateFinToString(fecha *d){
	char output[10]=" ";
	char auxDia[3];
	char auxMes[3];
	char auxAnyo[3];
	//Se hace una string con la fecha de fin
	char sentenceEnd[10]=" ";
	sprintf(auxDia,"%d",d->dia);
	strcat(sentenceEnd,auxDia);
	strcat(sentenceEnd,"/");
	sprintf(auxMes,"%d",d->mes);
	strcat(sentenceEnd,auxMes);
	strcat(sentenceEnd,"/");
	sprintf(auxAnyo,"%d",d->anyo);
	strcat(sentenceEnd,auxAnyo);
    strcat(output,sentenceEnd);

	return output;
}

char* activityToString(act *acti){
	char output[800]={"---ACTIVIDAD "};
	char auxForAll[6];
	char outputFromDate[10]=" ";

	sprintf(auxForAll,"%d",acti->id+1);
	strcat(output,auxForAll);
	strcat(output,"---\nEl id de la actividad es: ");
	sprintf(auxForAll,"%d",acti->id);
	strcat(output,auxForAll);
	strcat(output,"\nEl titulo de la actividad es: ");
	strcat(output,acti->titulo);
	strcat(output,"\nLa prioridad de la actividad es: ");
	strcat(output,acti->prioridad);
	strcat(output,"\nLa fecha de inicio de la actividad es: ");
	strcpy(outputFromDate,dateInicioToString(&acti->fechaInicio));
	strcat(output,outputFromDate);
	strcat(output,"\nLa fecha de fin de la actividad es: ");
	strcpy(outputFromDate,dateFinToString(&acti->fechaFin));
	strcat(output,outputFromDate);
	strcat(output,"\n");
	return output;
}

char* listToString(lista *list){
	int i;
	char output[8000]=" ";
	for (i=0;i<list->index;i++){
        strcat(output,activityToString(&list->actividad[i]));
	}
	return output;
}
