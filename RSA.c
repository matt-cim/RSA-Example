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
    int primeOne, primeTwo, ciphertext[101], *keyPair, e, totientNumber, cipherVal, asciiVal;
    unsigned long int exponentiation;
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

    // key generation, 127 because we have to cover entire ASCII table for enc/decryption
    printf("Enter two primes with sum greater than 127: ");
    scanf("%d  %d", &primeOne, &primeTwo);

    keyPair = genPubKey(primeOne, primeTwo);
    e = keyPair[0];
    totientNumber = keyPair[1];

    genPrivKey(primeOne, primeTwo, e, totientNumber);    

    printf("Private key is: %d\n", d);
    printf("Public key is: %d\n", e);

    // encryption, casting chars to numerical ASCII values for encrpyting
    printf("Ciphertext is: ");
    for (int i = 0; i < strlen(message); i++) {
        exponentiation = 1;
        asciiVal = message[i];
        //if (i == 0) {printf("%lli", asciiVal);}

        // switch for loop statement
        for (int j = 1; j <= e; j++) {
            exponentiation = exponentiation * asciiVal;
            //printf("\n%d", exponentiation);
            // exponents and mod rule 
            exponentiation = exponentiation % N;
        }
        //if (i == 0) {printf("%li", exponentiation);}
        cipherVal = exponentiation % N;
        ciphertext[i] == cipherVal;
        printf("%d ", cipherVal);
    }    



    // decryption
    //printf("\n Plaintext is: ");
    //for (int k = 0; k < strlen(message); k++) {
        //int cipherVal = ciphertext[k];
        //for (int l = d; l != 0; l--) {
        //    cipherVal *= cipherVal;
        //}
        //int plaintext = cipherVal % N;
        //decryption[k] = plaintext;
        //printf("%d", plaintext);
   // }

    

    return 0;
}
