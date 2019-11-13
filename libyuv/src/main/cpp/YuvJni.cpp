#include "YuvJni.h"
#include "YuvConvert.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_libyuv_util_YuvUtil_yuvCompress(JNIEnv *env, jclass jcls,
                                         jbyteArray nv21Src, jint width,
                                         jint height, jbyteArray i420Dst,
                                         jint dst_width, jint dst_height,
                                         jint mode, jint degree,
                                         jboolean isMirror) {

    jbyte *src_nv21_data = env->GetByteArrayElements(nv21Src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(i420Dst, NULL);
    jbyte *tmp_dst_i420_data = NULL;

    // nv21转化为i420
    jbyte *i420_data = (jbyte *) malloc(sizeof(jbyte) * width * height * 3 / 2);
    NV21ToI420(src_nv21_data, width, height, i420_data);
    tmp_dst_i420_data = i420_data;

    // 镜像
    jbyte *i420_mirror_data = NULL;
    if (isMirror) {
        i420_mirror_data = (jbyte *) malloc(sizeof(jbyte) * width * height * 3 / 2);
        MirrorI420(tmp_dst_i420_data, width, height, i420_mirror_data);
        tmp_dst_i420_data = i420_mirror_data;
    }

    // 缩放
    jbyte *i420_scale_data = NULL;
    if (width != dst_width || height != dst_height) {
        i420_scale_data = (jbyte *) malloc(sizeof(jbyte) * width * height * 3 / 2);
        scaleI420(tmp_dst_i420_data, width, height, i420_scale_data, dst_width, dst_height, mode);
        tmp_dst_i420_data = i420_scale_data;
        width = dst_width;
        height = dst_height;
    }

    // 旋转
    jbyte *i420_rotate_data = NULL;
    if (degree == libyuv::kRotate90 || degree == libyuv::kRotate180 ||
        degree == libyuv::kRotate270) {
        i420_rotate_data = (jbyte *) malloc(sizeof(jbyte) * width * height * 3 / 2);
        rotateI420(tmp_dst_i420_data, width, height, i420_rotate_data, degree);
        tmp_dst_i420_data = i420_rotate_data;
    }

    // 同步数据
    // memcpy(dst_i420_data, tmp_dst_i420_data, sizeof(jbyte) * width * height * 3 / 2);
    jint len = env->GetArrayLength(i420Dst);
    memcpy(dst_i420_data, tmp_dst_i420_data, len);
    tmp_dst_i420_data = NULL;
    env->ReleaseByteArrayElements(i420Dst, dst_i420_data, 0);

    // 释放
    if (i420_data != NULL) free(i420_data);
    if (i420_mirror_data != NULL) free(i420_mirror_data);
    if (i420_scale_data != NULL) free(i420_scale_data);
    if (i420_rotate_data != NULL) free(i420_rotate_data);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_libyuv_util_YuvUtil_yuvCropI420(JNIEnv *env, jclass jcls, jbyteArray src_, jint width,
                                         jint height, jbyteArray dst_, jint dst_width,
                                         jint dst_height,
                                         jint left, jint top) {
    //裁剪的区域大小不对
    if (left + dst_width > width || top + dst_height > height) {
        return;
    }
    //left和top必须为偶数，否则显示会有问题
    if (left % 2 != 0 || top % 2 != 0) {
        return;
    }
    jint src_length = env->GetArrayLength(src_);
    jbyte *src_i420_data = env->GetByteArrayElements(src_, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(dst_, NULL);
    CropI420(src_i420_data, src_length, width, height, dst_i420_data, dst_width, dst_height, left,
             top);
    env->ReleaseByteArrayElements(dst_, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_libyuv_util_YuvUtil_yuvMirrorI420(JNIEnv *env, jclass jcls, jbyteArray i420Src,
                                           jint width, jint height, jbyteArray i420Dst) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(i420Dst, NULL);
    // i420数据镜像
    MirrorI420(src_i420_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(i420Dst, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_libyuv_util_YuvUtil_yuvScaleI420(JNIEnv *env, jclass jcls, jbyteArray i420Src,
                                          jint width, jint height, jbyteArray i420Dst,
                                          jint dstWidth, jint dstHeight, jint mode) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(i420Dst, NULL);
    // i420数据缩放
    scaleI420(src_i420_data, width, height, dst_i420_data, dstWidth, dstHeight, mode);
    env->ReleaseByteArrayElements(i420Dst, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_libyuv_util_YuvUtil_yuvRotateI420(JNIEnv *env, jclass jcls, jbyteArray i420Src,
                                           jint width, jint height, jbyteArray i420Dst,
                                           jint degree) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(i420Dst, NULL);
    // i420数据旋转
    rotateI420(src_i420_data, width, height, dst_i420_data, degree);
    env->ReleaseByteArrayElements(i420Dst, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_libyuv_util_YuvUtil_yuvNV21ToI420(JNIEnv *env, jclass jcls, jbyteArray nv21Src,
                                           jint width, jint height, jbyteArray i420Dst) {
    jbyte *src_nv21_data = env->GetByteArrayElements(nv21Src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(i420Dst, NULL);
    // nv21转化为i420
    NV21ToI420(src_nv21_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(i420Dst, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_libyuv_util_YuvUtil_yuvI420ToNV21(JNIEnv *env, jclass jcls, jbyteArray i420Src,
                                           jint width, jint height, jbyteArray nv21Dst) {

    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_nv21_data = env->GetByteArrayElements(nv21Dst, NULL);
    I420ToNv21(src_i420_data, width, height, dst_nv21_data);
    env->ReleaseByteArrayElements(nv21Dst, dst_nv21_data, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_libyuv_util_YuvUtil_yuvNV21ToI420AndRotate(JNIEnv *env, jclass jcls, jbyteArray nv21Src,
                                                    jint width, jint height, jbyteArray i420Dst,
                                                    jint degree) {
    jbyte *src_nv21_data = env->GetByteArrayElements(nv21Src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(i420Dst, NULL);
    switch (degree) {
        case libyuv::kRotate0:
            NV21ToI420(src_nv21_data, width, height, dst_i420_data);
            break;
        case libyuv::kRotate90:
            NV21ToI420AndRotateClockwise(src_nv21_data, width, height, dst_i420_data);
            break;
        case libyuv::kRotate180:
            NV21ToI420AndRotate180(src_nv21_data, width, height, dst_i420_data);
            break;
        case libyuv::kRotate270:
            NV21ToI420AndRotateAntiClockwise(src_nv21_data, width, height, dst_i420_data);
            break;
    }
    env->ReleaseByteArrayElements(i420Dst, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvI420ToRGB24
        (JNIEnv *env, jclass jcls, jbyteArray i420Src, jint width, jint height,
         jbyteArray rgb24Dst) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_rgb24_data = env->GetByteArrayElements(rgb24Dst, NULL);
    I420ToRGB24(src_i420_data, width, height, dst_rgb24_data);
    env->ReleaseByteArrayElements(rgb24Dst, dst_rgb24_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvI420ToARGB
        (JNIEnv *env, jclass jcls, jbyteArray i420Src, jint width, jint height, jint dst_stride,
         jbyteArray argbDst) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_argb_data = env->GetByteArrayElements(argbDst, NULL);
    I420ToARGB(src_i420_data, width, height, dst_stride, dst_argb_data);
    env->ReleaseByteArrayElements(argbDst, dst_argb_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvI420ToRGBAMac
        (JNIEnv *env, jclass jcls, jbyteArray i420Src, jint width, jint height, jint dst_stride,
         jbyteArray rgbaMacDst) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_rgba_mac_data = env->GetByteArrayElements(rgbaMacDst, NULL);
    I420ToRGBAMac(src_i420_data, width, height, dst_stride, dst_rgba_mac_data);
    env->ReleaseByteArrayElements(rgbaMacDst, dst_rgba_mac_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvI420ToARGB4444
        (JNIEnv *env, jclass jcls, jbyteArray i420Src, jint width, jint height, jint dst_stride,
         jbyteArray argb4444Dst) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_argb4444_data = env->GetByteArrayElements(argb4444Dst, NULL);
    I420ToARGB4444(src_i420_data, width, height, dst_stride, dst_argb4444_data);
    env->ReleaseByteArrayElements(argb4444Dst, dst_argb4444_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvI420ToRGB565
        (JNIEnv *env, jclass jcls, jbyteArray i420Src, jint width, jint height,
         jbyteArray rgb565Dst) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_rgb565_data = env->GetByteArrayElements(rgb565Dst, NULL);
    I420ToRGB565(src_i420_data, width, height, dst_rgb565_data);
    env->ReleaseByteArrayElements(rgb565Dst, dst_rgb565_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvI420ToRGB565Android
        (JNIEnv *env, jclass jcls, jbyteArray i420Src, jint width, jint height,
         jbyteArray rgb565Dst) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_rgb565_data = env->GetByteArrayElements(rgb565Dst, NULL);
    I420ToRGB565Android(src_i420_data, width, height, dst_rgb565_data);
    env->ReleaseByteArrayElements(rgb565Dst, dst_rgb565_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvI420ToARGB1555
        (JNIEnv *env, jclass jcls, jbyteArray i420Src, jint width, jint height, jint dst_stride,
         jbyteArray argb1555Dst) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_argb1555_data = env->GetByteArrayElements(argb1555Dst, NULL);
    I420ToARGB1555(src_i420_data, width, height, dst_stride, dst_argb1555_data);
    env->ReleaseByteArrayElements(argb1555Dst, dst_argb1555_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvI420ToYUY2
        (JNIEnv *env, jclass jcls, jbyteArray i420Src, jint width, jint height, jint dst_stride,
         jbyteArray yuy2Dst) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_yuy2_data = env->GetByteArrayElements(yuy2Dst, NULL);
    I420ToYUY2(src_i420_data, width, height, dst_stride, dst_yuy2_data);
    env->ReleaseByteArrayElements(yuy2Dst, dst_yuy2_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvI420ToUYVY
        (JNIEnv *env, jclass jcls, jbyteArray i420Src, jint width, jint height, jint dst_stride,
         jbyteArray uyvyDst) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_uyvy_data = env->GetByteArrayElements(uyvyDst, NULL);
    I420ToUYVY(src_i420_data, width, height, dst_stride, dst_uyvy_data);
    env->ReleaseByteArrayElements(uyvyDst, dst_uyvy_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvI420ToYV12
        (JNIEnv *env, jclass jcls, jbyteArray i420Src, jint width, jint height, jint dst_stride,
         jbyteArray yv12Dst) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_yv12_data = env->GetByteArrayElements(yv12Dst, NULL);
    I420ToYV12(src_i420_data, width, height, dst_stride, dst_yv12_data);
    env->ReleaseByteArrayElements(yv12Dst, dst_yv12_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvYV12ToI420
        (JNIEnv *env, jclass jcls, jbyteArray yv12Src, jint width, jint height,
         jbyteArray i420Dst) {
    jbyte *src_yv12_data = env->GetByteArrayElements(yv12Src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(i420Dst, NULL);
    YV12ToI420(src_yv12_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(i420Dst, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvNV12ToI420
        (JNIEnv *env, jclass jcls, jbyteArray nv12Src, jint width, jint height,
         jbyteArray i420Dst) {
    jbyte *src_nv12_data = env->GetByteArrayElements(nv12Src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(i420Dst, NULL);
    NV12ToI420(src_nv12_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(i420Dst, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvI420ToNv12
        (JNIEnv *env, jclass jcls, jbyteArray i420Src, jint width, jint height,
         jbyteArray nv12Dst) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_nv12_data = env->GetByteArrayElements(nv12Dst, NULL);
    I420ToNv12(src_i420_data, width, height, dst_nv12_data);
    env->ReleaseByteArrayElements(nv12Dst, dst_nv12_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvNV12ToI420AndRotate
        (JNIEnv *env, jclass jcls, jbyteArray nv12Src, jint width, jint height, jbyteArray i420Dst,
         jint degree) {
    jbyte *src_nv12_data = env->GetByteArrayElements(nv12Src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(i420Dst, NULL);
    switch (degree) {
        case libyuv::kRotate0:
            NV12ToI420(src_nv12_data, width, height, dst_i420_data);
            break;
        case libyuv::kRotate90:
            NV12ToI420AndRotateClockwise(src_nv12_data, width, height, dst_i420_data);
            break;
        case libyuv::kRotate180:
            NV12ToI420AndRotate180(src_nv12_data, width, height, dst_i420_data);
            break;
        case libyuv::kRotate270:
            NV12ToI420AndRotateAntiClockwise(src_nv12_data, width, height, dst_i420_data);
            break;
    }
    env->ReleaseByteArrayElements(i420Dst, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvNV12ToRGB565
        (JNIEnv *env, jclass jcls, jbyteArray nv12Src, jint width, jint height,
         jbyteArray rgb565Dst) {
    jbyte *src_nv12_data = env->GetByteArrayElements(nv12Src, NULL);
    jbyte *dst_rgb565_data = env->GetByteArrayElements(rgb565Dst, NULL);
    NV12ToRGB565(src_nv12_data, width, height, dst_rgb565_data);
    env->ReleaseByteArrayElements(rgb565Dst, dst_rgb565_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvI420ToRGBAIPhone
        (JNIEnv *env, jclass jcls, jbyteArray i420Src, jint width, jint height, jint dst_stride,
         jbyteArray rgbaDst) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_rgba_data = env->GetByteArrayElements(rgbaDst, NULL);
    I420ToRGBAIPhone(src_i420_data, width, height, dst_stride, dst_rgba_data);
    env->ReleaseByteArrayElements(rgbaDst, dst_rgba_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvI420Copy
        (JNIEnv *env, jclass jcls, jbyteArray i420Src, jint width, jint height, jint dst_stride,
         jbyteArray i420Dst) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(i420Dst, NULL);
    I420Copy(src_i420_data, width, height, dst_stride, dst_i420_data);
    env->ReleaseByteArrayElements(i420Dst, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvUYVYToI420
        (JNIEnv *env, jclass jcls, jbyteArray uyvySrc, jint width, jint height,
         jbyteArray i420Dst) {
    jbyte *src_uyvy_data = env->GetByteArrayElements(uyvySrc, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(i420Dst, NULL);
    UYVYToI420(src_uyvy_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(i420Dst, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvYUY2ToI420
        (JNIEnv *env, jclass jcls, jbyteArray yuy2Src, jint width, jint height,
         jbyteArray i420Dst) {
    jbyte *src_yuy2_data = env->GetByteArrayElements(yuy2Src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(i420Dst, NULL);
    YUY2ToI420(src_yuy2_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(i420Dst, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvRGB24ToARGB
        (JNIEnv *env, jclass jcls, jbyteArray rgb24Src, jint width, jint height, jint dst_stride,
         jbyteArray argbDst) {
    jbyte *src_rgb24_data = env->GetByteArrayElements(rgb24Src, NULL);
    jbyte *dst_argb_data = env->GetByteArrayElements(argbDst, NULL);
    RGB24ToARGB(src_rgb24_data, width, height, dst_stride, dst_argb_data);
    env->ReleaseByteArrayElements(argbDst, dst_argb_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvRGB24ToI420
        (JNIEnv *env, jclass jcls, jbyteArray rgb24Src, jint width, jint height,
         jbyteArray i420Dst) {
    jbyte *src_rgb24_data = env->GetByteArrayElements(rgb24Src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(i420Dst, NULL);
    RGB24ToI420(src_rgb24_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(i420Dst, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvI420ToARGBMac
        (JNIEnv *env, jclass jcls, jbyteArray i420Src, jint width, jint height, jint dst_stride,
         jbyteArray argbMacDst) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_argb_mac_data = env->GetByteArrayElements(argbMacDst, NULL);
    I420ToARGBMac(src_i420_data, width, height, dst_stride, dst_argb_mac_data);
    env->ReleaseByteArrayElements(argbMacDst, dst_argb_mac_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvARGBMacToI420
        (JNIEnv *env, jclass jcls, jbyteArray argbMacSrc, jint width, jint height,
         jbyteArray i420Dst) {
    jbyte *src_argb_mac_data = env->GetByteArrayElements(argbMacSrc, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(i420Dst, NULL);
    ARGBMacToI420(src_argb_mac_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(i420Dst, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvMirrorI420LeftRight
        (JNIEnv *env, jclass jcls, jbyteArray i420Src, jint width, jint height,
         jbyteArray i420Dst) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(i420Dst, NULL);
    MirrorI420LeftRight(src_i420_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(i420Dst, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL Java_com_libyuv_util_YuvUtil_yuvMirrorI420UpDown
        (JNIEnv *env, jclass jcls, jbyteArray i420Src, jint width, jint height,
         jbyteArray i420Dst) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(i420Dst, NULL);
    MirrorI420UpDown(src_i420_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(i420Dst, dst_i420_data, 0);
}
