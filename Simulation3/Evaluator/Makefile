CC := gcc
CFLAGS := -O3
CPPFLAGS = -I${MIKENET_DIR}/include -I../../headers -I../Model/
LDFLAGS := -L${MIKENET_DIR}/lib/$(shell uname -m)
LDLIBS := -lmikenet -lm

PREFIX ?= evaluator_all

EXE_DIR := bin
EXE_ACCU := $(EXE_DIR)/$(PREFIX)
EXE_DOL := $(EXE_DIR)/$(PREFIX)_lesion

SRC_ACCU := $(PREFIX).c
SRC_DOL := $(PREFIX)_lesion.c

.PHONY: all
all: $(EXE_ACCU) $(EXE_DOL) ## build all the executable files

.PHONY: accuracy
accuracy: $(EXE_ACCU)      ## build executable for accuracy evaluation
$(EXE_ACCU): $(SRC_ACCU)
	@mkdir -p $(@D)
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

.PHONY: dol
dol: $(EXE_DOL)      ## build executable for division of labour
$(EXE_DOL): $(SRC_DOL)
	@mkdir -p $(@D)
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

.PHONY: clean
clean:  ## delete all the executable files and object files
	-@$(RM) -rv $(EXE_ACCU) $(EXE_DOL)

.PHONY: help
help:   ## print this help message
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) \
	| awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36mmake %-20s\033[0m %s\n", $$1, $$2}'