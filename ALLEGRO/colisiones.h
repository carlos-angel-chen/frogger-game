/***************************************************************************//**
  @file     colisiones.h
  @brief    Se tiene todas las funciones para analizar las colisiones en el juego
  @author   Carlos Angel Chen, Santiago Feldman, Anna Candela Gioia Perez, Tiago Nanni
 ******************************************************************************/

#ifndef _COLISIONES_H_
#define _COLISIONES_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "rana.h"
#include "obj.h"
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define CHARCO_SCORE  100   //Score por charco
#define ASCII 0x30 
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief COLISION: Analiza la colisión de la rana con todos los objetos
 * @param rana estructura de la rana
 * @param pasos RaspberryPI: 1; Allegro: 30
 * @param autos[] arreglo de autos
 * @param troncos[] arreglo de troncos
 * @param cant_au cantidad de autos
 * @param cant_tl cantidad de troncos
 * @return devuelve la estructura de la rana
*/
rana_t colision (rana_t rana, int pasos, obj_t autos[], obj_t troncos[], int cant_au, int cant_tl);
/**
 * @brief CHECK_CHARCOS: Analiza si la rana llegó a un charco o no
 * @param rana estructura de la rana
 * @param charcos[] arreglo de autos
 * @param pasos RaspberryPI: 1; Allegro: 30
 * @param nivel nivel del juego
 * @param score puntero al score acumulado
 * @return devuelve la estructura de la rana
*/
rana_t check_charcos(rana_t rana, charco_t charcos[], int pasos, int* nivel, int *score);

/**
 * @brief HIGHSCORE_CHECK: Analiza si la rana llegó a un charco o no
 * @param score Recibe el score del jugador en la partida 
 * @return devuelve la estructura de la rana
*/

int highscore_check (int score);
/*******************************************************************************
 ******************************************************************************/

#endif // _COLISIONES_H_
