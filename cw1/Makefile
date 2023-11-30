all: main.o
	gcc -std=c99 -o cw *.o
main.o: *.c
	gcc -c -std=c99 *.c
change_text.o: change_text.o change_text.h
	gcc -c -std=c99 change_text.c
cmps.o: cmps.c cmps.h
	gcc -c -std=c99 cmps.c
avg_len.o: avg_len.c avg_len.h
	gcc -c -std=c99 avg_len.c


clean:
	rm -rf *.o all