#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 

#define LADO 8 //Cambiar la constante cambia el numero de filas y columnas respectivamente
#define NumMinas 16 //Cambiar la constante cambia el numero de minas a plantar funcionalmente
//En la linea 266 se Encuentra una "trampa" para revelar la matriz real y ver las minas  , solo hay que descomentar la linea


bool CasillaExistente(int Fila, int Columna); //Linea 84
bool HayMina (int Fila, int Columna, char MatrizReal[][LADO]); //Linea 89
void ImprimeMatriz(char MatrizVisible[][LADO]); //Linea 98
int ContarMinas(int Fila, int Columna, int Minas[][2], char MatrizReal[][LADO]); //Linea 118
int ContarMarcas(int Fila, int Columna, char MatrizVisible[][LADO]); //Linea 161
void PlantarMinas(int Minas[][2], char MatrizReal[][LADO]); //Linea 204
void Inicializar(char MatrizReal[][LADO], char MatrizVisible[][LADO]); //Linea 228
void JugarBuscaminas ();  //Linea 249
bool Explorar(char MatrizVisible[][LADO], char MatrizReal[][LADO],int Minas[][2], int Fila, int Columna, int *MovimientosRestantes); //Linea 329
bool Buscar(char MatrizVisible[][LADO], char MatrizReal[][LADO],int Minas[][2], int Fila, int Columna, int *MovimientosRestantes);  //Linea 424
void Cascada(char MatrizVisible[][LADO], char MatrizReal[][LADO],int Minas[][2], int Fila, int Columna, int *MovimientosRestantes);  //Linea 587

// El main contiene mayoritariamente elementos graficos y visuales ,y llama a la funcion JugarBuscaminas que permite al usuario jugar. 
main(){
		printf("\n"
		"\n¯¦¦¦¦¦¦¦¦¦_  ¦¦¦    ¦_     _¦¦¦¦¦¦¦¦  _¦¦¦¦¦¦¦¦    _¦¦¦¦¦¦¦¦   ____¦¦¦____    _¦  ¦¦¦____      _¦¦¦¦¦¦¦¦    _¦¦¦¦¦¦¦¦ " 
		"\n  ¦¦¦    ¦¦¦ ¦¦¦    ¦¦¦   ¦¦¦    ¦¦¦ ¦¦¦    ¦¦¦   ¦¦¦    ¦¦¦ _¦¦¯¯¯¦¦¦¯¯¯¦¦_ ¦¦¦  ¦¦¦¯¯¯¦¦_   ¦¦¦    ¦¦¦   ¦¦¦    ¦¦¦ "
		"\n  ¦¦¦    ¦¦¦ ¦¦¦    ¦¦¦   ¦¦¦    ¦¯  ¦¦¦    ¦¯    ¦¦¦    ¦¦¦ ¦¦¦   ¦¦¦   ¦¦¦ ¦¦¦¦ ¦¦¦   ¦¦¦   ¦¦¦    ¦¦¦   ¦¦¦    ¦¯  "
		"\n _¦¦¦___¦¦¯  ¦¦¦    ¦¦¦   ¦¦¦        ¦¦¦          ¦¦¦    ¦¦¦ ¦¦¦   ¦¦¦   ¦¦¦ ¦¦¦¦ ¦¦¦   ¦¦¦   ¦¦¦    ¦¦¦   ¦¦¦        "
		"\n¯¯¦¦¦¯¯¯¦¦_  ¦¦¦    ¦¦¦ ¯¦¦¦¦¦¦¦¦¦¦¦ ¦¦¦        ¯¦¦¦¦¦¦¦¦¦¦¦ ¦¦¦   ¦¦¦   ¦¦¦ ¦¦¦¦ ¦¦¦   ¦¦¦ ¯¦¦¦¦¦¦¦¦¦¦¦ ¯¦¦¦¦¦¦¦¦¦¦¦ "
		"\n  ¦¦¦    ¦¦_ ¦¦¦    ¦¦¦          ¦¦¦ ¦¦¦    ¦_    ¦¦¦    ¦¦¦ ¦¦¦   ¦¦¦   ¦¦¦ ¦¦¦  ¦¦¦   ¦¦¦   ¦¦¦    ¦¦¦          ¦¦¦ "
		"\n  ¦¦¦    ¦¦¦ ¦¦¦    ¦¦¦    _¦    ¦¦¦ ¦¦¦    ¦¦¦   ¦¦¦    ¦¦¦ ¦¦¦   ¦¦¦   ¦¦¦ ¦¦¦  ¦¦¦   ¦¦¦   ¦¦¦    ¦¦¦    _¦    ¦¦¦ "
		"\n_¦¦¦¦¦¦¦¦¦¯  ¦¦¦¦¦¦¦¦¯   _¦¦¦¦¦¦¦¦¯  ¦¦¦¦¦¦¦¦¯    ¦¦¦    ¦¯   ¯¦   ¦¦¦   ¦¯  ¦¯    ¯¦   ¦¯    ¦¦¦    ¦¯   _¦¦¦¦¦¦¦¦¯  "
		"\n");
		
		
		
		printf("\n"
		"\n                    Bienvenidos al Buscaminas 2017 prestentado a usted por Re Originales S.A. \n" 
		"\n     _________________________________________Reglas de Juego_______________________________________________"
		"\n            Usted puede escoger entre 3 comandos validos , y el formato de entrada de sus movimientos"
		"\n            es el siguiente, Comando seguido de un Espacio y Fila(A-H)Columna(A-H)  Ej: E AD\n"
		"\n         Marcar : Marca una casilla como sospechosa de bomba con una X y su comando es la letra M"
		"\n                  usar este comando en una casilla marcada previamente quitara dicha marca"
		"\n"
		"\n       Explorar : Revela lo que se encontraba en todas las casillas no exploradas o marcadas"
		"\n                  adyacentes a la casilla explorada donde se realiza la busqueda y su comando es la letra E"
		"\n                  nota:solo se puede explorar en casillas cuyo numero de minas adyacentes corresponda"
		"\n                  con la cantidad de casillas marcadas"  
		"\n"
		"\n          Buscar: Revela el contenido de una casilla previamente inexplorada, su comando es la letra B "
		"\n"
		"\n      El juego se Ganara cuando todas las minas esten marcadas y no queden movimientos restantes, Suerte!"
		"\n"
		"\n       Plantando las Minas \n");
    // Cambia el color de las letras para una entrada "Flashera"
		system( "color F " );     
		Sleep(150);
		system( "color 03" );
		Sleep(150);
		system( "color D" );
		Sleep(150);
		system( "color 09" );
		Sleep(150);
		system( "color B " );
		Sleep(150);
		system( "color C" );
		Sleep(150);
		system( "color 05" );
		Sleep(150);
		system( "color E" );
		Sleep(150);
		system( "color 02" );
		Sleep(150);


		system( "color B0" );   //color de fondo celeste con letras negras       
		system("PAUSE");
		system("cls");      // Limpia la pantalla antes de jugar
	    JugarBuscaminas ();             // Funcion para jugar 
	}

// CasillaExistente revisa que dado un movimiento valido la casilla exista dentro de la matriz , si esta condicion es negativa retornara 0
bool CasillaExistente(int Fila, int Columna){
  	  return (Fila >= 0) && (Fila < LADO) && (Columna >= 0) && (Columna < LADO);
	}

// HayMina es la funcion que  dada una casilla, revisa si hay mina o no en la Matriz real  
bool HayMina (int Fila, int Columna, char MatrizReal[][LADO]){
	    if (MatrizReal[Fila][Columna] == 'B')
	        return (true);
	    else
	        return (false);
	}

/* ImprimeMatriz,Muestra la Matriz de Juego en la consola  
A los printf se les suma +65 Para pasar del Numero a la Letra del codigo Ascii correspondiente*/
void ImprimeMatriz(char MatrizVisible[][LADO]){
	    int i, j;
	 
	    printf ("|||||");
	 
	    for (i=0; i<LADO; i++)
	        printf ("|%c|", i+65);
	 		printf ("\n");
	 
	    for (i=0; i<LADO; i++){
	        printf ("| %c |", i+65);
	        for (j=0; j<LADO; j++)
	            printf (" %c ", MatrizVisible[i][j]);
	        	printf ("\n");
	    }
	    return;
	}

/* ContarMinas Revisa las 8 casillas adyacentes y devuelve el numero de minas por casilla , valiendose de las funciones CasillaExistente para 
no revisar en una casilla inexistente en la matriz y en la Funcion HayMina para ver si efectivamente hay una mina en la casilla a buscar */
int ContarMinas(int Fila, int Columna, int Minas[][2], char MatrizReal[][LADO]){
	 
	    int i;
	    int Contador = 0;
	
	        if (CasillaExistente (Fila-1, Columna) == true){
	               if (HayMina (Fila-1, Columna, MatrizReal) == true)
	                Contador++;
	        }
	        if (CasillaExistente (Fila+1, Columna) == true){
	               if (HayMina (Fila+1, Columna, MatrizReal) == true)
	                Contador++;
	        }
	        if (CasillaExistente (Fila, Columna+1) == true){
	               if (HayMina (Fila, Columna+1, MatrizReal) == true)
	                Contador++;
	        }
	        if (CasillaExistente (Fila, Columna-1) == true){
	               if (HayMina (Fila, Columna-1, MatrizReal) == true)
	                Contador++;
	        }
	        if (CasillaExistente (Fila-1, Columna+1) == true){
	               if (HayMina (Fila-1, Columna+1, MatrizReal) == true)
	                Contador++;
	        }
	        if (CasillaExistente (Fila-1, Columna-1) == true){
	               if (HayMina (Fila-1, Columna-1, MatrizReal) == true)
	                Contador++;
	        }
	        if (CasillaExistente (Fila+1, Columna+1) == true){
	               if (HayMina (Fila+1, Columna+1, MatrizReal) == true)
	            	Contador++;
	        }
	        if (CasillaExistente (Fila+1, Columna-1) == true){
	               if (HayMina (Fila+1, Columna-1, MatrizReal) == true)
	            	Contador++;
	        }
	     return (Contador);
	}

/*Si bien muy parecida a ContarMinas , ContarMarcas es una Funcion creada Exlusivamente para el Comando Buscar , 
esta funcion revisa la matriz visible en busca de marcas y devuelve el numero de marcas adyacentes a la casilla
usa tambien la Funcion CasillaExistente para evitar buscar en una casilla inexistente*/
int ContarMarcas(int Fila, int Columna, char MatrizVisible[][LADO]){
	 
	    int i;
	    int Marcadas = 0;
	
	    if (CasillaExistente (Fila-1, Columna) == true){
               if ( MatrizVisible[Fila-1][Columna] == 'X' )
                Marcadas++;
        }
	    if (CasillaExistente (Fila+1, Columna) == true){
               if ( MatrizVisible[Fila+1][Columna] == 'X' )
                Marcadas++;
	    }
        if (CasillaExistente (Fila, Columna+1) == true){
               if ( MatrizVisible[Fila][Columna+1] == 'X' )
                Marcadas++;
        }
        if (CasillaExistente (Fila, Columna-1) == true){
               if ( MatrizVisible[Fila][Columna-1] == 'X' )
                Marcadas++;
        }
        if (CasillaExistente (Fila-1, Columna+1) == true){
               if ( MatrizVisible[Fila-1][Columna+1] == 'X' )
                Marcadas++;
        }
        if (CasillaExistente (Fila-1, Columna-1) == true){
               if ( MatrizVisible[Fila-1][Columna-1] == 'X' )
                Marcadas++;
        }
        if (CasillaExistente (Fila+1, Columna+1) == true){
               if ( MatrizVisible[Fila+1][Columna+1] == 'X' )
                Marcadas++;
        }
        if (CasillaExistente (Fila+1, Columna-1) == true){
               if ( MatrizVisible[Fila+1][Columna-1] == 'X' )
                Marcadas++;
        }
		return (Marcadas);
	}

/*Plantar Minas aleatoriza las Minas  usando la funcion rand parte de la libreria stdlib.h  en % a Lado x Lado 
dando asi las cordenadas para x , y  siendo y el producto de la division del numero aleatorio y el lado , y siendo x el resto de la misma operacion
el rand funciona gracias a que en la funcion Inicializar se inicializa la funcion time null de la libreria time.h*/
void PlantarMinas(int Minas[][2], char MatrizReal[][LADO]){
	    bool Excavar[LADO*LADO]; //Si Hay Mina para que poner una sobre otra.....
	 
	
	    for (int i=0; i<NumMinas; ){
	        int random = rand() % (LADO*LADO);
	        int x = random / LADO;
	        int y = random % LADO;
	 
	
	        if (Excavar[random] == false){
	            Minas[i][0] = x;
	            Minas[i][1] = y;
	 
	            MatrizReal[Minas[i][0]][Minas[i][1]] = 'B';
	            Excavar[random] = true;
	            i++;
	        }
	    }
		return;
	}

/*Inicializa la funcion time de la libreria time.h para que la funcion srand funcione correctamente ,
 y usa un for para rellenar las matrizes Real y visible con el caracter ?*/
void Inicializar(char MatrizReal[][LADO], char MatrizVisible[][LADO]){
	
	    srand(time (NULL));  // Misterio y mas misterio!  .... que cosa aleatoria sera?
	 
	
	    for (int i=0; i<LADO; i++)
	    {
	        for (int j=0; j<LADO; j++){
	            MatrizVisible[i][j] = MatrizReal[i][j] = '?';
	        }
	    }
	 
	    return;
	}

/*Funcion principal para Jugar , Activa un booleano llamado Boom que es la condicion que evita que termine el juego 
Inicializa las matrizes  , planta las minas en la matriz real , limpiar  el buffer con fflush y procede a leer el movimiento  en el 
formato caracter y convertirlo a int restandole 65 para conferir el valor del codigo ascii al entero ,Despues el comando lo manda a un
Switch el cual respectivamente Marca , Explora o Busca , La opcion Marcar compara el numero de marcas con las minas y permite marcar casillas
sospechosas mientras las marcas no las exedan , Las opciones Explorar y Buscar , lamman a su correspondente funcion , si se abren todas las casillas
y todas las minas estan marcadas se gana */
void JugarBuscaminas (){

	    bool Boom = false;
	    char MatrizReal[LADO][LADO], MatrizVisible[LADO][LADO],a,b,c;
	 
	    int MovimientosRestantes = LADO * LADO - NumMinas, x, y;
		int MinasMarcadas = 0 ;
	    int Minas[NumMinas][2]; 
	     
	
	    Inicializar (MatrizReal, MatrizVisible);
	 
	    PlantarMinas (Minas, MatrizReal);
	
	    while (Boom == false){
	        printf("  Movimientos Restantes = %d \n",MovimientosRestantes);
	        printf ("Siguiente movimiento Por favor: \n\n");
			//ImprimeMatriz (MatrizReal);                                            //Para Ver localizacion de las Minas descomentar
			ImprimeMatriz (MatrizVisible);
	        fflush(stdin);
			printf("\nIngrese Comando seguido de espacio  y Movimiento Fila/Columna Ej:E AD \n");
			scanf("%c %c%c",&a,&b,&c);
			x=b-65;
			y=c-65;
			if ((x>=0)&&(x<LADO)&&(y>=0)&&(y<LADO)){
				switch(a) {
					case 'M':
						while(MinasMarcadas<=NumMinas){
							if(MinasMarcadas<NumMinas){
								if(MatrizVisible[x][y] == '?'){
					        		MatrizVisible[x][y] = 'X';
					        		MinasMarcadas++;
									printf (" Casilla marcada como sospechosa\n");
							    }else 
								  if(MatrizVisible[x][y] == 'X'){
						            MatrizVisible[x][y] = '?';
						            MinasMarcadas--;
							        printf (" Casilla desmarcada como sospechosa\n");
									}
							}
							else
							 if(MatrizVisible[x][y] == 'X'){
					            MatrizVisible[x][y] = '?';
					            MinasMarcadas--;
						        printf (" Casilla desmarcada como sospechosa\n");
					      		}else
					      			printf("\n Imposible marcar\n ");
					 				break; 		
						}
				    	break;

					case 'E':
						printf ("        Explorando \n");	
						Boom = Explorar (MatrizVisible, MatrizReal, Minas, x, y, &MovimientosRestantes);
					break;

					case 'B':
						printf ("          Buscando \n");
						Boom = Buscar (MatrizVisible, MatrizReal, Minas, x, y, &MovimientosRestantes); 
					break;

					default:
						printf ("\nFormato de Jugada Erroneo\n");
					break;
				}

				    if ((Boom == false) && (MovimientosRestantes == 0) && (MinasMarcadas == NumMinas)){  // Ganaste ?
			            printf ("\n         Ganaste , Gracias por Jugar!!!\n");
			            ImprimeMatriz (MatrizVisible);
			            Boom = true;
				    }
			}else
				printf("\n Formato de Juego Erroneo , Casilla Fuera de Rango\n");
		
		}	
	    return;
	}

/*Revisa una casilla inexplorada  si hay bomba imprime las bombas y entrega un mensaje  , si no hay bomba procede a revisar si hay bombas vecinas
si las hay , marca el numero de minas en la casilla , y en caso que no haya minas adyacentes revela todos los 0 adyacentes */
bool Explorar(char MatrizVisible[][LADO], char MatrizReal[][LADO],int Minas[][2], int Fila, int Columna, int *MovimientosRestantes){

	     if (MatrizVisible[Fila][Columna] != '?') //Para que explorar lo que ya esta explorado...?
	        return (false); 

	   	 int i;

	    if (MatrizReal[Fila][Columna] == 'B'){ //si Encuentras una casilla con bomba ..... Boom !
	        MatrizVisible[Fila][Columna]='B';
	 
	         for (i=0; i<NumMinas; i++)
	           	MatrizVisible[Minas[i][0]][Minas[i][1]]='B';
	 	        ImprimeMatriz (MatrizVisible);
				printf ("\nPerdiste ,Intenta no explotar a la proxima.!!!\n");
	         return(true);
	    }
		else
		 {
	        int Contador = ContarMinas(Fila, Columna, Minas, MatrizReal);
	        (*MovimientosRestantes)--;
	 		  MatrizVisible[Fila][Columna] = Contador + '0';
	
		        if(!Contador){         //Niega contador , si contador es 0 entra si es otra cosa no
		            if  (CasillaExistente (Fila-1, Columna) == true){
		                   if (HayMina (Fila-1, Columna, MatrizReal) == false)
		               		 	if (MatrizVisible[Fila-1][Columna] == '?'){
		                   	        int Contador = ContarMinas(Fila-1, Columna, Minas, MatrizReal);
									(*MovimientosRestantes)--;
		                            MatrizVisible[Fila-1][Columna] = Contador + '0';
								}
		            }
		             if (CasillaExistente (Fila+1, Columna) == true){
		                   if (HayMina (Fila+1, Columna, MatrizReal) == false)
		                		if (MatrizVisible[Fila+1][Columna] == '?'){
		                   	        int Contador = ContarMinas(Fila+1, Columna, Minas, MatrizReal);
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila+1][Columna] = Contador + '0';
								}
					}
		             if (CasillaExistente (Fila, Columna+1) == true){
		                   if (HayMina (Fila, Columna+1, MatrizReal) == false)
		                		if (MatrizVisible[Fila][Columna+1] == '?'){
		                   	        int Contador = ContarMinas(Fila, Columna+1, Minas, MatrizReal);
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila][Columna+1] = Contador + '0';
								}
					}
		             if (CasillaExistente (Fila, Columna-1) == true){
		                   if (HayMina (Fila, Columna-1, MatrizReal) == false)
		                		if (MatrizVisible[Fila][Columna-1] == '?'){
		                   	        int Contador = ContarMinas(Fila, Columna-1, Minas, MatrizReal);
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila][Columna-1] = Contador + '0';
								}
					}
		             if (CasillaExistente (Fila-1, Columna+1) == true){
		                   if (HayMina (Fila-1, Columna+1, MatrizReal) == false)
		                		if (MatrizVisible[Fila-1][Columna+1] == '?'){
		                   	        int Contador = ContarMinas(Fila-1, Columna+1, Minas, MatrizReal);
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila-1][Columna+1] = Contador + '0';
								}
					}
		             if (CasillaExistente (Fila-1, Columna-1) == true){
		                   if (HayMina (Fila-1, Columna-1, MatrizReal) == false)
		              		  	if (MatrizVisible[Fila-1][Columna-1] == '?'){
		                   	        int Contador = ContarMinas(Fila-1, Columna-1, Minas, MatrizReal);
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila-1][Columna-1] = Contador + '0';
								}
					}
		             if (CasillaExistente (Fila+1, Columna+1) == true){
		                   if (HayMina (Fila+1, Columna+1, MatrizReal) == false)
		                		if (MatrizVisible[Fila+1][Columna+1] == '?'){
		                   	        int Contador = ContarMinas(Fila+1, Columna+1, Minas, MatrizReal);
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila+1][Columna+1] = Contador + '0';
								}
				   	 }
		             if (CasillaExistente (Fila+1, Columna-1) == true){
		                   if (HayMina (Fila+1, Columna-1, MatrizReal) == false)
		               		 	if (MatrizVisible[Fila+1][Columna-1] == '?'){
		                   	        int Contador = ContarMinas(Fila+1, Columna-1, Minas, MatrizReal);
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila+1][Columna-1] = Contador + '0';
							}
			         }
		    	}
		    	return (false);
		}
	}

/*Buscar sigue varias condiciones para cumplir  su objetivo , primero se revisa que la casilla no este inexplorada o marcada,
si esas condiciones se cumplen se compara el contador de minas con el contador de marcas y solo si son iguales entra 
a revisar cada casilla  , si encuentra un 0 llama a la funcion Cascada para revelar cualquier otro 0 adyacente*/
bool Buscar(char MatrizVisible[][LADO], char MatrizReal[][LADO],int Minas[][2], int Fila, int Columna, int *MovimientosRestantes){

int x = Fila;
int y = Columna;
	
		 if (MatrizVisible[Fila][Columna] == '?') //Revisa que no sea una casilla inexplorada 
	        return (false); 
	
	     if (MatrizVisible[Fila][Columna] == 'X' ) //Revisa que no sea una casilla marcada
		 	return (false);
	
			int Contador = ContarMinas(Fila, Columna, Minas, MatrizReal);
			int Marcadas = ContarMarcas(Fila,Columna, MatrizVisible);
	       	 if( Contador == Marcadas ){
					if (CasillaExistente (Fila-1, Columna) == true){
	               	    if (HayMina (Fila-1, Columna, MatrizReal) == true && MatrizVisible[Fila-1][Columna] != 'X'){  //Si Hay Mina y no esta Marcada boom! 
						         for (int i=0; i<NumMinas; i++)
						             MatrizVisible[Minas[i][0]][Minas[i][1]]='B';
			        				 ImprimeMatriz (MatrizVisible);
			        				 printf ("\nPerdiste ,Intenta no explotar a la proxima.!!!\n");
					   		return (true);
				    	}
	                	if (MatrizVisible[Fila-1][Columna] != 'X'){
	                	    if (MatrizVisible[Fila-1][Columna] == '?'){
	                   	        int Contador = ContarMinas(Fila-1, Columna, Minas, MatrizReal);
	        					    (*MovimientosRestantes)--;
	                           		 MatrizVisible[Fila-1][Columna] = Contador + '0'; 
	                           		 	if (MatrizVisible[Fila-1][Columna] == '0')
	                           		 		Cascada(MatrizVisible, MatrizReal, Minas, x, y, *&MovimientosRestantes);
	                       	}
						}
	               }
	         	    if (CasillaExistente (Fila+1, Columna) == true){
	                    if (HayMina (Fila+1, Columna, MatrizReal) == true && MatrizVisible[Fila+1][Columna] != 'X'){
						         for (int i=0; i<NumMinas; i++)
						             MatrizVisible[Minas[i][0]][Minas[i][1]]='B';
			        				 ImprimeMatriz (MatrizVisible);
			        				 printf ("\nPerdiste ,Intenta no explotar a la proxima.!!!\n");
					   		return (true);
				    	}
	                	if (MatrizVisible[Fila+1][Columna] != 'X'){
	                	    if (MatrizVisible[Fila+1][Columna] == '?'){
	                   	        int Contador = ContarMinas(Fila+1, Columna, Minas, MatrizReal);
	        					    (*MovimientosRestantes)--;
	                           		 MatrizVisible[Fila+1][Columna] = Contador + '0' ; 
	                           		 	if (MatrizVisible[Fila+1][Columna] == '0')
	                           		 		Cascada(MatrizVisible, MatrizReal, Minas, x, y, *&MovimientosRestantes);
	                       	}
						}
	               }
	         	   if (CasillaExistente (Fila, Columna+1) == true){
	                   if (HayMina (Fila, Columna+1, MatrizReal) == true && MatrizVisible[Fila][Columna+1] != 'X'){
					         for (int i=0; i<NumMinas; i++)
						         MatrizVisible[Minas[i][0]][Minas[i][1]]='B';
								 ImprimeMatriz (MatrizVisible);
			        			 printf ("\nPerdiste ,Intenta no explotar a la proxima.!!!\n");
					   		return (true);
				    	} 
	                	if (MatrizVisible[Fila][Columna+1] != 'X'){
	                	    if (MatrizVisible[Fila][Columna+1] == '?'){
	                   	        int Contador = ContarMinas(Fila, Columna+1, Minas, MatrizReal);
	        					    (*MovimientosRestantes)--;
	                           		 MatrizVisible[Fila][Columna+1] = Contador + '0' ; 
	                           		 	if (MatrizVisible[Fila][Columna+1] == '0')
	                           		 		Cascada(MatrizVisible, MatrizReal, Minas, x, y, *&MovimientosRestantes);
	                       	}
						}
	               }
	         	   if (CasillaExistente (Fila, Columna-1) == true){
	                   if (HayMina (Fila, Columna-1, MatrizReal) == true && MatrizVisible[Fila][Columna-1] != 'X'){
					         for (int i=0; i<NumMinas; i++)
				                 MatrizVisible[Minas[i][0]][Minas[i][1]]='B';
	        					 ImprimeMatriz (MatrizVisible);
	        					 printf ("\nPerdiste ,Intenta no explotar a la proxima.!!!\n");
					   		return (true);
				    	}
	                	if (MatrizVisible[Fila][Columna-1] != 'X'){
	                	    if (MatrizVisible[Fila][Columna-1] == '?'){
	                   	        int Contador = ContarMinas(Fila, Columna-1, Minas, MatrizReal);
	        					    (*MovimientosRestantes)--;
	                           		 MatrizVisible[Fila][Columna-1] = Contador + '0' ; 
	                           		 	if (MatrizVisible[Fila][Columna-1] == '0')
	                           		 		Cascada(MatrizVisible, MatrizReal, Minas, x, y, *&MovimientosRestantes);
	                       	}
						}
	               }
	         	   if (CasillaExistente (Fila-1, Columna+1) == true){
	                   if (HayMina (Fila-1, Columna+1, MatrizReal) == true && MatrizVisible[Fila-1][Columna+1] != 'X'){
					         for (int i=0; i<NumMinas; i++)
					             MatrizVisible[Minas[i][0]][Minas[i][1]]='B';
		        				 ImprimeMatriz (MatrizVisible);
		        				 printf ("\nPerdiste ,Intenta no explotar a la proxima.!!!\n");
					   		return (true);
				    	}
	                	if (MatrizVisible[Fila-1][Columna+1] != 'X'){
	                	    if (MatrizVisible[Fila-1][Columna+1] == '?'){
	                   	        int Contador = ContarMinas(Fila-1, Columna+1, Minas, MatrizReal);
	        					    (*MovimientosRestantes)--;
	                           		 MatrizVisible[Fila-1][Columna+1] = Contador + '0' ; 
	                           		 	if (MatrizVisible[Fila-1][Columna+1] == '0')
	                           		 		Cascada(MatrizVisible, MatrizReal, Minas, x, y, *&MovimientosRestantes);
	                       	}
						}
	               }
	         	   if (CasillaExistente (Fila-1, Columna-1) == true){
	                   if (HayMina (Fila-1, Columna-1, MatrizReal) == true && MatrizVisible[Fila-1][Columna-1] != 'X'){
					         for (int i=0; i<NumMinas; i++)
					             MatrizVisible[Minas[i][0]][Minas[i][1]]='B';
		        				 ImprimeMatriz (MatrizVisible);
		        				 printf ("\nPerdiste ,Intenta no explotar a la proxima.!!!\n");
					   		return (true);
				    	}
	                	if (MatrizVisible[Fila-1][Columna-1] != 'X'){
	                	    if (MatrizVisible[Fila-1][Columna-1] == '?'){
	                   	        int Contador = ContarMinas(Fila-1, Columna-1, Minas, MatrizReal);
	        					    (*MovimientosRestantes)--;
	                           		 MatrizVisible[Fila-1][Columna-1] = Contador + '0' ; 
	                           			 if (MatrizVisible[Fila-1][Columna-1] == '0')
	                           		 		Cascada(MatrizVisible, MatrizReal, Minas, x, y, *&MovimientosRestantes);
	                       	}
						}
	               }
	         	   if (CasillaExistente (Fila+1, Columna+1) == true){
	                   if (HayMina (Fila+1, Columna+1, MatrizReal) == true && MatrizVisible[Fila+1][Columna+1] != 'X'){
					         for (int i=0; i<NumMinas; i++)
					             MatrizVisible[Minas[i][0]][Minas[i][1]]='B';
		        				 ImprimeMatriz (MatrizVisible);
		        				 printf ("\nPerdiste ,Intenta no explotar a la proxima.!!!\n");
					   		return (true);
				    	}
	                	if (MatrizVisible[Fila+1][Columna+1] != 'X'){
	                	    if (MatrizVisible[Fila+1][Columna+1] == '?'){
	                   	        int Contador = ContarMinas(Fila+1, Columna+1, Minas, MatrizReal);
	        					    (*MovimientosRestantes)--;
	                           		 MatrizVisible[Fila+1][Columna+1] = Contador + '0' ;
	                           			 if (MatrizVisible[Fila+1][Columna+1] == '0')
	                           		 		Cascada(MatrizVisible, MatrizReal, Minas, x, y, *&MovimientosRestantes);
	                       	}
						}
	               }
	         	   if (CasillaExistente (Fila+1, Columna-1) == true){
	                   if (HayMina (Fila+1, Columna-1, MatrizReal) == true && MatrizVisible[Fila+1][Columna-1] != 'X'){
					         for (int i=0; i<NumMinas; i++)
					             MatrizVisible[Minas[i][0]][Minas[i][1]]='B';
		        				 ImprimeMatriz (MatrizVisible);
		        				 printf ("\nPerdiste ,Intenta no explotar a la proxima.!!!\n");
					   		return (true);
				    	}
	                	if (MatrizVisible[Fila+1][Columna-1] != 'X'){
	                	    if (MatrizVisible[Fila+1][Columna-1] == '?'){
	                   	        int Contador = ContarMinas(Fila+1, Columna-1, Minas, MatrizReal);
	        					    (*MovimientosRestantes)--;
	                           		 MatrizVisible[Fila+1][Columna-1] = Contador + '0' ; 
	                           			 if (MatrizVisible[Fila+1][Columna-1] == '0')
	                           		 		Cascada(MatrizVisible, MatrizReal, Minas, x, y, *&MovimientosRestantes);
	                       	}
						}
	               }
	 		}                                                                                       
	        return (false);	
	}

//Funcion exclusiva del comando Buscar que entra en efecto si se revela una casilla con 0 , revelando las casillas con 0 vecinas 
void Cascada(char MatrizVisible[][LADO], char MatrizReal[][LADO],int Minas[][2], int Fila, int Columna, int *MovimientosRestantes){

int x = Fila;
int y = Columna;

		            if (CasillaExistente (Fila-2, Columna) == true){
		                int Contador = ContarMinas(Fila-2, Columna, Minas, MatrizReal);
						   if (HayMina (Fila-2, Columna, MatrizReal) == false)
		                		if ((MatrizVisible[Fila-2][Columna] == '?')&&( Contador == 0)){
		        						(*MovimientosRestantes)--;
		                     	        MatrizVisible[Fila-2][Columna] = Contador + '0';
								}
		            }
		             if (CasillaExistente (Fila+2, Columna) == true){
						int Contador = ContarMinas(Fila+2, Columna, Minas, MatrizReal);
						   if (HayMina (Fila+2, Columna, MatrizReal) == false)
		                		if ((MatrizVisible[Fila+2][Columna] == '?')&&(Contador == 0)){
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila+2][Columna] = Contador + '0';
								}
					}
		             if (CasillaExistente (Fila, Columna+2) == true){
		       	        int Contador = ContarMinas(Fila, Columna+2, Minas, MatrizReal);
		                   if (HayMina (Fila, Columna+2, MatrizReal) == false)
		                		if ((MatrizVisible[Fila][Columna+2] == '?')&&(Contador == 0)){
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila][Columna+2] = Contador + '0';
								}
					}
		             if (CasillaExistente (Fila, Columna-2) == true){
             	        int Contador = ContarMinas(Fila, Columna-2, Minas, MatrizReal);
		                   if (HayMina (Fila, Columna-2, MatrizReal) == false)
		         		       	if ((MatrizVisible[Fila][Columna-2] == '?')&&(Contador == 0)){
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila][Columna-2] = Contador + '0';
								}
					}
		             if (CasillaExistente (Fila-2, Columna+2) == true){
	           	        int Contador = ContarMinas(Fila-2, Columna+2, Minas, MatrizReal);
		                   if (HayMina (Fila-2, Columna+2, MatrizReal) == false)
		            	    	if ((MatrizVisible[Fila-2][Columna+2] == '?')&&(Contador == 0)){
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila-2][Columna+2] = Contador + '0';
								}
					}
		             if (CasillaExistente (Fila-2, Columna-2) == true){
						int Contador = ContarMinas(Fila-2, Columna-2, Minas, MatrizReal);
		                   if (HayMina (Fila-2, Columna-2, MatrizReal) == false)
		            	    	if ((MatrizVisible[Fila-2][Columna-2] == '?')&&(Contador == 0)){
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila-2][Columna-2] = Contador + '0';
								}
					}
		             if (CasillaExistente (Fila+2, Columna+2) == true){
		                int Contador = ContarMinas(Fila+2, Columna+2, Minas, MatrizReal);
		                   if (HayMina (Fila+2, Columna+2, MatrizReal) == false)
		             	    	if ((MatrizVisible[Fila+2][Columna+2] == '?')&&(Contador == 0)){
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila+2][Columna+2] = Contador + '0';
								}
					}
		             if (CasillaExistente (Fila+2, Columna-2) == true){
		             	int Contador = ContarMinas(Fila+2, Columna-2, Minas, MatrizReal);
		                   if (HayMina (Fila+2, Columna-2, MatrizReal) == false)
		        	        	if ((MatrizVisible[Fila+2][Columna-2] == '?')&&(Contador == 0)){
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila+2][Columna-2] = Contador + '0';
								}
		            }
		            if (CasillaExistente (Fila-2, Columna-1) == true){
		            	int Contador = ContarMinas(Fila-2, Columna-1, Minas, MatrizReal);
		                   if (HayMina (Fila-2, Columna-1, MatrizReal) == false)
		      		          	if ((MatrizVisible[Fila-2][Columna-1] == '?')&&(Contador == 0)){
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila-2][Columna-1] = Contador + '0';
								}
		            }
		             if (CasillaExistente (Fila-2, Columna+1) == true){
		             	int Contador = ContarMinas(Fila-2, Columna+1, Minas, MatrizReal);
		                   if (HayMina (Fila-2, Columna+1, MatrizReal) == false)
		              		  	if ((MatrizVisible[Fila-2][Columna+1] == '?')&&(Contador == 0)){
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila-2][Columna+1] = Contador + '0';
								}
					}
		             if (CasillaExistente (Fila-1, Columna-2) == true){
		             	int Contador = ContarMinas(Fila-1, Columna-2, Minas, MatrizReal);
		                   if (HayMina (Fila-1, Columna-2, MatrizReal) == false)
		      		          	if ((MatrizVisible[Fila-1][Columna-2] == '?')&&(Contador == 0)){
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila-1][Columna-2] = Contador + '0';
								}
					}
		             if (CasillaExistente (Fila-1, Columna+2) == true){
						int Contador = ContarMinas(Fila-1, Columna+2, Minas, MatrizReal);
		                   if (HayMina (Fila-1, Columna+2, MatrizReal) == false)
		 		               	if ((MatrizVisible[Fila-1][Columna+2] == '?')&&(Contador == 0)){

		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila-1][Columna+2] = Contador + '0';
								}
					}
		             if (CasillaExistente (Fila+1, Columna-2) == true){
		             	int Contador = ContarMinas(Fila+1, Columna-2, Minas, MatrizReal);
		                   if (HayMina (Fila+1, Columna-2, MatrizReal) == false)
		                		if ((MatrizVisible[Fila+1][Columna-2] == '?')&&(Contador == 0)){
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila+1][Columna-2] = Contador + '0';
								}
					}
		             if (CasillaExistente (Fila+1, Columna+2) == true){
					    int Contador = ContarMinas(Fila+1, Columna+2, Minas, MatrizReal);
		                   if (HayMina (Fila+1, Columna+2, MatrizReal) == false)
		              		  	if ((MatrizVisible[Fila+1][Columna+2] == '?')&&(Contador == 0)){
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila+1][Columna+2] = Contador + '0';
								}
					}
		             if (CasillaExistente (Fila+2, Columna-1) == true){
		             	int Contador = ContarMinas(Fila+2, Columna-1, Minas, MatrizReal);
		                   if (HayMina (Fila+2, Columna-1, MatrizReal) == false)
		               		 	if ((MatrizVisible[Fila+2][Columna-1] == '?')&&(Contador == 0)){
		        					(*MovimientosRestantes)--;
		                            MatrizVisible[Fila+2][Columna-1] = Contador + '0';
								}
					}
		             if (CasillaExistente (Fila+2, Columna+1) == true){
		             	int Contador = ContarMinas(Fila+2, Columna+1, Minas, MatrizReal);
		                   if (HayMina (Fila+2, Columna+1, MatrizReal) == false)
		              		  	if ((MatrizVisible[Fila+2][Columna+1] == '?')&&(Contador == 0)){
		        					(*MovimientosRestantes)--;
		                             MatrizVisible[Fila+2][Columna+1] = Contador + '0';
								}
	       			}
	}
