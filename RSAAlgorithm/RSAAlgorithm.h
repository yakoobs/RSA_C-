//
// Created by Kuba Sokolowski on 26/03/16.
//

#ifndef RSA_RSAALGORITHM_H
#define RSA_RSAALGORITHM_H


int decryptCharacter(int c);
int encryptCharacter(int l);

long long int RSA_modulo(int b, int d, int n);
long long int square(long long a);

int convertCharacterToInt(char c);
char convertIntToCharacter(int l);


#endif //RSA_RSAALGORITHM_H
