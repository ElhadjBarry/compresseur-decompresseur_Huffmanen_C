cc=gcc

huff:huffman.c 
	$(cc) -g -Wall huffman.c -o huff -lm

dhuff: conversions.o decompresseur.o
	$(cc) decompresseur.o conversions.o -o dhuff
decompresseur.o:decompresseur.c
	$(cc) -c decompresseur.c
conversion.o:conversions.c
	$(cc) -c conversions.c
