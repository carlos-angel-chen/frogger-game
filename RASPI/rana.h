/***************************************************************************//**
  @file     rana.h
  @brief    Se tiene todos los datos sobre la rana del juego Frogger
  @author   Carlos Angel Chen, Santiago Feldman, Anna Candela Gioia Perez, Tiago Nanni
 ******************************************************************************/

#ifndef _RANA_H_
#define _RANA_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define INIT_X  7           // Posicion de inicio de la rana
#define INIT_Y  15          // Posicion de inicio de la rana
#define FILA_SCORE 10       // Score de cada fila
#define RANA_W 1            // Ancho general de la rana
#define RANA_H 1            // Altura general de la rana
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef struct
{  
    int16_t pos_x;      // Posición en x del vértice de arriba a la izquierda
    int16_t pos_y;      // Posición en y del vértice de arriba a la izquierda
    uint8_t colision;   // Indica si hubo colisión (si está tocando un objeto que la mata)
    uint8_t cant_vida;  // Cantidad de vidas
}rana_t;                // Estructura con atributos de la rana


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief POSRANAINIT: inicializa la rana al comenzar la partida con todos sus atributos
 * @param init_pos estructura de la rana (jugador) 
 * @param pasos cantidad de pixeles que ocupa un casillero del juego. 1: RaspberryPI; 30: Allegro. 
 * @return devuelve la estructura de la rana inicializada
*/
rana_t pos_rana_init(rana_t init_pos, int pasos);

/**
 * @brief RESETRANA: devuelve a la rana a la posicion de partida cuando pasa de nivel o colisiona
 * @param rana estructura de la rana
 * @param pasos pixeles correspondientes a cada output. 1: RaspberryPI; 30: Allegro. 
 * @return devuelve la estructura de la rana con la nueva ubicacion
*/
rana_t reset_rana(rana_t rana, int pasos);

/**
 * @brief MOVIMIENTORANA: mueve al jugador
 * @param tecla indica la direccion en la que se mueve la rana
 * @param posicion estructura de la rana
 * @param pasos pixeles correspondientes a cada output. 1: RaspberryPI; 30: Allegro. 
 * @return devuelve la estructura de la rana con la nueva ubicacion
*/
rana_t movimiento_rana(char tecla, rana_t posicion, int pasos, int *score);

/*******************************************************************************
 ******************************************************************************/

#endif // _RANA_H_
