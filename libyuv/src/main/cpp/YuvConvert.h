#include <jni.h>
#include <string>
#include "libyuv.h"

#ifndef YUV_CONVERT
#define YUV_CONVERT


void scaleI420(jbyte *src_i420_data, jint width, jint height, jbyte *dst_i420_data, jint dst_width,
               jint dst_height, jint mode);

void rotateI420(jbyte *src_i420_data, jint width, jint height, jbyte *dst_i420_data, jint degree);

void RotateI420fff(jbyte *src_i420_data, jint width, jint height,
                   jbyte *dst_i420_data, jint degree);

void MirrorI420(jbyte *src_i420_data, jint width, jint height, jbyte *dst_i420_data);

void CropI420(jbyte *src_i420_data, jint src_length, jint width, jint height,
              jbyte *dst_i420_data, jint dst_width, jint dst_height, jint left, jint top);

void I420ToNv12(jbyte *src_i420_data, jint width, jint height, jbyte *src_nv12_data);

void I420ToRGB24(jbyte *src_i420_data, jint width, jint height, jbyte *dst_rgb24_data);

void I420ToARGB(jbyte *src_i420_data, jint width, jint height,
                jint dst_stride, jbyte *dst_argb_data);

void I420ToRGBAMac(jbyte *src_i420_data, jint width, jint height, jint dst_stride,
                   jbyte *dst_rgba_mac_data);

void I420ToARGB4444(jbyte *src_i420_data, jint width, jint height, jint dst_stride,
                    jbyte *dst_argb4444_data);

void I420ToRGB565(jbyte *src_i420_data, jint width, jint height, jbyte *dst_rgb565_data);

void I420ToRGB565Android(jbyte *src_i420_data, jint width, jint height, jbyte *dst_rgb565_data);

void I420ToARGB1555(jbyte *src_i420_data, jint width, jint height, jint dst_stride,
                    jbyte *dst_argb1555_data);

void I420ToYUY2(jbyte *src_i420_data, jint width, jint height,
                jint dst_stride, jbyte *dst_yuy2_data);

void I420ToUYVY(jbyte *src_i420_data, jint width, jint height,
                jint dst_stride, jbyte *dst_uyvy_data);

void I420ToYV12(jbyte *src_i420_data, jint width, jint height,
                jint dst_stride, jbyte *dst_yv12_data);

void YV12ToI420(jbyte *src_yv12_data, jint width, jint height, jbyte *dst_i420_data);

void NV12ToI420(jbyte *src_nv21_data, jint width, jint height, jbyte *dst_i420_data);

void I420ToNv21(jbyte *src_i420_data, jint width, jint height, jbyte *src_nv21_data);

void NV12ToI420AndRotate180(jbyte *src_nv12_data, jint width, jint height, jbyte *dst_i420_data);

void NV12ToI420AndRotateClockwise(jbyte *src_nv12_data, jint width, jint height,
                                  jbyte *dst_i420_data);

void NV12ToI420AndRotateAntiClockwise(jbyte *src_nv12_data, jint width, jint height,
                                      jbyte *dst_i420_data);

void NV12ToRGB565(jbyte *src_nv12_data, jint width, jint height, jbyte *dst_rgb565_data);

void NV21ToI420(jbyte *src_nv21_data, jint width, jint height, jbyte *dst_i420_data);

void NV21ToI420AndRotate180(jbyte *src_nv21_data, jint width, jint height, jbyte *dst_i420_data);

void NV21ToI420AndRotateClockwise(jbyte *src_nv21_data, jint width,
                                  jint height, jbyte *dst_i420_data);

void NV21ToI420AndRotateAntiClockwise(jbyte *src_nv21_data, jint width,
                                      jint height, jbyte *dst_i420_data);

void I420ToRGBAIPhone(jbyte *src_i420_data, jint width, jint height,
                      jint dst_stride, jbyte *dst_rgba_data);

void I420Copy(jbyte *src_i420_data, jint width, jint height,
              jint dst_stride, jbyte *dst_i420_data);

void UYVYToI420(jbyte *src_uyvy_data, jint width, jint height, jbyte *dst_i420_data);

void YUY2ToI420(jbyte *src_yuy2_data, jint width, jint height, jbyte *dst_i420_data);

void RGB24ToARGB(jbyte *src_rbg24_data, jint width, jint height,
                 jint dst_stride, jbyte *dst_argb_data);

void RGB24ToI420(jbyte *src_rbg24_data, jint width, jint height, jbyte *dst_i420_data);

void I420ToARGBMac(jbyte *src_i420_data, jint width, jint height,
                   jint dst_stride, jbyte *dst_argb_mac_data);

void ARGBMacToI420(jbyte *src_argb_mac_data, jint width, jint height, jbyte *dst_i420_data);

void MirrorI420LeftRight(jbyte *src_i420_data, jint width, jint height, jbyte *dst_i420_data);

void MirrorI420UpDown(jbyte *src_i420_data, jint width, jint height, jbyte *dst_i420_data);

#endif