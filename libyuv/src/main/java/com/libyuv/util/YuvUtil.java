package com.libyuv.util;

/**
 * @创建者 LQR
 * @时间 2019/10/17
 * @描述 请叫我百米冲刺
 */
public class YuvUtil {

    static {
        System.loadLibrary("yuvutil");
    }

    /**
     * YUV数据的基本的处理（nv21-->i420-->mirror-->scale-->rotate）
     *
     * @param nv21Src    原始数据
     * @param width      原始的宽
     * @param height     原始的高
     * @param dst_width  缩放的宽
     * @param i420Dst    目标数据
     * @param dst_height 缩放的高
     * @param mode       压缩模式。这里为0，1，2，3 速度由快到慢，质量由低到高，一般用0就好了，因为0的速度最快
     * @param degree     旋转的角度，90，180和270三种。切记，如果角度是90或270，则最终i420Dst数据的宽高会调换。
     * @param isMirror   是否镜像，一般只有270的时候才需要镜像
     */
    public static native void yuvCompress(byte[] nv21Src, int width, int height, byte[] i420Dst, int dst_width, int dst_height, int mode, int degree, boolean isMirror);

    /**
     * yuv数据的裁剪操作
     *
     * @param i420Src    原始数据
     * @param width      原始的宽
     * @param height     原始的高
     * @param i420Dst    输出数据
     * @param dst_width  输出的宽
     * @param dst_height 输出的高
     * @param left       裁剪的x的开始位置，必须为偶数，否则显示会有问题
     * @param top        裁剪的y的开始位置，必须为偶数，否则显示会有问题
     **/
    public static native void yuvCropI420(byte[] i420Src, int width, int height, byte[] i420Dst, int dst_width, int dst_height, int left, int top);

    /**
     * yuv数据的镜像操作
     *
     * @param i420Src i420原始数据
     * @param width
     * @param height
     * @param i420Dst i420目标数据
     */
    @Deprecated
    public static native void yuvMirrorI420(byte[] i420Src, int width, int height, byte[] i420Dst);

    /**
     * yuv数据的缩放操作
     *
     * @param i420Src   i420原始数据
     * @param width     原始宽度
     * @param height    原始高度
     * @param i420Dst   i420目标数据
     * @param dstWidth  目标宽度
     * @param dstHeight 目标高度
     * @param mode      压缩模式 ，0~3，质量由低到高，一般传入0
     */
    public static native void yuvScaleI420(byte[] i420Src, int width, int height, byte[] i420Dst, int dstWidth, int dstHeight, int mode);

    /**
     * yuv数据的旋转操作
     *
     * @param i420Src i420原始数据
     * @param width
     * @param height
     * @param i420Dst i420目标数据
     * @param degree  旋转角度
     */
    public static native void yuvRotateI420(byte[] i420Src, int width, int height, byte[] i420Dst, int degree);

    /**
     * 将NV21转化为I420
     *
     * @param nv21Src 原始I420数据
     * @param width   原始的宽
     * @param width   原始的高
     * @param i420Dst 转化后的NV21数据
     */
    public static native void yuvNV21ToI420(byte[] nv21Src, int width, int height, byte[] i420Dst);

    /**
     * 将I420转化为NV21
     *
     * @param i420Src 原始I420数据
     * @param width   原始的宽
     * @param width   原始的高
     * @param nv21Dst 转化后的NV21数据
     **/
    public static native void yuvI420ToNV21(byte[] i420Src, int width, int height, byte[] nv21Dst);

    /**
     * 将NV21转化为I420，同时可旋转
     *
     * @param nv21Src 原始NV21数据
     * @param width   原始的宽
     * @param height  原始的高
     * @param i420Dst 转化后的I420数据
     * @param degree  旋转角度：0、90、180、270
     */
    public static native void yuvNV21ToI420AndRotate(byte[] nv21Src, int width, int height, byte[] i420Dst, int degree);

    /**
     * 将I420转化为RGB24
     *
     * @param i420Src  原始I420数据
     * @param width    原始的宽
     * @param height   原始的高
     * @param rgb24Dst 转化后的RGB24数据
     */
    public static native void yuvI420ToRGB24(byte[] i420Src, int width, int height, byte[] rgb24Dst);

    /**
     * 将I420转化为ARGB
     *
     * @param i420Src    原始I420数据
     * @param width      原始的宽
     * @param height     原始的高
     * @param dst_stride 跨距，可传入0或width
     * @param argbDst    转化后的ARGB数据
     */
    public static native void yuvI420ToARGB(byte[] i420Src, int width, int height, int dst_stride, byte[] argbDst);

    /**
     * 将I420转化为RGBA
     *
     * @param i420Src    原始I420数据
     * @param width      原始的宽
     * @param height     原始的高
     * @param dst_stride 跨距，可传入0或width
     * @param rgbaMacDst 转化后的RGBA数据
     */
    public static native void yuvI420ToRGBAMac(byte[] i420Src, int width, int height, int dst_stride, byte[] rgbaMacDst);

    /**
     * 将I420转化为ARGB4444
     *
     * @param i420Src     原始I420数据
     * @param width       原始的宽
     * @param height      原始的高
     * @param dst_stride  跨距，可传入0或width
     * @param argb4444Dst 转化后的ARGB4444数据
     */
    public static native void yuvI420ToARGB4444(byte[] i420Src, int width, int height, int dst_stride, byte[] argb4444Dst);

    /**
     * 将I420转化为RGB565
     *
     * @param i420Src   原始I420数据
     * @param width     原始的宽
     * @param height    原始的高
     * @param rgb565Dst 转化后的RGB565数据
     */
    public static native void yuvI420ToRGB565(byte[] i420Src, int width, int height, byte[] rgb565Dst);

    /**
     * 将I420转化为RGB565
     *
     * @param i420Src   原始I420数据
     * @param width     原始的宽
     * @param height    原始的高
     * @param rgb565Dst 转化后的RGB565数据
     */
    public static native void yuvI420ToRGB565Android(byte[] i420Src, int width, int height, byte[] rgb565Dst);

    /**
     * 将I420转化为ARGB1555
     *
     * @param i420Src     原始I420数据
     * @param width       原始的宽
     * @param height      原始的高
     * @param dst_stride  跨距，可传入0或width
     * @param argb1555Dst 转化后的ARGB1555数据
     */
    public static native void yuvI420ToARGB1555(byte[] i420Src, int width, int height, int dst_stride, byte[] argb1555Dst);

    /**
     * 将I420转化为YUY2
     *
     * @param i420Src    原始I420数据
     * @param width      原始的宽
     * @param height     原始的高
     * @param dst_stride 跨距，可传入0或width
     * @param yuy2Dst    转化后的YUY2数据
     */
    public static native void yuvI420ToYUY2(byte[] i420Src, int width, int height, int dst_stride, byte[] yuy2Dst);

    /**
     * 将I420转化为UYVY
     *
     * @param i420Src    原始I420数据
     * @param width      原始的宽
     * @param height     原始的高
     * @param dst_stride 跨距，可传入0或width
     * @param uyvyDst    转化后的UYVY数据
     */
    public static native void yuvI420ToUYVY(byte[] i420Src, int width, int height, int dst_stride, byte[] uyvyDst);

    /**
     * 将I420转化为YV12
     *
     * @param i420Src    原始I420数据
     * @param width      原始的宽
     * @param height     原始的高
     * @param dst_stride 跨距，可传入0或width
     * @param yv12Dst    转化后的YV12数据
     */
    public static native void yuvI420ToYV12(byte[] i420Src, int width, int height, int dst_stride, byte[] yv12Dst);

    /**
     * 将YV12转化为I420
     *
     * @param yv12Src 原始YV12数据
     * @param width   原始的宽
     * @param height  原始的高
     * @param i420Dst 转化后的I420数据
     */
    public static native void yuvYV12ToI420(byte[] yv12Src, int width, int height, byte[] i420Dst);

    /**
     * 将NV12转化为I420
     *
     * @param nv12Src 原始NV12数据
     * @param width   原始的宽
     * @param height  原始的高
     * @param i420Dst 转化后的I420数据
     */
    public static native void yuvNV12ToI420(byte[] nv12Src, int width, int height, byte[] i420Dst);

    /**
     * 将I420转化为NV12
     *
     * @param i420Src 原始I420数据
     * @param width   原始的宽
     * @param height  原始的高
     * @param nv12Dst 转化后的NV12数据
     */
    public static native void yuvI420ToNv12(byte[] i420Src, int width, int height, byte[] nv12Dst);

    /**
     * 将I420转化为NV12，同时可以旋转
     *
     * @param nv12Src 原始NV12数据
     * @param width   原始的宽
     * @param height  原始的高
     * @param i420Dst 转化后的I420数据
     * @param degree  旋转角度
     */
    public static native void yuvNV12ToI420AndRotate(byte[] nv12Src, int width, int height, byte[] i420Dst, int degree);

    /**
     * 将NV12转化为RGB565
     *
     * @param nv12Src   原始NV12数据
     * @param width     原始的宽
     * @param height    原始的高
     * @param rgb565Dst 转化后的RGB565数据
     */
    public static native void yuvNV12ToRGB565(byte[] nv12Src, int width, int height, byte[] rgb565Dst);

    /**
     * 将I420转化为RGBA
     *
     * @param i420Src    原始I420数据
     * @param width      原始的宽
     * @param height     原始的高
     * @param dst_stride 跨距，可传入0或width
     * @param rgbaDst    转化后的RGBA数据
     */
    public static native void yuvI420ToRGBAIPhone(byte[] i420Src, int width, int height, int dst_stride, byte[] rgbaDst);

    /**
     * 将I420复制一份
     *
     * @param i420Src    原始I420数据
     * @param width      原始的宽
     * @param height     原始的高
     * @param dst_stride 跨距，可传入0或width
     * @param i420Dst    转化后的I420数据
     */
    public static native void yuvI420Copy(byte[] i420Src, int width, int height, int dst_stride, byte[] i420Dst);

    /**
     * 将UYVY转化为I420
     *
     * @param uyvySrc 原始UYVY数据
     * @param width   原始的宽
     * @param height  原始的高
     * @param i420Dst 转化后的I420数据
     */
    public static native void yuvUYVYToI420(byte[] uyvySrc, int width, int height, byte[] i420Dst);

    /**
     * 将YUY2转化为I420
     *
     * @param yuy2Src 原始YUY2数据
     * @param width   原始的宽
     * @param height  原始的高
     * @param i420Dst 转化后的I420数据
     */
    public static native void yuvYUY2ToI420(byte[] yuy2Src, int width, int height, byte[] i420Dst);

    /**
     * 将RGB24转化为ARGB
     *
     * @param rgb24Src   原始RGB24数据
     * @param width      原始的宽
     * @param height     原始的高
     * @param dst_stride 跨距，可传入0或width
     * @param argbDst    转化后的ARGB数据
     */
    public static native void yuvRGB24ToARGB(byte[] rgb24Src, int width, int height, int dst_stride, byte[] argbDst);

    /**
     * c
     *
     * @param rgb24Src 原始RGB24数据
     * @param width    原始的宽
     * @param height   原始的高
     * @param i420Dst  转化后的I420数据
     */
    public static native void yuvRGB24ToI420(byte[] rgb24Src, int width, int height, byte[] i420Dst);

    /**
     * 将I420转化为ARGB
     *
     * @param i420Src    原始I420数据
     * @param width      原始的宽
     * @param height     原始的高
     * @param dst_stride 跨距，可传入0或width
     * @param argbMacDst 转化后的ARGB数据
     */
    public static native void yuvI420ToARGBMac(byte[] i420Src, int width, int height, int dst_stride, byte[] argbMacDst);

    /**
     * 将ARGB转化为I420
     *
     * @param argbMacSrc 原始ARGB数据
     * @param width      原始的宽
     * @param height     原始的高
     * @param i420Dst    转化后的I420数据
     */
    public static native void yuvARGBMacToI420(byte[] argbMacSrc, int width, int height, byte[] i420Dst);

    /**
     * 将I420左右镜像
     *
     * @param i420Src 原始I420数据
     * @param width   原始的宽
     * @param height  原始的高
     * @param i420Dst 转化后的I420数据
     */
    public static native void yuvMirrorI420LeftRight(byte[] i420Src, int width, int height, byte[] i420Dst);

    /**
     * 将I420上下镜像
     *
     * @param i420Src 原始I420数据
     * @param width   原始的宽
     * @param height  原始的高
     * @param i420Dst 转化后的I420数据
     */
    public static native void yuvMirrorI420UpDown(byte[] i420Src, int width, int height, byte[] i420Dst);
}
