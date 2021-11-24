#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define tam 10
#define FILAS 5
#define COLS 12

//prototipos
void menu();

void verDiezMejores();
void reporteGeneralJugadores();

void registrarJugador();
int buscar_palabra(char *str1, char *str2);

void jugar();
int generarNumero();
void inicializarTablero(int **);
void imprimirTablero(int **);
void puntaje(int, int , char [25] , char [25], int, int);
bool seguirJugando();
int lanzarDados();
void dibujarDado(int);
void ganador(char [25], char [25], int, int );

using namespace std;

//elementos globales
FILE* fichero;

char dado6[FILAS][COLS]={ 
  "XXXXXXXXXXX",
  "X o     o X",
  "X o     o X",
  "X o     o X",
  "XXXXXXXXXXX",
};

char dado5[FILAS][COLS]={ 
  "XXXXXXXXXXX",
  "X o     o X",
  "X    o    X",
  "X o     o X",
  "XXXXXXXXXXX",
};

char dado4[FILAS][COLS]={ 
  "XXXXXXXXXXX",
  "X o     o X",
  "X         X",
  "X o     o X",
  "XXXXXXXXXXX",
};

char dado3[FILAS][COLS]={ 
  "XXXXXXXXXXX",
  "X o       X",
  "X    o    X",
  "X       o X",
  "XXXXXXXXXXX",
};

char dado2[FILAS][COLS]={ 
  "XXXXXXXXXXX",
  "X o       X",
  "X         X",
  "X       o X",
  "XXXXXXXXXXX",
};

char dado1[FILAS][COLS]={ 
  "XXXXXXXXXXX",
  "X         X",
  "X    o    X",
  "X         X",
  "XXXXXXXXXXX",
};

//funcion principal
int main(){
	
	srand(time(NULL));//reseteo de la semilla
	
	menu();
	
	return 0;
}

//funcion menu
void menu(){
	//variables locales 
	int opc=0;
	
	do{
		system("cls"); //borrar pantalla
		//mostrar menu principal
		cout<<"               Bienvenido al Menu Principal"<<endl<<endl<<endl;
		cout<<"*Ingrese 1 para Jugar"<<endl<<endl;
		cout<<"*Ingrese 2 para Ver los 10 mejores jugadores"<<endl<<endl;
		cout<<"*Ingrese 3 para Reporte general de jugadores"<<endl<<endl;
		cout<<"*Ingrese 4 para Registrar jugador"<<endl<<endl;
		cout<<"*Ingrese 0 para Salir\n\n->";
		cin.clear(); //limpia el buffer
		cin>>opc;
		
		system("cls");
		
		switch(opc){ //estudio de casos del menu principal
			
			case 0:{
				cout<<"Saliendo...\n";
				system("pause");
				break;
			}
				
			case 1:{
				jugar();
				break;	
			}
				
			case 2:{
				verDiezMejores();	
				break;	
			}
			
			case 3:{
				reporteGeneralJugadores();	
				break;	
			}
				
			case 4:{
				registrarJugador();	
				break;	
			}
	
			default:{
				cout<<"Parametro ingresado al menu no valido!\n";
				system("pause");
				break;
			}
		}
				
	}while(opc!=0);
	
}
	
//funcion jugar
void jugar(){
	
	//variables locales
	bool jugadorRegistrado=false;
	char jugador1[25];
	char cedula1[15];
	char jugador2[25];
	char cedula2[15];
	
	char linea[80];
	
	bool jugar=true;
	
	int nTurnos=1;
	
	int puntosJugador1=0; //contadores de los puntos por jugador
	int puntosJugador2=0;
	
	int multiplicacion=0;
	int resMultiplicacion=0;
		
	//inicializa la matriz de 10 x 10
	int** matriz = new int*[tam];
	for (int i = 0; i < tam; ++i) 
		matriz[i] = new int[tam];
	
	//ciclo para validar jugador 1 registrado para jugar	
	do{
		fichero = fopen("jugadores.dat", "rt"); //se abre el fichero de jugadores registrados en modo lectura
		jugadorRegistrado=false;
		
		cout<<"     Datos del jugador 1"<<endl<<endl;
		cout<<"*Ingrese su nombre\n->";
		cin.clear();
		cin>>jugador1;
		
		cout<<"*Ingrese su cedula\n->";
		cin.clear();
		cin>>cedula1;
		
		if(fichero==NULL){ //si no existe el fichero, no existen jugadores registrados, y se invoca la funcion registrar
			fclose(fichero); //se cierra el fichero
			registrarJugador();
			system("cls");
			jugadorRegistrado=false;
		}else{
			while (!feof(fichero)) {  //ciclo que recorre el fichero mientras no llegue al final
				
				fgets(linea, 80, fichero);  //se almacena la linea del fichero en la cadena linea
				
				if (!feof(fichero)){
					
					if(buscar_palabra(linea, cedula1)!=0){ //se busca en la linea leida si existe coincidencia en la cedula con la funcion buscar_palabra
						jugadorRegistrado=true;
					}
				}
				
			}
			fclose(fichero); //se cierra el fichero
		}
		
		if(jugadorRegistrado==true){
			cout<<"Bienvenido jugador uno: "<<jugador1<<endl;
			system("pause");
			system("cls");
		}else{
			cout<<"Jugador no registrado, redirigiendo para registrar.."<<endl;
			system("pause");
			system("cls");
			
			fclose(fichero); //se cierra el fichero
			registrarJugador();
			jugadorRegistrado=false;
			system("cls");
		}
		
	}while(jugadorRegistrado!=true);

	//ciclo para validar jugador 2 registrado para jugar	
	do{
		fichero = fopen("jugadores.dat", "rt"); //se abre el fichero de jugadores registrados en modo lectura
		jugadorRegistrado=false;
		
		cout<<"     Datos del jugador 2"<<endl<<endl;
		cout<<"*Ingrese su nombre\n->";
		cin.clear();
		cin>>jugador2;
		
		cout<<"*Ingrese su cedula\n->";
		cin.clear();
		cin>>cedula2;
		
		if(fichero==NULL){ //si no existe el fichero, no existen jugadores registrados, y se invoca la funcion registrar
			fclose(fichero); //se cierra el fichero
			registrarJugador();
			system("cls");
			jugadorRegistrado=false;
		}else{
			while (!feof(fichero)) {  //ciclo que recorre el fichero mientras no llegue al final
				
				fgets(linea, 80, fichero);  //se almacena la linea del fichero en la cadena linea
				
				if (!feof(fichero)){
					
					if(buscar_palabra(linea, cedula2)!=0){ //se busca en la linea leida si existe coincidencia en la cedula con la funcion buscar_palabra
						jugadorRegistrado=true;
					}
				}
				
			}
			fclose(fichero); //se cierra el fichero
		}
	
		if(jugadorRegistrado==true){
			cout<<"Bienvenido jugador dos: "<<jugador2<<endl;
			system("pause");
			system("cls");
		}else{
			cout<<"Jugador no registrado, redirigiendo para registrar.."<<endl;
			system("pause");
			system("cls");
			
			fclose(fichero); //se cierra el fichero
			registrarJugador();
			jugadorRegistrado=false;
			system("cls");
		}
		
	}while(jugadorRegistrado!=true);
	
	inicializarTablero(matriz); //invocacion de la funcion que inicia el tablero
	
	//loop del juego que se repite siempre que los jugadores quieran jugar y tengan turnos disponibles (20 x cada uno es el limite)
	while(jugar && nTurnos<=4){
		
		//para el jugador 1
		jugar=seguirJugando(); //se pregunta si se desea seguir jugando al jugador 1
		
		if(jugar){
			puntaje(puntosJugador1, puntosJugador2, jugador1, jugador2, 1, nTurnos);
			imprimirTablero(matriz); //se muestra en pantalla
			resMultiplicacion=lanzarDados();
			
			cout<<"*Digite el resultado de la multiplicacion de los valores de los dados\n->";
			cin>>multiplicacion;
			
			if(multiplicacion==resMultiplicacion){
				cout<<"Correcto"<<endl;
				system("pause");
			}else{
				cout<<"Lo sentimos! La respuesta correcta es: "<<resMultiplicacion<<endl;
				system("pause");
			}
			
		}else
			break;
		
		//para el jugador 2
		jugar=seguirJugando(); //se pregunta si se desea seguir jugando al jugador 2
		
		if(jugar){
			puntaje(puntosJugador1, puntosJugador2, jugador1, jugador2, 2, nTurnos);
			imprimirTablero(matriz); //se muestra en pantalla
			resMultiplicacion=lanzarDados();
			
			cout<<"*Digite el resultado de la multiplicacion de los valores de los dados\n->";
			cin>>multiplicacion;
			
			if(multiplicacion==resMultiplicacion){
				cout<<"Correcto"<<endl;
				system("pause");
			}else{
				cout<<"Lo sentimos! La respuesta correcta es: "<<resMultiplicacion<<endl;
				system("pause");
			}
			
		}else
			break;

		nTurnos++;	//al pasar el turno de ambos se asume un turno total
	}
	
	//al terminar el juego
	ganador(jugador1, jugador2, puntosJugador1, puntosJugador2); //invocacion de la funcion que mostrara un mensaje para declarar al ganador
	
}

//ver 10 mejores
void verDiezMejores(){
	
}

//reporte general de jugadores
void reporteGeneralJugadores(){
	fichero = fopen("jugadores.dat", "rt"); //se abre el fichero de jugadores registrados en modo lectura
	
	//var local
	char linea[80];
	
	if(fichero==NULL){	//si no existe el archivo, entonces no hay jugadores registrados
    	cout<<"No hay jugadores registrados aun!!"<<endl;
    	
	}else{
		cout<<"Nombres          Cedulas"<<endl<<endl;
		while (!feof(fichero)) {  //ciclo que recorre el archivo hasta llegar al final
	        fgets(linea, 80, fichero); //se toma la linea 
	        if (!feof(fichero)) 
	           	puts(linea); //se imprime en consola dicha linea que corresponde al registro de un jugador
   		} 
    
		fclose(fichero); //se cierra el fichero
	}
	
	system("pause");
    system("cls");
	
}

//registrar jugador 
void registrarJugador(){
	fichero = fopen("jugadores.dat", "rt"); //se abre el fichero de jugadores registrados en modo lectura

	//var locales
	char jugador[25];
	char cedula[25];
	char linea[25];
	int coincidencias=0;
	
	cout<<"        Registro de Jugador"<<endl<<endl;
	//solicitar datos
	cout<<"Ingrese el nombre del jugador\n->";
	cin.clear();
	cin>>jugador;
	
	cout<<"Ingrese la cedula del jugador\n->";
	cin.clear();
	cin>>cedula;
	
	if(fichero==NULL){ //si no existe el fichero, no existen coincidencias ya que no hay jugadores registrados previos
		coincidencias=0;
	}else{
		while (!feof(fichero)) {  //ciclo que recorre el fichero mientras no llegue al final
			
			fgets(linea, 80, fichero);  //se almacena la linea del fichero en la cadena linea
			
			if (!feof(fichero)){
				
				if(buscar_palabra(linea, cedula)!=0){ //se busca en la linea leida si existe coincidencia en la cedula con la funcion buscar_palabra
					coincidencias++;
				}
			}
			
		}
	}
	
	fclose(fichero); //se cierra el fichero
	
	if(coincidencias==0){ //se valida si no esta la cedula registrada...
		fichero = fopen("jugadores.dat", "at"); //se abre el fichero en modo modificacion para escribir al final
		
		fputs(jugador,fichero);
		fputs("\t\t",fichero);
		fputs(cedula,fichero);
		fputs("\n",fichero);
		
		fclose(fichero); //se cierra el fichero
	}else{
		cout<<endl<<"El jugador de cedula: "<<cedula<<" ya esta registrado..."<<endl;
		system("pause");
	}
		
}
	
//buscar palabra (se usa para saber si ya se registro un jugagor con cedula str2)
int buscar_palabra(char *str1, char *str2){ // recibe la cadena de la linea por referencia para reutilizarla en la funcion main, y la palabra a buscar
	//variables locales
	int len1=strlen(str1); //variable que tomara el valor del tamanio de la cadena de la linea
	int len2=strlen(str2); //variable que tomara el valor del tamanio de la cadena de la palabra
	int i=0; //contador
	char c=' '; //variable pivote que tomara el primer caracter de cada palabra para comprobar la palabra
	
	if(len2>len1){ 
		printf("La cadena 2 es mas grande que la cadena 1\n");
	}else{
		i=0;
		c=str2[0]; //se toma el valor del primer caracter de cada palabra 
		
		while(str1[i]!='\0'){ //ciclo que iterara en cada una de las posiciones de la cadena de la linea, siempre que no llegue al final
			if(str1[i]==c){ //si el caracter de la linea coincide con la variable pivote...
				if(strncmp(&str1[i], str2, len2)==0){ //se valida si desde la posicion de la cadena de la linea hasta el tamanio en caracteres de la palabra a buscar coinciden
					return 1; //retorna 1 indicando que si encontro la palabra
				}
			}
			i++; //aumento del contador para seguir iterando en las posiciones de la cadena de la linea
		}
		return 0; //retorna cero si no encontro coincidencia
	}
}
	
//funcion que general un numero aleatorio entre 1-36 multiplos de 1,2,3,4,5 y 6
int generarNumero(){
	//variables locales
	int num=0;
	
	do{
		num = rand() % 36+1; //numeo aleatorio entre 1 y 36
	}while(num%1!=0 && num%2!=0 && num%3!=0 && num%4!=0 && num%5!=0  && num%6!=0); //ciclo que asegura que el numero sea multiplo de 1,2,3,4,5,6
	
	return num;
}

//funcion que iniciliza el tablero y asigna numeros aleatorios a cada posicion de la matriz 10 x 10
void inicializarTablero(int **matriz){
	
	for(int i=0;i<tam;i++){
		for(int j=0;j<tam;j++){
			matriz[i][j]=generarNumero(); //invocacion de la funcion que genera los numeros aleatorios y los asigna en la posicion de la matriz durante el recorrido
		}
	}
}
	
//imprime el tablero (matriz)
void imprimirTablero(int **matriz){
	for(int i=0;i< tam;i++){
		for(int j=0;j< tam;j++){
			cout<<matriz[i][j]<<"\t";
		}
		cout<<endl;
	}
}

//funcion que muestra el puntaje
void puntaje(int p1, int p2, char jugador1[25] , char jugador2[25], int turno, int nTurno){
	if(turno==1)
		cout<<"Es el turno numero:"<<nTurno<<"            TURNO ACTUAL PARA: "<<jugador1<<endl<<endl;
	else
		cout<<"Es el turno numero:"<<nTurno<<"            TURNO ACTUAL PARA: "<<jugador2<<endl<<endl;
		
	cout<<jugador1<<": lleva "<<p1<<" Pts. |VS| ";
	cout<<jugador2<<": lleva "<<p2<<" Pts."<<endl<<endl;
}

//pregunta si se quiere seguir jugando si se desea salir al menu principal
bool seguirJugando(){
	int opc=0;
	
	do{
		system("cls");
		cout<<"*Ingresa 1 para confirmar que deseas seguir jugando, y 0 para no\n->";
		cin>>opc;
		
	}while(opc<0 || opc>1);
	
	system("cls");
	
	if(opc==1){
		return true;
	}else{
		return false;
	}
}

//lanzar dados
int lanzarDados(){

	int cantDado1=0, cantDado2=0;
	
	cout<<endl<<"Lanzando los dados ..."<<endl<<endl;
	cout<<"dado 1:"<<endl;
	cantDado1=rand() % 6 + 1;
	dibujarDado(cantDado1); //para el dado 1
	
	cout<<endl; //separacion entre los dados
	
	cout<<"dado 2:"<<endl;
	cantDado2=rand() % 6 + 1;
	dibujarDado(cantDado2); //para el dado 2
	
	return cantDado1*cantDado2;
		
}

//funcion que elige que dado dibujar 
void dibujarDado(int nDado){
	
	switch(nDado){
		case 1:{
			for(int i=0;i<FILAS;i++){
				for(int j=0;j<COLS;j++){
					cout<<dado1[i][j];
				}
				cout<<endl;
			}
			break;
		}
		case 2:{
			for(int i=0;i<FILAS;i++){
				for(int j=0;j<COLS;j++){
					cout<<dado2[i][j];
				}
				cout<<endl;
			}
			break;
		}
		case 3:{
			for(int i=0;i<FILAS;i++){
				for(int j=0;j<COLS;j++){
					cout<<dado3[i][j];
				}
				cout<<endl;
			}
			break;
		}
		case 4:{
			for(int i=0;i<FILAS;i++){
				for(int j=0;j<COLS;j++){
					cout<<dado4[i][j];
				}
				cout<<endl;
			}
			break;
		}
		case 5:{
			for(int i=0;i<FILAS;i++){
				for(int j=0;j<COLS;j++){
					cout<<dado5[i][j];
				}
				cout<<endl;
			}
			break;
		}
		case 6:{
			for(int i=0;i<FILAS;i++){
				for(int j=0;j<COLS;j++){
					cout<<dado6[i][j];
				}
				cout<<endl;
			}
			break;
		}
		default:{
			cout<<"Error!!."<<endl;
			system("pause");
			break;
		}
	}	
}

//funcion que muestra el ganador
void ganador(char jugador1[25], char jugador2[25], int puntosJugador1, int puntosJugador2){
	system("cls");
	
	if(puntosJugador1>puntosJugador2){
		cout<<"FELICIDADES "<<jugador1<<" Has ganado con: "<<puntosJugador1<<" puntos sobre los "<<puntosJugador2<<" puntos de tu oponente"<<endl<<endl;
		system("pause");
		system("cls");
	}else if(puntosJugador1>puntosJugador2){
		cout<<"FELICIDADES "<<jugador2<<" Has ganado con: "<<puntosJugador2<<" puntos sobre los "<<puntosJugador1<<" puntos de tu oponente"<<endl<<endl;
		system("pause");
		system("cls");
	}else{
		cout<<"FELICIDADES "<<jugador1<<" Y "<<jugador2<<" Han empatado con: "<<puntosJugador1<<" puntos."<<endl<<endl;
		system("pause");
		system("cls");
	}
	
}
