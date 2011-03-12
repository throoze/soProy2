# Universidad Simón Bolívar
# Departamento de Computación y Tecnología de la Información
# CI-3825  --  Sistemas Operativos I
# Prof.: Yudith Cardinale
# Proyecto 2: Comunicación entre procesos
# Grupo 26
# Autores:	Victor De Ponte, 05-38087
#	   	Isaac Lopez,	 07-41120

EXE1 = UsoDisco
EXE2 = job

LIBS = almacenamiento.h
LIBO = almacenamiento.o

OBJ1 = main.o ${LIBO}
OBJ2 = job.o ${LIBO}



# CFLAGS = -w
CFLAGS = 

all: ${EXE1} ${EXE2}

${EXE1}: ${OBJ1}
	gcc ${CFLAGS} ${OBJ1} -o ${EXE1}

${EXE2}: ${OBJ2}
	gcc ${CFLAGS} ${OBJ2} -o ${EXE2}

main.o: main.c main.h ${LIBS}
	gcc ${CFLAGS} -c main.c

almacenamiento.o: almacenamiento.c almacenamiento.h
	gcc ${CFLAGS} -c almacenamiento.c

job.o: job.c job.h ${LIBS}
	gcc ${CFLAGS} -c job.c

clean:
	rm *.o ${EXE1} ${EXE2}

check-syntax:
	gcc -o nul -Wall -S ${CHK_SOURCES}

