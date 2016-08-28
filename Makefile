#----------------------------------------------------------------------------
# Build process stream cipher A5/1 
#
# Coder - Nahit Pawar
#         PhD Indian Institute of Technology Bombay, India
# Starting Date  - 10/01/13
# Last Modified  - 04/08/13
#
#----------------------------------------------------------------------------

CPP    = g++ -std=c++11
CFLAGS = -g -Wall -o3
RM     = rm

EXEC   = a5
OBJECTS = \
    main.o \
	a5_utils.o \
	a5_init.o

.PHONEY: clean
.PHONEY: all
.PHONEY: compile
.PHONEY: acknowledge


all: $(OBJECTS) compile acknowledge

main.o : main.cpp
	$(CPP) -g -c $^

a5_utils.o : a5_utils.cpp
	$(CPP) -g -c $^

a5_init.o : a5_init.cpp
	$(CPP) -g -c $^

compile:
	$(CPP) $(CFLAGS) $(OBJECTS) -o $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

acknowledge:
	@echo " "
	@echo " "
	@echo "Perfecto! Compilation Done Successfully........"
	@echo " "
	@echo " "
