import java.util.*;

class WalshTable {
    int[][] wtable;
    int noOfStation;

    WalshTable(int noOfStation) {
        this.noOfStation = noOfStation;
        this.wtable = new int[noOfStation][noOfStation];
        this.buildWalshTable(this.noOfStation, 0, this.noOfStation - 1, 0, this.noOfStation - 1, false);
    }

    void printWalshTable() {
        System.out.println("WalshTable " + this.noOfStation + " * " + this.noOfStation);
        for (int i = 0; i < this.noOfStation; i++) {
            for (int j = 0; j < this.noOfStation; j++) {
                System.out.print(this.wtable[i][j] + " ");
            }
            System.out.println();
        }
    }

    public void buildWalshTable(int len, int i1, int i2, int j1, int j2, boolean isBar) {
        if (len == 2) {
            if (!isBar) {
                this.wtable[i1][j1] = 1;
                this.wtable[i1][j2] = 1;
                this.wtable[i2][j1] = 1;
                this.wtable[i2][j2] = -1;
            } else {
                this.wtable[i1][j1] = -1;
                this.wtable[i1][j2] = -1;
                this.wtable[i2][j1] = -1;
                this.wtable[i2][j2] = +1;
            }
            return;
        }
        int midi = (i1 + i2) / 2;
        int midj = (j1 + j2) / 2;
        this.buildWalshTable(len / 2, i1, midi, j1, midj, isBar);
        this.buildWalshTable(len / 2, i1, midi, midj + 1, j2, isBar);
        this.buildWalshTable(len / 2, midi + 1, i2, j1, midj, isBar);
        this.buildWalshTable(len / 2, midi + 1, i2, midj + 1, j2, !isBar);
        return;
    }
}

public class Simulator_cdma {
    public static int nearestPower(int noOfStation) {
        int x = 1;
        while (true) {
            if (noOfStation <= x)
                return x;
            else
                x *= 2;
        }
    }

    public static int[][] encodeSequence(String senderString[], int noOfStation, int WalshTableSize, WalshTable walsh) {
        int sequence[][] = new int[senderString[0].length()][WalshTableSize];
        for (int idx = 0; idx < senderString[0].length(); idx++) {
            int[] temp = new int[WalshTableSize];
            for (int i = 0; i < WalshTableSize; i++) {
                temp[i] = 0;
                for (int j = 0; j < noOfStation; j++) {
                    if (senderString[j].charAt(idx) == '1')
                        temp[i] += walsh.wtable[j][i];
                    else
                        temp[i] -= walsh.wtable[j][i];
                }
            }
            sequence[idx] = temp;
        }
        return sequence;
    }

    public static String[] decodeSequence(int[][] seq, int noOfStation, int WalshTableSize, WalshTable walsh) {
        String receiverData[] = new String[noOfStation];
        for (int i = 0; i < noOfStation; i++) {
            receiverData[i] = "";
        }
        for (int idx = 0; idx < seq.length; idx++) {
            for (int i = 0; i < noOfStation; i++) {
                int temp = 0;
                for (int j = 0; j < WalshTableSize; j++) {
                    temp += walsh.wtable[i][j] * seq[idx][j];
                }
                temp /= WalshTableSize;
                if (temp == 1) {
                    receiverData[i] += "1";
                } else {
                    receiverData[i] += "0";
                }
            }
        }
        return receiverData;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter number of senders-> ");
        int noOfStation = Integer.parseInt(sc.nextLine());

        int WalshTableSize = Simulator_cdma.nearestPower(noOfStation);
        WalshTable walsh = new WalshTable(WalshTableSize);

        String senderData[] = new String[WalshTableSize];
        for (int i = 0; i < noOfStation; i++) {
            String s = "HELLO I AM WITH SENDER AND I BRING DATA OF ->" + String.valueOf(i);
            System.out.println("SNDR " + i + " RCVR " + i + " -> " + s);
            senderData[i] = EthernetFrame.MakeEthernetFrame(s, "SNDR " + String.valueOf(i),
                    "RCVR " + String.valueOf(i));
        }

        long start = System.nanoTime();
        int seq[][] = Simulator_cdma.encodeSequence(senderData, noOfStation, WalshTableSize, walsh);
        String receiverData[] = Simulator_cdma.decodeSequence(seq, noOfStation, WalshTableSize, walsh);
        long end = System.nanoTime();

        for (int i = 0; i < noOfStation; i++) {
            String sender = EthernetFrame.getSendAddr(receiverData[i]);
            String receiver = EthernetFrame.getDestAddr(receiverData[i]);
            String data = EthernetFrame.getData(receiverData[i]);
            System.out.println("SNDR " + sender + " " + receiver + " " + " -> " + data);
        }

        long timeTaken = end - start;
        System.out.println();
        System.out.println();
        System.out.println();
        System.out.println("   <- <- <- <-   Stats   -> -> -> ->");
        System.out.println("No. of Senders -> " + noOfStation);
        System.out.println("Number of bits transferred -> " + (73 * 8 * noOfStation));
        System.out.println("Time Taken -> " + timeTaken + " nano sec");
        sc.close();
    }
}
