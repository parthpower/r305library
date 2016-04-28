all:r305Parser
	gcc test.c r305Parser.o -g -o test.exe

test_avr:test_avr.c r305Parser
	avr-gcc -mmcu=atmega16 Os test_avr.c o test_avr.o
	avr-objcopy -j .text -j .data -O ihex  test_avr.o  test_avr.hex

r305Parser:r305Parser.c
	gcc -c -g r305Parser.c

doc:doxy.Doxyfile
	doxygen doxy.Doxyfile

clean:
	rm *.o 

