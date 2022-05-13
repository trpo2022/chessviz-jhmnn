APP = chessviz

SRC = src
OBJ = obj
BIN = bin
CHESSVIZ = chessviz
LIBCHESSVIZ = libchessviz
TEST = test

SRC_EXT = c
OBJ_EXT = o
LIB_EXT = a

APP_SRC = $(shell find $(SRC)/$(CHESSVIZ) -name "*.$(SRC_EXT)")
APP_OBJ = $(APP_SRC:$(SRC)/%.$(SRC_EXT)=$(OBJ)/$(SRC)/%.$(OBJ_EXT))
APP_BIN = $(BIN)/$(APP)

LIB_CHESSVIZ_SRC = $(shell find $(SRC)/$(LIBCHESSVIZ) -name "*.$(SRC_EXT)")
LIB_CHESSVIZ_OBJ = $(LIB_CHESSVIZ_SRC:$(SRC)/%.$(SRC_EXT)=$(OBJ)/$(SRC)/%.$(OBJ_EXT))
LIB_CHESSVIZ = $(OBJ)/$(SRC)/$(LIBCHESSVIZ)/$(LIBCHESSVIZ).$(LIB_EXT)

TEST_SRC = $(shell find $(TEST) -name "*.$(SRC_EXT)")
TEST_OBJ = $(TEST_SRC:$(TEST)/%.$(SRC_EXT)=$(OBJ)/$(TEST)/%.$(OBJ_EXT))
TEST_BIN = $(BIN)/$(APP)-$(TEST)


DEPS = $(APP_OBJ:.$(OBJ_EXT)=.d) $(TEST_OBJ:.$(OBJ_EXT)=.d)

-include $(DEPS)

CFLAGS = -Wall -Werror
CPPFLAGS = -I $(SRC) -MMD
CPPFLAGS_TEST = -I thirdparty $(CPPFLAGS)
LIBFLAGS = -L $(OBJ)/$(SRC)/$(LIBCHESSVIZ) -lchessviz

.PHONY: all test clean run

all: $(APP_BIN)

$(APP_BIN): $(APP_OBJ) $(LIB_CHESSVIZ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LIBFLAGS)

$(OBJ)/$(SRC)/$(LIBCHESSVIZ)/%.$(OBJ_EXT): $(SRC)/$(LIBCHESSVIZ)/%.$(SRC_EXT)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(LIB_CHESSVIZ): $(LIB_CHESSVIZ_OBJ)
	ar rcs $@ $^

$(OBJ)/$(SRC)/$(CHESSVIZ)/%.$(OBJ_EXT): $(SRC)/$(CHESSVIZ)/%.$(SRC_EXT)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(TEST_BIN): $(TEST_OBJ) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS_TEST) $^ -o $@

$(OBJ)/$(TEST)/%.$(OBJ_EXT): $(TEST)/%.$(SRC_EXT)
	$(CC) -c $(CFLAGS) $(CPPFLAGS_TEST) $< -o $@

clean:
	$(RM) $(APP_OBJ) $(LIB_CHESSVIZ_OBJ) $(LIB_CHESSVIZ) $(TEST_BIN) $(TEST_OBJ) $(DEPS)

test: $(TEST_BIN)
	./$(TEST_BIN)

run: $(APP_BIN)
	./$(APP_BIN)
