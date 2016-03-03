all:
	clang --std=c11 -Wall -Werror -g -o bin/slambook src/slambook.c src/linked_list.c src/file_access.c src/slambook_funcs.c
