#include <stdlib.h>


void vec_mult(float *p, float *v1, float *v2, int N)
{

#pragma omp declare target

#pragma omp target data map(to: v1[0:N], v2[:N]) map(from: p[0:N])
    {
#pragma omp target
#pragma omp parallel for
        for(int i=0; i<N; i++) {
            p[i] = v1[i] * v2[i];
        }
    }
}

int main(int argc, char **argv) {
    int N = 64;
    float *p, *v1, *v2;
    if(argc > 1) {
        N = atoi(argv[1]);
    }
    p  = new float[N]{0};
    v1 = new float[N]{2};
    v2 = new float[N]{3};

    vec_mult(p, v1, v2, N);

}
