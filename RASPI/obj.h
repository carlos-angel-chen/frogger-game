/***************************************************************************//**
  @file     obj.h
  @brief    Se tiene todo los datos para inicializar los objetos del juego Frogger
  @author   Carlos Angel Chen, Santiago Feldman, Anna Candela Gioia Perez, Tiago Nanni
 ******************************************************************************/

#ifndef _OBJ_H_
#define _OBJ_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define CANT_AUTOS 19           // Cantidad de autos máximos
#define AL1 14                  // Cantidad de autos en el nivel 1
#define AL2 17                  // Cantidad de autos en el nivel 2
#define AL3 19                 // Cantidad de autos en el nivel 3
#define CANT_TRONCOS 17         // Cantidad de troncos máximos
#define TL1 17                  // Cantidad de troncos en el nivel 1
#define TL2 15                 // Cantidad de troncos en el nivel 2
#define TL3 14                  // Cantidad de troncos en el nivel 3
#define CANT_CHARCOS 5          // Cantidad de charcos en los niveles
#define POS_CHARCO	2       // Posición del primer charco en x
#define POS_Y_CHARCO 1          // Posición de los charcos en y
#define DIST 3                  // Distancia entre cada charco

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef struct
{
    int16_t pos_x;          // Posición en x del vértice de arriba a la izquierda
    int16_t pos_y;          // Posición en y del vértice de arriba a la izquierda
    int16_t width;          // Ancho
    uint8_t type_obj;       // 0: auto; 1:tronco
    int speed;              // Contador para controlar la velocidad del objeto
    int original_speed;     // Variable que mantiene el valor original de speed 
} obj_t;                    // Estructura de los autos y de los troncos


typedef struct 
{
    int16_t pos;          //Posición en x del vértice de arriba a la izquierda
    uint8_t filled;       //Indica si la rana ya llegó a ese charco o no
} charco_t;               //Estructura de los charcos 


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief INITAUTOS: inicializa los autos correspondientes a cada nivel
 * @param autos[] Arreglo de autos 
 * @param pasos RaspberryPI: 1; Allegro: 30
 * @param nivel Nivel en el que se encuentra la rana
 * @param speed Velocidad de cada auto
 * @return No devuelve nada
*/
void init_autos(obj_t autos[], int pasos, uint8_t nivel,int speed);

/**
 * @brief INITTRONCOS: inicializa los troncos correspondientes a cada nivel
 * @param troncos[] Arreglo de autos 
 * @param pasos RaspberryPI: 1; Allegro: 30
 * @param nivel Nivel en el que se encuentra la rana
 * @param speed Velocidad de cada tronco
 * @return No devuelve nada
*/
void init_troncos(obj_t troncos[], int pasos, uint8_t nivel, int speed);

/**
 * @brief MOVIMIENTOOBJ: mueve los objetos
 * @param objeto objeto que va a moverse
 * @param pasos RaspberryPI: 1; Allegro: 30
 * @return estructura del objeto con su nueva posicion
*/
obj_t movimiento_obj(obj_t objeto, int pasos);

/**
 * @brief INIT_CHARCOS: inicializa los charcos 
 * @param charcos objeto que va a moverse
 * @param pasos RaspberryPI: 1; Allegro: 30
 * @return no devuelve nada
*/
void init_charcos(charco_t charcos[], int pasos);
/*******************************************************************************
 ******************************************************************************/

#endif // _OBJ_H_
