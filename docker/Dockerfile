# 使用官方Ubuntu22.04作为基础镜像
FROM --platform=linux/amd64 ubuntu:22.04

# 设置非交互模式 避免安装过程中阻塞
ENV DEBIAN_FRONTEND=noninteractive

# 更新源并安装所需工具
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    # gcc g++ make ld etc
    build-essential \
    # x86 assembler
    nasm \
    gdb gdbserver \
    # ld objdump objcopy
    binutils \
    # mkfs dd支持
    dosfstools \
    # mount umount sync
    util-linux \
    # cp rm等基础命令
    coreutils \
    git wget \
    # OpenJDK 21和编译openjdk-22源码需要的依赖
    openjdk-21-jdk autoconf libasound2-dev libcups2-dev libfontconfig1-dev libx11-dev libxext-dev libxrender-dev libxrandr-dev libxtst-dev libxt-dev file zip unzip gawk \
    && rm -rf /var/lib/apt/lists/*

# 设置Java环境变量
ENV JAVA_HOME=/usr/lib/jvm/java-21-openjdk-amd64
ENV PATH="$JAVA_HOME/bin:$PATH"

# 设置工作目录
VOLUME /home/dev
WORKDIR /home/dev

# 容器启动后保持交互 shell
CMD ["/bin/bash"]
