all:
	gcc -c -Wall -Werror -fpic lib/cs50/cs50.c -o lib/cs50.a # Compile the CS50 library first
	chmod +x compile_jansson.sh
	./compile_jansson.sh
	cd ../../
	make app

app:
	mkdir -p bin # Now compile the application
	clang src/view/main.c src/view/HandleInputView.c src/view/DisplayView.c -o bin/gradingbook lib/cs50.a lib/libjansson.a
	rm StudentInfo.json SubjectCriteria.json SubjectRange.json
	echo "{ \"student\" {} }" >> StudentInfo.json
	echo "{ \"subject\" {} }" >> SubjectCriteria.json
	echo "{ \"subject\" {} }" >> SubjectRange.json
