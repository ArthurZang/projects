# common.mk
# This file is included in Makefile under each directory
#

ifeq ($(BUILD_DEBUG), 1)
	CFLAGS += -DDEBUG
else 
ifeq ($(BUILD_RELEASE),1)
	CFLAGS += -O2, -DNDEBUG
else
	CFLAGS += -O2 -DDEBUG
endif
endif

#global include path
INC_PATH = 


SRCS = $(wildcard $(SRC_DIR)/*.c)
#OBJS=$(addprefix $(OBJ_DIR)/, $(addsuffix .o,$(basename $(notdir $(SRCS)))))
OBJS= $(addsuffix .o,$(basename $(notdir $(SRCS))))

.PHONY:$(OBJS) clean 

ifeq ($(suffix $(PROGRAM)),)
$(PROGRAM):$(OBJS)
	@echo “compile program $@“
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
endif

ifeq ($(suffix $(PROGRAM)), .so)
$(PROGRAM):$(OBJS)
	@echo “compile library $@“
	$(CC) -shared $(CFLAGS) -o $@ $^
endif

ifeq ($(suffix $(PROGRAM)), .a)
$(PROGRAM):$(OBJS)
	@echo “compile library $@“
	$(AR) rcs  $@ $^
endif

#rule to build .o from .c
$(OBJS):%.o:$(SRC_DIR)/%.c
	@echo “compile $<“
	@$(CC) -c $(CFLAGS) -o $@ $<
	
	


