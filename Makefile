all:r305Parser
	gcc test.c r305Parser.o -g -o test.exe

r305Parser:r305Parser.c
	gcc -c -g r305Parser.c
doc:doxy.Doxyfile
	doxygen doxy.Doxyfile
clean:
	rm *.o 
	rm -rf ./html
