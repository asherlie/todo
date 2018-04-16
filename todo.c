#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* substr(const char* substr, char* str){
      if(str[0] == '\n')return NULL;
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
}

int main(int argc, char* argv[]){
      unsigned long lc = 0;
      int found = 0;
      int ln, nt;
      for(int i = 1; i < argc; ++i){
            FILE* fp = fopen(argv[i], "r");
            if(fp == NULL){
                  printf("FILE \"%s\" NOT FOUND\n", argv[i]);
                  continue;
            }
            char* line = NULL;
            char* sub = NULL;
            size_t sz;
            ssize_t read;
            nt = ln = 1;
            char pr_fn = 0;
            while((read = getline(&line, &sz, fp)) != EOF){
                  if((sub = substr("TODO", line))){
                        ++found;
                        if(line[read-1] == '\n')line[read-1] = '\0';
                        if(!pr_fn){
                              // TODO decide if there should be a newline after each file
                              /*if(i != 1)printf("\n");*/
                              pp_box(argv[i]);
                              pr_fn = 1;
                        }
                        printf("\n%i) (%i,%li): %s", nt++, ln, sub-line+1, sub);
                  }
                  ++ln;
            }
            free(line);
            if(nt != 1)printf("\n");
            fclose(fp);
            lc += ln;
      }
      printf("lines parsed: %li\nTODOs found: %i\n", lc, found);
}
