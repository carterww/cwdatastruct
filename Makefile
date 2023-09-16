CC := gcc
CFLAGS = -Wall
INCLUDE = -I./include/

singlist: singlist.c
	$(CC) $(INCLUDE) -c singlist.c $(CFLAGS)

queue: queue.c singlist
	$(CC) $(INCLUDE) -c queue.c $(CFLAGS)

clean:
	rm -rf *.o
