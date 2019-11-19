#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <strings.h>
#include <errno.h>
#include <sys/stat.h>

void specify_files (char path[100]){
  DIR * d;
  struct dirent * f;
  if ((d = opendir(path)) != NULL){
    printf("Directories:\n");
    while ((f = readdir(d)) != NULL){
      if (f->d_type == 4){
        printf("\t%s\n", f->d_name);
      }
    }
    printf("Regular files:\n");
    closedir(d);
    d = opendir(path);
    while ((f = readdir(d)) != NULL){
      if (f->d_type == 8){
        printf("\t%s\n", f->d_name);
      }
    }
    closedir(d);
  }
  else{
    printf("Error %d: %s\n", errno, strerror(errno));
  }
}

int dir_size(char path[100]){
  int ans = 0;
  DIR * d;
  struct dirent * f;
  char p[100];
  struct stat b;
  if ((d = opendir(path)) != NULL){
    while ((f = readdir(d)) != NULL){
      if (f->d_type == 8){
        // Finds path of regular files
        strcpy(p, path);
        strcat(p, "/");
        strcat(p, f->d_name);
        stat(p, &b);
        ans += b.st_size;
      }
    }
    return ans;
  }
  else{
    printf("Error %d: %s\n", errno, strerror(errno));
    return -1;
  }
}

int main(int argc, char *argv[]){
  char * d = malloc(100);

  if (argc <= 1){
    printf("Enter directory to scan: ");
    fgets(d, 100, stdin);
    d[strlen(d)-1] = 0; // ending
  }
  else{
    d = argv[1];
  }
  printf("Statistics for directory: %s\n", d);
  printf("Total Directory Size: %d\n", dir_size(d));
  specify_files(".");
  return 0;
}
