 #include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Function to generate the Playfair matrix
void generateMatrix(char matrix[SIZE][SIZE], char keyword[]) {
    int i, j, k = 0;
    char alphabet[] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

    // Add keyword to matrix
    for (i = 0; i < strlen(keyword); i++) {
        matrix[k / SIZE][k % SIZE] = toupper(keyword[i]);
        k++;
    }

    // Fill remaining cells with alphabet
    for (i = 0; i < strlen(alphabet); i++) {
        if (strchr(keyword, alphabet[i]) == NULL) {
            matrix[k / SIZE][k % SIZE] = alphabet[i];
            k++;
        }
    }
}

// Function to prepare plaintext for encryption
void preparePlaintext(char plaintext[]) {
    int i, j = 0;
    char temp[strlen(plaintext)];

    // Remove spaces and convert to uppercase
    for (i = 0; i < strlen(plaintext); i++) {
        if (plaintext[i] != ' ') {
            temp[j++] = toupper(plaintext[i]);
        }
    }
    temp[j] = '\0';

    for (i = 0; i < strlen(temp); i++) {
        if (temp[i] == 'J') {
            temp[i] = 'I';
        }
    }

    j = 0;
    while (j < strlen(temp) - 1) {
        if (temp[j] == temp[j + 1]) {
            memmove(&temp[j + 2], &temp[j + 1], strlen(temp) - j - 1);
            temp[j + 1] = 'X';
        }
        j += 2;
    }

    // Copy modified plaintext back to original array
    strcpy(plaintext, temp);
}

// Function to encrypt plaintext using Playfair cipher
void playfairCipher(char plaintext[], char ciphertext[], char matrix[SIZE][SIZE]) {
    int i, row1, row2, col1, col2;
    char temp[3];

    for (i = 0; i < strlen(plaintext); i += 2) {
        // Find positions of current pair of letters in matrix
        for (row1 = 0; row1 < SIZE; row1++) {
            for (col1 = 0; col1 < SIZE; col1++) {
                if (matrix[row1][col1] == plaintext[i]) {
                    goto found1;
                }
            }
        }
        found1:;
        for (row2 = 0; row2 < SIZE; row2++) {
            for (col2 = 0; col2 < SIZE; col2++) {
                if (matrix[row2][col2] == plaintext[i + 1]) {
                    goto found2;
                }
            }
        }
        found2:;

        if (row1 == row2) { 
            ciphertext[i] = matrix[row1][(col1 + 1) % SIZE];
            ciphertext[i + 1] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) { 
            ciphertext[i] = matrix[(row1 + 1) % SIZE][col1];
            ciphertext[i + 1] = matrix[(row2 + 1) % SIZE][col2];
        } else { // Different row and column
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i + 1] = matrix[row2][col1];
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; 
}

int main() {
    char keyword[100], plaintext[100], ciphertext[100];
    char matrix[SIZE][SIZE];

    printf("Enter keyword: ");
    scanf("%s", keyword);

    printf("Enter plaintext: ");
    scanf(" %[^\n]", plaintext);

    generateMatrix(matrix, keyword);
    preparePlaintext(plaintext);
    playfairCipher(plaintext, ciphertext, matrix);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
