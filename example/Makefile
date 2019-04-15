
.PHONY: all

all: basic_example classic_example

clean:
	rm -f basic_example classic_example

basic_example: basic_example.c
	@make -C ..
	$(CC) -o $@ $<  -I../clistlib/include  -L ../clistlib/bin -lclist

classic_example: classic_example.c
	@make -C ..
	$(CC) -o $@ $<  -I../clistlib/include  -L ../clistlib/bin -lclist
