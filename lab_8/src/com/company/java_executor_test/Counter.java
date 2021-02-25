package com.company.java_executor_test;

import com.company.Main;

import java.util.logging.Level;
import java.util.logging.Logger;

public class Counter {
    private long c1 = 0;
    private long c2 = 0;

    private Object lock1 = new Object();
    private Object lock2 = new Object();


    public void inc1() {
        synchronized (lock1) {
            try {
                c1++;
                Thread.sleep(1);
            } catch (InterruptedException e) {
                Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, e);
            }
        }
    }

    public void inc2() {
        synchronized (lock2) {
            try {
                c2++;
                Thread.sleep(1);
            } catch (InterruptedException e) {
                Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, e);
            }
        }
    }

    public long get_c1() {
        return (c1);
    }

    public long get_c2() {
        return (c2);
    }
}






