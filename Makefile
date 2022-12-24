scanner: *.c
	gcc -o main.exe -g *.c
	
clean:
	rm -f scanner *.o