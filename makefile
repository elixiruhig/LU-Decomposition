define N
endef
define T
endef
parallel_openmp: parallel_openmp.cpp
	g++ -o parallel_openmp -D n=$N -D t=$T -fopenmp parallel_openmp.cpp
	#/bin/bash -c "time ./parallel"
	
seq: seq.cpp
	g++ -o sequential -D n=$N seq.cpp
	#/bin/bash -c "time ./sequential"

parallel_pthread: parallel_pthread.cpp
	g++ -o parallel_pthread -lpthread parallel_pthread.cpp
	
clean:
	rm -f parallel_openmp parallel_pthread sequential
