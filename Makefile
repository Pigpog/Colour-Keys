# Tox key-image maker/extractor makefile

all: extract_keyimg make_keyimg keyimgtest dotest

extract_keyimg: extract_keyimg.c
	gcc -c -ggdb -Wall -Werror extract_keyimg.c

make_keyimg: make_keyimg.c
	gcc -c -ggdb -Wall -Werror make_keyimg.c

keyimgtest: keyimgtest.c
	gcc -c -ggdb -Wall -Werror keyimgtest.c

dotest:
	gcc -ggdb -Wall -Werror extract_keyimg.o make_keyimg.o keyimgtest.o -o dotest

clean:
	rm -f make_keyimg extract_keyimg keyimgtest dotest *.o a.out