# clover

The current branch is mainly for learning aarch64

* How to get?

```bash
git clone -b aarch64 https://github.com/littleWhitePoplar/clover.git
```

* How to build？

```bash
cd clover
mkdir -p build && cd build
cmake -DARCH=aarch64 -DBUILD_TESTS=OFF -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_C_COMPILER=aarch64-linux-gnu-gcc -DCMAKE_CXX_COMPILER=aarch64-linux-gnu-g++ -G Ninja ..
ninja
```

* How to use?

```bash
qemu-system-aarch64 -nographic -smp 1 -machine virt -cpu cortex-a57 -kernel build/bin/kernel.elf
```
