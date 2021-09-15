#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "server.h"


static char* page_start =
  "<html>\n"
  " <body>\n"
  "  <pre>\n";

static char* page_end =
  "  </pre>\n"
  " </body>\n"
  "</html>\n";


void module_generate(int fd, struct query_options* query_params)
{
  pid_t child_pid;
  int rval;

  write(fd, page_start, strlen(page_start));
  
  child_pid = fork();
  if (child_pid == 0) {
    
    size_t argv_length = 2;
    char** argv = (char**) xmalloc(argv_length* sizeof(char*));
    argv[0] = "/bin/ncal";
    argv[1] = "-h";
    
    if (query_params != NULL) {
      char* aux = NULL;

      for (int i=0 ; i<query_params->qnt ; i++) {
        aux = strtok(query_params->map[i], "=");

        if (strcasecmp(aux, "mes") == 0) {
          argv = (char**) xrealloc(argv, (argv_length+=2) * sizeof(char*));
          argv[argv_length-2] = "-m";
          aux = strtok(NULL, "=");
          argv[argv_length-1] = aux;
        }

        if (strcasecmp(aux, "ano") == 0) {
          argv = (char**) xrealloc(argv, (argv_length++) * sizeof(char*));
          aux = strtok(NULL, "=");
          argv[argv_length-1] = aux;
        }
      }
    }

    argv = (char**) xrealloc(argv, argv_length* sizeof(char*));
    argv[argv_length++] = NULL;

    rval = dup2(fd, STDOUT_FILENO);
    if (rval == -1) system_error("dup2");

    rval = dup2(fd, STDERR_FILENO);
    if (rval == -1) system_error("dup2");

    execv(argv[0], argv);
    system_error("execv");
  } else if (child_pid > 0) {
    rval = waitpid(child_pid, NULL, 0);
    if (rval == -1) system_error("waitpid");
  } else system_error ("fork");

  write (fd, page_end, strlen (page_end));
}