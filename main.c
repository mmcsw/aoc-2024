#include "src/solutions.h"
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Args
{
  unsigned long problem;
  char const* filename;
} Args;

Args*
args_from_input(int const argc, char const* const* argv)
{
  Args* output = malloc(sizeof(Args));
  if (!output)
  {
    fprintf(stderr, "Could not allocate arguments container\n");
    return NULL;
  }

  if (argc < 3)
  {
    fprintf(stderr, "Usage: %s [problem] [filename]\n", argv[0]);
    free(output);
    return NULL;
  }

  errno = 0;
  unsigned long problem = strtoul(argv[1], NULL, 0);
  if (problem == 0 && errno)
  {
    fprintf(stderr, "Usage: %s [problem] [filename]\n", argv[0]);
    fprintf(stderr, "Could not parse problem: %s\n%s\n", argv[1], strerror(errno));
    free(output);
    return NULL;
  }
  output->problem = problem;

  char const* filename = argv[2];
  if (!filename || filename[0] == '\0')
  {
    fprintf(stderr, "Usage: %s [problem] [filename]\n", argv[0]);
    fprintf(stderr, "Received empty filename\n");
    free(output);
    return NULL;
  }
  output->filename = filename;

  return output;
}

bool
args_is_valid(Args* args)
{
  return args->filename && 0 < args->problem && args->problem < 26;
}

int
main(int const argc, char const* const* argv)
{
  Args* args = args_from_input(argc, argv);
  if (!args)
  {
    return EXIT_FAILURE;
  }
  if (!args_is_valid(args))
  {
    fprintf(
      stderr,
      "invalid arguments\nsolution [1-25]: %lu\nfilename: %s\n",
      args->problem,
      args->filename
    );
    return EXIT_FAILURE;
  }

  // call the solution function on the file
  int status = solutions[args->problem - 1](args->filename);
  if(status) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
