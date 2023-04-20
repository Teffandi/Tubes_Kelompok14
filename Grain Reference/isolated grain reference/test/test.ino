
#include <stdio.h>
#include <string.h>
#include <crypto_aead.h>
#include <api.h>

void test(){
    unsigned long long mlen = 8;
    unsigned long long adlen = 9;

//KAT count 274
   unsigned char key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
   unsigned char nonce[12] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b};
   unsigned char msg[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
   unsigned char ad[9]= {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

    if ((crypto_aead_encrypt(ct, &clen, msg, mlen, ad, adlen, NULL, nonce, key)) == 0) {
        for (int i = 0; i<clen;i++){
                    Serial.print(ct[i],HEX);
                }
        //ret_val = KAT_CRYPTO_FAILURE;
        //break;
      }

}
void setup() {
  Serial.begin(9600);
  test();

}

void loop() {
  // put your main code here, to run repeatedly:

}
