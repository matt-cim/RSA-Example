#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int d, N, e;

// generates public and private key 
void genKeys(int primeOne, int primeTwo) {
    // in practice, sometimes e = 3 is used, but the most common value of e is 65537
    int totientNumber, e = 3, i, remainder;

    N = primeOne * primeTwo;
    totientNumber = (primeOne - 1) * (primeTwo - 1);
    remainder = totientNumber;

    // e must be relatively prime in order for Euclid's to work
    if ((totientNumber / e) == 0) {e = 5;}
    
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
    int primeOne, primeTwo, ciphertext[101];
    char message[101], decryption[101], *messagePtr;
    messagePtr = message;


    // reading in the unencrypted message
    printf("Enter message: ");
    // if input is > 100 chars -> buffer oveflow
    fgets(message, sizeof(message), stdin);

    printf("Hexadecimal value of message: ");
    while(*messagePtr) {
        printf("%x", *messagePtr);
        messagePtr++;
    }
    printf("\n");

    // key generation
    printf("Enter two large (> 10) primes: ");
    scanf("%d  %d", &primeOne, &primeTwo);
    genKeys(primeOne, primeTwo);

    printf("Private key is: %d\n", d);
    printf("Public key is: %d\n", e);

    // encryption, casting chars to numerical ASCII values for encrpyting
    printf("Ciphertext is: ");
    for (int i = 0; i < strlen(message); i++) {
         int asciiVal = message[i];
         printf("%d", asciiVal);
    //     for (int j = e; j != 0; j--) {
    //           asciiVal *= asciiVal;
    //     }
    //     int cipherVal = asciiVal % N;
    //     ciphertext[i] == cipherVal;
    //     printf("%d", cipherVal);
    }    


    // decryption
    printf("\n Plaintext is: ");
    for (int k = 0; k < strlen(message); k++) {
        //int cipherVal = ciphertext[k];
        //for (int l = d; l != 0; l--) {
        //    cipherVal *= cipherVal;
        //}
        //int plaintext = cipherVal % N;
        //decryption[k] = plaintext;
        //printf("%d", plaintext);
    }

    

    return 0;
}
