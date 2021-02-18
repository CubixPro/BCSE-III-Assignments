import java.nio.channels.Pipe;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;
import java.nio.ByteBuffer;
import java.io.*;

class Stats {
    ArrayList<Integer> attempRecord;
    int failedCount, successCount;

    Stats() {
        this.attempRecord = new ArrayList<>();
        this.failedCount = 0;
        this.successCount = 0;
    }
}

class Channel {
    Pipe.SinkChannel sink;
    Pipe.SourceChannel source;
    Boolean idle;
    Boolean collision;
    Pipe pipe;

    Channel() throws IOException {
        this.pipe = Pipe.open();
        this.sink = this.pipe.sink();
        this.source = this.pipe.source();
        this.idle = true;
        this.collision = false;
    }

}

class Sender extends Thread {
    ByteBuffer buffer;
    Channel channel;
    String filename;
    String sendAddr;
    String recvAddr;
    Stats stats;
    int kMax;
    int tp;
    int tt;
    int sleep;

    Sender(Channel channel, String filename, String sendAddr, String recvAddr, Stats stats) {
        this.channel = channel;
        this.stats = stats;
        this.buffer = ByteBuffer.allocate(2048);
        this.filename = filename;
        this.sendAddr = sendAddr;
        this.recvAddr = recvAddr;
        this.kMax = 15;
        this.tt = 6;
        this.tp = 10 + (new Random()).nextInt(4);
        this.sleep = 20 + (new Random()).nextInt(5);
    }

    public void run() {
        int c = 0;
        while (true) {
            Boolean restart = false;
            try {
                try {
                    Thread.sleep((new Random().nextInt(5)));
                } catch (Exception e) {
                }
                if (c == 0)
                    System.out.println(this.sendAddr + " started!!!");
                else
                    System.out.println(this.sendAddr + " restarted!!!");

                FileReader fr = new FileReader("input/" + this.filename);
                while (true) {
                    String text = "";
                    int count = 0, i;

                    // Frame processing
                    try {
                        while ((i = fr.read()) != -1 && count < 46) {
                            text = text + (char) i;
                            count++;
                        }
                    } catch (Exception e) {
                    }
                    String data = EthernetFrame.MakeEthernetFrame(text, this.recvAddr, this.sendAddr);
                    this.buffer.clear();
                    this.buffer.put(data.getBytes());

                    Boolean sent = false;
                    int sendRequestCount = 0;
                    while (!sent && sendRequestCount < this.kMax) {
                        sendRequestCount++;

                        // check until idle
                        while (this.channel.idle == false) {
                            try {
                                Thread.sleep(10 + (new Random()).nextInt(10));
                            } catch (Exception e) {
                            }
                        }
                        // frame processing
                        try {
                            Thread.sleep((new Random()).nextInt(3));
                        } catch (Exception e) {
                        }

                        if (this.channel.idle) {
                            this.channel.idle = false;
                            try {
                                Thread.sleep(this.tt);
                            } catch (Exception e) {
                            }
                            if (this.channel.collision == false) {
                                try {
                                    Thread.sleep(this.tp);
                                } catch (Exception e) {
                                }
                                try {
                                    this.buffer.flip();
                                    while (this.buffer.hasRemaining()) {
                                        this.channel.sink.write(this.buffer);
                                    }
                                    this.buffer.flip();
                                    this.stats.attempRecord.add(sendRequestCount);
                                    this.stats.successCount++;
                                } catch (Exception e) {
                                }
                                this.channel.collision = false;
                                sent = true;
                                this.channel.idle = true;
                            } else {
                                this.channel.idle = true;
                                this.channel.collision = false;
                                try {
                                    Thread.sleep(this.sleep);
                                } catch (Exception e) {
                                }
                            }
                        }
                        // collison found
                        else {
                            this.channel.collision = true;
                            try {
                                Thread.sleep(this.sleep);
                            } catch (Exception e) {
                            }
                        }
                    }
                    if (sendRequestCount >= this.kMax) {
                        this.stats.failedCount++;
                        restart = true;
                    }
                    if (count < 46) {
                        break;
                    }
                }
                try {
                    fr.close();
                } catch (Exception e) {
                }
            } catch (Exception e) {
            }
            if (!restart) {
                break;
            }
            c = 1;
        }
        try {
            Thread.sleep(10);
            System.out.println(this.sendAddr + " -> sending complete !!!");
        } catch (Exception e) {
        }
    }
}

class Reciever extends Thread {
    ByteBuffer buffer;
    Channel channel;

    Reciever(Channel channel) {
        this.channel = channel;
        this.buffer = ByteBuffer.allocate(2048);
    }

    public void run() {
        try {
            while (this.channel.source.read(this.buffer) > 0) {
                // System.out.println("Got data!!!");
                this.buffer.flip();
                String curr = "";
                while (this.buffer.hasRemaining()) {
                    curr = curr + (char) this.buffer.get();
                }
                try {
                    String destAddr = EthernetFrame.getDestAddr(curr);
                    String sendAddr = EthernetFrame.getSendAddr(curr);
                    String data = EthernetFrame.getData(curr);

                    // System.out.print(destAddr + " -> ");
                    // System.out.println(data);

                    BufferedWriter out = new BufferedWriter(
                            new FileWriter("output/" + destAddr + "_" + sendAddr + ".txt", true));
                    out.write(data);
                    out.close();
                } catch (IOException e) {
                }
                this.buffer.clear();
            }
        } catch (Exception e) {
        }
    }
}

public class Simulator_non_persistent {
    public static void main(String[] args) throws IOException {
        Channel channel = new Channel();
        Stats stats = new Stats();
        new Reciever(channel).start();

        new Sender(channel, "input.txt", "Sendr1", "Recvr1", stats).start();
        new Sender(channel, "input.txt", "Sendr2", "Recvr2", stats).start();
        new Sender(channel, "input.txt", "Sendr3", "Recvr3", stats).start();
        new Sender(channel, "input.txt", "Sendr4", "Recvr4", stats).start();
        new Sender(channel, "input.txt", "Sendr5", "Recvr5", stats).start();
        new Sender(channel, "input.txt", "Sendr6", "Recvr6", stats).start();
        new Sender(channel, "input.txt", "Sendr7", "Recvr7", stats).start();
        new Sender(channel, "input.txt", "Sendr8", "Recvr8", stats).start();
        new Sender(channel, "input.txt", "Sendr9", "Recvr9", stats).start();
        new Sender(channel, "input.txt", "Sendr0", "Recvr0", stats).start();

        new Thread() {
            public void run() {
                while (Thread.activeCount() != 3) {
                    try {
                        Thread.sleep(100);
                    } catch (Exception e) {
                    }
                }
                System.out.println(
                        "                                              <- <- <- <- <- <- <- stats -> -> -> -> -> -> ->");
                System.out.println("Attempts for every successful transmission -> " + stats.attempRecord);
                System.out.println("Backoff attempts -> " + stats.failedCount);
                System.exit(0);
            }
        }.start();
    }
}
