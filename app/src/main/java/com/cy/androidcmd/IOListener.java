package com.cy.androidcmd;
public interface IOListener<T> {
    public void onCompleted(T result);
    public void onLoding(T readedPart, long current, long length);
    public void onInterrupted();
    public void onFail(String errorMsg);
}