archlinux
---

### 1 conf

```sh
bash ./configure \
--with-debug-level=slowdebug \
--with-jvm-variants=server \
--with-freetype=bundled \
--with-boot-jdk=/usr/lib/jvm/jdk-15 \
--with-target-bits=64 \
--disable-warnings-as-errors
```

### 2 compile-commands

```shell
make CONF=linux-x86_64-server-slowdebug compile-commands
```

### 3 build or re-build

```sh
make CONF=linux-x86_64-server-slowdebug
```

### 4 verify

```sh
./build/linux-x86_64-server-slowdebug/jdk/bin/java --version
```
