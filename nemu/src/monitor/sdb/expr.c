#include <isa.h>
#include <memory/vaddr.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum {
  TK_NOTYPE = 256, TK_EQ,

  /* TODO: Add more token types */
  TK_DEC, TK_HEX, TK_REG, TK_NEQ, TK_AND, TK_DEREF,
};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"0[xX][0-9a-fA-F]+", TK_HEX}, // hexadecimal number
  {"[0-9]+", TK_DEC},   // decimal number
  //{"(\\$[0a-zA-Z]+)|([xX][0-9]+)", TK_REG},  // reg name
  {"(\\$[0a-zA-Z]+)|(\\$[a-zA-Z][0-9])", TK_REG},  // reg name
  {"\\+", '+'},         // plus
  {"==", TK_EQ},        // equal
  {"-", '-'},		    // minus
  {"\\*", '*'},         // pointer and mult
  {"\\/", '/'},          // lslash
  {"\\(", '('},          // lparenthesis
  {"\\)", ')'},          // rparenthesis
  {"!=", TK_NEQ},  // not equal
  {"&&", TK_AND}, // and
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
  Log("finish init regex\n");
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[9999] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        // Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
        //     i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
          default: 
            /* the token is operator, just store the type */
            tokens[nr_token].type = rules[i].token_type;
            nr_token++;
            break;

          case TK_NOTYPE:
            /* the token is blank, skip */
            break;

          case TK_DEC:
            /* the token is decimal number, store the value and type, here I have NOT deal with overflow */
            tokens[nr_token].type = rules[i].token_type;
            strncpy(tokens[nr_token].str, substr_start, substr_len);
            nr_token++;
            break;

          case TK_HEX:
            /* like the decimal number */
            tokens[nr_token].type = rules[i].token_type;
            strncpy(tokens[nr_token].str, substr_start, substr_len);
            nr_token++;
            break;
          
          case TK_REG:
            /* store the reg address */
            tokens[nr_token].type = rules[i].token_type;
            strncpy(tokens[nr_token].str, substr_start, substr_len);
            nr_token++;
            break;

        }

    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
      }
    }
  }
  return true;
}

int check_parentheses(int p, int q) {
    /* try to use STACK to implement */
    char p_stack[100];
    int NOT_BNF = 0;
    int NOT_MATCH = 0;
    int NOT_LR = 0;
    int idx = p; 
    /* check if the whole expression is surrounded by ( and ) */
    if (tokens[p].type != '(' || tokens[q].type != ')') {
       NOT_BNF = 1;
    } 

    int sp = 0;
    while (idx <= q) {
        /* if the token is ( put it in the stack and go to next token */
        if (tokens[idx].type == '(') {
            p_stack[sp] = '(';
            sp++;
            idx++;
        /* if the token is ), then the stack should contain at least one ( or it's wrong */
        } else if (tokens[idx].type == ')') {
            if (p_stack[--sp] == '(' && sp >= 0) {
                if (sp == 0 && idx != q) {
                    NOT_LR = 1;
                }
            } else {
                NOT_MATCH = 1;
                break;
            }
            idx++;
        /* the token is a number or operator skip */
        } else {
            idx++;
        }
    }
    if (sp != 0) {
        NOT_MATCH = 1;
    }
    
    /* return different flag for eval to determine */
    if (NOT_MATCH) {
        return -1;
    } else {
        if (NOT_BNF || NOT_LR) {
            return 2;
        } else {
            return 0;
        }
    }
}

int get_op(int p, int q) {
    /* op stores all the operator in order and loc_op stores the location in the expression of each operator */
    int idx = p;
    Token op[100];
    int loc_op[100] = { 0 };
    int num = 0;
    
    while (idx <= q) {
        /* ignore the sub expression in ( ) */
        if (tokens[idx].type == '(') {
            int num_p = 1;
            while (num_p != 0) {
                idx++;
                if (tokens[idx].type == '(') {
                    num_p++;
                } else if (tokens[idx].type == ')') {
                    num_p--;
                } else {
                    continue;
                }
            }
            idx++;
        /* ignore digit , hex, reg */
        } else if (tokens[idx].type == TK_DEC || tokens[idx].type == ')' || tokens[idx].type == TK_REG || tokens[idx].type == TK_HEX) {
            idx++;
        /* store the possible operator and its location */
        } else {
            op[num] = tokens[idx];
            loc_op[num] = idx;
            num++;
            idx++;
        }
    }
    
    /* find the pivot operator in op */
    int idx_op = 0;
    Token pivot;
    pivot = op[idx_op];
    int pivot_loc = loc_op[idx_op];
    while (++idx_op < num) {
        /* && has lowest priority, only when the next is also && will the pivot change */
        if (pivot.type == TK_AND) {
            if (op[idx_op].type == TK_AND) {
                pivot = op[idx_op];
                pivot_loc = loc_op[idx_op];
            }
        /* consider == and != */
        } else if (pivot.type == TK_EQ || pivot.type == TK_NEQ) {
            if (op[idx_op].type == TK_EQ || op[idx_op].type == TK_NEQ || op[idx_op].type == TK_AND) {
                pivot = op[idx_op];
                pivot_loc = loc_op[idx_op];
            }
        /* consider + and - */
        } else if (pivot.type == '+' || pivot.type == '-'){
            if (op[idx_op].type == '+' || op[idx_op].type == '-' || op[idx_op].type == TK_EQ || op[idx_op].type == TK_NEQ || op[idx_op].type == TK_AND) {
                pivot = op[idx_op];
                pivot_loc = loc_op[idx_op];
            }
        /* consider * and / */
        } else if (pivot.type == '*' || pivot.type == '/') {
            if (op[idx_op].type == '*' || op[idx_op].type == '/' ||op[idx_op].type == '+' || op[idx_op].type == '-' || op[idx_op].type == TK_EQ || op[idx_op].type == TK_NEQ || op[idx_op].type == TK_AND) {
                pivot = op[idx_op];
                pivot_loc = loc_op[idx_op];
            }
        /* consider pointer */
        } else {
            pivot = op[idx_op];
            pivot_loc = loc_op[idx_op];
        }
    }      
                
    return pivot_loc;
}

uint64_t eval(int p, int q) {
    if (p > q) {
        printf("bad expression at p = %d, q = %d \n",p ,q);
        return 0;
    } else if (p == q) {
        uint64_t val;
        bool success;
        if (tokens[p].type == TK_DEC) {
            val = atoi(tokens[p].str);
        } else if (tokens[p].type == TK_HEX) {
            sscanf(tokens[p].str+2, "%lx", &val); 
        } else {
            val = isa_reg_str2val(tokens[p].str+1, &success);
        }
        return val;
    } else {
        int flag = check_parentheses(p, q);

        if (flag == 0) {
            return eval(p+1, q-1);
        } else if (flag == -1) {
            printf("wrong expression: !!! \n");
            return 0;
        } else {
            int op = get_op(p, q);
            uint64_t addr;
            if (tokens[op].type == TK_DEREF) {
                addr = eval(op+1, q);
                printf("accessing address: %lu \n", addr);
                return 0; 
            }
            uint64_t val1 = eval(p, op-1);
            uint64_t val2 = eval(op+1, q);

            switch (tokens[op].type) {
                case '+': return val1 + val2;
                case '-': return val1 - val2;
                case '*': return val1 * val2;
                case '/': return val1 / val2;
                case TK_EQ: return val1 == val2;
                case TK_NEQ: return val1 != val2;
                case TK_AND: return val1 && val2;
                default: assert(0);
            }
        }
    }
}

word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
  
  int i;
  for (i = 0; i < nr_token; i++) {
      if (tokens[i].type == '*' && (i == 0 || (tokens[i-1].type == '+' || tokens[i-1].type == '-' || tokens[i-1].type == '(') ) ) {
          tokens[i].type = TK_DEREF;
      }
  }
  return eval(0, nr_token-1) ;
}
