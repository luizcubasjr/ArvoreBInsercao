arvoreb.o: arvoreb.h arvoreb.c
	gcc -c arvoreb.h arvoreb.c 
	
arvoreb: arvore.o
	gcc arvoreb.o -o arvoreb
	
	