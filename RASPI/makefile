.SUFFIXES: .o .c 

.PHONY: TPFINAL
.PHONY: clean

CC = gcc

CFLAGS = -Wall  -D RASPI


RASPI = obj.o colisiones.o rana.o rpi_funs.o rpi_draw.o disdrv.o joydrv.o termlib.o

main: $(RASPI)
main.o: main.c rpi_funs.c colisiones.c rana.c obj.c rpi_draw.c   rana.h colisiones.h obj.h  rpi_funs.h rpi_draw.h disdrv.h joydrv.h termlib.h

colisiones.o:   colisiones.c rana.c obj.c rana.h colisiones.h obj.h
colisiones.o:   colisiones.c rana.c obj.c rana.h colisiones.h obj.h
rana.o: rana.c rana.h 
rpi_funs.o = rpi_funs.c rpi_funs.h
rpi_draw.o = rpi_draw.c rpi_draw.h 
clean:
	$(RM) $(RASPI) main
	
