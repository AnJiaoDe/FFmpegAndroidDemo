package com.cy.ffmpegcmd;

import java.util.concurrent.ConcurrentHashMap;

public class JniUtils {
    private ConcurrentHashMap<Integer, CmdCallback> map_cmdCallback = new ConcurrentHashMap<>();

    static {
        System.loadLibrary("ffmpegcmd");
    }

    private JniUtils() {
    }

    private static class JniUtilsFactory {
        private static JniUtils instance = new JniUtils();
    }

    public static JniUtils getInstance() {
        return JniUtilsFactory.instance;
    }

    public void cmdAsync(final String[] commands, CmdCallback cmdCallback) {
        final int index = map_cmdCallback.size() > 0 ? map_cmdCallback.size() - 1 : 0;
        map_cmdCallback.put(index, cmdCallback);
        runCmd(index, commands);
    }

    private static native void runCmd(int index, String[] commands);

    private static native void cancelCmd(int index);

    private void onProgress(int index, int hour, int min, int secs, int totalSecs) {

        LogUtils.log("onProgress", hour + ":" + min + ":" + secs + "__________" + totalSecs);
    }

    private void onFail(int index) {
        LogUtils.log("onFail");
        map_cmdCallback.remove(index);
    }

    private void onSuccess(int index) {
        LogUtils.log("onSuccess");
        map_cmdCallback.remove(index);
    }
}
