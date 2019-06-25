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

typedef struct nodo{
	act actividad;
	struct nodo *siguiente;
}NODO;

typedef struct{
	int index;
	struct nodo *cabezaLista;
	struct nodo *colaLista;
}lista;

int main()
{
	//Se declara el struct de tipo lista llamado list
	lista list;
	list.index=0;
	list.cabezaLista=NULL;
	list.colaLista=NULL;
	
	//Se hace un vector que guarde las direcciones de los malloc para hacerles free al final
	struct nodo *frees[10];
	
	//Se hacen las 10 actividades
	act actividades[10];
	int i;
	for (i=0;i<10;i++){
		actividades[i].id=i+1;
		strcpy(actividades[i].titulo,"Actividad");
		strcpy(actividades[i].prioridad,"Alta");
		actividades[i].fechaInicio.dia=20+i;
		actividades[i].fechaInicio.mes=10;
		actividades[i].fechaInicio.anyo=2019;
		actividades[i].fechaFin.dia=10-i;
		actividades[i].fechaFin.mes=10;
		actividades[i].fechaFin.anyo=2019;
	}
	
	//Se genera la lista con las actividades
	int counterAux=0;
	for (i=0;i<10;i++){
		counterAux=counterAux+agregarNodo(&list,&actividades[i],&frees[i]);
	}
	if (counterAux==10){
		printf("Las (10) actividades se generaron con exito\n");
	}else {
		printf("No hubo espacio suficiente para generar algunas actividades\n");
	}
	
	//Se hace un vector donde se ordenaran las actividades segun su fecha de inicio
	act *actividadesOrdenadas[10];
	struct nodo *indice;
	counterAux=0;
	for (indice=list.cabezaLista;indice!=NULL;indice=indice->siguiente){
		actividadesOrdenadas[counterAux]=&indice->actividad;
		counterAux++;
	}
	
	//Se ejecuta un menu
	int opcion=0;
	while (opcion!=5){
		printf("\nIngresa una opcion del menu \n");
		printf("Opcion 1. Mostrar actividades \n");
		printf("Opcion 2. Modificar actividad \n");
		printf("Opcion 3. Eliminar actividades \n");
		printf("Opcion 4. Imprimir ordenadamente las actividades (Ascendente por fecha) \n");
		printf("Opcion 5. Salir \n");
		scanf("%d",&opcion);
		if (opcion == 1){
			system("cls");
			printList(&list,list);
		}else if (opcion == 2){
			system("cls");
			int idToFind,newDayI,newMonthI,newYearI,newDayF,newMonthF,newYearF;
			char newTittle[20];
			char newPriority[5];
			act newAct;
			printf("Ingresa el id de la actividad a actualizar:\n");
			scanf("%d",&idToFind);
			struct nodo *positionFound=findById(&list,&idToFind);
			if (positionFound!=NULL){
				printf("---Vamos a actualizar la actividad %d--- \n",positionFound->actividad.id);
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
	    		//Asignacion de valores a la actividad a mandar
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
			if (updateActivity(&list,positionFound,&newAct)==1){
				printf("La actividad se actualizo con exito \n");
			}else {
      			printf("No se encontro una actividad con ese id \n");
			}
		}else if (opcion == 3){
			system("cls");
			int idToFind;
			printf("Ingresa el id de la actividad a eliminar: \n");
			scanf("%d",&idToFind);
			struct nodo *positionFound=findById(&list,&idToFind);
			if (positionFound!=NULL){
				printf("La actividad con este id es la actividad %d \n",positionFound->actividad.id);
			}
			if (deleteActivity(&list,positionFound)==1){
				printf("La actividad se elimino con exito \n");
			}else{
      			printf("No se encontro una actividad con ese id \n");
			}
		}else if (opcion == 4){
			system("cls");
			ordenarLista(&list,actividadesOrdenadas);
			printListOrdenada(&list,actividadesOrdenadas);
			printf("Se imprimieron ordenadamente las actividades (Ascendente por fecha)\n");
		}
	}
	
	
	//Se hace free a la memoria usada
	for (i=0;i<10;i++){
		free(frees[i]);
	}
	return 0;
}

int agregarNodo(lista *list,act *nuevaAct,struct nodo *frees){
	int flag=0;
	struct nodo *nuevoNodo;
	nuevoNodo=(struct nodo*)malloc(sizeof(struct nodo));
	frees=nuevoNodo;
	if (list->index>0 && nuevoNodo!=NULL){
		nuevoNodo->actividad=*nuevaAct;
		nuevoNodo->siguiente=NULL;
		list->colaLista->siguiente=nuevoNodo;
		list->colaLista=nuevoNodo;
		list->index++;
		flag=1;
	}else if (list->index==0 && nuevoNodo!=NULL){
		nuevoNodo->actividad=*nuevaAct;
		nuevoNodo->siguiente=NULL;
		list->cabezaLista=nuevoNodo;
		list->colaLista=nuevoNodo;
		list->index++;
		flag=1;
	}
	return flag;
}

/*int recorrerLista(lista *list){
	struct nodo *indice;
	for (indice=list->cabezaLista;indice!=NULL;indice=indice->siguiente){
		printf("El id de prueba es: %d \n",indice->actividad.id);
	}
}*/

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
	struct nodo *indice;
	for (indice=list->cabezaLista;indice!=NULL;indice=indice->siguiente){
		strcat(output,activityToString(&indice->actividad));
	}
	return output;
}

void printList(lista *list){
	char outputFromList[8000]=" ";
	strcpy(outputFromList,listToString(list));
	printf("%s",outputFromList);
}

int findById(lista *list,int *idToFind){
	struct nodo *indice,*indiceFound=NULL;
	for (indice=list->cabezaLista;indice!=NULL;indice=indice->siguiente){
		if (indice->actividad.id==*idToFind){
			indiceFound=indice;
			break;
		}
	}
	return indiceFound;
}

int updateActivity(lista *list,struct nodo *positionFound,act *newAct){
	int flagUpdate=0;
	if (positionFound!=NULL){
		positionFound->actividad=*newAct;
		flagUpdate=1;
	}
	return flagUpdate;
}

int deleteActivity(lista *list,struct nodo *positionFound){
	int flagDelete=0;
	struct nodo *actual;
	struct nodo *anterior;
	struct nodo *auxForFree;
	if (positionFound!=NULL){
		for (actual=list->cabezaLista;actual!=positionFound->siguiente;actual=actual->siguiente){
			if (actual==positionFound){
				if (positionFound==list->cabezaLista){
					auxForFree=list->cabezaLista;
					list->cabezaLista=list->cabezaLista->siguiente;
					free (auxForFree);
				}else
				if (positionFound==list->colaLista){
					anterior->siguiente=NULL;
					free (list->colaLista);
					list->colaLista=anterior;
				}else {
					anterior->siguiente=actual->siguiente;
					free (actual);
				}
				list->index--;
				flagDelete=1;
			}
			anterior=actual;
		}
	}
	return flagDelete;
}

void ordenarLista(lista *list,act *actividadesOrdenadas[]){
	int n=list->index;
	int i,j,aux;
	
	//Se convierten las fechas de las actividades a enteros comparables
	int fechaAct[n];
	//Se obtienen las fechas de las actividades del segundo vector
	for (i=0;i<n;i++){
		fechaAct[i]=(actividadesOrdenadas[i]->fechaInicio.dia+actividadesOrdenadas[i]->fechaInicio.mes*(actividadesOrdenadas[i]->fechaInicio.anyo));
	}
	
	int auxAct;
	for (i=0;i<10;i++) {
		for (j=0;j<10-i;j++) {
			if (fechaAct[j]<fechaAct[j+1]){
				//Hace burbuja al vector que contiene un valor en relacion a la fecha de la actividad
				aux=fechaAct[j]; 
				fechaAct[j]=fechaAct[j+1]; 
				fechaAct[j+1]=aux;
				//Si hace burbuja a los elementos del vector de las fechas
				//Tambien lo hara en el vector de las actividades a ordenar
				auxAct=actividadesOrdenadas[j];
				actividadesOrdenadas[j]=actividadesOrdenadas[j+1];
				actividadesOrdenadas[j+1]=auxAct;
				printf("Entra al for \n");
			}
		}
	}
}

char* listToStringOrdenada(lista *list,act *actividades[]){
	int i;
	char output[8000]=" ";
	for (i=0;i<list->index;i++){
        strcat(output,activityToString(actividades[i]));
	}
	return output;
}

void printListOrdenada(lista *list,act *actividades[]){
	char outputFromList[8000]=" ";
	strcpy(outputFromList,listToStringOrdenada(list,actividades));
	printf("%s",outputFromList);
}

