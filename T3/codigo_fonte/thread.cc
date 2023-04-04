#include "thread.h"

__BEGIN_API

// Inicializando os atributos estáticos da classe Thread
int Thread::_threads_identifier = 0;
Thread* Thread::_running = nullptr;
Thread::Ready_Queue Thread::_ready;
Thread Thread::_dispatcher;
Thread Thread::_main;
CPU::Context Thread::_main_context;

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

void Thread::dispatcher() {
    db<Thread>(TRC) <<"Chamada de Thread Dispatcher";

    // enquanto há mais de duas threads significa que temos a thread system e a thread usuário funcionais
    while(Thread::_threads_identifier > 2){
        // escolhendo a próxima thread a ser executada
        // tirando a thread que está na saída da fila de threads prontas
        Thread * next = Thread::_ready.remove()->object();

        // Atualização do status da thread dispatcher e inserção da thread na fila de prontos
        Thread::_dispatcher._state = READY;
        Thread::_ready.insert_tail(&Thread::_dispatcher._link);

        // Atualiza o ponteiro _running para apontar para a próxima thread a ser executada
        Thread * prev = Thread::_running;
        Thread::_running = next;

        // Atualiza o estado da próxima thread a ser executada para Running
        next->_state = RUNNING;

        //Troca o contexto entre duas threads
        Thread::switch_context(&_dispatcher, next);

        //Testa se o estado da próxima thread é FINISHING, caso sim, remove-o da fila _ready
        if(next->_state == FINISHING){
            Thread::_ready.remove(next);
            Thread::_threads_identifier--;
        };
    };
    //Muda o estado da thread dispatcher para FINISHING
    Thread::_dispatcher._state = FINISHING;

    // Remove a thread dispatcher da fila de prontos
    Thread::_ready.remove(&Thread::_dispatcher);

    //Troca de contexto da thread dispatcher para main
    Thread::switch_context(&Thread::_dispatcher, &Thread::_main);
};

void Thread::init(void (* main)(void *)){
    // criação da thread main
    new (&_main) Thread(main, (void *) "main");
    
    // criação do contexto da thread main
    new (&_main_context) CPU::Context();

    // Criação da fila de prontos
    new (&_ready) Thread::Ready_Queue();
    
    // criação da thread dispatcher
    new (&_dispatcher) Thread((void (*) (void *)) &Thread::dispatcher, (void *) NULL);

    //Para realizar a troca de contexto da thread main, seta-se o estado da Thread para running
    Thread::_running = &Thread::_main;
    Thread::_main._state = RUNNING;

    //Troca de contexto da thread system para a thread main
    CPU::switch_context(&_main_context, _main.context());
}

void Thread::yield() {
    db<Thread>(TRC) <<"Chamada de Thread yield";
    Thread * prev = Thread::_running;

    // escolhendo a próxima thread a ser executada, ou seja a thread que está na fila de prontos
    Thread * next = Thread::_ready.remove()->object();

    /*
    Atualiza a prioridade da tarefa que estava sendo executada (aquela que chamou yield) com o
    timestamp atual, a fim de reinserí-la na fila de prontos atualizada (cuide de casos especiais, como
    estado ser FINISHING ou Thread main que não devem ter suas prioridades alteradas)
    */
    if(prev != &Thread::_main && prev->_state != FINISHING){
        prev->_link.rank(std::chrono::duration_cast<std::chrono::microseconds>
        (std::chrono::high_resolution_clock::now().time_since_epoch()).count());
        
        // reinsira a thread que estava executando na fila de prontos
        if (prev->id() > 0) {
            prev->_state = READY;
            Thread::_ready.insert_tail(&prev->_link);
        }
    };

    //atualiza o ponteiro _running
    Thread::_running = next;

    //atualiza o estado da próxima thread a ser executada
    next->_state = RUNNING;

    //troque o contexto entre as threads
    Thread::switch_context(prev,next);
}

Thread::~Thread() {
    // remoção da fila de prontos da thread que está chamando o valor
    Thread::_ready.remove(this);
    // deleta-se o contexto da thread
    delete context();
}

__END_API