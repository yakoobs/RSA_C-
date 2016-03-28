//
// Created by Kuba Sokolowski on 26/03/16.
//

#ifndef RSA_RSAALGORITHM_H
#define RSA_RSAALGORITHM_H


/* === Encryption and decryption of characters === */
/**
 * Decrypting character using defined secret (d = 611, n = 899) key
 */
int decryptCharacter(int c);

/**
 * Encrypt character using defined public (e = 11, n = 899) key
 */
int encryptCharacter(int l);

/* === Calculating === */
/**
 * Main RSA algorithm implementation
 */
long long int RSA_modulo(int b, int d, int n);

/**
 * Calculating square value of the numeric argument
 */
long long int square(long long a);


/* === Characters <-> Int value conversion ===*/
/**
 * Do conversion
 * space (' ') -> 0
 * a -> 1
 * b -> 2
 * ...
 * z -> 26
 */
int convertCharacterToInt(char c);

/**
 * Do conversion
 * 0 -> space (' ')
 * 1 -> a
 * 2 -> b
 * ...
 * 26 -> z
 * */
char convertIntToCharacter(int l);

#endif //RSA_RSAALGORITHM_H
