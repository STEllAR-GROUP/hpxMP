
int main() {
    int x = 0;
#pragma omp parallel num_threads(42)
    {
        x++;   
    }
    return x;
}
