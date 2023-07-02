
TARGET= vec.out
CC= gcc
CFLAGS= -ansi -g -pedantic 
OBJS= Gvector.o GvectorTest.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
Gvector.o: Gvector.h Gvector.c
	$(CC) $(CFLAGS) -c Gvector.c
	
GvectorTest.o: GvectorTest.c Gvector.h 
	$(CC) $(CFLAGS) -c GvectorTest.c
	
	
	
clean:
	rm -f $(TARGET) $(OBJS)

