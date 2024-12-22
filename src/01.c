#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 65536

int
count_lines_in_file(FILE* file, size_t* counter)
{
  if (!file || !counter)
  {
    return -1;
  }

  char buf[BUF_SIZE];

  while (true)
  {
    size_t read_bytes = fread(buf, sizeof(char), BUF_SIZE, file);
    if (ferror(file))
    {
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

  return fseek(file, 0, SEEK_SET);
}

int
size_t_cmp(const void* size_t_a, const void* size_t_b)
{
  size_t* a = (size_t*)(size_t_a);
  size_t* b = (size_t*)(size_t_b);

  if (*a < *b)
  {
    return -1;
  }
  else if (*a > *b)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int
read_location_ID_file(char const* const filename, size_t** arrays, size_t* array_len)
{
  if (!arrays || !array_len)
  {
    return -1;
  }

  FILE* file = fopen(filename, "r");
  if (!file)
  {
    return -1;
  }

  size_t num_lines = 0;
  if (count_lines_in_file(file, &num_lines))
  {
    return -1;
  }
  *array_len = num_lines;

  size_t* arr_0 = malloc(num_lines * sizeof(size_t));
  size_t* arr_1 = malloc(num_lines * sizeof(size_t));
  if (!arr_0 || !arr_1)
  {
    free(arr_0);
    free(arr_1);
    return -1;
  }
  arrays[0] = arr_0;
  arrays[1] = arr_1;

  for (size_t i = 0; i < num_lines; i++)
  {
    size_t id_0, id_1;
    if (fscanf(file, "%zu   %zu", &id_0, &id_1) != 2)
    {
      return -1;
    }
    arr_0[i] = id_0;
    arr_1[i] = id_1;
  }
  fclose(file);

  return 0;
}

size_t
array_location_id_distance(size_t* arr_0, size_t* arr_1, size_t arr_len)
{
  qsort(arr_0, arr_len, sizeof(size_t), size_t_cmp);
  qsort(arr_1, arr_len, sizeof(size_t), size_t_cmp);

  size_t distance = 0;
  for (size_t i = 0; i < arr_len; i++)
  {
    size_t* a = &arr_0[i];
    size_t* b = &arr_1[i];
    if (size_t_cmp(a, b) > 0)
    {
      distance += *a - *b;
    }
    else
    {
      distance += *b - *a;
    }
  }
  return distance;
}

size_t
array_location_id_similarity(size_t* arr_0, size_t* arr_1, size_t arr_len)
{
  size_t similarity = 0;
  size_t i = 0;
  size_t j = 0;
  while (i < arr_len && j < arr_len)
  {
    if (arr_0[i] < arr_1[j])
    {
      i += 1;
    }
    else if (arr_0[i] > arr_1[j])
    {
      j += 1;
    }
    else
    {
      size_t value = arr_0[i];
      size_t r_occurrences = 0;
      size_t l_occurrences = 0;
      while (j < arr_len && arr_0[i] == arr_1[j])
      {
        r_occurrences += 1;
        j += 1;
      }
      while (i < arr_len && arr_0[i] == value)
      {
        l_occurrences += 1;
        i += 1;
      }
      similarity += (l_occurrences * value * r_occurrences);
    }
  }
  return similarity;
}

int
main_01(const int argc, char const* const* argv)
{

  char const* filename = "1.txt";
  if (argc > 1)
  {
    filename = argv[1];
  }

  size_t* arrays[2] = { NULL, NULL };
  size_t array_len = 0;
  if (read_location_ID_file(filename, arrays, &array_len))
  {
    return EXIT_FAILURE;
  }

  size_t distance = array_location_id_distance(arrays[0], arrays[1], array_len);
  fprintf(stdout, "%zu\n", distance);

  size_t similarity = array_location_id_similarity(arrays[0], arrays[1], array_len);
  fprintf(stdout, "%zu\n", similarity);

  free(arrays[0]);
  free(arrays[1]);

  return EXIT_SUCCESS;
}
