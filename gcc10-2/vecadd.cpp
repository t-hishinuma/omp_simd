#include<iostream>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(int argc, char** argv){
    size_t N = atoi(argv[1]);
    std::vector<double> x(N,1.0);
    std::vector<double> y(N,2.0);
    std::vector<double> z(N,0.0);

    double stime = omp_get_wtime();

    double* xd = x.data();
    double* yd = y.data();
    double* zd = z.data();

    for(size_t i = 0; i < 10; i++){

    //z = x + y
        #pragma omp simd
        for(size_t i=0; i<N; i++){
            zd[i] += xd[i] * yd[i];
        }

    }

    double time = (omp_get_wtime() - stime) / 10;

    double perf = N / time / 1.0e+9;
    std::cout << time << "\t" << perf << std::endl;

    return 0;
}
