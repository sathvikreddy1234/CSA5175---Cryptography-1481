#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MATRIX_SIZE 5
void constructMatrix(char key[], char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int used[26] = {0};
    int row = 0, col = 0;
    char letter;
    for (int i = 0; key[i] != '\0'; i++) {
        letter = toupper(key[i]);
        if (letter == 'J') letter = 'I';
        if (!used[letter - 'A']) {
            matrix[row][col++] = letter;
            used[letter - 'A'] = 1;
            if (col == MATRIX_SIZE) {
                col = 0;
                row++;
            }
        }
    }
    for (letter = 'A'; letter <= 'Z'; letter++) {
        if (letter == 'J') continue; 
        if (!used[letter - 'A']) {
            matrix[row][col++] = letter;
            used[letter - 'A'] = 1;
            if (col == MATRIX_SIZE) {
                col = 0;
                row++;
            }
        }
    }
}
void findPosition(char matrix[MATRIX_SIZE][MATRIX_SIZE], char ch, int *row, int *col) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encryptPair(char matrix[MATRIX_SIZE][MATRIX_SIZE], char a, char b, char *enc1, char *enc2) {
    int row1, col1, row2, col2;
    findPosition(matrix, a, &row1, &col1);
    findPosition(matrix, b, &row2, &col2);
    if (row1 == row2) {
        *enc1 = matrix[row1][(col1 + 1) % MATRIX_SIZE];
        *enc2 = matrix[row2][(col2 + 1) % MATRIX_SIZE];
    } else if (col1 == col2) {
        *enc1 = matrix[(row1 + 1) % MATRIX_SIZE][col1];
        *enc2 = matrix[(row2 + 1) % MATRIX_SIZE][col2];
    } else {
        *enc1 = matrix[row1][col2];
        *enc2 = matrix[row2][col1];
    }
}
void encryptText(char matrix[MATRIX_SIZE][MATRIX_SIZE], char plaintext[], char ciphertext[]) {
    int len = strlen(plaintext), y = 0;
    for (int i = 0; i < len; i += 2) {
        char a = toupper(plaintext[i]);
        char b = (i + 1 < len) ? toupper(plaintext[i + 1]) : 'X';
        if (a == b) b = 'X'; 
        encryptPair(matrix, (a == 'J' ? 'I' : a), (b == 'J' ? 'I' : b), &ciphertext[y], &ciphertext[y + 1]);
        y += 2;
    }
    ciphertext[y] = '\0'; 
}
int main() {
    char key[50], plaintext[100], ciphertext[100];
    char matrix[MATRIX_SIZE][MATRIX_SIZE];
    printf("Enter the keyword (no spaces): ");
    scanf("%s", key);
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);
    constructMatrix(key, matrix);
    printf("Playfair Matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    encryptText(matrix, plaintext, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}