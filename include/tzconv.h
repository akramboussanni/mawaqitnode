#ifndef TZCONV_H
#define TZCONV_H

#include <cstring>

typedef struct {
  const char *name;
  const char *posixStr;
} tzPair;

extern const tzPair tzTranslations[425];

const char* translate(const char* name);

#endif
