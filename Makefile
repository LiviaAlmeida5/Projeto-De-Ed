# Makefile usado para compilação do programa

all:
	g++ src/*.cpp -Iinclude -o programa

clean:
	rm -f programa