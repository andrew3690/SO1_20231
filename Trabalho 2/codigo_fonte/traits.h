#ifndef traits_h
#define traits_h

//Não alterar as 3 declarações abaixo

#define __BEGIN_API             namespace SOLUTION {
#define __END_API               }
#define __USING_API            using namespace SOLUTION;

__BEGIN_API
//declaração das classes criadas nos trabalhos devem ser colocadas aqui
class CPU; 
class Main;
class Debug;
class System;
class Thread;

//declaração da classe Traits
template<typename T>
struct Traits {
};

template<> struct Traits<Debug>: public Traits<void>
{
 static const bool error = false;
 static const bool warning = false;
 static const bool info = false;
 static const bool trace = true;
};

template<> struct Traits<System>: public Traits<void>
{
 static const bool error = false;
 static const bool warning = false;
 static const bool info = false;
 static const bool trace = true;
};

template<> struct Traits<Thread>: public Traits<void>
{
 static const bool error = false;
 static const bool warning = false;
 static const bool info = false;
 static const bool trace = true;
};

// Exemplo de Debug utilizado para a classe Traits
template<typename T>
struct Traits {
 static const bool debugged = false;
};

template<> struct Traits<CPU>
{
    //Adicionar aqui a declaração do tamanho da Pilha
    static const unsigned int STACK_SIZE = 1024 * 128;// tamanho total da pilha
};

__END_API

#endif
