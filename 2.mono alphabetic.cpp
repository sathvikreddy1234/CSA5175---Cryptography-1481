#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main() 
{
    char plaintext[100];
    char key[27]; 
    char ciphertext[100];
    int y = 0;
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);
    printf("Enter the 26 unique alphabets key: ");
    scanf("%s", key);
    if (strlen(key) != 26) 
    {
        printf("Invalid key! The key must contain exactly 26 unique letters.\n");
        return 1;
    }
    for (int i = 0; plaintext[i] != '\0'; i++) 
    {
        if (isalpha(plaintext[i])) 
        { 
            if (isupper(plaintext[i])) 
            {
                ciphertext[y] = key[plaintext[i] - 'A']; 
            } 
            else 
            {
                ciphertext[y] = tolower(key[plaintext[i] - 'a']); 
            }
        } 
        else 
        {
            ciphertext[y] = plaintext[i];
        }
        y++; 
    }
    ciphertext[y] = '\0'; 
    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}