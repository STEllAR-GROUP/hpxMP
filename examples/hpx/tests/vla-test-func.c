
int arr_add(int size) {
    int n[size];
    int i;
    for( i = 0; i < size; i++) {
        n[i] = 2;
    }
    int sum = 0;
    for( i = 0; i < size; i++) {
        sum += n[i];
    }
    return sum;
}

