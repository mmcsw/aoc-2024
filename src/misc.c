#include "misc.h"

int
count_lines_in_file(FILE* file, uintptr_t* counter)
{
  if (!file || !counter)
  {
    return -1;
  }

  const size_t BUF_SIZE = UINT16_MAX + 1;
  char buf[BUF_SIZE];

  // read the file in chunks and count the newlines in each chunk
  while (true)
  {
    errno = 0;
    size_t read_bytes = fread(buf, sizeof(char), BUF_SIZE, file);
    if (ferror(file))
    {
      fprintf(stderr, "❌ Error reading file\n%s\n", strerror(errno));
      return -1;
    }

    for (size_t i = 0; i < read_bytes; i++)
    {
      if (buf[i] == '\n')
      {
        *counter += 1;
      }
    }

    if (feof(file))
    {
      break;
    }
  }

  errno = 0;
  if (fseek(file, 0, SEEK_SET))
  {
    fprintf(stderr, "❌ Error counting lines in file\n%s\n", strerror(errno));
    return -1;
  }

  return 0;
}
