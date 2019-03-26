#include "jit/inc/jit_thread.hpp"
#include "jit/inc/jit_support.hpp"
#include "core/inc/core.hpp"

using namespace c6x;

#ifdef _WIN32
HANDLE jit_compile_req_event;
HANDLE jit_mutext;
#else
pthread_cond_t jit_compile_req_event;
pthread_mutex_t jit_mutext;
#endif

bool inited = false;

void *jit_compile_thread(void* param)
{
  for(;;)
  {
    c6x::BasicBlock *bb;
    {
      //WaitForSingleObject(jit_mutext,INFINITE);
      pthread_mutex_lock(&jit_mutext);
      if(JITThread::compile_req_list.empty())
      {
        while(JITThread::compile_req_list.empty())
        {//wait for compile request
	  pthread_cond_wait(&jit_compile_req_event, &jit_mutext);
          //SignalObjectAndWait(jit_mutext,jit_compile_req_event,INFINITE,false);
        }
        //WaitForSingleObject(jit_mutext,INFINITE);// re-acquire mutex
      }
      bb = JITThread::compile_req_list.back();
      JITThread::compile_req_list.pop_back();
      pthread_mutex_unlock(&jit_mutext);
      //ReleaseMutex(jit_mutext);
    }
#ifdef CORE_USE_LLVM
    JIT::compile_basic_block(Core::get(),bb);
#endif
  }
}

std::vector<c6x::BasicBlock*> JITThread::compile_req_list;

void JITThread::init()
{
  if(!inited)
  {
    pthread_t mythread;

    pthread_cond_init(&jit_compile_req_event, NULL);
    //jit_compile_req_event = CreateEvent(NULL,true,false,NULL);
    pthread_mutex_init(&jit_mutext, NULL);
    //jit_mutext = CreateMutex(NULL,false,NULL);
    pthread_create(&mythread, NULL, jit_compile_thread, NULL);
    //CreateThread( 
    //              NULL,       // default security attributes
    //              0,          // default stack size
    //              (LPTHREAD_START_ROUTINE) jit_compile_thread, 
    //              NULL,       // no thread function arguments
    //              0,          // default creation flags
    //              NULL); // receive thread identifier
    inited = true;
  }
}

void JITThread::push_compile_req(c6x::BasicBlock *bb)
{
  compile_req_list.push_back(bb);
}
