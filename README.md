# Payment system module template for vending machine 

Implement your own logic in MyPaymentSystem class.

For mor information visit https://3voda.ru

### PREREQUISITIES

* ahrmhf gcc toolchain
* libmosquitto-dev
* libmosquittopp-dev
* libpoco-dev

### CROSS BUILDING
```
cmake -DCMAKE_TOOLCHAIN_FILE=cmake_toolchains/ubuntu-armhf.cmake .
make
```