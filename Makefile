CFLAGS = -Wall -g -pedantic

CLIST_HDRS_DIR = clistlib/include
CLIST_SRC_DIR = clistlib/src
CLIST_OBJ_DIR = clistlib/obj

CLIST_HDRS = $(shell find $(CLIST_HDRS_DIR) -iname "*.h")
CLIST_SRCS = $(shell find $(CLIST_SRC_DIR) -iname "*.c")

CLIST_OBJS = $(subst $(CLIST_SRC_DIR),$(CLIST_OBJ_DIR),$(CLIST_SRCS:.c=.o))

CLIST_INCLUDE = -I$(CLIST_HDRS_DIR)

TEST_BUILD_DIR = test/bin
TEST_SRC_DIR = test/src
TEST_LIB_DIR = test/minunit

TEST_EXE = $(TEST_BUILD_DIR)/test_clist
TEST_SRCS = $(shell find $(TEST_SRC_DIR) -iname "*.c")
TEST_OBJS = $(subst $(TEST_SRC_DIR),$(TEST_BUILD_DIR),$(TEST_SRCS:.c=.o))

TEST_INCLUDES = -I$(TEST_LIB_DIR)

.PHONY: all run_tests clean

all: run_tests

run_tests: $(TEST_EXE)
	@valgrind -v $(TEST_EXE)

$(TEST_EXE): $(TEST_OBJS) $(CLIST_OBJS) $(CLIST_HDRS)
	@mkdir -p $(@D)
	$(CC)  -o $@  $(TEST_OBJS)  $(CLIST_OBJS)  $(CFLAGS)

$(TEST_BUILD_DIR)/%.o: $(TEST_SRC_DIR)/%.c $(CLIST_HDRS)
	@echo $@
	@mkdir -p $(dir $@)
	$(CC)  -o $@  -c $<  $(CFLAGS)  $(CLIST_INCLUDE)  $(TEST_INCLUDES)

$(CLIST_OBJ_DIR)/%.o: $(CLIST_SRC_DIR)/%.c $(CLIST_HDRS)
	@echo $@
	@mkdir -p $(dir $@)
	$(CC)  -o $@  -c $<  $(CFLAGS)  $(CLIST_INCLUDE)  


clean:
	rm -rf $(TEST_BUILD_DIR)
	rm -rf $(CLIST_OBJ_DIR)