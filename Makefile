CC = gcc
CFLAGS = -Wall
INCDIR = -I./include/

LIBDIR = ./lib
SRCDIR = ./src
OBJDIR = ./obj

LIB = $(LIBDIR)/cwdatastruct.a
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))


all: $(LIB)

$(LIB): $(LIBDIR) $(OBJS)
	ar -rc $@ $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(OBJDIR)
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

clean:
	rm -r $(OBJDIR)/* $(LIBDIR)/*

$(OBJDIR):
	mkdir $@

$(LIBDIR):
	mkdir $@
