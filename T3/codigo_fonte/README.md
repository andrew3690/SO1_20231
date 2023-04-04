### COMANDOS PARA COMPILAR, EXECUTAR E TESTAR O PROGRAMA

Para utilização dos comandos abaixo, é indicada a instalação do pacote ```build-essential``` no sistema. Ele já incorpora a instalação do make (para execução do MakeFile) e do g++ (compilador utilizado):

```
    sudo apt install build-essential
```

 - Para compilar, basta digitar:

```
    make
```

 - Para executar o código:

```
    make run
 ```

 - Para gerar o teste de Leak Memory (Valgrind):

 ```
    make check
 ```
 
 **OBS.:** Para executar o comando acima, o ```valgrind``` deve estar instalado na máquina. Veja como instalar o ```valgrind``` [aqui](https://wiki.ubuntu.com/Valgrind)

 - Para gerar o arquivo tar.gz:

 ```
    make submission
 ```
