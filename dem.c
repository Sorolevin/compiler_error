#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM 100
#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define NEWLINE 22
#define ADD 30
#define SUBSTRACT 31
#define DIVIDE 32
#define MUL 33

#define POW 34
#define MOD 35

#define ENTSTR 50

#define PRTSTR 51

#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43
int main(void) {
  void dump_file(int word[]);

  FILE *cfPtr;

  char buf[5];
  void branch(int *cnt, int accum, int nxt, int comn);
  int buf_mem[100] = {0};
  void dump(int word[]);
  int x = 0, y = 0, s = 0;
  // int mem[MEM] = {0};
  int mem[MEM];

  for (; x != MEM; x++) {
    mem[x] = 0;
  }

  int acc = 0, d = 0;
  int ins_cnt = 0, ins_rgr = 0, op_code = 0, operand = 1;
  /*
    char *s_mem[MEM][4];


    memset(c_mem, 0, sizeof(mem));
    memset(s_mem, '0', sizeof(s_mem));
  */
  int b = 0, l, r = 0, m = 0, ti = 0, sign = 0;

  mem[0] = 2098;
  mem[1] = 2199;
  mem[2] = 2096;
  mem[3] = 2197;
  mem[4] = 1095;
  mem[5] = 2097;
  mem[6] = 3095;
  mem[7] = 2194;
  mem[8] = 2094;
  mem[9] = 2197;
  mem[10] = 2093;
  mem[11] = 3092;
  mem[12] = 2191;
  mem[13] = 2091;
  mem[14] = 2193;
  mem[15] = 2095;
  mem[16] = 3193;
  mem[17] = 4104;
  mem[18] = 2097;
  mem[19] = 3299;
  mem[20] = 2190;
  mem[21] = 2090;
  mem[22] = 2197;
  mem[23] = 1197;
  mem[24] = 4300;
  mem[98] = 7;
  mem[92] = 1;

  /*
       mem[0] = 2020;
       mem[1] = 3118;
       mem[2] = 4211;
       mem[3] = 1016;
       mem[4] = 2016;
       mem[5] = 3017;
       mem[6] = 2117;
       mem[7] = 2018;
       mem[8] = 3019;
       mem[9] = 2118;
       mem[10] = 4000;
       mem[11] = 2017;
       mem[12] = 3220;
       mem[13] = 2117;
       mem[14] = 1117;
       mem[15] = 4300;
       mem[16] = 0000;
       mem[17] = 0000;
       mem[18] = 0000;
       mem[19] = 0001;
       mem[20] = 0007;
   */
  /*
cfPtr = fopen("rtr.sml", "r");

    for (d = 0; feof(cfPtr) == 0; ++d) {
      fscanf(cfPtr, "%d\n", &mem[d]);

      // fgets ((char *)&s_mem[d][0], 100, cfPtr);
    }

    fclose(cfPtr);

  mem[96] = 1;
  */
  /*
    cfPtr = fopen("simp.base", "r");

    for (d = 0; feof(cfPtr) == 0; ++d) {
      fscanf(cfPtr, "%d %d\n", &y, &s);
      mem[y] = s;

      printf("%d %d\n", s, y);
    }

    fclose(cfPtr);
  */
  /*
    for (d = 0; c_mem[d] != 0; d++) {
      y = c_mem[d];
      s = c_mem[d];

      mem[y] = s;
      printf("%d %d\n", y, s);
    }
  */
  /*
    for (; (char)s_mem[b][0] != '0'; b++) {

      buf_mem[b] = strtol((void *)&s_mem[b][0], NULL, 10);

      //	sprintf((int)  &mem[b], "%d", s_mem[b][0]);
    }

  */

  while ((mem[operand] > -9999) && (mem[operand] < 9999) && sign != 1) {

    ins_rgr = (mem[ins_cnt]);

    op_code = (ins_rgr / 100);
    operand = (ins_rgr % 100);
    printf("op_code = %d   operand = %d  count = %d  acc = %d\n", op_code,
           operand, mem[97], acc);
    switch (op_code) {

    case HALT:
      sign = 1;
      break;

    case READ:
      printf("? read ");
      scanf("%d", &mem[operand]);
      ins_cnt++;
      break;

    case WRITE:
      printf("%d\n", mem[operand]);
      ins_cnt++;
      break;

    case LOAD:
      acc = mem[operand];
      ins_cnt++;
      break;

    case STORE:
      mem[operand] = acc;
      ins_cnt++;
      break;

    case ADD:
      acc += mem[operand];
      ins_cnt++;
      break;

    case SUBSTRACT:
      acc -= mem[operand];
      ins_cnt++;
      break;

    case DIVIDE:
      acc /= mem[operand];
      ins_cnt++;
      break;

    case MUL:
      acc *= mem[operand];
      ins_cnt++;
      break;

    case POW:
      acc = pow(acc, mem[operand]);
      ins_cnt++;
      break;

    case MOD:
      acc = fmod(acc, mem[operand]);
      ins_cnt++;
      break;

    case NEWLINE:
      puts(" ");
      ins_cnt++;
      break;

      /*
   case ENTSTR:
     b = operand;
     scanf("%s", *s_mem);
     l = r = (int)strlen(*s_mem);
     l *= 100;
     while (r) {
       mem[operand] =  (l + s_mem[m]);
       l -= 100;
       r--;
       operand++;
       m++;
     }
     break;
*/

      /*
      case PRTSTR:
        for (m = b; mem[m] / 100; m++) {
          printf("%0d\n", mem[m]);
        }
        break;
        */

    default:
      branch(&ins_cnt, acc, operand, op_code);
      break;
    }
  }

  dump(mem);
  dump_file(mem);
  puts(" ");
}

void branch(int *cnt, int accum, int nxt, int comn) {

  if (accum < -1) {
    *cnt = nxt;
  } else if (accum == 0) {
    *cnt = nxt;
  } else if (comn == 40) {
    *cnt = nxt;
  } else {
    (*cnt)++;
  }
}

void dump(int word[]) {
  int d = 0, x;
  printf("%3c", ' ');
  while (d != 10) {
    printf("%5d ", d);
    d++;
  }
  for (d = 0; d != MEM; d++) {
    x = word[d];
    if (0 == (d % 10))
      puts(" "), printf("%3d", d);
    printf(x >= 0 ? " +%.4X" : " %.4d", x);
  }
  puts(" ");
}

void dump_file(int word[]) {
  int d = 0, x;
  FILE *flrun;
  flrun = fopen("wrt.txt", "w+");

  fprintf(flrun, "%3c", ' ');
  while (d != 10) {
    fprintf(flrun, "%5d ", d);
    d++;
  }
  for (d = 0; d != MEM; d++) {
    x = word[d];
    if (0 == (d % 10))
      fprintf(flrun, "\n"), fprintf(flrun, "%3d", d);
    fprintf(flrun, x >= 0 ? " +%.4X" : " %.4d", x);
  }
}

long long_var(long var) {
  long step = 1;
  do {
    step *= 10;
  } while (var /= step);
  return (step / 10);
}
