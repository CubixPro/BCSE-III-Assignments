import java.io.InterruptedIOException;
import java.util.*;

class Data {
    int q;

    // Permission p;
    Data(int i) {
        q = i;
    }

    int read() {
        return q;
    }

    void write(int x) {
        q = x;
    }
}

class Permission {
    private int cr = 0;
    private int cw = 0;
    private int cwq = 0;

    synchronized public void seekReadPermission() throws InterruptedException {

        if (cw > 0 || cwq > 0) {
            wait();
        }
        cr++;
    }

    synchronized public void seekWritePermission() throws InterruptedException {

        if (cw > 0 ) {
            cwq++;
            wait();
        }
        cw++;
        if (cwq > 0)
            cwq--;

    }

    synchronized public void readOverNotify() {
        cr--;
        notifyAll();
    }

    synchronized public void writeOverNotify() {
        cw--;
        notifyAll();
    }
}

class Reader implements Runnable {
    Data d;
    Permission p;

    Reader(Data d, Permission p) {
        this.d = d;
        this.p = p;
    }

    public void run() {
        int a;
        while (true) {
            try {
                p.seekReadPermission();
                a = d.read();
                System.out.println("Inside Reader class");
                System.out.println(a + " in Thread : " + Thread.currentThread());
                p.readOverNotify();
            } catch (Exception e) {

            }
        }
    }
}

class Writer implements Runnable {
    Data d;
    Permission p;

    Writer(Data d, Permission p) {
        this.d = d;
        this.p = p;
    }

    public void run() {
        while (true) {
            try {
                int a;
                // System.out.println("Enter the new number : ");
                // Scanner sc = new Scanner(System.in);
                // a = sc.nextInt();
                a = (int) (Math.random() * 10);
                p.seekWritePermission();
                System.out.println("Inside Writer changing data to " + a + " Thread : " + Thread.currentThread());
                d.write(a);
                p.writeOverNotify();
            } catch (Exception e) {
            }
        }

    }
}

class Testxxx {
    public static void main(String args[]) throws InterruptedException {
        Data d = new Data(1);
        Permission p = new Permission();
        Reader r = new Reader(d, p);
        Writer w = new Writer(d, p);
        Thread t1 = new Thread(r);
        Thread t3 = new Thread(r);
        Thread t2 = new Thread(w);
        Thread t4 = new Thread(w);
        t2.start();
        t1.start();
        t3.start();
        t4.start();
        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }
}
