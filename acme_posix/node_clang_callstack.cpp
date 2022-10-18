//
//  node_clang_callstack.cpp
//  acme_posix
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 30/09/22 23:56.
//
// Code originally found at https://eli.thegreenplace.net/2015/programmatic-access-to-the-call-stack-in-c/ on 30/09/22
#include "framework.h"

#if !defined(__clang__)
#error "This file should be only compiled with a CLANG compiler."
#endif

#define UNW_LOCAL_ONLY
#ifdef ANDROID
#include <unwind.h>
#else
#include <libunwind.h>
#endif
#include <stdio.h>

// Call this function to get a backtrace.
::string clang_backtrace()
{
  unw_cursor_t cursor;
  unw_context_t context;

  // Initialize cursor to current frame for local unwinding.
  unw_getcontext(&context);
  unw_init_local(&cursor, &context);
   string str;
  // Unwind frames one by one, going up the frame stack.
  while (unw_step(&cursor) > 0) {
    unw_word_t offset, pc;
    unw_get_reg(&cursor, UNW_REG_IP, &pc);
    if (pc == 0) {
      break;
    }
    str.append_format("0x%lx:", pc);

    char sym[256];
    if (unw_get_proc_name(&cursor, sym, sizeof(sym), &offset) == 0) {
      str.append_format(" (%s+0x%lx)\n", sym, offset);
    } else {
      str.append_format(" -- error: unable to obtain symbol name for this frame\n");
    }
  }
   return str;
}
//
//void foo() {
//  backtrace(); // <-------- backtrace here!
//}
//
//void bar() {
//  foo();
//}
//
//int main(int argc, char **argv) {
//  bar();
//
//  return 0;
//}
