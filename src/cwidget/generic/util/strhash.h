// strhash.h, -*-c++-*-
//
//  Copyright 199 Daniel Burrows
//
//  Make hash_map<string, footype> do the Right Thing.

#ifndef STRHASH_H
#define STRHASH_H

#include <cwidget-config.h>

#ifdef CWIDGET_HAVE_HASH_MAP
#include <hash_map>
#else
#ifdef CWIDGET_HAVE_EXT_HASH_MAP
#include <ext/hash_map>
#else
// Fallback to the non-hashing map class
#include <map>
#define hash_map map
#endif
#endif

#include <string>

#if defined(CWIDGET_HAVE_HASH_MAP) || defined(CWIDGET_HAVE_EXT_HASH_MAP)
namespace CWIDGET_HASH_NAMESPACE
{
  template <>
  struct hash<std::string>
  {
    inline size_t operator()(const std::string &s) const
    {
      return hash<char *>()(s.c_str());
    }
  };
}
#endif

#endif
