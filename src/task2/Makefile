CXX = gcc
CXX_FLAGS = -pedantic -Wall -Werror -rdynamic
CXX_OBJ_LIB_FLAGS = -c -pedantic -Wall -Werror -fpic
CXX_LIB_FLAGS = -shared 
NAME = lab5_t2
NAME_LSQR = libsquarer.so
NAME_LSQT = libsquaret.so
NAME_LTRB = libtranslationb.so
NAME_LTRT = libtranslationt.so
DIR = ../lib

all: square_r translation_b square_t translation_t
	export DYLD_LIBRARY_PATH=.
	$(CXX) $(CXX_FLAGS) lab5_t2.c -o $(NAME) -lsquarer -lsquaret -ltranslationb -ltranslationt
translation_b: translation_b.o
	$(CXX) $(CXX_LIB_FLAGS) -o $(NAME_LTRB) translation_b.o
translation_b.o: 
	$(CXX) $(CXX_OBJ_LIB_FLAGS) $(DIR)/translation_b.c
square_r: square_r.o
	$(CXX) $(CXX_LIB_FLAGS) -o $(NAME_LSQR) square_r.o
square_r.o:
	$(CXX) $(CXX_OBJ_LIB_FLAGS) $(DIR)/square_r.c
translation_t: translation_t.o
	$(CXX) $(CXX_LIB_FLAGS) -o $(NAME_LTRT) translation_t.o
translation_t.o: 
	$(CXX) $(CXX_OBJ_LIB_FLAGS) $(DIR)/translation_t.c
square_t: square_t.o
	$(CXX) $(CXX_LIB_FLAGS) -o $(NAME_LSQT) square_t.o
square_t.o:
	$(CXX) $(CXX_OBJ_LIB_FLAGS) $(DIR)/square_t.c
clean:
	rm -f *.o *.so $(NAME)