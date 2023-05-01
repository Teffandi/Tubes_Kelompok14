
#include "grain128aead-v2_opt.h"
#include "api.h"


#define MAX_FILE_NAME        256
#define MAX_MESSAGE_LENGTH      32
#define MAX_ASSOCIATED_DATA_LENGTH  32
void setup() {
  // put your setup code here, to run once:

   

    
    unsigned char msg2[MAX_MESSAGE_LENGTH];
    unsigned char ct[MAX_MESSAGE_LENGTH + CRYPTO_ABYTES];
    unsigned long long clen, mlen2;
    unsigned long long mlen = 8;
    unsigned long long adlen = 9;
  
   unsigned char key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
   unsigned char nonce[12] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b};
   unsigned char msg[8] = {0x54, 0x65, 0x66, 0x66, 0x61, 0x6E, 0x64, 0x69};
   unsigned char ad[9]= {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
 
   Serial.begin(115200);

    Serial.println("[APP] Free memory: " + String(esp_get_free_heap_size()) + " bytes");

    if ((crypto_aead_encrypt(ct, &clen, msg, mlen, ad, adlen, NULL, nonce, key)) == 0) {
       for (int i = 0; i<clen;i++){
                    Serial.print(ct[i],HEX);
                    Serial.print("-");
                }
        //ret_val = KAT_CRYPTO_FAILURE;
        //break;
      }
      Serial.println(clen);
      crypto_aead_decrypt(msg2,&mlen2,NULL,ct,clen,ad,adlen,nonce,key);
        for (int i = 0; i<mlen2;i++){
                    Serial.println(char(msg2[i]));
                }
     Serial.println("[APP] Free memory: " + String(esp_get_free_heap_size()) + " bytes");

    
}

void loop() {
  // put your main code here, to run repeatedly:

}
