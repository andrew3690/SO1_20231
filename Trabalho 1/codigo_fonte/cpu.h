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

// Instanciação de classe Context
template<typename ... Tn>
CPU::Context::Context(void (* func)(Tn ...), Tn ... an)
{
    // obtenção do contexto atual
    getcontext(&_context);
    // criação da pilha do contexto, alocando de acordo com o tamanho alocado para a pilha fo contexto em Traits.h 
    _stack = new char[STACK_SIZE];
    // ponteiro _context aponta para o topo da pilha, tipo um stack pointer de SO
    _context.uc_stack.ss_sp = _stack;
    // ponteiro _context obtém o tamanho da pilha utilizando stack
    _context.uc_stack.ss_size = STACK_SIZE;
    
    // Cria contexto com o ponteiro _context
    makecontext(&_context, (void (*) ()) func, 1,an ...);
}

__END_API

#endif

