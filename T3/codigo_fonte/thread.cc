#include "thread.h"

__BEGIN_API

// Inicializando os atributos estáticos da classe Thread
int Thread::_threads_identifier = 0;
Thread* Thread::_running = nullptr;

int Thread::id(){
	return _id;
}

int Thread::switch_context(Thread * prev, Thread * next) {
    // Thread que está executando será a próxima
    _running = next;
    db<Thread>(INF) << "[Debug] Trocando contexto: Thread " + std::to_string(prev -> id()) + " -> Thread " + std::to_string(next -> id()) + "\n";
    // CPU::switch_context() já retorna int
    return CPU::switch_context(prev-> context(), next -> context());
}

void Thread::thread_exit (int exit_code) {
    delete _context;
    db<Thread>(INF) << "[Debug] Finalizando Thread " + std::to_string(_id) + "\n";
    _threads_identifier--;
}

void Thread::init(void (* main)(void *)){
    // criação da thread main
    new (&_main) Thread(main, (void *) "main");
    
    // criação do contexto da thread main
    new (&_main_context) CPU::Context();

    // Criação da fila de prontos
    new (&_ready) Thread::Ready_Queue();
    
    // criação da thread dispatcher
    new (&_dispatcher) Thread((void (*) (void *)) &Thread::dispatcher, (void *) NULL);

    //Troca de contexto da thread main, setando o estado da Thread para running
    Thread::_running = &Thread::_main;
    Thread::_main._state = RUNNING;

    //Troca de contexto da thread system para a thread main
    CPU::switch_context(&_main_context, _main.context());
}


void Thread::dispatcher() {
    db<Thread>(TRC) <<"Chamada de Thread Dispatcher";

    // enquanto há mais de duas threads significa que temos a thread system e a thread usuário funcionais
    while(Thread::_threads_identifier > 2){
        // escolhendo a próxima thread a ser executada
        // tirando a thread que está na saída da fila de threads prontas
        Thread * next = Thread::_ready.remove()->object();

        // Atualização do status da thread dispatcher e res
    };
};


__END_API