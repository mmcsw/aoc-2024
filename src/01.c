#include "01.h"

int
solution_01_read_file(char const* const filename, vec_loc_id lists[2])
{
  if (!lists)
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

  lists[0] = vec_loc_id_init();
  lists[1] = vec_loc_id_init();
  if (!vec_loc_id_reserve(&lists[0], num_lines) || !vec_loc_id_reserve(&lists[1], num_lines))
  {
    return -1;
  }

  for (size_t i = 0; i < num_lines; i++)
  {
    size_t id_0, id_1;
    if (fscanf(file, "%zu   %zu", &id_0, &id_1) != 2)
    {
      return -1;
    }
    vec_loc_id_push(&lists[0], id_0);
    vec_loc_id_push(&lists[1], id_1);
  }
  fclose(file);

  return 0;
}

uintptr_t
solution_01_part_1(vec_loc_id const lists[2])
{
  uintptr_t distance = 0;
  for (size_t i = 0; i < vec_loc_id_size(&lists[0]); i++)
  {
    uintptr_t a = *vec_loc_id_at(&lists[0], i);
    uintptr_t b = *vec_loc_id_at(&lists[1], i);
    if (a > b)
    {
      distance += a - b;
    }
    else
    {
      distance += b - a;
    }
  }
  return distance;
}

uintptr_t
solution_01_part_2(vec_loc_id const lists[2])
{
  uintptr_t similarity = 0;
  size_t i = 0;
  size_t j = 0;
  while (i < vec_loc_id_size(&lists[0]) && j < vec_loc_id_size(&lists[1]))
  {
    if (*vec_loc_id_at(&lists[0], i) < *vec_loc_id_at(&lists[1], j))
    {
      i += 1;
    }
    else if (*vec_loc_id_at(&lists[0], i) > *vec_loc_id_at(&lists[1], j))
    {
      j += 1;
    }
    else
    {
      size_t value = *vec_loc_id_at(&lists[0], i);
      size_t r_occurrences = 0;
      size_t l_occurrences = 0;
      while (j < vec_loc_id_size(&lists[1]) && value == *vec_loc_id_at(&lists[1], j))
      {
        r_occurrences += 1;
        j += 1;
      }
      while (i < vec_loc_id_size(&lists[0]) && *vec_loc_id_at(&lists[0], i) == value)
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
solution_01(char const* filename)
{
  vec_loc_id lists[2];
  if (solution_01_read_file(filename, lists))
  {
    return -1;
  }

  vec_loc_id sorted_lists[2] = { vec_loc_id_clone(lists[0]), vec_loc_id_clone(lists[1]) };
  vec_loc_id_sort(&sorted_lists[0]);
  vec_loc_id_sort(&sorted_lists[1]);

  size_t distance = solution_01_part_1(sorted_lists);
  fprintf(stdout, "%zu\n", distance);

  size_t similarity = solution_01_part_2(sorted_lists);
  fprintf(stdout, "%zu\n", similarity);

  vec_loc_id_drop(&lists[0]);
  vec_loc_id_drop(&lists[1]);
  vec_loc_id_drop(&sorted_lists[0]);
  vec_loc_id_drop(&sorted_lists[1]);

  return 0;
}
