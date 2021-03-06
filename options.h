#ifndef _OPTIONS_H
#define _OPTIONS_H

#include "view.h"
#include "util.h"

enum class OptionId {
  HINTS,
  ASCII,

  EASY_KEEPER,
  AGGRESSIVE_HEROES,

  EASY_ADVENTURER,
};

enum class OptionSet {
  GENERAL,
  KEEPER,
  ADVENTURER,
};

ENUM_HASH(OptionId);

class Options {
  public:
  static void init(const string& path);
  static int getValue(OptionId);
  static void handle(View*, OptionSet, int lastIndex = 0);
  static bool handleOrExit(View*, OptionSet, int lastIndex = -1);

  private:
  static void setValue(OptionId, int);
  static unordered_map<OptionId, int> readValues(const string& path);
  static void writeValues(const string& path, const unordered_map<OptionId, int>&);
  static string filename;
};


#endif
