#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int dia;
	int mes;
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
	act *actividades[10];
}lista;

int rellenarActividad(lista *list,act *actividadVacia);
int createActivity(lista *list,act *actividadVacia);
int updateActivity(lista *list,int *positionFound,act *newAct);
int deleteActivity(lista *list,int *positionFound);
int findById(lista *list,int *idToFind);
void printList(lista *list);
char* dateInicioToString(fecha *d);
char* dateFinToString(fecha *d);
char* activityToString(act *acti);
char* listToString(lista *list);

void ordenarLista(lista *list,act actividadesOrdenadas[]);

int main()
{
	//Se declaran las actividades
	/*fecha fecha1I = {10,21,2019};
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
	act actividad10 = {10,"Actividad10","Alta",fecha10I,fecha10F};*/

	//Se declara el struct de tipo lista llamado list
	lista list;
	list.index=0;
	
	act *actividadesOrdenadas[10];
	
	//Se reserva memoria para las actividades ordenadas
	act *actividadOrdenada1=(act*)malloc(sizeof(act));
	act *actividadOrdenada2=(act*)malloc(sizeof(act));
	act *actividadOrdenada3=(act*)malloc(sizeof(act));
	act *actividadOrdenada4=(act*)malloc(sizeof(act));
	act *actividadOrdenada5=(act*)malloc(sizeof(act));
	act *actividadOrdenada6=(act*)malloc(sizeof(act));
	act *actividadOrdenada7=(act*)malloc(sizeof(act));
	act *actividadOrdenada8=(act*)malloc(sizeof(act));
	act *actividadOrdenada9=(act*)malloc(sizeof(act));
	act *actividadOrdenada10=(act*)malloc(sizeof(act));
	
	//Enlazo los apuntadores de mi vector con los obtenidos con malloc
	enlazarActividadesOrdenadas(actividadesOrdenadas[0],actividadOrdenada1);
	enlazarActividadesOrdenadas(actividadesOrdenadas[1],actividadOrdenada2);
	enlazarActividadesOrdenadas(actividadesOrdenadas[2],actividadOrdenada3);
	enlazarActividadesOrdenadas(actividadesOrdenadas[3],actividadOrdenada4);
	enlazarActividadesOrdenadas(actividadesOrdenadas[4],actividadOrdenada5);
	enlazarActividadesOrdenadas(actividadesOrdenadas[5],actividadOrdenada6);
	enlazarActividadesOrdenadas(actividadesOrdenadas[6],actividadOrdenada7);
	enlazarActividadesOrdenadas(actividadesOrdenadas[7],actividadOrdenada8);
	enlazarActividadesOrdenadas(actividadesOrdenadas[8],actividadOrdenada9);
	enlazarActividadesOrdenadas(actividadesOrdenadas[9],actividadOrdenada10);
	/*printf("El valor es: %d \n \n",actividadOrdenada1);
	printf("El valor es: %d \n \n",actividadOrdenada2);
	printf("El valor es: %d \n \n",actividadOrdenada3);*/
	
	//Se reserva memoria para las actividades
	act *actividad1=(act*)malloc(sizeof(act));
	act *actividad2=(act*)malloc(sizeof(act));
	act *actividad3=(act*)malloc(sizeof(act));
	act *actividad4=(act*)malloc(sizeof(act));
	act *actividad5=(act*)malloc(sizeof(act));
	act *actividad6=(act*)malloc(sizeof(act));
	act *actividad7=(act*)malloc(sizeof(act));
	act *actividad8=(act*)malloc(sizeof(act));
	act *actividad9=(act*)malloc(sizeof(act));
	act *actividad10=(act*)malloc(sizeof(act));
	
	//Se rellenan las actividades creadas con malloc y se les pasa su dirección al vector de apuntadores
	rellenarActividad(&list,actividad1);
	createActivity(&list,actividad1);
	rellenarActividad(&list,actividad2);
	createActivity(&list,actividad2);
	rellenarActividad(&list,actividad3);
	createActivity(&list,actividad3);
	rellenarActividad(&list,actividad4);
	createActivity(&list,actividad4);
	rellenarActividad(&list,actividad5);
	createActivity(&list,actividad5);
	rellenarActividad(&list,actividad6);
	createActivity(&list,actividad6);
	rellenarActividad(&list,actividad7);
	createActivity(&list,actividad7);
	rellenarActividad(&list,actividad8);
	createActivity(&list,actividad8);
	rellenarActividad(&list,actividad9);
	createActivity(&list,actividad9);
	rellenarActividad(&list,actividad10);
	createActivity(&list,actividad10);


	//Se ejecuta un menu
	int opcion=0;
	printf("Todas las actividades (10) se generaron exitosamente\n");
	while (opcion!=5){
		int i;
		printf("\nIngresa una opcion del menu \n");
		printf("Opcion 1. Mostrar actividades \n");
		printf("Opcion 2. Modificar actividad \n");
		printf("Opcion 3. Eliminar actividades \n");
		printf("Opcion 4. Ordenar actividades \n");
		printf("Opcion 5. Salir \n");
		scanf("%d",&opcion);
		if (opcion == 1){
			system("cls");
			printList(&list);
		}else if (opcion == 2){
			system("cls");
			int idToFind,newDayI,newMonthI,newYearI,newDayF,newMonthF,newYearF;
			char newTittle[20];
			char newPriority[5];
			act newAct;
			printf("Ingresa el id de la actividad a actualizar:\n");
			scanf("%d",&idToFind);
			int positionFound=findById(&list,&idToFind);
			if (positionFound!=-1){
				printf("---Vamos a actualizar la actividad %d--- \n",list.actividades[positionFound]->id);
	      		printf("Ingresa el nuevo titulo de la actividad: \n");
	   			scanf("%s",newTittle);
				printf("Ingresa la nueva prioridad de la actividad: \n");
	    		scanf("%s",newPriority);
	    		printf("Ingresa la nueva fecha de inicio de la actividad: \n");
	    		printf("Ingresa dia, mes y anio (ingresa y presiona enter) en ese orden \n");
	    		scanf("%d",&newDayI);
	    		scanf("%d",&newMonthI);
	    		scanf("%d",&newYearI);
	    		printf("Ingresa la nueva fecha de inicio de la actividad: \n");
	    		printf("Ingresa dia, mes y anio (ingresa y presiona enter) en ese orden \n");
	    		scanf("%d",&newDayF);
	    		scanf("%d",&newMonthF);
	    		scanf("%d",&newYearF);
	    		//Asignacion de valores
	    		newAct.id=idToFind;
	    		strcpy(newAct.titulo,newTittle);
	    		strcpy(newAct.prioridad,newPriority);
	    		newAct.fechaInicio.dia=newDayI;
	    		newAct.fechaInicio.mes=newMonthI;
	    		newAct.fechaInicio.anyo=newYearI;
	    		newAct.fechaFin.dia=newDayF;
	    		newAct.fechaFin.mes=newMonthF;
	    		newAct.fechaFin.anyo=newYearF;
			}
			if (updateActivity(&list,&positionFound,&newAct)==1){
				printf("La actividad se actualizo con exito \n");
			}else {
      			printf("No se encontro una actividad con ese id \n");
			}
		}else if (opcion == 3){
			system("cls");
			int idToFind;
			printf("Ingresa el id de la actividad a eliminar: \n");
			scanf("%d",&idToFind);
			int positionFound=findById(&list,&idToFind);
			if (deleteActivity(&list,&positionFound)==1){
      			printf("La actividad con este id es la actividad %d \n",positionFound+1);
      			printf("Procedo a eliminar la actividad \n");
				printf("La actividad se elimino con exito \n");
			}else{
      			printf("No se encontro una actividad con ese id \n");
			}
		}else if (opcion == 4){
			ordenarLista(&list,actividadesOrdenadas);
			printf("Se ordenaron las actividades");
			//printf("El id de la actividad mas proxima es: ",actividadesOrdenadas[0]->id);
		}
	}
	
	free(actividad1);
	free(actividad2);
	free(actividad3);
	free(actividad4);
	free(actividad5);
	free(actividad6);
	free(actividad7);
	free(actividad8);
	free(actividad9);
	free(actividad10);
	
	free(actividadOrdenada1);
	free(actividadOrdenada2);
	free(actividadOrdenada3);
	free(actividadOrdenada4);
	free(actividadOrdenada5);
	free(actividadOrdenada6);
	free(actividadOrdenada7);
	free(actividadOrdenada8);
	free(actividadOrdenada9);
	free(actividadOrdenada10);
	
	return 0;
}

void ordenarLista(lista *list,act actividadesOrdenadas[]){
	int n=10;
	//Se convierten las fechas de las actividades a enteros comparables
	int fechaAct[n];
	
	fechaAct[0]=(list->actividades[0]->fechaInicio.dia+list->actividades[0]->fechaInicio.mes+list->actividades[0]->fechaInicio.anyo);
	fechaAct[1]=(list->actividades[1]->fechaInicio.dia+list->actividades[1]->fechaInicio.mes+list->actividades[1]->fechaInicio.anyo);
	fechaAct[2]=(list->actividades[2]->fechaInicio.dia+list->actividades[2]->fechaInicio.mes+list->actividades[2]->fechaInicio.anyo);
	fechaAct[3]=(list->actividades[3]->fechaInicio.dia+list->actividades[3]->fechaInicio.mes+list->actividades[3]->fechaInicio.anyo);
	fechaAct[4]=(list->actividades[4]->fechaInicio.dia+list->actividades[4]->fechaInicio.mes+list->actividades[4]->fechaInicio.anyo);
	fechaAct[5]=(list->actividades[5]->fechaInicio.dia+list->actividades[5]->fechaInicio.mes+list->actividades[5]->fechaInicio.anyo);
	fechaAct[6]=(list->actividades[6]->fechaInicio.dia+list->actividades[6]->fechaInicio.mes+list->actividades[6]->fechaInicio.anyo);
	fechaAct[7]=(list->actividades[7]->fechaInicio.dia+list->actividades[7]->fechaInicio.mes+list->actividades[7]->fechaInicio.anyo);
	fechaAct[8]=(list->actividades[8]->fechaInicio.dia+list->actividades[8]->fechaInicio.mes+list->actividades[8]->fechaInicio.anyo);
	fechaAct[9]=(list->actividades[9]->fechaInicio.dia+list->actividades[9]->fechaInicio.mes+list->actividades[9]->fechaInicio.anyo);
	
	int i,j,aux;
	act auxAct;
	
	for (i=0;i<n;i++){
		printf("Aqui llega\n");
		actividadesOrdenadas[i]=*list->actividades[i];
		printf("El id de la actividadOrd %d: %d \n",i+1,actividadesOrdenadas[i].id);
	}
	
	
	for (i=0;i<n;i++) {
		for (j=0;j<n-i;j++) {
			if (fechaAct[j]>=fechaAct[j+1]){
				aux=fechaAct[j]; 
				fechaAct[j]=fechaAct[j+1]; 
				fechaAct[j+1]=aux;
				auxAct=actividadesOrdenadas[j]; 
				actividadesOrdenadas[j]=actividadesOrdenadas[j+1]; 
				actividadesOrdenadas[j+1]=auxAct;
			}
			
		}
	}
}

void enlazarActividadesOrdenadas(act *actividadesOrdenadas,act *actividadVacia){
	actividadesOrdenadas=actividadVacia;
}

int rellenarActividad(lista *list,act *actividadVacia){
	act actividad = {list->index+1,"Actividad","Alta",{21,10,2019},{22,10,2019}};
	*actividadVacia=actividad;
}

int createActivity(lista *list,act *actividadVacia){
	list->actividades[list->index]=actividadVacia;
	list->index++;
}

int updateActivity(lista *list,int *positionFound,act *newAct){
	int flagUpdate=0;
	if (*positionFound!=-1){
		*list->actividades[*positionFound]=*newAct;
		flagUpdate=1;
	}
	return flagUpdate;
}

int deleteActivity(lista *list,int *positionFound){
	int flagDelete=0,i;
	if (*positionFound!=-1){
		for (i=*positionFound;i<list->index;i++){
            list->actividades[i] = list->actividades[i+1] ;
		}
		
		list->index--;
		flagDelete=1;
	}
	return flagDelete;
}

int findById(lista *list,int *idToFind){
	int i,idFound=-1;
	for (i=0;i<10;i++){
		if (list->actividades[i]->id==*idToFind){
			idFound=i;
			break;
		}
	}
	return idFound;
}

void printList(lista *list){
	char outputFromList[8000]=" ";
	strcpy(outputFromList,listToString(list));
	printf("%s",outputFromList);
}

char* dateToString(fecha *d){
	char output[10]=" ";
	char auxDia[3];
	char auxMes[3];
	char auxAnyo[5];

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

char* activityToString(act *acti){
	char output[800]={"---ACTIVIDAD "};
	char auxForAll[6];
	char outputFromDate[12]=" ";

	sprintf(auxForAll,"%d",acti->id);
	strcat(output,auxForAll);
	strcat(output,"---\nEl id de la actividad es: ");
	sprintf(auxForAll,"%d",acti->id);
	strcat(output,auxForAll);
	strcat(output,"\nEl titulo de la actividad es: ");
	strcat(output,acti->titulo);
	strcat(output,"\nLa prioridad de la actividad es: ");
	strcat(output,acti->prioridad);
	strcat(output,"\nLa fecha de inicio de la actividad es:");
	strcpy(outputFromDate,dateToString(&acti->fechaInicio));
	strcat(output,outputFromDate);
	strcat(output,"\nLa fecha de fin de la actividad es:");
	strcpy(outputFromDate,dateToString(&acti->fechaFin));
	strcat(output,outputFromDate);
	strcat(output,"\n");
	return output;
}

char* listToString(lista *list){
	int i;
	char output[8000]=" ";
	for (i=0;i<list->index;i++){
        strcat(output,activityToString(list->actividades[i]));
	}
	return output;
}
