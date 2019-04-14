CFLAGS_BASE = -Wall -Werror -pedantic

PROJ_DIR = clistlib
CLIST_HDRS_DIR = $(PROJ_DIR)/include
CLIST_SRC_DIR = $(PROJ_DIR)/src
CLIST_OBJ_DIR = $(PROJ_DIR)/obj
CLIST_BIN_DIR = $(PROJ_DIR)/bin
CLIST_LIB = $(CLIST_BIN_DIR)/libclist.a

CLIST_HDRS = $(shell find $(CLIST_HDRS_DIR) -iname "*.h")
CLIST_SRCS = $(shell find $(CLIST_SRC_DIR) -iname "*.c")
CLIST_OBJS = $(subst $(CLIST_SRC_DIR),$(CLIST_OBJ_DIR),$(CLIST_SRCS:.c=.o))

CLIST_INCLUDE = -I$(CLIST_HDRS_DIR)

.PHONY: all test test_valg clean

#
# By default only create the library
#
all: $(CLIST_LIB)

$(CLIST_LIB): CFLAGS = $(CFLAGS_BASE) -ansi
$(CLIST_LIB): $(CLIST_OBJS)
	@mkdir -p $(@D)
	ar rcs $@ $^

$(CLIST_OBJ_DIR)/%.o: $(CLIST_SRC_DIR)/%.c $(CLIST_HDRS)
	@echo $@
	@mkdir -p $(@D)
	$(CC)  -o $@  -c $<  $(CFLAGS)  $(CLIST_INCLUDE)  



#
# Some testing scripts
#

TEST_BUILD_DIR = test/bin
TEST_SRC_DIR = test/src
TEST_LIB_DIR = test/minunit

TEST_EXE = $(TEST_BUILD_DIR)/test_clist
TEST_SRCS = $(shell find $(TEST_SRC_DIR) -iname "*.c")

TEST_INCLUDES = $(CLIST_INCLUDE)  -I$(TEST_LIB_DIR)

test: $(TEST_EXE)
	$(TEST_EXE)

test_valg: $(TEST_EXE)
	valgrind --leak-check=full --error-exitcode=2 $(TEST_EXE)

$(TEST_EXE): CFLAGS = $(CFLAGS_BASE) -g  # Tests should be compiled without ansi
$(TEST_EXE): $(TEST_SRCS) $(CLIST_HDRS) $(CLIST_LIB)
	@mkdir -p $(@D)
	$(CC)  -o $@  $(TEST_INCLUDES)  $(TEST_SRCS)  -L $(CLIST_BIN_DIR) -lclist  $(CFLAGS)

#
# Let's start over
#
clean:
	rm -rf $(TEST_BUILD_DIR)
	rm -rf $(CLIST_OBJ_DIR)
	rm -rf $(CLIST_BIN_DIR)
	make -C example clean