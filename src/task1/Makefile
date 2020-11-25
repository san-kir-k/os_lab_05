CXX = gcc
CXX_FLAGS = -pedantic -Wall -Werror -L .
CXX_OBJ_LIB_FLAGS = -c -pedantic -Wall -Werror -fPIC
CXX_LIB_FLAGS = -shared 
NAME = lab5_t1
NAME_LSQ = libsrt.so
NAME_LTR = libtrb.so
DIR = ../lib

all: square_r translation_b
	export DYLD_LIBRARY_PATH=.
	$(CXX) $(CXX_FLAGS) lab5_t1.c -o $(NAME) -lsrt -ltrb

translation_b: translation_b.o
	$(CXX) $(CXX_LIB_FLAGS) -o $(NAME_LTR) translation_b.o
translation_b.o: 
	$(CXX) $(CXX_OBJ_LIB_FLAGS) $(DIR)/translation_b.c

square_r: square_r.o
	$(CXX) $(CXX_LIB_FLAGS) -o $(NAME_LSQ) square_r.o
square_r.o:
	$(CXX) $(CXX_OBJ_LIB_FLAGS) $(DIR)/square_r.c
	
clean:
	rm -f *.o *.so $(NAME)