//
// Created by Kuba Sokolowski on 28/03/16.
//

#include "Etap1.h"
#include "../RSAAlgorithm/RSAAlgorithm.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define NUMBER_OF_PROCESSORS 2

char* textBuffer;
long textLength;
long int encoded[MAX_TEXT_LENGTH];
char* encodedText;
char* decodedText;

void writeToFile(char* filePath, char* text);
void loadEncodedTextFromFile();





void testEncryption() {

//    encryptFile();
//    decryptText();
//    saveDecodedTextToFile();
//
//    printf("\nDECODED: %s", decodedText) ;
//
//    int isCorrectlyDecoded = (strcmp(textBuffer, decodedText) == 0);
//    if (isCorrectlyDecoded) {
//        printf("\nText has been decoded CORRECTLY");
//    } else {
//        printf("\nText has been decodedText INCORRECTLY");
//    }

    decryptFile();

}




/*
 * FILE ENCRYPTION
 *
 * Program gets the path to the text file and encodes it with RSA algorithm
 * Finally saves the encoded characters in the file - every single character in a single line
 */

void encryptFile() {
    loadClearTextFromFile();
    encryptText();
    saveEncodedTextToFile();
}

void loadClearTextFromFile() {
    FILE *fp = fopen(TEXT_FILE_PATH, "r");
    if( !fp ) perror(TEXT_FILE_PATH),exit(1);
    fseek( fp , 0L , SEEK_END);
    long length = ftell( fp );
    textLength = (length <= MAX_TEXT_LENGTH) ? length : MAX_TEXT_LENGTH; /* if text is too long cut it down */
    rewind( fp );

    textBuffer = calloc( 1, textLength + 1 );
    encodedText = calloc( 1, textLength + 1 );
    decodedText = calloc( 1, textLength + 1 );

    if( !textBuffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

    if( 1!=fread( textBuffer , textLength, 1 , fp) )
        fclose(fp),free(textBuffer),fputs("entire read fails",stderr),exit(1);

    fclose(fp);
}

void encryptText() {
    const char* text = textBuffer;
    size_t len = strlen(text);

    for(int i = 0; i < len; i++) {
        encoded[i] = encryptCharacter(convertCharacterToInt(text[i]));
        printf("%ld ", encoded[i]) ;
    }
}


void saveEncodedTextToFile() {
    FILE *fp = fopen(ENCODED_TEXT_FILE_PATH, "w");
    for (int i = 0; i < textLength; ++i) {
        fprintf(fp,"%li\n",encoded[i]);
    }
    fclose(fp);
}



/*
 * FILE DECRYPTION
 *
 * Program gets the path to the file with encoded characters and decodes it with RSA algorithm
 * Finally saves the decoded text in the file.
 */

void decryptFile() {
    loadEncodedTextFromFile();
    decryptText();
    saveDecodedTextToFile();
}

void loadEncodedTextFromFile() {
    char * line = NULL;
    size_t len = 0;
    int index = 0;
    ssize_t read;

    FILE *fp = fopen(ENCODED_TEXT_FILE_PATH, "r");
    if( !fp ) perror(ENCODED_TEXT_FILE_PATH),exit(1);

    int ch = 0;
    textLength = 0;

    do
    {
        ch = fgetc(fp);
        if(ch == '\n')
            textLength++;
    } while (ch != EOF);

    textBuffer = calloc( 1, textLength + 1 );
    encodedText = calloc( 1, textLength + 1 );
    decodedText = calloc( 1, textLength + 1 );

    rewind( fp );

    while ((read = getline(&line, &len, fp)) != -1) {
        encoded[index++] = atoi(line);
    }

    fclose(fp);
}

void decryptText() {
    size_t len = textLength;

    for(int i = 0; i < len; i++) {
        decodedText[i] = convertIntToCharacter(decryptCharacter(encoded[i]));
    }
}

void saveDecodedTextToFile() {
    writeToFile(DECODED_TEXT_FILE_PATH,decodedText);
}

void writeToFile(char* filePath, char* text) {
    FILE *fp = fopen(filePath, "w");

    int results = fputs(text, fp);
    if (results == EOF) {
        fputs("No text has been written",stderr),exit(1);
    }
    fclose(fp);
}
