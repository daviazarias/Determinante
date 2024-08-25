NOME_PROJ=determinante

ARQS_C=$(wildcard ./codigos_fonte/*.c)

ARQS_H=$(wildcard ./codigos_fonte/*.h)

OBJ=$(subst .c,.o,$(subst _fonte,_objeto,$(ARQS_C)))

CC=gcc

FLAGS=-c            \
      -W            \
	  -Wall         \
      -ansi         \
      -pedantic 

all: cria_dir $(NOME_PROJ)

$(NOME_PROJ): $(OBJ)
	$(CC) $^ -lm -o $@ 

./codigos_objeto/main.o: ./codigos_fonte/main.c $(ARQS_H)
	$(CC) $< $(FLAGS) -o $@

./codigos_objeto/%.o: ./codigos_fonte/%.c ./codigos_fonte/%.h 
	$(CC) $< $(FLAGS) -o $@ 

cria_dir: 
	mkdir -p codigos_objeto

clean:
	rm -rf ./codigos_objeto/*.o *~ $(NOME_PROJ)
	rmdir codigos_objeto

.PHONY: all clean