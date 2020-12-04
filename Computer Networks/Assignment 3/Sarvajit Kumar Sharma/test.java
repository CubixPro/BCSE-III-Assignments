public class test {
    public static void main(String[] args) {
        String frame = EthernetFrame.MakeEthernetFrame("Good Boi", "123456", "789012");
        System.out.println(EthernetFrame.getData(frame));
        System.out.println(EthernetFrame.getDestAddr(frame));
    }
}
