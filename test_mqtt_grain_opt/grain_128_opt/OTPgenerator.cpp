#include<iostream>
#include<io.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include <iomanip>

#include <chrono> //for execution time
using namespace std::chrono;
using namespace std;

auto start = high_resolution_clock::now();
//GRAIN
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>

#include "api.h"
#include "grain128aead-v2_opt.h"
#include "grain128aead-v2_opt.cpp"

#define KAT_SUCCESS          0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR      -3
#define KAT_CRYPTO_FAILURE  -4

#define MAX_FILE_NAME				256
#define MAX_MESSAGE_LENGTH			32
#define MAX_ASSOCIATED_DATA_LENGTH	32
//END OF GRAIN

void call_grain(unsigned char *msg){

    unsigned char msg2[MAX_MESSAGE_LENGTH];
    unsigned char ct[MAX_MESSAGE_LENGTH + CRYPTO_ABYTES];
    unsigned long long clen, mlen2;
    unsigned long long mlen = 8;
    unsigned long long adlen = 9;

   unsigned char key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
   unsigned char nonce[12] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b};
  // unsigned char msg[8] = {0x54, 0x65, 0x66, 0x66, 0x61, 0x6E, 0x64, 0x69};
   unsigned char ad[9]= {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

 if ((crypto_aead_encrypt(ct, &clen, msg, mlen, ad, adlen, NULL, nonce, key)) == 0) {
				for (int i = 0; i<clen;i++){
                     printf("%X",ct[i]);
                   //std::cout << std::hex << ct[i];

                }
			}

}

string OTPgenerator(int n) // Generating OTP
{
	unsigned char msg[n];
	string str = "0123456789";
    int len = str.length();
 	string otp;
    int j;
    srand(time(0));
	for(int i=1;i<=n;i++)
    {
	   int j = rand()%len;
       otp[i]=str[j];
	}
    for(int i=1;i<=n;i++)
    {
        msg[i]= (char)(otp[i]);
    	cout<<otp[i];
	}
	cout<<endl;
    cout<<"Encrypted OTP : ";
    auto start = high_resolution_clock::now(); //start counting execution time
    call_grain(msg);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<endl;
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
    cout<<endl;
    cout<<"OTP will expire in 5 seconds....."<<endl;
    Sleep(1000);
	cout<<"Oops OTP is expired !!\n\n";
    int choice;
	cout<<"press 1 for new OTP generation"<<endl;
	cout<<"press 2 for exit \n\n";
	cin>>choice;

	switch(choice)
	{
		case 1: {system("CLS");

		        cout<<"New OTP : "<<OTPgenerator(n).c_str();

		     //   unsigned char* to_grain = reinterpret_cast<unsigned char*>(final_otp);
		      //  call_grain(to_grain);

		        Sleep(5);
		        break;
		}
		case 2:{ exit(0);
		        break;
		}
	}
}
int main() //main function
{

    int n = 6;
	//cout<<"Enter length :";
	//cin>>n;

	OTPgenerator(n);

    return 0;
}


