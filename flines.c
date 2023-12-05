#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// gcc flines.c -o flines.bin -O3 -Wall -march=native 

_Bool isgoodtext(char*text, char *goodchars) {
  uint8_t goodcharsarr[256] = {0};
  int goodcharslen = strlen(goodchars);
  long textlen = strlen(text);
  for (int i = 0; i<goodcharslen; i++) goodcharsarr[(uint8_t)goodchars[i]] = 1;
  for (long i = 0; i<textlen; i++) if (goodcharsarr[(uint8_t)text[i]] != 1) return false;
  return true;
} 

int32_t printlines(char*filename, FILE ** fp, int64_t linenum1, int64_t linenum2, _Bool printlinenumbers) {
  //printf("Printing lines %li to %li of %s\n", linenum1, linenum2, filename);
  if (linenum1 < 0) linenum1 = 0;
  if (linenum2 < linenum1) return 0;
  _Bool newline = true;
  int32_t bufferlen;
  char buffer[256] = {0};
  const int32_t buffersize = sizeof(buffer)/sizeof(buffer[0]);
  int64_t i;
  for (i=0; i<=linenum2; i++) {
    if (buffer != fgets(buffer, buffersize, *fp)) {
      if (feof(*fp)) {
        break;
      } else {
        fprintf(stderr, "fgets() read error!\n");
        return 1;
      }
    }
    if (i>=linenum1) {
      if (printlinenumbers && newline) {
        printf("%li %s", i, buffer);
      } else {
        printf("%s", buffer);
      }
    }
    bufferlen = strlen(buffer);
    if ((bufferlen == buffersize-1) && (buffer[bufferlen-1] != '\n')) {
      i--;
      newline = false;
    } else {
      newline = true;
    }
  }
  //printf("Printed %li lines.\n", i-linenum1);
  return 0;
}

int32_t printhelp() {
  printf("This program prints lines from a text file. The line number can be prepended to the output with the switch below.\n");
  printf("Usage:- ./flines.bin filename linenum1 [linenum2] [--linenumbers]\n");
  printf("e.g. ./flines.bin myfilename.txt 10 20 ...prints lines 10 to 20 of myfilename.txt.\n");
  exit(0);
}

int32_t main(int32_t argc, char* argv[]) {
  if (argc <= 1) printhelp();
#ifdef WIN32
  char * goodfilename_rx = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWZYZ0123456789_.\\"; 
#else
  char * goodfilename_rx = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWZYZ0123456789_./"; 
#endif
  int64_t linenum1, linenum2;
  _Bool printlinenumbers = false;
  if (!isgoodtext(argv[1], goodfilename_rx)) {
    printf("Unsupported filename.\n");
    exit(1);
  }
  FILE * fp;
  if (!(fp = fopen(argv[1], "r"))) {
    printf("Invalid filename.\n");
    exit(1);
  }
  if (argc >= 3) {
    linenum1 = atol(argv[2]);
    if (argc >= 4) {
      if (strcmp(argv[3], "--linenumbers") == 0) {
        printlinenumbers = true;
        linenum2 = linenum1 + 20;
      } else {
        linenum2 = atol(argv[3]);
      }
      if (argc >= 5) {
        if (strcmp(argv[4], "--linenumbers") == 0) printlinenumbers = true;
      }
    } else {
      linenum2 = linenum1 + 20;
    }
    printlines(argv[1], &fp, linenum1, linenum2, printlinenumbers);  
  };
  fclose(fp);
}
