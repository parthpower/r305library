all:r305Parser test_exe test_avr 

test_exe:test.c r305Parser
	gcc test.c r305Parser.o -g --static -o test.exe

test_exe_ci:test.c r305Parser_ci
	gcc-mingw-w64 test.c r305Parser.o -g --static -o test.exe

test_avr:test_avr.c r305Parser_avr
	avr-gcc -g -mmcu=atmega32 -Os -c test_avr.c
	avr-gcc -g -mmcu=atmega32 -o test_avr.elf test_avr.o r305Parser.o
	avr-objdump -h -S test_avr.elf > test_avr.lst
	cat test_avr.lst

r305Parser:r305Parser.c
	gcc -c -g r305Parser.c

r305Parser_avr:r305Parser.c
	avr-gcc -mmcu=atmega32 -Os -c -g r305Parser.c

r305Parser_ci:r305Parser.c
	gcc-mingw-w64 -c -g r305Parser.c
	
doc:doxy.Doxyfile
	doxygen doxy.Doxyfile

clean:
	rm *.o *.lst *.elf *.exe

