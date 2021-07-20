.SUFFIXES: .o .c 

.PHONY: TPFINAL
.PHONY: clean

CC = gcc

CFLAGS = -Wall  -D ALLEGRO

LDLIBS =  -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_image -lallegro_main -lallegro_memfile -lallegro_physfs -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro
ALLEGRO = obj.o colisiones.o rana.o allegro.o

main: $(ALLEGRO)
main.o: main.c allegro.c colisiones.c rana.c obj.c allegro.h rana.h colisiones.h obj.h
colisiones.o:   colisiones.c rana.c obj.c rana.h colisiones.h obj.h
colisiones.o:   colisiones.c rana.c obj.c rana.h colisiones.h obj.h
rana.o: rana.c rana.h 
allegro.o: allegro.c allegro.h
clean:
	$(RM) $(OBJALLEGRO) main
	
