import sys
sys.path.append('../package')
import helper
from packet import *


def fileRead(filename):
	file = open(filename, 'r')
	byte = file.read(36)
	packet = Packet(1,1,byte,1,1).makePacket()
	#print(packet)
	#git print(len(packet.packet))
	print(packet.checkForError())
	file.close()


if __name__ == "__main__":
	fileRead('input0.txt')