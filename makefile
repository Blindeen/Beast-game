CFLAGS = -Wall -pedantic
LDFLAGS = -lm -lncurses -lpthread

SRC_DIR = src
BUILD_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))
EXEC = Beasts

all: $(BUILD_DIR) $(EXEC)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(EXEC): $(OBJ)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS)

build/%.o: src/%.c
	gcc $(CFLAGS) -o $@ -c $<

.PHONY: clean run

clean:
	rm -rf $(BUILD_DIR) $(EXEC)

run: $(EXEC)
	./$(EXEC)
