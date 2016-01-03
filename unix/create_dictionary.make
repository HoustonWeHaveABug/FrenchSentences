CREATE_DICTIONARY_C_FLAGS=-c -I/usr/include/libxml2 -O2 -Wall -Wextra -Waggregate-return -Wcast-align -Wcast-qual -Wconversion -Wformat=2 -Winline -Wlong-long -Wmissing-prototypes -Wmissing-declarations -Wnested-externs -Wno-import -Wpointer-arith -Wredundant-decls -Wreturn-type -Wshadow -Wstrict-prototypes -Wswitch -Wwrite-strings

create_dictionary.exe: create_dictionary.obj
	gcc -o create_dictionary.exe create_dictionary.obj -lxml2

create_dictionary.obj: ../src/create_dictionary.c create_dictionary.make
	gcc ${CREATE_DICTIONARY_C_FLAGS} -o create_dictionary.obj ../src/create_dictionary.c
