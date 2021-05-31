SRC_DIR=.
OBJ_DIR=./obj
BIN_DIR=./bin

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
BINS := $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR/%.o))

CXX=g++
CXXFLAGS= -std=c++2a -Wall -o=bin
LDFLAGS=
# CXX=icpc
# -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk

# if no .DEFAULT it runs first target
all: $(BINS) 	
	@:

run: $(BIN_DIR)/$(basename $(filter-out run,$(MAKECMDGOALS)))
	@$(BIN_DIR)/$(basename $(filter-out $@,$(MAKECMDGOALS)))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/%: $(OBJ_DIR)/%.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# even if all run clean filename exists
.PHONY:	all run clean

# keep intermediate files
.PRECIOUS:	$(OBJ_DIR)/%.o

clean:
	rm -r $(BIN_DIR) $(OBJ_DIR)
