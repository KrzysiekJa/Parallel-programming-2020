package com.company;

import com.company.Classes.Obraz;
import com.company.Classes.RunnableWatek;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.*;

class Histogram_test_prim {
    Histogram_test_prim() {
    }

    private static final int NTHREADS = 4;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Set image size: n (#rows), m(#kolumns)");
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        Obraz obraz_1 = new Obraz(n, m);



        ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);
        List<Future<Integer>> list = new ArrayList<>();

        for (int i = 0; i < 94; i++) {
            Callable<Integer> worker = new RunnableWatek(i, obraz_1);
            Future<Integer> future = executor.submit(worker);
            list.add(future);
            try{
                Thread.sleep(1);
            }catch (InterruptedException exception){
                System.err.println("ERROR: " + exception);
            }
        }

        for(int i = 0; i < 94; i++) {
            try {
                int result = list.get(i).get();
                synchronized (obraz_1) {
                    obraz_1.sign_searching(i, result);
                }
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
        }


        // This will make the executor accept no new threads
        // and finish all existing threads in the queue
        executor.shutdown();

        // Wait until all threads finish
        while (!executor.isTerminated()) {
        }


    }
}
