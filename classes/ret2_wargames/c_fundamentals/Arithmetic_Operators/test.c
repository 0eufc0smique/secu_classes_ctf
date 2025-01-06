#include<stdio.h>

int main() {
    int numbers[16] = {};
    for (int i = 0; i < 100; i++) {
        numbers[i % 16] += 1; 
        printf("%ls", numbers);
    }
}