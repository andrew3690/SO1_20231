#include "cpu.h"
#include <iostream>

__BEGIN_API

void CPU::Context::save()
{
    //adicionar implementação
    // Usar a classe getcontext() aqui, salvando ponteiros do contexto atual
    getcontext( &_context); // salvando contexto 1
}

void CPU::Context::load()
{
    // adicionar implementação
    // provavel uso de setcontext() aqui para carregar um dado contexto previamente salvo com uso de save()
    setcontext( &_context);
}

CPU::Context::~Context()
{
    //adicionar implementação
    // pilha de processo vai a zero
    _stack = 0; 
}

int CPU::switch_context(Context *from, Context *to)
{
     //implementação do método
     // troca de contexto usando swapcontext, trocando do conexto atual para o próximo
     swapcontext(&from ->_context,&to ->_context);
     return 0;
}

__END_API
