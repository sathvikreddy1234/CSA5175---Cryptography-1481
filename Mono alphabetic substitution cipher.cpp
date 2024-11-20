#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100
#define ALPHABET_SIZE 26

void encrypt(char *plaintext, char *ciphertext) {
    char mapping[26];
    printf("Enter mapping (26 characters): ");
    scanf("%s", mapping);

    for (int i = 0; i < strlen(plaintext); i++) {
        if (isalpha(plaintext[i])) {
            int position = tolower(plaintext[i]) - 'a';
            if (isupper(plaintext[i])) {
                ciphertext[i] = toupper(mapping[position]);
            } else {
                ciphertext[i] = mapping[position];
            }
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; 
}

void decrypt(char *ciphertext, char *plaintext) {
    char mapping[26];
    printf("Enter mapping (26 characters): ");
    scanf("%s", mapping);

    char reverseMapping[26];
    for (int i = 0; i < 26; i++) {
        reverseMapping[mapping[i] - 'a'] = 'a' + i;
    }

    for (int i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            int position = tolower(ciphertext[i]) - 'a';
            if (isupper(ciphertext[i])) {
                plaintext[i] = toupper(reverseMapping[position]);
            } else {
                plaintext[i] = reverseMapping[position];
            }
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; 
}

int main() {
    char plaintext[MAX_LENGTH], ciphertext[MAX_LENGTH];
    int choice;

    printf("Monoalphabetic Substitution Cipher\n");
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter plaintext: ");
        scanf(" %[^\n]", plaintext);
        encrypt(plaintext, ciphertext);
        printf("Ciphertext: %s\n", ciphertext);
    } else if (choice == 2) {
        printf("Enter ciphertext: ");
        scanf(" %[^\n]", ciphertext);
        decrypt(ciphertext, plaintext);
        printf("Plaintext: %s\n", plaintext);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}