package com.cy.ffmpegcmd;

import java.util.concurrent.ConcurrentHashMap;

public class JniUtils {
    private static ConcurrentHashMap<Integer, CmdCallback> map_cmdCallback = new ConcurrentHashMap<>();

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

    public int cmdAsync(final String[] commands, CmdCallback cmdCallback) {
        final int index = map_cmdCallback.size() > 0 ? map_cmdCallback.size() - 1 : 0;
        map_cmdCallback.put(index, cmdCallback);
        cmdCallback.setId_thread(runCmd(index, commands));
        return index;
    }

    public void cancel(int index) {
        CmdCallback cmdCallback = map_cmdCallback.get(index);
        if (cmdCallback != null) {
            cancelCmd(cmdCallback.getId_thread());
            cmdCallback.onCancel();
            map_cmdCallback.remove(index);
        }
    }
    public void cancelAll() {
        for(Integer index:map_cmdCallback.keySet()){
            CmdCallback cmdCallback = map_cmdCallback.get(index);
            if (cmdCallback != null) {
                cancelCmd(cmdCallback.getId_thread());
                cmdCallback.onCancel();
            }
        }
        map_cmdCallback.clear();
    }

    private static native long runCmd(int index, String[] commands);

    private static native void cancelCmd(long id_thread);

    private static void onProgress(int index, int hour, int min, int secs, long totalSecs) {
        CmdCallback cmdCallback = map_cmdCallback.get(index);
        if (cmdCallback != null) cmdCallback.onProgress(hour, min, secs, totalSecs);
        LogUtils.log("onProgress", hour + ":" + min + ":" + secs + "__________" + totalSecs);
    }

    private static void onFail(int index) {
        LogUtils.log("onFail");
        CmdCallback cmdCallback = map_cmdCallback.get(index);
        if (cmdCallback != null) {
            cmdCallback.onFail();
            map_cmdCallback.remove(index);
        }
    }

    private void onCancel(int index) {
        LogUtils.log("onFail");
        CmdCallback cmdCallback = map_cmdCallback.get(index);
        if (cmdCallback != null) {
            cmdCallback.onCancel();
            map_cmdCallback.remove(index);
        }
    }

    private void onSuccess(int index) {
        LogUtils.log("onSuccess");
        CmdCallback cmdCallback = map_cmdCallback.get(index);
        if (cmdCallback != null) {
            cmdCallback.onSuccess();
            map_cmdCallback.remove(index);
        }
    }
}
