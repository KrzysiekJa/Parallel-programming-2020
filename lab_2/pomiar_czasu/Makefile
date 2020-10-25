# kompilator c
CCOMP = gcc

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

AR = ar crs


pomiar_czasu: pomiar_czasu.o pomiar_czasu.h 
	$(AR) libpomiar_czasu.a pomiar_czasu.o 

pomiar_czasu.o: pomiar_czasu.c pomiar_czasu.h 
	$(CCOMP) -c $(OPT) pomiar_czasu.c
