CC = clang
CFLAGS = -Iinclude -g $(shell llvm-config --cflags)
LDFLAGS = $(shell llvm-config --ldflags --libs core)

SRCS = src/main.c
OBJS = $(SRCS:.c=.o)
EXEC = jocky

TOOL_SRC = tools/obfuscator.c
TOOL_EXEC = jocky-obfuscator

all: $(EXEC) $(TOOL_EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TOOL_EXEC): $(TOOL_SRC)
	$(CC) $(CFLAGS) $< -o $(TOOL_EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC) $(TOOL_EXEC)

.PHONY: all clean
