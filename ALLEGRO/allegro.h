/***************************************************************************//**
  @file     allegro.h
  @brief    Contiene todos los datos y funciones para poder dibujar en el front si se utiliza allegro
  @author   Carlos Angel Chen, Santiago Feldman, Anna Candela Gioia Perez, Tiago Nanni
 ******************************************************************************/

#ifndef _ALLEGRO_H_
#define _ALLEGRO_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "colisiones.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_ttf.h> 



/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
*******************************************************************************/
#define PASOS 30
#define WIDTH 16
#define HEIGHT 16
#define FPS 7.0
#define OFF 0
#define ON 1
#define AGAIN 2
#define DEATH 10
#define WIN_CHARCO 1

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT,KEY_ENTER, KEY_P //arrow keys
};

typedef struct
{
    ALLEGRO_DISPLAY*display;            // puntero a display
    ALLEGRO_EVENT_QUEUE *event_queue;   // puntero a eventos
    ALLEGRO_TIMER *timer;               // puntero al timer
    ALLEGRO_BITMAP *objbit_1_au;        // puntero a un auto de longitud 1
    ALLEGRO_BITMAP *objbit_1_au1;       // puntero a un auto de longitud 1 (otra imagen)
    ALLEGRO_BITMAP *objbit_2_au;        // puntero a un auto de longitud 2
    ALLEGRO_BITMAP *objbit_2_tr;        // puntero a un tronco de longitud 2
    ALLEGRO_BITMAP *objbit_3_tr;        // puntero a un tronco de longitud 3
    ALLEGRO_BITMAP *ranabit_x;          // puntero a la rana
    ALLEGRO_BITMAP *ranabit_y;          // puntero a la rana
    ALLEGRO_BITMAP *image_on;           // puntero a la rana
    ALLEGRO_BITMAP *image_off;          // puntero a la rana
    ALLEGRO_BITMAP *image_leave;        // puntero a la rana
    ALLEGRO_FONT *font;                 // puntero a la fuente del texto
    ALLEGRO_BITMAP *death;              // puntero a la imagen del esqueleto de la rana
    ALLEGRO_BITMAP *rana_charco;        // puntero a la imagen de la rana estática en el charco
    ALLEGRO_BITMAP *lives;              // puntero a la imagen de la vidas restantes
    ALLEGRO_SAMPLE* background;         // puntero al sonido del fondo
    ALLEGRO_SAMPLE* hop;                // puntero al sonido de movimiento
    ALLEGRO_SAMPLE* dead;               // puntero al sonido de muerte
    ALLEGRO_EVENT ev;                   // evento
     
}pointers_t;
/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief INIT_POINTERS: Inicializa los pointer de arreglo necesarios
 * @param do_exit Puntero a la variable que indica que se debe terminar el juego 
 * @return No devuelve nada
*/
pointers_t init_pointers (bool *do_exit);


/**
 * @brief DRAW_RANA: Dibuja en el display la rana con su respectivo tamaño, imagen y posición
 * @param display Puntero al display donde se dibuja el objeto
 * @param x Posición en x
 * @param y Posición en y
 * @param direccion Puntero a la variable que indica que imagen debe ponerse
 * @param ranabit_y Puntero al bitmap que tiene la imagen de arriba y de abajo
 * @param ranabit_x Puntero al bitmap que tiene la imagen de izquierda y de derecha
 * @return No devuelve nada
*/
void draw_rana ( float x, float y, int *direccion,ALLEGRO_BITMAP*ranabit_y, ALLEGRO_BITMAP*ranabit_x);

/**
 * @brief DRAW_ALL: Dibuja en el display todos los autos y troncos correspondientes al nivel 
 * @param cantidad_au Cantidad de autos en el nivel
 * @param cantidad_tr Cantidad de troncos en el nivel
 * @param autos[] Arreglo de los autos
 * @param troncos[] Arreglo de los troncos
 * @param bits Estructura que tiene todos los puteros necesarios para arreglo (en este caso se necesita el del display y los de los bitmaps)
 * @return No devuelve nada
*/
void draw_all ( int cantidad_au, int cantidad_tr, obj_t autos[], obj_t troncos[], pointers_t bits);

/**
 * @brief LANDSCAPE: Dibuja en el display el escenario del fondo 
 * @return No devuelve nada
*/
void landscape(void);

/**
 * @brief EV_TECLA: Analiza si se presiono una tecla o no (evento del teclado de allegro)
 * @param state El cambio de estado de cada tecla
 * @param key_pressed[] Arreglo que tiene los estados de cada letra 
 * @param ev Estructura que representa el evento
 * @return No devuelve nada
*/
void ev_tecla(bool state, bool key_pressed[], ALLEGRO_EVENT ev );

/**
 * @brief EV_TIME: Analiza si en cierto tiempo cambio el estado de las teclas (evento del tiempo de allegro) y modifica la posición de la ran
 * @param key_pressed[] Arreglo que tiene los estados de cada letra 
 * @param ev Estructura que representa el evento
 * @param rana Estructura que representa a la rana
 * @param score Puntero al score 
 * @param direccion Puntero a la variable que indica que imagen debe ponerse
 * @param menu_flag Variable que indica si el menú principal está abierto o no
 * @param pause_flag Variable que indica si el menú de pause está abierto o no
 * @param do_exit Puntero a la variable que indica que se debe terminar el juego 
 * @param select Puntero a la variable que indica que opción se está seleccionando en el menú
 * @return Devuelve la estructura de la rana con sus campos actualizados
*/
rana_t ev_time (bool key_pressed[], pointers_t pointers, rana_t rana, int *score, int *direccion,bool *menu_flag, bool *pause_flag, bool *do_exit, int *select);

/**
 * @brief INIT_LEVEL: Inicializa cada nivel 
 * @param nivel Nivel del juego 
 * @param autos[] Arreglo de estructuras de autos 
 * @param troncos[] Arreglo de estructuras de autos 
 * @param rana Estructura de la rana 
 * @return Devuelve la estructura de la rana con sus campos actualizados
*/
rana_t init_level (int nivel,obj_t autos[], obj_t troncos[], rana_t rana);


 
 /**
 * @brief DRAW_MENU: Dibuja las imágenes del menú
 * @param select Variable que indica que opción se está seleccionando en el menú
 * @param pointers Estructura con pointers de allegro 
 * @param menu_flag Flag de menú
 * @return No devuelve nada
*/
 
void draw_menu (int select, pointers_t pointers, bool menu_flag);

 /**
 * @brief DRAW_LEVEL: Le avisa al usuario el nivel del juego
 * @param nivel Nivel en el que se encuentra en jugador
 * @param font Puntero al font del texto
 * @return No devuelve nada
*/
void draw_level(int nivel,  ALLEGRO_FONT* font);
 /**
 * @brief DRAW_LEVEL: Le avisa al usuario la cantidad de vidas restantes
 * @param cant_vida Cantidad de vidas restantes
 * @param font Puntero al font del texto
 * @return No devuelve nada
*/


 /**
 * @brief SHOW_SCORE: Muestra el score de la partida y el highscore
 * @param score Puntaje de la partida
 * @param font Puntero al font del texto
 * @return No devuelve nada
*/
void show_score (int score, ALLEGRO_FONT*font );


 /**
 * @brief DRAW_LIVES: Muestra el score de la partida y el highscore
 * @param cant_vida Cantidad de vidas de la rana 
 * @param x Posición en x del vértice de arriba a la izquierda
 * @param y Posición en y del vértice de arriba a la izquierda
 * @param type Tipo de imagen que se debe mostrar (muerte o rana estática)
 * @param point Puntero a la imagen
 * @param font Puntero a la fuente del texto 
 * @return No devuelve nada
*/

void draw_lives( uint8_t cant_vida,int x, int y, int type, ALLEGRO_BITMAP* point, ALLEGRO_FONT* font );
/*******************************************************************************
 ******************************************************************************/

#endif // _ALLEGRO_H_


