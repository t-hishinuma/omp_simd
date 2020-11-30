#include<iostream>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<immintrin.h>

int main(int argc, char** argv){
    size_t N = atoi(argv[1]);
    std::vector<double> x(N,1.0);


    double* xd = x.data();

    ///////////////////////////////////////////////////
    double stime = omp_get_wtime();

    for(size_t i = 0; i < 10; i++){

        #pragma omp simd
        for(size_t i=0; i<N; i++){
            xd[i] += xd[i] * xd[i];
        }

    }

    double time = (omp_get_wtime() - stime) / 10;

    double perf = 2*N / time / 1.0e+9;
    std::cout << time << "\t" << perf << std::endl;

    ///////////////////////////////////////////////
    stime = omp_get_wtime();

    for(size_t i = 0; i < 10; i++){

        #pragma omp parallel for
        for(size_t i=0; i<N-3; i+=4){
            __m256d xv = _mm256_loadu_pd((double*)&xd[i]);
            xv = _mm256_fmadd_pd(xv, xv, xv);
            _mm256_storeu_pd((double*)&xd[i], xv);
        }

    }

    time = (omp_get_wtime() - stime) / 10;

    perf = 2*N / time / 1.0e+9;
    std::cout << time << "\t" << perf << std::endl;
    ///////////////////////////////////////////////
    stime = omp_get_wtime();

    for(size_t i = 0; i < 10; i++){

        #pragma omp parallel for
        for(size_t i=0; i<N-7; i+=8){
            __m512d xv = _mm512_loadu_pd((double*)&xd[i]);
            xv = _mm512_fmadd_pd(xv, xv, xv);
            _mm512_storeu_pd((double*)&xd[i], xv);
        }

    }

    time = (omp_get_wtime() - stime) / 10;

    perf = 2*N / time / 1.0e+9;
    std::cout << time << "\t" << perf << std::endl;
    ///////////////////////////////////////////////

    return 0;
}
