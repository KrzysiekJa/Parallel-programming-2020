package com.company.Classes;

public class RunnableWatek implements Runnable {
    private Thread thr;
    private Obraz obraz;
    private int first;
    private int last;
    private int i;


    public RunnableWatek(int first, int last, int i, Obraz obraz_1) {
        this.obraz = obraz_1;
        this.first = first;
        this.last = last;
        this.i = i;
    }

    public void run() {

        for (int num = first; num < last; ++num) {
            int result = obraz.calculate_search(num);
            synchronized (obraz) {
                System.out.print("Watek " + i + ": ");
                obraz.sign_searching(num, result);
            }
        }
    }

    public void start() {
        if (thr == null) {
            thr = new Thread(this);
            thr.start();
        }
    }
}
