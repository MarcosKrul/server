# Adequação servidor

## Sobre

Engenharia de Computação, UEPG - 5º período

Projeto realizado para a disciplina de Sistemas Operacionais

Marcos Renan Krul

## Sobre

Adequação código *TCP stream server socket* do livro ***Advanced Linux Programming*** para recebimento de *query params*.

## Módulos implementados

| Módulo | Descrição              | Parâmetros                   |
|---     |---                     |---                           |
| rota   | Executa /sbin/route    | -                            |
| portas | Executa /bin/netstat   | base_url?tipo=TIPO           |
| cal    | Executa /bin/ncal -h   | base_url?mes=MES&ano=ANO     |
| rede   | Executa /sbin/ifconfig | base_url?interface=INTERFACE |

## Utilização

* Clonar o projeto

```
    mkdir teste-servidor
    cd teste-servidor
    git clone https://github.com/MarcosKrul/server .
    make
```

* Compilação e execução

```
    make
    ./server -p 8080 -a localhost -v
```
