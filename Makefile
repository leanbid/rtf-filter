CC=g++
OPTIONS=$(-lboost_filesystem -lboost_program_options -o)
SOURCES=$(src/main.cpp src/rtf.cpp src/ccontrolword.cpp src/aux.cpp) 
EXECUTABLE=rtf-filter

all:
	$(CC) $(SOURCES) $(OPTIONS) $(EXECUTABLE)

install:
	cp $(EXECUTABLE) .......
	rm $(EXECUTABLE)
	


