#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <strings.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
  char name[100];

  if (argc <= 1){
    printf("Enter directory to scan: ");
    fgets(name, 100, stdin);
    name[strlen(name)-1] = '\0';
  }
  else{
    strcpy(name, argv[1]);
  }

  printf("Statistics for directory: %s\n", name);
  DIR * d;
  struct dirent * f;
  int size = 0;
  char p[100];
  struct stat b;
  if ((d = opendir(name)) != NULL){
    printf("Directories:\n");
    while ((f = readdir(d)) != NULL){
      if (f->d_type == 4){
        printf("\t%s\n", f->d_name);
      }
    }
    printf("Regular files:\n");
    closedir(d);
    d = opendir(name);
    while ((f = readdir(d)) != NULL){
      if (f->d_type == 8){
        printf("\t%s\n", f->d_name);
        strcpy(p, name);
        strcat(p, "/");
        strcat(p, f->d_name);
        stat(p, &b);
        size += b.st_size;
      }
    }
    closedir(d);
  }
  else{
    printf("Error %d: %s\n", errno, strerror(errno));
  }

  printf("Total Directory Size: %d\n", size);
  return 0;
}
