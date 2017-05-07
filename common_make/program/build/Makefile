

.PHONY: shared_lib static_lib hello_world hello_arthur

all: shared_lib static_lib hello_world hello_arthur
	@echo “Make build”
 
#processes libs


libs: static_lib shared_lib

static_lib:
	make -C static_lib

shared_lib:
	make -C shared_lib

processes: hello_world hello_arthur

hello_world:
	@echo “Make hello_world”
	make -C hello_world

hello_arthur:
	make -C hello_arthur








