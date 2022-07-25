INCLUDE_DIR_C=-Ibril_histogram/components/bril_histogram/software/src

DummyHistogramGenerator:
	g++ -fPIC src/DummyHistogramGenerator.cpp $(INCLUDE_DIR_C) -std=c++11 -c -o lib/DummyHistogramGenerator.so

clean:
	rm lib/*
