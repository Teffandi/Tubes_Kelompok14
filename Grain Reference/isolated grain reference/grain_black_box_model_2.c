/*description : second attempt prototype for modeling GRAIN algorithm as a blackbox to ease its implementation on more complex system 
date created : 08/04/23
*/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>

#include "crypto_aead.h"
#include "api.h"

#define KAT_SUCCESS          0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR      -3
#define KAT_CRYPTO_FAILURE  -4

#define MAX_FILE_NAME				256
#define MAX_MESSAGE_LENGTH			32
#define MAX_ASSOCIATED_DATA_LENGTH	32


//start of function declaration ==============================================
void init_buffer(unsigned char *buffer, unsigned long long numbytes);
int generate_test_vectors();
//end of function declaration ================================================


//start of main program body==================================================
int main(){

   // unsigned char       key[CRYPTO_KEYBYTES];
//	unsigned char		nonce[CRYPTO_NPUBBYTES];
//	unsigned char       msg[MAX_MESSAGE_LENGTH];
	unsigned char       msg2[MAX_MESSAGE_LENGTH];
//	unsigned char		ad[MAX_ASSOCIATED_DATA_LENGTH];
	unsigned char		ct[MAX_MESSAGE_LENGTH + CRYPTO_ABYTES];
	unsigned long long  clen, mlen2;

    unsigned long long mlen = 8;
    unsigned long long adlen = 9;

//KAT count 274
   unsigned char key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
   unsigned char nonce[12] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b};
   unsigned char msg[8] = {0x54, 0x65, 0x66, 0x66, 0x61, 0x6E, 0x64, 0x69};
   unsigned char ad[9]= {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

    printf("Key: ");
   for (int i = 0; i < 16; i++) {
    printf("%x",key[i]);
   } printf("\n");

   printf("Nonce: ");
   for (int i = 0; i < 12; i++) {
    printf("%x", nonce[i]);
   } printf("\n");

   printf("Message: ");
   for (int i = 0; i < 8; i++) {
    printf("%c", msg[i]);
   } printf("\n");

   printf("AD: ");
   for (int i = 0; i < 9; i++) {
    printf("%x", ad[i]);
   } printf("\nCiphered: ");
    
    if ((crypto_aead_encrypt(ct, &clen, msg, mlen, ad, adlen, NULL, nonce, key)) == 0) {
				for (int i = 0; i<clen;i++){
                    printf("%X",ct[i]);
                }
				//ret_val = KAT_CRYPTO_FAILURE;
				//break;
			}
    
    printf("\n");
    //mlen2 = 32;
     crypto_aead_decrypt(msg2,&mlen2,NULL,ct,clen,ad,adlen,nonce,key);
				for (int i = 0; i<mlen2;i++){
                    printf("%c",msg2[i]);
                }
				
			
    
    return 0;
}
