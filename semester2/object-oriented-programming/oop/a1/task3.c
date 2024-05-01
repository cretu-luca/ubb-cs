#include <stdio.h>

void generate_pascal_matrix(int dimension, int pascal_matrix[20][20]){
    for(int i = 0; i < dimension; i++)
        pascal_matrix[i][0] = pascal_matrix[i][i] = 1;

    for(int i = 2; i < dimension; i++)
        for(int j = 1; j < i; j++)
            pascal_matrix[i][j] = pascal_matrix[i - 1][j - 1] + pascal_matrix[i - 1][j];
}

int numberOfDigits(int num){
    int count = 0;
    while(num > 0){
        count += 1;
        num /= 10;
    }

    return count;
}

void pascal_triangle(){
    int dimension, pascal_matrix[20][20];
    printf("dimension=");
    scanf("%d", &dimension);

    generate_pascal_matrix(dimension, pascal_matrix);
    int numberOfSpaces = numberOfDigits(pascal_matrix[dimension - 1][(dimension - 1) / 2]);

    if(numberOfSpaces == 1)
        numberOfSpaces = 2;

    for(int i = 0; i < dimension; i++, printf("\n")) {

        for(int j = 1; j <= 2 * (dimension - i); j++)
            printf(" ");

        for (int j = 0; j < i + 1; j++) {
            for (int k = 1; k <= numberOfSpaces - numberOfDigits(pascal_matrix[i][j]) + 1; k++)
                printf(" ");

            printf("%d", pascal_matrix[i][j]);
        }
    }

}

int isPrime(int number){
    if(number == 0 || number == 1)
        return 0;
    if(number == 2)
        return 1;
    if(number % 2 == 0)
        return 0;
    for(int d = 3; d * d <= number; d += 2)
        if(number % d == 0)
            return 0;

    return 1;
}


void longest_subsequence(){
    int numberOfValues, currentValue, currentLength = 0, maximumLength = -1;

    printf("number of values=");
    scanf("%d", &numberOfValues);

    for(int i = 1; i <= numberOfValues; i++){
        scanf("%d", &currentValue);

        if(isPrime(currentValue)) {
            currentLength += 1;

            if (currentLength > maximumLength)
                maximumLength = currentLength;
        }
        else
            currentLength = 0;
    }

    printf("Longest contiguous sequence of prime numbers is %d.\n", maximumLength);
}

int main(){
    int running = 1, option;
    while(running == 1){
        printf("1. Pascal Triangle\n2. Longest Sequence\n3. Exit\noption=");
        scanf("%d", &option);
        if(option == 1)
            pascal_triangle();
        else
            if(option == 2)
                longest_subsequence();
            else
                if(option == 3)
                    running = 0;
                else
                    printf( "invalid option");
    }
}