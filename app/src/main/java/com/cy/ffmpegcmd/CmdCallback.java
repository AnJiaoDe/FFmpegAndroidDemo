package com.cy.ffmpegcmd;

public interface CmdCallback {
    public void onProgress(int hour, int min, int secs, int totalSecs);
    public void onFail();
    public void onSuccess();
}
