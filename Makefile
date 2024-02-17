CC = gcc


all: projekat

projekat:  projekat9.c
	$(CC)  -o grep projekat9.c
	

clean:
	rm projekat
