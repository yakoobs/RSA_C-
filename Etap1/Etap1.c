//
// Created by Kuba Sokolowski on 28/03/16.
//

#include "Etap1.h"
#include "../RSAAlgorithm/RSAAlgorithm.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUMBER_OF_PROCESSORS 2

char* textBuffer;
long textLength;
long int encoded[MAX_TEXT_LENGTH];
char* decodedText;
long indexes[NUMBER_OF_PROCESSORS + 1];

void writeToFile(char* filePath, char* text);
void loadEncodedTextFromFile();
void splitIntoIndexes();




void test() {

    clock_t start = clock();
    encryptFile();
    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("\nEncryption time: %f", seconds);

    start = clock();
    decryptFile();
    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("\nDecryption time: %f", seconds);

}




/*
 * FILE ENCRYPTION
 *
 * Program gets the path to the text file and encodes it with RSA algorithm
 * Finally saves the encoded characters in the file - every single character in a single line
 */

void encryptFile() {
    loadClearTextFromFile();
    splitIntoIndexes();
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
    decodedText = calloc( 1, textLength + 1 );

    if( !textBuffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

    if( 1!=fread( textBuffer , textLength, 1 , fp) )
        fclose(fp),free(textBuffer),fputs("entire read fails",stderr),exit(1);

    fclose(fp);
}

void encryptText(long fromIndex, long toIndex) {
    const char* text = textBuffer;

    for (int i = 0; i < NUMBER_OF_PROCESSORS; i++) {
        for(int k = indexes[i]; k < indexes[i+1]; k++) {
            encoded[k] = encryptCharacter(convertCharacterToInt(text[k]));
        }
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
    splitIntoIndexes();
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
    decodedText = calloc( 1, textLength + 1 );

    rewind( fp );

    while ((read = getline(&line, &len, fp)) != -1) {
        encoded[index++] = atoi(line);
    }

    fclose(fp);
}

void decryptText() {
    for (int i = 0; i < NUMBER_OF_PROCESSORS; i++) {
        for(int k = indexes[i]; k < indexes[i+1]; k++) {
            decodedText[k] = convertIntToCharacter(decryptCharacter(encoded[k]));
        }
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


void splitIntoIndexes() {
    indexes[0] = 0;
    for (int i = 1; i < NUMBER_OF_PROCESSORS; i++) {
        indexes[i] = i*floor(textLength/NUMBER_OF_PROCESSORS);
    }
    indexes[NUMBER_OF_PROCESSORS] = textLength;
}