CC := gcc
CFLAGS := -O3
CPPFLAGS = -I${MIKENET_DIR}/include -I../../headers
LDFLAGS := -L${MIKENET_DIR}/lib/$(shell uname -m)
LDLIBS := -lmikenet -lm

PREFIX ?= eng

EXE_DIR := bin
EXE_ORAL := $(EXE_DIR)/$(PREFIX)_oral
EXE_READ_OS := $(EXE_DIR)/$(PREFIX)_OS_focused_reading
EXE_READ_OP := $(EXE_DIR)/$(PREFIX)_OP_focused_reading

SRC_ORAL := reading_model_recur50_randcon.c $(PREFIX)_oral.c
SRC_READ := reading_model_recur50_randcon.c $(PREFIX)_reading.c

.PHONY: all
all: $(EXE_ORAL) $(EXE_READ_OS) $(EXE_READ_OP)  ## build all the executable files

.PHONY: oral
oral: $(EXE_ORAL)      ## build executable for oral
$(EXE_ORAL): $(SRC_ORAL)
	@mkdir -p $(@D)
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

.PHONY: os-read
os-read: $(EXE_READ_OS)     ## build executable for OS focused reading
$(EXE_READ_OS): CPPFLAGS += -DOS -UOP
$(EXE_READ_OS): $(SRC_READ)
	@mkdir -p $(@D)
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

.PHONY: op-read
op-read: $(EXE_READ_OP)     ## build executable for OP focused reading
$(EXE_READ_OP): CPPFLAGS += -DOP -UOS
$(EXE_READ_OP): $(SRC_READ)
	@mkdir -p $(@D)
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

.PHONY: clean
clean:  ## delete all the executable files and object files
	-@$(RM) -rv $(EXE_ORAL) $(EXE_READ_OS) $(EXE_READ_OP)

.PHONY: help
help:   ## print this help message
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) \
	| awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36mmake %-20s\033[0m %s\n", $$1, $$2}'
