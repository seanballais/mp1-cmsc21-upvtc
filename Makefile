all:
	clang --std=c11 -Wall -Werror -g -o bin/gradebook src/gradebook.c src/linked_list.c src/file_access.c src/gradebook_funcs.c
