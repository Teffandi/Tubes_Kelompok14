#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>

#include "api.h"
#include "grain128aead-v2_opt.h"

#define KAT_SUCCESS          0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR      -3
#define KAT_CRYPTO_FAILURE  -4

#define MAX_FILE_NAME				256
#define MAX_MESSAGE_LENGTH			32
#define MAX_ASSOCIATED_DATA_LENGTH	32

int main(){


    unsigned char msg2[MAX_MESSAGE_LENGTH];
    unsigned char ct[MAX_MESSAGE_LENGTH + CRYPTO_ABYTES];
    unsigned long long clen, mlen2;
    unsigned long long mlen = 8;
    unsigned long long adlen = 9;
  
   unsigned char key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
   unsigned char nonce[12] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b};
   unsigned char msg[8] = {0x54, 0x65, 0x66, 0x66, 0x61, 0x6E, 0x64, 0x69};
   unsigned char ad[9]= {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

 if ((crypto_aead_encrypt(ct, &clen, msg, mlen, ad, adlen, NULL, nonce, key)) == 0) {
				for (int i = 0; i<clen;i++){
                    printf("%X",ct[i]);
                }
				//ret_val = KAT_CRYPTO_FAILURE;
				//break;
			}




}