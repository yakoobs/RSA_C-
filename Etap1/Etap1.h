//
// Created by Kuba Sokolowski on 28/03/16.
//

#ifndef RSA_TESTETAPI_H
#define RSA_TESTETAPI_H

void encryptText();
void decryptText();
void testEncryption();

#define MAX_TEXT_LENGTH 2048
#define TEXT_FILE_PATH "/Users/kuba.sokolowski/Desktop/text.txt"
#define ENCODED_TEXT_FILE_PATH "/Users/kuba.sokolowski/Desktop/encodedText.txt"
#define DECODED_TEXT_FILE_PATH "/Users/kuba.sokolowski/Desktop/decodedText.txt"


/**
 * Writing and reading from the text file
 */
void saveEncodedTextToFile();
void saveDecodedTextToFile();
void loadTextFromFile();

#endif //RSA_TESTETAPI_H
