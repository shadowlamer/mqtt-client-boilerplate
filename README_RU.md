# Модуль платежной системы для вендингового терминала

Эта библиотека предназначена для упрощения написания модулей внешних платежных систем
для вендинговых устройств

Пример реализации платежной системы есть в каталоге src. Для реализации собственной 
платежной системы нужно реализовать свою бизнес-логику в классе MyPaymentSystem.

### Зависимости

* ahrm64 gcc toolchain
* libmosquitto-dev:arm64
* libmosquittopp-dev:arm64
* libpoco-dev:arm64

### Сборка платежной системы

```
mkdir buid
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=cmake_toolchains/ubuntu-arm64.cmake ..
make
```

### Сборка библиотеки в виде DEB пакета

```
mkdir buid
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=cmake_toolchains/ubuntu-arm64.cmake ..
make package
```

### Сборка документации
```
mkdir buid
cd build
cmake ..
make doc-doxygen
```