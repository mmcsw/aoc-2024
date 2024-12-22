#pragma once
#include "misc.h"

#define i_key uintptr_t
#define i_use_cmp
#define i_tag loc_id
#include "../lib/stc/vec.h"

static int
solution_01_read_file(char const* const filename, vec_loc_id lists[2]);

static uintptr_t
solution_01_part_1(vec_loc_id const lists[2]);

static uintptr_t
solution_01_part_2(vec_loc_id const lists[2]);

int
solution_01(char const* filename);
