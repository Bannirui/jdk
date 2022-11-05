/*
 * Copyright (c) 2012, 2018, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

#include <strings.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

#include "jni.h"
#include "jni_util.h"
#include "jlong.h"
#include "nio.h"
#include "nio_util.h"

#include "sun_nio_ch_KQueue.h"

JNIEXPORT jint JNICALL
Java_sun_nio_ch_KQueue_keventSize(JNIEnv* env, jclass clazz)
{
    return sizeof(struct kevent);
}

JNIEXPORT jint JNICALL
Java_sun_nio_ch_KQueue_identOffset(JNIEnv* env, jclass clazz)
{
    return offsetof(struct kevent, ident);
}

JNIEXPORT jint JNICALL
Java_sun_nio_ch_KQueue_filterOffset(JNIEnv* env, jclass clazz)
{
    return offsetof(struct kevent, filter);
}

JNIEXPORT jint JNICALL
Java_sun_nio_ch_KQueue_flagsOffset(JNIEnv* env, jclass clazz)
{
    return offsetof(struct kevent, flags);
}

JNIEXPORT jint JNICALL
Java_sun_nio_ch_KQueue_create(JNIEnv *env, jclass clazz) {
    int kqfd = kqueue(); // 创建内核事件队列 返回文件描述符
    if (kqfd < 0) {
        JNU_ThrowIOExceptionWithLastError(env, "kqueue failed");
        return IOS_THROWN;
    }
    return kqfd;
}

JNIEXPORT jint JNICALL
Java_sun_nio_ch_KQueue_register(JNIEnv *env, jclass clazz, jint kqfd,
                                jint fd, jint filter, jint flags)

{
    struct kevent changes[1];
    int res;

    EV_SET(&changes[0], fd, filter, flags, 0, 0, 0); // kevent实例 为这个kevent进行赋值 fd=属于fd的kevent filter=让kqueue关注fd的filter事件 flags=告诉kqueue如何处理这个kevent(添加 移除 ...)
    RESTARTABLE(kevent(kqfd, &changes[0], 1, NULL, 0, NULL), res); // int kevent(int kq, const struct kevent *changelist, int nchanges, struct kevent *eventlist, int nevents, const struct timespec *timeout) 一次系统调用 向kqueue注册kevent事件 changelist=待监听事件 nchanges=待监听事件数量
    return (res == -1) ? errno : 0; // 但凡changes注册发生失败就返回-1 超时返回0
}

JNIEXPORT jint JNICALL
Java_sun_nio_ch_KQueue_poll(JNIEnv *env, jclass clazz, jint kqfd, jlong address,
                            jint nevents, jlong timeout)
{ // kqfd=kqueue()系统调用返回的fd 标识这个kqueue实例 给定超时时间为timeout毫秒 那些已经注册到kqueue队列的事件 监听其中nevents个 将这nevents个事件已经就绪的数量返回出来 并将就绪状态的kevent放在address这个指针指向的这一片内存上
    struct kevent *events = jlong_to_ptr(address); // kevent数组首地址指针
    int res;
    struct timespec ts;
    struct timespec *tsp; // 超时时间

    if (timeout >= 0) {
        ts.tv_sec = timeout / 1000; // 秒
        ts.tv_nsec = (timeout % 1000) * 1000000; // 纳秒
        tsp = &ts;
    } else {
        tsp = NULL;
    }

    res = kevent(kqfd, NULL, 0, events, nevents, tsp); // 系统调用 kqfd=kqueue实例 给定超时时间为tsp毫秒 那些已经注册到kqueue队列的事件 监听其中nevents个 将这nevents个事件已经就绪的数量返回出来 并将就绪状态的kevent放在events这个指针指向的这一片内存上
    if (res < 0) { // 发生异常
        if (errno == EINTR) {
            return IOS_INTERRUPTED;
        } else {
            JNU_ThrowIOExceptionWithLastError(env, "kqueue failed");
            return IOS_THROWN;
        }
    }
    return res; // res个事件处于就绪状态
}
