mac
---

### 1 conf

```sh
bash ./configure \
--with-debug-level=slowdebug \
--with-jvm-variants=server \
--with-freetype=bundled \
--with-boot-jdk=/Library/Java/JavaVirtualMachines/adoptopenjdk-15.jdk/Contents/Home \
--with-target-bits=64 \
--disable-warnings-as-errors \
--enable-dtrace
```

### 2 compile-commands

```sh
make CONF=macosx-x86_64-server-slowdebug compile-commands
```

### 3 build

```sh
make CONF=macosx-x86_64-server-slowdebug
```

### 4 verify

```sh
./build/macosx-x86_64-server-slowdebug/jdk/bin/java -version
```
