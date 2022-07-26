INCLUDE_DIR_C=-I../bril_histogram/components/bril_histogram/software/src

DummyHistogramGenerator:
	g++ -fPIC src/DummyHistogramGenerator.cpp $(INCLUDE_DIR_C) -std=c++11 -c -o lib/DummyHistogramGenerator.so

test:
	g++ src/test.cpp $(INCLUDE_DIR_C) -std=c++11 -o lib/test.out

clean:
	rm lib/*
