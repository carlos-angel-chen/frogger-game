/***************************************************************************//**
  @file     +rpi_funs.h+
  @brief    +header de rpi_funs.c+
  @author   +Integrantes del grupo+
 ******************************************************************************/

#ifndef _RPI_FUNS_H_
#define _RPI_FUNS_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "disdrv.h"
#include "joydrv.h"
#include "termlib.h"
#include "obj.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define RPI 1
#define SPEED 1

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
 * @brief INITAGUA: enciende los LEDs de agua (filas 2 a 8)
*/
void init_agua(void); 

/**
 * @brief INITCHARCOSRPI: apaga los LEDs de los charcos y define el arreglo de charcos
 * @param charcos arreglo de charcos
*/
void init_charcos_rpi(charco_t charcos[]);

/**
 * @brief INITOBJ: Define y enciende los autos y troncos correspondientes
 * @param autos arreglo de autos a inicializar
 * @param size_autos tamaño del arreglo de autos
 * @param troncos arreglo de troncos a inicializar
 * @param size_troncos tamaño del arreglo de troncos
 * @param nivel nivel en el que se encuentra el jugador
*/
void init_obj(obj_t autos[], int size_autos, obj_t troncos[], int size_troncos, int nivel);

/**
 * @brief MOVEOBJ: mueve los objetos que se indican (autos o troncos)
 * @param mat arreglo de objetos a mover
 * @param size_mat tamaño del arreglo de objetos
 * @param val D_ON o D_OFF, dependiendo de su es auto o tronco
*/
void move_obj(obj_t mat[], int size_mat, dlevel_t val);

/*******************************************************************************
 ******************************************************************************/

#endif // _RPI_FUNS_H_
