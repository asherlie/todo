#include <string.h>
#include <stdbool.h>
#include <stdio.h>

char* substr(const char* substr, char* str){
      int len = strlen(substr);
      char buf[len+1];
      int i = 0;
      while(str[i+len-1] != '\0'){
            memset(buf, '\0', len);
            memcpy(buf, str+(i++), len);
            buf[len]='\0';
            if(strcmp(buf, substr) == 0)return str+i-1;
      }
      return NULL;
}

void pp_box(const char* str){
      int len = strlen(str);
      printf(" ");
      for(int i = 0; i < len; ++i)printf("-");
      printf("\n|%s|\n ", str);
      for(int i = 0; i < len; ++i)printf("-");
      printf("\n");
}

int main(int argc, char* argv[]){
      int ln;
      for(int i = 1; i < argc; ++i){
            pp_box(argv[i]);
            FILE* fp = fopen(argv[i], "r");
            char* line = NULL;
            char* sub = NULL;
            size_t sz;
            ssize_t read;
            ln = 0;
            while(getline(&line, &sz, fp) != EOF){
                  ++ln;
                  if((sub = substr("TODO", line)))
                  printf("(%i,%li): %s\n", ln, sub-line+1, sub);
            }
            fclose(fp);
      }
}
