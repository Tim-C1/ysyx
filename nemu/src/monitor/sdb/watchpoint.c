#include "sdb.h"

#define NR_WP 32

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */
  char *exp;
  uint64_t val;
} WP;

static WP wp_pool[NR_WP] = {};
static WP *free_ = NULL;
static WP head =  {-1, NULL, NULL, 0};

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

int new_wp(char *exp) {
    
    /* if the free_ points to NULL it means we reach the end of the free watchpoints list */
    if (free_ == NULL) {
        printf("no more free watchpoint ! \n");
        return -1;
        assert(0);
    }

    WP *fp = free_;
    free_->exp = exp;
    free_ = free_->next;
    fp->next = head.next;
    head.next = fp;
    return head.next->NO;
}

char* get_exp(int NO) {
    return wp_pool[NO].exp;
}


void free_wp_no(int NO) {
    WP *p = &head;
    if (p->next == NULL) {
        printf("no more watchpoint to delete\n");
        return;
    }
    while (p->next != NULL && p->next->NO != NO) {
        p = p->next;
    }
    if (p->next == NULL) {
        printf("the watchpoint: %d has not been used yet !\n", NO);
        return;
    }
    
    WP *q = p->next;
    p->next = p->next->next; 
    q->next = free_->next;
    free_->next = q;
    printf("the wp: %d has been deleted\n", q->NO);
    return;
}

int check_wp(void) {

  bool success = true;
  int has_changed = 0;
  WP *p = head.next;
  while (p != NULL) {
      uint64_t val = expr(p->exp, &success);
      if (!success) {
          printf("something wrong when expr !! \n");
          assert(0);
      }
      if (val != p->val) {
          printf("at watchpoint %d the exp:%s has changed, before: %lu, now: %lu \n", p->NO, p->exp, p->val, val);
          p->val = val;
          has_changed = 1;
      }
      p = p->next;
  }
  if (has_changed) {
      return 1;
  }
  return 0;
}


void display_all(void) {
    if (head.next == NULL) {
        printf("no watpoints in used ! \n");
        return;
    }
    for (WP *p = head.next; p != NULL; p = p->next) {
        printf("watchpoint: %d, the exp is: %s \n", p->NO, p->exp);
    }
    return;
}



