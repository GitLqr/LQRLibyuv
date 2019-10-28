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
     * @param nv21Src 转化后的NV21数据
     **/
    public static native void yuvI420ToNV21(byte[] i420Src, int width, int height, byte[] nv21Src);
}
