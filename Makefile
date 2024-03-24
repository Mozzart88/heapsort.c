
S := src/
NAME := heapsort
SS := $(S)$(NAME).c
H := -I include/
LIB := lib$(NAME).a
CC := gcc
OCF := -O3 -Wall -Wextra -Werror
GCF := -g -Wall -Wextra -Werror
ifeq ($(shell echo $$DOCKER), 1)
debug = 1
endif
ifdef debug
CF := $(GCF)
else
CF := $(OCF)
endif
ifeq ($(shell echo $$DOCKER), 1)
TEST = $(CC) $(CF) $(H) -o test.run test/main.c $(LIB)
else
TEST = $(CC) $(CF) $(H) -L ./ -l$(NAME) -o test.run test/main.c
endif

all: $(LIB)

%.o: %.c
	$(CC) $(CF) $(H) -c -o $@ $<

$(LIB): $(SS:.c=.o)
	ar rc $(LIB) $(SS:.c=.o) 
	
test: $(LIB) 
	$(TEST)
	./test.run

clean:
	/bin/rm -f $(SS:.c=.o)

fclean: clean
	/bin/rm -f $(LIB)

tclean: fclean
	/bin/rm -f test.run test.run.dSYM

re: fclean all

.PHONY: test
