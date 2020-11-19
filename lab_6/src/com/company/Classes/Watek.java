package com.company.Classes;

public class Watek extends Thread {
    private Thread thr;
    private Obraz obraz;
    private int num;


    public Watek(int i, Obraz obraz_1) {
        this.obraz = obraz_1;
        this.num = i;
    }

    public void run() {
        int result = obraz.calculate_search(num);
        synchronized (obraz) {
            System.out.print("Watek " + num + ": ");
            obraz.sign_searching(num, result);
        }
    }

    public void start() {
        if (thr == null) {
            thr = new Thread(this);
            thr.start();
        }
    }
}
