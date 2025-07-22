CC      ?= clang
CFLAGS  := -std=c11 -Wall -Wextra -O2
LDFLAGS :=

# enable sanitizers easily: `make SAN=1`
ifeq ($(SAN),1)
 CFLAGS += -fsanitize=address,undefined -g
 LDFLAGS+= -fsanitize=address,undefined
endif

SRC = mini_proto.c vuln_demo.c
BIN = vuln_demo.bin

all: $(BIN)

$(BIN): $(SRC) mini_proto.h
	$(CC) $(CFLAGS) $(SRC) -o $@ $(LDFLAGS)

clean:
	rm -f $(BIN)

.PHONY: all clean
