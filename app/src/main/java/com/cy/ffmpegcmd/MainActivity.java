package com.cy.ffmpegcmd;

import android.os.Environment;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.cy.ffmpegdemo.R;

public class MainActivity extends BaseActivity {

    // Used to load the 'native-lib' library on application startup.

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        new Thread(new Runnable() {
            @Override
            public void run() {
                checkPermissionWRITE_EXTERNAL_STORAGE(new OnPermissionRequestListener() {
                    @Override
                    public void onPermissionHave() {
                        Log.e("getExternalS", Environment.getExternalStorageDirectory() + "/FFmpegDemo/video.mp4");
                        //先取得读写权限
//                        Log.e("issuccess?", "" + JniUtils.remuxe(Environment.getExternalStorageDirectory() + "/FFmpegDemo/video.mp4",
//                                Environment.getExternalStorageDirectory() + "/FFmpegDemo/video.mkv"));
//                        ffmpeg -i C:\Users\Administrator\Desktop\袋熊.mp4
//                                -i F:\表情包\JB`~O0J_SH{U{VA0U{3%X~I.gif
//-filter_complex "[1:v]scale=300:300[logo];[0:v][logo]overlay=x=0:y=0"
//C:\Users\Administrator\Desktop\filtered_video.mp4
                        JniUtils.runCmd(new CmdCommandList().append("ffmpeg")
                                .append("-i")
                                .append(Environment.getExternalStorageDirectory() +"/FFmpegDemo/video.mp4")
                                .append("-i")
                                .append(Environment.getExternalStorageDirectory() +"/FFmpegDemo/logo.png")
                                .append("-filter_complex")
                                .append("[1:v]scale=300:300[logo];[0:v][logo]overlay=x=0:y=0")
                                .append(Environment.getExternalStorageDirectory() + "/FFmpegDemo/video_filtered.mp4").build());

                    }

                    @Override
                    public void onPermissionRefuse() {

                    }

                    @Override
                    public void onPermissionRefuseNoAsk() {

                    }
                });

            }
        }).start();
    }


    @Override
    public void onClick(View v) {

    }

}
