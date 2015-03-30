all: sumsqrt_mono sumsqrt_threads

sumsqrt_mono: sumsqrt_mono.c
	gcc -g -o sumsqrt_mono sumsqrt_mono.c -lm

sumsqrt_threads: sumsqrt_threads.c
	gcc -g -o sumsqrt_threads sumsqrt_threads.c -lm -lpthread

clean:
	rm -f *~

clean-all: clean
	rm -f sumsqrt_mono sumsqrt_threads

