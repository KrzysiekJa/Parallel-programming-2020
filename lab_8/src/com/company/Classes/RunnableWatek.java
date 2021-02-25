package com.company.Classes;

import java.util.concurrent.Callable;

public class RunnableWatek implements Callable<Integer> {
    private Thread thr;
    private Obraz obraz;
    private int i;

    public RunnableWatek(int i, Obraz obraz_1) {
        this.obraz = obraz_1;
        this.i = i;
    }

    public int compute() {
        int result = this.obraz.calculate_search(i);

        return result;
    }

    public Integer call() {
        return compute();
    }
}
