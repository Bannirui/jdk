# Welcome to the JDK!

> 从官网fork的代码切的学习分支

### 1 编译环境

#### 1.1 做一个的镜像

```shell
docker buildx build \
  --add-host=host.docker.internal:host-gateway \
  --build-arg http_proxy=http://host.docker.internal:7890 \
  --build-arg https_proxy=http://host.docker.internal:7890 \
  -t my-jdk-dev ./docker/arch
```

#### 1.2 用镜像启个容器

```shell
docker run \
--ulimit nofile=65535:65535 \
--cap-add=SYS_PTRACE \
--security-opt seccomp=unconfined \
--rm -it \
--privileged \
--name my-jdk-dev \
-v /etc/localtime:/etc/localtime:ro \
-v $PWD:/home/dev my-jdk-dev
```

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

before build, i modify the src `src/hotspot/share/utilities/globalDefinitions.hpp`, replace all the `uabs` with `uabs_legacy`.

because of

- ubuntu 22.04 + boot jdk 21 + gcc 11, all of them are ok
- archlinux is rolling release, so it's difficult to trade off historic package version on docker image, it breaks down for jdk21 and gcc12

```sh
make CONF=linux-x86_64-server-slowdebug
```

if need IDEA support

```sh
make CONF=linux-x86_64-server-slowdebug compile-commands
```

#### 2.3 java

```sh
./build/linux-x86_64-server-slowdebug/jdk/bin/java -version
```

### 3 调试&运行

> java源代码写在根目录的`my_test`下

- 运行 `./my_exe.sh 类名`
- 调试 `./my_debug.sh 类名`
