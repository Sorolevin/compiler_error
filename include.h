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
#define ADD 30
#define SUBSTRACT 31
#define DIVIDE 32
#define MUL 33
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

int count_down = 99;

struct stackNode_2 {
  int data;
  struct stackNode_2 *nextPtr;
};

typedef struct stackNode_2 StackNode_2;
typedef StackNode_2 *StackNodePtr_2;

typedef struct tableEntry {
  char symbol[10];
  char type;
  int location;

} data;

int my_isdigit(char alpha);
int my_isalpha(char alpha);
int isOperator_2(char c);

char stackTop_1(StackNodePtr_2 topPtr);

int helper_search_1(data *base, char *token, int run);

int helper_search_2(data *base, char *token, int run);

int (*helper_search[2])(data *base, char *token, int run) = {helper_search_1,
                                                             helper_search_2};

int search_in_base(data *intro_search, char *str_tok_search);
int helper_search_base(data *base, char *token, int run);

void convertToPostfix_1(char infix[], char postfix[]);

int pop_2(StackNodePtr_2 *topPtr);
void push_2(StackNodePtr_2 *topPtr, int info);
int isEmpty_2(StackNodePtr_2 topPtr);

int precedence_1(char operator1, char operator2);

void convertToPostfix_1(char infix[], char postfix[]) {
  int i = 0, j = 0;
  char c;

  /* Push left parenthesis to stack */
  StackNodePtr_2 stackPtr = NULL;
  push_2(&stackPtr, '(');

  /* Add right parenthesis to end of infix */
  while (infix[i] != '\0')
    i++;

  infix[i++] = ')';
  infix[i] = '\0';

  i = 0;

  /* Do the conversion */
  while (!isEmpty_2(stackPtr) && infix[i] != '\0') {
    c = infix[i++];

    if (my_isdigit(c) || my_isalpha(c)) {
      while (my_isdigit(c) || my_isalpha(c)) {
        postfix[j++] = c;
        c = infix[i++];
      }
      postfix[j++] = ' ';

      if (c == ')' || isOperator_2(c))
        i--;
    } else if (c == '(')
      push_2(&stackPtr, '(');
    else if (isOperator_2(c) == 1) {
      if (!isEmpty_2(stackPtr) && isOperator_2(stackTop_1(stackPtr))) {
        while (isOperator_2(stackTop_1(stackPtr)) &&
               (precedence_1(stackTop_1(stackPtr), c)) >= 0) {
          postfix[j++] = pop_2(&stackPtr);
          postfix[j++] = ' ';
        }
        push_2(&stackPtr, c);
      } else
        push_2(&stackPtr, c);
    } else if (c == ')') {
      if (!isEmpty_2(stackPtr)) {
        c = pop_2(&stackPtr);

        while (!isEmpty_2(stackPtr) && c != '(') {
          postfix[j++] = c;
          postfix[j++] = ' ';
          c = pop_2(&stackPtr);
        }
      }
    }
  }
  postfix[j] = '\0';
}

int precedence_1(char operator1, char operator2) {
  int result = 1;

  switch (operator1) {
  case '^':
    if (operator2 == '^')
      result = 0;
    break;
  case '*':
  case '/':
  case '%':
    switch (operator2) {
    case '^':
      result = -1;
      break;
    case '*':
    case '/':
    case '%':
      result = 0;
      break;
    default:
      break;
    }
    break;
  case '+':
  case '-':
    switch (operator2) {
    case '-':
    case '+':
      result = 0;
      break;
    default:
      result = -1;
      break;
    }
    break;
  }

  return result;
}

void push_2(StackNodePtr_2 *topPtr, int info) {
  StackNodePtr_2 newPtr;

  newPtr = malloc(sizeof(StackNode_2)); /* Now points to a place in memory*/

  if (newPtr != NULL) {
    newPtr->data = info;
    newPtr->nextPtr = *topPtr;
    *topPtr = newPtr;
  } else
    printf("%c not inserted. No memory available.\n", info);
}

int pop_2(StackNodePtr_2 *topPtr) {
  StackNodePtr_2 tempPtr;
  int popValue;

  tempPtr = *topPtr;
  popValue = (*topPtr)->data;
  *topPtr = (*topPtr)->nextPtr;
  free(tempPtr);

  return popValue;
}

/* Return the value at the top of the stack */
char stackTop_1(StackNodePtr_2 topPtr) {
  char topValue;

  topValue = topPtr->data;

  return topValue;
}

int isEmpty_2(StackNodePtr_2 topPtr) { return topPtr == NULL; }

/* Test if the list is empty */

int my_isalpha(char alpha) {
  return ((alpha >= 65 && alpha <= 90) || (alpha >= 97 && alpha <= 122));
}

int my_isdigit(char alpha) { return (alpha >= 48) && (alpha <= 57); }

int isOperator_2(char c) {

  return c == '/' || c == '*' || c == '-' || c == '+' || c == '^' || c == '%';
}

int goto_search(data *table, char *token) {

  int x = 0;

  for (x = 0; x != 100; x++) {

    if (memcmp((table + x)->symbol, token, 2) == 0) {
      return (table + x)->location;
    }
  }
  return 0;
}

int helper_search_1(data *base, char *token, int run) {
  return ((base + run)->symbol[0] == *token ||
          strcmp((base + run)->symbol, "0") == 0);
}

int helper_search_2(data *base, char *token, int run) {
  return (strcmp((base + run)->symbol, token) == 0 ||
          strcmp((base + run)->symbol, "0") == 0);
}

int search_in_base(data *intro_search, char *str_tok_search) {

  int runner = 0, ch = !my_isalpha(*str_tok_search);
  for (; !helper_search_base(intro_search, str_tok_search, runner); ++runner)
    ;
  return runner;
}
int helper_search_base(data *base, char *token, int run) {
  return strcmp((base + run)->symbol, "0") == 0;
}

int search_in_table(data *intro_search, char *str_tok_search) {

  int runner = 0, ch = !my_isalpha(*str_tok_search);
  for (; !(*helper_search[ch])(intro_search, str_tok_search, runner); ++runner)
    ;
  return runner;
}

int rem_break(char *token) {

  if (memcmp(token, "rem", 3) == 0) {
    return 1;
  }
  return 0;
}

int let_past(data *base, char *infix, char *post_infix) {
  char *buffer;

  int past_in_table_cons_or_value(data * table, char *str_tok);
  int data_adress = 0;
  int lng = 0;
  int left_side = 0;

  past_in_table_cons_or_value(base, &infix[0]);

  buffer = strtok(&infix[1], "  ");

  for (; buffer != (char *)'\0';
       post_infix[lng++] = ' ', buffer = strtok(NULL, " ")) {

    if (isalnum(*buffer)) {

      data_adress = past_in_table_cons_or_value(base, buffer);

      sprintf(&post_infix[lng], "%d", data_adress);

      lng += 2;
    }

    else {
      post_infix[lng] = *buffer;
      lng++;
    }
  }

  post_infix[lng] = '\0';
  left_side = search_in_table(base, &infix[0]);

  return (base + left_side)->location;
}
