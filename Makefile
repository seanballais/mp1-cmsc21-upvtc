all:
	gcc -c -Wall -Werror -fpic lib/cs50/cs50.c -o lib/cs50.a # Compile the CS50 library first
	mkdir -p lib/include/
	cp lib/cs50/cs50.h lib/include/cs50.h
	cd ../../
	make app

app:
	mkdir -p bin # Now compile the application
	clang src/view/main.c src/view/HandleInputView.c src/view/DisplayView.c src/model/StudentModel.c -o bin/gradingbook lib/cs50.a
