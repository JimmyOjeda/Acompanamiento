#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int day;
	int month;
	int year;
}date;

typedef struct{
   	int id;
   	char tittle[20];
   	char priority[5];
   	date startDate;
   	date endDate;
}act;

typedef struct nodo{
	act *activity;
	struct nodo *next;
}NODO;

typedef struct{
	int index;
	struct nodo *headList;
}lista;

typedef struct{
	lista *list;
	char name[10];
}persona;

//Prototipos para CRUD de personas
void printPersonList(int *indexPersons,persona *listPersons[]);
int createPerson(int *indexPersons,char name[],act *activities);
int setActivityList(persona *personX,act *activity);
int createActivityList(persona *personX);
int findByUserName(int *indexPersons,persona *listPersons[],char *nameToFind[]);
int updateUserName(persona *listPersons[],int *personFound,char *newName[]);
int deleteUser(int *indexPersons,persona *listPersons[],int *personFound);

//Prototipos para lista de actividades
int createActivity(lista *list,act *activity);
int addNodo(lista *list,act *nuevaAct);
char* dateToString(date *date);
long int dateToDays(date *date);
int durationOfActivity(date *startDate,date *endDate);
char* activityToString(act *acti);
char* listToString(lista *list);
void printList(lista *list);
int findById(lista *list,int *idToFind);
int updateActivity(lista *list,struct nodo *positionFound,act *newAct);
int deleteActivity(lista *list,struct nodo *positionFound);
void fillSortedVector(lista *list,act **sortedActivities);
int compareDays(date *date1,date *date2);
void sortList(lista *list,act **sortedActivities);
char* sortedListToString(lista *list,act **activities);
void printSortedList(lista *list,act **activities);
int compareDuration(date *sDate1,date *eDate1,date *sDate2,date *eDate2);
void sortDurationList(lista *list,act **durationSortedActivities);

int main()
{
	srand (time(NULL));
	
	//Se generan 10 actividades
	act activities[10];
	int i;
	for (i=0;i<10;i++){
		activities[i].id=i+1;
		strcpy(activities[i].tittle,"Actividad");
		strcpy(activities[i].priority,"Alta");
		activities[i].startDate.day=rand()%31+1;
		activities[i].startDate.month=rand()%12+1;
		activities[i].startDate.year=2019;
		activities[i].endDate.day=20+i;
		activities[i].endDate.month=10;
		activities[i].endDate.year=2020;
	}
	
	//Se hace un vector de personas y se crean y se guardan las 5 personas en el vector
	int indexPersons=0;
	persona **listPersons=(persona**)malloc(5*sizeof(persona*));
	listPersons[0]=createPerson(&indexPersons,"Jose",activities);
	listPersons[1]=createPerson(&indexPersons,"Jairo",activities);
	listPersons[2]=createPerson(&indexPersons,"Raul",activities);
	listPersons[3]=createPerson(&indexPersons,"Luis",activities);
	listPersons[4]=createPerson(&indexPersons,"Pedro",activities);
	
	//Se hace un vector donde se ordenaran las actividades segun su fecha de inicio
	act *sortedActivities=(act*)malloc(10*sizeof(act));
	
	//Se hace otro vector para las actividades ordenadas por duracion
	act *durationSortedActivities=(act*)malloc(10*sizeof(act));
	
	int optionWhatToDo=0;
	while (optionWhatToDo!=3){
		printf("----MENU PRINCIPAL----\n");
		printf("Que quieres hacer? \n(Ingresa el numero de la opcion)\n");
		printf("1. Administrar mis usuarios\n");
		printf("2. Administrar las listas de actividades de mis usuarios\n");
		printf("3. Salir \n");
		scanf("%d",&optionWhatToDo);
		system("cls");
		if (optionWhatToDo==1){
			int optionPerson1=0;
			while (optionPerson1!=4){
				printf("\nIngresa una opcion del menu \n");
				printf("Opcion 1. Mostrar usuarios \n");
				printf("Opcion 2. Modificar nombres de usuario \n");
				printf("Opcion 3. Eliminar usuarios \n");
				printf("Opcion 4. Regresar al menu principal \n");
				scanf("%d",&optionPerson1);
				system("cls");
				
				if (optionPerson1==1){
					printPersonList(&indexPersons,listPersons);
				}else if (optionPerson1==2){
					char nameToFind[10];
					printf("Introduce el nombre del usuario que quieres modificar:\n");
					scanf("%s",nameToFind);
					int userFound=findByUserName(&indexPersons,listPersons,nameToFind);
					if (userFound!=-1){
						char newName[10];
						printf("Vamos a modificar el nombre de %s\n",listPersons[userFound]->name);
						printf("Ingresa el nuevo nombre: (No mayor a 9 letras) \n");
						scanf("%s",newName);
						if (updateUserName(listPersons,&userFound,newName)==1){
							printf("Listo! Ahora el usuario se llama: %s\n",listPersons[userFound]->name);
						}
					}else {
						printf("No hay un usuario con ese nombre\n");
					}
				}else if (optionPerson1==3){
					char nameToFind[10];
					printf("Introduce el nombre del usuario que quieres eliminar:\n");
					scanf("%s",nameToFind);
					int userFound=findByUserName(&indexPersons,listPersons,nameToFind);
					if (userFound!=-1){
						printf("Vamos a eliminar al usuario llamado %s\n",listPersons[userFound]->name);
						if (deleteUser(&indexPersons,listPersons,&userFound)==1){
							printf("Listo! El usuario llamado %s fue eliminado",nameToFind);
						}
					}else {
						printf("No hay un usuario con ese nombre\n");
					}
				}
			}
			
		}else if (optionWhatToDo==2){
			int optionPerson=0;
			while (optionPerson!=6){
				printf("Ingresa el numero correspondiente a tu usuario (%d usuarios disponibles) \n",indexPersons);
				printPersonList(&indexPersons,listPersons);
				printf("6. Para regresar al menu principal \n");
				scanf("%d",&optionPerson);
				system("cls");
				
				int option=0;
				while (optionPerson!=6 && option!=6 && optionPerson<=indexPersons && (optionPerson==1 || optionPerson==2 || 
																	optionPerson==3 || optionPerson==4 || optionPerson==5)){
					lista *list=listPersons[optionPerson-1]->list;
					printf("\nEstamos trabajando con la lista de %s",listPersons[optionPerson-1]->name);
					printf("\nIngresa una opcion del menu \n");
					printf("Opcion 1. Mostrar actividades \n");
					printf("Opcion 2. Modificar actividad \n");
					printf("Opcion 3. Eliminar actividades \n");
					printf("Opcion 4. Imprimir ordenadamente las actividades (Ascendente por fecha) \n");
					printf("Opcion 5. Imprimir ordenadamente las actividades (Por duracion en dias) \n");
					printf("Opcion 6. Seleccionar otro usuario \n");
					scanf("%d",&option);
					if (option == 1){
						system("cls");
						printList(list);
					}else if (option == 2){
						system("cls");
						int idToFind,newSDay,newSMonth,newSYear,newEDay,newEMonth,newEYear;
						char newTittle[20];
						char newPriority[5];
						act newAct;
						printf("Ingresa el id de la actividad a actualizar:\n");
						scanf("%d",&idToFind);
						struct nodo *positionFound=findById(list,&idToFind);
						if (positionFound!=NULL){
							printf("---Vamos a actualizar la actividad %d--- \n",positionFound->activity->id);
		   		   			printf("Ingresa el nuevo titulo de la actividad: \n");
		   					scanf("%s",newTittle);
							printf("Ingresa la nueva prioridad de la actividad: \n");
		   		 			scanf("%s",newPriority);
		   			 		printf("Ingresa la nueva fecha de inicio de la actividad: \n");
		   		 			printf("Ingresa dia, mes y anio (ingresa y presiona enter) en ese orden \n");
		   		 			scanf("%d",&newSDay);
		   		 			scanf("%d",&newSMonth);
		   	 				scanf("%d",&newSYear);
		   	 				printf("Ingresa la nueva fecha de inicio de la actividad: \n");
		    				printf("Ingresa dia, mes y anio (ingresa y presiona enter) en ese orden \n");
		    				scanf("%d",&newEDay);
		    				scanf("%d",&newEMonth);
		    				scanf("%d",&newEYear);
		    				//Asignacion de valores a la actividad a mandar
		    				newAct.id=idToFind;
		    				strcpy(newAct.tittle,newTittle);
		    				strcpy(newAct.priority,newPriority);
		    				newAct.startDate.day=newSDay;
		    				newAct.startDate.month=newSMonth;
		    				newAct.startDate.year=newSYear;
		    				newAct.endDate.day=newEDay;
		    				newAct.endDate.month=newEMonth;
		    				newAct.endDate.year=newEYear;
						}
						if (updateActivity(list,positionFound,&newAct)==2){
							printf("La actividad se actualizo con exito \n");
						}else {
	      					printf("No se encontro una actividad con ese id \n");
						}
					}else if (option == 3){
						system("cls");
						int idToFind;
						printf("Ingresa el id de la actividad a eliminar: \n");
						scanf("%d",&idToFind);
						struct nodo *positionFound=findById(list,&idToFind);
						if (positionFound!=NULL){
							printf("La actividad con este id es la actividad %d \n",positionFound->activity->id);
						}
						if (deleteActivity(list,positionFound)==1){
							printf("La actividad se elimino con exito \n");
						}else{
   	   					printf("No se encontro una actividad con ese id \n");
						}
					}else if (option == 4){
						system("cls");
						fillSortedVector(list,sortedActivities);
						sortList(list,sortedActivities);
						printSortedList(list,sortedActivities);
						printf("\nSe imprimieron ordenadamente las actividades (Ascendente por fecha)\n");
					}else if (option == 5){
						system("cls");
						fillSortedVector(list,durationSortedActivities);
						sortDurationList(list,durationSortedActivities);
						printSortedList(list,durationSortedActivities);
						printf("\nSe imprimieron ordenadamente las actividades (Por duracion en dias)\n");
					}
				}
				system("cls");
			}
		}
	//Aqui abajo cierra el primer while
	}
	
	//Se hace free a la memoria usada
	for (i=0;i<indexPersons;i++){
		struct nodo *index;
		struct nodo *anterior=NULL;
		index=listPersons[i]->list->headList;
		while (index!=NULL){
			anterior=index;
			index=index->next;
			free(anterior->activity);
			free(anterior);
		}
		free(listPersons[i]->list);
		free(listPersons[i]);
	}
	free(listPersons);
	free(sortedActivities);
	free(durationSortedActivities);
	printf("La memoria se libero correctamente");
	return 0;
}

/*--------------------------------------APARTADO DE FUNCIONES--------------------------------------*/

/*---------FUNCIONES PARA CRUD DE USUARIOS--------*/

void printPersonList(int *indexPersons,persona *listPersons[]){
	int i;
	for (i=0;i<*indexPersons;i++){
		printf("%d. %s  --- %d actividades\n",i+1,listPersons[i]->name,listPersons[i]->list->index);
	}
	return 0;
}

int createPerson(int *indexPersons,char name[],act *activities){
	persona *person=(persona*)malloc(sizeof(persona));
	if (person!=NULL){
		strcpy(person->name,name);
		setActivityList(person,activities);
		*indexPersons=*indexPersons+1;
	}
	return person;
}

int setActivityList(persona *personX,act *activity){
	int flag=0;
	//Se crea la lista para la persona y se enlaza con su elemento *list
	if (createActivityList(personX)==1){
			//Se crean las 10 actividades y se guarda su direccion en un apuntador
		act *activity1=createActivity(personX->list,&activity[0]);
		act *activity2=createActivity(personX->list,&activity[1]);
		act *activity3=createActivity(personX->list,&activity[2]);
		act *activity4=createActivity(personX->list,&activity[3]);
		act *activity5=createActivity(personX->list,&activity[4]);
		act *activity6=createActivity(personX->list,&activity[5]);
		act *activity7=createActivity(personX->list,&activity[6]);
		act *activity8=createActivity(personX->list,&activity[7]);
		act *activity9=createActivity(personX->list,&activity[8]);
		act *activity10=createActivity(personX->list,&activity[9]);
		
		//Se generan los 10 nodos con sus respectivas actividades
		int counterAux=0;
		counterAux=counterAux+addNodo(personX->list,activity1);
		counterAux=counterAux+addNodo(personX->list,activity2);
		counterAux=counterAux+addNodo(personX->list,activity3);
		counterAux=counterAux+addNodo(personX->list,activity4);
		counterAux=counterAux+addNodo(personX->list,activity5);
		counterAux=counterAux+addNodo(personX->list,activity6);
		counterAux=counterAux+addNodo(personX->list,activity7);
		counterAux=counterAux+addNodo(personX->list,activity8);
		counterAux=counterAux+addNodo(personX->list,activity9);
		counterAux=counterAux+addNodo(personX->list,activity10);
		if (counterAux==10){
			flag=1;
		}
	}
	return flag;
}

int createActivityList(persona *personX){
	int flag=0;
	lista *list;
	list=(lista*)malloc(sizeof(lista));
	if (list!=NULL){
		personX->list=list;
		personX->list->index=0;
		personX->list->headList=NULL;
		flag=1;
	}
	return flag;
}

int findByUserName(int *indexPersons,persona *listPersons[],char *nameToFind[]){
	int userFound=-1;
	int i;
	for (i=0;i<*indexPersons;i++){
		if (strcmp(listPersons[i]->name,nameToFind)==0) {
			userFound=i;
			break;
		}
	}
	return userFound;
}

int updateUserName(persona *listPersons[],int *personFound,char *newName[]){
	int flag=0;
	if (*personFound!=-1){
		strcpy(listPersons[*personFound]->name,newName);
		flag=1;
	}
	return flag;
}

int deleteUser(int *indexPersons,persona *listPersons[],int *personFound){
	int flag=0;
	int auxIndexPerson=*indexPersons-1;
	int i;
	for (i=*personFound;i<auxIndexPerson;i++){
        listPersons[i] = listPersons[i+1];
	}
	struct nodo *index;
	struct nodo *anterior=NULL;
	index=listPersons[auxIndexPerson]->list->headList;
	while (index!=NULL){
		anterior=index;
		index=index->next;
		free(anterior->activity);
		free(anterior);
	}
	free(listPersons[auxIndexPerson]->list);
	free(listPersons[auxIndexPerson]);
	*indexPersons=*indexPersons-1;
	flag=1;
	return flag;
}

/*----------------FUNCIONES PARA CRUD DE LISTAS DE ACTIVIDADES---------------*/

//Recibe una actividad para tomar sus valores y los vierte en otra actividad que crea con malloc
int createActivity(lista *list,act *activity){
	act *newactivity;
	newactivity=(act*)malloc(sizeof(act));
	if (newactivity!=NULL){
		*newactivity=*activity;
	}
	return newactivity;
}

//Recibe un apuntador a una actividad (ya en su posicion con malloc)
//Hace malloc para un nuevo nodo y asigna el apuntador a actividad a su elemento *actividad
int addNodo(lista *list,act *nuevaAct){
	int flag=0;
	struct nodo *nuevoNodo;
	nuevoNodo=(struct nodo*)malloc(sizeof(struct nodo));
	//Verifica: Es el primer nodo o es cualquier otro
	if (list->index>0 && nuevoNodo!=NULL){
		struct nodo *index;
		index=list->headList;
		long int newActivityDuration=dateToDays(&nuevaAct->startDate);
		//Si el nodo a insertar es menor (por fecha) que la cabeza de la lista
		//Se situa el nodo como nueva cabeza y se enlaza con la anterior cabeza
		if (newActivityDuration<dateToDays(&index->activity->startDate)){
			nuevoNodo->next=list->headList;
			list->headList=nuevoNodo;
			nuevoNodo->activity=nuevaAct;
		}else{
			//Si es mayor (por fecha) que la cabeza, recorremos la lista
			//hasta encontrar un nodo que sea mayor (por fecha) que el que vamos a insertar
			//y se situa el nuevo nodo justo detras del que es mayor
			struct nodo *buscado;
			while (index!=NULL && newActivityDuration>=dateToDays(&index->activity->startDate)){
				buscado=index;
				index=index->next;
			}
			buscado->next=nuevoNodo;
			nuevoNodo->activity=nuevaAct;
			nuevoNodo->next=index;
		}
		list->index++;
		flag=1;
	}else if (list->index==0 && nuevoNodo!=NULL){
		list->headList=nuevoNodo;
		nuevoNodo->activity=nuevaAct;
		nuevoNodo->next=NULL;
		list->index++;
		flag=1;
	}
	return flag;
}

//Recibe una fecha y la devuelve como string
char* dateToString(date *d){
	char output[10]=" ";
	char auxDay[3];
	char auxMonth[3];
	char auxYear[5];

	//Se hace una string con la fecha 
	char sentenceStart[10]=" ";
	sprintf(auxDay,"%d",d->day);
	strcat(sentenceStart,auxDay);
	strcat(sentenceStart,"/");
	sprintf(auxMonth,"%d",d->month);
	strcat(sentenceStart,auxMonth);
	strcat(sentenceStart,"/");
	sprintf(auxYear,"%d",d->year);
	strcat(sentenceStart,auxYear);
	strcat(output,sentenceStart);

	return output;
}

//Recibe una fecha y devuelve los dias (contando los de los anios bisiestos)
//entre el dia 0 y la fecha dada
long int dateToDays(date *date){
	long int days=0;
	if(date->month==1){
		days=date->day;
	}else if(date->month==2){
		days=date->day+31;
	}else if(date->month==3){
		days=date->day+58;
	}else if(date->month==4){
		days=date->day+90;
	}else if(date->month==5){
		days=date->day+120;
	}else if(date->month==6){
		days=date->day+151;
	}else if(date->month==7){
		days=date->day+181;
	}else if(date->month==8){
		days=date->day+212;
	}else if(date->month==9){
		days=date->day+243;
	}else if(date->month==10){
		days=date->day+273;
	}else if(date->month==11){
		days=date->day+304;
	}else if(date->month==12){
		days=date->day+334;
	}
	days=days+(date->year*365);
	//Si es anio bisiesto y ya paso febrero se agrega un dia (29 de febrero)
	if (date->year%4==0){
		if (date->year%100==0){
			if (date->year%400==0){
				days=days+1;
			}
		}else {
			days=days+1;
		}
	}
	//Se agregan los dias de cada anio bisiesto entre el dia 0 y el dia de la fecha
	long int i,counterBisiesto=0;
	for (i=0;i<date->year-1;i++){
		if (i%4==0){
			if (i%100==0){
				if (i%400==0){
					counterBisiesto=counterBisiesto+1;
				}
			}else {
				counterBisiesto=counterBisiesto+1;
			}
		}
	}
	days=days+counterBisiesto;
	
	return days;
}

//Recibe una fecha de inicio y una fecha de fin
//Calcula los dias de cada fecha y resta los del inicio a los del fin
//Devuelve la duracion de la actividad
int durationOfActivity(date *startDate,date *endDate){
	long int duration=0;
	long int days1=0;
	long int days2=0;
	days1=dateToDays(startDate);
	days2=dateToDays(endDate);	
	duration=days2-days1;
	return duration;
}

//Recibe una actividad y devuelve una string que proporciona sus datos
char* activityToString(act *acti){
	char output[800]={"---ACTIVIDAD "};
	char auxForAll[6];
	char duration[10];
	char outputFromDate[12]=" ";

	sprintf(auxForAll,"%d",acti->id);
	strcat(output,auxForAll);
	strcat(output,"---\nEl id de la actividad es: ");
	sprintf(auxForAll,"%d",acti->id);
	strcat(output,auxForAll);
	strcat(output,"\nEl titulo de la actividad es: ");
	strcat(output,acti->tittle);
	strcat(output,"\nLa prioridad de la actividad es: ");
	strcat(output,acti->priority);
	strcat(output,"\nLa fecha de inicio de la actividad es:");
	strcpy(outputFromDate,dateToString(&acti->startDate));
	strcat(output,outputFromDate);
	strcat(output,"\nLa fecha de fin de la actividad es:");
	strcpy(outputFromDate,dateToString(&acti->endDate));
	strcat(output,outputFromDate);
	strcat(output,"\nLa duracion de la actividad es: ");
	sprintf(duration,"%d",durationOfActivity(&acti->startDate,&acti->endDate));
	strcat(output,duration);
	strcat(output," dias");
	strcat(output,"\n");
	return output;
}

//Concatena todas las strings generadas con la funcion anterior
char* listToString(lista *list){
	int i;
	char output[8000]=" ";
	struct nodo *index;
	for (index=list->headList;index!=NULL;index=index->next){
		strcat(output,activityToString(index->activity));
	}
	return output;
}

//Llama a la funcion que concatena las strings con los datos de las
//actividades para devolverlos
void printList(lista *list){
	char outputFromList[8000]=" ";
	strcpy(outputFromList,listToString(list));
	printf("%s",outputFromList);
}

//Recibe un id y recorre la lista en busca del nodo con la actividad que contiene dicho id
//Si no encuentra coincidencias devuelve un apuntador NULL
int findById(lista *list,int *idToFind){
	struct nodo *index,*indexFound=NULL;
	for (index=list->headList;index!=NULL;index=index->next){
		if (index->activity->id==*idToFind){
			indexFound=index;
			break;
		}
	}
	return indexFound;
}

//Recibe una actividad que contiene los nuevos datos y la direccion de memoria
//del nodo que contiene la actividad a actualizar
//Primero elimina el nodo y luego genera uno nuevo con la informacion recibida
//Al generar un nuevo nodo se inserta ordenadamente
int updateActivity(lista *list,struct nodo *positionFound,act *newAct){
	int flagUpdate=0;
	flagUpdate=flagUpdate+deleteActivity(list,positionFound);
	if (flagUpdate==1){
		flagUpdate=flagUpdate+addNodo(list,newAct);
	}
	return flagUpdate;
}

//Recibe la direccion de memoria del nodo que contiene la actividad a eliminar
//Pueden haber 3 situaciones: El nodo es la cabeza, el nodo se encuentra en medio de la lista
//o el nodo es el ultimo elemento de la lista
int deleteActivity(lista *list,struct nodo *positionFound){
	int flagDelete=0;
	struct nodo *actual;
	struct nodo *anterior;
	struct nodo *auxForFree;
	if (positionFound!=NULL){
		for (actual=list->headList;actual!=positionFound->next;actual=actual->next){
			if (actual==positionFound){
				//Si es el la cabeza de la lista...
				if (positionFound==list->headList){
					auxForFree=list->headList;
					list->headList=list->headList->next;
					free (auxForFree);
				}else
				//Si es el ultimo elemento de la lista...
				if (positionFound->next==NULL){
					anterior->next=NULL;
					free (positionFound->activity);
					free (positionFound);
				}else {
					//Si se encuentra dentro de la lista (no al prinicipio ni al final)...
					anterior->next=actual->next;
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

//Recibe un vector en el cual va a vaciar las direcciones de las actividades de la lista
void fillSortedVector(lista *list,act **sortedActivities){
	struct nodo *index;
	int counterAux=0;
	for (index=list->headList;index!=NULL;index=index->next){
		sortedActivities[counterAux]=index->activity;
		counterAux++;
	}
}

int compareDays(date *date1,date *date2){
	int flag=0;
	int days1,days2;
	days1=dateToDays(date1);
	days2=dateToDays(date2);
	if (days1<days2){
		flag=1;
	}
	return flag;
}

//Hace comparaciones entre las fechas de las actividades
//y reordena el vector(rellenado en la funcion anterior)
//de forma ascendente (por fecha) con un ordenamiento burbuja 
void sortList(lista *list,act **sortedActivities){
	int n=list->index;
	int i,j;
	long int days1,days2;
	act *aux;
	for (i=0;i<n;i++) {
		for (j=0;j<n-1;j++) {
			days1=0;
			days2=0;
			if (compareDays(&sortedActivities[j]->startDate,&sortedActivities[j+1]->startDate)==1){
				aux=sortedActivities[j]; 
				sortedActivities[j]=sortedActivities[j+1]; 
				sortedActivities[j+1]=aux;
			}
		}
	}
}

//Concatena todas las strings generadas con la funcion activityToString
//mandando una por una las actividades ordenadas del vector ordenado (por fecha)
char* sortedListToString(lista *list,act **activities){
	int i;
	char output[8000]=" ";
	for (i=0;i<list->index;i++){
        strcat(output,activityToString(activities[i]));
	}
	return output;
}

//Imprime la string resultante de la funcion anterior
void printSortedList(lista *list,act **activities){
	char outputFromList[8000]=" ";
	strcpy(outputFromList,sortedListToString(list,activities));
	printf("%s",outputFromList);
}

int compareDuration(date *sDate1,date *eDate1,date *sDate2,date *eDate2){
	int flag=0;
	int duration1,duration2;
	duration1=durationOfActivity(sDate1,eDate2);
	duration2=durationOfActivity(sDate1,eDate2);
	if (duration1>=duration2){
		flag=1;
	}
	return flag;
}

//Hace comparaciones entre las duraciones de las actividades
//y reordena el vector recibido (otro vector para ordenar por duracion)
//de forma ascendente (por duracion) con un ordenamiento burbuja 
void sortDurationList(lista *list,act **durationSortedActivities){
	int n=list->index;
	int i,j;
	long int days1,days2;
	act *aux;
	for (i=0;i<n;i++) {
		for (j=0;j<n-1;j++) {
			days1=0;
			days2=0;
			if (compareDuration(&durationSortedActivities[j]->startDate,&durationSortedActivities[j]->endDate,
						&durationSortedActivities[j+1]->startDate,&durationSortedActivities[j+1]->endDate)==1){
				aux=durationSortedActivities[j]; 
				durationSortedActivities[j]=durationSortedActivities[j+1]; 
				durationSortedActivities[j+1]=aux;
			}
		}
	}
}
