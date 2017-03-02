
TARGET = libwslay_websocket.so 

INC_DIR+=./ 
SOURCE_DIR=./
SOURCE_DIR+=./nettle_lib

CFLAGS += -g -O2 -I$(INC_DIR) 

SOURCE_TYPE=.c
HEADER_TYPE=.h

SOURCES=$(foreach d,$(SOURCE_DIR),$(wildcard $(addprefix $(d)/*,$(SOURCE_TYPE))))
OBJS=$(addsuffix .o, $(basename $(SOURCES)))


.PHONY:all clean 

all:$(TARGET)

%.o:%.c
	@echo [Compiling...] $<
	@$(CC) $(CPPFLAGS) $(CFLAGS) -fPIC -c $< -o $@ 

$(TARGET):$(OBJS)
	@echo [Linking...] $<
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJS) -shared -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)
