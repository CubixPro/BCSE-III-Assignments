public class EthernetFrame {

    // preamble(7) + sfd(1) + dest(6) + send(6) + len(2) + data(46) + crc(4) =
    // frame(72)

    public static String charToByte(String data) {
        String res = "";
        for (int i = 0; i < data.length(); i++) {
            String curr = Integer.toBinaryString((int) data.charAt(i));
            while (curr.length() != 8) {
                curr = '0' + curr;
            }
            res = res + curr;
        }
        return res;
    }

    public static String ByteToChar(String data) {
        String res = "";
        for (int i = 0; i < data.length(); i += 8) {
            res = res + (char) Integer.parseInt(data.substring(i, i + 8), 2);
        }
        return res;
    }

    public static String div(String data, String gen) {
        int pointer = gen.length();
        String result = data.substring(0, pointer);
        String remainder = "";
        for (int i = 0; i < gen.length(); i++) {
            if (result.charAt(i) == gen.charAt(i))
                remainder += "0";
            else
                remainder += "1";
        }
        while (pointer < data.length()) {
            if (remainder.charAt(0) == '0') {
                remainder = remainder.substring(1, remainder.length());
                remainder = remainder + String.valueOf(data.charAt(pointer));
                pointer++;
            }
            result = remainder;
            remainder = "";
            for (int i = 0; i < gen.length(); i++) {
                if (result.charAt(i) == gen.charAt(i))
                    remainder += "0";
                else
                    remainder += "1";
            }
        }
        return remainder.substring(1, remainder.length());
    }

    public static String genCrc(String data) {
        String outputCodeWord = new String(data);
        // used Generator Polynomial CRC-32-802.3
        String generator = new String("100000100110000010001110110110111");
        while (outputCodeWord.length() < (data.length() + generator.length() - 1)) {
            outputCodeWord = outputCodeWord + "0";
        }
        String rem = EthernetFrame.div(outputCodeWord, generator);
        return rem;
    }

    public static String MakeEthernetFrame(String data, String destAddr, String sendAddr) {
        String preamble;
        String sfd;
        String len;
        String crc;
        String frame;
        String sendAdd;
        String destAdd;
        // preamble
        preamble = "";
        for (int i = 0; i < 56; i++) {
            if (i % 2 == 0) {
                preamble = preamble + '0';
            } else {
                preamble = preamble + '1';
            }
        }

        // sfd
        sfd = "10101011";

        // sendAddr
        sendAdd = EthernetFrame.charToByte(sendAddr.substring(0, 6));

        // destAddr
        destAdd = EthernetFrame.charToByte(destAddr.substring(0, 6));

        // len
        len = Integer.toBinaryString(72 * 8);
        while (len.length() < 16) {
            len = '0' + len;
        }

        // data
        data = EthernetFrame.charToByte(data);
        while (data.length() < 46 * 8) {
            data = '0' + data;
        }

        // crc
        frame = destAdd + sendAdd + len + data;
        crc = EthernetFrame.genCrc(frame);
        frame = preamble + sfd + frame;
        return frame + crc;
    }

    public static String getData(String frame) {
        return EthernetFrame.ByteToChar(frame.substring(176, 176 + 46 * 8));
    }

    public static String getDestAddr(String frame) {
        return EthernetFrame.ByteToChar(frame.substring(64, 64 + 48));
    }

    public static String getSendAddr(String frame) {
        return EthernetFrame.ByteToChar(frame.substring(112, 160));
    }

    public static Boolean isErrorFree(String frame) {
        String frameCrc = frame.substring(544, 544 + 32);
        String currCrc = EthernetFrame.genCrc(frame.substring(64, 544));
        if (frameCrc.equals(currCrc))
            return true;
        else
            return false;
    }
}
