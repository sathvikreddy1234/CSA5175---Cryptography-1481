#include <stdio.h>
#include <string.h>
#include <ctype.h>
void encrypt(char *plaintext, char *key, char *ciphertext) 
{
    int i, j = 0;
    int keyLength = strlen(key);
    int textLength = strlen(plaintext);
    for (i = 0; i < textLength; i++) 
	{
        char p = plaintext[i];
        if (isalpha(p)) 
		{ 
            char k = toupper(key[j % keyLength]);
            int shift = k - 'A'; 
            if (isupper(p)) 
			{
                ciphertext[i] = (p - 'A' + shift) % 26 + 'A'; 
            } else {
                ciphertext[i] = (p - 'a' + shift) % 26 + 'a';
            }
            j++; 
        } else {
            ciphertext[i] = p;
        }
    }
    ciphertext[i] = '\0'; 
}
int main() {
    char plaintext[256], key[256], ciphertext[256];
    printf("Enter the key (letters only): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; 
    for (int i = 0; key[i] != '\0'; i++) {
        if (!isalpha(key[i])) 
		{
            printf("Error: The key must contain only alphabetic characters.\n");
            return 1;
        }
    }
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}