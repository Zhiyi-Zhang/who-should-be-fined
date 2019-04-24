#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "ot_sender.h"

#include "cpucycles.h"
#include "network.h"
#include "ot_config.h"

// A VERY simple and naive encryption.
void myencrypt(char *message, char *key, char *buffer) {
  for (int i = 0; i < AES_KEY_BYTES; ++i)
    buffer[i] = (message[i] + key[i]) % 256;
}

// Print x in HEX system.
inline void print16(FILE *f, unsigned int x) {
  if (x < 10)
    fprintf(f, "%d", x);
  else
    fprintf(f, "%c", 'A' + x - 10);
}

// Record sender's secrets.
void record(FILE *f, char *buffer, const unsigned len) {
  for (unsigned long i = 0; i < len; ++i) {
    print16(f, (buffer[i] >> 4 + 16) & 15);
    print16(f, buffer[i] & 15);
  }
  fprintf(f, "\n");
}

void ot_sender_test(SENDER *sender, int newsockfd) {
  int i, j, k, number_of_ots;
  unsigned char S_pack[PACKBYTES];
  unsigned char Rs_pack[4 * PACKBYTES];
  unsigned char keys[2][4][HASHBYTES];
  unsigned char all_AES_keys[2][AES_KEY_BYTES + 1];
  unsigned char AES_pack[2 * AES_KEY_BYTES];

  // input txt of AES keys
  // The first line contains a number number_of_ots which indicates the number
  // of OTs (must be multiple of 4). The following 2*number_of_ots lines contains
  // number_of_ots pairs of 16bytes AES keys.
  FILE *input;
  input = fopen("Sender_input.txt", "r");

  // Sender_Secret.txt records all data sent or received by sender. (in Hex
  // system)
  FILE *fp;
  fp = fopen("Sender_Secret.txt", "w");

  // Read number_of_ots.
  fscanf(input, "%d\n", &number_of_ots);

  // Sender send the shared secrets to receiver before OT.
  sender_genS(sender, S_pack);

  // Recording to Sender_Secret.txt
  writing(newsockfd, S_pack, sizeof(S_pack));
  fprintf(fp, "SETUP:\n");
  fprintf(fp, "Sent:\n");
  record(fp, S_pack, sizeof(S_pack));

  //
  fprintf(fp, "=========================================\n\nTRANSMISSION:\n");
  for (i = 0; i < number_of_ots; i += 4) {
    fprintf(fp, "Round %d-%d:\n", i, i + 3);
    reading(newsockfd, Rs_pack, sizeof(Rs_pack));

    // Recording to Sender_Secret.txt
    fprintf(fp, "  Received:\n  ");
    record(fp, Rs_pack, sizeof(Rs_pack));

    sender_keygen(sender, Rs_pack, keys);

    //

    if (VERBOSE) {
      for (j = 0; j < 4; j++) {
        printf("%4d-th sender keys:", i + j);

        for (k = 0; k < HASHBYTES; k++) printf("%.2X", keys[0][j][k]);
        printf(" ");
        for (k = 0; k < HASHBYTES; k++) printf("%.2X", keys[1][j][k]);
        printf("\n");

        // read one pair of AES keys
        for (int j = 0; j < 2; ++j) fscanf(input, "%s", all_AES_keys[j]);

        // Encrypt AES keys by the randomly generated keys above.
        myencrypt(all_AES_keys[0], keys[0][j], AES_pack);
        myencrypt(all_AES_keys[1], keys[1][j], AES_pack + AES_KEY_BYTES);

        // Send two encrypted AES keys to receiver.
        writing(newsockfd, AES_pack, sizeof(AES_pack));

        // Recording to Sender_Secret.txt
        fprintf(fp, "  Round %d:\n    Sent:\n    ", i + j);
        record(fp, AES_pack, sizeof(AES_pack));
      }

      printf("\n");
    }
    fprintf(fp, "\n");
  }
  fclose(input);
  fclose(fp);
}

int main(int argc, char *argv[]) {
  int sockfd;
  int newsockfd;
  int rcvbuf = BUFSIZE;
  int reuseaddr = 1;

  long long t = 0;

  SENDER sender;

  //

  if (argc != 2) {
    fprintf(stderr, "usage %s port\n", argv[0]);
    exit(-1);
  }

  //

  sockfd = server_listen(atoi(argv[1]));
  newsockfd = server_accept(sockfd);

  if (setsockopt(newsockfd, SOL_SOCKET, SO_RCVBUF, &rcvbuf, sizeof(rcvbuf)) !=
      0) {
    perror("ERROR setsockopt");
    exit(-1);
  }
  if (setsockopt(newsockfd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr,
                 sizeof(reuseaddr)) != 0) {
    perror("ERROR setsockopt");
    exit(-1);
  }

  t -= cpucycles_amd64cpuinfo();

  ot_sender_test(&sender, newsockfd);

  t += cpucycles_amd64cpuinfo();

  //

  if (!VERBOSE) printf("[n=%d] Elapsed time:  %lld cycles\n", NOTS, t);

  shutdown(newsockfd, 2);
  shutdown(sockfd, 2);

  //

  return 0;
}
