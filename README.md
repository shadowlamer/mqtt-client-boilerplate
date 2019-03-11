# Payment system module template for vending machine 

Implement your own logic in MyPaymentSystem class.

For mor information visit https://3voda.ru

### PREREQUISITIES

* ahrm64 gcc toolchain
* libmosquitto-dev:arm64
* libmosquittopp-dev:arm64
* libpoco-dev:arm64

### CROSS BUILDING
```
cmake -DCMAKE_TOOLCHAIN_FILE=cmake_toolchains/ubuntu-arm64.cmake .
make
```

### PACKAGING LIBRARY
```
cmake -DCMAKE_TOOLCHAIN_FILE=cmake_toolchains/ubuntu-arm64.cmake .
make package

```