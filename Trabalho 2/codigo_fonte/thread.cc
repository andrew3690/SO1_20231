#include "thread.h"
#include <iostream>

__BEGIN_API
Thread* Thread::_running = nullptr;

// Return Id
int Thread::id(){
    return(_id);
}

// Finalização da Thread
void Thread::thread_exit(int exit_code){
    delete(Thread::_context);
}

// Switch context
int Thread::switch_context(Thread *prev, Thread *next){
    CPU::switch_context(prev->_context,prev->_context);
    _running = next;
    return 0;
}


__END_API