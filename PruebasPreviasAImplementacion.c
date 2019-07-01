#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @struct date
 * @brief Representa una fecha
 */
typedef struct{
	int day;///< Dia de una fecha
	int month;///< Mes de una fecha
	int year;///< Anio de una fecha
}date;

/**
 * @struct act
 * @brief Representa una actividad
 */
typedef struct{
   	int id;///< Id unico para una actividad
   	char tittle[20];///< Titulo para una actividad
   	char priority[5];///< Prioridad de una actividad
   	date startDate;///< Fecha de inicio de una actividad
   	date endDate;///< Fecha en que termina una actividad
}act;

/**
 * @struct nodo
 * @brief Representa un nodo de una LSL
 */
typedef struct nodo{
	act *activity;///< Apuntador a una actividad
	struct nodo *next;///< Apuntador al siguiente nodo
};

/**
 * @struct lista
 * @brief Representa una lista de actividades
 */
typedef struct{
	int index;///< Indice que indica la cantidad de actividades de la lista
	struct nodo *headList;///< Apuntador al primer nodo de la lista
}lista;

/**
 * @struct persona
 * @brief Representa una persona con una lista de actividades
 */
typedef struct{
	lista *list;///< Lista de actividades perteneciente a una persona
	char name[10];///< Nombre de una persona
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

/**
 * @brief Regula la interaccion con el usuario, el usuario selecciona opciones y el main llama a las funciones
 * @return 0
 */
int main()
{
	srand (time(NULL));
	
	act activities[10];///< Crea un vector de 10 actividades
	int i;
	/**
 	 * Rellena el vector las actividades del vector
	 */
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
	
	
	int indexPersons=0;///< Inicializa un indice para saber cuantas personas existen
	/**
 	 * Se hace un vector de personas y se crean y guardan las 5 personas en el vector
	 */
	persona **listPersons=(persona**)malloc(5*sizeof(persona*));
	listPersons[0]=createPerson(&indexPersons,"Jose",activities);
	listPersons[1]=createPerson(&indexPersons,"Jairo",activities);
	listPersons[2]=createPerson(&indexPersons,"Raul",activities);
	listPersons[3]=createPerson(&indexPersons,"Luis",activities);
	listPersons[4]=createPerson(&indexPersons,"Pedro",activities);
	
	/**
 	 * Se hace un vector donde se ordenaran las actividades segun su fecha de inicio
	 */
	act *sortedActivities=(act*)malloc(10*sizeof(act));
	
	/**
 	 * Se hace otro vector donde se ordenaran las actividades segun su duracion
	 */
	act *durationSortedActivities=(act*)malloc(10*sizeof(act));
	
	int optionWhatToDo=0;
	/**
 	 * Se ejecutan un menu que lleva a otros dos, y uno de esos lleva a otro menu (4 menus en total)
 	 * Un menun para elegir si administrar personas o administrar las listas de las personas
 	 * Un menu para administrar personas (CRUD de personas)
 	 * Un menu para elegir una persona (para administrar su lista)
 	 * Un menu para administrar la lista de una persona
	 */
	while (optionWhatToDo!=3){
		printf("----MENU PRINCIPAL----\n");
		printf("(Ingresa el numero de la opcion)\n");
		printf("1. Administrar mis usuarios\n");
		printf("2. Administrar las listas de actividades de mis usuarios\n");
		printf("3. Salir \n");
		scanf("%d",&optionWhatToDo);
		system("cls");
		if (optionWhatToDo==1){///< Si se elige administrar personas se muetra un menu con las opciones para administrar
			printf("(%d usuarios disponibles) \n",indexPersons);
			printPersonList(&indexPersons,listPersons);///< Se imprime la lista de personas
			int optionPerson1=0;
			while (optionPerson1!=4){///< Se pregunta que quiere hacer con las personas
				printf("\nIngresa una opcion del menu \n");
				printf("Opcion 1. Mostrar usuarios \n");
				printf("Opcion 2. Modificar nombres de usuario \n");
				printf("Opcion 3. Eliminar usuarios \n");
				printf("Opcion 4. Regresar al menu principal \n");
				scanf("%d",&optionPerson1);
				system("cls");
				if (optionPerson1==1){///< Si presiona 1, se imprime la lista de personas
					printPersonList(&indexPersons,listPersons);
				}else if (optionPerson1==2){///< Si presiona 2, pregunta el nombre de la persona a modificar
					char nameToFind[10];
					printf("Introduce el nombre del usuario que quieres modificar:\n");
					scanf("%s",nameToFind);
					int userFound=findByUserName(&indexPersons,listPersons,nameToFind);///< Si el usuario es encontrado entonces pide 
																					///< el nuevo nombre y llama a la funcion update
					if (userFound!=-1){
						char newName[10];
						printf("Vamos a modificar el nombre de %s\n",listPersons[userFound]->name);
						printf("Ingresa el nuevo nombre: (No mayor a 9 letras) \n");
						scanf("%s",newName);
						if (updateUserName(listPersons,&userFound,newName)==1){///< Si el nombre se actualizo correctamente, lo imprime
							printf("Listo! Ahora el usuario se llama: %s\n",listPersons[userFound]->name);
						}else {
							printf("Hubo un fallo al actualizar el nombre");
						}
					}else {
						printf("No hay un usuario con ese nombre\n");
					}
				}else if (optionPerson1==3){///< Si presiona 3, pide el nombre de la persona a eliminar
					char nameToFind[10];
					printf("Introduce el nombre del usuario que quieres eliminar:\n");
					scanf("%s",nameToFind);
					int userFound=findByUserName(&indexPersons,listPersons,nameToFind);///< Verifica si hay alguna persona con ese nombre
					if (userFound!=-1){///< Si se encontro una persona con ese nombre entonces llama a la funcion delete
						printf("Vamos a eliminar al usuario llamado %s\n",listPersons[userFound]->name);
						if (deleteUser(&indexPersons,listPersons,&userFound)==1){
							printf("Listo! El usuario llamado %s fue eliminado",nameToFind);
						}
					}else {
						printf("No hay un usuario con ese nombre\n");
					}
				}
			}
		}else if (optionWhatToDo==2){///< Si se elige administrar la lista de usuarios
			int optionPerson=0;
			while (optionPerson!=6){///< Se imprime la lista de personas y se pregunta con que usuario se quiere trabajar
				printf("Ingresa el numero correspondiente a tu usuario (%d usuarios disponibles) \n",indexPersons);
				printPersonList(&indexPersons,listPersons);
				printf("6. Para regresar al menu principal \n");
				scanf("%d",&optionPerson);
				system("cls");
				int option=0;
				while (optionPerson!=6 && option!=6 && optionPerson<=indexPersons && (optionPerson==1 || optionPerson==2 || 
																	optionPerson==3 || optionPerson==4 || optionPerson==5)){
					///< Se hace un apuntador a una lista
					///< El apuntador a una lista toma la direccion de la lista de la persona seleccionada
					lista *list=listPersons[optionPerson-1]->list;
					printf("\nEstamos trabajando con la lista de %s",listPersons[optionPerson-1]->name);
					printf("\nIngresa una opcion del menu \n");
					printf("Opcion 1. Mostrar actividades \n");
					printf("Opcion 2. Modificar actividad \n");
					printf("Opcion 3. Eliminar actividades \n");
					printf("Opcion 4. Imprimir ordenadamente las actividades (Ascendente por fecha) \n");
					printf("Opcion 5. Imprimir ordenadamente las actividades (Por duracion en dias) \n");
					printf("Opcion 6. Seleccionar otro usuario \n");
					scanf("%d",&option);///< Se elige una opcion para administrar la lista de actividades
					if (option == 1){///< Si presiona 1, imprime la lista de actividades
						system("cls");
						printList(list);
					}else if (option == 2){///< Si presiona 2, pide el id de la actividad a actualizar
						system("cls");
						int idToFind,newSDay,newSMonth,newSYear,newEDay,newEMonth,newEYear;
						char newTittle[20];
						char newPriority[5];
						act newAct;
						printf("Ingresa el id de la actividad a actualizar:\n");
						scanf("%d",&idToFind);
						///< Se llama a la funcion findById para ver si alguna actividad tiene ese id
						struct nodo *positionFound=findById(list,&idToFind);///< Se guarda la direccion encontrada
						if (positionFound!=NULL){///< Si la direccion encontrada es diferente de NULL se piden los nuevos datos
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
		    				///< Se rellena una actividad con los datos obtenidos para mandarla a la funcion updateActivity
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
						if (updateActivity(list,positionFound,&newAct)==2){///< Se seniala si el update se hizo correctamente
							printf("La actividad se actualizo con exito \n");
						}else {
	      					printf("No se encontro una actividad con ese id \n");
						}
					}else if (option == 3){///< Si se presiona 3, se pide el id de la actividad a eliminar
						system("cls");
						int idToFind;
						printf("Ingresa el id de la actividad a eliminar: \n");
						scanf("%d",&idToFind);
						struct nodo *positionFound=findById(list,&idToFind);
						///< Se comprueba si existe una actividad con ese id y se guarda su direccion
						if (positionFound!=NULL){///< Si se encontro una coincidencia la direccion no debe ser NULL
							printf("La actividad con este id es la actividad %d \n",positionFound->activity->id);
						}
						if (deleteActivity(list,positionFound)==1){///< Se llama a la funcion deleteActivity
							printf("La actividad se elimino con exito \n");///< Se seniala si se borro la actividad
						}else{
   	   					printf("No se encontro una actividad con ese id \n");
						}
					}else if (option == 4){
						///< Si se presiona 4, el vector sortedActivities es rellenado con la lista de actividades
						system("cls");
						fillSortedVector(list,sortedActivities);
						///< Se  ordena el vector segun la fecha de las actividades
						sortList(list,sortedActivities);
						printSortedList(list,sortedActivities);///< Se imprime el vector ordenado
						printf("\nSe imprimieron ordenadamente las actividades (Ascendente por fecha)\n");
					}else if (option == 5){
						///< Si se presiona 5, el vector durationSortedActivities es rellenado con la lista de actividades
						system("cls");
						fillSortedVector(list,durationSortedActivities);
						///< Se ordena el vector segun la duracion de las actividades
						sortDurationList(list,durationSortedActivities);
						printSortedList(list,durationSortedActivities);///< Se imprime el vector ordenado
						printf("\nSe imprimieron ordenadamente las actividades (Por duracion en dias)\n");
					}
				}
				system("cls");
			}
		}
	//Aqui abajo cierra el primer while
	}
	
	///< Se hace free a la memoria usada
	for (i=0;i<indexPersons;i++){///< Se hace un for para las personas
		struct nodo *index;
		struct nodo *anterior=NULL;
		index=listPersons[i]->list->headList;
		while (index!=NULL){///< Se recorre la lista de la persona
			anterior=index;
			index=index->next;
			free(anterior->activity);///< Se hace free de una en una las actividades de su lista
			free(anterior);
		}
		free(listPersons[i]->list);///< Se hace free al espacio de la lista
		free(listPersons[i]);///< Se hace free a la persona
	}
	free(listPersons);///< Se hace free al vector de personas
	free(sortedActivities);///< Se hace free al vector de actividades ordenadas por fecha
	free(durationSortedActivities);///< Se hace free al vector de actividades ordenadas por duracion
	printf("La memoria se libero correctamente");
	return 0;
}

/*--------------------------------------APARTADO DE FUNCIONES--------------------------------------*/

/*---------FUNCIONES PARA CRUD DE USUARIOS--------*/

/**
 * @brief Imprime en pantalla las personas contenidas en el vector
 * @param indexPersons Indice de personas
 * @param listPersons Vector de personas
 * @return vacio
 */
void printPersonList(int *indexPersons,persona *listPersons[]){
	int i;
	for (i=0;i<*indexPersons;i++){
		printf("%d. %s  --- %d actividades\n",i+1,listPersons[i]->name,listPersons[i]->list->index);
	}
	return 0;
}

/**
 * @brief Crea espacio para una variable persona, le asigna un nombre y crea su lista de actividades
 * @param indexPersons Indice de personas
 * @param name Nombre de la persona
 * @param activities Vector de actividades
 * @return La direccion de memoria del malloc persona
 */
int createPerson(int *indexPersons,char name[],act *activities){
	persona *person=(persona*)malloc(sizeof(persona));
	if (person!=NULL){
		strcpy(person->name,name);
		setActivityList(person,activities);
		*indexPersons=*indexPersons+1;
	}
	return person;
}

/**
 * @brief Llama a la funcion createActivityList y rellena con actividades la lista obtenida
 * @param personX Direccion de memoria de una persona
 * @param activity Vector de actividades
 * @return Una bandera, 1 si se relleno con exito, 0 si no se pudo rellenar
 */
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

/**
 * @brief Genera una lista con malloc, inicializa su indice y headlist
 * @param personX Direccion de memoria de una persona
 * @return Una bandera, 1 si se genero con exito, 0 si no se pudo generar
 */
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
/**
 * @brief Ubica la posicion de una persona en el vector de personas por medio de su nombre
 * @param indexPersons Indice de personas
 * @param listPersons Lista de personas
 * @param nameToFind Nombre con el cual buscar a la persona
 * @return La posicion de una persona en el vector de personas
 */
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

/**
 * @brief Actualiza el nombre de una persona
 * @param listPersons El vector de personas
 * @param personFound La posicion de la persona en el vector de personas
 * @param newName Nuevo nombre de la persona
 * @return Una bandera, 1 si actualizo el nombre, 0 si no se actualizo
 */
int updateUserName(persona *listPersons[],int *personFound,char *newName[]){
	int flag=0;
	if (*personFound!=-1){
		strcpy(listPersons[*personFound]->name,newName);
		flag=1;
	}
	return flag;
}

/**
 * @brief Elimina una persona del vector de personas
 * @param indexPersons Indice de personas
 * @param listPersons La lista de personas
 * @param personFound La posicion en el vector de la persona a eliminar
 * @return Una bandera, 1 si el usuario se elimino, 0 si no se elimino
 */
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

/**
 * @brief Crea una nueva actividad con malloc y la rellena con la actividad recibida
 * @param list La lista de actividades
 * @param activity La diraccion de memoria de una actividad
 * @return La direccion de memoria de la nueva actividad
 */
int createActivity(lista *list,act *activity){
	act *newactivity;
	newactivity=(act*)malloc(sizeof(act));
	if (newactivity!=NULL){
		*newactivity=*activity;
	}
	return newactivity;
}

/**
 * @brief Agrega un nodo de forma ordenada (por fecha de inicio de actividad) 
 *	verificando si va al principio, al final o en cualquier otro lugar
 * @param list La lista de actividades
 * @param nuevaAct La actividad a insertar en el nuevo nodo
 * @return Una bandera, 1 si el nodo se anadio a la lista, 0 si no se pudo agregar
 */
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

/**
 * @brief Genera una string para una fecha
 * @param date La fecha a transformar
 * @return La fecha como string con la forma dd/mm/yyyy
 */
//Recibe una fecha y la devuelve como string
char* dateToString(date *date){
	char output[10]=" ";
	char auxDay[3];
	char auxMonth[3];
	char auxYear[5];

	//Se hace una string con la fecha 
	char sentenceStart[10]=" ";
	sprintf(auxDay,"%d",date->day);
	strcat(sentenceStart,auxDay);
	strcat(sentenceStart,"/");
	sprintf(auxMonth,"%d",date->month);
	strcat(sentenceStart,auxMonth);
	strcat(sentenceStart,"/");
	sprintf(auxYear,"%d",date->year);
	strcat(sentenceStart,auxYear);
	strcat(output,sentenceStart);

	return output;
}

/**
 * @brief Calcula los dias que hay entre el dia 0 y la fecha recibida
 * @param date La fecha a la cual se le va a calcular los dias
 * @return Los dias contenidos entre el dia 0 y la fecha recibida (contemplando anios bisiestos)
 */
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

/**
 * @brief Calcula la duracion de una actividad recibiendo la fecha de inicio y fin
 * @param startDate La fecha de inicio
 * @param endDate La fecha de finalizado
 * @return La duracion de una actividad
 */
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

/**
 * @brief Genera una string que brinda informacion sobre los datos de una actividad
 * @param acti Una actividad
 * @return Una string con toda la informacion de la actividad
 */
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

/**
 * @brief Manda todas las actividades de la lista a la funcion activityToString y concatena sus returns
 * @param list La lista de actividades
 * @return Una string que contiene la informacion de todas las actividades
 */
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

/**
 * @brief Imprime la string obtenida en la funcion listToString
 * @param list La lista de actividades
 * @return vacio
 */
//Llama a la funcion que concatena las strings con los datos de las
//actividades para devolverlos
void printList(lista *list){
	char outputFromList[8000]=" ";
	strcpy(outputFromList,listToString(list));
	printf("%s",outputFromList);
}

/**
 * @brief Busca por id una actividad contenida en la lista recibida
 * @param list La lista de actividades
 * @param idToFind El id de la actividad a buscar
 * @return Si encontro una actividad que coincide devuelve su direccion,sino,devuelve NULL
 */
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

/**
 * @brief Elimina el nodo que contiene a la actividad y genera uno nuevo con una actividad
 * con el mismo id y los nuevos datos para simular el update
 * @param list La lista de actividades
 * @param positionFound La direccion de memoria del nodo que contiene la actividad a actualizar
 * @param newAct Una actividad con la nueva informacion de la actividad a actualizar
 * @return Una bandera, 2 si pudo eliminar el viejo nodo y agregar la nueva actividad,
 * 1 si solo logro hacer una cosa, 0 si no logro hacer nada
 */
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

/**
 * @brief Elimina un nodo segun su posicion en la lista
 * @param list La lista de actividades
 * @param positionFound La direccion de memoria del nodo a eliminar
 * @return Una bandera, 1 si pudo eliminar el nodo, 0 si no puedo eliminar el nodo
 */
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

/**
 * @brief Recibe una lista de apuntadores a actividades y las guarda sus direcciones en un nuevo vector
 * @param list La lista de actividades
 * @param sortedActivities El nuevo vector en el cual se van a reorganizar
 * @return vacio
 */
//Recibe un vector en el cual va a vaciar las direcciones de las actividades de la lista
void fillSortedVector(lista *list,act **sortedActivities){
	struct nodo *index;
	int counterAux=0;
	for (index=list->headList;index!=NULL;index=index->next){
		sortedActivities[counterAux]=index->activity;
		counterAux++;
	}
}

/**
 * @brief Compara los dias de dos fechas
 * @param date1 Fecha 1
 * @param date2 Fecha 2
 * @return 1 si la fecha 1 es mayor y 0 si la fecha 2 es mayor
 */
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

/**
 * @brief Ordena por fecha el vector de actividades ordenadas
 * @param list La lista de actividades
 * @param sortedActivities El vector con las actividad obtenido en la funcion fillSortedVector
 * @return vacio
 */
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

/**
 * @brief Genera una string con las actividades del vector de actividades ordenadas
 * @param list La lista de actividades
 * @param activities Vector de actividades ordenadas
 * @return Una string con la informacion ordenada de las actividades
 */
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

/**
 * @brief Imprime la string obtenida de la funcion sortedListToString
 * @param list La lista de actividades
 * @param activities El vector de actividades ordenadas
 * @return vacio
 */
//Imprime la string resultante de la funcion anterior
void printSortedList(lista *list,act **activities){
	char outputFromList[8000]=" ";
	strcpy(outputFromList,sortedListToString(list,activities));
	printf("%s",outputFromList);
}

/**
 * @brief Compara la duracion en dias de dos actividades en base a sus fechas de inicio y fechas de fin
 * @param sDate1 Fecha de inicio 1
 * @param eDate1 Fecha de fin 1
 * @param sDate2 Fecha de inicio 2
 * @param eDate2 Fecha de fin 2
 * @return Una bandera, 1 si la actividad1 dura mas que la actividad2, 0 si resulta lo contrario
 */
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

/**
 * @brief Reordena (por duracion de actividad) el vector de actividades ordenadas
 * @param list La lista de actividades
 * @param durationSortedActivities El vector para reordenar las actividades
 * @return vacio
 */
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
