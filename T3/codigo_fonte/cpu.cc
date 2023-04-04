#include "cpu.h"
#include <iostream>

__BEGIN_API

void CPU::Context::save()
{
    // Saves the current context
    getcontext(&_context);
}

void CPU::Context::load()
{
    // Loads the context for the caller (that will take on the execution)
    setcontext(&_context);
}

CPU::Context::~Context()
{
    // Deletes stack to liberate the memory
    if (_stack) delete _stack;
}

int CPU::switch_context(Context *from, Context *to)
{
    // Switches context
    return swapcontext(&from->_context, &to->_context);
}

__END_API
