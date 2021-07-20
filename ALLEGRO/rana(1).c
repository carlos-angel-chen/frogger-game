/***************************************************************************//**
  @file     rana.c
  @brief    Contiene todas las funciones para inicializar y mover la rana del juego frogger
  @author   Carlos Angel Chen, Santiago Feldman, Anna Candela Gioia Perez, Tiago Nanni
 ******************************************************************************/
/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "rana.h"

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
/* FUNCIÓN POS_RANA_INIT: inicializa la rana con los parámetros iniciales*/ 
rana_t pos_rana_init(rana_t init_pos, int pasos)
{

	init_pos.pos_x = INIT_X * pasos;
	init_pos.pos_y = INIT_Y * pasos;
	init_pos.colision = 0;
	init_pos.cant_vida = 3;


	return init_pos;
}
/* FUNCIÓN RESET_RANA: resetea la posición de la rana a la posición inicial*/ 
rana_t reset_rana(rana_t rana, int pasos)
{
    rana.pos_x = INIT_X*pasos;
    rana.pos_y = INIT_Y*pasos;
    return rana;
}
/* FUNCIÓN MOVIMIENTO_RANA: dependiendo de lo ingresado por teclado, actualiza la posición de la rana */ 
rana_t movimiento_rana(char tecla, rana_t posicion, int pasos, int *score)
{

	if (tecla == 'U')	
	{
		if(posicion.pos_y!=0)							//Si la rana está en el borde, no se mueve
		{
			posicion.pos_y = posicion.pos_y - pasos;			//La rana se mueve un casillero para arriba
			*score += FILA_SCORE;                                           //Se aumenta el puntaje por pasar a la siguiente fila
		}
	}
	else if (tecla == 'D')
	{
		if(posicion.pos_y != 15*pasos) 						//Si la rana está en el borde, no se mueve
		{
			posicion.pos_y = posicion.pos_y + pasos;			//La rana se mueve un casillero para abajo
			*score -= FILA_SCORE;						//Se disminuye el puntaje por pasar a la anterior fila
		}
	}
	else if (tecla == 'L')
	{
		if (posicion.pos_x != 0) 						//Si la rana está en el borde, no se mueve
		{
			posicion.pos_x = posicion.pos_x - pasos;			//La rana se mueve un casillero a la izquierda
		}
	}
	else if (tecla == 'R')
	{
		if(posicion.pos_x != 15*pasos) 						//Si la rana está en el borde, no se mueve
		{
			posicion.pos_x = posicion.pos_x + pasos;			//La rana se mueve un casillero a la derecha
		}
	}

	return posicion; //Devuelve la rana actualizada
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
