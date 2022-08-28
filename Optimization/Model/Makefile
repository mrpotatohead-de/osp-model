CC := gcc
CFLAGS := -O3 -Wall

CPPFLAGS = -I${MIKENET_DIR}/include -I../../headers
LDFLAGS := -L${MIKENET_DIR}/lib/$(shell uname -m)
LDLIBS := -lmikenet -lm

CPPFLAGS_OPT = -I${MIKENET_DIR}/include -I../../headers -I${MKLROOT}/include
LDFLAGS_OPT := -L${MIKENET_DIR}/lib/$(shell uname -m)/mkl -L${MKLROOT}/lib/intel64
LDLIBS_OPT := \
	-lmikenet \
	-lmkl_intel_lp64 \
	-lmkl_sequential \
	-lmkl_core \
	-lm -lpthread -ldl

EXE_DIR := bin
EXE_RAW := $(EXE_DIR)/eng_oral_raw
EXE_OPT := $(EXE_DIR)/eng_oral_opt

SRC := reading_model_recur50_randcon.c eng_oral.c

.PHONY: all
all: raw opt  ## build all the executable files

.PHONY: raw
raw: $(EXE_RAW)		## build executable for english oral experiminet without optimization
$(EXE_RAW): $(SRC)
	@mkdir -p $(@D)
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

.PHONY: opt
opt: $(EXE_OPT)		## build executable for english oral experiminet with MKL optimization
$(EXE_OPT): $(SRC)
	@mkdir -p $(@D)
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS_OPT) $(LDFLAGS_OPT) $(LDLIBS_OPT)

.PHONY: clean
clean:  ## delete all the executable files and object files
	-@$(RM) -rv $(EXE_RAW) $(EXE_OPT)

.PHONY: help
help:   ## print this help message
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) \
	| awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36mmake %-20s\033[0m %s\n", $$1, $$2}'
