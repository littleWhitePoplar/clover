# clover

* 0.How to get?

```bash
git clone https://github.com/littleWhitePoplar/clover.git
```

* 1.How to build？

```bash
cd clover
mkdir build && cd build
cmake -DARCH=aarch64 -DCMAKE_C_COMPILER=aarch64-linux-gnu-gcc -DCMAKE_CXX_COMPILER=aarch64-linux-gnu-g++ -G Ninja ..
ninja
```

* 2.How to use?

```bash
qemu-system-aarch64 -nographic -smp 1 -machine virt -cpu cortex-a57 -kernel os.elf
```
