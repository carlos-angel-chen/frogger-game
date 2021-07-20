/****************************************************************************//**
  @file     +rpi_funs.c+
  @brief    +contiene funciones para el funcionamiento del juego con LEDs+
  @author   +Integrantes del grupo+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "rpi_funs.h"


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
static void se_fue(dcoord_t pos, int16_t width, int state);

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

/*FUNCIÓN INIT_AGUA: enciende los LEDs de agua (filas 2 a 8)*/
void init_agua(void)                                                                         
{                                                                                           
    int i;
    dcoord_t pos_agua;
    pos_agua.x = DISP_MIN;
    pos_agua.y = 2;
    int j; 
    for(i=DISP_MIN; i<=8; i++)       				//filas
    {
        for(j=0; j<=DISP_MAX_X; j++)         		//columnas
        {
            pos_agua.x = j;
            disp_write(pos_agua, D_ON);
        }
        pos_agua.y=i;
    }
}

/*FUNCIÓN INIT_CHARCOS_RPI: apaga los LEDs de los charcos y define el arreglo de charcos*/
void init_charcos_rpi(charco_t charcos[])                                           
{
    int i;
    dcoord_t pos_charco;
    init_charcos(charcos, RPI);                                                         
    pos_charco.y = DISP_MIN+1;						//fila en la que se encuentran los charcos

    for(i=0; i<CANT_CHARCOS; i++)					//marco cada charco en el display
    {
        pos_charco.x = charcos[i].pos;
        disp_write(pos_charco, D_OFF);
    }
}

/*FUNCIÓN INIT_OBJ: Define y enciende los autos y troncos correspondientes*/
void init_obj(obj_t autos[], int size_autos, obj_t troncos[], int size_troncos, int nivel)
{
    int i, j;
    init_autos(autos, RPI, nivel, SPEED);								//inicializa los autos del nivel indicado
    dcoord_t pos_auto;
    for (i = 0; i<size_autos; i++)										//enciende los LEDs de los autos
    {
        pos_auto.x = autos[i].pos_x;
        pos_auto.y = autos[i].pos_y;
        disp_write(pos_auto, D_ON);
        if (autos[i].width > 1)											//el auto ocupa dos casilleros
        {
            ++pos_auto.x;
            disp_write(pos_auto, D_ON);
        }
    }

    init_troncos(troncos, RPI, nivel, SPEED);
    dcoord_t pos_tronco;                                    			//creo la estructura pos_tronco
    for (i = 0; i<size_troncos; i++)
    {
        pos_tronco.x = troncos[i].pos_x-1;                				//doy pos.x a tronco
        pos_tronco.y = troncos[i].pos_y;
        for(j=0; j<troncos[i].width; j++)                    			//recorro el ancho del tronco 2 o 3
        {
            pos_tronco.x++;                                  			//aumento posicion del tronco
            if(pos_tronco.x>=DISP_MIN && pos_tronco.x<=DISP_MAX_X)  	//verifico que el led del tronco este dentro de 0 y 15
            {
                disp_write(pos_tronco, D_OFF);              			//apago el led
            }
        }             
    }
}

/*FUNCIÓN MOVE_OBJ: mueve los objetos que se indican (autos o troncos)*/
void move_obj(obj_t mat[], int size_mat, dlevel_t val)
{
    int i;
    dcoord_t pos_mat;													//posición del objeto que se moverá
    dlevel_t second_val;
    if(val == D_ON)														//variables utiliazdas para encender los LEDs
    {																	//de los autos o apagar los LEDs de los troncos
        second_val = D_OFF;
    }
    else
    {
        second_val = D_ON;
    }

    for(i=0; i<(size_mat); i++)											//muevo el objeto enviado, por su fila
    {
        pos_mat.x = mat[i].pos_x;
        pos_mat.y = mat[i].pos_y;
        se_fue(pos_mat, mat[i].width, val);
        
        mat[i] = movimiento_obj(mat[i], RPI);
        pos_mat.x = mat[i].pos_x;
        se_fue(pos_mat, mat[i].width, second_val);
    }
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/*FUNCIÓN SE_FUE: Chequea si la posición del objeto entra en los parámetros del display.*/
static void se_fue(dcoord_t pos, int16_t width, int state)		//Si no está en los parámetros no debe mostrar nada con respecto a ese objet0
{                                                             	//x=16 ; y=9 ; width=2
    dcoord_t pos2;
    dcoord_t pos3;
    if (pos.y>=0 && pos.y<=15)
    {
        pos2.y = pos.y;
        pos3.y = pos.y;
    }

    if(width==2)
    {
        pos2.x = pos.x + (width-1);                       		//pos2.x = 14

        if(pos.x<=DISP_MAX_X && pos.x>=0)
        {
            disp_write(pos, state);
        }
        if(pos2.x<=DISP_MAX_X && pos2.x>=0)
        {
            disp_write(pos2, state);
        }
    }
    else if(width==3)
    {
        pos2.x = pos.x + (width-1);
        pos3.x = pos.x + (width-2);
 
        if(pos.x<=DISP_MAX_X && pos.x>=0)
        {
            disp_write(pos, state);
        }
         if(pos2.x<=DISP_MAX_X && pos2.x>=0)
        {
            disp_write(pos2, state);
        }
         if(pos3.x<=DISP_MAX_X && pos3.x>=0)
        {
            disp_write(pos3, state);
        }
    }
    else
    {
        if(pos.x<=DISP_MAX_X && pos.x>=0)
        {
            disp_write(pos, state);
        }
    }
}