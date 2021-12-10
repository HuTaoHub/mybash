objects=main.o mybash.o 

mybash:$(objects)
	gcc -o mybash $(objects)

$(objects): mybash.h main.o mybash.o

.PHONY:clean
clean:
	rm mybash $(objects)