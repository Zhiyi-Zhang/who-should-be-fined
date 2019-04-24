#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "ot_receiver.h"

#include "ot_config.h"
#include "randombytes.h"
#include "network.h"
#include "cpucycles.h"

//A VERY simple and naive decryption.
void mydecrypt(char *buffer, char *key, char *AES_KEY)
{
	for (int i = 0; i < AES_KEY_BYTES; ++i)
		AES_KEY[i] = (buffer[i] - key[i] + 256) % 256;
}

//Print x in HEX system.
inline void print16(FILE *f, unsigned int x)
{
	if (x < 10) fprintf(f, "%d", x); else fprintf(f, "%c", 'A' + x - 10);
}

//Record sender's secrets.
void record(FILE *f, char *buffer, const unsigned len)
{
	for (unsigned long i = 0; i < len; ++i) {
		print16(f, (buffer[i] >> 4 + 16) & 15);
		print16(f, buffer[i] & 15);
	}
    fprintf(f, "\n");
}

void ot_receiver_test(RECEIVER * receiver, int sockfd)
{
	int i, j, k, number_of_ots;

	unsigned char Rs_pack[ 4 * PACKBYTES ];
	unsigned char keys[ 4 ][ HASHBYTES ];
	unsigned char cs[ 4 ];
	unsigned char AES_pack[2 * AES_KEY_BYTES];
	unsigned char AES_KEY[AES_KEY_BYTES];
	int choice[4];

	//Receiver_Secret.txt records all data sent or received by receiver. (in Hex system)
	FILE* fp;
	fp = fopen("Receiver_Secret.txt", "w");

	//Receiver_output.txt lists all AES keys finally received by receiver.
	FILE* output;
	output = fopen("Receiver_output.txt", "w");

	//input of receiver's choice.
	//The first line contains a number number_of_ots which indicates the number of OTs (must be multiple of 4).
	//For the following number_of_ots lines, each line contains 0 or 1 which indicates receiver's choice for each OT.
	FILE* input;
	input = fopen("Receiver_input.txt", "r");

	//
	fscanf(input, "%d\n", &number_of_ots);

	//Receiver read the shared secrets from sender before OT.
	reading(sockfd, receiver->S_pack, sizeof(receiver->S_pack));
	
	//Recording to Receiver_Secret.txt
	fprintf(fp, "SETUP:\n");
	fprintf(fp, "Received:\n");
	record(fp, receiver->S_pack, sizeof(receiver->S_pack));

	receiver_procS(receiver);

	//

	receiver_maketable(receiver);

	fprintf(fp, "=========================================\n\nTRANSMISSION:\n");
	for (i = 0; i < number_of_ots; i += 4)
	{
		for (j = 0; j < 4; j++)
		{
			//Read receiver's choice for these 4 OTs from Receiver_input.txt
			fscanf(input, "%d\n", &choice[i]);
			cs[j] = choice[i];

			if (VERBOSE) printf("%4d-th choose bit = %d\n", i+j, cs[j]);
		}

		receiver_rsgen(receiver, Rs_pack, cs);

		writing(sockfd, Rs_pack, sizeof(Rs_pack));

		//Recording to Receiver_Secret.txt
		fprintf(fp, "Round %d-%d:\n", i, i+3);
		fprintf(fp, "  Sent:\n  ");
		record(fp, Rs_pack, sizeof(Rs_pack));

		receiver_keygen(receiver, keys);
	
		//

		if (VERBOSE)
		{
			for (j = 0; j < 4; j++)
			{
				printf("%4d-th reciever key:", i+j);

				for (k = 0; k < HASHBYTES; k++) printf("%.2X", keys[j][k]);
				printf("\n");

				//Receive 2 AES keys.
				reading(sockfd, AES_pack, sizeof(AES_pack));
				
				//Recording to Receiver_Secret.txt
				fprintf(fp, "  Round %d:\n    Received:\n    ", i+j);
				record(fp, AES_pack, sizeof(AES_pack));
				
				//Decrypt one of the AES key which receiver can decrypt.
				if (cs[j] == 0) mydecrypt(AES_pack, keys[j], AES_KEY); else mydecrypt(AES_pack + AES_KEY_BYTES, keys[j], AES_KEY);

				//Write the decrypted AES key to Receiver_output.txt
				fprintf(output, "Turn %d: AES_key=%s\n", i+j, AES_KEY);
			}
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	fclose(input);
	fclose(output);
}


int main(int argc, char * argv[])
{
	int sockfd;
	int sndbuf = BUFSIZE;
	int flag = 1;

	long long t = 0;

	RECEIVER receiver;

	//

	if (argc != 3)
	{
		fprintf(stderr,"usage %s hostname port\n", argv[0]); exit(-1);
	}

	//

	client_connect(&sockfd, argv[1], atoi(argv[2]));

	if( setsockopt(sockfd,  SOL_SOCKET,   SO_SNDBUF, &sndbuf, sizeof(int)) != 0 ) { perror("ERROR setsockopt"); exit(-1); }
	if( setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY,   &flag, sizeof(int)) != 0 ) { perror("ERROR setsockopt"); exit(-1); }

t -= cpucycles_amd64cpuinfo();

	ot_receiver_test(&receiver, sockfd);

t += cpucycles_amd64cpuinfo();

	//

	if (!VERBOSE) printf("[n=%d] Elapsed time:  %lld cycles\n", NOTS, t);

	shutdown (sockfd, 2);

	//

	return 0;
}

