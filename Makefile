all:
	gcc -c -Wall -Werror -fpic lib/cs50/cs50.c -o lib/cs50.a # Compile the library first
	mkdir -p bin # Now compile the application
	clang -Llib/ src/view/main.c src/view/HandleInputView.c src/view/DisplayView.c -o bin/gradingbook lib/cs50.a
