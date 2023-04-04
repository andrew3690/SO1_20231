#ifndef cpu_h
#define cpu_h

#include <ucontext.h>
#include <iostream>
#include "traits.h"

__BEGIN_API

class CPU
{
    public:

        class Context
        {
        private:
            static const unsigned int STACK_SIZE = Traits<CPU>::STACK_SIZE;
        public:
            Context() { _stack = 0; }

            template<typename ... Tn>
            Context(void (* func)(Tn ...), Tn ... an);

            ~Context();

            void save();
            void load();

        private:            
            char *_stack;
        public:
            ucontext_t _context;
        };

    public:

        static int switch_context(Context *from, Context *to);

};

template<typename ... Tn>
CPU::Context::Context(void (* func)(Tn ...),Tn ... an) {
    // Initializes the context with getcontext()
    save();
    // Allocates the Context's stack
    _stack = new char[STACK_SIZE];
    // Sets the stack's stack pointer
    _context.uc_stack.ss_sp = (void *) _stack;
    // Sets the Context's stack size
    _context.uc_stack.ss_size = STACK_SIZE;
    // Provides a function for the Context to run
    makecontext(&_context, (void (*) ()) func, sizeof...(Tn), an...);
}

__END_API

#endif