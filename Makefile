all:
	gcc -g -o child child.c
	gcc -g -o parent parent.c

parent:
	gcc -o parent parent.c

child:
	gcc -o child child.c

clean:
	rm -rf child
	rm -rf parent
	rm -rf *.o
	rm test.txt
	rm parent.txt

run:
	./parent
