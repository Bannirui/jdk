#!/bin/bash

JDK_HOME=/home/dingrui/MyDev/code/cpp/jdk/build/linux-x86_64-server-slowdebug/jdk
JAVAC=${JDK_HOME}/bin/javac
JAVA=${JDK_HOME}/bin/java

# 类(java不带.java后缀文件名)
CLASS_NAME=$1
if [ -z "$CLASS_NAME" ]; then
  echo "Usage: $0 Hello"
  exit 1
fi

# 源文件
SRC_FILE_ABS_PATH=$(pwd)/my_test/${CLASS_NAME}.java

echo "[*] Compiling $CLASS_NAME ..."
$JAVAC "$SRC_FILE_ABS_PATH"

if [ $? -ne 0 ]; then
  echo "[!] Compilation failed."
  exit 1
fi

echo "[*] Running $CLASS_NAME ..."
gdb --args $JAVA -cp my_test $CLASS_NAME
