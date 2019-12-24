package com.cy.androidcmd;

public class JniUtils {
    private JniUtils() {
    }

    static {
        System.loadLibrary("native-lib");
    }

    public static native boolean remuxe(String inPath, String outPath);

    public static native void runCmd(String[] commands);

    private void onSuccess() {
    }

    private void onProgress(int hour,int min,int secs,int totalSecs) {
    }
    private void onFail(){

    }
}
