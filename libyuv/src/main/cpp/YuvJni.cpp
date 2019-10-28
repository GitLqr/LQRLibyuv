#include <jni.h>
#include <string>
#include "libyuv.h"

void scaleI420(jbyte *src_i420_data, jint width, jint height, jbyte *dst_i420_data, jint dst_width,
               jint dst_height, jint mode) {

    jint src_i420_y_size = width * height;
    jint src_i420_u_size = (width >> 1) * (height >> 1);
    jbyte *src_i420_y_data = src_i420_data;
    jbyte *src_i420_u_data = src_i420_data + src_i420_y_size;
    jbyte *src_i420_v_data = src_i420_data + src_i420_y_size + src_i420_u_size;

    jint dst_i420_y_size = dst_width * dst_height;
    jint dst_i420_u_size = (dst_width >> 1) * (dst_height >> 1);
    jbyte *dst_i420_y_data = dst_i420_data;
    jbyte *dst_i420_u_data = dst_i420_data + dst_i420_y_size;
    jbyte *dst_i420_v_data = dst_i420_data + dst_i420_y_size + dst_i420_u_size;

    libyuv::I420Scale((const uint8 *) src_i420_y_data, width,
                      (const uint8 *) src_i420_u_data, width >> 1,
                      (const uint8 *) src_i420_v_data, width >> 1,
                      width, height,
                      (uint8 *) dst_i420_y_data, dst_width,
                      (uint8 *) dst_i420_u_data, dst_width >> 1,
                      (uint8 *) dst_i420_v_data, dst_width >> 1,
                      dst_width, dst_height,
                      (libyuv::FilterMode) mode);
}

void rotateI420(jbyte *src_i420_data, jint width, jint height, jbyte *dst_i420_data, jint degree) {
    jint src_i420_y_size = width * height;
    jint src_i420_u_size = (width >> 1) * (height >> 1);

    jbyte *src_i420_y_data = src_i420_data;
    jbyte *src_i420_u_data = src_i420_data + src_i420_y_size;
    jbyte *src_i420_v_data = src_i420_data + src_i420_y_size + src_i420_u_size;

    jbyte *dst_i420_y_data = dst_i420_data;
    jbyte *dst_i420_u_data = dst_i420_data + src_i420_y_size;
    jbyte *dst_i420_v_data = dst_i420_data + src_i420_y_size + src_i420_u_size;

    //要注意这里的width和height在旋转之后是相反的
    if (degree == libyuv::kRotate90 || degree == libyuv::kRotate270) {
        libyuv::I420Rotate((const uint8 *) src_i420_y_data, width,
                           (const uint8 *) src_i420_u_data, width >> 1,
                           (const uint8 *) src_i420_v_data, width >> 1,
                           (uint8 *) dst_i420_y_data, height,
                           (uint8 *) dst_i420_u_data, height >> 1,
                           (uint8 *) dst_i420_v_data, height >> 1,
                           width, height,
                           (libyuv::RotationMode) degree);
    }else{
        libyuv::I420Rotate((const uint8 *) src_i420_y_data, width,
                           (const uint8 *) src_i420_u_data, width >> 1,
                           (const uint8 *) src_i420_v_data, width >> 1,
                           (uint8 *) dst_i420_y_data, width,
                           (uint8 *) dst_i420_u_data, width >> 1,
                           (uint8 *) dst_i420_v_data, width >> 1,
                           width, height,
                           (libyuv::RotationMode) degree);
    }
}

void rotateI420fff(jbyte *src_i420_data, jint width, jint height, jbyte *dst_i420_data, jint degree) {
	jint I420_Y_Size = width * height;
	jint I420_U_Size = (width >> 1)*(height >> 1);
	jint I420_V_Size = I420_U_Size;

    // src: buffer address of  Y channel、U channel and V channel
    jbyte * Y_data_Src = src_i420_data;
    jbyte * U_data_Src = src_i420_data + I420_Y_Size;
    jbyte * V_data_Src = src_i420_data + I420_Y_Size + I420_U_Size;
    jint src_stride_y = width;
    jint src_stride_u = width >> 1;
    jint src_stride_v = src_stride_u;

    //dst: buffer address of Y channel、U channel and V channel
    jbyte * Y_data_Dst = dst_i420_data;
    jbyte * U_data_Dst = dst_i420_data + I420_Y_Size;
    jbyte * V_data_Dst = dst_i420_data + I420_Y_Size + I420_U_Size;
    jint Dst_Stride_Y;
    jint Dst_Stride_U;
    jint Dst_Stride_V;
    if (degree == libyuv::kRotate90 || degree == libyuv::kRotate270)
    {
        Dst_Stride_Y = height;
        Dst_Stride_U = height >> 1;
        Dst_Stride_V = Dst_Stride_U;
    }
    else
    {
        Dst_Stride_Y = width;
        Dst_Stride_U = width >> 1;
        Dst_Stride_V = Dst_Stride_U;
    }

    libyuv::I420Rotate((const uint8 *) Y_data_Src, src_stride_y,
                       (const uint8 *) U_data_Src, src_stride_u,
                       (const uint8 *) V_data_Src, src_stride_v,
                       (uint8 *) Y_data_Dst, Dst_Stride_Y,
                       (uint8 *) U_data_Dst, Dst_Stride_U,
                       (uint8 *) V_data_Dst, Dst_Stride_V,
                       width, height,
                       (libyuv::RotationMode) degree);
}

void mirrorI420(jbyte *src_i420_data, jint width, jint height, jbyte *dst_i420_data) {
    jint src_i420_y_size = width * height;
    // jint src_i420_u_size = (width >> 1) * (height >> 1);
    jint src_i420_u_size = src_i420_y_size >> 2;

    jbyte *src_i420_y_data = src_i420_data;
    jbyte *src_i420_u_data = src_i420_data + src_i420_y_size;
    jbyte *src_i420_v_data = src_i420_data + src_i420_y_size + src_i420_u_size;

    jbyte *dst_i420_y_data = dst_i420_data;
    jbyte *dst_i420_u_data = dst_i420_data + src_i420_y_size;
    jbyte *dst_i420_v_data = dst_i420_data + src_i420_y_size + src_i420_u_size;

    libyuv::I420Mirror((const uint8 *) src_i420_y_data, width,
                       (const uint8 *) src_i420_u_data, width >> 1,
                       (const uint8 *) src_i420_v_data, width >> 1,
                       (uint8 *) dst_i420_y_data, width,
                       (uint8 *) dst_i420_u_data, width >> 1,
                       (uint8 *) dst_i420_v_data, width >> 1,
                       width, height);
}

void cropI420(jbyte *src_i420_data, jint src_length, jint width, jint height,
				jbyte *dst_i420_data, jint dst_width, jint dst_height, jint left, jint top){
    jint dst_i420_y_size = dst_width * dst_height;
    jint dst_i420_u_size = (dst_width >> 1) * (dst_height >> 1);

    jbyte *dst_i420_y_data = dst_i420_data;
    jbyte *dst_i420_u_data = dst_i420_data + dst_i420_y_size;
    jbyte *dst_i420_v_data = dst_i420_data + dst_i420_y_size + dst_i420_u_size;

    libyuv::ConvertToI420((const uint8 *) src_i420_data, src_length,
                          (uint8 *) dst_i420_y_data, dst_width,
                          (uint8 *) dst_i420_u_data, dst_width >> 1,
                          (uint8 *) dst_i420_v_data, dst_width >> 1,
                          left, top,
                          width, height,
                          dst_width, dst_height,
                          libyuv::kRotate0, libyuv::FOURCC_I420);
}

void nv21ToI420(jbyte *src_nv21_data, jint width, jint height, jbyte *src_i420_data) {
    jint src_y_size = width * height;
    jint src_u_size = (width >> 1) * (height >> 1);

    jbyte *src_nv21_y_data = src_nv21_data;
    jbyte *src_nv21_vu_data = src_nv21_data + src_y_size;

    jbyte *src_i420_y_data = src_i420_data;
    jbyte *src_i420_u_data = src_i420_data + src_y_size;
    jbyte *src_i420_v_data = src_i420_data + src_y_size + src_u_size;


    libyuv::NV21ToI420((const uint8 *) src_nv21_y_data, width,
                       (const uint8 *) src_nv21_vu_data, width,
                       (uint8 *) src_i420_y_data, width,
                       (uint8 *) src_i420_u_data, width >> 1,
                       (uint8 *) src_i420_v_data, width >> 1,
                       width, height);
}

void nv12ToI420(jbyte *Src_data, jint src_width, jint src_height, jbyte *Dst_data) {
	// NV12 video size
	jint NV12_Size = src_width * src_height * 3 / 2;
	jint NV12_Y_Size = src_width * src_height;

	// YUV420 video size
	jint I420_Size = src_width * src_height * 3 / 2;
	jint I420_Y_Size = src_width * src_height;
	jint I420_U_Size = (src_width >> 1)*(src_height >> 1);
	jint I420_V_Size = I420_U_Size;

    // src: buffer address of Y channel and UV channel
    jbyte *Y_data_Src = Src_data;
    jbyte *UV_data_Src = Src_data + NV12_Y_Size;
    jint src_stride_y = src_width;
    jint src_stride_uv = src_width;

    //dst: buffer address of Y channel、U channel and V channel
    jbyte *Y_data_Dst = Dst_data;
    jbyte *U_data_Dst = Dst_data + I420_Y_Size;
    jbyte *V_data_Dst = Dst_data + I420_Y_Size + I420_U_Size;
    jint Dst_Stride_Y = src_width;
    jint Dst_Stride_U = src_width >> 1;
    jint Dst_Stride_V = Dst_Stride_U;

    libyuv::NV12ToI420((const uint8 *) Y_data_Src, src_stride_y,
                         (const uint8 *) UV_data_Src, src_stride_uv,
                         (uint8 *) Y_data_Dst, Dst_Stride_Y,
                         (uint8 *) U_data_Dst, Dst_Stride_U,
                         (uint8 *) V_data_Dst, Dst_Stride_V,
                         src_width, src_height);
}

void i420ToNv12(jbyte *src_i420_data, jint width, jint height, jbyte *src_nv12_data) {
    jint src_y_size = width * height;
    jint src_u_size = (width >> 1) * (height >> 1);

    jbyte *src_nv12_y_data = src_nv12_data;
    jbyte *src_nv12_uv_data = src_nv12_data + src_y_size;

    jbyte *src_i420_y_data = src_i420_data;
    jbyte *src_i420_u_data = src_i420_data + src_y_size;
    jbyte *src_i420_v_data = src_i420_data + src_y_size + src_u_size;


    libyuv::I420ToNV12(
            (const uint8 *) src_i420_y_data, width,
            (const uint8 *) src_i420_u_data, width >> 1,
            (const uint8 *) src_i420_v_data, width >> 1,
            (uint8 *) src_nv12_y_data, width,
            (uint8 *) src_nv12_uv_data, width,
            width, height);
}

void i420ToNv21(jbyte *src_i420_data, jint width, jint height, jbyte *src_nv21_data) {
    jint src_y_size = width * height;
    jint src_u_size = (width >> 1) * (height >> 1);

    jbyte *src_nv21_y_data = src_nv21_data;
    jbyte *src_nv21_uv_data = src_nv21_data + src_y_size;

    jbyte *src_i420_y_data = src_i420_data;
    jbyte *src_i420_u_data = src_i420_data + src_y_size;
    jbyte *src_i420_v_data = src_i420_data + src_y_size + src_u_size;


    libyuv::I420ToNV21(
            (const uint8 *) src_i420_y_data, width,
            (const uint8 *) src_i420_u_data, width >> 1,
            (const uint8 *) src_i420_v_data, width >> 1,
            (uint8 *) src_nv21_y_data, width,
            (uint8 *) src_nv21_uv_data, width,
            width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_libyuv_util_YuvUtil_yuvCompress(JNIEnv *env, jclass type,
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
    nv21ToI420(src_nv21_data, width, height, i420_data);
    tmp_dst_i420_data = i420_data;

    // 镜像
    jbyte *i420_mirror_data = NULL;
    if(isMirror){
        i420_mirror_data = (jbyte *)malloc(sizeof(jbyte) * width * height * 3 / 2);
        mirrorI420(tmp_dst_i420_data, width, height, i420_mirror_data);
        tmp_dst_i420_data = i420_mirror_data;
    }

    // 缩放
    jbyte *i420_scale_data = NULL;
    if(width != dst_width || height != dst_height){
        i420_scale_data = (jbyte *)malloc(sizeof(jbyte) * width * height * 3 / 2);
        scaleI420(tmp_dst_i420_data, width, height, i420_scale_data, dst_width, dst_height, mode);
        tmp_dst_i420_data = i420_scale_data;
        width = dst_width;
        height = dst_height;
    }

    // 旋转
    jbyte *i420_rotate_data = NULL;
    if (degree == libyuv::kRotate90 || degree == libyuv::kRotate180 || degree == libyuv::kRotate270){
        i420_rotate_data = (jbyte *)malloc(sizeof(jbyte) * width * height * 3 / 2);
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
    if(i420_data != NULL) free(i420_data);
    if(i420_mirror_data != NULL) free(i420_mirror_data);
    if(i420_scale_data != NULL) free(i420_scale_data);
    if(i420_rotate_data != NULL) free(i420_rotate_data);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_libyuv_util_YuvUtil_yuvCropI420(JNIEnv *env, jclass type, jbyteArray src_, jint width,
                                     jint height, jbyteArray dst_, jint dst_width, jint dst_height,
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
    cropI420(src_i420_data, src_length, width, height, dst_i420_data, dst_width, dst_height, left, top);
    env->ReleaseByteArrayElements(dst_, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_libyuv_util_YuvUtil_yuvMirrorI420(JNIEnv *env, jclass type, jbyteArray i420Src,
                                          jint width, jint height, jbyteArray i420Dst) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(i420Dst, NULL);
    // i420数据镜像
    mirrorI420(src_i420_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(i420Dst, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_libyuv_util_YuvUtil_yuvScaleI420(JNIEnv *env, jclass type, jbyteArray i420Src,
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
Java_com_libyuv_util_YuvUtil_yuvRotateI420(JNIEnv *env, jclass type, jbyteArray i420Src,
                                           jint width, jint height, jbyteArray i420Dst, jint degree) {
    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(i420Dst, NULL);
    // i420数据旋转
    rotateI420(src_i420_data, width, height, dst_i420_data, degree);
    env->ReleaseByteArrayElements(i420Dst, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_libyuv_util_YuvUtil_yuvNV21ToI420(JNIEnv *env, jclass type, jbyteArray nv21Src,
                                           jint width, jint height, jbyteArray i420Dst) {
    jbyte *src_nv21_data = env->GetByteArrayElements(nv21Src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(i420Dst, NULL);
    // nv21转化为i420
    nv21ToI420(src_nv21_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(i420Dst, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_libyuv_util_YuvUtil_yuvI420ToNV21(JNIEnv *env, jclass type, jbyteArray i420Src,
                                           jint width, jint height, jbyteArray nv21Dst) {

    jbyte *src_i420_data = env->GetByteArrayElements(i420Src, NULL);
    jbyte *dst_nv21_data = env->GetByteArrayElements(nv21Dst, NULL);
    i420ToNv21(src_i420_data, width, height, dst_nv21_data);
    env->ReleaseByteArrayElements(nv21Dst, dst_nv21_data, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_libyuv_util_YuvUtil_yuvNV21ToRGBA(JNIEnv *env, jclass type, jbyteArray nv21Src,
                                           jint width, jint height, jbyteArray argbDst) {

}

void nv21ToRgba(byte[] nv21, int width, int height, int[] rgba) {
    final int frameSize = width * height;
    for (int j = 0, yp = 0; j < height; j++) {
        int uvp = frameSize + (j >> 1) * width, u = 0, v = 0;
        for (int i = 0; i < width; i++, yp++) {
         int y = (0xff & ((int) nv21[yp])) - 16;
         if (y < 0)
             y = 0;
         if ((i & 1) == 0) {
             v = (0xff & nv21[uvp++]) - 128;
             u = (0xff & nv21[uvp++]) - 128;
         }
         int y1192 = 1192 * y;
         int r = (y1192 + 1634 * v);
         int g = (y1192 - 833 * v - 400 * u);
         int b = (y1192 + 2066 * u);

         if (r < 0)
             r = 0;
         else if (r > 262143)
             r = 262143;
         if (g < 0)
             g = 0;
         else if (g > 262143)
             g = 262143;
         if (b < 0)
             b = 0;
         else if (b > 262143)
             b = 262143;

        // 下面为百度到的方法，其实就是r和b变量调换下位置
        rgba[yp] = 0xff000000 | ((b << 6) & 0xff0000)
                 | ((g >> 2) & 0xff00) | ((r >> 10) & 0xff);
        }
    }
}

// int rgbaToI420(JNIEnv * env,jclass clazz,jbyteArray rgba,jint rgba_stride,
//                 jbyteArray yuv,jint y_stride,jint u_stride,jint v_stride,
//                 jint width,jint height,
//                 int (*func)(const uint8 *,int,uint8 *,int,uint8 *,int ,uint8 *,int,int,int)){
//     size_t ySize=(size_t) (y_stride * height);
//     size_t uSize=(size_t) (u_stride * height >> 1);
//     jbyte * rgbaData= env->GetByteArrayElements(rgba,JNI_FALSE);
//     jbyte * yuvData=env->GetByteArrayElements(yuv,JNI_FALSE);
//     int ret=func((const uint8 *) rgbaData, rgba_stride, (uint8 *) yuvData, y_stride,
//                  (uint8 *) (yuvData) + ySize, u_stride, (uint8 *) (yuvData )+ ySize + uSize,
//                  v_stride, width, height);
//     env->ReleaseByteArrayElements(rgba,rgbaData,JNI_OK);
//     env->ReleaseByteArrayElements(yuv,yuvData,JNI_OK);
//     return ret;
// }
// int i420ToRgba(JNIEnv * env,jclass clazz,jbyteArray yuv,jint y_stride,jint u_stride,jint v_stride,
//                 jbyteArray rgba,jint rgba_stride,jint width,jint height,
//                 int (*func)(const uint8 *,int, const uint8 *,int,const uint8 *,int,uint8 *,
//                 int ,int ,int )){
//     size_t ySize=(size_t) (y_stride * height);
//     size_t uSize=(size_t) (u_stride * height >> 1);
//     jbyte * rgbaData= env->GetByteArrayElements(rgba,JNI_FALSE);
//     jbyte * yuvData=env->GetByteArrayElements(yuv,JNI_FALSE);
//     int ret=func((const uint8 *) yuvData, y_stride, (uint8 *) yuvData + ySize, u_stride,
//                  (uint8 *) (yuvData)+ ySize + uSize, v_stride, (uint8 *) (rgbaData),
//                  rgba_stride, width, height);
//     env->ReleaseByteArrayElements(rgba,rgbaData,JNI_OK);
//     env->ReleaseByteArrayElements(yuv,yuvData,JNI_OK);
//     return ret;
// }
