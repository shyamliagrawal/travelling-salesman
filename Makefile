obj = main.o graph.o
travellingSalesman: $(obj)
	cc -o travellingSalesman $(obj)
main.o graph.o : graph.h
clean:
	rm $(obj)
	rm travellingSalesman
