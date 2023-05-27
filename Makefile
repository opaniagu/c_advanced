# desde la linea de comandos, ejecutar:
# $ make target 
# por default busca el archivo Makefile
# se puede especificar con -f <makefile>
# make -f Makefile
# make -f mi_makefile

# target: prerequisites
# 	command
# 	command
# 	command

# target y prerequisites son archivos

all: bin/main

bin/main: build/main.o build/buffer.o build/todo.o
	gcc -Wall build/main.o build/buffer.o build/todo.o -o bin/main

build/main.o: src/main.c
	gcc -Wall -Iinclude -c src/main.c -o build/main.o

build/buffer.o: src/buffer.c
	gcc -Wall -Iinclude -c src/buffer.c -o build/buffer.o

build/todo.o: src/todo.c
	gcc -Wall -Iinclude -c src/todo.c -o build/todo.o

run:
# el @ para que no muestre por pantalla el comando a ejecutar
	@./bin/main

clean: 
	rm -f ./build/*.o
	rm -f ./bin/main

# le dice al make que estos nombres no son archivos
.PHONY: all run clean