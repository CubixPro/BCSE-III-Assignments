;


#########################################################
#########################################################

class Caller:
    def __init__(self, name, callerToReceiver, receiverToCaller):
        self.name               = name
        self.callerToReceiver   = callerToReceiver # pipes for sending msgs
        self.receiverToCaller   = receiverToCaller # pipes for receiving msgs

    def sendMsgToReceiver(self):
        while True:
            
            print("Enter exit to end the conversation!")
            msg = input("Enter your msg: ")
            if msg == "exit": sys.exit("(End of conversation:) Byeeeeeee!")
            self.callerToReceiver.send(msg)
            msg = self.receiverToCaller.recv()
            print("-----------------------------------------------")
            print("(Reseponse from Receiver:)\n" + msg)
    

    def start(self):

        t = threading.Thread(name="Caller", target=self.sendMsgToReceiver)
        t.start()
        t.join()

###########################################################
###########################################################

class Receiver:

    def __init__(self, name, callerToReceiver, receiverToCaller):
        self.name               = name
        self.callerToReceiver   = callerToReceiver
        self.receiverToCaller   = receiverToCaller
    
    def receiveMsgFromCaller(self):
        while True:
            msg = self.callerToReceiver.recv()
            print("-----------------------------------------------")
            print("Msg from Caller: \n"+ msg)
            print("-----------------------------------------------")
            msg = input("Enter your msg to Caller: ")
            self.receiverToCaller.send(msg)
    
    def start(self):
        t = threading.Thread(name="Receiver", target=self.receiveMsgFromCaller)
        t.start()
        t.join()

###########################################################
###########################################################

def start():
    rHofCallerToReceiver, wHofCallerToReceiver = Pipe()
    rHofReceiverToCaller, wHofReceiverToCaller = Pipe()

    caller = Caller("Caller", wHofCallerToReceiver, rHofReceiverToCaller)
    receiver = Receiver("Receiver", rHofCallerToReceiver, wHofReceiverToCaller)

    thread1 = threading.Thread(name="Caller", target=caller.start)
    thread2 = threading.Thread(name="Receiver", target=receiver.start)

    thread1.start()
    thread2.start()

    thread1.join()
    thread2.join()

if __name__ == "__main__":
    start()