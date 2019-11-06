#include "YuvConvert.h"

//void NV21ToRGBA(jbyte *nv21, jint width, jint height, jbyte *rgba) {
//    jint frameSize = width * height;
//    for (jint j = 0, yp = 0; j < height; j++) {
//        jint uvp = frameSize + (j >> 1) * width, u = 0, v = 0;
//        for (jint i = 0; i < width; i++, yp++) {
//            jint y = (0xff & ((jint) nv21[yp])) - 16;
//            if (y < 0)
//                y = 0;
//            if ((i & 1) == 0) {
//                v = (0xff & nv21[uvp++]) - 128;
//                u = (0xff & nv21[uvp++]) - 128;
//            }
//            jint y1192 = 1192 * y;
//            jint r = (y1192 + 1634 * v);
//            jint g = (y1192 - 833 * v - 400 * u);
//            jint b = (y1192 + 2066 * u);
//
//            if (r < 0)
//                r = 0;
//            else if (r > 262143)
//                r = 262143;
//            if (g < 0)
//                g = 0;
//            else if (g > 262143)
//                g = 262143;
//            if (b < 0)
//                b = 0;
//            else if (b > 262143)
//                b = 262143;
//
//            // 下面为百度到的方法，其实就是r和b变量调换下位置
//            rgba[yp] = 0xff000000 | ((b << 6) & 0xff0000)
//                       | ((g >> 2) & 0xff00) | ((r >> 10) & 0xff);
//        }
//    }
//}

// jint RGBAToI420(JNIEnv * env,jclass clazz,jbyteArray rgba,jint rgba_stride,
//                 jbyteArray yuv,jint y_stride,jint u_stride,jint v_stride,
//                 jint width,jint height,
//                 jint (*func)(const uint8 *,jint,uint8 *,jint,uint8 *,jint ,uint8 *,jint,jint,jint)){
//     size_t ySize=(size_t) (y_stride * height);
//     size_t uSize=(size_t) (u_stride * height >> 1);
//     jbyte * rgbaData= env->GetByteArrayElements(rgba,JNI_FALSE);
//     jbyte * yuvData=env->GetByteArrayElements(yuv,JNI_FALSE);
//     jint ret=func((const uint8 *) rgbaData, rgba_stride, (uint8 *) yuvData, y_stride,
//                  (uint8 *) (yuvData) + ySize, u_stride, (uint8 *) (yuvData )+ ySize + uSize,
//                  v_stride, width, height);
//     env->ReleaseByteArrayElements(rgba,rgbaData,JNI_OK);
//     env->ReleaseByteArrayElements(yuv,yuvData,JNI_OK);
//     return ret;
// }
// jint i420ToRgba(JNIEnv * env,jclass clazz,jbyteArray yuv,jint y_stride,jint u_stride,jint v_stride,
//                 jbyteArray rgba,jint rgba_stride,jint width,jint height,
//                 jint (*func)(const uint8 *,jint, const uint8 *,jint,const uint8 *,jint,uint8 *,
//                 jint ,jint ,jint )){
//     size_t ySize=(size_t) (y_stride * height);
//     size_t uSize=(size_t) (u_stride * height >> 1);
//     jbyte * rgbaData= env->GetByteArrayElements(rgba,JNI_FALSE);
//     jbyte * yuvData=env->GetByteArrayElements(yuv,JNI_FALSE);
//     jint ret=func((const uint8 *) yuvData, y_stride, (uint8 *) yuvData + ySize, u_stride,
//                  (uint8 *) (yuvData)+ ySize + uSize, v_stride, (uint8 *) (rgbaData),
//                  rgba_stride, width, height);
//     env->ReleaseByteArrayElements(rgba,rgbaData,JNI_OK);
//     env->ReleaseByteArrayElements(yuv,yuvData,JNI_OK);
//     return ret;
// }


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
    } else {
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

void RotateI420fff(jbyte *src_i420_data, jint width, jint height,
                   jbyte *dst_i420_data, jint degree) {
    jint I420_Y_Size = width * height;
    jint I420_U_Size = (width >> 1) * (height >> 1);
    jint I420_V_Size = I420_U_Size;

    // src: buffer address of  Y channel、U channel and V channel
    jbyte *Y_data_Src = src_i420_data;
    jbyte *U_data_Src = src_i420_data + I420_Y_Size;
    jbyte *V_data_Src = src_i420_data + I420_Y_Size + I420_U_Size;
    jint src_stride_y = width;
    jint src_stride_u = width >> 1;
    jint src_stride_v = src_stride_u;

    //dst: buffer address of Y channel、U channel and V channel
    jbyte *Y_data_Dst = dst_i420_data;
    jbyte *U_data_Dst = dst_i420_data + I420_Y_Size;
    jbyte *V_data_Dst = dst_i420_data + I420_Y_Size + I420_U_Size;
    jint Dst_Stride_Y;
    jint Dst_Stride_U;
    jint Dst_Stride_V;
    if (degree == libyuv::kRotate90 || degree == libyuv::kRotate270) {
        Dst_Stride_Y = height;
        Dst_Stride_U = height >> 1;
        Dst_Stride_V = Dst_Stride_U;
    } else {
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

void MirrorI420(jbyte *src_i420_data, jint width, jint height, jbyte *dst_i420_data) {
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

void CropI420(jbyte *src_i420_data, jint src_length, jint width, jint height,
              jbyte *dst_i420_data, jint dst_width, jint dst_height, jint left, jint top) {
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

//void NV21ToI420(jbyte *src_nv21_data, jint width, jint height, jbyte *src_i420_data) {
//    jint src_y_size = width * height;
//    jint src_u_size = (width >> 1) * (height >> 1);
//
//    jbyte *src_nv21_y_data = src_nv21_data;
//    jbyte *src_nv21_vu_data = src_nv21_data + src_y_size;
//
//    jbyte *src_i420_y_data = src_i420_data;
//    jbyte *src_i420_u_data = src_i420_data + src_y_size;
//    jbyte *src_i420_v_data = src_i420_data + src_y_size + src_u_size;
//
//
//    libyuv::NV21ToI420((const uint8 *) src_nv21_y_data, width,
//                       (const uint8 *) src_nv21_vu_data, width,
//                       (uint8 *) src_i420_y_data, width,
//                       (uint8 *) src_i420_u_data, width >> 1,
//                       (uint8 *) src_i420_v_data, width >> 1,
//                       width, height);
//}

//void NV12ToI420(jbyte *Src_data, jint src_width, jint src_height, jbyte *Dst_data) {
//    // NV12 video size
//    jint NV12_Size = src_width * src_height * 3 / 2;
//    jint NV12_Y_Size = src_width * src_height;
//
//    // YUV420 video size
//    jint I420_Size = src_width * src_height * 3 / 2;
//    jint I420_Y_Size = src_width * src_height;
//    jint I420_U_Size = (src_width >> 1) * (src_height >> 1);
//    jint I420_V_Size = I420_U_Size;
//
//    // src: buffer address of Y channel and UV channel
//    jbyte *Y_data_Src = Src_data;
//    jbyte *UV_data_Src = Src_data + NV12_Y_Size;
//    jint src_stride_y = src_width;
//    jint src_stride_uv = src_width;
//
//    //dst: buffer address of Y channel、U channel and V channel
//    jbyte *Y_data_Dst = Dst_data;
//    jbyte *U_data_Dst = Dst_data + I420_Y_Size;
//    jbyte *V_data_Dst = Dst_data + I420_Y_Size + I420_U_Size;
//    jint Dst_Stride_Y = src_width;
//    jint Dst_Stride_U = src_width >> 1;
//    jint Dst_Stride_V = Dst_Stride_U;
//
//    libyuv::NV12ToI420((const uint8 *) Y_data_Src, src_stride_y,
//                       (const uint8 *) UV_data_Src, src_stride_uv,
//                       (uint8 *) Y_data_Dst, Dst_Stride_Y,
//                       (uint8 *) U_data_Dst, Dst_Stride_U,
//                       (uint8 *) V_data_Dst, Dst_Stride_V,
//                       src_width, src_height);
//}

void I420ToNv12(jbyte *src_i420_data, jint width, jint height, jbyte *src_nv12_data) {
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

void I420ToRGB24(jbyte *src_i420_data, jint width, jint height, jbyte *dst_rgb24_data) {

    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);

    libyuv::I420ToRGB24(
            (const uint8 *) yplane, width,
            (const uint8 *) uplane, width / 2,
            (const uint8 *) vplane, width / 2,
            (uint8 *) dst_rgb24_data, width * 3,
            width, height);
}

void I420ToARGB(jbyte *src_i420_data, jint width, jint height,
                jint dst_stride, jbyte *dst_argb_data) {

    if (dst_stride == 0 || dst_stride == width)
        dst_stride = width * 4;
    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);

    libyuv::I420ToARGB(
            (const uint8_t *) yplane, width,
            (const uint8_t *) uplane, width / 2,
            (const uint8_t *) vplane, width / 2,
            (uint8_t *) dst_argb_data, dst_stride,
            width, height);
}

void I420ToRGBAMac(jbyte *src_i420_data, jint width, jint height, jint dst_stride,
                   jbyte *dst_rgba_mac_data) {
    // Equivalent to Convert YV12ToBGRA.
    // YV12 same as I420 with U and V swapped.
    if (dst_stride == 0 || dst_stride == width) dst_stride = 4 * width;
    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    libyuv::I420ToBGRA(
            (const uint8_t *) yplane, width,
            (const uint8_t *) vplane, width / 2,
            (const uint8_t *) uplane, width / 2,
            (uint8_t *) dst_rgba_mac_data, dst_stride,
            width, height);
}

void I420ToARGB4444(jbyte *src_i420_data, jint width, jint height, jint dst_stride,
                    jbyte *dst_argb4444_data) {
    if (dst_stride == 0 || dst_stride == width)
        dst_stride = 2 * width;
    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    libyuv::I420ToARGB4444(
            (const uint8_t *) yplane, width,
            (const uint8_t *) uplane, width / 2,
            (const uint8_t *) vplane, width / 2,
            (uint8_t *) dst_argb4444_data, dst_stride,
            width, height);
}

void I420ToRGB565(jbyte *src_i420_data, jint width, jint height, jbyte *dst_rgb565_data) {
    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    libyuv::I420ToRGB565(
            (const uint8_t *) yplane, width,
            (const uint8_t *) uplane, width / 2,
            (const uint8_t *) vplane, width / 2,
            (uint8_t *) dst_rgb565_data, width,
            width, height);
}

void I420ToRGB565Android(jbyte *src_i420_data, jint width, jint height, jbyte *dst_rgb565_data) {
    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    // Same as RGB565 + inversion - set negative height.
    height = -height;
    libyuv::I420ToRGB565(
            (const uint8_t *) yplane, width,
            (const uint8_t *) uplane, width / 2,
            (const uint8_t *) vplane, width / 2,
            (uint8_t *) dst_rgb565_data, width,
            width, height);
}

void I420ToARGB1555(jbyte *src_i420_data, jint width, jint height, jint dst_stride,
                    jbyte *dst_argb1555_data) {
    if (dst_stride == 0 || dst_stride == width)
        dst_stride = 2 * width;
    else if (dst_stride < 2 * width)
        return;
    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    libyuv::I420ToARGB1555(
            (const uint8_t *) yplane, width,
            (const uint8_t *) uplane, width / 2,
            (const uint8_t *) vplane, width / 2,
            (uint8_t *) dst_argb1555_data, dst_stride,
            width, height);
}

void I420ToYUY2(jbyte *src_i420_data, jint width, jint height,
                jint dst_stride, jbyte *dst_yuy2_data) {
    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    if (dst_stride == 0 || dst_stride == width)
        dst_stride = 2 * width;
    libyuv::I420ToYUY2(
            (const uint8_t *) yplane, width,
            (const uint8_t *) uplane, width / 2,
            (const uint8_t *) vplane, width / 2,
            (uint8_t *) dst_yuy2_data, dst_stride,
            width, height);
}

void I420ToUYVY(jbyte *src_i420_data, jint width, jint height,
                jint dst_stride, jbyte *dst_uyvy_data) {
    if (dst_stride == 0 || dst_stride == width)
        dst_stride = 2 * width;
    else if (dst_stride < width)
        return;
    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    libyuv::I420ToUYVY(
            (const uint8_t *) yplane, width,
            (const uint8_t *) uplane, width / 2,
            (const uint8_t *) vplane, width / 2,
            (uint8_t *) dst_uyvy_data, dst_stride,
            width, height);
}

void I420ToYV12(jbyte *src_i420_data, jint width, jint height,
                jint dst_stride, jbyte *dst_yv12_data) {
    if (dst_stride == 0 || dst_stride == width)
        dst_stride = width;
    else if (dst_stride < width)
        return;
    jbyte *src_yplane = src_i420_data;
    jbyte *src_uplane = src_i420_data + width * height;
    jbyte *src_vplane = src_uplane + (width * height / 4);
    jbyte *dst_yplane = dst_yv12_data;
    jbyte *dst_uplane = dst_yv12_data + width * height;

    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    // YV12 is YVU => Use I420(YUV) copy and flip U and V.
    libyuv::I420Copy((const uint8_t *) src_yplane, width,
                     (const uint8_t *) src_vplane, width / 2,
                     (const uint8_t *) src_uplane, width / 2,
                     (uint8_t *) dst_yplane, dst_stride,
                     (uint8_t *) dst_uplane, dst_stride / 2,
                     (uint8_t *) dst_vplane, dst_stride / 2,
                     width, height);
}

void YV12ToI420(jbyte *src_yv12_data, jint width, jint height, jbyte *dst_i420_data) {
    jbyte *src_yplane = src_yv12_data;
    jbyte *src_uplane = src_yv12_data + width * height;
    jbyte *src_vplane = src_uplane + (width * height / 4);
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    // YV12 is YVU => Use I420(YUV) copy and flip U and V.
    libyuv::I420Copy(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_vplane, width / 2,
            (const uint8_t *) src_uplane, width / 2,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_uplane, width / 2,
            (uint8_t *) dst_vplane, width / 2,
            width, height);
}

void NV12ToI420(jbyte *src_nv21_data, jint width, jint height, jbyte *dst_i420_data) {
    jbyte *src_yplane = src_nv21_data;
    jbyte *src_uvplane = src_nv21_data + width * height;
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::NV12ToI420(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uvplane, width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_uplane, width / 2,
            (uint8_t *) dst_vplane, width / 2,
            width, height);
}

void I420ToNv21(jbyte *src_i420_data, jint width, jint height, jbyte *src_nv21_data) {
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

void NV12ToI420AndRotate180(jbyte *src_nv12_data, jint width, jint height, jbyte *dst_i420_data) {
    jbyte *src_yplane = src_nv12_data;
    jbyte *src_uvplane = src_nv12_data + width * height;
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::NV12ToI420Rotate(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uvplane, width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_uplane, width / 2,
            (uint8_t *) dst_vplane, width / 2,
            width, height,
            libyuv::kRotate180);
}

void NV12ToI420AndRotateClockwise(jbyte *src_nv12_data, jint width, jint height,
                                  jbyte *dst_i420_data) {
    jbyte *src_yplane = src_nv12_data;
    jbyte *src_uvplane = src_nv12_data + width * height;
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::NV12ToI420Rotate(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uvplane, width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_uplane, width / 2,
            (uint8_t *) dst_vplane, width / 2,
            width, height,
            libyuv::kRotate90);
}

void NV12ToI420AndRotateAntiClockwise(jbyte *src_nv12_data, jint width, jint height,
                                      jbyte *dst_i420_data) {
    jbyte *src_yplane = src_nv12_data;
    jbyte *src_uvplane = src_nv12_data + width * height;
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::NV12ToI420Rotate(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uvplane, width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_uplane, width / 2,
            (uint8_t *) dst_vplane, width / 2,
            width, height,
            libyuv::kRotate270);
}

void NV12ToRGB565(jbyte *src_nv12_data, jint width, jint height, jbyte *dst_rgb565_data) {
    jbyte *yplane = src_nv12_data;
    jbyte *uvInterlaced = src_nv12_data + (width * height);
    libyuv::NV12ToRGB565(
            (const uint8_t *) yplane, width,
            (const uint8_t *) uvInterlaced, width / 2,
            (uint8_t *) dst_rgb565_data, width,
            width, height);
}

void NV21ToI420(jbyte *src_nv21_data, jint width, jint height, jbyte *dst_i420_data) {
    // NV21 = y plane followed by an interleaved V/U plane, i.e. same as NV12
    // but the U and the V are switched. Use the NV12 function and switch the U
    // and V planes.
    jbyte *src_yplane = src_nv21_data;
    jbyte *src_uvplane = src_nv21_data + width * height;
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::NV12ToI420(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uvplane, width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_vplane, width / 2,
            (uint8_t *) dst_uplane, width / 2,
            width, height);
}

void NV21ToI420AndRotate180(jbyte *src_nv21_data, jint width, jint height, jbyte *dst_i420_data) {
    jbyte *src_yplane = src_nv21_data;
    jbyte *src_uvplane = src_nv21_data + width * height;
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::NV12ToI420Rotate(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uvplane, width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_vplane, width / 2,
            (uint8_t *) dst_uplane, width / 2,
            width, height,
            libyuv::kRotate180);
}

void NV21ToI420AndRotateClockwise(jbyte *src_nv21_data, jint width,
                                  jint height, jbyte *dst_i420_data) {
    jbyte *src_yplane = src_nv21_data;
    jbyte *src_uvplane = src_nv21_data + width * height;
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::NV12ToI420Rotate(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uvplane, width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_vplane, width / 2,
            (uint8_t *) dst_uplane, width / 2,
            width, height,
            libyuv::kRotate90);
}

void NV21ToI420AndRotateAntiClockwise(jbyte *src_nv21_data, jint width,
                                      jint height, jbyte *dst_i420_data) {
    jbyte *src_yplane = src_nv21_data;
    jbyte *src_uvplane = src_nv21_data + width * height;
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::NV12ToI420Rotate(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uvplane, width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_vplane, width / 2,
            (uint8_t *) dst_uplane, width / 2,
            width, height,
            libyuv::kRotate270);
}

void I420ToRGBAIPhone(jbyte *src_i420_data, jint width, jint height,
                      jint dst_stride, jbyte *dst_rgba_data) {
    if (dst_stride == 0 || dst_stride == width)
        dst_stride = 4 * width;
    else if (dst_stride < 4 * width)
        return;
    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    // RGBAIPhone = ABGR
    libyuv::I420ToABGR(
            (const uint8_t *) yplane, width,
            (const uint8_t *) uplane, width / 2,
            (const uint8_t *) vplane, width / 2,
            (uint8_t *) dst_rgba_data, dst_stride,
            width, height);
}

void I420Copy(jbyte *src_i420_data, jint width, jint height,
              jint dst_stride, jbyte *dst_i420_data) {

    if (dst_stride == 0)
        dst_stride = width;
    jbyte *src_yplane = src_i420_data;
    jbyte *src_uplane = src_i420_data + width * height;
    jbyte *src_vplane = src_uplane + (width * height / 4);
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::I420Copy(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uplane, width / 2,
            (const uint8_t *) src_vplane, width / 2,
            (uint8_t *) dst_yplane, dst_stride,
            (uint8_t *) dst_uplane, dst_stride / 2,
            (uint8_t *) dst_vplane, dst_stride / 2,
            width, height);
}

void UYVYToI420(jbyte *src_uyvy_data, jint width, jint height, jbyte *dst_i420_data) {
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::UYVYToI420(
            (const uint8_t *) src_uyvy_data, 2 * width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_uplane, width / 2,
            (uint8_t *) dst_vplane, width / 2,
            width, height);
}

void YUY2ToI420(jbyte *src_yuy2_data, jint width, jint height, jbyte *dst_i420_data) {
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::YUY2ToI420(
            (const uint8_t *) src_yuy2_data, 2 * width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_uplane, width / 2,
            (uint8_t *) dst_vplane, width / 2,
            width, height);
}

void RGB24ToARGB(jbyte *src_rbg24_data, jint width, jint height,
                 jint dst_stride, jbyte *dst_argb_data) {
    if (dst_stride == 0 || dst_stride == width)
        dst_stride = width;
    // Stride - currently webrtc style
    libyuv::RGB24ToARGB(
            (const uint8_t *) src_rbg24_data, width,
            (uint8_t *) dst_argb_data, dst_stride,
            width, height);
}

void RGB24ToI420(jbyte *src_rbg24_data, jint width, jint height, jbyte *dst_i420_data) {
    jbyte *yplane = dst_i420_data;
    jbyte *uplane = yplane + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    // WebRtc expects a vertical flipped image.
    libyuv::RGB24ToI420(
            (const uint8_t *) src_rbg24_data, width * 3,
            (uint8_t *) yplane, width,
            (uint8_t *) uplane, width / 2,
            (uint8_t *) vplane, width / 2,
            width, -height);
}

void I420ToARGBMac(jbyte *src_i420_data, jint width, jint height,
                   jint dst_stride, jbyte *dst_argb_mac_data) {
    // Equivalent to YV12ToARGB.
    // YV12 = YVU => use I420 and interchange U and V.
    jbyte *yplane = src_i420_data;
    jbyte *uplane = yplane + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    if (dst_stride == 0 || dst_stride == width)
        dst_stride = 4 * width;
    else if (dst_stride < 4 * width)
        return;
    libyuv::I420ToARGB(
            (const uint8_t *) yplane, width,
            (const uint8_t *) vplane, width / 2,
            (const uint8_t *) uplane, width / 2,
            (uint8_t *) dst_argb_mac_data, dst_stride,
            width, height);
}

void ARGBMacToI420(jbyte *src_argb_mac_data, jint width, jint height, jbyte *dst_i420_data) {
    // Equivalent to BGRAToI420
    jbyte *yplane = dst_i420_data;
    jbyte *uplane = yplane + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    libyuv::BGRAToI420(
            (const uint8_t *) src_argb_mac_data, width * 4,
            (uint8_t *) yplane, width,
            (uint8_t *) uplane, width / 2,
            (uint8_t *) vplane, width / 2,
            width, height);
}

void MirrorI420LeftRight(jbyte *src_i420_data, jint width, jint height, jbyte *dst_i420_data) {
    jbyte *src_yplane = src_i420_data;
    jbyte *src_uplane = src_yplane + width * height;
    jbyte *src_vplane = src_uplane + (width * height / 4);
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_yplane + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::I420Mirror(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uplane, width / 2,
            (const uint8_t *) src_vplane, width / 2,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_uplane, width / 2,
            (uint8_t *) dst_vplane, width / 2,
            width, height);
}

void MirrorI420UpDown(jbyte *src_i420_data, jint width, jint height, jbyte *dst_i420_data) {
    jbyte *src_yplane = src_i420_data;
    jbyte *src_uplane = src_i420_data + width * height;
    jbyte *src_vplane = src_uplane + (width * height / 4);
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);

    // Inserting negative height flips the frame.
    libyuv::I420Copy(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uplane, width / 2,
            (const uint8_t *) src_vplane, width / 2,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_uplane, width / 2,
            (uint8_t *) dst_vplane, width / 2,
            width, -height);
}
