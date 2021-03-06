#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void pp_box(const char* str){
      int len = strlen(str);
      putchar(' ');
      for(int i = 0; i < len; ++i)putchar('-');
      printf("\n|%s|\n ", str);
      for(int i = 0; i < len; ++i)putchar('-');
}

char** get_args(int* nargs){
      // starting at index 1 to be consistent with argv
      int sp = 1, cap = 100;
      char** args = malloc(sizeof(char*)*cap);
      size_t sz;
      ssize_t read;
      char* ln;
      while(1){
            ln = NULL;
            sz = 0;
            if((read = getline(&ln, &sz, stdin)) == EOF){
                  free(ln);
                  break;
            }
            if(ln[read-1] == '\n')ln[read-1] = '\0';
            if(sp == cap){
                  cap *= 2;
                  char** tmp = malloc(sizeof(char*)*cap);
                  memcpy(tmp, args, sizeof(char*)*sp);
                  args = tmp;
            }
            args[sp++] = ln;
      }
      *nargs = sp;
      return args;
}

int main(int argc, char* argv[]){
      _Bool stdn = 0;
      if(argc == 1){
            stdn = 1;
            argv = get_args(&argc);
      }
      long lc = 0;
      int ln, nt, found = 0, gf = argc-1;
      char* line = NULL;
      char* sub = NULL;
      size_t sz;
      for(int i = 1; i < argc; ++i){
            FILE* fp = fopen(argv[i], "r");
            if(!fp){
                  printf("FILE \"%s\" NOT FOUND\n", argv[i]);
                  --gf;
                  continue;
            }
            sz = 0;
            ssize_t read;
            nt = ln = 1;
            char pr_fn = 0;
            while((read = getline(&line, &sz, fp)) != EOF){
                  if((sub = strstr(line, "TODO"))){
                        ++found;
                        if(line[read-1] == '\n')line[read-1] = '\0';
                        if(!pr_fn){
                              pp_box(argv[i]);
                              pr_fn = 1;
                        }
                        printf("\n%i) (%i,%li): %s", nt++, ln, sub-line+1, sub);
                  }
                  ++ln;
                  memset(line, '\0', read);
            }
            free(line);
            line = NULL;
            if(nt != 1)printf("\n");
            else --gf;
            fclose(fp);
            lc += ln;
      }
      printf("\nparsed %li lines from %i files\n%i TODOs found in %i files\n", lc-1, argc-1, found, gf);
      if(stdn){
            for(int i = 0; i < argc; ++i)
                  free(argv[i]);
            free(argv);
      }
}
