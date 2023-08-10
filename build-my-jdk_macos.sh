# conf
bash ./configure \
--with-debug-level=slowdebug \
--with-jvm-variants=server \
--with-freetype=bundled \
--with-boot-jdk=/Library/Java/JavaVirtualMachines/adoptopenjdk-15.jdk/Contents/Home \
--with-target-bits=64 \
--disable-warnings-as-errors \
--enable-dtrace

# compile-commands
make CONF=macosx-x86_64-server-slowdebug compile-commands

# build
make CONF=macosx-x86_64-server-slowdebug

# verify
./build/macosx-x86_64-server-slowdebug/jdk/bin/java -version
