#include "system.h"
#include "thread.h"

__BEGIN_API

void System::init(void (*main)(void *))
{
    //db<System>(TRC) << "System::init() chamado\n";
    setvbuf(stdout, 0, _IONBF, 0);
    // Inicialização da Thread Main
    Thread::init(main);
}

__END_API