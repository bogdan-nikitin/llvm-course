#ifndef INSTR_H
#define INSTR_H
#include <cstdint>
#include <map>
#include <string>

struct Instr {
  enum {
#define _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,       \
             _IRGenExecute)                                                    \
  _Name = _Opcode,
#include "ISA.h"
#undef _ISA
  };
  uint64_t Op;
  int64_t A1;
  int64_t A2;
  int64_t A3;
  int64_t A4;
  static std::map<std::string, uint64_t> Str2Op;
  static std::map<uint64_t, std::string> Op2Str;
  static void prepareDicts();
  static uint64_t getOpcode(std::string &InstrName);
};
#endif // INSTR_H
