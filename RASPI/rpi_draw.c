/***************************************************************************//**
  @file     +rpi_draw.c+
  @brief    +funciones que encienden grandes bloques de LEDs+
  @author   +Integrantes del grupo+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "rpi_draw.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void draw_play(void);
static void draw_heart(dcoord_t start);
static void draw_cifras(char arr[], int score, dcoord_t start, char altura_y);
static void draw_num_vida(int vida);
static void draw_num(char num, dcoord_t start);
static void draw_top(dcoord_t start);
static void draw_score(dcoord_t start);


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/*FUNCIÓN MENÚ: acceso a las opciones del menú principal y el menú de pausa*/
void menu(char* p_opt, void(*p2fun)(void))
{
    dcoord_t pos = {DISP_MAX_X>>1 , DISP_MAX_Y>>1};         	//pos es la posición actual, empieza en el centro de la matriz
    dcoord_t npos = pos;                                    	//npos es la próxima posición
    jcoord_t coord = {0,0};                                 	//coordenadas medidas del joystick
    draw_play();
    int option_flag=PLAY;                                   	//flag que indica en la opcion del menu en que estas

    while(*p_opt == 0)
    {   
        joy_update();                                       	//Mide las coordenadas del joystick
        coord = joy_get_coord();                            	//Guarda las coordenadas medidas
        if((coord.x > THRESHOLD) && (npos.x <= DISP_MAX_X))   	//Establece la próxima posición 
        {
            disp_clear();
            p2fun();
            option_flag = EXIT;
        }
        if((coord.x < -THRESHOLD) && (npos.x > DISP_MIN))   	//según las coordenadas medidas
        {
            disp_clear();
            draw_play();
            option_flag = PLAY;
        }

        switch (option_flag)
        {
            case PLAY:
            {
                if(joy_get_switch()!=J_NOPRESS)
                {
                    *p_opt=PLAY;            					//se apretó el botón para jugar
                }
                break;
            }
            case EXIT:
            {
                if(joy_get_switch()!=J_NOPRESS)
                {
                    *p_opt=EXIT;           						//se apretó el botón de apagar/salir
                }
                break;
            }
            default:
                break;
        }
                                        
    }
}

/*FUNCIÓN VIDAS_RESTANTES: muestra las vidas restantes de la rana en el display*/
void vidas_restantes(int cant_vidas)
{
    disp_clear();
    dcoord_t coord = {5,1};                         			// posición en donde comienza el corazón
    draw_heart(coord);                                       	// enciendo el corazón que representa las vidas
    draw_num_vida(cant_vidas);									// muestro la cantidad de vidas que le quedan a la rana
    sleep(PAUSE);
    disp_clear();
}

/*FUNCIÓN DRAW_SKULL: dibuja una calavera en el display*/
void draw_skull(void)
{
    int f, c;
    dcoord_t pos;

    disp_clear();
    
    for(f=0; f<16; f++)
    {
        pos.x = c;
        pos.y = f;
        if (f==0 || f==1 || f==14 || f==15)                             //dibujo los detalles de las esquinas
        {
            for (c=1; c<15; c++)
            {
                if (c==1 || c==2 || c==13 || c==14)
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_ON);
                }

            }    
        }
        if(f==1 || f==2 || f==13 || f==14)
        {
            for(c=2; c<14; c++)
            {
                if(f==1 && (c==3 || c==12))
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_ON);
                }
                if (f==2 && (c==2 || c==13))
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_ON);
                }
                if(f==14 && (c==3 || c==12))
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_ON);
                }
                if (f==13 && (c==2 || c==13))
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_ON);
                }
            }
        }

        if(f>=2 && f<=11)                                           //dibujo la calavera y sus detalles
        {
            for(c=3; c<13; c++)
            {
                pos.x=c;
                pos.y=f;
                disp_write(pos, D_ON);
            }
            if (f>=2 && f<=3)
            {
                for(c=3; c<13; c++)
                {
                    if(f==2 && (c==4 || c==3 || c==11 || c==12))
                    {
                        pos.x=c;
                        pos.y=f;
                        disp_write(pos, D_OFF);
                    }
                    if (f==3 &&(c==3 || c==12))
                    {
                        pos.x=c;
                        pos.y=f;
                        disp_write(pos, D_OFF);
                    }
                }
            }
            if(f==10)                                               //dibujo los detalles de la nariz
            {
                for (c=3; c<13; c++)
                {
                    if(c==3 || c==7 || c==8 || c==12)
                    {
                        pos.x=c;
                        pos.y=f;
                        disp_write(pos, D_OFF);
                    }
                }
            }
            if(f>=6 && f<=8)                                        //dibujo detalles de los ojos
            {
                for (c=4; c<12; c++)
                {
                    if(f==6 && (c==5 || c==6 || c==9 || c==10))
                    {
                        pos.x=c;
                        pos.y=f;
                        disp_write(pos, D_OFF);
                    }
                    if(f==7 && (c==4 || c==5 || c==6 || c==9 || c==10 || c==11))
                    {
                        pos.x=c;
                        pos.y=f;
                        disp_write(pos, D_OFF);
                    }
                    if(f==8 && (c==5 || c==10))
                    {
                        pos.x=c;
                        pos.y=f;
                        disp_write(pos, D_OFF);
                    }
                }
            }   
        }
        if(f>=12 && f<=13)
        {
            for(c=4; c<=11; c++)
            {
                if(f==12 && (c==4 || c==5 || c==7 || c==8 || c==10 || c==11))
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_ON);
                }
                if(f==13 && (c==5 || c==7 || c==8 || c==10))
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_ON);
                }
            }
        }
    }

    disp_update();
    sleep(PAUSE);
    disp_clear();
}

/*FUNCIÓN DRAW_OFF: dibuja el simbolo de off en el display*/
void draw_off(void)
{
    disp_clear();

    dcoord_t pos;
    int f, c;
    for(f=4, c=7; f<=8; f++)					//dibujo la línea del medio
    {
        pos.x = c;
        pos.y = f;
        disp_write(pos, D_ON);
    }
    for (c=3; c<=11; c++)						//dibujo los laterales del círculo
    {
        for(f=6; f<=9; f++)
        {
            if(c==3 || c==11)
            {
                pos.x = c;
                pos.y = f;
                disp_write(pos, D_ON);
            }
        }
    }

    pos.x = 4;									//dibujo la parte superior del círculo
    pos.y = 5;
    disp_write(pos, D_ON);
    pos.x = 10;
    disp_write(pos, D_ON);

    pos.x = 4;									//dibujo la parte inferior del círculo
    pos.y = 10;
    disp_write(pos, D_ON);
    pos.x = 10;
    disp_write(pos, D_ON);
    pos.y = 11;
    for(c=5; c<=9; c++)
    {
        pos.x = c;
        disp_write(pos, D_ON);
    }

    disp_update();
}

/*FUNCIÓN DRAW_EXIT: dibuja el simbolo de exit en el display*/
void draw_exit(void)
{
    disp_clear();
    dcoord_t pos;
    int f,c;
    
    //dibujo flecha
    pos.y=7;									//dibujo la línea horizontal de la flecha
    for(c=3; c<=8; c++)
    {
        pos.x = c;
        disp_write(pos, D_ON);
    }

    pos.x = 6;									//dibujo la punta de la flecha
    pos.y = 5;
    disp_write(pos, D_ON);
    pos.y = 9;
    disp_write(pos, D_ON);
    pos.x = 7;
    pos.y = 6;
    disp_write(pos, D_ON);
    pos.y = 8;
    disp_write(pos, D_ON);

    //dibujo el cuadro
    pos.x = 5;									//dibujo la parte lateral izquierda de la puerta
    pos.y = 3;
    disp_write(pos, D_ON);
    pos.y = 11;
    disp_write(pos, D_ON);

    for(f=2; f<=12; f++)						//dibujo las partes superior e inferior de la puerta
    {
        if(f==2 || f==12)
        {
            for(c=5; c<=12; c++)
            {
                pos.x = c;
                pos.y = f;
                disp_write(pos, D_ON);
            }
        }
    }

    pos.x = 12;									//dibujo el costado restante de la puerta
    for(c=2; c<=12; c++)
    {
        pos.y=c;
        disp_write(pos, D_ON);
    }

    disp_update();
}

/*FUNCIÓN SHOW_SCORE: muestra el puntaje en el display*/
void show_score(int score, int highscore)
{
    disp_clear();
    char arr[MAX_SCORE] = {DEC,DEC,DEC,DEC};
    dcoord_t start = {0,0};
    draw_score(start);                        	//dibujo la palabra "score"
    draw_cifras(arr, score, start, 6);       	//dibujo el puntaje obtenido en la partida, cifra por cifra

    disp_update();
    sleep(PAUSE);
    disp_clear();

    start.x=0;
    start.y=0;
    draw_top(start);                  			//dibujo la palabra "top"
    start.y+=5;
    draw_score(start);                  		//dibujo la palabra score
    draw_cifras(arr, highscore, start, 11); 	//dibujo el puntaje máximo

    disp_update();
    sleep(PAUSE);
    disp_clear();
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/*FUNCIÓN DRAW_PLAY: dibuja el simbolo de play en el display*/
static void draw_play(void)
{
    disp_clear();
    dcoord_t pos;
    int fila = 12;								//fila y columna del borde inferior derecho
    int col = 9;								//del bloque del símbolo
    int f, c;
    int counter=3;

    while(fila>7)								//dibujo el símbolo de play
    {
        for (c=5; c<=col; c++)
        {
            for(f=counter; f<=fila; f++)
            {
                pos.x = c;
                pos.y = f;
                disp_write(pos, D_ON);
            }
            fila--;
            counter++;
        }
    }
    
    disp_update();
}

/*FUNCIÓN DRAW HEART: dibuja un corazón en el display*/
static void draw_heart(dcoord_t start)                     		    	// start son las coordenadas del primer LED encendido del corazón 
{                                                              			// (ej: en el bloque arriba a la izquierda, pos_inicial={2,0})
    dcoord_t now = start;                                     			// posición actual

    for(now = start; now.x <= (start.x+5) ; ++now.x)          			// Este ciclo prende los LEDs de 
    {                                                          			// la primera fila del corazón
        if(now.x == start.x+2) 
        {
            now.x += 2;
        }
        disp_write(now, D_ON);
    }

    for(now.y = start.y+1; now.y <= (start.y+4); ++now.y)    			// Este ciclo prende los LEDs de
    {                                                           		// las siguientes tres filas en el corazón
        for(now.x = start.x-1; now.x <= (start.x+6); ++now.x)
        {
            disp_write(now, D_ON);
        }
    }

    int shrink;
    now.y = start.y+5;                                     				// Sigo a la siguiente fila
    for(shrink=0;shrink < 3; ++shrink, ++now.y)
    {
        for(now.x=start.x+shrink; now.x <= start.x-shrink+5; ++now.x)	// Prendo los LEDs restantes
        {
            disp_write(now, D_ON);
        }
    }

    disp_update();
}

/*FUNCIÓN DRAW_CIFRAS: dibuja las cifras del puntaje obtenido*/
static void draw_cifras(char arr[], int score, dcoord_t start, char altura_y)
{   //hay un bug: si pasas los 9999 puntos, rompes todo. De todos modos, es muy difícil llegar a +9999. Reminiscente del error 256 de PacMan
    int i;
    int cifra;
    //, score!=0
    for(i=1; i<=MAX_SCORE; i++)   				//obtengo el puntaje pedido, cifra por cifra
    {
        cifra = score%DEC;
        score /= DEC;
        arr[MAX_SCORE-i]=cifra;
    }

    start.y=altura_y;
    for(i=0; i<MAX_SCORE; i++)              	//muestra los números en pantalla
    {
        start.x=4*i;
        if(arr[i]!=10) 
        {
            draw_num(arr[i], start);
        }
    }
}

/*FUNCIÓN DRAW_NUM_VIDA: dibuja el número correspondiente a las vidas restantes en el display*/
static void draw_num_vida(int vida)
{                                             	//X comienza en x=5 ; y=11
    dcoord_t now;                                   
    int i,j;
    for(i=5; i<8; i++)                       	//columnas
    {
        for(j=11; j<14; j++)                	//filas
        {
            now.x=i;
            now.y=j;
            if(i%2==1 && j%2==1)
            {
                disp_write(now, D_ON);
            }
            else if(j==12 && i==6)
            {
                disp_write(now, D_ON);
            }
        }
    }
                                              
    int f, c; 
    now.x = 9;                              	//comienta x=9 ; y=10
    now.y = 10;

    if(vida==1)									//dibujo el nro 1
    {
        for(f=10; f<15; f++)
        {
            now.y=f;
            for(c=9; c<11; c++)
            {
                now.x=c;
                if(c==9 && f==11)
                {

                    disp_write(now, D_ON);
                }
            }
            disp_write(now, D_ON);
        }
    }
    else if(vida==2)							//dibujo el nro 2
    {
        for(f=10; f<15; f++)
        {
            now.y=f;
            for(c=9; c<11; c++)
            {
                now.x=c;
                disp_write(now, D_ON);
            }
            disp_write(now,D_ON);
        }
        now.x = 9;
        now.y = 11;
        disp_write(now, D_OFF);
        now.x = 10;
        now.y = 13;
        disp_write(now, D_OFF);
    }
    else										//dibujo el nro 3
    {
        for(f=10; f<15; f++)
        {
            now.y=f;
            for(c=9; c<11; c++)
            {
                now.x=c;
                disp_write(now, D_ON);
            }
            disp_write(now,D_ON);
        }
        now.x = 9;
        now.y = 11;
        disp_write(now, D_OFF);
        now.x = 9;
        now.y = 13;
        disp_write(now, D_OFF);
    }
    disp_update();
}

/*FUNCIÓN DRAW_NUM: dibuja el número correspondiente en el display*/
static void draw_num(char num, dcoord_t start)
{
    int f,c;
    int col=3, fil=5;
    dcoord_t pos;
    pos.x = start.x;
    pos.y = start.y;

    if(num == 0)								//dibujo el nro 0
    {
        for(c=start.x; c<(start.x+col); c++)
        {
            for(f=start.y; f<(start.y+fil); f++)
            {
                pos.x=c;
                pos.y=f;
                disp_write(pos, D_ON);
            }
        }

        for(c=start.x; c<(start.x+col); c++)
        {
            for(f=start.y; f<(start.y+fil); f++)
            {
                if( c==(start.x+1) && (f==start.y+1 || f==start.y+2 || f==start.y+3) )
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_OFF);
                }   
            }
        }
    }
    else if(num == 1)							//dibujo el nro 1
    {
        pos.x = start.x+1;
        for(f=start.y; f<start.y+fil; f++)
        {
            pos.y = f;
            disp_write(pos, D_ON);
        }
        
        pos.x = start.x;
        pos.y = start.y +1;
        disp_write(pos, D_ON);

        pos.y = start.y + fil-1;
        for(c=start.x; c<start.x+col; c++)
        {
            pos.x = c;
            disp_write(pos, D_ON);
        }
    }
    else if(num == 2)							//dibujo el nro 2
    {
        for(c=start.x; c<(start.x+col); c++)
        {
            for(f=start.y; f<(start.y+fil); f++)
            {
                pos.x=c;
                pos.y=f;
                disp_write(pos, D_ON);
            }
        }
        for(c=start.x; c<(start.x+col); c++)
        {
            for(f=start.y; f<(start.y+fil); f++)
            {
                if((f==start.y+1) && ((c==start.x) || (c==start.x+col-2)))
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_OFF);
                }
                if ((f==start.y+fil-2) && ((c==start.x+1) || (c==start.x+col-1)))
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_OFF);
                }
            }
        }

    }
    else if(num == 3)							//dibujo el nro 3
    {
        for(c=start.x; c<(start.x+col); c++)
        {
            for(f=start.y; f<(start.y+fil); f++)
            {
                pos.x=c;
                pos.y=f;
                disp_write(pos, D_ON);
            }
        }
        for(c=start.x; c<(start.x+col); c++)
        {
            for(f=start.y; f<(start.y+fil); f++)
            {
                if((f==start.y+1) && ((c==start.x) || (c==start.x+col-2)))
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_OFF);
                }
                if ((f==start.y+fil-2) && ((c==start.x) || (c==start.x+col-2)))
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_OFF);
                }
            }
        }
    }
    else if(num == 4)							//dibujo el nro 4
    {
        pos.x = start.x + col - 1;
        for(f=start.y; f<start.y+fil; f++)
        {
            pos.y = f;
            disp_write(pos, D_ON);
        }

        pos.x = start.x;
        for(f=start.y; f<start.y+fil-2; f++)
        {
            pos.y = f;
            disp_write(pos, D_ON);
        }

        pos.x = start.x+1;
        pos.y = start.y+2;
        disp_write(pos, D_ON);
    }
    else if(num == 5)							//dibujo el nro 5
    {
        for(c=start.x; c<(start.x+col); c++)
        {
            for(f=start.y; f<(start.y+fil); f++)
            {
                pos.x=c;
                pos.y=f;
                disp_write(pos, D_ON);
            }
        }
        for(c=start.x; c<(start.x+col); c++)
        {
            for(f=start.y; f<(start.y+fil); f++)
            {
                if((f==start.y+fil-2) && ((c==start.x) || (c==start.x+col-2)))
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_OFF);
                }
                if ((f==start.y+1) && ((c==start.x+1) || (c==start.x+col-1)))
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_OFF);
                }
            }
        }
    }
    else if(num == 6)							//dibujo el nro 6
    {
        for(c=start.x; c<(start.x+col); c++)
        {
            for(f=start.y; f<(start.y+fil); f++)
            {
                pos.x=c;
                pos.y=f;
                disp_write(pos, D_ON);
            }
        }
        for(c=start.x; c<(start.x+col); c++)
        {
            for(f=start.y; f<(start.y+fil); f++)
            {
                if((f==start.y+fil-2) && ((c==start.x+col-2)))
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_OFF);
                }
                if ((f==start.y+1) && ((c==start.x+1) || (c==start.x+col-1)))
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_OFF);
                }
            }
        }
    }
    else if(num == 7)							//dibujo el nro 7
    {   
        pos.y = start.y;
        for(c=start.x; c<start.x+col; c++)
        {
            pos.x = c;
            disp_write(pos, D_ON);
        }

        pos.x = start.x + col - 1;
        for(f=start.y; f<start.y+fil; f++)
        {
            pos.y = f;
            disp_write(pos, D_ON);
        }
    }
    else if(num == 8)							//dibujo el nro 8
    {
        for(c=start.x; c<(start.x+col); c++)
        {
            for(f=start.y; f<(start.y+fil); f++)
            {
                pos.x=c;
                pos.y=f;
                disp_write(pos, D_ON);
            }
        }
        for(c=start.x; c<(start.x+col); c++)
        {
            for(f=start.y; f<(start.y+fil); f++)
            {
                if((f==start.y+1) && ((c==start.x+1)))
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_OFF);
                }
                if ((f==start.y+fil-2) && ((c==start.x+1)))
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_OFF);
                }
            }
        }
    }
    else if(num == 9)							//dibujo el nro 9
    {
        for(c=start.x; c<(start.x+col); c++)
        {
            for(f=start.y; f<(start.y+fil); f++)
            {
                pos.x=c;
                pos.y=f;
                disp_write(pos, D_ON);
            }
        }
        for(c=start.x; c<(start.x+col); c++)
        {
            for(f=start.y; f<(start.y+fil); f++)
            {
                if((f==start.y+1) && ((c==start.x+1)))
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_OFF);
                }
                if ((f==start.y+fil-1) && ((c==start.x) || (c==start.x+1)))
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_OFF);
                }
                if ((f==start.y+fil-2) && ((c==start.x) || (c==start.x+1)))
                {
                    pos.x=c;
                    pos.y=f;
                    disp_write(pos, D_OFF);
                }
            }
        }
    }
    disp_update();
}

/*FUNCIÓN DRAW_TOP: dibuja la palabra "TOP" a partir de la ubicación enviada*/
static void draw_top(dcoord_t start)
{
    int f,c;
    dcoord_t pos;

    pos.y = start.y;								//dibujo la T
    for(c=start.x; c<start.x+3; c++)
    {
        pos.x = c;
        disp_write(pos, D_ON);
    }
    pos.x = start.x+1;
    for (f=start.y; f<start.y+4; f++)
    {
        pos.y=f;
        disp_write(pos, D_ON);
    }

    for(c=start.x+4; c<start.x+7; c++)				//dibujo la O
    {
        for(f=start.y; f<start.y+4; f++)
        {
            pos.x = c;
            pos.y = f;
            disp_write(pos, D_ON);
        }
    }
    
    pos.x = start.x + 5;
    for (f=start.y+1; f<start.y+3; f++)
    {
        pos.y = f;
        disp_write(pos, D_OFF);
    }
    
    for(c=start.x+8; c<start.x+11; c++)				//dibujo la P
    {
        for(f=start.y; f<start.y+4; f++)
        {
            pos.x = c;
            pos.y = f;
            disp_write(pos, D_ON);
        }
    }
    pos.x = start.x +9;
    pos.y = start.y +1;
    disp_write(pos, D_OFF);
    pos.x = start.x +9;
    pos.y = start.y +3;
    disp_write(pos, D_OFF);
    pos.x = start.x +10;
    pos.y = start.y +3;
    disp_write(pos, D_OFF);
    
    disp_update();
}

/*FUNCIÓN DRAW_SCORE: dibuja la palabra "SCORE" a partir de la ubicación enviada*/
static void draw_score(dcoord_t start)
{
    int f,c;
    dcoord_t pos;

    for(c=start.x; c<start.x+2; c++)				//dibujo la S
    {
        for(f=start.y; f<start.y+5; f++)
        {
            pos.x=c;
            pos.y=f;
            disp_write(pos, D_ON);
        }
    }
    pos.x=start.x+1;
    pos.y=start.y+1;
    disp_write(pos, D_OFF);
    pos.x=start.x;
    pos.y=start.y+3;
    disp_write(pos, D_OFF);

    for(c=start.x+3; c<start.x+5; c++)				//dibujo la C
    {
        for(f=start.y; f<start.y+5; f++)
        {
            pos.x=c;
            pos.y=f;
            disp_write(pos, D_ON);
        }
    }
    pos.x = start.x+4;
    for(f=start.y+1; f<start.y+4; f++)
    {
        pos.y=f;
        disp_write(pos, D_OFF);
    }

    for(c=start.x+6; c<start.x+9; c++)				//dibujo la O
    {
        for(f=start.y; f<start.y+5; f++)
        {
            pos.x=c;
            pos.y=f;
            disp_write(pos, D_ON);
        }
    }
    pos.x = start.x+7;
    for(f=start.y+1; f<start.y+4; f++)
    {
        pos.y=f;
        disp_write(pos, D_OFF);
    }

    for(c=start.x+10; c<start.x+13; c++)			//dibujo la R
    {
        for(f=start.y; f<start.y+5; f++)
        {
            pos.x=c;
            pos.y=f;
            disp_write(pos, D_ON);
        }
    }
    pos.x = start.x+11;
    pos.y = start.y+1;
    disp_write(pos, D_OFF);
    pos.x = start.x+12;
    pos.y = start.y+3;
    disp_write(pos, D_OFF);
    pos.x = start.x+11;
    pos.y = start.y+4;
    disp_write(pos, D_OFF);

    for(c=start.x+14; c<start.x+16; c++)			//dibujo la E
    {
        for(f=start.y; f<start.y+5; f++)
        {
            pos.x=c;
            pos.y=f;
            disp_write(pos, D_ON);
        }
    }
    pos.x = start.x+15;
    pos.y = start.y+1;
    disp_write(pos, D_OFF);
    pos.x = start.x+15;
    pos.y = start.y+3;
    disp_write(pos, D_OFF);

    disp_update();
}