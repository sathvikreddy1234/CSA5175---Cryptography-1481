#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100
#define ALPHABET_SIZE 26

void caesarCipher(char* text, int shift, char* result) {
  int i;
  for (i = 0; i < strlen(text); i++) {
    if (isalpha(text[i])) {
      int position = tolower(text[i]) - 'a';
      int newPosition = (position + shift) % ALPHABET_SIZE;
      if (isupper(text[i])) {
        result[i] = 'A' + newPosition;
      } else {
        result[i] = 'a' + newPosition;
      }
    } else {
      result[i] = text[i]; 
    }
  }
  result[i] = '\0';
}

int main() {
  char text[MAX_LENGTH], result[MAX_LENGTH];
  int shift;

  printf("Enter text: ");
  fgets(text, MAX_LENGTH, stdin);
  text[strlen(text) - 1] = '\0';

  printf("Enter shift (1-25): ");
  scanf("%d", &shift);
 caesarCipher(text, shift, result);

  printf("Encrypted/Decrypted text: %s\n", result);

  return 0;
}

