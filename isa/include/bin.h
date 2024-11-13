#ifndef BIN_H
#define BIN_H
#include "instr.h"
#include <cstdint>
#include <map>
#include <string>
#include <vector>

struct Binary {
  std::vector<Instr> Instrs;
  std::map<std::string, uint64_t> BBName2PC;
  std::map<uint64_t, std::string> PC2BBName;

  bool searchBBs(std::ifstream &InputFile, std::string &ErrorMsg);

  std::string writeBBs();

  bool readInstrs(std::ifstream &InputFile, std::string &ErrorMsg);

  std::string writeInstrs();

  bool readFile(std::string FileName, std::string &ErrorMsg);
};
#endif // BIN_H
