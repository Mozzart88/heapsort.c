NAME := cunit
TARGET := $(NAME).run
TEST_LIB_NAME := cu_test
TEST_LIB_TARGET := lib$(TEST_LIB_NAME).so
SHARED_LIB_NAME := $(NAME)
SHARED_LIB_TARGET := lib$(SHARED_LIB_NAME).so

PWD := $(shell pwd)
not_build_targets := clean fclean tclean aclean $(SHARED_LIB_TARGET)
ifeq ($(filter $(MAKECMDGOALS), $(not_build_targets)), )
ifndef path
$(error Please define path)
endif

ifndef lib
$(error Please define lib)
endif
endif

USER_PATH := $(path)
USER_LIB_PATH := $(USER_PATH)
USER_LIB_NAME := $(lib)
USER_LIB_TARGET := lib$(lib).so

ifdef lib_dir
USER_LIB_PATH := $(USER_PATH)/$(lib_dir)
endif

SRC_DIR := src
OBJ_DIR := obj
LIB_DIR := lib

LIB_PATH := $(PWD)/$(LIB_DIR)
SRC := $(SRC_DIR)/cunit.c 
SHARED_SRC := $(SRC_DIR)/tests.c $(SRC_DIR)/common.c $(SRC_DIR)/err.c
OBJ := $(notdir $(SRC:.c=.o))
SHARED_OBJ := $(notdir $(SHARED_SRC:.c=.o))
ifeq ($(filter $(MAKECMDGOALS), $(not_build_targets)), )
TEST_SRC := $(shell find $(USER_PATH) -path '*/test[s]/*.c' -o -name 'test_*.c' -o -name '*_test.c' -not -path '*/cunit/*')
endif
TEST_OBJ := $(notdir $(TEST_SRC:.c=.o))
TEST_DIR := $(dir $(TEST_SRC))

CC := gcc
CFLAGS := -Wall -Wextra -Werror
CFLAGS += -I $(PWD)/include/
LDLIBS := -L $(LIB_PATH) -l$(TEST_LIB_NAME)

LDLIBS_TEST := -L $(LIB_PATH) -l$(SHARED_LIB_NAME)
LDLIBS_TEST += -l$(USER_LIB_NAME)

CFLAGS_TEST := $(CFLAGS) -I $(USER_PATH)/include

ifeq ($(shell echo $$DOCKER), 1)
debug = 1
LDLIBS := $(LIB_PATH)/$(TEST_LIB_TARGET)
LDLIBS_TEST := $(LIB_PATH)/$(USER_LIB_TARGET) $(LIB_PATH)/$(SHARED_LIB_TARGET)
endif
LDLIBS += $(LDLIBS_TEST)

ifdef debug
CFLAGS += -g
CFLAGS_TEST += -g
else
CFLAGS += -O3
CFLAGS_TEST += -O3
endif
USER_LIB_TARGET_PATH := $(USER_LIB_PATH)/$(USER_LIB_TARGET)

vpath %.c $(SRC_DIR) $(TEST_DIR)
vpath %.o $(OBJ_DIR)
vpath %.so $(LIB_DIR)

all: $(TARGET)

$(OBJ):%.o:%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS)  -c $< -o $(OBJ_DIR)/$@ 

$(SHARED_OBJ) $(TEST_OBJ):%.o:%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS_TEST)  -c $< -o $(OBJ_DIR)/$@ 

$(TARGET): $(OBJ) | $(TEST_LIB_TARGET)
	$(CC) $(CFLAGS)  -o $(TARGET) $(LDLIBS) $(addprefix $(OBJ_DIR)/, $(OBJ))

$(SHARED_LIB_TARGET): $(SHARED_OBJ) | $(USER_LIB_TARGET)
	$(CC) $(CFLAGS_TEST)  -shared -o $(LIB_DIR)/$(SHARED_LIB_TARGET) $(addprefix $(OBJ_DIR)/, $(SHARED_OBJ))

$(TEST_LIB_TARGET): $(TEST_OBJ) | $(SHARED_LIB_TARGET)
	$(CC) $(CFLAGS_TEST)  -shared -o $(LIB_DIR)/$(TEST_LIB_TARGET) $(LDLIBS_TEST) $(addprefix $(OBJ_DIR)/, $(TEST_OBJ))
	
$(USER_LIB_TARGET): | $(LIB_DIR)
	$(shell ln -s $(USER_LIB_TARGET_PATH) $(LIB_DIR)/$(USER_LIB_TARGET))
	
$(OBJ_DIR):
	$(shell mkdir -p $(OBJ_DIR))

$(LIB_DIR):
	$(shell mkdir -p $(LIB_DIR))

run: | $(TARGET) 
	./$(TARGET)

test: $(SHARED_LIB_TARGET) $(TEST_LIB_TARGET) run

clean:
	/bin/rm -rf $(OBJ_DIR)

tclean: 
	/bin/rm -f $(LIB_DIR)/$(TEST_LIB_TARGET)

fclean: clean
	/bin/rm -f $(TARGET)

aclean: fclean
	/bin/rm -fr $(LIB_DIR)

re: aclean all

.PHONY: test get_dir aclean

# .SILENT: test run $(USER_LIB_TARGET_PATH) $(LIB_DIR)

