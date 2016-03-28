//
// Created by Kuba Sokolowski on 28/03/16.
//

#include "Etap1.h"
#include "../RSAAlgorithm/RSAAlgorithm.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TEXT_LENGTH 2048
#define TEXT_FILE_PATH "/Users/kuba.sokolowski/Desktop/text.txt"
#define ENCODED_TEXT_FILE_PATH "/Users/kuba.sokolowski/Desktop/encodedText.txt"
#define DECODED_TEXT_FILE_PATH "/Users/kuba.sokolowski/Desktop/decodedText.txt"

#define NUMBER_OF_PROCESSORS 2

char* textBuffer;
long textLength;
long int encodedText[MAX_TEXT_LENGTH];
char* decodedText;

void loadTextFromFile() {
    FILE *fp = fopen(TEXT_FILE_PATH, "r");
    if( !fp ) perror(TEXT_FILE_PATH),exit(1);
    fseek( fp , 0L , SEEK_END);
    long length = ftell( fp );
    textLength = (length <= MAX_TEXT_LENGTH) ? length : MAX_TEXT_LENGTH; /* if text is too long cut it down */
    rewind( fp );

    textBuffer = calloc( 1, textLength+1 );
    //encodedText = calloc( 1, textLength+1 );
    decodedText = calloc( 1, textLength+1 );

    if( !textBuffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

    if( 1!=fread( textBuffer , textLength, 1 , fp) )
        fclose(fp),free(textBuffer),fputs("entire read fails",stderr),exit(1);

    fclose(fp);
}

void saveEncodedTextToFile() {
//    FILE *fp = fopen(ENCODED_TEXT_FILE_PATH, "w");
//
//    int results = fputs(encodedText, fp);
//    if (results == EOF) {
//        fputs("No text has been written",stderr),exit(1);
//    }
//    fclose(fp);
}


void saveDecodedTextToFile() {
    FILE *fp = fopen(DECODED_TEXT_FILE_PATH, "w");

    int results = fputs(decodedText, fp);
    if (results == EOF) {
        fputs("No text has been written",stderr),exit(1);
    }
    fclose(fp);
}

void testEncryption() {

    loadTextFromFile();
    const char* text = textBuffer;
    size_t len = strlen(text);

    for(int i = 0; i < len; i++) {
        encodedText[i] = encryptCharacter(convertCharacterToInt(text[i]));
        printf("%ld ",encodedText[i]) ;
    }

   // saveEncodedTextToFile();
    decryptText();
   // saveDecodedTextToFile();

    printf("\nDECODED: %s", decodedText) ;

    int isCorrectlyDecoded = (strcmp(text, decodedText) == 0);
    if (isCorrectlyDecoded) {
        printf("\nText has been decoded CORRECTLY");
    } else {
        printf("\nText has been decodedText INCORRECTLY");
    }
}

void decryptText() {
    size_t len = textLength;

    for(int i = 0; i < len; i++) {
        decodedText[i] = convertIntToCharacter(decryptCharacter(encodedText[i]));
    }
}