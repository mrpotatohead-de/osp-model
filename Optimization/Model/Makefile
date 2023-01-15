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

CPPFLAGS_OPENMP = -I${MIKENET_DIR}/include -I../../headers -fopenmp
LDFLAGS_OPENMP := -L${MIKENET_DIR}/lib/$(shell uname -m)/openmp
LDLIBS_OPENMP := -lmikenet -lm

CPPFLAGS_BLIS = -I${MIKENET_DIR}/include -I../../headers -I/home/chingenkuo/ce_ws/blis/include/zen2
LDFLAGS_BLIS := -L${MIKENET_DIR}/lib/$(shell uname -m)/blis -L/home/chingenkuo/ce_ws/blis/lib/zen2
LDLIBS_BLIS := -lmikenet -lm

CC_CUDA := nvcc
CFLAGS_CUDA := 
CPPFLAGS_CUDA = -I/home/nm6114083/ching_ws/mikenet-gpu/include -I../../headers
LDFLAGS_CUDA := -L/home/nm6114083/ching_ws/mikenet-gpu/lib/$(shell uname -m)/cuda
LDLIBS_CUDA := -lmikenet -lm  -lcublas

EXE_DIR := bin
EXE_RAW := $(EXE_DIR)/eng_oral_raw
EXE_OPT := $(EXE_DIR)/eng_oral_opt
EXE_OPENMP := $(EXE_DIR)/eng_oral_openmp
EXE_BLIS := $(EXE_DIR)/eng_oral_blis
EXE_CUDA := $(EXE_DIR)/eng_oral_cuda

SRC := reading_model_recur50_randcon.c eng_oral.c

.PHONY: all
all: raw opt openmp blis cuda## build all the executable files

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

.PHONY: openmp
openmp: $(EXE_OPENMP)		## build executable for english oral experiminet with openMP
$(EXE_OPENMP): $(SRC)
	@mkdir -p $(@D)
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS_OPENMP) $(LDFLAGS_OPENMP) $(LDLIBS_OPENMP)

.PHONY: blis
blis: $(EXE_BLIS)		## build executable for english oral experiminet with AMD BLIS
$(EXE_BLIS): $(SRC)
	@mkdir -p $(@D)
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS_BLIS) $(LDFLAGS_BLIS) $(LDLIBS_BLIS) /home/chingenkuo/ce_ws/blis/lib/zen2/libblis.a
    
.PHONY: cuda
cuda: $(EXE_CUDA)		## build executable for english oral experiminet with cuBLAS
$(EXE_CUDA): $(SRC)
	@mkdir -p $(@D)
	$(CC_CUDA) -o $@ $^ $(CFLAGS_CUDA) $(CPPFLAGS_CUDA) $(LDFLAGS_CUDA) $(LDLIBS_CUDA)

.PHONY: clean
clean:  ## delete all the executable files and object files
	-@$(RM) -rv $(EXE_RAW) $(EXE_OPT) $(EXE_OPENMP) $(EXE_BLIS) $(EXE_CUDA)

.PHONY: help
help:   ## print this help message
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) \
	| awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36mmake %-20s\033[0m %s\n", $$1, $$2}'
