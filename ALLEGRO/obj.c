/***************************************************************************//**
  @file     obj.c
  @brief    Contiene todos los datos para incializar los objetos/obstáculso del juego frogger
  @author   Carlos Angel Chen, Santiago Feldman, Anna Candela Gioia Perez, Tiago Nanni
 ******************************************************************************/
/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "obj.h"
#define VELOCIDAD 25
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/


// +ej: unsigned int anio_actual;+
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
// +ej: static void falta_envido (int);+
/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+
/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
// +ej: static int temperaturas_actuales[4];+
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************/
/*FUNCIÓN INIT_AUTOS: inicializa los autos dependiendo del nivel*/ 
void init_autos(obj_t autos[], int pasos, uint8_t nivel, int speed)
{
    
   
        if(nivel == 1)
        {
            obj_t auto1 = {pasos, 14*pasos, pasos, 0,VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto2 = {10*pasos, 14*pasos, pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto3 = {15*pasos, 14*pasos, pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto4 = {4*pasos, 13*pasos, pasos, 0,VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto5 = {11*pasos, 13*pasos, pasos, 0,VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto6 = {0, 12*pasos, pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto7 = {6*pasos, 12*pasos, pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto8 = {13*pasos, 12*pasos, pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto9 = {pasos, 11*pasos, 2*pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto10 = {11*pasos, 11*pasos, 2*pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto11 = {5*pasos, 10*pasos, pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto12 = {9*pasos, 10*pasos, pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto13 = {4*pasos, 9*pasos, 2*pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto14 = {13*pasos, 9*pasos, 2*pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            autos[0] = auto1;
            autos[1] = auto2;
            autos[2] = auto3;
            autos[3] = auto4;
            autos[4] =  auto5;
            autos[5] =  auto6;
            autos[6] =  auto7;
            autos[7] = auto8;
            autos[8] =  auto9;
            autos[9] =  auto10;
            autos[10] =  auto11;
            autos[11] =  auto12;
            autos[12] = auto13;
            autos[13] = auto14;
        }
            
        else if (nivel ==2)
        {
            obj_t auto1 = {pasos, 14*pasos, pasos, 0,VELOCIDAD * speed , VELOCIDAD * speed};
            obj_t auto2 = {7*pasos, 14*pasos, pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto3 = {10*pasos, 14*pasos, pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto4 = {15*pasos, 14*pasos, pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto5 = {4*pasos, 13*pasos, pasos, 0,VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto6 = {11*pasos, 13*pasos, pasos, 0,VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto7 = {0, 12*pasos, pasos, 0, VELOCIDAD * speed/2, VELOCIDAD * speed/2};
            obj_t auto8 = {6*pasos, 12*pasos, pasos, 0, VELOCIDAD * speed/2, VELOCIDAD * speed/2};
            obj_t auto9 = {13*pasos, 12*pasos, pasos, 0, VELOCIDAD * speed/2, VELOCIDAD * speed/2};
            obj_t auto10 = {pasos, 11*pasos, 2*pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto11 = {11*pasos, 11*pasos, 2*pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto12 = {15*pasos, 11*pasos, 2*pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto13 = {pasos, 10*pasos, pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto14 = {5*pasos, 10*pasos, pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto15 = {9*pasos, 10*pasos, pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto16 = {15*pasos, 10*pasos, pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto17 = {4*pasos, 9*pasos, 2*pasos, 0, VELOCIDAD * speed/4, VELOCIDAD * speed/4};
         
            autos[0] = auto1;
            autos[1] = auto2;
            autos[2] = auto3;
            autos[3] = auto4;
            autos[4] = auto5;
            autos[5] = auto6;
            autos[6] = auto7;
            autos[7] = auto8;
            autos[8] = auto9;
            autos[9] = auto10;
            autos[10] = auto11;
            autos[11] = auto12;
            autos[12] = auto13;
            autos[13] = auto14;
            autos[14 ]= auto15;
            autos[15] = auto16;
            autos[16] = auto17;
        }
      
            
        else if (nivel == 3)
        {
            obj_t auto1 = {pasos, 14*pasos, pasos, 0,VELOCIDAD * speed/2 , VELOCIDAD * speed/2};
            obj_t auto2 = {7*pasos, 14*pasos, pasos, 0, VELOCIDAD * speed/2, VELOCIDAD * speed/2};
            obj_t auto3 = {10*pasos, 14*pasos, pasos, 0, VELOCIDAD * speed/2, VELOCIDAD * speed/2};
            obj_t auto4 = {15*pasos, 14*pasos, pasos, 0, VELOCIDAD * speed/2, VELOCIDAD * speed/2};
            obj_t auto5 = {4*pasos, 13*pasos, pasos, 0,VELOCIDAD * speed/4, VELOCIDAD * speed/4};
            obj_t auto6 = {11*pasos, 13*pasos, pasos, 0,VELOCIDAD * speed/4, VELOCIDAD * speed/4};
            obj_t auto7 = {0, 12*pasos, pasos, 0, VELOCIDAD * speed/2, VELOCIDAD * speed/2};
            obj_t auto8 = {6*pasos, 12*pasos, pasos, 0, VELOCIDAD * speed/2, VELOCIDAD * speed/2};
            obj_t auto9 = {13*pasos, 12*pasos, pasos, 0, VELOCIDAD * speed/2, VELOCIDAD * speed/2};
            obj_t auto10 = {pasos, 11*pasos, 2*pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto11 = {11*pasos, 11*pasos, 2*pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto12 = {15*pasos, 11*pasos, 2*pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto13 = {pasos, 10*pasos, pasos, 0, VELOCIDAD * speed/3, VELOCIDAD * speed/3};
            obj_t auto14 = {5*pasos, 10*pasos, pasos, 0, VELOCIDAD * speed/3, VELOCIDAD * speed/3};
            obj_t auto15 = {9*pasos, 10*pasos, pasos, 0, VELOCIDAD * speed/3, VELOCIDAD * speed/3};
            obj_t auto16 = {15*pasos, 10*pasos, pasos, 0, VELOCIDAD * speed/3, VELOCIDAD * speed/3};
            obj_t auto17 = {4*pasos, 9*pasos, 2*pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto18 = {8*pasos, 9*pasos, 2*pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t auto19 = {13*pasos, 9*pasos, 2*pasos, 0, VELOCIDAD * speed, VELOCIDAD * speed};
            autos[0] = auto1;
            autos[1] = auto2;
            autos[2] = auto3;
            autos[3] = auto4;
            autos[4] = auto5;
            autos[5] = auto6;
            autos[6] = auto7;
            autos[7] = auto8;
            autos[8] = auto9;
            autos[9] = auto10;
            autos[10] = auto11;
            autos[11] = auto12;
            autos[12] = auto13;
            autos[13] = auto14;
            autos[14] = auto15;
            autos[15] = auto16;
            autos[16] = auto17;
            autos[17] = auto18;
            autos[18] = auto19;
        }
    
}

/*FUNCIÓN INIT_TRONCOS: inicializa los troncos dependiendo del nivel*/ 
void init_troncos(obj_t troncos[], int pasos, uint8_t nivel, int speed)
{
    if (nivel == 1)
    {
            obj_t tronco1 = {2*pasos, 7*pasos, 2*pasos, 1, VELOCIDAD * speed ,VELOCIDAD * speed};
            obj_t tronco2 = {8*pasos, 7*pasos, 2*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco3 = {14*pasos, 7*pasos, 2*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco4 = {pasos, 6*pasos, 2*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco5 = {9*pasos, 6*pasos, 2*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco6 = {12*pasos, 6*pasos, 2*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco7 = {0, 5*pasos, 2*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco8 = {5*pasos, 5*pasos, 2*pasos, 1,VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco9 = {9*pasos, 5*pasos, 2*pasos, 1,VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco10 = {pasos, 4*pasos, 3*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco11 = {9*pasos, 4*pasos, 3*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco12 = {4*pasos, 3*pasos, 2*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco13 = {8*pasos, 3*pasos, 2*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco14 = {12*pasos, 3*pasos, 2*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco15 = {-pasos, 2*pasos, 3*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco16 = {4*pasos, 2*pasos, 3*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco17 = {10*pasos, 2*pasos, 3*pasos, 1,VELOCIDAD * speed, VELOCIDAD * speed};
            troncos[0] = tronco1;
            troncos[1] = tronco2;
            troncos[2] =  tronco3;
            troncos[3] =  tronco4;
            troncos[4] =  tronco5;
            troncos[5] =  tronco6;
            troncos[6] = tronco7;
            troncos[7] =  tronco8;
            troncos[8] =  tronco9;
            troncos[9] =  tronco10;
            troncos[10] =  tronco11;
            troncos[11] =  tronco12;
            troncos[12] = tronco13;
            troncos[13] =  tronco14;
            troncos[14] =  tronco15;
            troncos[15] =  tronco16;
            troncos[16] =  tronco17;
    }
    else if (nivel == 2)
    {
            obj_t tronco1 = {2*pasos, 7*pasos, 2*pasos, 1, VELOCIDAD * speed/2 ,VELOCIDAD * speed/2};
            obj_t tronco2 = {8*pasos, 7*pasos, 2*pasos, 1, VELOCIDAD * speed/2, VELOCIDAD * speed/2};
            obj_t tronco3 = {14*pasos, 7*pasos, 2*pasos, 1, VELOCIDAD * speed/2, VELOCIDAD * speed/2};
            obj_t tronco4 = {2*pasos, 6*pasos, 2*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco5 = {8*pasos, 6*pasos, 2*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco6 = {14*pasos, 5*pasos, 2*pasos, 1, VELOCIDAD * speed/2, VELOCIDAD * speed/2};
            obj_t tronco7 = {1*pasos, 5*pasos, 2*pasos, 1,VELOCIDAD * speed/2, VELOCIDAD * speed/2};
            obj_t tronco8 = {pasos, 4*pasos, 3*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco9 = {13*pasos, 4*pasos, 3*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco10 = {4*pasos, 3*pasos, 2*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco11 = {8*pasos, 3*pasos, 2*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco12 = {12*pasos, 3*pasos, 2*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco13 = {-pasos, 2*pasos, 3*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco14 = {4*pasos, 2*pasos, 3*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco15 = {10*pasos, 2*pasos, 3*pasos, 1,VELOCIDAD * speed, VELOCIDAD * speed};
            troncos[0] = tronco1;
            troncos[1] = tronco2;
            troncos[2] =  tronco3;
            troncos[3] =  tronco4;
            troncos[4] =  tronco5;
            troncos[5] =  tronco6;
            troncos[6] = tronco7;
            troncos[7] =  tronco8;
            troncos[8] =  tronco9;
            troncos[9] =  tronco10;
            troncos[10] =  tronco11;
            troncos[11] =  tronco12;
            troncos[12] = tronco13;
            troncos[13] =  tronco14;
            troncos[14] =  tronco15;
            
    }
    else if (nivel == 3)
    {
            obj_t tronco1 = {2*pasos, 7*pasos, 2*pasos, 1, VELOCIDAD * speed/2 ,VELOCIDAD * speed/2};
            obj_t tronco2 = {8*pasos, 7*pasos, 2*pasos, 1, VELOCIDAD * speed/2, VELOCIDAD * speed/2};
            obj_t tronco3 = {2*pasos, 6*pasos, 2*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco4 = {8*pasos, 6*pasos, 2*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco5 = {14*pasos, 5*pasos, 2*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco6 = {1*pasos, 5*pasos, 2*pasos, 1,VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco7 = {pasos, 4*pasos, 3*pasos, 1, VELOCIDAD * speed/3, VELOCIDAD * speed/3};
            obj_t tronco8 = {9*pasos, 4*pasos, 3*pasos, 1, VELOCIDAD * speed/3, VELOCIDAD * speed/3};
            obj_t tronco9 = {16*pasos, 4*pasos, 3*pasos, 1, VELOCIDAD * speed/3, VELOCIDAD * speed/3};
            obj_t tronco10= {4*pasos, 3*pasos, 2*pasos, 1, VELOCIDAD * speed/4, VELOCIDAD * speed/4};
            obj_t tronco11 = {8*pasos, 3*pasos, 2*pasos, 1, VELOCIDAD * speed/4, VELOCIDAD * speed/4};
            obj_t tronco12= {12*pasos, 3*pasos, 2*pasos, 1, VELOCIDAD * speed/4, VELOCIDAD * speed/4};
            obj_t tronco13 = {-pasos, 2*pasos, 3*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
            obj_t tronco14 = {4*pasos, 2*pasos, 3*pasos, 1, VELOCIDAD * speed, VELOCIDAD * speed};
         
            troncos[0] = tronco1;
            troncos[1] = tronco2;
            troncos[2] =  tronco3;
            troncos[3] =  tronco4;
            troncos[4] =  tronco5;
            troncos[5] =  tronco6;
            troncos[6] = tronco7;
            troncos[7] =  tronco8;
            troncos[8] =  tronco9;
            troncos[9] =  tronco10;
            troncos[10] =  tronco11;
            troncos[11] =  tronco12;
            troncos[12] = tronco13;
            troncos[13] =  tronco14;
            
            
           
    }
   
}

/*FUNCIÓN INIT_CHARCOS: inicializa los charcos */ 
void init_charcos(charco_t charcos[], int pasos)
{
    int i;
    
    for(i=0; i<CANT_CHARCOS; ++i)
    {
    	charcos[i].pos = pasos*POS_CHARCO+i*pasos*DIST;
        charcos[i].filled =  0;
    }
}

/*FUNCIÓN MOVIMIENTO_OBJ: Mueve el objeto dependiendo de su velocidad en el sentido correspondiente*/ 
obj_t movimiento_obj(obj_t objeto, int pasos)
{
    -- objeto.speed;

    if( objeto.speed <= 0 )
    {
        if( ((objeto.pos_y)/pasos) % 2 == 0 )           // El objeto se mueve de izquierda a derecha
        {
            if(objeto.pos_x == 16*pasos)                // El objeto llega al final de la calle. Reaparece del otro lado
            {
                objeto.pos_x = -3*pasos;
            }
            else                                        //El objeto avanza
            {
                objeto.pos_x+=pasos;
               
            }
            
            objeto.speed = objeto.original_speed;       //Resetea la velocidad
        }
        else                                            //El objeto se mueve de derecha a izquierda
        {
            if(objeto.pos_x == -3*pasos)               //El objeto llega al final de la calle. Reaparece del otro lado
            {
                objeto.pos_x = 16*pasos;
            }
            else                                       //El objeto avanza
            {
                objeto.pos_x-=pasos;   
                
                		
            }

            objeto.speed = objeto.original_speed;    //Resetea la velocidad
        }
    }

    return objeto; //Devuelve el objeto actualizado
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
