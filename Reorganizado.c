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
	act *actividad;
	struct nodo *siguiente;
}NODO;

typedef struct{
	int index;
	struct nodo *cabezaLista;
}lista;

//Prototipos
int createActivity(lista *list,act *actividad);
int agregarNodo(lista *list,act *nuevaAct);
char* dateToString(fecha *d);
long int dateToDays(fecha *fecha);
int durationOfActivity(fecha *fechaI,fecha *fechaF);
char* activityToString(act *acti);
char* listToString(lista *list);
void printList(lista *list);
int findById(lista *list,int *idToFind);
int updateActivity(lista *list,struct nodo *positionFound,act *newAct);
int deleteActivity(lista *list,struct nodo *positionFound);
void rellenarVectorOrdenado(lista *list,act **actividadesOrdenadas);
void ordenarLista(lista *list,act **actividadesOrdenadas);
char* listToStringOrdenada(lista *list,act **actividades);
void printListOrdenada(lista *list,act **actividades);
void ordenarListaDuracion(lista *list,act **actividadesOrdenadasDuracion);

int main()
{
	srand (time(NULL));
	
	//Se declara el struct de tipo lista llamado list
	lista list;
	list.index=0;
	list.cabezaLista=NULL;
	
	//Se rellenan las 10 actividades
	act actividades[10];
	int i;
	for (i=0;i<10;i++){
		actividades[i].id=i+1;
		strcpy(actividades[i].titulo,"Actividad");
		strcpy(actividades[i].prioridad,"Alta");
		actividades[i].fechaInicio.dia=rand()%31+1;
		actividades[i].fechaInicio.mes=rand()%12+1;
		actividades[i].fechaInicio.anyo=2019;
		actividades[i].fechaFin.dia=20+i;
		actividades[i].fechaFin.mes=10;
		actividades[i].fechaFin.anyo=2020;
	}
	
	//Se crean las 10 actividades y se guarda su direccion en un apuntador
	act *actividad1=createActivity(&list,&actividades[0]);
	act *actividad2=createActivity(&list,&actividades[1]);
	act *actividad3=createActivity(&list,&actividades[2]);
	act *actividad4=createActivity(&list,&actividades[3]);
	act *actividad5=createActivity(&list,&actividades[4]);
	act *actividad6=createActivity(&list,&actividades[5]);
	act *actividad7=createActivity(&list,&actividades[6]);
	act *actividad8=createActivity(&list,&actividades[7]);
	act *actividad9=createActivity(&list,&actividades[8]);
	act *actividad10=createActivity(&list,&actividades[9]);
	
	//Se generan los 10 nodos con sus respectivas actividades
	int counterAux=0;
	counterAux=counterAux+agregarNodo(&list,actividad1);
	counterAux=counterAux+agregarNodo(&list,actividad2);
	counterAux=counterAux+agregarNodo(&list,actividad3);
	counterAux=counterAux+agregarNodo(&list,actividad4);
	counterAux=counterAux+agregarNodo(&list,actividad5);
	counterAux=counterAux+agregarNodo(&list,actividad6);
	counterAux=counterAux+agregarNodo(&list,actividad7);
	counterAux=counterAux+agregarNodo(&list,actividad8);
	counterAux=counterAux+agregarNodo(&list,actividad9);
	counterAux=counterAux+agregarNodo(&list,actividad10);
	//Se comprueba si se generaron las 10 actividades
	if (counterAux==10){
		printf("Las (10) actividades se generaron con exito\n");
	}else {
		printf("No hubo espacio suficiente para generar algunas actividades\n");
	}
	
	//Se hace un vector donde se ordenaran las actividades segun su fecha de inicio
	act *actividadesOrdenadas=(act**)malloc(list.index*sizeof(act*));
	
	//Se hace otro vector para las actividades ordenadas por duracion
	act *actividadesOrdenadasDuracion=(act**)malloc(list.index*sizeof(act*));
	
	//
	int opcion=0;
	while (opcion!=6){
		printf("\nIngresa una opcion del menu \n");
		printf("Opcion 1. Mostrar actividades \n");
		printf("Opcion 2. Modificar actividad \n");
		printf("Opcion 3. Eliminar actividades \n");
		printf("Opcion 4. Imprimir ordenadamente las actividades (Ascendente por fecha) \n");
		printf("Opcion 5. Imprimir ordenadamente las actividades (Por duracion en dias) \n");
		printf("Opcion 6. Salir \n");
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
			struct nodo *positionFound=findById(&list,&idToFind);
			if (positionFound!=NULL){
				printf("---Vamos a actualizar la actividad %d--- \n",positionFound->actividad->id);
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
			if (updateActivity(&list,positionFound,&newAct)==2){
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
				printf("La actividad con este id es la actividad %d \n",positionFound->actividad->id);
			}
			if (deleteActivity(&list,positionFound)==1){
				printf("La actividad se elimino con exito \n");
			}else{
      			printf("No se encontro una actividad con ese id \n");
			}
		}else if (opcion == 4){
			system("cls");
			rellenarVectorOrdenado(&list,actividadesOrdenadas);
			ordenarLista(&list,actividadesOrdenadas);
			printListOrdenada(&list,actividadesOrdenadas);
			printf("\nSe imprimieron ordenadamente las actividades (Ascendente por fecha)\n");
		}else if (opcion == 5){
			system("cls");
			rellenarVectorOrdenado(&list,actividadesOrdenadasDuracion);
			ordenarListaDuracion(&list,actividadesOrdenadasDuracion);
			printListOrdenada(&list,actividadesOrdenadasDuracion);
			printf("\nSe imprimieron ordenadamente las actividades (Por duracion en dias)\n");
		}
	}
	//
	
	
	//Se hace free a la memoria usada
	struct nodo *indice;
	struct nodo *anterior=NULL;
	indice=list.cabezaLista;
	while (indice!=NULL){
		anterior=indice;
		indice=indice->siguiente;
		free(anterior->actividad);
		free(anterior);
	}
	free(actividadesOrdenadas);
	free(actividadesOrdenadasDuracion);
	return 0;
}

//---------APARTADO DE FUNCIONES----------

int createActivity(lista *list,act *actividad){
	act *nuevaActividad;
	nuevaActividad=(act*)malloc(sizeof(act));
	if (nuevaActividad!=NULL){
		*nuevaActividad=*actividad;
	}
	return nuevaActividad;
}

int agregarNodo(lista *list,act *nuevaAct){
	int flag=0;
	struct nodo *nuevoNodo;
	nuevoNodo=(struct nodo*)malloc(sizeof(struct nodo));
	
	if (list->index>0 && nuevoNodo!=NULL){
		struct nodo *indice;
		indice=list->cabezaLista;
		long int duracionNuevaActividad=dateToDays(&nuevaAct->fechaInicio);
		if (duracionNuevaActividad<dateToDays(&indice->actividad->fechaInicio)){
			nuevoNodo->siguiente=list->cabezaLista;
			list->cabezaLista=nuevoNodo;
			nuevoNodo->actividad=nuevaAct;
		}else{
			struct nodo *buscado;
			while (indice!=NULL && duracionNuevaActividad>=dateToDays(&indice->actividad->fechaInicio)){
				buscado=indice;
				indice=indice->siguiente;
			}
			buscado->siguiente=nuevoNodo;
			nuevoNodo->actividad=nuevaAct;
			nuevoNodo->siguiente=indice;
		}
		list->index++;
		flag=1;
	}else if (list->index==0 && nuevoNodo!=NULL){
		list->cabezaLista=nuevoNodo;
		nuevoNodo->actividad=nuevaAct;
		nuevoNodo->siguiente=NULL;
		list->index++;
		flag=1;
	}
	return flag;
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

long int dateToDays(fecha *fecha){
	long int dias=0;
	if(fecha->mes%2==0 && fecha->mes<9){
		dias= ((fecha->anyo-1)*365 + (fecha->mes-1)*31 + fecha->dia);
	}else if(fecha->mes%2==0 && fecha->mes>9){
		dias= ((fecha->anyo-1)*365 + (fecha->mes-1)*30 + fecha->dia);
	}else if(fecha->mes%2!=0 && fecha->mes==1){
		dias= ((fecha->anyo-1)*365 + fecha->dia);
	}else if(fecha->mes%2!=0 && fecha->mes==3){
		dias= ((fecha->anyo-1)*365 + (fecha->mes-1)*28 + fecha->dia);
	}else if(fecha->mes%2!=0 && fecha->mes<8){
		dias= ((fecha->anyo-1)*365 + (fecha->mes-1)*30 + fecha->dia);
	}else if(fecha->mes%2!=0 && fecha->mes>8){
		dias= ((fecha->anyo-1)*365 + (fecha->mes-1)*31 + fecha->dia);
	}
	//Si es anio bisiesto y ya paso febrero se agrega un dia (29 de febrero)
	if (fecha->anyo%4==0 && fecha->anyo%100!=0 && fecha->anyo%400==0){
		if (fecha->mes>2){
			dias=dias+1;
		}
	}
	//Se agregan los dias de cada anio bisiesto entre el dia 0 y el dia de la fecha
	long int i,counterBisiesto=0;
	for (i=0;i<fecha->anyo-1;i++){
		if (fecha->anyo%400==0 && fecha->anyo%100!=0 && fecha->anyo%4==0){
			counterBisiesto++;
		}
	}
	dias=dias+counterBisiesto;
	
	return dias;
}

int durationOfActivity(fecha *fechaI,fecha *fechaF){
	long int duration=0;
	long int dias1=0;
	long int dias2=0;
	dias1=dateToDays(fechaI);
	dias2=dateToDays(fechaF);	
	duration=dias2-dias1;
	return duration;
}

char* activityToString(act *acti){
	char output[800]={"---ACTIVIDAD "};
	char auxForAll[6];
	char duracion[10];
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
	strcat(output,"\nLa duracion de la actividad es: ");
	sprintf(duracion,"%d",durationOfActivity(&acti->fechaInicio,&acti->fechaFin));
	strcat(output,duracion);
	strcat(output," dias");
	strcat(output,"\n");
	return output;
}

char* listToString(lista *list){
	int i;
	char output[8000]=" ";
	struct nodo *indice;
	for (indice=list->cabezaLista;indice!=NULL;indice=indice->siguiente){
		strcat(output,activityToString(indice->actividad));
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
		if (indice->actividad->id==*idToFind){
			indiceFound=indice;
			break;
		}
	}
	return indiceFound;
}

int updateActivity(lista *list,struct nodo *positionFound,act *newAct){
	int flagUpdate=0;
	flagUpdate=flagUpdate+deleteActivity(list,positionFound);
	if (flagUpdate==1){
		flagUpdate=flagUpdate+agregarNodo(list,newAct);
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
				if (positionFound->siguiente==NULL){
					anterior->siguiente=NULL;
					free (positionFound->actividad);
					free (positionFound);
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

void rellenarVectorOrdenado(lista *list,act **actividadesOrdenadas){
	struct nodo *indice;
	int counterAux=0;
	for (indice=list->cabezaLista;indice!=NULL;indice=indice->siguiente){
		actividadesOrdenadas[counterAux]=indice->actividad;
		counterAux++;
	}
}

void ordenarLista(lista *list,act **actividadesOrdenadas){
	int n=list->index;
	int i,j;
	long int dias1,dias2;
	act *aux;
	for (i=0;i<n;i++) {
		for (j=0;j<n-1;j++) {
			dias1=0;
			dias2=0;
			dias1=dateToDays(&actividadesOrdenadas[j]->fechaInicio);
			dias2=dateToDays(&actividadesOrdenadas[j+1]->fechaInicio);
			if (dias1<=dias2){
				//Falta estructurar el burbuja
				aux=actividadesOrdenadas[j]; 
				actividadesOrdenadas[j]=actividadesOrdenadas[j+1]; 
				actividadesOrdenadas[j+1]=aux;
			}
		}
	}
}

char* listToStringOrdenada(lista *list,act **actividades){
	int i;
	char output[8000]=" ";
	for (i=0;i<list->index;i++){
        strcat(output,activityToString(actividades[i]));
	}
	return output;
}

void printListOrdenada(lista *list,act **actividades){
	char outputFromList[8000]=" ";
	strcpy(outputFromList,listToStringOrdenada(list,actividades));
	printf("%s",outputFromList);
}

void ordenarListaDuracion(lista *list,act **actividadesOrdenadasDuracion){
	int n=list->index;
	int i,j;
	long int dias1,dias2;
	act *aux;
	for (i=0;i<n;i++) {
		for (j=0;j<n-1;j++) {
			dias1=0;
			dias2=0;
			dias1=durationOfActivity(&actividadesOrdenadasDuracion[j]->fechaInicio,&actividadesOrdenadasDuracion[j]->fechaInicio);
			dias2=durationOfActivity(&actividadesOrdenadasDuracion[j+1]->fechaInicio,&actividadesOrdenadasDuracion[j+1]->fechaInicio);
			if (dias1<=dias2){
				//Falta estructurar el burbuja
				aux=actividadesOrdenadasDuracion[j]; 
				actividadesOrdenadasDuracion[j]=actividadesOrdenadasDuracion[j+1]; 
				actividadesOrdenadasDuracion[j+1]=aux;
			}
		}
	}
}




