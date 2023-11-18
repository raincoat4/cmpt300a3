
test:
	gcc -c avltree.c tree-test.c
	gcc -o test avltree.o tree-test.o

clean:
	rm *.o test a.out