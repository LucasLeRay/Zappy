#
# Socket.py
#

# Imports
import socket

# Globals
debug = False

# Class Socket
class Socket:

	# Init
	def __init__(self, host, port):
		self.socket = None
		self.host = host
		self.port = port

	# Connect
	def connect(self):
		self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		try:
			self.socket.connect((self.host, self.port))
		except Exception as e:
			print("socket: {}".format(e))
			return (-1)
		return (0)

	# Disconnect
	def disconnect(self):
		self.socket.close()

	# Send Message
	def send_msg(self, msg):
		if debug:
			print("msg : " + msg)
		self.socket.send(str.encode(msg + "\n"))

	# Receive Message
	def rcv_msg(self):
		#return (self.socket.recv(512))
		msg = self.socket.recv(2048).decode()
		if debug:
			print("rcv : " + msg, end="")
		return (msg)
