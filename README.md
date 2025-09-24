# Welcome to the JDK!

> 从官网fork的代码切的学习分支

### 1 编译环境

- 做一个名my-linux-dev的镜像 `docker build ./docker -t my-linux-dev`
- 用镜像启个名为my-linux-dev的容器 `docker run --ulimit nofile=65535:65535 --rm -it --privileged --name my-linux-dev -v /etc/localtime:/etc/localtime:ro -v $PWD:/home/dev my-linux-dev`

### 2 在docker中编译

#### 2.1 生成make脚本

```sh
bash ./configure \
--with-debug-level=slowdebug \
--with-jvm-variants=server \
--with-freetype=bundled \
--with-boot-jdk=$JAVA_HOME \
--with-target-bits=64 \
--disable-warnings-as-errors \
--with-extra-cxxflags="-std=c++14"
```

#### 2.2 make编译

```sh
make CONF=linux-x86_64-server-slowdebug
```

#### 2.3 java

```sh
./build/linux-x86_64-server-slowdebug/jdk/bin/java -version
```

### 3 调试&运行

> java源代码写在根目录的`my_test`下

- 运行 `./my_exe.sh 类名`
- 调试 `./my_debug.sh 类名`