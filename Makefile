# Makefile usado para compilação do programa

all:
	g++ src/*.cpp -Iinclude -o projeto

clean:
	rm -f projeto