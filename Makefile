PWD := $(shell pwd)
NAME := heapsort
TARGET := lib$(NAME).so

OBJ_DIR := obj
SRC_DIR := src
LIB_DIR := lib

SRC := $(SRC_DIR)/heapsort.c 
OBJ := $(notdir $(SRC:.c=.o))


CC := gcc
CFLAGS := -Wall -Wextra -Werror
CFLAGS += -I $(PWD)/include/

ifeq ($(shell echo $$DOCKER), 1)
debug = 1
endif

ifdef debug
CFLAGS += -g
else
CFLAGS += -O3
endif

vpath %.c $(SRC_DIR)
vpath %.o $(OBJ_DIR)
vpath %.so $(LIB_DIR)

all: $(LIB_DIR) $(OBJ_DIR) $(TARGET)

$(OBJ):%.o:%.c
	$(CC) $(CFLAGS)  -c $< -o $(OBJ_DIR)/$@ 
	
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -shared -o $(LIB_DIR)/$(TARGET) $(addprefix $(OBJ_DIR)/, $(OBJ)) 
	
$(LIB_DIR):
	$(shell mkdir -p $(LIB_DIR))

$(OBJ_DIR):
	$(shell mkdir -p $(OBJ_DIR))

test: all
	make -C cunit test lib=$(NAME) path=$(PWD) lib_dir=$(LIB_DIR)

clean:
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	/bin/rm -rf $(LIB_DIR)

re: fclean all

.PHONY: test

.SILENT: test 
