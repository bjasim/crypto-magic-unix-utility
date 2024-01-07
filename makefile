# Filename:    makefile
# Project:     cryptoMagic
# Author:      Bakr Jasim
# Date:        2022-01-22
# Description: This is the makefile for the cryptoMagic utility, and it includes all the dependencies and     
# their directory location for linking and compiling the code.

./bin/cryptoMagic: ./obj/cryptoMagic.o ./obj/main.o
	cc ./obj/cryptoMagic.o ./obj/main.o -o ./bin/cryptoMagic
	
	
./obj/cryptoMagic.o: ./src/cryptoMagic.c ./inc/cryptoMagic.h
	cc -c ./src/cryptoMagic.c -o ./obj/cryptoMagic.o
	
./obj/main.o: ./src/main.c ./inc/cryptoMagic.h
	cc -c ./src/main.c -o ./obj/main.o
	
all: ./bin/cryptoMagic

clean: 
	rm ./bin/*
	rm ./obj/*
