GCC = g++ -std=c++17
MACHINE = $(shell uname -m) 

ifeq ($(MACHINE), i386)
all: mapping_core.o
	$(GCC) mapping_structure.o mapping_module.o main.cpp -o main -mavx2
else
all: mapping_core.o
	$(GCC) mapping_core.o main.cpp -o main
endif

mapping_core.o: mapping_module.o mapping_structure.o runners.o tests.o
	ld -relocatable mapping_module.o mapping_structure.o runners.o tests.o -o mapping_core.o

mapping_module.o:
	$(GCC) -c mapping_module.cpp -o mapping_module.o

runners.o:
	$(GCC) -c runners.cpp -o runners.o

tests.o:
	$(GCC) -c tests.cpp -o tests.o

mapping_structure.o:
	$(GCC) -c mapping_structure.cpp -o mapping_structure.o

clean:
	rm main *.o