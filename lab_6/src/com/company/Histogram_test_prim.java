package com.company;

import com.company.Classes.Obraz;
import com.company.Classes.RunnableWatek;
import java.util.Scanner;


class Histogram_test_prim {

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        System.out.println("Set image size: n (#rows), m(#kolumns)");
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        Obraz obraz_1 = new Obraz(n, m);



        System.out.println("Set number of threads");
        int num_threads = scanner.nextInt();

        Thread[] NewThr = new Thread[num_threads];
        int first, last;



        for (int i = 0; i < num_threads; i++) {
            first = (int)(Math.ceil((float)94/ num_threads) * i);
            last  = (int)(Math.ceil((float)94/ num_threads) * (i+1));
            (NewThr[i] = new Thread (new RunnableWatek(first, last, i, obraz_1))).start();
        }

        for (int i = 0; i < num_threads; i++) {
            try {
                NewThr[i].join();
            } catch (InterruptedException e) {
                System.out.println("Thread interrupted -" + e);
            }
        }

    }

}