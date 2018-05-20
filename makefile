FORMULAPATH = ~/formula
AVRCOMP = avr-gcc -c -std=c++11 -mmcu=at90can128
AVRLINK = avr-gcc -o $(NAME) -mmcu=at90can128
NAME = bmstempboard

bmstempboard: main.o bms_can.o adc.o cpfecanlib.o
	$(AVRLINK) main.o bms_can.o adc.o cpfecanlib.o
	# @rm -f *.o

cpfecanlib.o: $(FORMULAPATH)/AVRLibrary/AVRLibrary/CPFEAVRAnalog.cpp $(FORMULAPATH)/AVRLibrary/AVRLibrary/CPFEAVRAnalog.h $(FORMULAPATH)/AVRLibrary/AVRLibrary/CPFECANLib.cpp $(FORMULAPATH)/AVRLibrary/AVRLibrary/CPFECANLib.h
	# $(AVRCOMP) -o cpfeavranalog.o $(FORMULAPATH)/AVRLibrary/AVRLibrary/CPFEAVRAnalog.cpp # not necessary here
	$(AVRCOMP) -o cpfecanlib.o $(FORMULAPATH)/AVRLibrary/AVRLibrary/CPFECANLib.cpp # backwards compatible, thanks hunter

main.o: main.cpp bms_can.h adc.h # avrlibrary
	$(AVRCOMP) -I $(FORMULAPATH)/AVRLibrary main.cpp

bms_can.o: bms_can.cpp bms_can.h
	$(AVRCOMP) -I $(FORMULAPATH)/AVRLibrary bms_can.cpp

adc.o: adc.cpp adc.h
	$(AVRCOMP) adc.cpp

flash:
	avrdude -c avrispmkII -pat90can128 -U flash:w:$(NAME):e # -U hfuse:w:0x5C:m # gotta check this

clean:
	@rm -f *.o $(NAME)
