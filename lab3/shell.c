#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PROMPT "myshell>"
#define BUFFERSIZE 150

char** split_by_space(char* string) {
  char** tokens = (char**)malloc(sizeof(char*) * 40);
  int i = 0;
  char *token = strtok(string, " ");
  while (token != NULL) {
    tokens[i++] = token;
    token = strtok(NULL, " ");
  }
  tokens[i] = NULL;
  return tokens;
}

int main() {
  char command[BUFFERSIZE];
  int status;
  pid_t pid;

  while (1) {

    printf("%s ", PROMPT);
    fgets(command, BUFFERSIZE, stdin);
    command[strlen(command) - 1] = '\0';

    if (strcmp(command, "exit") == 0)
      break;

    else if (strstr(command, "cd") != NULL) {
      char dirname[BUFFERSIZE/3];
      strcpy(dirname, command + 3);
      int ret = chdir(dirname);
      if (ret)
        printf("%s: No such directory\n", dirname);
    }

    else if (strcmp(command, "pwd") == 0) {
      char cwd[BUFFERSIZE];
      getcwd(cwd, BUFFERSIZE);
      printf("%s\n", cwd);
    }

    else if (strstr(command, "mkdir") != NULL) {
      char dirname[BUFFERSIZE/3];
      strcpy(dirname, command + 6);
      int status = mkdir(dirname, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
      if (status)
        printf("%s: Directory could not be created due to some error!\n", dirname);
    }
    
    else if (strstr(command, "rmdir") != NULL) {
      char dirname[BUFFERSIZE/3];
      strcpy(dirname, command + 6);
      int status = rmdir(dirname);
      if (status)
        printf("%s: Directory could not be removed due to some error!\n", dirname);
    }

    else if (strcmp(command, "ls") == 0) {
      struct dirent *dp;
      DIR *dirp = opendir(".");
      int count = 0;
      if (dirp != NULL) {
        while ((dp = readdir(dirp)) != NULL) {
          if (dp->d_name[0] != '.') {
            if (++count % 4)
              printf("%-16s", dp->d_name);
            else
              printf("%-16s\n", dp->d_name);
          }
        }
        closedir(dirp);
        if (count % 4 != 0)
          printf("\n");
      } else {
        printf("Could not get the files of the current directory\n");
      }
    }

    else {
      if ((pid = fork()) == 0) {
        char **tokens = split_by_space(command);
        int file_in_cur_dir = 0;

        struct dirent *dp;
        DIR *dirp = opendir(".");
        if (dirp != NULL) {
          while ((dp = readdir(dirp)) != NULL) {
            if (strcmp(tokens[0], dp->d_name) == 0) {
              file_in_cur_dir = 1;
              break;
            }
          }
          closedir(dirp);
        }

        if (file_in_cur_dir) {
          const char* PATH = "PATH";
          char* path = getenv(PATH);

          char newpath[BUFFERSIZE*10];
          getcwd(newpath, BUFFERSIZE); 
          strcat(newpath, ":");
          strcat(newpath, path);        

          setenv(PATH, newpath, 1);     
        }
        execvp(tokens[0], tokens);
      }
      else {
        waitpid(pid, &status, 0);
      }
    }
  }
}
