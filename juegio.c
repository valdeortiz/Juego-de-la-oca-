#include<stdio.h>   //standar input/output library
#include<stdlib.h>
//#include<conio.h> //libreria para windows de la funcion getch

#include<time.h> // para usar la funcion time y crear un numero random
#include<ncurses.h>// libreria para linux de la funcion getch

// declaro todas las variables universales a ser utilizadas proximamente ...
// decalro mis parametros
int  Menu(void); // nuestro menu principal con parametro vacio pero con retorno
void EscribeNombres(char [1][50]); // funcion vacia sin retorno con parametro de una variable de tipo char
int  Empieza(char [1][50]);
int  Cargar_Tablero(int [8][8]);
int  IniciaTablero(char [1][50],int,int [8][8],int);
int  MenuJuego(int ,int,char [1][50]);
int dados1();
int dados();
void Redibuja_Tablero(int [8][8]);
void jugar(int ,int,int, int [8][8], int);
int MenuJuego_maquina(int, int,char [1][50]);
int dados2();


//para ejecutar y compilar en linux: SI ESTAS EJECUTANDO DESDE CONSOLA. DEBES HACER LO SIGUIENTE > gcc tu_archivo.c -lncurses -o tu_ejecutable

int main()
{
    int Matriz_Tablero[8][8];  // decalramos nuestra maatriz de 8*8
    int vdado,opcion,color,rehazMenu,turno; //declaro mis variables locales a ser utilizados dentro del main
    char nombre[1][50]; // utilizamos un vector para guardar el nombre ..  utilizamos matriz porque al utilizar solamente como variable no se guarda el nombre del usuario



    do // operaciones a ser realizados antes del while
    {

        rehazMenu=0; // cierro mi bandera
		system("clear"); // limpiamos la pantalla..utilizar system cls en caso de ser windows
        opcion=Menu(); // guardamos lo retornado por la funcion menu en una variable para utilizar en el switch
        switch(opcion)   //con break salgo del switch, y veo cual es la opcion que tengo .. para poder desarrolar uno de los siguientes casos
        {

        case 1: // en el caso de comenzar el juego
        {
			 EscribeNombres(nombre); // llamamos a la funcion escribe nombre utilizando como parametro el nombre a ser ingresado

            if(Empieza(nombre)) // verificamos quien empieza
            {
                printf("\n\t JUGADOR 1 = %s\n\t", nombre[0]); //imprimimos el nombre de cada jugador
                turno=1; //designamos el turno
                if(Cargar_Tablero(Matriz_Tablero)) // vemos si nuestra matriz fue cargada con exito
                    printf("\n\n\tTablero cargado satisfactoriamente.");
                else
                {
                    printf("\t\nPartida anulada\n\t");
                    rehazMenu=1; // regresamos al menu en caso de no ser cargada nuestra matriz
                    break;
                }

            }
            else
            {
                printf("\n\t JUGADOR 2 = Maquina\n\t"); // realizamos la misma funcion pero para el jugador 2
                turno=2; // designamos el turno
                if(Cargar_Tablero(Matriz_Tablero))
                    printf("\n\n\tTablero cargado satisfactoriamente.");
                else
                {
                    printf("\t\nPartida anulada\n\t");
                    rehazMenu=1;
                    break;
                }
            }

            getch(); // pausamos el programa hasta ser presionada una tecla
            IniciaTablero(nombre,turno,Matriz_Tablero, vdado); // inciamos nuestro juego
            rehazMenu=1; // regresamos al menu al terminar nuestro juego
            break;
        }
        case 2: // Imprimimos las reglas a ser seguidas durante el desarrollo del juego
        {
            printf("\n\t**LAS CASILLAS ESPECIALES SON: \n\n\t=>La Oca:Ubicadas cada nueve casillas desde las casillas 5 y 9. Se avanza hasta la siguiente Oca.\n\n\t=>6 y 12-El puente: De un puente se avanza o retrocede hasta el otro puente.\n\n\t=>19-La posada: se pierde un turno(si el otro jugador cae tambien.. se levanta el castigo).\n\n\t=>31-El pozo: Se pierden dos turnos, si el otro jugador cae en la calavera(tomamos la calavera la casilla 31) se invalida el castigo.\n\n\t=>26 y 53-El dado: Se avanza o retrocede a la otra con el mismo simbolo y se vuelve a jugar lanzando un solo dado.\n\n\t=>42-El laberinto: Se regresa a la casilla 30.\n\n\t=>52-La carcel: En el siguiente turno el jugador debera obtener un puntaje de 2,6 o 12 al lanzar los dados para\n salir de la carcel. Tiene dos opurtunidades, una vez que recupere su libertad, podra lanzar nuevamente para avanzar.\n\n\t=>63-El jardin de la oca: Se debe de llegar a la ultima casilla con puntaje exacto por lo contrario se retrocede\ntantas casillas como puntos sobren. Otra forma de llegar es cuando se llega a la penultima, el jugador va de oca a oca y por lo tanto gana.\n ");
			getch();
            rehazMenu=1;
            break;
        }
        case 3: // creditos al desarrollador del programa
        {
            printf("\n\tDESARROLLADO POR VALDEMAR ORTIZ\n\n\tUNIVERSIDAD CATOLICA DE ASUNCION\n\n\t\tASUNCION - 2017\n\n"); // no me deja colocar acentos..
            getch();
            rehazMenu=1;
            break;
        }
        case 4: //controles del juego
        {
            printf("\n\tCONTROLES DE TECLADO:\n\n\tEl lanzamiento de los dados y las opciones del menu se escogera mediante\n\tel teclado numerico.\n\n\tCONTROLES DE RATON\n\n\tNinguno.\n\n\t");
            printf("\n\t *** PARA PODER PASAR A LA SIGUIENTE INTRUCCION SE DEBE PRESIONAR CUALQUIER TECLA ***\n\n\t**ADVERTENCIA: NO UTILIZAR LETRAS EN LOS MENUS DE OPCIONES**\n\n\t\t DISFRUTA DE ESTE MARAVILLOSO JUEGO !!!");
			getch();
            rehazMenu=1;
            break;
        }

        case 5: // la opcion para cerrar nuestro programa una vez finalizado.
        {
            printf("\n\n\tPresione una tecla para salir del juego: \n\n\n");
            break;
        }
        //default: // si se ingresa un tecla que no corresponda a ningun caso .. imprimimos lo sgte.
        //    printf("\n\tOpcion elegida no existente: \n\n\n"); // no es necesario un default .. pero siempre es bueno poner uno, para una buena tecnica de programacion
        }
    }
    while(rehazMenu==1); // repetimos el ciclo mientras nuestra bandera sea 1, en casi contrario cerramos el juego
    return(0);
}
//menu de bienvenida
int Menu() // nuestro menu principal .. preguntando cada uno de los casos
{
    int menu;
    do
    {
        printf("\n\t\t      || --------------------------------- ||");
		printf("\n\t\t      || --------------------------------- ||");
		printf("\n\t\t <====|| ** BIENVENIDO/A AL OCA VIRTUAL ** ||===>");
		printf("\n\t\t      || --------------------------------- ||");
		printf("\n\t\t      || --------------------------------- ||");
		printf("\n\n\t<= MENU =>:\n\t1-JUGAR.\n\t2-CASILLAS ESPECIALES.\n\t3-CREDITOS.\n\t4-CONTROLES.\n\t5-SALIR.\n\n\tADV:'NO INGRESAR LETRAS EN EL MENU PARA EVITAR PROBLEMAS.'\n\tOBS: RECOMENDAMOS LA LECTURA DE LAS REGLAS DEL JUEGO Y LOS CONTROLES ANTES DE EMPEZAR A JUGAR.\n\n\t\t\t\t*-* DIVIERTETE !!! *-*\n");
        scanf("%d", &menu);

        if (menu<=0 || menu>=6) //imprimirmos una advertencia si ingresa mal el dato
        {
            system("clear");
            printf("\n\tOpcion no valida, pulsa una tecla para volver al menu");
            getch();
            system("clear");
        }
    }
    while (menu<=0 || menu>=6); // repetimos el ciclo mientras no se cumpla la condicion
    system("clear");// limpiamos pantalla
    return(menu); // retornamos un valor para poder guardar en la variable opcion
}

// cargamos nuestro tablero de nuestro archivo .txt
int Cargar_Tablero(int Matriz_Tablero[8][8])
{
    int i,j;
    FILE *fp; // reservo un espacio en memoria
    fp=fopen("Tablero.txt","r"); //cargo todos los datos del txt
    if(fp!=NULL) // si se cargo bien el txt realiz la siguiente operacion (que no este vacio)
    {
        for (i=0;i<8;i++) //recorremos nuestra matriz y le cargamos los datos
        {
            for (j=0;j<8;j++)
            {
             fscanf(fp,"%d ", &Matriz_Tablero[i][j]);//guarda en forma de matriz los datos leidos en el txt
            }
             fscanf(fp,"\n");
        }

    return(1);//retornamos con valor para utilizar la variable .. para poder imprimir si se cargo o no el tablero
             fclose(fp);// borro todo espacio en memoria  .. ya que se guardo en la variable matriz
    }
    else
    {
         fprintf(stdout,"\n\tNo se pudo abrir el fichero que contine las posiciones de las fichas");
         return(0);
         fclose(fp);
    }

}

// el menu preguntando las opciones de juego para el jugador
int MenuJuego(int suma_tiros1, int suma_tiros2, char nombre [1][50])
{
    int repite;
    do
    {

        printf("\n\t** %s: Casilla N°'%d'\t** Maquina: Casilla N°'%d'\n\t**Las casillas especiales llevan '*'\n",nombre[0], suma_tiros1, suma_tiros2);
        printf("\n\t1-Lanzar Dado\n\t2-Rendirse\n\n\t");//imprimimos las opciones a ser elegidos por el usuario
        scanf("%d",&repite); //guardamos en la variable repite

    }
    while(repite<=0 || repite>3);
    return(repite); //retorno el valor para poder utilizar en switch.. guardando el valor en una variable
}
// menu de juego para el jugador 2 (maquina)
int MenuJuego_maquina(int suma_tiros1, int suma_tiros2, char nombre [1][50]) // realizamos la misma funcion que el anterior .. sin opcion de rendirse
{

    int repite;
    do
    {

        printf("\n\t** %s: Casilla N°'%d'\t** Maquina: Casilla N°'%d'\n\t**Las casillas especiales llevan '*'\n",nombre[0], suma_tiros1, suma_tiros2);
        printf("\n\t1-Lanzar Dado para la maquina\n\t");
        scanf("%d",&repite);

    }
    while(repite<=0 || repite>3); //  mientras no se cumpla la condicion se regresa el ciclo
 	return(repite);   // para poder utilizar en algun if  si fuera necesario
}

void EscribeNombres(char nombre [1][50]) //realizamos una funcion sin retorno .. con parametro de variable char
{
    int i=0;

    for(i=0; i<=0; i++)
    {
        printf("\n\tOBS: 'Colocar el nombre sin espacios'");
        printf("\n\n\tEscribe el nombre del Jugador %d: ",i+1);
        scanf("%s", nombre[i]); // NOMBRE ES UNA MATRIZ. AL COLOCARLE SOLAMENTE UN [] ESTAS MANEJANDO CON UN VECTOR. EN ESTE CASO EL OPERADOR "&" DE REFERENCIA NO ES NECESARIO COLOCAR.
     }

	   system("clear");
}


int Empieza(char nombre [1][50])// sorteo quien empieza el juego entre mis dos competidores atraves un lanzamiento de dados
{
    int num,begin;

    do
    {
        system("clear"); //limpiamos la pantalla
        srand(time(NULL));
    	num=1+rand()%3; //simulamos un lanzamiento de dados y el que sale empieza
		if(num==1){ // imprimimos quien empieza segun el numero sorteo anteriormente
			printf("\n\tEl jugador 1 saco el dado mas alto." );
			begin=1;
		}else{
			printf("\n\tEl jugador 2 saco el dado mas alto.");
			begin=2;
		}

    }
    while(begin<1 || begin>2);// por si coloca mal el dato

    if(begin==1)// devolvemos un valor a nuestra variable para poder utilizar en nuestro if principal
        return(1);
    else
        return(0);
    }



// nuestro tablero a ser impreso en cada movimiento ..
void Redibuja_Tablero(int Matriz_Tablero[8][8])
{

        printf("\n\t    COL    1     2    3    4    5    6    7   8");
        printf("\n\tFIL      |----|----|----|----|----|----|----|----|");
        printf("\n\t 1       | %d | %d | %d |*%d |*%d | %d | %d | %d |",Matriz_Tablero[0][0],Matriz_Tablero[0][1],Matriz_Tablero[0][2],Matriz_Tablero[0][3],Matriz_Tablero[0][4],Matriz_Tablero[0][5],Matriz_Tablero[0][6],Matriz_Tablero[0][7]);
        printf("\n\t         |----|----|----|----|----|----|----|----|");
        printf("\n\t 2       |*%d | %d | %d | %d |*%d | %d | %d |*%d |",Matriz_Tablero[1][0],Matriz_Tablero[1][1],Matriz_Tablero[1][2],Matriz_Tablero[1][3],Matriz_Tablero[1][4],Matriz_Tablero[1][5],Matriz_Tablero[1][6],Matriz_Tablero[1][7]);
        printf("\n\t         |----|----|----|----|----|----|----|----|");
        printf("\n\t 3       | %d |*%d | %d | %d | %d | %d | %d | %d |",Matriz_Tablero[2][0],Matriz_Tablero[2][1],Matriz_Tablero[2][2],Matriz_Tablero[2][3],Matriz_Tablero[2][4],Matriz_Tablero[2][5],Matriz_Tablero[2][6],Matriz_Tablero[2][7]);
        printf("\n\t         |----|----|----|----|----|----|----|----|");
        printf("\n\t 4       | %d | %d |*%d |*%d   %d*|*%d | %d |*%d |",Matriz_Tablero[3][0],Matriz_Tablero[3][1],Matriz_Tablero[3][2],Matriz_Tablero[3][3],Matriz_Tablero[3][4],Matriz_Tablero[3][5],Matriz_Tablero[3][6],Matriz_Tablero[3][7]);
        printf("\n\t         |----|----|----|----|----|----|----|----|");
        printf("\n\t 5       |*%d | %d | %d | %d | %d |*%d |*%d | %d |",Matriz_Tablero[4][0],Matriz_Tablero[4][1],Matriz_Tablero[4][2],Matriz_Tablero[4][3],Matriz_Tablero[4][4],Matriz_Tablero[4][5],Matriz_Tablero[4][6],Matriz_Tablero[4][7]);
        printf("\n\t         |----|----|----|----|----|----|----|----|");
        printf("\n\t 6       |*%d | %d | %d |*%d | %d | %d | %d | %d |",Matriz_Tablero[5][0],Matriz_Tablero[5][1],Matriz_Tablero[5][2],Matriz_Tablero[5][3],Matriz_Tablero[5][4],Matriz_Tablero[5][5],Matriz_Tablero[5][6],Matriz_Tablero[5][7]);
        printf("\n\t         |----|----|----|----|----|----|----|----|");
        printf("\n\t 7       | %d | %d | %d |*%d |*%d |*%d | %d | *%d |",Matriz_Tablero[6][0],Matriz_Tablero[6][1],Matriz_Tablero[6][2],Matriz_Tablero[6][3],Matriz_Tablero[6][4],Matriz_Tablero[6][5],Matriz_Tablero[6][6],Matriz_Tablero[6][7]);
        printf("\n\t         |----|----|----|----|----|----|----|----|");
        printf("\n\t 8       |  %d |  %d |  %d |  %d | *%d | *%d |  %d |  %d |",Matriz_Tablero[7][0],Matriz_Tablero[7][1],Matriz_Tablero[7][2],Matriz_Tablero[7][3],Matriz_Tablero[7][4],Matriz_Tablero[7][5],Matriz_Tablero[7][6],Matriz_Tablero[7][7]);
        printf("\n\t         |----|----|----|----|----|----|----|----|\n\n");

}


int IniciaTablero(char nombre [1][50],int turno, int Matriz_Tablero[8][8], int vdado) //iniciamos nuestro juego
{
    int rendicion=0;
    int opcion, rdados=0,k;
    int band1=0,band2=0,band3=0,band4=0;
    int suma_tiros1=0, suma_tiros2=0, resto=0;

    do
    {

        //system("clear"); //borro la pantalla
        //verificamos si alguno ṕierde un turno
        if(suma_tiros1==52 && turno==1){
            for(k=0; k<3; k++){
                rdados=dados2();
                if(rdados==2 || rdados==6 || rdados==12){
                    printf("\n\tLograste escapar de la carcel");
                    turno=1;
                }else{
                    printf("\n\tSigues en la carcel");
                    turno=2;
                }
            }
        }
        if(suma_tiros2==52 && turno==2){
            for(k=0; k<3; k++){
                rdados=dados();
                if(rdados==2 || rdados==6 || rdados==12){
                    printf("\n\tLograste escapar de la carcel");
                    turno=2;
                }else{
                    printf("\n\tSigues en la carcel");
                    turno=1;
                }
            }
        }
        if(band1<=2){
        if(suma_tiros1==19){
            band1=band1+1;
            turno=2;}}
         if(suma_tiros1==31 && band2<=3){
            band2=band2+1;
            turno=2;
        }

        if(suma_tiros1==19 && band1>2){
        turno=1;}
        if(suma_tiros1==31 && band2>3){
        turno=1;}

        if(band3<=2){
        if(suma_tiros2==19){
            band3=band3+1;
            turno=1;}}
        if(suma_tiros2==31 && band4<=3)
            {
            band4=band4+1;
            turno=1;
            }

        if (suma_tiros2==19 && band3>2 ){
        turno=2;}
        if(suma_tiros2==31 && band4>3){
            turno=2;
        }


        if(turno==1)   //turno del jugador 1.. realizar lo siguiente
        {
            printf("\n\n\t\t\tJUEGA %s\n", nombre[0]); // imprimimos de quien es la opurtunidad de jugar
   			Redibuja_Tablero(Matriz_Tablero);   //redibujo el tablero para poder ver en que posicion esta
        	opcion=MenuJuego( suma_tiros1, suma_tiros2,nombre); // guardanos la variable regrsada de nuestra funcion menu en una nueva llamada 'opcion'

		}

        if(turno==2) // si es el turno del jugador 2 realizar la siguientes operaciones
        {

			printf("\n\n\t\t\tJUEGA LA MAQUINA\n"); // imprimimos que la maquina es quien juega
        	Redibuja_Tablero(Matriz_Tablero);   //redibujo tablero
	        opcion=MenuJuego_maquina( suma_tiros1, suma_tiros2,nombre); // guardamos lo retornado por nuestra funcion menu en la variable opcion

		}

        getch(); //presionar una tecla para poder pasar
        system("clear");//limpiamos nuestra pantalla
             // elige si quiere jugar o rendirse

        switch(opcion) //realizamos la operacion segun la variable opcion
        {
        case 1: // en el caso uno lanzamos el dado y nos movemos en el tablero
        {
            system("clear");
            if(turno==1){ //cambio de turno y sumamos la cantidad de casillas que se movio y verificamos la casilla en que se encuentra
                if(suma_tiros1==26 || suma_tiros1==53){
                    vdado=dados1(); //llamamos a nuestra funcion de lanzamiento de dados a realizar sus operaciones
                }else{
                    vdado=dados();// para todas las casilla menos la 26 y 53
                }

                suma_tiros1=suma_tiros1+vdado; //sumamos los dados para poder saber en que casilla se encuentra el jugador

                if(suma_tiros1>63){ // verificamos que no pase el numero de casilla de ser asi retrocede las casilla que le sobra
                    band1=0;
                    band2=0;
                    resto=suma_tiros1-63;
                    suma_tiros1=63-resto;
                }
               switch(suma_tiros1){ //verificamos que el jugador no se encuentre en alguna casilla especial
                case 5: {
                    printf("\n\tCaiste en la Oca(N°5).. Avanzas hasta la casilla N°9");
                    suma_tiros1=9;
                    break;}
                case 9: {
                    printf("\n\tCaiste en la Oca(N°9).. Avanzas hasta la casilla N°14");
                    suma_tiros1=14;
                    break;}
                case 14: {
                    printf("\n\tCaiste en la Oca(N°14).. Avanzas hasta la casilla N°18");
                    suma_tiros1=18;
                    break;}
                case 18: {
                    printf("\n\tCaiste en la Oca(N°18).. Avanzas hasta la casilla N°23");
                    suma_tiros1=23;
                    break;}
                case 23: {
                    printf("\n\tCaiste en la Oca(N°23).. Avanzas hasta la casilla N°27");
                    suma_tiros1=27;
                    break;}
                case 27: {
                    printf("\n\tCaiste en la Oca(N°27).. Avanzas hasta la casilla N°32");
                    suma_tiros1=32;
                    break;}
                case 32: {
                    printf("\n\tCaiste en la Oca(N°32).. Avanzas hasta la casilla N°36");
                    suma_tiros1=36;
                    break;}
                case 36: {
                    printf("\n\tCaiste en la Oca(N°36).. Avanzas hasta la casilla N°41");
                    suma_tiros1=41;
                    break;}
                case 41: {
                    printf("\n\tCaiste en la Oca(N°41).. Avanzas hasta la casilla N°45");
                    suma_tiros1=45;
                    break;}
                case 45: {
                    printf("\n\tCaiste en la Oca(N°45).. Avanzas hasta la casilla N°50");
                    suma_tiros1=50;
                    break;}
                case 50: {
                    printf("\n\tCaiste en la Oca(N°50).. Avanzas hasta la casilla N°54");
                    suma_tiros1=54;
                    break;}
                case 54: {
                    printf("\n\tCaiste en la Oca(N°54).. Avanzas hasta la casilla N°59");
                    suma_tiros1=59;
                    break;}

                case 6: {
                    printf("\n\tCaiste en el Puente(N°6).. Avanzas hasta la casilla N°12");
                    suma_tiros1=12;
                    break;}
                case 12:{
                    printf("\n\tCaiste en el Puente(N°12).. retrocedes hasta la casilla N°6");
                    suma_tiros1=6;
                    break;}
                case 19: {
                    printf("\n\tCaiste en la Posada(N°19).. Pierdes un turno");
                    break;}
                case 31: {
                    if(suma_tiros2==31){
                        printf("\n\tCaiste en la casilla calavera.. Se reinicia el juego para vos");
                        suma_tiros1=0;
                        band3=5; //hacemos bandera mayores para que el turno opuesto .. siga jugando
                        band4=5;
                        }else {
                        printf("\n\tCaiste en el pozo(N°31).. Pierdes dos turnos");
                        band1=0,band2=0;
                        }break;}
                case 26: {
                    printf("\n\tCaiste en el Dado(N°26).. Avanzas a la casilla N°53  Y Lanzas con un solo dado el proximo turno");
                    suma_tiros1=53;
                    break;}
                case 53:{
                    printf("\n\tCaiste en el dado(N°53).. Retrocedes a la casilla N°26 Y lanzas con un solo dado el proximo turno");
                    suma_tiros1=26;
                    break;}
                case 42: {
                    printf("\n\tCaiste en la casilla (N°42).. Retrocedes hasta la casilla N°30");
                    suma_tiros1=30;
                    break;}
                case 52:{
                    printf("\n\tCaiste en la Carcel(N°52).. Debes de obtener un valor de 2,6,12 en los dados para volver a jugar ");
                break;}
                case 59: {
                    printf("\n\tCaiste en la Oca(N°59).. Avanzas hasta la casilla N°63");
                    suma_tiros1=63;
                    }//sacamos el break para que ingresa en el caso 63
                case 63:{ // mesaje de victoria y los datos de cada jugador
                    system("clear");
                    printf("\n\n\t\t|--------------------------------------------|");
                    printf("\n\t\t|--------------------------------------------| ");
                    printf("\n\t\t|*-* FELICIDADES %s, ERES EL VENCEDOR *-* |", nombre[0]);
                    printf("\n\t\t|--------------------------------------------|");
                    printf("\n\t\t|--------------------------------------------|");
                    printf("\n\t\t|                                            |");
                    printf("\n\t\t|                                            |");
                    printf("\n\t\t|                                            |");
                    printf("\n\n\tPOSICION FINAL DE: \n\n\t\t %s: Casilla N°%d \n\t\t Maquina: Casilla N°%d ",nombre[0], suma_tiros1,suma_tiros2);
                    getch();
                    rendicion=1;
                    break;
                }
               }

                turno=2; //cambiamos de turno

            }else{ //em caso contrario(turno=2) .. hacemos los mismos pasos que la anterior pero para el jugador 2
                if(suma_tiros2==26 || suma_tiros2==53){
                    vdado=dados1(); //llamamos a nuestra funcion de lanzamiento de dados a realizar sus operaciones
                }else{
                    vdado=dados();// para todas las casilla menos la 26 y 53
                }
                suma_tiros2=suma_tiros2+vdado;
                if(suma_tiros2>63){
                    band3=0;
                    band4=0;
                    resto=suma_tiros2-63;
                    suma_tiros2=63-resto;
                }

                switch(suma_tiros2){ //verificamos si el jugador cayo en ualguna casilla especial
                case 5: {
                    printf("\n\tCaiste en la Oca(N°5).. Avanzas hasta la casilla N°9");
                    suma_tiros2=9;
                    break;}
                case 9: {
                    printf("\n\tCaiste en la Oca(N°9).. Avanzas hasta la casilla N°14");
                    suma_tiros2=14;
                    break;}
                case 14: {
                    printf("\n\tCaiste en la Oca(N°14).. Avanzas hasta la casilla N°18");
                    suma_tiros2=18;
                    break;}
                case 18: {
                    printf("\n\tCaiste en la Oca(N°18).. Avanzas hasta la casilla N°23");
                    suma_tiros2=23;
                    break;}
                case 23: {
                    printf("\n\tCaiste en la Oca(N°23).. Avanzas hasta la casilla N°27");
                    suma_tiros2=27;
                    break;}
                case 27: {
                    printf("\n\tCaiste en la Oca(N°27).. Avanzas hasta la casilla N°32");
                    suma_tiros2=32;
                    break;}
                case 32: {
                    printf("\n\tCaiste en la Oca(N°32).. Avanzas hasta la casilla N°36");
                    suma_tiros2=36;
                    break;}
                case 36: {
                    printf("\n\tCaiste en la Oca(N°36).. Avanzas hasta la casilla N°41");
                    suma_tiros2=41;
                    break;}
                case 41: {
                    printf("\n\tCaiste en la Oca(N°41).. Avanzas hasta la casilla N°45");
                    suma_tiros2=45;
                    break;}
                case 45: {
                    printf("\n\tCaiste en la Oca(N°45).. Avanzas hasta la casilla N°50");
                    suma_tiros2=50;
                    break;}
                case 50: {
                    printf("\n\tCaiste en la Oca(N°50).. Avanzas hasta la casilla N°54");
                    suma_tiros2=54;
                    break;}
                case 54: {
                    printf("\n\tCaiste en la Oca(N°54).. Avanzas hasta la casilla N°59");
                    suma_tiros2=59;
                    break;}
                case 6: {
                        printf("\n\tCaiste en el Puente(N°6).. Avanzas hasta la casilla N°12");
                        suma_tiros2=12;
                    break;}
                case 12:{
                        printf("\n\tCaiste en el Puente(N°12).. retrocedes hasta la casilla N°6");
                        suma_tiros2=6;
                    break;}
                case 19: {
                    printf("\n\tCaiste en la Posada(N°19).. Pierdes un turno");
                    band3=0, band4=0;
                    break;}
                case 31: {
                    if(suma_tiros1==31){
                    printf("\n\tCaiste en la casilla calavera .. Se reinicia el juego para vos");
                    suma_tiros2=0;
                    band1=5;// para que el jugador contrario se encuentra en alguna casilla de pierde turno .. vuelva a jugar
                    band2=5;
                    }else{
                    printf("\n\tCaiste en el pozo(N°31).. Pierdes dos turnos");
                    band3=0,band4=0;
                    }break;}
                case 26: {
                    printf("\n\tCaiste en el Dado(N°26).. Avanzas a la casilla N°53 Y Lanzas con un solo dado el proximo turno");
                    suma_tiros2=53;
                    break;}
                case 53:{
                    printf("\n\tCaiste en el dado(N°53).. Retrocedes a la casilla N°26 Y Lanzas con un solo dado el proximo turno");
                    suma_tiros2=26;
                    break;}
                case 42: {
                    printf("\n\tCaiste en el Laberinto(N°42).. Retrocedes hasta la casilla N°30");
                    suma_tiros2=30;
                    break;}
                case 52:{
                    printf("\n\tCaiste en la Carcel(N°52).. Debes de obtener un valor de 2,6 o 12 en los dados para volver a jugar ");
                break;}
                case 59: {
                    printf("\n\tCaiste en la Oca(N°59).. Avanzas hasta la casilla N°63");
                    suma_tiros2=63;
                    }
                case 63:{
                    system("clear");
                    printf("\n\n\t\t| ----------------------------| ");
                    printf("\n\t\t|  EL GANADOR ES: LA MAQUINA  |");
                    printf("\n\t\t| ----------------------------|");
                    printf("\n\n\tPOSICION FINAL DE: \n\n\t\t %s: Casilla N°%d \n\n\t\t Maquina: Casilla N°%d ",nombre[0], suma_tiros1,suma_tiros2);
                    getch();
                    rendicion=1; //regresamos al menu principal... concluyendo el juego
                    break;
                }
               }

                turno=1; //cambiamos de turno
            }

            getch();
            break;  //salgo de switch
        }
        case 2: // el jugador 1 desea rendirse.. el jugador 2 no tiene posibilidad de rendirse por ser la maquina
        {
            if(turno==1) // imprimimos un mensaje de victoria para la maquina
            {
                system("clear");
                printf("\n\t%s se rinde, EL GANADOR ES: La Maquina", nombre[0]);
                printf("\n\n\tPOSICION FINAL DE: \n\n\t\t %s: Casilla N°%d \n\n\t\t Maquina: Casilla N°%d ",nombre[0], suma_tiros1,suma_tiros2);
                rendicion=1;
                getch();
            }
            break;
        }
        }
    }
    while(rendicion==0); // la maquina no puede rendirse por ende no puede perder por rendicion y no entra en el caso 2
}

int dados() // lanzamos ambos dado
{
    system("clear");
    int dado=0;
        srand(time(NULL));
        dado= 2+rand()%11 ; // elegimos un numero entre 2 y 12
        printf("\n\tEl jugador se movio %d lugares. ", dado); // imprimimos el mensaje de movimientos a ser realizados
    getch();
    system("clear");
    return(dado); // retornamos el valor del dado para poder sumar a nuestro contador
}

int dados1() // la misma funcion que la anterior solo que el numero varia de 1 a 6 por ser de un solo dado
{
    int dado1=0;
    	system("clear");
    	srand(time(NULL));
    	dado1= 1+rand()%6;
    	printf("\n\tEl jugador se movio %d lugares", dado1);
        getch();
    return(dado1);
}

int dados2() // Dado utilizado para salir de la carcel
{
    int dado2=0;
    	system("clear");
    	srand(time(NULL));
    	dado2= 2+rand()%11 ;
    return(dado2);
}
