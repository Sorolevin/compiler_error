#include "simltron_include.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int evaluatePostfixExpression_2(char *, int memory_smp[], int *count_command);
int calculate_2(int, int, char, int memory_smp[], int *count_command);

int main(void) {
  int search_flag(data * base, int noname);
  char infix[150];
  char postfix[150];
  int line_simple_comands_input_print(int cmd, data *table, int token,
                                      int memory[]);
  
  int past_in_table_cons_or_value(data * table, char *str_tok);
  int goto_search(data * table, char *token);
  int count_st = 0;
  int search_cmd(char *dict[15], char *token);
  char *comparison_signs = "> < <= >= == !=";
  int token_string_count = 0;
  data symbolTable[100];
  int cnt = 0;
  int d = 0;
  int flags[100];
  int dz = 0;
  int mem_smp[100];
  char copy_buf_data[150][150] = {{0}};
  char post_buf[150];
  int count_cmd = 0;
  int lng = 0;
  int sign_ch;
  FILE *file_buf;
  char *buffer = 0;
  char *intro_buffer = 0;
  int save_left_side = 0, save_exp = 0;
  int goto_flag = 0;
  int count_table_intro = 0;
  int count_table_extra = 0;
  char buffer_postfix[150];
  char buf_data[150][150] = {{0}};
  int val_if[2] = {0};
  int second_buf = 0;
 
  for (; d != 100; d++) {
    strcpy((symbolTable + d)->symbol, "0");
    (symbolTable + d)->location = 0;
    (symbolTable + d)->type = 'q';
    mem_smp[d] = 0;
    flags[d] = -1;
  }
  
  file_buf = fopen("file.smp", "r");
  
  for (d = 0; feof(file_buf) == 0; ++d) {
    fgets(&buf_data[d][0], 150, file_buf);
  }
  fclose(file_buf);
  memcpy(copy_buf_data, buf_data, sizeof(char) * 150 * 150);
  
  for (d = 0; buf_data[d][0] != 0; d++) {

    buffer = strtok(&buf_data[d][0], " ");

    for (; buffer != NULL; buffer = strtok(NULL, " ")) {

      if (token_string_count == 0 && my_isdigit(*buffer)) {

        count_table_intro = search_in_base(symbolTable, buffer);

        strcpy((symbolTable + count_table_intro)->symbol, buffer);

        (symbolTable + count_table_intro)->type = 'L';

        (symbolTable + count_table_intro)->location = count_table_extra;
      }

      if (rem_break(buffer) == 1) {

        (symbolTable + count_table_intro)->location = count_table_extra;

        break;
      }

      else if (strcmp(buffer, "let") == 0) {

        strcpy(infix, &copy_buf_data[d][7]);
        convertToPostfix_1(infix, postfix);
        save_left_side = let_past(symbolTable, postfix, post_buf);

        save_exp = evaluatePostfixExpression_2(post_buf, mem_smp, &count_cmd);
        mem_smp[count_cmd] = (2000 + save_exp);
        count_cmd++;

        mem_smp[count_cmd] = (2100 + save_left_side);
        count_cmd++;

      }

      else if (strcmp(buffer, "if") == 0) {
        cnt = 0;

        second_buf = 0;
        for (dz = 0; intro_buffer != (char *)'\0';
             intro_buffer = strtok(NULL, " ")) {

          if (!strcmp(intro_buffer, "goto")) {
            goto_flag = 0;
            intro_buffer = strtok(NULL, " ");

            second_buf = goto_search(symbolTable, intro_buffer);

            if (second_buf == 0) {
              second_buf = atoi(intro_buffer);
              goto_flag = 1;
            }

          }

          else if (strstr(comparison_signs, intro_buffer)) {

            if (strcmp(intro_buffer, "==") == 0) {
              sign_ch = 0;
            } else if (strcmp(intro_buffer, "!=") == 0) {
              sign_ch = 1;
            } else if (strcmp(intro_buffer, "<=") == 0) {
              sign_ch = 2;
            } else if (strcmp(intro_buffer, "<") == 0) {
              sign_ch = 3;
            } else if (strcmp(intro_buffer, ">=") == 0) {
              sign_ch = 4;
            } else if (strcmp(intro_buffer, ">") == 0) {
              sign_ch = 5;
            }

          }

          else if (isalnum(*intro_buffer)) {
            past_in_table_cons_or_value(symbolTable, intro_buffer);

            val_if[cnt++] = search_in_table(symbolTable, intro_buffer);
          }
        }

        if (sign_ch == 0) {
          mem_smp[count_cmd] = 2000 + (symbolTable + val_if[1])->location;
          count_cmd++;
          mem_smp[count_cmd] = 3100 + (symbolTable + val_if[0])->location;
          count_cmd++;
          if (goto_flag == 1) {
            flags[count_cmd] = second_buf;
            mem_smp[count_cmd] = 4200;
            count_cmd++;
          } else {
            mem_smp[count_cmd] = 4200 + second_buf;
            count_cmd++;
          }

        } else if (sign_ch == 1) {
          mem_smp[count_cmd] = 2000 + (symbolTable + val_if[0])->location;
          count_cmd++;
          mem_smp[count_cmd] = 3100 + (symbolTable + val_if[1])->location;
          count_cmd++;

          if (goto_flag == 1) {
            flags[count_cmd] = second_buf;
            mem_smp[count_cmd] = 4100;
            count_cmd++;
          } else {
            mem_smp[count_cmd] = 4100 + second_buf;
            count_cmd++;
          }
          /*
           mem_smp[count_cmd] = 2000 + (symbolTable + val_if[0])->location;
           count_cmd++;
           mem_smp[count_cmd] = 3100 + (symbolTable + val_if[1])->location;
           count_cmd++;

           if (goto_flag == 1) {
             flags[count_cmd] = second_buf;
             mem_smp[count_cmd] = 4100;
             count_cmd++;
           } else {
             mem_smp[count_cmd] = 4100 + second_buf;
             count_cmd++;
           }
         */

        }

        else if (sign_ch == 2) {
          mem_smp[count_cmd] = 2000 + (symbolTable + val_if[1])->location;
          count_cmd++;
          mem_smp[count_cmd] = 3100 + (symbolTable + val_if[0])->location;
          count_cmd++;

          if (goto_flag == 1) {
            flags[count_cmd] = second_buf;
            mem_smp[count_cmd] = 4200;
            count_cmd++;
          } else {
            mem_smp[count_cmd] = 4200 + second_buf;
            count_cmd++;
          }

          mem_smp[count_cmd] = 2000 + (symbolTable + val_if[0])->location;
          count_cmd++;
          mem_smp[count_cmd] = 3100 + (symbolTable + val_if[1])->location;
          count_cmd++;

          if (goto_flag == 1) {
            flags[count_cmd] = second_buf;
            mem_smp[count_cmd] = 4100;
            count_cmd++;
          } else {
            mem_smp[count_cmd] = 4100 + second_buf;
            count_cmd++;
          }
        } else if (sign_ch == 3) {

          mem_smp[count_cmd] = 2000 + (symbolTable + val_if[0])->location;
          count_cmd++;
          mem_smp[count_cmd] = 3100 + (symbolTable + val_if[1])->location;
          count_cmd++;

          if (goto_flag == 1) {
            flags[count_cmd] = second_buf;
            mem_smp[count_cmd] = 4100;
            count_cmd++;
          } else {
            mem_smp[count_cmd] = 4100 + second_buf;
            count_cmd++;
          }
        } else if (sign_ch == 4) {

          mem_smp[count_cmd] = 2000 + (symbolTable + val_if[1])->location;
          count_cmd++;
          mem_smp[count_cmd] = 3100 + (symbolTable + val_if[0])->location;
          count_cmd++;

          if (goto_flag == 1) {
            flags[count_cmd] = second_buf;
            mem_smp[count_cmd] = 4200;
            count_cmd++;
          } else {
            mem_smp[count_cmd] = 4200 + second_buf;
            count_cmd++;
          }

          mem_smp[count_cmd] = 2000 + (symbolTable + val_if[0])->location;
          count_cmd++;
          mem_smp[count_cmd] = 3100 + (symbolTable + val_if[1])->location;
          count_cmd++;

          if (goto_flag == 1) {
            flags[count_cmd] = second_buf;
            mem_smp[count_cmd] = 4100;
            count_cmd++;
          } else {
            mem_smp[count_cmd] = 4100 + second_buf;
            count_cmd++;
          }
        } else if (sign_ch == 5) {
          mem_smp[count_cmd] = 2000 + (symbolTable + val_if[0])->location;
          count_cmd++;
          mem_smp[count_cmd] = 3100 + (symbolTable + val_if[1])->location;
          count_cmd++;

          if (goto_flag == 1) {
            flags[count_cmd] = second_buf;
            mem_smp[count_cmd] = 4100;
            count_cmd++;
          } else {
            mem_smp[count_cmd] = 4100 + second_buf;
            count_cmd++;
          }
        }
      }

      else if (strcmp(buffer, "goto") == 0) {

        second_buf = 0;
        goto_flag = 0;

        intro_buffer = strtok(NULL, " ");
        second_buf = goto_search(symbolTable, intro_buffer);

        if (second_buf == 0) {
          second_buf = atoi(intro_buffer);
          goto_flag = 1;
        }

        if (goto_flag == 1) {
          flags[count_cmd] = second_buf;
          mem_smp[count_cmd] = 4000;
          count_cmd++;
        } else {
          mem_smp[count_cmd] = 4000 + second_buf;
          count_cmd++;
        }
      }

      else if (strcmp(buffer, "print") == 0) {
        intro_buffer = strtok(NULL, " ");
        second_buf = search_in_table(symbolTable, intro_buffer);
        mem_smp[count_cmd] = 1100 + (symbolTable + second_buf)->location;
        count_cmd++;

      }

      else if (strcmp(buffer, "input") == 0) {
        intro_buffer = strtok(NULL, " ");
        past_in_table_cons_or_value(symbolTable, intro_buffer);
        second_buf = search_in_table(symbolTable, intro_buffer);
        mem_smp[count_cmd] = 1000 + (symbolTable + second_buf)->location;
        count_cmd++;
      } else if (strcmp(buffer, "end") == 0) {

        mem_smp[count_cmd] = 4300;
      }

      ////////////////////////////////////////////////////////////////////////
      count_table_extra = count_cmd;
      /////////////////////////////////////////////////////////////////////////
    }
  }

  for (d = 0; mem_smp[d] != 0; d++) {
    if (flags[d] != -1) {

      sprintf(&postfix[0], "%d", flags[d]);

      goto_flag = search_in_table(symbolTable, postfix);
      mem_smp[d] += (symbolTable + goto_flag)->location;
    }
  }

  for (d = 0; (symbolTable + d)->type != 'q'; d++) {

    printf("%s - %c - %d \n", (symbolTable + d)->symbol,
           (symbolTable + d)->type, (symbolTable + d)->location);
  }

  file_buf = fopen("simp.base", "w");

  for (d = 0; (symbolTable + d)->type != 'q'; d++) {

    if ((symbolTable + d)->type != 'V') {

      fprintf(file_buf, "%d %s\n", (symbolTable + d)->location,
              (symbolTable + d)->symbol);
    }
  }

  fclose(file_buf);

  file_buf = fopen("rtr.sml", "w");

  for (d = 0; mem_smp[d] != 0; d++) {
    fprintf(file_buf, "mem[%d] = %d;\n", d, mem_smp[d]);
  }

  fclose(file_buf);

  for (d = 0; mem_smp[d] != 0; d++) {
    printf("%d\n", mem_smp[d]);
  }

  return 0;
}

int past_in_table_cons_or_value(data *table, char *str_tok) {

  int search_in_table(data * intro_search, char *str_tok_search);

  int find = search_in_table(table, str_tok);

  if ((table + find)->type == 'q') {

    if (my_isalpha(*str_tok)) {
      (table + find)->symbol[0] = *str_tok; //  or  str_tok don't atoi

    } else {
      strcpy((table + find)->symbol, str_tok);
    }

    (table + find)->type = my_isalpha(*str_tok) ? 'V' : 'C';

    (table + find)->location = count_down;

    count_down--;
  }

  return (table + find)->location;
}

int evaluatePostfixExpression_2(char *expr, int memory_smp[],
                                int *count_command) {
  StackNodePtr_2 stackPtr = NULL;
  char c;
  int x, y;
  int i = 0, mult = 1, num = 0;

  while (expr[i] != '\0') {
    mult = 1;
    num = 0;
    c = expr[i];
    if (my_isdigit(c)) {
      while (my_isdigit(c)) {
        num *= mult;
        num += c - 48;
        c = expr[++i];
        mult *= 10;
      }
      --i;
      push_2(&stackPtr, num);
    } else if (isOperator_2(c)) {
      if (isEmpty_2(stackPtr)) {
        printf("Invalid postfix expression!\n");
        return 0;
      }
      x = pop_2(&stackPtr);

      if (isEmpty_2(stackPtr)) {
        printf("Invalid postfix expression!\n");
        return 0;
      }
      y = pop_2(&stackPtr);

      push_2(&stackPtr, calculate_2(y, x, c, memory_smp, &(*count_command)));
    }
    i++;
  }

  if (isEmpty_2(stackPtr)) {
    printf("Invalid postfix expression!\n");
    return 0;
  }

  return pop_2(&stackPtr);
}

int calculate_2(int op1, int op2, char operator, int memory_smp[],
                int *count_command) {

  int result = 0;

  switch (operator) {
  case '+':

    memory_smp[*count_command] = (2000 + op1);
    (*count_command)++;

    memory_smp[*count_command] = (3000 + op2);
    (*count_command)++;

    memory_smp[*count_command] = (2100 + count_down);

    (*count_command)++;
    result = count_down;
    count_down--;

    // result = op1 + op2;
    break;
  case '-':
    memory_smp[*count_command] = (2000 + op1);
    (*count_command)++;
    memory_smp[*count_command] = (3100 + op2);
    (*count_command)++;
    memory_smp[*count_command] = (2100 + count_down);
    (*count_command)++;
    result = count_down;
    count_down--;
    // result = op1 - op2;
    break;
  case '*':
    memory_smp[*count_command] = (2000 + op1);
    (*count_command)++;
    memory_smp[*count_command] = (3300 + op2);
    (*count_command)++;
    memory_smp[*count_command] = (2100 + count_down);
    (*count_command)++;
    result = count_down;
    count_down--;
    // result = op1 * op2;
    break;
  case '/':

    memory_smp[*count_command] = (2000 + op1);
    (*count_command)++;
    memory_smp[*count_command] = (3200 + op2);
    (*count_command)++;
    memory_smp[*count_command] = (2100 + count_down);
    (*count_command)++;
    result = count_down;
    count_down--;
    //   result = op1 / op2;
    break;
  /*
  case '^':
    result = pow(op1, op2);
    break;
  case '%':
    result = op1 % op2;
    break;
  */
  default:
    break;
  }

  return result;
}
