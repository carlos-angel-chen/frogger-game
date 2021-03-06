/***************************************************************************//**
  @file    colisiones.c
  @brief   Contiene todos los datos para detectar colisiones en el juego frogger
  @author  Carlos Angel Chen, Santiago Feldman, Anna Candela Gioia Perez, Tiago Nanni
 ******************************************************************************/
/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "colisiones.h"

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
static rana_t reset_life(rana_t rana, int pasos);
static rana_t check_colision(rana_t rana, obj_t objeto, int pasos);
static rana_t movimiento_rana_tronco(rana_t rana, obj_t objeto , int pasos );

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

/* FUNCI??N COLISION: Se encarga de analizar todo tipo de colisi??n que pueda ocurrir y dependiendo de eso modifica el estado de la rana*/
rana_t colision (rana_t rana, int pasos, obj_t autos[], obj_t troncos[], int cant_au, int cant_tl)
{

	int i;                                              											//??ndice
	int conta_colisiones=0;                             											//Contador de colisiones
	if (rana.pos_y <= 7*pasos && rana.pos_y >= 2*pasos)												//Si la rana se encuentra en la zona superior (parte del agua)
	{
		for (i=0; i<cant_tl; i++)              														//Analiza la colisi??n con todos los troncos
		{
			rana = check_colision(rana, troncos[i], pasos);
			conta_colisiones += rana.colision;  													//Incrementa el contador si la rana no est?? tocando el tronco
                        if (rana.colision == 0 )            										//Si la rana est?? arriba de alg??n tronco
                        {
                          
                             rana = movimiento_rana_tronco( rana,troncos[i], pasos);				//Entonces actualiza el movimiento de la rana para que corresponda con el tronco
                             i = cant_tl;                                      						//Se deja de analizar el resto de los troncos
			
                        }
                        else if (conta_colisiones == cant_tl)                  						//Si no est?? tocando ning??n tronco
                        {

                                rana = reset_life(rana,pasos);                      				//Entonces est?? tocando el agua, muere la rana 
                        }

		}

	}
        else                                                                        				//Si la rana se encuentra en la zona inferior (parte de la calle)
	{
            for (i=0; i<cant_au; i++)                                               				//Analiza la colisi??n con todos los autos
		{
			rana = check_colision(rana, autos[i], pasos); 
			
			if (rana.colision == 1)                                      							//Si la rana choca con un auto
			{
				rana = reset_life(rana,pasos);                      								//Entonces, muere la rana
				i=cant_au;                                              							//Se deja de analizar el resto de los autos
			}
			
			
		} 
	}
	return rana;  																					//Se devuelve la rana actualizada

}

/* FUNCI??N CHECK_CHARCOS: chequea si la rana lleg?? a uno de los charcos. La rana avanza de nivel si los ocup?? a todos; muere si lleg?? a uno ya ocupado
Se actualizan los charcos dentro de la estructura de la rana con la finalidad de que el front pueda representar gr??ficamente cu??les charchos est??n
ocupados */ 
rana_t check_charcos(rana_t rana, charco_t charcos[], int pasos, int* nivel, int *score)
{
	
    static int cant_goals = CANT_CHARCOS;        	    // variable que verifica el numero de charcos que la rana alcanzo dentro de un nivel
    if (rana.cant_vida <= 0)						//Si se muri?? la rana 
    {
    	cant_goals = CANT_CHARCOS;					//Se vuelve a inicializar la variable 
    	init_charcos( charcos, pasos);              //Incializaci??n de los charcos  
    }
    else
    {
		if(rana.pos_y == POS_Y_CHARCO*pasos)                             // la rana llego a la ante??ltima fila del nivel
		{
		    int toca_piso = 1;
			int i;
		    for(i=0; i < CANT_CHARCOS; ++i)
		    {
		        if(rana.pos_x == charcos[i].pos)        // la rana llego a un charco
		        {
		            if(charcos[i].filled == 0)
		            {
		                --cant_goals;    	            // se disminuye la cantidad de charchos a los que la rana necesita llegar para completar el nivel
		                charcos[i].filled = 1;           // el charco al que llego ahora esta ocupado, la rana morira si cae ahi de nuevo
		                toca_piso = 0;
		                rana = reset_rana(rana, pasos);
		                i = CANT_CHARCOS;
		                *score+=CHARCO_SCORE;
		            }
		            else
		            {
		                rana = reset_life(rana, pasos);	// el charcho al que llego estaba ocupado, la rana muere
		                toca_piso = 0;
		            }
		        }
		    }

		    if(toca_piso == 1)                          // la rana no llego a ningun charco y toco el piso
		    {
		        rana = reset_life(rana, pasos);
		    }

			if(cant_goals == 0)                          // la rana llego a todos los charcos del nivel. Pasa al siguiente nivel
			{
					cant_goals = CANT_CHARCOS;                      
					++(*nivel);
					 (*score)+= 2*CHARCO_SCORE ;		//Se aumenta el score por charco
					int j; 
					for(j=0; j< CANT_CHARCOS; ++j)
					{
						charcos[j].filled = 0;			//Se resetean los charcos
					}                       
			 }
		}
    }
	return rana;
}
/* FUNCI??N HIGHSCORE_CHECK: se analiza el highscore, si el nuevo score es mayor a ??ste entonces lo actualiza y devuelve el highscore */ 
int highscore_check (int score)
{
    FILE *highscore_f;

    highscore_f = fopen("highscore.txt","r");			//Se abre el highscore

   	int c = fgetc(highscore_f);
    int ent = 0;

    if(c == EOF)										//Si el primer car??cter es un terminador
    {
        fclose(highscore_f);
        highscore_f = fopen("highscore.txt","w");
        fprintf(highscore_f, "%d", 0); 					//Pone en 0 el highscore
        fclose(highscore_f);
    }
    else												//Si el primer car??cter no es un terminador
    {
        while (c!= EOF)									//Mientras que no encuentra el terminador, pasa los car??cteres y los convierte a un n??mero entero
        {
                ent *= 10;           
                ent += c - ASCII;	 					//Transformaci??n a ascii 
                c = fgetc (highscore_f);	
        }
        fclose(highscore_f);
    }
    if (score > ent )									//Si el score es m??s grande que el highscore
    {
            highscore_f = fopen  ("highscore.txt","w");
            fprintf(highscore_f, "%d", score); 			//Se actualiza el highscore
            fclose(highscore_f);
            ent = score;
    }

    return ent; 										//Devuelve el highscore
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* FUNCI??N RESET_LIFE: Decrementa una vida a la rana y actualiza su posici??n a la posici??n inicial*/ 
static rana_t reset_life(rana_t rana, int pasos)
{
	

	--rana.cant_vida;
	if(rana.cant_vida > 0)
	{
		rana.colision = 0;
		rana = reset_rana ( rana, pasos);
	}

	return rana;
}

/* FUNCI??N CHECK_COLISION: Chequea para cualquier tipo de obst??culo u objeto el contacto de est?? con la rana*/ 
 static rana_t check_colision(rana_t rana, obj_t objeto, int pasos)
{
	
    if(rana.pos_y == objeto.pos_y)                                                      //Si la rana est?? a la misma altura que el objeto
    {

        if( (rana.pos_x >= objeto.pos_x && rana.pos_x <=(objeto.pos_x + objeto.width-1))) //y la rana est?? en el mismo rango de x que el objeto
        {
        	
            if (objeto.type_obj == 0)                                                   //Si el objeto es un auto
            {
               rana.colision = 1;                                                       //Se activa la colisi??n
            }
            if (objeto.type_obj ==1 )                                                    //Si el objeto es un tronco
            {
                rana.colision = 0;                                                      //No se activa la colisi??n
            }

        }
       else if (rana.pos_y <= 7*pasos && rana.pos_y >= 2*pasos)                         //la rana est?? en la zona superior pero no tiene contacto con el tronco
        {
            
            rana.colision = 1;                                                          //Se activa la colisi??n (est?? tocando agua)
    	}
    }
    else if (rana.pos_y <= 7*pasos && rana.pos_y >= 2*pasos)                            //La rana est?? tocandoo agua
    {
    
    	rana.colision = 1;                                                              //Se activa la colisi??n
    }
    
    return rana; //Se devuelve la rana actualizada
}

/* FUNCI??N MOVIMIENTO_RANA_TRONCO: Si la rana se encuentra en un tronco, mueve la rana con ese tronco*/ 
static rana_t movimiento_rana_tronco(rana_t rana, obj_t objeto , int pasos )
{
    --objeto.speed;                             //Decrementa el contador que representa la velocidad    -- objeto.speed;

    if( ((objeto.pos_y)/pasos) % 2 == 0 )       //El objeto se mueve de izquierda a derecha
    {
        if( objeto.speed <= 0 )
        {
            if(rana.pos_x == 15*pasos)          //La rana llega al final de la calle.
            {
                rana = reset_life(rana, pasos); //La rana muere
            }
            else                                //La rana avanza
            {
                rana.pos_x+=pasos;
                 
            }

            objeto.speed = objeto.original_speed; //Se resetea el contador
        }
    }
    else                                         // El objeto se mueve de derecha a izquierda
    {
        if( objeto.speed <= 0)
        {
            if(rana.pos_x == 0)                 //La rana llega al final de la calle
            {
                
                rana = reset_life(rana, pasos); //La rana muere
            }
            else                                // La rana  avanza
            {
                rana.pos_x-=pasos;   
                	
            }

            objeto.speed = objeto.original_speed; //Se resetea el contador
        }
    }
    return rana;  //Se devuelve la rana actualizada
}






