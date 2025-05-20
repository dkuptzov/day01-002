#include "reg.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "malloc.h"
#include "print.h"

int work_with_reg(const short *args, const char *search_queries,
                  const char *str, struct param *param) {
  int value = 0;
  long int len_search_q = 1024;
  regex_t rx;
  char *search_q = calloc(len_search_q + 1, sizeof(char));
  if (search_q == NULL)
    param->error = 2;
  else {
    int count = 0;
    for (int i = 0; i < (int)strlen(search_queries); i++) {
      if (search_queries[i] != '\n') {
        search_q[count++] = search_queries[i];
        if (count >= len_search_q - 100) {
          len_search_q *= 2;
          char *temp = realloc(search_q, (len_search_q * sizeof(char)) + 1);
          if (temp == NULL) {
            param->error = 2;
            break;
          } else
            search_q = temp;
        }
      } else {
        search_q[count] = '\0';
        if (args[1] == 1)
          value = regcomp(&rx, search_q, REG_ICASE);
        else
          value = regcomp(&rx, search_q, 0);
        if (value != 0) {
          param->error = 1;
          break;
        } else {
          value = regexec(&rx, str, 0, NULL, 0);
          regfree(&rx);
        }
        count = 0;
        memset(search_q, 0, len_search_q);
        if (value == 0) break;
      }
    }
  }
  free(search_q);
  return value;
}
/*
int work_with_reg_o(const short *args, const char *search_queries, char *str,
                    const char *file_name, int count_files, int *string_count,
                    struct param *param) {
  int val = 0;
  position pos = {37000, 0, 0, 0, 0};
  regex_t rx;
  size_t nmatch = 1;
  regmatch_t pmatch[nmatch];
  long int len_search_q = 1024, len_print = 1024;
  char *search_q = calloc(len_search_q + 1, sizeof(char));
  char *print = calloc(len_print + 1, sizeof(char));
  if (search_q == NULL || print == NULL) param->error = 2;
  char *ptr = str;
  ptr[(int)strlen(ptr) - 1] = '\0';
  while (pos.next_position == 0 && param->error == 0) {
    pos.next_position = 1;
    for (int i = 0; i < (int)strlen(search_queries); i++) {
      int ready = 0;
      //int a;
      //scanf("%d", &a);
      printf("TUT1\n");
      printf("ptr: %s*\n", ptr);
      if (pos.count > len_search_q - 100) {
        printf("TUT111111111111111111111111111111111\n");
        len_search_q *= 2;
        char *temp = realloc(search_q, (len_search_q * sizeof(char)) + 1);
        //param->error = 2;
        if (temp == NULL) {
          param->error = 2;
          break;
        } else
            search_q = temp;
      }
      //printf("STR1: %s ***\n", search_q);
      //////////////////////////////////////////////////
      //printf("SEARCH %s ***\n", str);
      //int a;
      //scanf("%d", &a);
      if (search_queries[i] != '\n') {
        printf("TUT2\n");
        search_q[pos.count++] = search_queries[i];
      }
      else {
        printf("TUT3\n");
        printf("search_q: %s*\n", search_q);
        ready = 1;
        search_q[pos.count] = '\0';
        pos.count = 0;
        val = (args[1] == 1) ? regcomp(&rx, search_q, REG_ICASE)
                             : regcomp(&rx, search_q, 0);
      }
      //printf("STR2: %s ***\n", search_q);
      if (ready == 1 && val != 0) {
        printf("TUT4\n");
        param->error = 1;
      }
      else if (val == 0 && ready == 1 && (int)strlen(search_q) > 0) {
        printf("TUT5\n");
        val = regexec(&rx, ptr, nmatch, pmatch, 0);
        printf("val: %d*\n", val);
        regfree(&rx);
        //ready = 0;
        if (val == 0 && args[4] == 1) {
          printf("TUT6\n");
          break;
        }
        else if ((val == 0 && args[3] == 1) || (val != 0 && args[2] == 1)) {
          printf("TUT7\n");
          *string_count += 1;
          break;
        } else if (val == 0 && args[2] == 0 &&
                   (long int)pmatch[0].rm_so < pos.start_position) {
            printf("TUT8\n");
            printf("pmatch[0].rm_so: %ld*\n", (long int)pmatch[0].rm_so);
            change_pos(&pos, (int)pmatch[0].rm_so, (int)pmatch[0].rm_eo, 0, 0, 0);
            //if ((int)strlen(print) > 0) memset(print, 0, len_print);
        }
        pos.count2 = 0;
        for (int j = pos.start_position; j < pos.end_position; j++)
          print[pos.count2++] = ptr[j];
        printf("TUT9\n");
        printf("print: %s*\n", print);
        //проверить здесь все ли норм в строке выше
        if ((long int)strlen(search_q) > 0) memset(search_q, 0, len_search_q);
      }
    }
    printf("TUT10\n");
    if (pos.next_position == 0 && param->error == 0) {
      ptr += pos.end_position;
      printf("TUT11\n");
      if ((args[2] == 1 && args[3] == 0) || (args[3] == 1)) {
        printf("TUT12\n");
        break;
      }
      else {
        printf("TUT13\n");
        print_reg_o(args, count_files, &string_count, print, file_name);
        memset(print, 0, len_print);
      }
    } else if (args[5] == 1 && args[2] == 0 && args[3] == 0)
      *string_count += 1;
    change_pos(&pos, 37000, 0, pos.next_position, 0, 0);
    printf("TUT14\n");
    //memset(search_q, 0, len_search_q);
    //memset(print, 0, len_print);
  }
  free(search_q);
  free(print);
  return val;
}
*/

int work_with_reg_o(const short *args, const char *search_queries, char *str,
  const char *file_name, int count_files, int *string_count,
  struct param *param) {
  int val = 0;
  position pos = {37000, 0, 0, 0, 0};
  regex_t rx;
  size_t nmatch = 1;
  regmatch_t pmatch[nmatch];
  long int len_search_q = 1024, len_print = 1024;
  char *search_q = calloc(len_search_q + 1, sizeof(char));
  char *print = calloc(len_print + 1, sizeof(char));
  if (search_q == NULL || print == NULL) param->error = 2;
  //char find[10000] = {0}, print_this[10000] = {0}, 
  char *ptr = str;
  ptr[strlen(ptr) - 1] = '\0';
  while (pos.next_position == 0 && param->error == 0) {
    pos.next_position = 1;
    for (int i = 0; i < (int)strlen(search_queries); i++) {
      int ready = 0;
      if (search_queries[i] != '\n') {
        search_q[pos.count++] = search_queries[i];
      }
      else {
        ready = 1;
        search_q[pos.count] = '\0';
        pos.count = 0;
        if ((int)strlen(search_q) > 0) 
          val = (args[1] == 1) ? regcomp(&rx, search_q, REG_ICASE)
                    : regcomp(&rx, search_q, 0);
      }
      if (ready == 1 && val != 0)
        param->error = 1;
      else if (val == 0 && ready == 1 && (int)strlen(search_q) > 0) {
        val = regexec(&rx, ptr, nmatch, pmatch, 0);
        regfree(&rx);
        memset(search_q, 0, len_search_q);
        ready = 0;
        if (val == 0 && args[4] == 1)
          break;
        else if ((val == 0 && args[3] == 1) || (val != 0 && args[2] == 1)) {
          *string_count += 1;
          break;
        } else if (val == 0 && args[2] == 0 &&
        (int)pmatch[0].rm_so < pos.start_position) {
          change_pos(&pos, (int)pmatch[0].rm_so, (int)pmatch[0].rm_eo, 0, 0, 0);
        }
        pos.count2 = 0;
        memset(print, 0, len_print);
        for (int j = pos.start_position; j < pos.end_position; j++)
          print[pos.count2++] = ptr[j];
      }
    }
    if (pos.next_position == 0 && param->error == 0) {
      ptr += pos.end_position;
      if ((args[2] == 1 && args[3] == 0) || (args[3] == 1))
        break;
      else
        print_reg_o(args, count_files, &string_count, print, file_name);
    } else if (args[5] == 1 && args[2] == 0 && args[3] == 0)
        *string_count += 1;
    change_pos(&pos, 37000, 0, pos.next_position, 0, 0);
  }
  return val;
}


void change_pos(position *pos, int start, int end, int next, int count,
                int count2) {
  //printf("%d, %d *\n", start, end);
  pos->start_position = start;
  pos->end_position = end;
  pos->next_position = next;
  pos->count = count;
  pos->count2 = count2;
}
