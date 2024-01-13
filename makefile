all:
	g++ main.cpp -o main -mavx2

clean:
	rm main