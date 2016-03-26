//
// Created by Kuba Sokolowski on 26/03/16.
//

#include "RSAAlgorithm.h"
#include "Constants.h"

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

int convertCharacterToInt(char c) {
    if (c == ' ') return 0;
    return (c - CONVERSION_CONST);
}

char convertIntToCharacter(int l) {
    if (l == 0) return ' ';
    return (char) (l + CONVERSION_CONST);
}