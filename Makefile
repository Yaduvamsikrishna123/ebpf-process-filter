all: bpf loader

bpf:
	clang -O2 -g -target bpf \
	-I/usr/include/x86_64-linux-gnu \
	-c block_process_port.bpf.c \
	-o block_process_port.bpf.o

loader:
	gcc loader.c -o loader -lbpf

clean:
	rm -f *.o loader
