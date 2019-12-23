package com.cy.androidcmd;

import java.util.ArrayList;
public class CmdCommandList extends ArrayList<String> {

    /**
     * 清除命令集合
     */
    public void clear() {
        this.clear();
    }

    public CmdCommandList append(String s) {
        this.add(s);
        return this;
    }

    public String[] build() {
        String[] command = new String[this.size()];
        for (int i = 0; i < this.size(); i++) {
            command[i] = this.get(i);
        }
        return command;
    }

}
