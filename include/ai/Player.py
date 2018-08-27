#
# Player.py
#

# Imports
from include.ai.Socket import Socket
from random import randint
from enum import Enum

# Rules
vision = [(0, 0), (1, 3), (4, 8), (9, 15), (16, 24), (25, 36), (37, 51), (52, 69), (70, 90)]
stones = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]
need_members = [0, 1, 2, 2, 4, 4, 6, 6]
max_stuff = {
	"linemate": 9,
	"deraumere": 8,
	"sibur": 10,
	"mendiane": 5,
	"phiras": 6,
	"thystame": 1
}
need_stones = [{},
	{
		"linemate": 1,
		"deraumere": 0,
		"sibur": 0,
		"mendiane": 0,
		"phiras": 0,
		"thystame": 0
	},
	{
		"linemate": 1,
		"deraumere": 1,
		"sibur": 1,
		"mendiane": 0,
		"phiras": 0,
		"thystame": 0
	},
	{
		"linemate": 2,
		"deraumere": 0,
		"sibur": 1,
		"mendiane": 0,
		"phiras": 2,
		"thystame": 0
	},
	{
		"linemate": 1,
		"deraumere": 1,
		"sibur": 2,
		"mendiane": 0,
		"phiras": 1,
		"thystame": 0
	},
	{
		"linemate": 1,
		"deraumere": 2,
		"sibur": 1,
		"mendiane": 3,
		"phiras": 0,
		"thystame": 0
	},
	{
		"linemate": 1,
		"deraumere": 2,
		"sibur": 3,
		"mendiane": 0,
		"phiras": 1,
		"thystame": 0
	},
	{
		"linemate": 2,
		"deraumere": 2,
		"sibur": 2,
		"mendiane": 2,
		"phiras": 2,
		"thystame": 1
	}
]
turn = 0

# Macros
LEVEL_MAX = 8
MIN_FOOD = 120

ACTIVE = True
PASSIVE = False

CONTINUE = 0
QUIT = 1

### Functions
# My Range
def my_range(a, b):
	if a < b:
		return (range(a, b))
	return (range(b, a))

# Swap
def swap(vector):
	tmp = vector.x
	vector.x = vector.y
	vector.y = tmp
	return (vector)

# Same Sign
def same_sign(a, b):
	if a < 0 and b < 0:
		return (True)
	elif a > 0 and b > 0:
		return (True)
	elif a == 0 and b == 0:
		return (True)
	return (False)

# Class Pos
class Pos:
	x = 0
	y = 0

# Class Player
class Player:

	# Init
	def __init__(self):
		self.socket = None
		self.stuff = {
			"food": 1200,
			"linemate": 0,
			"deraumere": 0,
			"sibur": 0,
			"mendiane": 0,
			"phiras": 0,
			"thystame": 0
		}
		self.msg_functions = {
			"ready": self.msg_ready,
			"start": self.msg_start,
			"zone": self.msg_zone
		}
		self.dispo_members = [0] * (LEVEL_MAX + 1)
		self.team_name = ""
		self.last_look = ""
		self.level = 1
		self.zone_id = 0
		self.is_ready = False
		self.is_joining = False

	### Network Method
	# Connect
	def connect(self, infos):
		self.socket = Socket(infos["host"], int(infos["port"]))
		return (self.socket.connect())

	# Send Message
	def send_msg(self, msg):
		self.socket.send_msg(msg)

	# Receive Message
	def rcv_msg(self):
		return (self.socket.rcv_msg())

	### Preliminaries Methods
	# Preliminaries
	def preliminaries(self):
		self.rcv_msg()
		self.send_msg(self.team_name)
		self.rcv_msg()
		self.rcv_msg()

	##### AI Methods
	### Level 3
	# Need Object
	def need_object(self, object):
		if object == "":
			return (False)
		if object == "food" or self.stuff[object] < max_stuff[object]:
			return (True)
		return (False)

	### Level 2
	# Take Everything
	def take_everything(self):
		seen = self.look()

		for object in seen.split(",")[0].split(" "):
			if object == "player":
				continue
			if self.need_object(object):
				self.take_object(object)

	# Have Seen Stone
	def have_seen_stones(self, missing):
		infos = {
			"found": False,
			"case": 0
		}

		for stone in missing:
			for case in self.last_look.split(","):
				for object in case.split(" "):
					if object == stone:
						infos["found"] = True
						return (infos)
				infos["case"] += 1
		return (infos)

	# Go To Case
	def go_to_case(self, case):
		dest = Pos()
		i = 0

		for step in vision:
			if min(step) <= case <= max(step):
				dest.y = i
				dest.x = case - (max(step) - int((max(step) - min(step)) / 2))
				break
			i += 1
		if dest.x < 0:
			self.left()
		elif dest.x > 0:
			self.right()
		for i in my_range(0, dest.x):
			self.forward()
		if dest.x < 0:
			self.right()
		elif dest.x > 0:
			self.left()
		for i in my_range(0, dest.y):
			self.forward()

	# Enough Are Ready
	def enough_are_ready(self):
		print("dispo : " + str(self.dispo_members[self.level]) + " | need : " + str(need_members[self.level]))
		if self.dispo_members[self.level] == need_members[self.level] - 1:
			return (True)
		return (False)

	# Start Gathering
	def start_gathering(self):
		nb_call = 0

		print("Start Gathering")
		if self.level == 1:
			self.start_incantation(ACTIVE)
			return (0)
		self.zone_id = randint(1000, 3000)
		self.broadcast("start:" + str(self.level) + "-" + str(self.zone_id))
		while self.not_enough_player() and nb_call < 20:
			self.broadcast("zone:" + str(self.zone_id))
			print(">> zone:" + str(self.zone_id))
			self.left()
			print("wait")
		self.zone_id = 0
		if nb_call < 20:
			self.start_incantation(ACTIVE)

	### Level 1
	# Begin
	def begin(self):
		#self.fork()
		self.take_everything()

	# Get Missing Stones
	def get_missing_stones(self):
		missing = []

		for stone in stones:
			if need_stones[self.level][stone] > self.stuff[stone]:
				missing.append(stone)
		if (len(missing) == 0):
			return (None)
		return (missing)

	# Move To Farm
	def move_to_farm(self, missing):
		global turn

		if missing[0] != "food":
			print("Missing : " + str(missing))
		infos = self.have_seen_stones(missing)
		if infos["found"]:
			self.go_to_case(infos["case"])
			self.take_everything()
			return (0)
		self.left()
		self.forward()
		self.take_everything()
		turn += 1
		if turn == 4:
			turn = 0
			self.right()
			for i in range(0, 5):
				self.forward()
		return (self.move_to_farm(missing))

	# Rise Up
	def rise_up(self):
		if not self.is_ready and self.enough_are_ready():
			#si je suis le dernier à avoir suffisament de ressources pour lvl up
			print("Je lance le rassemblement")
			self.is_ready = True
			self.start_gathering()
		elif not self.is_ready:
			#si il manque encore des joueurs pour l'incantation
			self.broadcast("ready:" + str(self.level))
			self.is_ready = True


	### Level 0
	# Play
	def play(self):
		print(">> Play")
		self.begin()
		while 42:
			missing = self.get_missing_stones()
			if missing:
				self.move_to_farm(missing)
			else:
				self.move_to_farm(["food"])
				self.rise_up()


	###########################################################

	### Player Actions
	# Start Incantation
	def start_incantation(self, active):
		print("Start Incantation")
		for stone, nb in need_stones[self.level].items():
			for i in range(0, nb):
				self.set_object(stone)
		if self.incantation(active):
			self.level += 1
		self.is_ready = False
		self.is_joining = False
		print(">> level : " + str(self.level))

	# Not Enough Player
	def not_enough_player(self):
		nb_player = 0

		msg = self.look()
		for item in msg.split(",")[0].split(" "):
			if item == "player":
				nb_player += 1
		#print("nb player : " + str(nb_player) + " | need : " + str(need_members[self.level]))
		if nb_player < need_members[self.level]:
			return (True)
		self.broadcast("zone:" + str(self.zone_id))
		print(">> zone:" + str(self.zone_id))
		return (False)

	# Join Zone
	def join_zone(self, msg):
		print("join zone : " + msg)
		orient = int(msg.split(",")[0].split(" ")[1])
		print("orient : " + str(orient))
		if orient == 0:
			self.start_incantation(PASSIVE)
			return (0)
		if orient == 1:
			self.forward()
		elif orient in [2, 3, 4]:
			self.left()
			self.forward()
		elif orient in [6, 7, 8]:
			self.right()
			self.forward()
		elif orient == 5:
			self.left()
			self.left()
		return (self.verify_answer(self.rcv_msg()))

	# Handle Broadcast
	def handle_broadcast(self, msg):
		msg_type = msg.split(" ")[-1].split(":")[0]
		msg_value = msg.split(":")[1]

	# Msg Ready
	def msg_ready(self, msg):
		msg_value = int(msg.split(":")[1])

		print("msg ready")
		self.dispo_members[msg_value] += 1
		return (CONTINUE)

	# Msg Start
	def msg_start(self, msg):
		msg_value = int(msg.split(":")[1].split("-")[0])
		zone_id = int(msg.split("-")[1])

		#print("msg start")
		if not self.is_ready:
			print("dispo : " + str(self.dispo_members[msg_value]) + " " + str(msg_value))
			self.dispo_members[msg_value] -= need_members[msg_value] - 1
			print("dispo: " + str(self.dispo_members[msg_value]) + " " + str(msg_value))
		if not self.is_joining and self.is_ready and msg_value == self.level:
			print("New Zone id : " + str(zone_id))
			self.zone_id = zone_id
			self.is_joining = True
		return (QUIT)

	# Msg Zone
	def msg_zone(self, msg):
		msg_value = int(msg.split(":")[1])
		
		#print("msg zone")
		if self.is_joining and self.zone_id == msg_value:
			print("try to join zone : " + str(self.zone_id))
			self.join_zone(msg)
			return (QUIT)
		return (CONTINUE)

	# Verify Answer
	def verify_answer(self, msg):
		ret = ""

		for m in msg.split("\n"):
			if m == "":
				if ret == "":
					ret = "other"
				return (ret)
			if m == "dead":
				print("The AI Starved")
				exit(0)
			elif m == "eject":
				pass
			elif m.split(" ")[0] == "message":
				ret = self.msg_functions[m.split(" ")[-1].split(":")[0]](m)
				if ret == QUIT:
					return ("skip")
				elif ret == CONTINUE:
					ret = "other"
			else:
				ret = m
		return (ret)
	
	# Forward
	def forward(self):
		self.send_msg("Forward")
		self.stuff["food"] -= 7
		while True:
			ret = self.verify_answer(self.rcv_msg())
			if ret in ["ok", "ko", "skip"]:
				break
		return (ret)

	# Right
	def right(self):
		self.send_msg("Right")
		self.stuff["food"] -= 7
		while True:
			ret = self.verify_answer(self.rcv_msg())
			if ret in ["ok", "ko", "skip"]:
				break
		return (ret)

	# Left
	def left(self):
		self.send_msg("Left")
		self.stuff["food"] -= 7
		while True:
			ret = self.verify_answer(self.rcv_msg())
			if ret in ["ok", "ko", "skip"]:
				break
		return (ret)

	# Look
	def look(self):
		self.send_msg("Look")
		self.stuff["food"] -= 7
		while True:
			ret = self.verify_answer(self.rcv_msg())
			if ret == "skip" or (ret[0] == "[" and len(ret) > 5):
				break
		objects = ret[2:-2]
		self.last_look = objects
		return (objects)

	# Inventory
	def inventory(self):
		self.send_msg("Inventory")
		self.stuff["food"] -= 1
		while True:
			ret = self.verify_answer(self.rcv_msg())
			if ret == "skip" or ret[0] == "[" and len(ret) > 5:
				break
		objects = ret[2:-2]
		return (objects)

	# Broadcast
	def broadcast(self, msg):
		self.send_msg("Broadcast " + msg)
		self.stuff["food"] -= 7
		while True:
			ret = self.verify_answer(self.rcv_msg())
			if ret in ["ok", "ko", "skip"]:
				break
		return (ret)

	# Connect Number
	def connect_nbr(self):
		self.send_msg("Connect_nbr")
		self.stuff["food"] -= 0
		while True:
			ret = self.verify_answer(self.rcv_msg())
			if ret == "skip" or ret in range(200):
				break
		return (ret)

	# Fork
	def fork(self):
		self.send_msg("Fork")
		self.stuff["food"] -= 42
		while True:
			ret = self.verify_answer(self.rcv_msg())
			if ret in ["ok", "ko", "skip"]:
				break
		return (ret)

	# Eject
	def eject(self):
		self.send_msg("Eject")
		self.stuff["food"] -= 7
		while True:
			ret = self.verify_answer(self.rcv_msg())
			if ret in ["ok", "ko", "skip"]:
				break
		return (ret)

	# Take Object
	def take_object(self, object):
		self.send_msg("Take " + object)
		self.stuff["food"] -= 7
		while True:
			ret = self.verify_answer(self.rcv_msg())
			if ret in ["ok", "ko", "skip"]:
				break
		success = True if ret == "ok" else False
		if success:
			self.stuff[object] += 1
			if object == "food":
				self.stuff[object] += 119
		return (success)

	# Set Object
	def set_object(self, object):
		self.send_msg("Set " + object)
		self.stuff["food"] -= 7
		while True:
			ret = self.verify_answer(self.rcv_msg())
			if ret in ["ok", "ko", "skip"]:
				break
		success = True if ret == "ok" else False
		if success:
			self.stuff[object] -= 1
		return (success)

	# Incantation
	def incantation(self, active):
		tmp = {True:"active", False:"passive"}
		nb_msg = 0

		print("Incantation : " + tmp[active])
		self.stuff["food"] -= 300
		if active:
			self.send_msg("Incantation")
		while True:
			ret = self.verify_answer(self.rcv_msg())
			nb_msg += 1
			if ret in ["Elevation underway", "ko", "skip"]:
				break
			if nb_msg >= 2:
				ret = "ko"
				break
		if ret == "ko":
			return (ret)
		while True:
			ret = self.verify_answer(self.rcv_msg())
			if ret.split(" ")[0] in ["Current", "ko", "skip"]:
				break
		return (ret)

	### Getters Methods
	# Get Team Name
	def get_team_name(self):
		return (self.team_name)

	### Setters Methods
	# Set Team Name
	def set_team_name(self, team_name):
		self.team_name = team_name
