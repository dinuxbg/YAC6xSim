#ifndef JIT_JIT_THREAD_HPP
#define JIT_JIT_THREAD_HPP

#include "jit/inc/jit_support.hpp"
#include "decode/inc/inst.hpp"

#include <list>
#include <vector>
#include <pthread.h>

#ifdef _WIN32
extern HANDLE jit_compile_req_event;
extern HANDLE jit_mutext;
#else
extern pthread_cond_t jit_compile_req_event;
extern pthread_mutex_t jit_mutext;
#endif

class JITThread
{
public:
  static void init();
  static void push_compile_req(c6x::BasicBlock *bb);

public:
  static std::vector<c6x::BasicBlock*> compile_req_list;
};

#endif
