package com.company.Classes;

public class ObrazThreads extends Thread {
    private Thread thr;
    private Obraz obraz;
    private int first;
    private int last;
    private int i;


    public ObrazThreads(int first, int last, int i, Obraz obraz_1) {
        this.obraz = obraz_1;
        this.first = first;
        this.last = last;
        this.i = i;
    }

    public void run() {
        char[] histogram = new char[94];

        for (int num = first; num < last; ++num) {
            synchronized (obraz) {
                histogram = obraz.go_by_row(num, num + 1);
                int[] temp = obraz.getHistogram();

                for (int k = 0; k < 94; k++) {
                    temp[k] += histogram[k];
                }
                obraz.setHistogram(temp);
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
