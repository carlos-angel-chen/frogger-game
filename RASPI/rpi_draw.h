/***************************************************************************//**
  @file     +rpi_draw.h+
  @brief    +header de rpi_draw.c+
  @author   +Integrantes del grupo+
 ******************************************************************************/

#ifndef _RPI_DRAW_H_
#define _RPI_DRAW_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdio.h>
#include <unistd.h>     	// Librería que contiene la función sleep, para esperar antes de impirmir otra cosa
#include "disdrv.h"
#include "joydrv.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define MAX_SCORE 4			//Cantidad máxima de cifras que puede mostrar el display de LEDs
#define DEC 10				//Constante utilizada para obtener las cifras individuales de un entero
#define THRESHOLD 100      	//Límite a partir del cual se mueve el LED encendido
#define PLAY 2				//Constante que indica que se decidió jugar/ reanudar el juego
#define EXIT 1				//Constante que indica que se decidió salir del juego o del programa
#define PAUSE 3				//Tiempo a esperar para mostrar símbolos y palabras en el display

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
 * @brief MENU: acceso a las opciones del menú principal y el menú de pausa
 * @param p_opt puntero que apunta a la variable que indica la opción elegida en el menú
 * @param p2fun puntero a funciones que dibujan ciertas opciones para el menú, dependiendo de qué menú se invoca
*/
void menu(char* p_opt, void(*p2fun)(void));

/**
 * @brief VIDASRESTANTES: muestra las vidas restantes de la rana en el display
 * @param cant_vidas cantidad de vidas que le quedan a la rana
*/
void vidas_restantes(int cant_vidas);

/**
 * @brief DRAWSKULL: dibuja una calavera en el display
*/
void draw_skull(void);

/**
 * @brief DRAWOFF: dibuja el simbolo de off en el display
*/
void draw_off(void);

/**
 * @brief DRAWEXIT: dibuja el simbolo de exit en el display
*/
void draw_exit(void);

/**
 * @brief SHOWSCORE: muestra el puntaje en el display
 * @param score puntaje obtenido durante la partida
 * @param highscore puntaje máximo
*/
void show_score(int score, int highscore);


/*******************************************************************************
 ******************************************************************************/

#endif // _RPI_DRAW_H_
