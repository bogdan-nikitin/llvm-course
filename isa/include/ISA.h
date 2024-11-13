// ISA format:
// Opcode
// Name
// SkipArgs: string -> 0 [ifstream InputFile]
// ReadArgs: string -> args [ifstream InputFile, Instr I, map BBName2PC]
// WriteArgs: args -> string [stringstream Stream, Instr I, map PC2BBName]
// Execute: args -> EXECUTION [uint32_t R1, uint32_t R2, uint32_t R3Imm, CPU *C]
// IRGenExecute = args -> IR [IRBuilder builder, regFileType regFile, Instr I,
//                            map BBMap, uint32_t PC, GraphicalFuncs]

// _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,
// _IRGenExecute)

// SkipArgs
#define SKIP_4ARGS                                                             \
  {                                                                            \
    InputFile >> Arg >> Arg >> Arg >> Arg;                                     \
  }
#define SKIP_3ARGS                                                             \
  {                                                                            \
    InputFile >> Arg >> Arg >> Arg;                                            \
  }
#define SKIP_2ARGS                                                             \
  {                                                                            \
    InputFile >> Arg >> Arg;                                                   \
  }
#define SKIP_1ARG                                                              \
  {                                                                            \
    InputFile >> Arg;                                                          \
  }

// ReadArgs
#define READ_REG(Reg)                                                          \
  {                                                                            \
    InputFile >> Arg;                                                          \
    I.Reg = std::stoi(Arg.substr(1));                                          \
  }
#define READ_IMM(Imm)                                                          \
  {                                                                            \
    InputFile >> Arg;                                                          \
    I.Imm = std::stoll(Arg);                                                   \
  }
#define READ_LABEL                                                             \
  {                                                                            \
    InputFile >> Arg;                                                          \
    if (BBName2PC.find(Arg) == BBName2PC.end()) {                              \
      ErrorMsg = std::string("Can't find label: " + Arg);                      \
      return true;                                                             \
    }                                                                          \
    I.A1 = BBName2PC[Arg];                                                     \
  }
#define READ_1REG {READ_REG(A1)}
#define READ_REG_IMM {READ_REG(A1) READ_IMM(A2)}
#define READ_2REGS {READ_REG(A1) READ_REG(A2)}
#define READ_3REGS {READ_REG(A1) READ_REG(A2) READ_REG(A3)}
#define READ_3REGS_IMM {READ_REG(A1) READ_REG(A2) READ_REG(A3) READ_IMM(A4)}
#define READ_4REGS {READ_REG(A1) READ_REG(A2) READ_REG(A3) READ_REG(A4)}
#define READ_LABEL_REG_IMM {READ_LABEL READ_REG(A2) READ_IMM(A3)}
#define READ_2REGS_2IMMS {READ_REG(A1) READ_REG(A2) READ_IMM(A3) READ_IMM(A4)}
#define READ_LABEL_2REGS {READ_LABEL READ_REG(A2) READ_REG(A3)}

// WriteArgs
#define WRITE_REG(Reg)                                                         \
  {                                                                            \
    Stream << " x" << I.Reg;                                                   \
  }
#define WRITE_REG(Reg)                                                         \
  {                                                                            \
    Stream << " x" << I.Reg;                                                   \
  }
#define WRITE_IMM(Imm)                                                         \
  {                                                                            \
    Stream << " " << I.Imm;                                                    \
  }
#define WRITE_LABEL                                                            \
  {                                                                            \
    Stream << " " << PC2BBName[I.A1];                                          \
  }
#define WRITE_REG_IMM {WRITE_REG(A1) WRITE_IMM(A2)}
#define WRITE_1REG {WRITE_REG(A1)}
#define WRITE_2REGS {WRITE_REG(A1) WRITE_REG(A2)}
#define WRITE_3REGS {WRITE_REG(A1) WRITE_REG(A2) WRITE_REG(A3)}
#define WRITE_3REGS_IMM                                                        \
  {WRITE_REG(A1) WRITE_REG(A2) WRITE_REG(A3) WRITE_IMM(A4)}
#define WRITE_2REGS_IMM {WRITE_REG(R1) WRITE_REG(R2) WRITE_IMM}
#define WRITE_REG_LABEL {WRITE_REG(R1) WRITE_LABEL}
#define WRITE_LABEL_REG_IMM {WRITE_LABEL WRITE_REG(A2) WRITE_IMM(A3)}
#define WRITE_LABEL_2REGS {WRITE_LABEL WRITE_REG(A2) WRITE_REG(A3)}
#define WRITE_2REGS_2IMMS                                                      \
  {WRITE_REG(A1) WRITE_REG(A2) WRITE_IMM(A3) WRITE_IMM(A4)}

// _IRGenExecute
#define GEP2_64(Arg) builder.CreateConstGEP2_64(regFileType, regFile, 0, Arg)
#define LOAD_REG(Arg) builder.CreateLoad(int64Type, GEP2_64(Arg))
#define GEN_IMM(Arg) builder.getInt64(Arg)
#define STORE_REG(Arg) builder.CreateStore(Arg, GEP2_64(I.A1))

// _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,
// _IRGenExecute)

//    EXIT (NO ARGS)
_ISA(0x1, EXIT, {}, {}, {}, { C->Run = 0; }, { builder.CreateRetVoid(); })

//    FLUSH (NO ARGS)
_ISA(
    0x2, FLUSH, {}, {}, {}, { simFlush(); },
    { builder.CreateCall(simFlushFunc); })

//    ALLOC (REG_IMM)
_ISA(
    0x3, ALLOC, SKIP_2ARGS, READ_REG_IMM, WRITE_REG_IMM,
    {
      C->RegFile[A1] = reinterpret_cast<uint64_t>(C->Stack + C->StackPointer);
      C->StackPointer += A2;
    },
    {
      STORE_REG(
          builder.CreateAlloca(ArrayType::get(builder.getInt8Ty(), I.A2)));
    })

//    MOV x1 x2 (2REGS)
_ISA(
    0x4, MOV, SKIP_2ARGS, READ_2REGS, WRITE_2REGS,
    { C->RegFile[A1] = C->RegFile[A2]; }, { STORE_REG(LOAD_REG(I.A2)); })

//    SET x1 s2 (REG_IMM)
_ISA(
    0x5, SET, SKIP_2ARGS, READ_REG_IMM, WRITE_REG_IMM, { C->RegFile[A1] = A2; },
    { STORE_REG(GEN_IMM(I.A2)); })

//    RAND x1 (1REG)
_ISA(
    0x6, RAND, SKIP_1ARG, READ_1REG, WRITE_1REG,
    { C->RegFile[A1] = simRand(); },
    { STORE_REG(builder.CreateCall(simRandFunc)); })

//    AND x1 1 (REG_IMM)
_ISA(
    0x7, AND, SKIP_2ARGS, READ_REG_IMM, WRITE_REG_IMM,
    { C->RegFile[A1] &= A2; },
    { STORE_REG(builder.CreateAnd(LOAD_REG(I.A1), GEN_IMM(I.A2))); })

//    STORE x1 x2 (2REGS)
_ISA(
    0x8, STORE, SKIP_2ARGS, READ_2REGS, WRITE_2REGS,
    { *reinterpret_cast<uint8_t *>(C->RegFile[A2]) = C->RegFile[A1]; },
    {
      builder.CreateStore(
          LOAD_REG(I.A1),
          builder.CreateIntToPtr(LOAD_REG(I.A2),
                                 builder.getInt8Ty()->getPointerTo()));
    })

//    INC x1 (1REG)
_ISA(
    0x9, INC, SKIP_1ARG, READ_1REG, WRITE_1REG, { ++C->RegFile[A1]; },
    { STORE_REG(builder.CreateAdd(LOAD_REG(I.A1), GEN_IMM(1))); })

//    LOOP x_loop_init x3 512 (LABEL_REG_IMM)
_ISA(
    0xa, LOOP, SKIP_3ARGS, READ_LABEL_REG_IMM, WRITE_LABEL_REG_IMM,
    {
      if (++C->RegFile[A2] != A3) {
        C->NextPC = A1;
      }
    },
    {
      PC++;
      builder.CreateStore(builder.CreateAdd(LOAD_REG(I.A2), GEN_IMM(1)),
                          GEP2_64(I.A2));
      builder.CreateCondBr(builder.CreateICmpEQ(LOAD_REG(I.A2), GEN_IMM(I.A3)),
                           BBMap[PC], BBMap[I.A1]);
      builder.SetInsertPoint(BBMap[PC]);
      continue;
    })

//    ADD x1 x2 (2REGS)
_ISA(
    0xb, ADD, SKIP_2ARGS, READ_2REGS, WRITE_2REGS,
    { C->RegFile[A1] += C->RegFile[A2]; },
    { STORE_REG(builder.CreateAdd(LOAD_REG(I.A1), LOAD_REG(I.A2))); })

//    SHL x1 1 (REG_IMM)
_ISA(
    0xc, SHL, SKIP_2ARGS, READ_REG_IMM, WRITE_REG_IMM,
    { C->RegFile[A1] <<= A2; },
    { STORE_REG(builder.CreateShl(LOAD_REG(I.A1), GEN_IMM(I.A2))); })

//    LOAD x1 x2 (2REGS)
_ISA(
    0xd, LOAD, SKIP_2ARGS, READ_2REGS, WRITE_2REGS,
    { C->RegFile[A1] = *reinterpret_cast<uint8_t *>(C->RegFile[A2]); },
    {
      STORE_REG(builder.CreateLoad(
          builder.getInt8Ty(),
          builder.CreateIntToPtr(LOAD_REG(I.A2),
                                 builder.getInt8Ty()->getPointerTo())));
    })

//    MOVIFZ x1 x2 1 2 (2REGS_2IMMS)
_ISA(
    0xe, MOVIFZ, SKIP_4ARGS, READ_2REGS_2IMMS, WRITE_2REGS_2IMMS,
    { C->RegFile[A1] = C->RegFile[A2] == 0 ? A3 : A4; },
    {
      STORE_REG(
          builder.CreateSelect(builder.CreateICmpEQ(LOAD_REG(I.A2), GEN_IMM(0)),
                               GEN_IMM(I.A3), GEN_IMM(I.A4)));
    })

//    PUT_PIXEL x5 x2 x6 (3REGS)
_ISA(
    0xf, PUTPIXEL, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { simPutPixel(C->RegFile[A1], C->RegFile[A2], C->RegFile[A3]); },
    {
      builder.CreateCall(simPutPixelFunc,
                         {LOAD_REG(I.A1), LOAD_REG(I.A2), LOAD_REG(I.A3)});
    })

//    BRZ loop_end x13 x10 (LABEL_2REGS)
_ISA(
    0x10, BRZ, SKIP_3ARGS, READ_LABEL_2REGS, WRITE_LABEL_2REGS,
    {
      if (C->RegFile[A2] == 0 && C->RegFile[A3] == 0) {
        C->NextPC = A1;
      }
    },
    {
      PC++;
      builder.CreateCondBr(
          builder.CreateICmpEQ(builder.CreateOr(LOAD_REG(I.A2), LOAD_REG(I.A3)),
                               GEN_IMM(0)),
          BBMap[I.A1], BBMap[PC]);
      builder.SetInsertPoint(BBMap[PC]);
      continue;
    })

//    ANDD x14 x13 x5 511 (3REGS_IMM)
_ISA(
    0x11, ANDD, SKIP_4ARGS, READ_3REGS_IMM, WRITE_3REGS_IMM,
    { C->RegFile[A1] = (C->RegFile[A2] + C->RegFile[A3]) & A4; },
    {
      STORE_REG(builder.CreateAnd(
          builder.CreateAdd(LOAD_REG(I.A2), LOAD_REG(I.A3)), GEN_IMM(I.A4)));
    })

//       THOR x14 x12 x3 (3REGS)
_ISA(
    0x12, THOR, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { C->RegFile[A1] |= C->RegFile[A2] | C->RegFile[A3]; },
    {
      STORE_REG(builder.CreateOr(
          LOAD_REG(I.A1), builder.CreateOr(LOAD_REG(I.A2), LOAD_REG(I.A3))));
    })

//    BREQ live x11 3 (LABEL_REG_IMM)
_ISA(
    0x13, BREQ, SKIP_3ARGS, READ_LABEL_REG_IMM, WRITE_LABEL_REG_IMM,
    {
      if (C->RegFile[A2] == A3) {
        C->NextPC = A1;
      }
    },
    {
      PC++;
      builder.CreateCondBr(builder.CreateICmpEQ(LOAD_REG(I.A2), GEN_IMM(I.A3)),
                           BBMap[I.A1], BBMap[PC]);
      builder.SetInsertPoint(BBMap[PC]);
      continue;
    })

//    BR update (1LABEL)
_ISA(
    0x14, BR, SKIP_1ARG, READ_LABEL, WRITE_LABEL, { C->NextPC = A1; },
    {
      PC++;
      builder.CreateBr(BBMap[I.A1]);
      builder.SetInsertPoint(BBMap[PC]);
      continue;
    })

//    XOR x1 1 (REG_IMM)
_ISA(
    0x15, XOR, SKIP_2ARGS, READ_REG_IMM, WRITE_REG_IMM,
    { C->RegFile[A1] ^= A2; },
    { STORE_REG(builder.CreateXor(LOAD_REG(I.A1), GEN_IMM(I.A2))); })
