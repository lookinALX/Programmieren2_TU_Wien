#pragma once

#include <stddef.h> // size_t
#include <stdint.h> // uint64_t, UINT64_C, uint32_t, UINT32_C,

// FNV1
// https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
static uint64_t FNV1_64(const void *data, size_t size)
{
  const static uint64_t offset = UINT64_C(14695981039346656037);
  const static uint64_t prime = UINT64_C(1099511628211);

  size_t n = 0;
  const uint8_t *iter = data;

  uint64_t res = offset;
  while (n++ != size)
  {
    res *= prime;
    res ^= iter[n];
  }

  return res;
}

// DJB2 http://www.cse.yorku.ca/~oz/hash.html
static uint64_t hash_djb2(const void *data, size_t size)
{
  const static uint64_t offset = UINT64_C(5381);

  size_t n = 0;
  const uint8_t *iter = data;
  uint64_t res = offset;
  while (n++ != size)
  {
    res = ((res << 5) + res) + iter[n];
  }

  return res;
}

// really bad hash
static uint64_t really_bad_bash(const void *data, size_t size)
{
  return 100;
}
