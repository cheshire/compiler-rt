/*===- InstrProfilingPlatformLinux.c - Profile data Linux platform ------===*\
|*
|*                     The LLVM Compiler Infrastructure
|*
|* This file is distributed under the University of Illinois Open Source
|* License. See LICENSE.TXT for details.
|*
\*===----------------------------------------------------------------------===*/

#include "InstrProfiling.h"

#if defined(__linux__) || defined(__FreeBSD__)
#include <stdlib.h>

#define PROF_DATA_START INSTR_PROF_SECT_START(INSTR_PROF_DATA_SECT_NAME)
#define PROF_DATA_STOP INSTR_PROF_SECT_STOP(INSTR_PROF_DATA_SECT_NAME)
#define PROF_NAME_START INSTR_PROF_SECT_START(INSTR_PROF_NAME_SECT_NAME)
#define PROF_NAME_STOP INSTR_PROF_SECT_STOP(INSTR_PROF_NAME_SECT_NAME)
#define PROF_CNTS_START INSTR_PROF_SECT_START(INSTR_PROF_CNTS_SECT_NAME)
#define PROF_CNTS_STOP INSTR_PROF_SECT_STOP(INSTR_PROF_CNTS_SECT_NAME)

/* Declare section start and stop symbols for various sections
 * generated by compiler instrumentation.
 */
extern __llvm_profile_data PROF_DATA_START LLVM_LIBRARY_VISIBILITY;
extern __llvm_profile_data PROF_DATA_STOP LLVM_LIBRARY_VISIBILITY;
extern uint64_t PROF_CNTS_START LLVM_LIBRARY_VISIBILITY;
extern uint64_t PROF_CNTS_STOP LLVM_LIBRARY_VISIBILITY;
extern char PROF_NAME_START LLVM_LIBRARY_VISIBILITY;
extern char PROF_NAME_STOP LLVM_LIBRARY_VISIBILITY;

/* Add dummy data to ensure the section is always created. */
__llvm_profile_data
    __prof_data_sect_data[0] LLVM_SECTION(INSTR_PROF_DATA_SECT_NAME_STR);
uint64_t __prof_cnts_sect_data[0] LLVM_SECTION(INSTR_PROF_CNTS_SECT_NAME_STR);
char __prof_nms_sect_data[0] LLVM_SECTION(INSTR_PROF_NAME_SECT_NAME_STR);

LLVM_LIBRARY_VISIBILITY const __llvm_profile_data *
__llvm_profile_begin_data(void) {
  return &PROF_DATA_START;
}
LLVM_LIBRARY_VISIBILITY const __llvm_profile_data *
__llvm_profile_end_data(void) {
  return &PROF_DATA_STOP;
}
LLVM_LIBRARY_VISIBILITY const char *__llvm_profile_begin_names(void) {
  return &PROF_NAME_START;
}
LLVM_LIBRARY_VISIBILITY const char *__llvm_profile_end_names(void) {
  return &PROF_NAME_STOP;
}
LLVM_LIBRARY_VISIBILITY uint64_t *__llvm_profile_begin_counters(void) {
  return &PROF_CNTS_START;
}
LLVM_LIBRARY_VISIBILITY uint64_t *__llvm_profile_end_counters(void) {
  return &PROF_CNTS_STOP;
}
#endif
