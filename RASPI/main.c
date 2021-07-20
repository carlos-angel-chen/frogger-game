#include <stdio.h>
#include <stdlib.h>

#ifdef ALLEGRO
#include "allegro.h"
int main(void) 
{
	
    /*VARIABLES*/
    int direccion = 0;                          //Variable que indica la dirección de la imagen 
    int i;                                      //Índice
    int j;                                      //Índice    
    int nivel ;                                 //Variable que indica el nivel
    int *p_nivel = &nivel;                      //Puntero a nivel
    int nivel_aux;                              //Variable auxiliar de nivel 
    int vidas = 0;                              //Variable que analiza las vidas 
    int type;                                   //Variable que indica el tipo de imagen a mostrar
    obj_t autos [CANT_AUTOS];                   //Arreglo de autos
    obj_t troncos [CANT_TRONCOS];               //Arreglo de troncos
    charco_t charcos [CANT_CHARCOS];            //Arreglo de charcos
    bool do_exit = false;                       //Variable que indica si debe cerrarse el display
    bool key_pressed[6] = {false, false, false, false,false,false}; //Estado de teclas, true cuando esta apretada
    bool change_level = false;                  //Variable que indica si se debe cambiar de nivel 
    pointers_t bits;                            //Punteros de allegro
    bits = init_pointers (&do_exit);            //Se completan los punteros 
    int score=0;                                //Variable que indica el score 
    int *score_p = &score;                      //Puntero al score
    bool menu_flag=true;                        //Variable que indica si se debe estar en el menú principal
    bool pause_flag =false;                     //Variable que indica si se debe estar en el menú de pausa
    int select= ON;                             //Variable que indica que opción se tocó en el menú
    change_level = false;                       //Todavía no se tiene que cambiar de nivel 
    rana_t rana;                                //Rana
    rana =  pos_rana_init(rana, PASOS);    //Inicialización de la rana
    vidas = rana.cant_vida;
    /*INICIALIZACIÓN*/
    
    

    al_play_sample(bits.background, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
    /*JUEGO*/
    while (!do_exit)                                //Mientras que no se haya cerrado el display o se haya terminado el juego
    {
        init_charcos( charcos, PASOS);              //Incialización de los charcos  
        if (change_level==false)
        {        
        	rana =  pos_rana_init(rana, PASOS);    	//Inicialización de la rana
        }
        while (menu_flag)                           //Mientras que no se haya elegido una opción del menú principal
        {
        	
            nivel = 1;
            if (al_get_next_event(bits.event_queue, &bits.ev))      //Toma un evento de la cola
            {
                if (bits.ev.type == ALLEGRO_EVENT_TIMER)            //Si el evento es el tiempo
                {
                    rana= ev_time ( key_pressed, bits , rana, score_p, &direccion, &menu_flag,&pause_flag,&do_exit,&select); //Se analiza si en ese tiempo se toco alguna tecla
                } 
                else if (bits.ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                {//Si el evento es del cerrado del display
                    do_exit = true;                                 //Se sale del juego
                    menu_flag = false;
                }
                else if (bits.ev.type == ALLEGRO_EVENT_KEY_DOWN)    //Si el evento es del teclado 
                {
                    ev_tecla(true,  key_pressed,  bits.ev );        //Se analiza que teclas están bajas 
                }
                else if (bits.ev.type == ALLEGRO_EVENT_KEY_UP) 
                {
                    ev_tecla(false,  key_pressed,  bits.ev );       //Se analiza que teclas están subidas
                }
            } 
             if (al_is_event_queue_empty(bits.event_queue)) 
             {
                 draw_menu ( select, bits,menu_flag); //Se dibuja el menú
                 al_flip_display();
             }
        }
        
        if ( do_exit == false)                              //Si se quiere empezar el juego
        {
            rana=init_level (nivel, autos, troncos,rana);   //Incialización del nivel (inicializa todos lo objetos)
            nivel_aux = nivel;                              //Se guarda el nivel actual
            draw_level(nivel, bits.font);          //Se le avisa al usuario que se paso de nivel
            type = DEATH;
            draw_lives (rana.cant_vida,0 ,0, type, bits.lives, bits.font); //Se dibuja la cantidad de vidas restantes 
        }

        change_level = false;                           //Todavía no se tiene que cambiar de nivel 
        while (!do_exit && !change_level && !menu_flag) //Mientras que no se haya cambiado de nivel 
        {
            if (al_get_next_event(bits.event_queue, &bits.ev))          //Toma un evento de la cola
            {
                if (bits.ev.type == ALLEGRO_EVENT_TIMER)                //Si el evento es el tiempo
                {
                    rana= ev_time ( key_pressed,  bits, rana, score_p, &direccion, &menu_flag,&pause_flag,&do_exit, &select);   //Se analiza si en ese tiempo se toco alguna tecla
                } 
                else if (bits.ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)   //Si el evento es del cerrado del display
                    do_exit = true;                                     //Se sale del juego

                else if (bits.ev.type == ALLEGRO_EVENT_KEY_DOWN)        //Si el evento es del teclado 
                {
                    ev_tecla(true,  key_pressed,  bits.ev );        //Se analiza que teclas están bajas 
                }
                else if (bits.ev.type == ALLEGRO_EVENT_KEY_UP)  
                {
                    ev_tecla(false,  key_pressed,  bits.ev );             //Se analiza que teclas están subidas
                }
            }

            if (al_is_event_queue_empty(bits.event_queue)) 
            {
                   //Si se tocó la letra "p"
                while (pause_flag) //Mientras no se haya elegido una opción del menú de pausa
                {
                    if (al_get_next_event(bits.event_queue, &bits.ev))      //Toma un evento de la cola
                    {
                        if (bits.ev.type == ALLEGRO_EVENT_TIMER)            //Si el evento es el tiempo
                        {
                            rana= ev_time ( key_pressed, bits , rana, score_p, &direccion, &menu_flag,&pause_flag,&do_exit,&select); //Se analiza si en ese tiempo se toco alguna tecla
                        } 
                        else if (bits.ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                        {//Si el evento es del cerrado del display
                            do_exit = true;                                 //Se sale del juego
                            pause_flag = false;
                        }
                        else if (bits.ev.type == ALLEGRO_EVENT_KEY_DOWN)    //Si el evento es del teclado 
                        {
                            ev_tecla(true,  key_pressed,  bits.ev );        //Se analiza que teclas están bajas 
                        }
                        else if (bits.ev.type == ALLEGRO_EVENT_KEY_UP) 
                        {
                            ev_tecla(false,  key_pressed,  bits.ev );       //Se analiza que teclas están subidas
                        }
                    } 
                    if (al_is_event_queue_empty(bits.event_queue)) 
                    {
                        draw_menu ( select, bits,menu_flag); //Se dibuja el menú
                        al_flip_display();
                    }

                }

                int aux_rana_x =rana.pos_x;
                int aux_rana_y = rana.pos_y;
                //Si no se tocó la letra "p"
                vidas = rana.cant_vida;                             //Se guarda la vida de la rana antes analizar colisiones
                if (nivel == 1)
                {
                    rana =  colision (rana, PASOS, autos,troncos,AL1, TL1);    //Se analiza las colisiones dependiendo del nivel        
                }
                else if (nivel == 2)
                {
                    rana =  colision (rana, PASOS,autos,troncos, AL2, TL2);    //Se analiza las colisiones dependiendo del nivel  
                }
                else if (nivel == 3)
                {
                     rana =  colision (rana, PASOS,autos,troncos, AL3, TL3);    //Se analiza las colisiones dependiendo del nivel 
                }
                rana = check_charcos( rana,  charcos, PASOS, p_nivel, score_p); //Se analiza si llegó a algún charco                  
                if ( rana.cant_vida < vidas )  //Si se murió la rana 
                {
               		key_pressed[KEY_UP] = false;       //Se deja de leer el teclado (evita que la rana cambie de posición cuando se muestran las animaciones)
               		key_pressed[KEY_DOWN] = false;        
               		key_pressed[KEY_LEFT] = false;        
               		key_pressed[KEY_RIGHT] = false;        
                    direccion = DEATH;          //Se cambia la dirección a death
                    landscape();                //Se dibuja el escenario
                    draw_rana( aux_rana_x, aux_rana_y,&direccion, bits.ranabit_y, bits.death);  //Se dibuja la imagen del esqueleto de la rana
                    al_play_sample(bits.dead, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);      //Se reproduce el audio de muerte
                    al_flip_display();                                                          //Se muestra en el display por 1 segundo
                    al_rest(1.0);                                                               
                    
                    if (rana.cant_vida <= 0)   //Si se quedó sin vida la rana  
                    {
                    	 rana = check_charcos( rana,  charcos, PASOS, p_nivel, score_p); //Se analiza si llegó a algún charco                  
               
                         show_score (score, bits.font );                 //Se muestra el score de la partida y el highscore
                         score=0;                                        //Se vuelve el score al 0 debido a que murió          
                         menu_flag=true;                                 //Se resetea el juego

                    }
                    else if (rana.cant_vida > 0)                        //Si sigue con vida la rana
                    {
                        type = DEATH;                                                             //El tipo de imagen corresponde a la imagen de las vidas
                        draw_lives ( rana.cant_vida,0 ,0, type, bits.lives, bits.font);          //Se dibuja la cantidad de vidas restantes 
                    }
                }                   
	            if (nivel_aux < nivel)      //Si hubo un cambio de nivel 
	            {
	                change_level = true;    //Se cambia de nivel    
	            }
	            else if (nivel >= 4)        //Si el nivel no es compatible con los dados en el juego
	            {
	                show_score (score, bits.font);     //Se muestra el score de la partida y el highscore
	                nivel = 1;              //Se vuelve al nivel 1
	                change_level = true;    //Se cambia de nivel 
	                rana.cant_vida = 3;     //Se reinician las vidas
	            }     
                landscape();                                            //Se dibuja el fondo 
                for (i=0, j=2; i < CANT_CHARCOS && j< 15; i++, j+=3)    //Se dibujan los charcos 
                {
                    if (charcos[i].filled ==1)                          //Si la rana llegó a unos de los charcos
                    {
                        type = WIN_CHARCO;
                        draw_lives ( rana.cant_vida, charcos[i].pos, POS_Y_CHARCO, type, bits.rana_charco, bits.font);       //Se dibuja la rana estática en el charco                
                    }
                }
                if (nivel == 1)
                {
                     draw_all ( AL1,TL1, autos, troncos,bits);          //Se dibujan los troncos y autos del nivel 1
                }
                else if (nivel == 2)
                {
                     draw_all ( AL2,TL2, autos, troncos,bits);          //Se dibujan los troncos y autos del nivel 2
                }
                else if (nivel == 3)
                {
                     draw_all ( AL3,TL3, autos, troncos,bits);          //Se dibujan los troncos y autos del nivel 3
                }
                draw_rana( rana.pos_x, rana.pos_y,&direccion, bits.ranabit_y, bits.ranabit_x);  //Se dibuja la rana 
                al_flip_display();                                                              //Se representa todo en el display 
                }          
            }
    }
  
    //Se termina el juego, se destruye todo 
   al_uninstall_audio();
   al_destroy_event_queue(bits.event_queue); 
   al_destroy_bitmap(bits.ranabit_x);
   al_destroy_bitmap(bits.ranabit_y);
   al_destroy_bitmap(bits.objbit_1_au);
   al_destroy_bitmap(bits.objbit_2_au);
   al_destroy_bitmap(bits.objbit_2_tr);
   al_destroy_bitmap(bits.objbit_3_tr);
   al_destroy_bitmap(bits.image_leave);
   al_destroy_bitmap(bits.image_off);
   al_destroy_bitmap(bits.image_on);
   al_destroy_bitmap(bits.death);
   al_destroy_bitmap(bits.lives);
   al_destroy_bitmap(bits.rana_charco);
   al_destroy_timer(bits.timer);
   al_destroy_display(bits.display); 

    return 0;
    
    
}
#endif




#ifdef RASPI

#include "colisiones.h"
#include "rpi_funs.h"
#include "rpi_draw.h"

#define ON 0  
#define OFF 1
#define FIRST_LVL 1
#define WAIT_TIME 1

int main(void)
{
	joy_init();                                     				//inicializa el joystick
	disp_init();                                    				//inicializa el display
	disp_clear();                                   				//limpia todo el display

	char off_flag=ON;                                				//flag para indicar que se apagó el programa

	while(off_flag!=OFF)
	{
		char opcion=ON;                                          	//EXIT si en el menú se eligió apagar, PLAY si se eligió jugar
		char *p_opcion=&opcion;

		menu(p_opcion, &draw_off);         							// MENÚ

		switch(opcion)
		{
			case EXIT:                                           	//se apagó el programa
			{ 
				off_flag=OFF;
				disp_clear();
				break;
			}
			case PLAY:                                         		//se eligió jugar
			{   
				int cant_auto;
				int cant_tronco;
				char letra = ON;                                	//variable que indica la dirección en la que se mueve la rana
				char break_flag=ON;                             	//flag para indicar un break del ciclo provocado por haber pasado un nivel
				char pause_flag=ON;                             	//flag para indicar que se pausó el juego
				char menu_flag=ON;									//flag para indicar que se desea volver al menú principal

				int score = 0;	                                 	//inicializo el contador de puntaje
				int *p_score = &score;

				int nivel = FIRST_LVL;                          	//inicializo el contador de niveles
				int *p_nivel = &nivel;

				obj_t autos[CANT_AUTOS];                         	//inicializo objetos (autos y troncos)
				obj_t troncos[CANT_TRONCOS];
				charco_t charcos[CANT_CHARCOS];
				
				rana_t rana = pos_rana_init(rana, RPI);         	//inicializo la rana
				
				while(menu_flag!=OFF) 								//mientras no se desee volver al menú principal 
				{
					dcoord_t pos = {rana.pos_x, rana.pos_y};        //pos es la posición actual, empieza en el centro de la matriz
					dcoord_t npos = pos;                            //npos es la próxima posición
					jcoord_t coord = {0,0};							//coordenadas medidas del joystick

					vidas_restantes(rana.cant_vida);             	//muestro las vidas con la que comienza el juego
					
					init_agua();                                	//inicializo el agua 
					init_charcos_rpi(charcos);  					//inicializo el charcos

					if(nivel==1)									//inicializo los objetos respecto al nivel
					{
						init_obj(autos, AL1, troncos, TL1, nivel);
						cant_auto = AL1;
						cant_tronco = TL1;
					}
					else if (nivel==2)
					{
						init_obj(autos, AL2, troncos, TL2, nivel);
						cant_auto = AL2;
						cant_tronco = TL2;
					}
					else if (nivel==3)
					{
						init_obj(autos, AL3, troncos, TL3, nivel);
						cant_auto = AL3;
						cant_tronco = TL3;
					}

					while((pause_flag != OFF)&&(break_flag != OFF))                             //Mientras no se pause el juego y mientras no se
					{																			//supere el nivel actual
						disp_update();                                                         	//Actualiza el display con el contenido del buffer
						move_obj(autos, cant_auto, D_OFF);                                   	//mueve los autos
                        move_obj(troncos, cant_tronco, D_ON);                                   //mueve los troncos

                        joy_update();                                                           //Mide las coordenadas del joystick
						coord = joy_get_coord();                                                //Guarda las coordenadas medidas
						if((coord.x > THRESHOLD) && (npos.x <= DISP_MAX_X)) letra = 'R';      	//Establece la próxima posición 
						if((coord.x < -THRESHOLD) && (npos.x > DISP_MIN)) letra = 'L';        	//según las coordenadas medidas
						if((coord.y > THRESHOLD) && (npos.y > DISP_MIN)) letra = 'U';
						if((coord.y < -THRESHOLD) && (npos.y <= DISP_MAX_Y)) letra = 'D';
						rana = movimiento_rana(letra, rana, RPI, p_score);
						npos.x = rana.pos_x;
						npos.y = rana.pos_y;
						disp_write(pos,D_OFF);                                                  //apaga la posición vieja en el buffer
						disp_write(npos,D_ON);                                                  //enciende la posición nueva en el buffer
						pos = npos;                                                             //actualiza la posición actual
						letra = ON;                                                             //resetea la letra, por si la rana no se mueve en el próximo ciclo

						int vida_antes = rana.cant_vida;                                        //variable para chequear si la rana perdió una vida
						rana = colision (rana, RPI, autos, troncos, cant_auto, cant_tronco);    //verifico si la rana colisionó con un auto o si se subió a un tronco
						int nivel_antes = nivel;                                                //variable para chequear si la rana pasó de nivel
						rana = check_charcos(rana, charcos, RPI, p_nivel, p_score);             //verifico si la rana legó a un charco

						if (vida_antes>rana.cant_vida)
						{
							if(rana.cant_vida<=0)                                              	//la rana perdió todas sus vidas
							{
								draw_skull();													//se muestra la calavera
								int highscore = highscore_check(score);							//se obtiene el highscore
								show_score(score, highscore);									//se muestra el score de la partida y el top score
								menu_flag=OFF;					                             	//vuelvo al menu principal
								break_flag=OFF;                                                
                                rana = check_charcos(rana, charcos, RPI, p_nivel, p_score);		//reseteo los charcos para la próxima partida
                            }
							else                                                                //la rana perdió una vida
							{
								vidas_restantes(rana.cant_vida);                                //muestro la cantidad de vidas restantes
								
								init_agua();   													//vuelvo a mostrar el nivel
								init_charcos_rpi(charcos);  
								if(nivel==1)
								{
									init_obj(autos, AL1, troncos, TL1, nivel);
								}
								else if (nivel==2)
								{
									init_obj(autos, AL2, troncos, TL2, nivel);
								}
								else if (nivel==3)
								{
									init_obj(autos, AL3, troncos, TL3, nivel);
								}
							}
						}

						if(nivel_antes < nivel) break_flag=OFF;                              	//la rana pasó de nivel
						if(nivel == 4) nivel=FIRST_LVL;                                   		//si pasa el nivel 3, vuelve al 1
						joy_init();
						if(joy_get_switch()!=J_NOPRESS) 
						{
							pause_flag=OFF;                      								// se pausó el juego
							sleep(WAIT_TIME);
						}

                        int c;
                        dcoord_t pos_charco;
					    for (c=0; c<CANT_CHARCOS; c++)    										//Se dibujan los charcos 
                        {
                            if (charcos[c].filled ==1)                          				//Se enciende el LED del charco al que la 
                            {																	//rana llegó
                                pos_charco.x = charcos[c].pos;
                                pos_charco.y = DISP_MIN+1;										//fila en la que se encuentran los charcos
                                disp_write(pos_charco, D_ON);
                            }
                        }
                    }

					disp_clear();                                                             	//limpia todo el display
					
					if(pause_flag==OFF)
					{	
						char opt=ON; 															//EXIT si se eligió salir al menú principal, PLAY si se desea reanudar
						char *p_opt=&opt;
						menu(p_opt, &draw_exit);                      							//Menú de pausa
						switch(opt)
						{
							case EXIT:                                  						//Se sale al menú principal
							{
								menu_flag=OFF;
								disp_clear();
								sleep(WAIT_TIME);
								opcion=ON;
								break;
							}	
							case PLAY:                                  						//Se reanuda el juego
							{
								pause_flag=ON;
								disp_clear();
								sleep(WAIT_TIME);   
								break;
							}	
						}	
					}
				}
				break;
			}
		}
	}
	return 0;
}
#endif


