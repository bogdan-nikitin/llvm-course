#ifndef CPU_H
#define CPU_H
#include "../../sim.h"
#include "bin.h"
#include "llvm/Support/raw_ostream.h"
#include <cstdint>
#include <string>

struct CPU {
  static constexpr uint64_t RegSize = 16;
  static constexpr uint64_t StackSize = 512 * 512;
  uint64_t RegFile[RegSize] = {};
  uint64_t PC;
  uint64_t NextPC;
  uint64_t Run;
  uint8_t  Stack[StackSize] = {};
  uint64_t StackPointer = 0;
  bool DumpInstrs = false;

  bool Execute(Binary &Bin, std::string &ErrorMsg);
  std::string dumpStatus();

  static CPU *C;
  static void setCPU(CPU *Cpu) { C = Cpu; }
#define _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,       \
             _IRGenExecute)                                                    \
  static void do_##_Name(uint32_t A1, uint32_t A2, uint32_t A3, uint32_t A4) { \
    if (C->DumpInstrs)                                                         \
      llvm::outs() << #_Name "\n";                                             \
    _Execute;                                                                  \
  }
#include "ISA.h"
#undef _ISA
};
#endif // CPU_H
