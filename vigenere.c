#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define alphabetLength 26
#define ASCIIZValue 90
#define ASCIIAValue 65

int main(int argc, string argv[])
{
    char letter;
    int length;
    int k;
    int cipherVal;
    char cipherChar;
    char plainLetter;
    int plainVal;

    // Ensure one argument is given
    if (argc != 2)
    {
        printf("One keyword required!\n");
        return 1;
    }

    // Ensure the key is all alphabetical characters
    string keyword = argv[1];
    int keyLength = strlen(keyword);
    for (int i = 0; i < keyLength; i++)
    {
        if (isalpha(keyword[i]) == false)
        {
            printf("Alphabetical characters only!\n");
            return 1;
        }
    }

    // Convert keyword characters to uppercase, and then to shift values (ints)
    int keyVals[keyLength];
    for (int i = 0; i < keyLength; i++)
    {
        letter = keyword[i];
        letter = toupper(letter);
        keyVals[i] = (int) letter - ASCIIAValue;
    }

    // Ask user for plaintext
    string plaintext = get_string("Plaintext: ");
    length = strlen(plaintext);

    // Declare cipherText array and cap it off with null character '\0'
    // You must cap it off with null to avoid strange results when check50 encrypts "world!$?"
    char cipherText[length + 1];
    cipherText[length] = '\0';

    // Counter for cycling through plaintext string
    int i = 0;
    // Seperate counter for cycling through keyVals indecies
    int j = 0;

    while (i < length)
    {
        k = 0;
        cipherVal = 0;

        // Convert plaintext chars to uppercase
        plainLetter = toupper(plaintext[i]);

        // Pass non-alphabetical chars to cipherText unchanged, continue loop to avoid incrementing j
        if (isalpha(plainLetter) == false)
        {
            cipherText[i] = plainLetter;
            i++;
            continue;
        }

        // Convert plaintext chars to their ASCII decimal values
        plainVal = (int) plainLetter;

        // Apply cipher to key chars
        if (plainVal + keyVals[j%3] > ASCIIZValue)
        {
            k = keyVals[j%3] - alphabetLength;
            cipherVal = plainVal + k;
        }

        else
        {
            k = keyVals[j%3];
            cipherVal = plainVal + k;
        }

        // Convert ASCII ints back to characters
        cipherChar = (char) cipherVal;

        // If original char was lowercase, make it lowercase again
        if (islower(plaintext[i]))
        {
            cipherChar = tolower(cipherChar);
        }

        // Add character to ciphertext array
        cipherText[i] = cipherChar;

        // Increment counters
        i++;
        j++;
    }

    printf("ciphertext: %s\n", cipherText);
    return 0;

}