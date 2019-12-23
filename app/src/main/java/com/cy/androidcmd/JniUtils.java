package com.cy.androidcmd;

public class JniUtils {
    private JniUtils() {
    }

    static {
        System.loadLibrary("native-lib");
    }

    public static native boolean remuxe(String inPath, String outPath);

    public static native void runCmd(String[] commands);

    private void onFinish(int ret) {
//        if (sOnCmdExecListener != null)
//        {
//            if (ret == 0)
//            {
//                sOnCmdExecListener.onProgress(sDuration);
//                sOnCmdExecListener.onSuccess();
//            }
//            else
//            {
//                sOnCmdExecListener.onFailure();
//            }
//        }
    }

    private void onProgress(int hour,int min,int secs,int totalSecs) {
//        if (sOnCmdExecListener != null)
//        {
//            if (sDuration != 0)
//            {
//                sOnCmdExecListener.onProgress(progress / (sDuration / 1000) * 0.95f);
//            }
//        }
    }
    private void onFailed(String msg){

    }
}
