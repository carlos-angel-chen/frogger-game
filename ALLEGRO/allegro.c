/***************************************************************************//**
  @file     allegro.c
  @brief    Contiene todas las funciones que permiten usar allegro para el front del frogger
  @author   Carlos Angel Chen, Santiago Feldman, Anna Candela Gioia Perez, Tiago Nanni
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "allegro.h" 

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define SPEED 2 //Define la mínima velocidad de los objetos

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static void draw_obt( int16_t x, int16_t y,ALLEGRO_BITMAP* objbit ,int typeobj, int16_t width);
 static ALLEGRO_BITMAP* sprite_grab(int x, int y, int w, int h,int foto);
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
/*FUNCIÓN INIT_POINTER: Se incializan todos los pointer necesarios para allegro*/
pointers_t init_pointers (bool *do_exit)
{
    if (!al_init())   //Se inicializa allegro
    {
        *do_exit = false;
        exit(1);
    }
    pointers_t pointer;
    ALLEGRO_DISPLAY*display = NULL;             //Crea en puntero al display 
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;    //Crea la secuencia de eventos
    ALLEGRO_TIMER *timer = NULL;                //Crea el timer
    ALLEGRO_BITMAP *objbit_1_au= NULL;          //Se crea el puntero a los autos de longitud 1 
    ALLEGRO_BITMAP *objbit_1_au1= NULL;         //Se crea el puntero a los autos de longitud 1 (otro color)
    ALLEGRO_BITMAP *objbit_2_au= NULL;          //Se crea el puntero a los autos de longitud 2
    ALLEGRO_BITMAP *objbit_2_tr= NULL;          //Se crea el puntero a los troncos de longitud 2
    ALLEGRO_BITMAP *objbit_3_tr= NULL;          //Se crea el puntero a los troncos de longitud 3
    ALLEGRO_BITMAP *ranabit_x= NULL;            //Se crea el puntero a la rana
    ALLEGRO_BITMAP *ranabit_y= NULL;            //Se crea el puntero a la rana
    ALLEGRO_BITMAP *image_on= NULL;             //Se crea el puntero a la imagen de play
    ALLEGRO_BITMAP *image_off= NULL;            //Se crea el puntero a la imagen de apagado
    ALLEGRO_BITMAP *image_leave= NULL;          //Se crea el puntero a la imagen de salir al menú principal
    ALLEGRO_BITMAP *death= NULL;                //Se crea el puntero a la imagen de muerte
    ALLEGRO_BITMAP *rana_charco= NULL;          //Se crea el puntero a la imagen de la rana en el charco
    ALLEGRO_BITMAP *lives= NULL;                //Se crea el puntero a la imagen de la vidas
    ALLEGRO_FONT* font = NULL;                  //Se crea el puntero al font del texto
    ALLEGRO_SAMPLE* sample = NULL;              //Se crea el puntero al sample de audio de background
    ALLEGRO_SAMPLE* hop = NULL;                 //Se crea el puntero al sample de audio de movimiento
    ALLEGRO_SAMPLE* dead = NULL;                //Se crea el puntero al sample de audio de muerte
    
    if (!al_install_keyboard())                             //Se inicializa el teclado
    {
        *do_exit = true;
        exit(1);
    }
    timer = al_create_timer(1.0 / FPS);                     //Se incializa el timer 
    if (!timer)                                      
    {
        *do_exit = true;
        exit(1);
    }
    if (!al_init_primitives_addon())                        //Se inicializa las primitivas 
    {
        *do_exit = true;
        exit(1);
    }
    if(!al_init_image_addon())                              //Se inicializa las imágenes
    {
       *do_exit = true;
        exit(1);
    }
    if(!al_init_font_addon())                               //Se inicializa las fuentes de texto
    {
       *do_exit = true;
        exit(1);
    }
    if(!al_init_ttf_addon())                                //Se inicializa las fuentes de texto
    {
       *do_exit = true;
        exit(1);
    }
    if(!al_install_audio())                                 //Se inicializa el audio
    {
       *do_exit = true;
        exit(1);
    }
    if(!al_init_acodec_addon())
    {
       *do_exit = true;
        exit(1);
    }

    al_reserve_samples(3);                                  //Se reservan los tres audios
    sample = al_load_sample("export.wav");                  //Se cargan los audios
    hop = al_load_sample("hop.wav");
    dead = al_load_sample("dead.wav");
    event_queue = al_create_event_queue();                  //Se incializa la cola de eventos
    if (!event_queue) 
    {
        *do_exit = true;
        exit(1);     
    }
    if (!event_queue) 
    {
        *do_exit = true;
        exit(1);     
    }

    font =al_load_ttf_font("Uroob-Regular.ttf", 80, 0);     //Se carga la fuente
    if (!font)                                  
    {
        *do_exit = true;
        exit(1);     
    }
    ranabit_y = al_create_bitmap(RANA_W*PASOS,RANA_H*PASOS);   //Se define el tamaño de la rana
    ranabit_x = al_create_bitmap(RANA_W*PASOS,RANA_H*PASOS);   //Se define el tamaño de la rana 
    objbit_1_au = al_create_bitmap(PASOS*1,PASOS);             //Se define el tamaño de un auto de longitud 1   
    objbit_1_au1 = al_create_bitmap(PASOS*1,PASOS);            //Se define el tamaño de un auto de longitud 1 (otro color)
    objbit_2_au= al_create_bitmap(PASOS*2,PASOS);              //Se define el tamaño de un auto de longitud 2
    objbit_2_tr= al_create_bitmap(PASOS*2,PASOS);              //Se define el tamaño de un tronco de longitud 2
    objbit_3_tr = al_create_bitmap(PASOS*3,PASOS);             //Se define el tamaño de un tronco de longitud 3
    death= al_create_bitmap(RANA_W*PASOS,RANA_H*PASOS);        //Se define el tamaño del esqueleto de la rana
    rana_charco = al_create_bitmap(RANA_W*PASOS,RANA_H*PASOS); //Se define el tamaño de la rana
    ranabit_x = al_create_bitmap(RANA_W*PASOS,RANA_H*PASOS);   //Se define el tamaño de la rana 
    image_on = al_load_bitmap("play.png");                     //Se define la imagen de play
    image_off = al_load_bitmap("apagar.png");                  //Se define la imagen de apagado
    image_leave = al_load_bitmap("leave.png");                 //Se define la imagen de salir al menú principal
    lives = al_load_bitmap("lives.png");                       //Se define la imagen que indica las vidas
    if (!ranabit_y || !ranabit_x || !objbit_1_au || !objbit_2_au || !objbit_2_tr || !objbit_3_tr || !image_on || !image_off || !image_leave || !death || !lives || !rana_charco || !objbit_1_au1)  
    {
        *do_exit = true;
        exit(1);     
    }

    display = al_create_display(HEIGHT*PASOS, WIDTH*PASOS); //Se inicializa el display
    if (!display) 
    {
        *do_exit = true;
        exit(1);     
    }

       //Se registran los eventos:
    al_register_event_source(event_queue, al_get_keyboard_event_source()); //teclado
    al_register_event_source(event_queue, al_get_display_event_source(display)); //display
    al_register_event_source(event_queue, al_get_timer_event_source(timer)); //timer

    ranabit_y = sprite_grab(0, 31, 22, 16,1);     //Se toma la imagen que la representa la rana de arriba y abajo
    ranabit_x = sprite_grab(1, 1, 16, 22,1);      //Se toma la imagen que la representa la rana de derecha e izquierda
    objbit_2_tr = sprite_grab(0, 180,  83, 20,1); //Se toma la imagen de los troncos de longitud de 2
    objbit_3_tr = sprite_grab(0, 180,  83, 20,1); //Se toma la imagen de los troncos de longitud de 3
    objbit_1_au = sprite_grab(71, 56,  23, 23,1); //Se toma la imagen de los autos de longitud de 1
    objbit_1_au1 = sprite_grab(0,57,31,20,1);     //Se toma la imagen de los autos de longitud de 1 (otro color)
    objbit_2_au = sprite_grab(95, 92,  49, 17,1); //Se toma la imagen de los autos de longitud de 2
    death=sprite_grab(0,48,16,16,0);              //Se toma la imagen del esqueleto de la rana
    rana_charco=sprite_grab(48,96,16,16,0);       //Se toma la imagen de la rana estática en el charco
    al_start_timer(timer);                        //Empieza el tiempo
    ALLEGRO_EVENT ev;                           
    pointer.ev = ev; //Se completan todos los campos de la estructura 
    pointer.display = display;
    pointer.event_queue = event_queue;
    pointer.objbit_1_au = objbit_1_au;
    pointer.objbit_1_au1 = objbit_1_au1;
    pointer.objbit_2_au = objbit_2_au;
    pointer.objbit_2_tr = objbit_2_tr;
    pointer.objbit_3_tr= objbit_3_tr;
    pointer.ranabit_x = ranabit_x;
    pointer.ranabit_y = ranabit_y;
    pointer.timer = timer;
    pointer.image_leave= image_leave;
    pointer.image_off = image_off;
    pointer.image_on = image_on;
    pointer.death=death;
    pointer.rana_charco=rana_charco;
    pointer.lives = lives;
    pointer.font = font;
    pointer.background = sample;
    pointer.hop = hop;
    pointer.dead= dead;
    return pointer;  //Devuelve la estructura
    
    
}

/*FUNCIÓN DRAW_ALL: Dibuja todos los objetos del juego dependiendo del nivel y el movimiento*/
void draw_all ( int cantidad_au, int cantidad_tr,obj_t autos[], obj_t troncos[], pointers_t bits)
{
    int i; //Índice 
    for (i=0; i<cantidad_au;i++)    
    {
        autos[i] = movimiento_obj(autos[i], PASOS); //Se mueven los autos 
        if (autos[i].width == 1*PASOS)
        {
            if( (autos[i].pos_y/PASOS) %2 == 0 )  //Si están en una fila par se muestra un auto de un color
            {
                draw_obt( autos[i].pos_x, autos[i].pos_y,bits.objbit_1_au, autos[i].type_obj,autos[i].width);//Se dibujan los autos
            }
            else                                    //Si están en una fila impar se muestra un auto de otro color
            {
                draw_obt( autos[i].pos_x, autos[i].pos_y,bits.objbit_1_au1, autos[i].type_obj,autos[i].width);//Se dibujan los autos
            }
            

        }//Se crea el objeto 
        else if (autos[i].width == 2*PASOS)
        {
            draw_obt(autos[i].pos_x, autos[i].pos_y,bits.objbit_2_au, autos[i].type_obj,autos[i].width);//Se dibujan los autos

        }//Se crea el objeto 
    }
        for (i=0; i< cantidad_tr;i++)  
        {
            troncos[i] = movimiento_obj(troncos[i], PASOS);//Se mueven los troncos 
            if (troncos[i].width == 3*PASOS)
            {
                draw_obt( troncos[i].pos_x, troncos[i].pos_y,bits.objbit_3_tr, troncos[i].type_obj,troncos[i].width);//Se dibujan los autos

            }//Se crea el objeto 
            else if (troncos[i].width == 2*PASOS)
            {
                draw_obt( troncos[i].pos_x, troncos[i].pos_y,bits.objbit_2_tr, troncos[i].type_obj,troncos[i].width);//Se dibujan los autos

            }//Se crea el objeto 
           
        }
   
}



/*FUNCIÓN DRAW_RANA: Dibuja la rana en el display con su respectiva imagen y posición*/
void draw_rana (float x, float y, int *direccion,ALLEGRO_BITMAP*ranabit_y, ALLEGRO_BITMAP*ranabit_x)
{

            if (*direccion == KEY_UP)                           											//Si la dirección es para arriba 
            {                                                   											//Se dibuja la imagen para arriba
                al_draw_scaled_bitmap(ranabit_y,
                0, 0, al_get_bitmap_width(ranabit_y), al_get_bitmap_height(ranabit_y), 
                x,y, RANA_W*PASOS, RANA_H*PASOS, 															//Se indica el tamaño de la imagen
                0); 
            }
       		else if(*direccion == KEY_DOWN)                      											//Si la dirección es para abajo
            {                                                    											//Se dibuja la imagen para abajo
                al_draw_scaled_bitmap(ranabit_y,
                0, 0, al_get_bitmap_width(ranabit_y), al_get_bitmap_height(ranabit_y), 
                x, y, RANA_W*PASOS, RANA_H*PASOS, 
                ALLEGRO_FLIP_VERTICAL);   																	//La imagen se da vuelta verticalmente y se indica el tamaño de la imagen 
                 
            }
            else if(*direccion == KEY_LEFT)                     											//Si la dirección es para la izquierda
            {                                                   											//Se dibuja la imagen para la izquierda 
                al_draw_scaled_bitmap(ranabit_x,
                0, 0, al_get_bitmap_width(ranabit_x), al_get_bitmap_height(ranabit_x), 
                x, y, RANA_W*PASOS, RANA_H*PASOS, 
                ALLEGRO_FLIP_HORIZONTAL); 																	//La imagen se da vuelta horizontalmente y se indica el tamaño de la imagen 
                 
            }
            else if(*direccion == KEY_RIGHT)                    											//Si la dirección es para la derecha 
            {                                                   											//Se dibuja la imagen para la derecha
                al_draw_scaled_bitmap(ranabit_x,
                0, 0, al_get_bitmap_width(ranabit_x), al_get_bitmap_height(ranabit_x), 
                x, y, RANA_W*PASOS, RANA_H*PASOS, 															//Se indica el tamaño de la imagen 
                0); 
                
            }
            else if (*direccion == DEATH)                        											//Si la direccion indica que se ha muerto la rana
            {
                *direccion = KEY_UP;                             											//La direccion se resetea hacia arriba
                al_draw_scaled_bitmap(ranabit_x,                											//Se dibuja el esqueleto de la rana 
                0, 0, al_get_bitmap_width(ranabit_x), al_get_bitmap_height(ranabit_x), 
                x, y, RANA_W*PASOS, RANA_H*PASOS, 
                0);  
            }

            else                                                											//Si no cambio la dirección, entonces se dibuja como estaba anteriormente 
            {
                al_draw_scaled_bitmap(ranabit_y,
                0, 0, al_get_bitmap_width(ranabit_y), al_get_bitmap_height(ranabit_y), 
                x, y, RANA_W*PASOS, RANA_H*PASOS, 															//Se indica el tamaño de la imagen 
                0); 
            }
}
/*FUNCIÓN LANDSCAPE: Dibuja el escenario del juego*/
void landscape(void)

{
    al_draw_filled_rectangle(0, RANA_H *PASOS, WIDTH * PASOS, HEIGHT*PASOS/2, al_color_name("blue"));           //Agua
    al_draw_filled_rectangle(0, HEIGHT*PASOS/2, WIDTH*PASOS, HEIGHT*PASOS, al_color_name("black"));             //Calle 
    al_draw_filled_rectangle(0, HEIGHT*PASOS - PASOS, WIDTH *PASOS, WIDTH*PASOS, al_color_name("purple"));      //Descansos
    al_draw_filled_rectangle(0, HEIGHT*PASOS/2 +PASOS, WIDTH*PASOS , WIDTH*PASOS/2, al_color_name("purple"));   
    al_draw_filled_rectangle(0, 0, WIDTH*PASOS, PASOS*2, al_color_name("green"));                               //Pasto
    int i;  //Índice 
    for (i=2; i<15; i+=3)
    {
        al_draw_filled_rectangle(i*PASOS, 0, PASOS*(i+1), PASOS*2, al_color_name("blue"));   //Se dibujan los charcos 
    }

}


/*FUNCIÓN INIT_LEVEL: Inicializa la rana y cada objeto dependiendo del nivel */
rana_t init_level (int nivel,obj_t autos[], obj_t troncos[], rana_t rana)   
{   
    rana_t rana_aux = reset_rana( rana_aux, PASOS); //Se obtienen las valores de las posiciones iniciales de la rana 
    rana.pos_x = rana_aux.pos_x;  //Se actualiza la rana
    rana.pos_y = rana_aux.pos_y;
    init_autos(autos, PASOS, nivel,SPEED);      //Se inicializa los autos 
    init_troncos(troncos, PASOS, nivel,SPEED);  //Se inicializan los troncos 
    return rana; //Se devuelve la rana
    
}
/*FUNCIÓN EV_TIME: Analiza el evento del tiempo de allegro para ver si la rana debe moverse*/
rana_t ev_time (bool key_pressed[], pointers_t pointers, rana_t rana, int *score, int *direccion,bool *menu_flag, bool *pause_flag,  bool *do_exit, int *select)
{
   
          if (pointers.ev.type == ALLEGRO_EVENT_TIMER) 
          {
                if (key_pressed[KEY_UP])                                    //Si se presiono la tecla indicando hacia arriba 
                {
                    if (*menu_flag==false && *pause_flag == false)
                    {
                        rana = movimiento_rana('U',rana,  PASOS,score);     //Se mueve la rana en esa dirección
                        *direccion = KEY_UP;                                //Se actualiza el valor de la dirección
                        al_play_sample(pointers.hop, 0.5, 0.0, 3.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                }
                if (key_pressed[KEY_DOWN])                                  //Si se presiono la tecla indicando hacia abajo
                {
                    if (*menu_flag==false && *pause_flag == false)
                    {
                        rana = movimiento_rana('D',rana , PASOS,score);      //Se mueve la rana en esa dirección
                        *direccion = KEY_DOWN;                               //Se actualiza el valor de la dirección
                        al_play_sample(pointers.hop, 0.5, 0.0, 3.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    } 
                }
                if (key_pressed[KEY_LEFT])                                  //Si se presiono la tecla indicando hacia la izquierda
                {
                    if (*menu_flag==false && *pause_flag == false)          //Y no se está ni el menú principal o el de pausa
                    {
                        rana = movimiento_rana('L',rana ,  PASOS,score);    //Se mueve la rana en esa dirección
                        *direccion = KEY_LEFT;                              //Se actualiza el valor de la dirección
                        al_play_sample(pointers.hop, 0.5, 0.0, 3.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    else                                                    //Si se está en el menú principal o de pausa
                    {                      
                        *select = ON;                                       //Es la opción de prendido
                    }                 
                }
                if (key_pressed[KEY_RIGHT])                                 //Si se presiono la tecla indicando hacia la derecha
                {
                    if (*menu_flag==false && *pause_flag == false)          //Y no se está ni el menú principal o el de pausa
                    {
                        rana = movimiento_rana('R',rana ,  PASOS,score);     //Se mueve la rana en esa dirección
                        *direccion = KEY_RIGHT;                              //Se actualiza el valor de la dirección
                        al_play_sample(pointers.hop, 0.5, 0.0, 3.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    else if (*menu_flag == true)                            //Si se está en el menú principal
                    {                      
                        *select = OFF;                                      //Es la opción de apagado
                        
                    }
                    else if (*pause_flag == true)                           //Si se está en el menú de pausa
                    {
                        *select = AGAIN;                                    //Es la opción de salir al menú principal
                        
                    }
                        
                }
                if (key_pressed[KEY_ENTER])                                 //Si se presiono la tecla enter
                {
                    if (*menu_flag== true  || *pause_flag == true)          //Si se está en el menú principal o en el menú de pause
                    {
                        switch (*select)                                    
                        {
                            case OFF:                                       //Si se quiere apagar el juego
                                *do_exit = true;                            //Se activan los flags para salir del juego
                                *menu_flag = false;
                                *pause_flag=false;
                                break;
                            case ON:                                        //Si se quiere prender el juego
                                *menu_flag = false;                         //Se desactivan los flags para salir del menú
                                *pause_flag = false;
                                break;
                            case AGAIN:                                     //Si se quiere salir al menú principal
                                *menu_flag = true;                          //Se activa el flag del menú principal
                                *pause_flag = false;                        //Se desactiva el flag del menú inicial 
                                *select=ON;                                 
                                break;
                        }    
                    }           
                }
                if (key_pressed[KEY_P])                                     //Si se tocó la letra "p" 
                {
                    if (*pause_flag== false)                                //y el flag del menú de pausa esta desactivado
                    {
                        *pause_flag = true;                                 //se activa
                    }
                    
                }


          } 
    return rana;
}
/*FUNCIÓN EV_TECLA: Analiza el evento del teclado de allegro para ver si se presionó alguna tecla*/
void ev_tecla(bool state, bool key_pressed[], ALLEGRO_EVENT ev )
{
        switch (ev.keyboard.keycode) 
        {
            case ALLEGRO_KEY_UP:
                key_pressed[KEY_UP] = state;        //Se cambia el estado de cada tecla dependiendo de si cumple la condición del evento
                break;
            case ALLEGRO_KEY_DOWN:
                key_pressed[KEY_DOWN] = state;
                break;
            case ALLEGRO_KEY_LEFT:
                key_pressed[KEY_LEFT] = state;
                break;
            case ALLEGRO_KEY_RIGHT:
                key_pressed[KEY_RIGHT] = state;
                break;
            case ALLEGRO_KEY_ENTER:
                key_pressed[KEY_ENTER] = state;
                break;
            case ALLEGRO_KEY_P:
                key_pressed[KEY_P] = state;
                break;
        }
}

/*FUNCIÓN DRAW_MENU: Dibuja la imagen correspondiente en el menú*/
void draw_menu (int select, pointers_t pointers, bool menu_flag)
{
    switch (select)
    {
        case ON:   //Se muestra la imagen de jugar o seguir jugando 
            
            al_draw_scaled_bitmap(pointers.image_on,
            0, 0, al_get_bitmap_width(pointers.image_on), al_get_bitmap_height(pointers.image_on), 
            0, 0, al_get_display_width(pointers.display), al_get_display_height(pointers.display), 
            0); 
            if (menu_flag == true)
            {
            	al_draw_text(pointers.font, al_map_rgb(255, 255, 255), PASOS*WIDTH/ 2, PASOS*HEIGHT - 400, ALLEGRO_ALIGN_CENTER, "FROGGER");
				al_draw_text(pointers.font, al_map_rgb(255, 255, 255), PASOS*WIDTH/ 2, PASOS*HEIGHT - 100, ALLEGRO_ALIGN_CENTER, "MENÚ PRINCIPAL");
			}

            break;
        case OFF:  //Se muestra la imagen de apagar el juego
            
            al_draw_scaled_bitmap(pointers.image_off,
            0, 0, al_get_bitmap_width(pointers.image_off), al_get_bitmap_height(pointers.image_off), 
            0, 0, al_get_display_width(pointers.display), al_get_display_height(pointers.display), 
            0); 
            break;
        case AGAIN: //Se muestra la imagen de salir al menú principal
            
            al_draw_scaled_bitmap(pointers.image_leave,
            0, 0, al_get_bitmap_width(pointers.image_leave), al_get_bitmap_height(pointers.image_leave), 
            0, 0, al_get_display_width(pointers.display), al_get_display_height(pointers.display), 
            0); 
            break;            
    }
}
/*FUNCIÓN DRAW_LEVEL: Le avisa el nivel al usuario*/
void draw_level(int nivel, ALLEGRO_FONT* font)
{

    if (nivel == 1)   //Nivel 1
    {
        landscape();            //Se muestra el escenario
        al_draw_text(font, al_map_rgb(255, 255, 255), PASOS*WIDTH/ 2, (PASOS*HEIGHT / 4), ALLEGRO_ALIGN_CENTER, "LEVEL 1"); //Se escribe que se está en el nivel 1
        al_flip_display();
        al_rest(1.0);  //Se muestra por 1 segundos 
        
    }
    else if (nivel ==2)//Nivel 2
    {
        landscape();        //Se muestra el escenario
        al_draw_text(font, al_map_rgb(255, 255, 255), PASOS*WIDTH/ 2, (PASOS*HEIGHT / 4), ALLEGRO_ALIGN_CENTER, "LEVEL 2"); //Se escribe que se está en el nivel 2
        al_flip_display();
        al_rest(1.0);//Se muestra por 1 segundos 
    }
    else if (nivel == 3)//Nivel 3
    {
        landscape();    //Se muestra el escenario
        al_draw_text(font, al_map_rgb(255, 255, 255), PASOS*WIDTH/ 2, (PASOS*HEIGHT / 4), ALLEGRO_ALIGN_CENTER, "LEVEL 3"); //Se escribe que se está en el nivel 3
        al_flip_display();
        al_rest(1.0);//Se muestra por 1 segundos 
    }

}
/*FUNCIÓN DRAW_LIVES: Le avisa la cantidad de vidas restantes al usuario*/

/*FUNCIÓN SHOW_SCORE: Le meustra al usuario su score y el highscore*/
void show_score (int score, ALLEGRO_FONT*font )
{
    int highscore_n = highscore_check(score);  //Se obtiene el highscore 
    landscape();
    al_draw_textf (font, al_map_rgb(255, 255, 255),
   PASOS*WIDTH/ 2, (PASOS*HEIGHT / 4),ALLEGRO_ALIGN_CENTER,
   "SCORE %d",score);  //Score de la partida
    al_flip_display();
    al_rest(2.0);//Se muestra por 2 segundos 
    landscape();
    al_draw_textf (font, al_map_rgb(255, 255, 255),
   PASOS*WIDTH/ 2, (PASOS*HEIGHT / 4),ALLEGRO_ALIGN_CENTER,
   "TOP SCORE %d",highscore_n); //Highscore 
    al_flip_display();
    al_rest(2.0);//Se muestra por 2 segundos 
    
    
}
void draw_lives( uint8_t cant_vida,int x, int y, int type, ALLEGRO_BITMAP* point, ALLEGRO_FONT* font )
{
    if (type == WIN_CHARCO)                 //Si la imagen corresponde a un charco completado
    {
        
        al_draw_scaled_bitmap(point,                //Se dibuja la rana estática en el charco
        0, 0, al_get_bitmap_width(point), al_get_bitmap_height(point), 
        x, y, RANA_W*PASOS, RANA_H*PASOS, 
        0);      
    }
    else if (type == DEATH)             //Si la imagen corresponde a un decremento en la cantidad de vidas de la rana 
    {
        al_draw_scaled_bitmap(point,                //Se dibuja el esqueleto de la rana 
        0, 0, al_get_bitmap_width(point), al_get_bitmap_height(point), 
        x, y, WIDTH*PASOS , HEIGHT*PASOS , 
        0); 
        al_draw_textf (font, al_map_rgb(255, 255, 255),
        PASOS*WIDTH/2, PASOS*HEIGHT - 120,ALLEGRO_ALIGN_CENTER,
        "X%d",cant_vida); //Se muestran la cantidad de vidas restantes 
        al_flip_display();
        al_rest(1.0);//Se muestra por 1 segundos 
    }
}



/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
 
 /*FUNCIÓN SPRITE_GRAB: Dibuja la imagen en el bitmap*/
static ALLEGRO_BITMAP* sprite_grab(int x, int y, int w, int h,int foto)
{
    ALLEGRO_BITMAP *sprites;
    
    if (foto == 1)                                          				//Imagen: primer sprite
    {
        sprites  = al_load_bitmap("frogger_sprites.png");
    }   
    else                                                    				//Imagen: segundo sprite
    {               
         sprites  = al_load_bitmap("death.png");        
    }
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sprites, x, y, w, h);  	//Se crea la imagen en el bitmap 
    return sprite;
}

/*FUNCIÓN DRAW_OBJ:  Dibuja un objeto por vez con su imagen correspondiente*/
static void draw_obt( int16_t x, int16_t y,ALLEGRO_BITMAP* objbit ,int typeobj, int16_t width)
{
    if (typeobj == 0)             //Si el objeto es un auto, se dibuja un auto
    {
        if ((y/PASOS) %2 == 0)      //Si se mueve de izquierda a derecha 
        {
            al_draw_scaled_bitmap(objbit,
            0, 0, al_get_bitmap_width(objbit), al_get_bitmap_height(objbit), 
            x,y, width,PASOS, //Se indica el tamaño de la imagen
            ALLEGRO_FLIP_HORIZONTAL); //Se da vuelta la imagen 
        }
        else                        //Si se mueve de derecha a izquierda 
        {
            al_draw_scaled_bitmap(objbit,
            0, 0, al_get_bitmap_width(objbit), al_get_bitmap_height(objbit), 
            x,y, width,PASOS, //Se indica el tamaño de la imagen
            0);
        }       
    }
    else                          //Si el objeto es un tronco, se dibuja un tronco
    {    
       
        al_draw_scaled_bitmap(objbit,
        0, 0, al_get_bitmap_width(objbit), al_get_bitmap_height(objbit), 
        x,y, width,PASOS, //Se indica el tamaño de la imagen
        0);
    } 
}
