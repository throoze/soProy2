# Universidad Simón Bolívar
# Departamento de Computación y Tecnología de la Información
# CI-3825  --  Sistemas Operativos I
# Prof.: Yudith Cardinale
# Proyecto 2: Comunicación entre procesos
# Grupo 26
# Autores: Victor De Ponte, 05-38087
#	       Isaac Lopez, 07-41120
# Archivo: Makefile


EXE1 = UsoDisco
EXE2 = job

LIBS = almacenamiento.h misc.h
LIBO = almacenamiento.o misc.o

LIBSJ = almacenamiento.h misc.h
LIBOJ = almacenamiento.o misc.o

OBJ1 = main.o ${LIBO}
OBJ2 = job.o ${LIBOJ}

# CFLAGS = -w
CFLAGS = 

all: ${EXE1} ${EXE2}

${EXE1}: ${OBJ1}
	gcc ${CFLAGS} ${OBJ1} -o ${EXE1}

${EXE2}: ${OBJ2}
	gcc ${CFLAGS} ${OBJ2} -o ${EXE2}

main.o: main.c main.h ${LIBS}
	gcc ${CFLAGS} -c main.c

job.o: job.c job.h ${LIBSJ}
	gcc ${CFLAGS} -c job.c

misc.o: misc.c misc.h
	gcc ${CFLAGS} -c misc.c

almacenamiento.o: almacenamiento.c almacenamiento.h
	gcc ${CFLAGS} -c almacenamiento.c

clean:
	makeclean.sh

check-syntax:
	gcc -o nul -Wall -S ${CHK_SOURCES}

