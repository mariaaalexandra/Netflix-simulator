build: 
	gcc -g -Wall -o tema2 lista.c stiva.c coada.c tema2.c

.PHONY : clean
clean :
	rm -f tema2 *~