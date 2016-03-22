//// Created by Jakub Sokołowski on 3/15/16.
////
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Constants.h"

long int encoded[1000];
char decoded[1000];
void decryptText();
void testEncryption();
int decryptCharacter(int c);
int encryptCharacter(int l);

long long int RSA_modulo(int b, int d, int n);
long long int square(long long a);

int convertCharacterToInt(char c);
char convertIntToCharacter(int l);

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


//Encryption and decryption of characters
int encryptCharacter(int l) {
    return RSA_modulo(l, PUBLIC_KEY_e, PUBLIC_KEY_n);
}

int decryptCharacter(int c) {
    return RSA_modulo(c, PRIVATE_KEY_d, PRIVATE_KEY_n);
}


//Calculating
long long int square(long long arg) { return arg * arg; }

long long int RSA_modulo(int b, int d, int n) {
    if(d == 0) {
        return 1;
    } else if(d % 2 == 0) {
        return square(RSA_modulo(b, d / 2, n)) % n;
    } else {
        return ((b % n) * RSA_modulo(b, d - 1, n)) % n;
    }
}

//Initial conversion
int convertCharacterToInt(char c) {
    if (c == ' ') return 0;
    return (int)(c - CONVERSION_CONST);
}

char convertIntToCharacter(int l) {
    if (l == 0) return ' ';
    return (char) (l + CONVERSION_CONST);
}