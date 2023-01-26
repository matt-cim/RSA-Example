#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int d, N;


//generates public key
int* genPubKey(int primeOne, int primeTwo) {
    static int keyPair[2];
    int e = 2, totientNumber;
    // public key must be > 1 and relatively prime to totient number
    totientNumber = (primeOne - 1) * (primeTwo - 1);

    while (gcd(e, totientNumber) != 1) {
        e++;
    }

    keyPair[0] = e, keyPair[1] = totientNumber;

    return keyPair;
}


// function from geeksforgeeks https://www.geeksforgeeks.org/program-to-find-gcd-or-hcf-of-two-numbers/
// O(min(a,b)) complexity
int gcd(int a, int b) {
    int result = ((a < b) ? a : b);

    while (result > 0) {
        if (a % result == 0 && b % result == 0) {
            break;
        }
        result--;
    }

    return result;
}


// generates private key 
void genPrivKey(int primeOne, int primeTwo, int e, int totientNumber) {
    int remainder, eSave;

    N = primeOne * primeTwo;
    remainder = totientNumber;

    // solving for private key d in ed = 1 mod totientFunction(N)
    // using extended Euclid's algo. O(logM) complexity where M = totient number
    d = euclids(e, totientNumber, 1, 0, remainder);
}


// finding modular multiplicative inverse
int euclids(int e, int totientNumber, int X, int Y, int remainder) {
    int quotient, temp;

    //base case
    if (e == 1) {
        if (X > 0) {
            return X;
        }
        else {
            // negative value case
            return X + remainder;
        }
    }

    temp = totientNumber;
    quotient = e / totientNumber;
    totientNumber = e % totientNumber;
    e = temp;
    temp = Y;
    euclids(e, totientNumber, temp, X - quotient * Y, remainder);
}


int main() {
    int primeOne, primeTwo, ciphertext[101], *keyPair, e, totientNumber, asciiVal;
    unsigned long int exponentiation;
    unsigned char message[101], decrypted[101], hexCipher[101], *messagePtr, asciiToChar;
    messagePtr = message;
  

    // reading in the unencrypted message
    printf("Enter message: ");
    // if input is > 100 chars -> buffer oveflow
    fgets(message, sizeof(message), stdin);

    printf("Hexadecimal value of message: ");
    while (*messagePtr) {
        printf("%x", *messagePtr);
        messagePtr++;
    }
    printf("\n");

    // key generation, 127 because we have to cover entire ASCII table for enc/decryption
    printf("\nEnter two primes with product greater than 127: ");
    scanf("%d  %d", &primeOne, &primeTwo);

    keyPair = genPubKey(primeOne, primeTwo);
    e = keyPair[0];
    totientNumber = keyPair[1];

    genPrivKey(primeOne, primeTwo, e, totientNumber);    

    printf("\nPrivate key is: %d", d);
    printf("\nPublic key is: %d", e);

    // encryption, casting chars to numerical ASCII values for encrpyting
    printf("\n\nCiphertext is: ");
    for (int i = 0; i < strlen(message) - 1; i++) {
        exponentiation = 1;
        asciiVal = message[i];

        for (int j = e; j >= 1; j--) {
            exponentiation *= asciiVal;
            // exponents and mod rule -> data savings
            exponentiation = exponentiation % N;
        }        
        asciiToChar = exponentiation % 128;
        hexCipher[i] = asciiToChar;
        ciphertext[i] = exponentiation;
        printf("%c", asciiToChar);
    }    
    printf("\nHexadecimal value of ciphertext: ");
    messagePtr = hexCipher;
    while (*messagePtr) {
        printf("%x", *messagePtr);
        messagePtr++;
    }


    // decryption with private key
    printf("\nDeciphering... \n");
    for (int k = 0; k < strlen(message) - 1; k++) {
        exponentiation = 1;
        asciiVal = ciphertext[k];

        for (int l = d; l >= 1; l--) {
            exponentiation *= asciiVal;
            exponentiation = exponentiation % N;
        }
        asciiToChar = exponentiation;
        decrypted[k] = asciiToChar;
        printf("%c -> %d: (%d ^ %d) mod %d = %d: %d -> %c\n", ciphertext[k], asciiVal, asciiVal, d, N, exponentiation, exponentiation, decrypted[k]);   
    }
    printf("\nDecrypted Ciphertext: ");
    for (int t = 0; t < strlen(message) - 1; t++) {
        printf("%c", decrypted[t]);
    }


    return 0;
}
