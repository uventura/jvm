# Java Virtual Machine (JVM)
Implementação da Java Virtual Machine(JVM) utilizando C.

- [JVM](#java-virtual-machine-jvm)
  - [Windows](#compilando-o-projeto-no-windows)
  - [Linux](#compilando-o-projeto-no-linux)
  - [Modo de Leitura](#modo-de-leitura)
  - [Modo de Execução](#modo-de-execução)
  - [Modo de Execução com Depuração](#modo-de-execução-com-depuração)


## Compilando o projeto no Windows
No Powershell pode-se utilizar:
```shell
./build.ps1
```
No CMD pode-se utilizar:
```shell
./build.bat
```

> Após este processo de compilação, na pasta `bin` haverá o artefato `jvm.exe`

## Compilando o projeto no Linux
Use o comando:
```shell
make
```

> Após este processo de compilação, na pasta `bin` haverá o artefato `jvm`

## Modo de Leitura
Use o comando:
```shell
./bin/jvm -read <caminho>/File.class
```

## Modo de Execução
Use o comando:
```shell
./bin/jvm -run <path>/File.class
```

## Modo de Execução com Depuração
```shell
./bin/jvm -d -run <path>/File.class
```
