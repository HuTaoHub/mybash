objects=main.o mybash.o 

mybash:$(objects)
	gcc -o mybash $(objects)

$(objects): mybash.h main.c mybash.c

.PHONY:clean
clean:
	rm -f mybash $(objects)