//// Created by Jakub Sokołowski on 3/15/16.
////
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RSAAlgorithm/RSAAlgorithm.h"

long int encoded[1000];
char decoded[1000];
void decryptText();
void testEncryption();

int main() {
    testEncryption();

    return EXIT_SUCCESS;
}

#define EXAMPLE_TEXT "testowy tekst testowy tekst testowy tekst testowy tekst testowy tekst "

void testEncryption() {

    const char* text = EXAMPLE_TEXT;
    size_t len = strlen(text);

    for(int i = 0; i < len; i++) {
        encoded[i] = encryptCharacter(convertCharacterToInt(text[i]));
        printf(" %ld",encoded[i]) ;
    }

    decryptText();
    printf("\nDECODED: %s ",decoded) ;

    int isCorrectlyDecoded = (strcmp(text, decoded) == 0);
    if (isCorrectlyDecoded) {
        printf("\n Text has been decoeded CORRECTLY");
    } else {
        printf("\n Text has been decoded INCORRECTLY");
    }
}

void decryptText() {
    size_t len = strlen(EXAMPLE_TEXT);

    for(int i = 0; i < len; i++) {
        decoded[i] = convertIntToCharacter(decryptCharacter(encoded[i]));
    }
    decoded[len] = '\0';
}