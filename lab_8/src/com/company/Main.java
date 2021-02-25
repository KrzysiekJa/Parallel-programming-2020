package com.company;

import com.company.Classes.Calka_callable;

import java.util.concurrent.FutureTask;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Main {

    public static void main(String[] args) {
        Double result;
        Calka_callable integral = new Calka_callable(0, Math.PI, 0.01);

        try{
            FutureTask<Double> future = new FutureTask<>(integral);
            Thread thr = new Thread(future);
            thr.start();
            result = future.get();
            System.out.println("Result: " + result);
            integral.call();
        }catch (Exception exception){
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, exception);
        }
    }
}
