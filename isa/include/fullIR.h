#ifndef FULLIR_H
#define FULLIR_H
#include "bin.h"
#include "cpu.h"
#include "extIR.h"

struct FullIR : ExtIR {
  void buildIR(Binary &Bin);
  void executeIR(CPU &Cpu);
};

#endif // FULLIR_H
