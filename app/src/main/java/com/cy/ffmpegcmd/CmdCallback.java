package com.cy.ffmpegcmd;

public abstract class CmdCallback {
    private long id_thread;

    public long getId_thread() {
        return id_thread;
    }

    public void setId_thread(long id_thread) {
        this.id_thread = id_thread;
    }

    public abstract void onProgress(int hour, int min, int secs, int totalSecs);
    public abstract void onSuccess();
    public abstract void onFail();
    public abstract void onCancel();
}
