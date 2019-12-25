package com.cy.ffmpegcmd;

import android.os.Bundle;
import android.support.annotation.Nullable;

import com.cy.permission.PermissionActivity;

public abstract class BaseActivity extends PermissionActivity {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }
}
