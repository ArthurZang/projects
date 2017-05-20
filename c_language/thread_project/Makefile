
.PHONY: pthread libcommon

all:  libcommon pthread

pthread:
	gcc main.c -o pthread_demo -lpthread -lcommon -L./

libcommon:
	gcc -shared -o libcommon.so lib_common.c

clean:
	rm -rf pthread_demo *.o 
	rm -rf libcommon.so 
