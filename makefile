x86:
	g++ main.cpp -o main -mavx2

arm:
	g++ main.cpp -o main

clean:
	rm main