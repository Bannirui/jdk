# conf
bash ./configure \
--with-debug-level=slowdebug \
--with-jvm-variants=server \
--with-freetype=bundled \
--with-boot-jdk=/usr/lib/jvm/jdk-15 \
--with-target-bits=64 \
--disable-warnings-as-errors

# compile-commands
make CONF=linux-x86_64-server-slowdebug compile-commands

# build or re-build
make CONF=linux-x86_64-server-slowdebug

# verify
./build/linux-x86_64-server-slowdebug/jdk/bin/java --version
