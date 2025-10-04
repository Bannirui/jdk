FROM archlinux:latest

# ---------- Proxy (optional) ----------
ARG http_proxy
ARG https_proxy
ENV http_proxy=$http_proxy
ENV https_proxy=$https_proxy

# ---------- Snapshot Date ----------
# Use a snapshot before GCC 15 (GCC 12 era ≈ May 2023)
ARG DATE=2023/05/01
RUN echo "Server=https://archive.archlinux.org/repos/${DATE}/\$repo/os/\$arch" > /etc/pacman.d/mirrorlist

# ---------- Pacman config ----------
RUN sed -i 's/^SigLevel.*/SigLevel = Never/g' /etc/pacman.conf && \
    sed -i 's/^#ParallelDownloads/ParallelDownloads/g' /etc/pacman.conf

# ---------- Install GCC 12 toolchain + deps ----------
RUN pacman -Syu --noconfirm \
    base-devel \
    gcc \
    git \
    gdb \
    gdb-common \
    autoconf \
    alsa-lib \
    libcups \
    fontconfig \
    libx11 \
    libxext \
    libxrender \
    libxrandr \
    libxtst \
    libxt \
    zip unzip file gawk \
    jdk20-openjdk \
    && pacman -Scc --noconfirm

# ---------- Environment ----------
WORKDIR /home/dev
ENV JAVA_HOME=/usr/lib/jvm/java-20-openjdk
ENV PATH="$JAVA_HOME/bin:$PATH"
VOLUME /home/dev

CMD ["/bin/bash"]