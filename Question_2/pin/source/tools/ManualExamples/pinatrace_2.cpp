/*
 * Copyright (C) 2004-2021 Intel Corporation.
 * SPDX-License-Identifier: MIT
 */

/*! @file
 *  This file contains an ISA-portable PIN tool for functional simulation of
 *  instruction+data TLB+cache hierarchies
 */

#include <iostream>

#include "pin.H"

typedef UINT32 CACHE_STATS; // type of cache hit/miss counters

#include "pin_cache.H"

 __inline__ uint64_t rdtsc(void)
   {
uint32_t lo, hi;
__asm__ __volatile__ (
        "xorl %%eax,%%eax \n        cpuid"
        ::: "%rax", "%rbx", "%rcx", "%rdx");
__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
return (uint64_t)hi << 32 | lo;
 }

namespace ITLB
{
// instruction TLB: 4 kB pages, 32 entries, fully associative
const UINT32 lineSize                          = 4 * KILO;
const UINT32 cacheSize                         = 32 * lineSize;
const UINT32 associativity                     = 32;
const CACHE_ALLOC::STORE_ALLOCATION allocation = CACHE_ALLOC::STORE_ALLOCATE;

const UINT32 max_sets          = cacheSize / (lineSize * associativity);
const UINT32 max_associativity = associativity;

typedef CACHE_ROUND_ROBIN(max_sets, max_associativity, allocation) CACHE;
} // namespace ITLB
static ITLB::CACHE itlb("ITLB", ITLB::cacheSize, ITLB::lineSize, ITLB::associativity);

namespace DTLB
{
// data TLB: 4 kB pages, 32 entries, fully associative
const UINT32 lineSize                          = 4 * KILO;
const UINT32 cacheSize                         = 32 * lineSize;
const UINT32 associativity                     = 32;
const CACHE_ALLOC::STORE_ALLOCATION allocation = CACHE_ALLOC::STORE_ALLOCATE;

const UINT32 max_sets          = cacheSize / (lineSize * associativity);
const UINT32 max_associativity = associativity;

typedef CACHE_ROUND_ROBIN(max_sets, max_associativity, allocation) CACHE;
} // namespace DTLB
static DTLB::CACHE dtlb("DTLB", DTLB::cacheSize, DTLB::lineSize, DTLB::associativity);

namespace IL1
{
// 1st level instruction cache: 32 kB, 32 B lines, 32-way associative
const UINT32 cacheSize                         = 32 * KILO;
const UINT32 lineSize                          = 32;
const UINT32 associativity                     = 32;
const CACHE_ALLOC::STORE_ALLOCATION allocation = CACHE_ALLOC::STORE_NO_ALLOCATE;

const UINT32 max_sets          = cacheSize / (lineSize * associativity);
const UINT32 max_associativity = associativity;

typedef CACHE_ROUND_ROBIN(max_sets, max_associativity, allocation) CACHE;
} // namespace IL1
static IL1::CACHE il1("L1 Instruction Cache", IL1::cacheSize, IL1::lineSize, IL1::associativity);

namespace DL1
{
// 1st level data cache: 32 kB, 32 B lines, 32-way associative
const UINT32 cacheSize                         = 32 * KILO;
const UINT32 lineSize                          = 32;
const UINT32 associativity                     = 32;
const CACHE_ALLOC::STORE_ALLOCATION allocation = CACHE_ALLOC::STORE_NO_ALLOCATE;

const UINT32 max_sets          = cacheSize / (lineSize * associativity);
const UINT32 max_associativity = associativity;

typedef CACHE_ROUND_ROBIN(max_sets, max_associativity, allocation) CACHE;
} // namespace DL1
static DL1::CACHE dl1("L1 Data Cache", DL1::cacheSize, DL1::lineSize, DL1::associativity);

namespace UL2
{
// 2nd level unified cache: 2 MB, 64 B lines, direct mapped
const UINT32 cacheSize                         = 2 * MEGA;
const UINT32 lineSize                          = 64;
const UINT32 associativity                     = 1;
const CACHE_ALLOC::STORE_ALLOCATION allocation = CACHE_ALLOC::STORE_ALLOCATE;

const UINT32 max_sets = cacheSize / (lineSize * associativity);

typedef CACHE_DIRECT_MAPPED(max_sets, allocation) CACHE;
} // namespace UL2
static UL2::CACHE ul2("L2 Unified Cache", UL2::cacheSize, UL2::lineSize, UL2::associativity);

namespace UL3
{
// 3rd level unified cache: 16 MB, 64 B lines, direct mapped
const UINT32 cacheSize                         = 16 * MEGA;
const UINT32 lineSize                          = 64;
const UINT32 associativity                     = 1;
const CACHE_ALLOC::STORE_ALLOCATION allocation = CACHE_ALLOC::STORE_ALLOCATE;

const UINT32 max_sets = cacheSize / (lineSize * associativity);

typedef CACHE_DIRECT_MAPPED(max_sets, allocation) CACHE;
} // namespace UL3
static UL3::CACHE ul3("L3 Unified Cache", UL3::cacheSize, UL3::lineSize, UL3::associativity);

FILE* trace;

// Print a memory read record
VOID RecordMemRead(ADDRINT addr, UINT64 timestamp) 
{ 
    const UINT32 size                        = 1; // assuming access does not cross cache lines
    const CACHE_BASE::ACCESS_TYPE accessType = CACHE_BASE::ACCESS_TYPE_LOAD;

    if (/*!dtlb.AccessSingleLine(addr, accessType) &&*/ !dl1.AccessSingleLine(addr, accessType) &&  !ul2.Access(addr, size, accessType) && !ul3.Access(addr, size, accessType))
        fprintf(trace, "R %p %lu\n", (void*)addr, timestamp); 
}

// Print a memory write record
VOID RecordMemWrite(ADDRINT addr, UINT64 timestamp) 
{ 
    const UINT32 size                        = 1; // assuming access does not cross cache lines
    const CACHE_BASE::ACCESS_TYPE accessType = CACHE_BASE::ACCESS_TYPE_STORE;

    if (/*!dtlb.AccessSingleLine(addr, accessType) && */!dl1.AccessSingleLine(addr, accessType) &&  !ul2.Access(addr, size, accessType) && !ul3.Access(addr, size, accessType))
        fprintf(trace, "W %p %lu\n", (void*)addr, timestamp);
}

VOID RecordInstruction(ADDRINT addr, UINT64 timestamp)
{
    const UINT32 size                        = 1; // assuming access does not cross cache lines
    const CACHE_BASE::ACCESS_TYPE accessType = CACHE_BASE::ACCESS_TYPE_LOAD;

    if (!itlb.AccessSingleLine(addr, accessType) && !il1.AccessSingleLine(addr, accessType) &&  !ul2.Access(addr, size, accessType) && !ul3.Access(addr, size, accessType))
        fprintf(trace, "I %p %lu\n", (void*)addr, timestamp);
}

// Is called for every instruction and instruments reads and writes
VOID Instruction(INS ins, VOID* v)
{
    // Instruments memory accesses using a predicated call, i.e.
    // the instrumentation is called iff the instruction will actually be executed.
    //
    // On the IA-32 and Intel(R) 64 architectures conditional moves and REP
    // prefixed instructions appear as predicated instructions in Pin.
    INS_InsertPredicatedCall(ins, IPOINT_BEFORE, (AFUNPTR)RecordInstruction, IARG_INST_PTR, IARG_UINT64, rdtsc(), IARG_END);
    UINT32 memOperands = INS_MemoryOperandCount(ins);

    // Iterate over each memory operand of the instruction.
    for (UINT32 memOp = 0; memOp < memOperands; memOp++)
    {
        if (INS_MemoryOperandIsRead(ins, memOp))
        {
            INS_InsertPredicatedCall(ins, IPOINT_BEFORE, (AFUNPTR)RecordMemRead, IARG_INST_PTR, IARG_MEMORYOP_EA, memOp,
                                     IARG_END);
        }
        // Note that in some architectures a single memory operand can be
        // both read and written (for instance incl (%eax) on IA-32)
        // In that case we instrument it once for read and once for write.
        if (INS_MemoryOperandIsWritten(ins, memOp))
        {
            INS_InsertPredicatedCall(ins, IPOINT_BEFORE, (AFUNPTR)RecordMemWrite, IARG_INST_PTR, IARG_MEMORYOP_EA, memOp,
                                     IARG_END);
        }
    }
}

VOID Fini(INT32 code, VOID* v)
{
    fprintf(trace, "#eof\n");
    fclose(trace);
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
    PIN_ERROR("This Pintool prints a trace of memory addresses\n" + KNOB_BASE::StringKnobSummary() + "\n");
    return -1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char* argv[])
{
    if (PIN_Init(argc, argv)) return Usage();

    trace = fopen("myinstr.out", "w");

    INS_AddInstrumentFunction(Instruction, 0);
    PIN_AddFiniFunction(Fini, 0);

    // Never returns
    PIN_StartProgram();

    return 0;
}




