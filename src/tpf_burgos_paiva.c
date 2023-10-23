#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Se puso una funcion que con el vector de dados imprime la cantidad de dados y tambien ve quien gano o si hubo un empate (print_ganador)
//Tambien se hizo una funcion que resetea los valores de detector[12] para evitar
//Se hizo un void para que retorne correctamente los valores del vector director[12]
//Se puso un if(acabar_juego == 1){ } tambien entre las jugadas del cpu porque podia resultar el caso que el tablero se llenara e igual se ejecutase la jugada del Jugador

int matriz[10][10];

void inicializarmatriz(){
	for(int i = 0; i < 5; i++){
			for(int j = 0; j < 5; j++){
				matriz[i][j] = 0;
			}
		}
}
void mostrarmatriz(){

	printf("\n");
	printf("+");
	for(int i = 0; i < 5; i++){
		printf("---+");
		if(i == 5-1)
			printf("\n");
	}
	for(int i = 0; i < 5; i++){

		printf("|");
		for(int j = 0; j < 5; j++){

			printf(" %d |", matriz[i][j]);
		}
		printf("\n");
		printf("+");
		for(int i = 0; i < 5; i++){
			printf("---+");
			if(i == 5-1)
				printf("\n");
		}
	}
	printf("\n");
}

//Detecta la cantidda de opciones de suma hay ya que cada vez que entra en un if este aumenta. Tambien se guarda en un vector que clase de suma es dependiendo en donde entre va a guardar un numero que es el tipo de suma
void detectar_tip_suma(int detector [12],int y, int x){
	int cant_pos = 0; //calcula las posibilidades para comer las fichas
	detector[1] = 0;
	//Sumamos +1 porque queremos la posicion [0] libre para luego colocarle el valor de cant_post
	// suma en cruz
	if(matriz[y-1][x] != 0 && matriz[y+1][x] != 0 && matriz[y][x-1] != 0 && matriz[y][x+1] != 0 && (abs(matriz[y-1][x]) + abs(matriz[y+1][x]) + abs(matriz[y][x-1]) + abs(matriz[y][x+1]) )<= 6){
		detector[cant_pos+1] = 1;
		++cant_pos;
	}
	//Grupo autito
	//vacio arriba
	if( matriz[y][x-1] && matriz[y+1][x] != 0  && matriz[y][x+1] != 0 && abs(matriz[y][x-1]) + abs(matriz[y+1][x]) + abs(matriz[y][x+1]) <= 6){
		detector[cant_pos+1] = 2;
		++cant_pos;
	}
	//vacio abajo
	if(matriz[y-1][x] != 0  &&  matriz[y][x-1] != 0 && matriz[y][x+1] != 0 && abs(matriz[y-1][x])  + abs(matriz[y][x-1]) + abs(matriz[y][x+1]) <= 6){
		detector[cant_pos+1] = 3;
		++cant_pos;
	}
	//vacio izquieda
	if(matriz[y-1][x] != 0 && matriz[y+1][x] != 0 && matriz[y][x+1] != 0 && abs(matriz[y-1][x]) + abs(matriz[y+1][x])  + abs(matriz[y][x+1]) <= 6){
		detector[cant_pos+1] = 4;
		++cant_pos;
	}
	//vacio derecha
	if(matriz[y-1][x] != 0 && matriz[y+1][x] != 0 && matriz[y][x-1] != 0  && abs(matriz[y-1][x]) + abs(matriz[y+1][x]) + abs(matriz[y][x-1]) <= 6){
		detector[cant_pos+1] = 5;
		++cant_pos;
	}
	//Grupo esquina
	//izquieda arriba
	if(matriz[y-1][x] != 0  && matriz[y][x-1] != 0  && abs(matriz[y-1][x]) + abs(matriz[y][x-1]) <= 6){
		detector[cant_pos+1] = 6;
		++cant_pos;
	}
	//derecha arriba
	if(matriz[y-1][x] != 0  && matriz[y][x+1] != 0 && abs(matriz[y-1][x]) + abs(matriz[y][x+1]) <= 6){
		detector[cant_pos+1] = 7;
		++cant_pos;
	}
	// izquieda abajo
	if( matriz[y+1][x] != 0 && matriz[y][x-1] != 0 &&   abs(matriz[y+1][x]) + abs(matriz[y][x-1]) <= 6){
		detector[cant_pos+1] = 8;
		++cant_pos;
	}
	//derecha abajo
	if(matriz[y+1][x] != 0 && matriz[y][x+1] != 0  && abs(matriz[y+1][x])  + abs(matriz[y][x+1]) <= 6){
		detector[cant_pos+1] = 9;
		++cant_pos;
	}
	//Grupo palito
	//izquieda-derecha
	if(  matriz[y][x-1] != 0 && matriz[y][x+1] != 0 && abs(matriz[y][x-1]) + abs(matriz[y][x+1]) <= 6){
		detector[cant_pos+1] = 10;
		++cant_pos;
	}
	//arriba-abajo
	if(matriz[y-1][x] != 0 && matriz[y+1][x] != 0 && abs(matriz[y-1][x]) + abs(matriz[y+1][x])  <= 6){
		detector[cant_pos+1] = 11;
		++cant_pos;
	}
	if( cant_pos == 0){
		detector[1] = 1;
	}
	// Aca alojamos la cantidad de opciones de suma en la primera posicion de detector
	// Se hace esto por que probablemente necesite esta variable en otras funciones y solo puedo retornar una variable en c, asi que intento poner todos los datos posibles en detector[]
	detector[0] = cant_pos;
	// Si detector es hay mas opciones te va tirar distintos prints de tus posibles sumas
	// Empieza en 1 porque en la posicion 0 esta la cantidad de opciones
	// El por hace que salte a cada una de las opciones
	if(detector[0] > 1){
		for( int i = 1; i <= cant_pos; ++i){

			//cruz
			if(detector[i] == 1){
				printf("Si quieres sumar en forma de cruz presione 1: \n");
			}
			//Grupito auto
			//vacio arriba
			if(detector[i] == 2){
				printf("Si quieres sumar en todos los valores adyacentes menos el de arriba presione 2: \n");
			}
			//vacio abajo
			if(detector[i] == 3){
				printf("Si quieres sumar todos los valores adyacentes menos el de abajo presione 3: \n");
			}
			//vacio izquieda
			if(detector[i] == 4){
				printf("Si quieres sumar todos los valores adyacentes menos el de la izquieda presione 4: \n");
			}
			//vacio derecha
			if(detector[i] == 5){
				printf("Si quieres todos los valores adyacentes menos el de la derecha presione 5: \n");
			}
			//Grupo esquina
			//arriba-izquierda
			if(detector[i] == 6){
				printf("Si quieres sumar el valor de la izquierda y arriba presione 6: \n");
			}
			//arriba-derecha
			if(detector[i] == 7){
				printf("Si quieres sumar los valores de derecha y arriba presione 7:  \n");
			}
			//abajo-izquieda
			if(detector[i] == 8){
				printf("Si quieres sumar los valores de izquieda y abajo presione 8: \n");
			}
			//abajo-derecha
			if(detector[i] == 9){
				printf("Si quieres sumar los valores de derecha y abajo persione 9: \n");
			}
			//Grupo palito
			// derecha-izquieda
			if(detector[i] == 10){
				printf("Si quieres sumar los valores de derecha y izquieda presione 10: \n");
			}
			//arriba-abajo
			if(detector[i] == 11){
				printf("Si quieres sumar los valores de arriba y abajo presione 11: \n");
			}
		}
	}
}
//La funcion recorre toda la matriz y va sumando a cont siempre y cuando no encientre 0
//Si cont llega a valer 25 (la matriz es 5x5 eso significa que no hay espacios vacios en la matriz) fin va valer 1
//La utilidad de esto es que todo el codigo va estar en un while que mientras fin no sea distinto a 0 se va a volver a ejecutarse, esta funcion cambia el valor de fin si es que no hay espacion vacios en la matriz
int ver_fin_juego(int fin){
	int cont = 0;

	for(int i = 0; i < 5; i++){
			for(int j = 0; j < 5; j++){
				if(matriz[i][j] != 0){ ++cont;}
			}
		}
	if(cont == 25){ fin = 1;}
	return fin;
}
//Almacena en la variable ganador la cantidad de dadods azules y rojos

//Compara con las cantidades almacenadas en ganador para ver quien gano o si hubo un empate
void print_ganador(int ganador[1]){
    if( ganador[0] > ganador[1] ){
        printf("Jugador azul: %d Jugador rojo: %d \n", ganador[0],ganador[1]);
        printf("El ganador es el jugador azul!");
    }

    if( ganador[0] < ganador[1] ){
        printf("Jugador azul: %d Jugador rojo: %d \n", ganador[0],ganador[1]);
        printf("El ganador es el jugador rojo!");
    }

    if( ganador[0] == ganador[1] ){
        printf("Jugador azul: %d Jugador rojo: %d \n", ganador[0],ganador[1]);
        printf("El un empate!");
    }
}
//Validar x e y para que no tomen valores fuera de la matriz
//Validacion de que no se sobreescriba en un lugar dode hay un dado
int ver_posicion_libre(int y, int x, int ver_coordenas[1]){

	while(matriz[y][x] != 0 || y < 0 || y > 4 || x < 0 || x > 4 ){
	    printf("La posicion puesta ya no es valida, vuelva a intentarlo \n");
		printf("Escriba las posiciones x para jugar: ");
		scanf("%d", &x);
		getchar();
		printf("Escribe la posicion de y para jugar: ");
		scanf("%d", &y);
		getchar();
	}
	ver_coordenas[0] = x;
	ver_coordenas[1] = y;
	return ver_coordenas[1];
}

int val_sum(int detector[12], int suma){
	//los valores permitidos seran todos los del detector menos el primero donde guardamos el tamaño
	int correcto = 0;
	//Es un while de verdadero o falso como inicialmente correcto es 0 es falso
	//entra en un for que recorre el detector desde 1
	//Si hay algun valor igual dentro del detector con el ingresado, entra en un if donde cambia el valor de correcto a 1 (verdadero)
	//Luego usamos break para que no entre de vuelta en el bucle
	if( detector[0] > 1){
	while (!correcto) {
        printf("Ingrese un valor permitido: ");
        scanf("%d", &suma);

        for (int i = 1; i < detector[0]+1 ; i++) {
            if (suma == detector[i]) {
                correcto = 1;
                break;
            }
        }
        if (!correcto) {
            printf("Valor no permitido. Intente de nuevo.\n");
        }
    }
    printf("El valor ingresado es válido: %d\n", suma);
	}
	if(detector[0] == 1){
		suma = detector[1];
	}
	if(detector[0] == 0){
		suma = 0;
	}
    return suma;
}
//Esta funcion hace que los valores que se sobrescriban en negativo o positivo dependiendo que que conjunto de opciones hayas elegido
int val_negativo(int i, int color, int empezar , int a, int y, int x ){

	if( (color == 1 && empezar == 1)||( color == 2 && empezar == 2 ) ){
		if(i % 2 == 1 ){
			matriz[y][x] = -a;
		}
		else{
			matriz[y][x] = a;
		}
	}
	if( (color == 2 && empezar == 1)||( color == 1 && empezar == 2 ) ){
			if(i % 2 == 0 ){
				matriz[y][x] = -a;
			}
			else{
				matriz[y][x] = a;
			}
		}
	return a;
}
// Esta funcion realizara la suma y vaciara los valores adyacentes
//El caso de suma sera seleccionado en funcion del valor
void suma_final(int suma, int x, int y, int i, int a, int color, int empezar){
	//sumar en forma de cruz
	if( suma == 1){
		a = abs(matriz[y-1][x]) + abs(matriz[y+1][x]) + abs(matriz[y][x-1]) + abs(matriz[y][x+1]);
		a = val_negativo(i,color,empezar , a,y, x );
		matriz[y-1][x] = 0;
		matriz[y+1][x] = 0;
		matriz[y][x+1] = 0;
		matriz[y][x-1] = 0;
	}
	//Grupo auto
	//vacio arriba
	if( suma == 2){
		a =  abs(matriz[y+1][x]) + abs(matriz[y][x-1]) + abs(matriz[y][x+1]);
		a = val_negativo(i,color,empezar , a,y, x );
		matriz[y+1][x] = 0;
		matriz[y][x+1] = 0;
		matriz[y][x-1] = 0;
	}
	//vacio abajo
	if( suma == 3){
		a = abs(matriz[y-1][x]) + abs(matriz[y][x-1]) + abs(matriz[y][x+1]);
		a = val_negativo(i,color,empezar , a,y, x );
		matriz[y-1][x] = 0;
		matriz[y][x+1] = 0;
		matriz[y][x-1] = 0;
	}
	//vacio izquierda
	if( suma == 4){
		a = abs(matriz[y-1][x]) + abs(matriz[y+1][x]) + abs(matriz[y][x+1]);
		a = val_negativo(i,color,empezar , a,y, x );
		matriz[y-1][x] = 0;
		matriz[y+1][x] = 0;
		matriz[y][x+1] = 0;
	}
	//vacio derecha
	if( suma == 5 ){
		a = abs(matriz[y-1][x]) + abs(matriz[y+1][x]) + abs(matriz[y][x-1]) + abs(matriz[y][x+1]);
		a = val_negativo(i,color,empezar , a,y, x );
		matriz[y-1][x] = 0;
		matriz[y+1][x] = 0;
		matriz[y][x+1] = 0;
		matriz[y][x-1] = 0;
	}
	//Grupo esquina
	//arriba-izquierda
	if( suma == 6){
		a = abs(matriz[y-1][x]) + abs(matriz[y][x-1]);
		a = val_negativo(i,color,empezar , a,y, x );
		matriz[y-1][x] = 0;
		matriz[y][x-1] = 0;
	}
	//arriba-derecha
	if( suma == 7){
		a = abs(matriz[y-1][x])  + abs(matriz[y][x+1]);
		a = val_negativo(i,color,empezar , a,y, x );
		matriz[y-1][x] = 0;
		matriz[y][x+1] = 0;
	}
	//abajo-izquieda
	if( suma == 8){
		a =  abs(matriz[y+1][x]) + abs(matriz[y][x-1]);
		a = val_negativo(i,color,empezar , a,y, x );
		matriz[y+1][x] = 0;
		matriz[y][x-1] = 0;
	}
	//abajo-derecha
	if( suma == 9){
		a =  abs(matriz[y+1][x]) + abs(matriz[y][x+1]);
		a = val_negativo(i,color,empezar , a,y, x );
		matriz[y+1][x] = 0;
		matriz[y][x+1] = 0;
	}
	//Grupo Palito
	//izquierda-derecha
	if( suma == 10){
		a = abs(matriz[y][x-1]) + abs(matriz[y][x+1]);
		a = val_negativo(i,color,empezar , a,y, x );
		matriz[y][x+1] = 0;
		matriz[y][x-1] = 0;
	}
	//arriba-abajo
	if( suma == 11){
		a = abs(matriz[y-1][x]) + abs(matriz[y+1][x]) ;
		a = val_negativo(i,color,empezar , a,y, x );
		matriz[y-1][x] = 0;
		matriz[y+1][x] = 0;
	}
	//No se puede sumar
	if(suma == 0){
		a = 1;
		a = val_negativo(i,color,empezar , a,y, x );
	}
}

int ver_color(int color){
	while( color != 1 && color != 2){
		printf("Los valores validos estan entre el 1 y el 2. Vuelva a ingresar un valor: ");
		scanf("%d", &color);
	}
	return color;
}

int ver_posicion_libre_maquina(int y, int x, int ver_coordenas[1]){

	while(matriz[y][x] != 0  ){
	    srand(time(NULL));

            	x = rand() % 5;
            	y = rand() % 5;
	}
	ver_coordenas[0] = x;
	ver_coordenas[1] = y;
	return ver_coordenas[1];
}

void reset_det(int detector[12]){

    for(int i = 0; i < 12; i++){
        detector[i] = 0;
    }
}
//detector es un vector donde se almacena en su primera posicion la cantidad de posibles jugadas y en las otras posiciones el tipo de jugadas que un puede hacer
//x e y son las cordenadas puestas para jugar
//La variable suma que se utiliza para elegir que forma de capturar dados se va a utilizar
//comp es una variable que define se se va jugar contra la CPU o PvP
//fin es la variable que entra a una funcion si toda la matriz es distinta 0 fin cambia de valor y eso hace que se deje de ejecutar el while
//color es la variable que selecciona que color tendra tu dado (para rojo le dimos valores negativos y para azul positivos)
//empezar es la variable que hace que se elija quien empieza

int main(){
	int detector[12],ver_coordenas[1];
	int x,y,suma, comp;
	int fin = 0;
	int color = 0;
	int empezar = 0;
	int i = 1;
	int a = 0;
	int acabar_juego = 0;


	printf("Escriba 1 si quiere jugar contra la CPU, escriba 2 si quiere jugar PvP: ");
	scanf("%d", &comp);
	comp = ver_color(comp);

	printf("Escriba 1 si quiere ser color rojo, escriba 2 si quiere ser color azul: ");
	scanf("%d", &color);
	color = ver_color(color);

	printf("Presione 1 si quieres empezar primero y 2 si jugar segundo: ");
	scanf("%d", &empezar);
	empezar = ver_color(empezar);

    inicializarmatriz();

    mostrarmatriz();

    if(comp == 2){
	while( fin == 0){
	printf("Escriba las posiciones x para jugar: ");
	scanf("%d", &x);
	getchar();
	printf("Escribe la posicion de y para jugar: ");
	scanf("%d", &y);
	getchar();

	ver_coordenas[0] = x;
	ver_coordenas[1] = y;

	ver_coordenas[1] =  ver_posicion_libre(y, x, ver_coordenas);

	x = ver_coordenas[0];
	y = ver_coordenas[1];

	detectar_tip_suma( detector, y, x);

	suma = val_sum(detector, suma);

	suma_final(suma, x,y,i, a, color,empezar);

	mostrarmatriz();

	reset_det(detector);

	fin = ver_fin_juego(fin);

    printf("Escriba 1 si quiere acabar el juego, sino ponga 2: ");
    scanf("%d", &acabar_juego);
    ver_color(acabar_juego);
    if(acabar_juego == 1){
        fin = 1;

    }

	// cambio de turno, cambio de color
	i++;
	    }
    }
    if(empezar == 1 && comp == 1){
        if(empezar == 1){
            while( fin == 0){
    	        printf("Escriba las posiciones x para jugar: ");
    	        scanf("%d", &x);
    	        getchar();
    	        printf("Escribe la posicion de y para jugar: ");
    	        scanf("%d", &y);
    	        getchar();

            	ver_coordenas[0] = x;
            	ver_coordenas[1] = y;

            	ver_coordenas[1] =  ver_posicion_libre(y, x, ver_coordenas);

            	x = ver_coordenas[0];
            	y = ver_coordenas[1];

                 detectar_tip_suma( detector, y, x);

            	suma = val_sum(detector, suma);

            	suma_final(suma, x,y,i, a, color,empezar);

            	mostrarmatriz();

            	fin = ver_fin_juego(fin);

            	if (fin == 0){
            	//cambio de turno y cambio de color
            	++i;
            	srand(time(NULL));


            	ver_coordenas[0] = rand() % 5;
            	ver_coordenas[1] = rand() % 5;
            	ver_coordenas[1] = ver_posicion_libre_maquina(y,x,ver_coordenas);

            	x = ver_coordenas[0];
            	y = ver_coordenas[1];


            	detectar_tip_suma( detector, y, x);

            	suma = val_sum(detector, suma);


            	suma_final(suma, x,y,i, a, color,empezar);

            	mostrarmatriz();
            	reset_det(detector);

            	fin = ver_fin_juego(fin);
            	//cambio de turno y cambio de color
            	i++;
            	printf("Escriba 1 si quiere acabar el juego, sino ponga 2: ");
                scanf("%d", &acabar_juego);
                ver_color(acabar_juego);
                if(acabar_juego == 1){
                fin = 1;

                    }
            	}
            }
        }
    }
    if(empezar == 2 && comp == 1){
        while( fin == 0){
            srand(time(NULL));


                ver_coordenas[0] = rand() % 5;
            	ver_coordenas[1] = rand() % 5;
            	ver_coordenas[1] = ver_posicion_libre_maquina(y,x,ver_coordenas);


            	x = ver_coordenas[0];
            	y = ver_coordenas[1];
            	detectar_tip_suma( detector, y, x);


            	suma = val_sum(detector, suma);

            	suma_final(suma, x,y,i, a, color,empezar);

            	mostrarmatriz();
            	reset_det(detector);

            	fin = ver_fin_juego(fin);
            	// si ya esta el juego no se va a ejecutar lo que esta dentro del if
            	if (fin == 0){

                //cambio de turno y cambio de color
            	i++;
            	printf("Escriba las posiciones x para jugar: ");
    	        scanf("%d", &x);
    	        getchar();
    	        printf("Escribe la posicion de y para jugar: ");
    	        scanf("%d", &y);
    	        getchar();

            	ver_coordenas[0] = x;
            	ver_coordenas[1] = y;

            	ver_coordenas[1] =  ver_posicion_libre(y, x, ver_coordenas);

            	x = ver_coordenas[0];
            	y = ver_coordenas[1];

            	detectar_tip_suma( detector, y, x);

            	suma = val_sum(detector, suma);

            	suma_final(suma, x,y,i, a, color,empezar);

            	mostrarmatriz();
            	reset_det(detector);
            	//cambio de turno y cambio de color
            	++i;
            	fin = ver_fin_juego(fin);
            	printf("Escriba 1 si quiere acabar el juego, sino ponga 2: ");
                scanf("%d", &acabar_juego);
                ver_color(acabar_juego);
                if(acabar_juego == 1){
                fin = 1;

                }

                //para que imprima quien gano si es que ya se lleno el table cuando jugo la CPU
                if(acabar_juego == 1){

            }
            }
        }
    }
    return 0;
}




