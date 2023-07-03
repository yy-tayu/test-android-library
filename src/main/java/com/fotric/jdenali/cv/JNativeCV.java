package com.fotric.jdenali.cv;

import com.fotric.jdenali.bean.JImage;
import com.fotric.jdenali.bean.JRect;

public class JNativeCV {
    public static final int COLOR_BGR2BGRA = 0;
    public static final int COLOR_YUV2RGB_UYVY = 107;
    public static final int COLOR_YUV2BGRA_UYVY = 112;

    static {
        System.loadLibrary("jnativecv");
    }

    public native boolean openUYVYFileToRGBA(String filePath, String filename, int width, int height,JImage ret);
    public native boolean openUYVYFile(String filePath, String filename, int width, int height, JImage ret);
    public native void convertUYVYStreamToRGBA(JImage src, JImage dest,JRect rect);
    public native void convertColorSpace(JImage src, JImage dest, int type);
    public native void cutImage(JImage src, JImage dest, JRect rect);
    public native void resize(JImage src, JImage dest);
    public native boolean blendImages(JImage image1, float alpha1, JImage image2, float alpha2, JImage dest);
    public native void cvSaveImages(JImage image1, String filePath, String fileName);
    public native void ofstreamSaveImages(JImage image, String filePath, String fileName);
    public native void encodeSaveImages(JImage image, String filePath, String fileName);
}
