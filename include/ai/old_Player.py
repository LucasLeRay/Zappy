#
# old Player.py
#

# Imports
from include.ai.Socket import Socket
from enum import Enum

# Rules
vision = [(0, 0), (1, 3), (4, 8), (9, 15), (16, 24), (25, 36), (37, 51), (52, 69), (70, 90)]

stones = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]

members_to_lvl_up = [1, 2, 2, 4, 4, 6, 6]

rules = [
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
			"food": 10,
			"linemate": 0,
			"deraumere": 0,
			"sibur": 0,
			"mendiane": 0,
			"phiras": 0,
			"thystame": 0
		}
		self.nb_to_lvlup = [0, 0, 0, 0, 0, 0, 0]
		self.team_name = ""
		self.level = 1
		self.last_look = ""
		self.food_list = []
		self.is_ready = False

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
		ret = self.rcv_msg()

	### AI Methods
	# Need Object
	def need_object(self, object):
		if object == "food":
			return (True)
		if object == "linemate" and self.stuff[object] < 9:
			return (True)
		if object == "deraumere" and self.stuff[object] < 8:
			return (True)
		if object == "sibur" and self.stuff[object] < 10:
			return (True)
		if object == "mendiane" and self.stuff[object] < 5:
			return (True)
		if object == "phiras" and self.stuff[object] < 6:
			return (True)
		if object == "thystame" and self.stuff[object] < 1:
			return (True)
		return (False)
	
	# Take Everything
	def take_everything(self):
		seen = self.look()

		for object in seen.split(",")[0].split(" "):
			if object == "player":
				continue
			if self.need_object(object):
				self.take_object(object)
	
	# Begin
	def begin(self):
		self.take_everything()
		#self.fork()

	# Ready For Ritual
	def get_missing_stones(self):
		missing = []

		for stone in stones:
			if rules[self.level - 1][stone] > self.stuff[stone]:
				missing.append(stone)
		if (len(missing) == 0):
			return (None)
		return (missing)

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
		tmp = ["up", "down", "left", "right"]
		dest = Pos()
		i = 0

		#print("case : " + str(case))
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
		#print("Is on the case")

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
			print("circle complete")
			self.right()
			for i in range(0, 5):
				self.forward()
		return (self.move_to_farm(missing))

	# Start Incantation
	def start_incatation(self, active):
		print("Start Incantation")
		for stone, nb in rules[self.level - 1].items():
			for i in range(0, nb):
				self.set_object(stone)
		if self.incantation(active):
			self.level += 1
		print(">> level : " + str(self.level))

	# Join Ritual Zone
	def join_ritual_zone(self):
		if self.level == 1:
			self.start_incatation(True)
			return (0)
		elif self.nb_to_lvlup[self.level - 1] + 1 < members_to_lvl_up[self.level - 1]:
			if not self.is_ready:
				print(">> ready:" + str(self.level))
				self.broadcast("ready:" + str(self.level))
				self.is_ready = True
			return (0)
		self.broadcast("start:" + str(self.level))
		print(">> start:" + str(self.level))
		self.broadcast("food:" + str(self.level) + "-" + str(self.stuff["food"]))
		print(">> food:" + str(self.level) + "-" + str(self.stuff["food"]))

	# Play
	def play(self):
		print(">> Play")
		self.begin()
		print(">> Start")
		while 42:
			missing = self.get_missing_stones()
			if missing:
				self.move_to_farm(missing)
			else:
				self.move_to_farm(["food"])
				self.join_ritual_zone()

	### Player Actions
	# Not Enough Player
	def not_enough_player(self):
		nb_player = 0

		msg = self.look()
		for item in msg.split(",")[0].split(" "):
			if item == "player":
				nb_player += 1
		if nb_player < members_to_lvl_up[self.level - 1]:
			return (True)
		print("enough player : " + msg.replace("food", "."))
		self.broadcast("zone:" + str(self.level))
		print(">> zone:" + str(self.level))
		self.look()
		print("wait")
		return (False)

	# Join Zone
	def join_zone(self, msg):
		print("join zone : " + msg)
		orient = int(msg.split(",")[0].split(" ")[1])
		print("orient : " + str(orient))
		if orient == 0:
			self.start_incatation(False)
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
		return (self.verify_answer(self.rcv_msg(), ["zone"]))

	# Handle Broadcast
	def handle_broadcast(self, msg):
		msg_type = msg.split(" ")[-1].split(":")[0]
		msg_value = msg.split(":")[1]

		if msg_type == "ready":
			print("<< ready")
			#self.nb_to_lvlup[self.level - 1] += 1
			self.nb_to_lvlup[int(msg_value) - 1] += 1
			print("nb to lvlup : " + str(self.nb_to_lvlup[int(msg_value) - 1]))
		elif msg_type == "start":
			print("<< Start")
			if int(msg_value) == self.level and self.is_ready:
				self.broadcast("food:" + str(self.level) + "-" + str(self.stuff["food"]))
				print(">> food:" + str(self.level) + "-" + str(self.stuff["food"]))
		#elif msg_type == "food"and int(msg_value.split("-")[0]) == self.level:
		elif msg_type == "food":
			if int(msg_value.split("-")[0]) == self.level and self.is_ready:
				print("<< food: " + msg_value)
				self.food_list.append(int(msg_value.split("-")[1]))
			self.nb_to_lvlup[int(msg_value.split("-")[0]) - 1] -= 1
			#self.nb_to_lvlup[self.level - 1] -= 1
			print("nb to lvlup : " + str(self.nb_to_lvlup[self.level - 1]))
			if self.nb_to_lvlup[self.level - 1] <= 0 and self.is_ready:
				print("nb food : " + str(self.stuff["food"]) + " - " + str(self.food_list))
				if int(self.stuff["food"]) >= max(self.food_list):
					while self.not_enough_player():
						self.broadcast("zone:" + str(self.level))
						print(">> zone:" + str(self.level))
					self.start_incatation(True)
					print("finished1")
					self.is_ready = False
				self.food_list = []
		elif msg_type == "zone" and int(msg_value) == self.level and self.is_ready:
			self.join_zone(msg)
			print("finished2")
			self.is_ready = False

	# Verify Answer
	def verify_answer(self, msg, expected):
		ret = ""

		for m in msg.split("\n"):
			if m == "":
				if not str(ret).split(" ")[0] in expected:
					return (self.verify_answer(self.rcv_msg(), expected))
				return (ret)
			if m == "dead":
				print(">> The AI Starved !")
				exit(0)
			elif m.split(" ")[0] == "message":
				self.handle_broadcast(m)
			elif m == "Eject":
				pass
			elif m == "ok":
				ret = True
			elif m == "ko":
				ret = False
			else:
				ret = m
		if not str(ret).split(" ")[0] in expected:
			return (self.verify_answer(self.rcv_msg(), expected))
		return (ret)
	
	# Forward
	def forward(self):
		self.send_msg("Forward")
		return (self.verify_answer(self.rcv_msg(), ["True", "False"]))

	# Right
	def right(self):
		self.send_msg("Right")
		return (self.verify_answer(self.rcv_msg(), ["True", "False"]))

	# Left
	def left(self):
		self.send_msg("Left")
		return (self.verify_answer(self.rcv_msg(), ["True", "False"]))

	# Look
	def look(self):
		self.send_msg("Look")
		objects = self.verify_answer(self.rcv_msg(), ["["])[2:-2]
		self.last_look = objects
		return (objects)

	# Inventory
	def inventory(self):
		self.send_msg("Inventory")
		return (self.verify_answer(self.rcv_msg(), ["["]))

	# Broadcast
	def broadcast(self, msg):
		self.send_msg("Broadcast " + msg)
		return (self.verify_answer(self.rcv_msg(), ["True", "False"]))

	# Connect Number
	def connect_nbr(self):
		self.send_msg("Connect_nbr")
		return (self.verify_answer(self.rcv_msg(), []))

	# Fork
	def fork(self):
		self.send_msg("Fork")
		return (self.verify_answer(self.rcv_msg(), ["True", "False"]))

	# Eject
	def eject(self):
		self.send_msg("Eject")
		return (self.verify_answer(self.rcv_msg(), ["True", "False"]))

	# Take Object
	def take_object(self, object):
		self.send_msg("Take " + object)
		success = self.verify_answer(self.rcv_msg(), ["True", "False"])
		if success:
			self.stuff[object] += 1
		return (success)

	# Set Object
	def set_object(self, object):
		self.send_msg("Set " + object)
		success = self.verify_answer(self.rcv_msg(), ["True", "False"])
		if success:
			self.stuff[object] -= 1
		return (success)

	# Incantation
	def incantation(self, active):
		tmp = {True:"active", False:"passive"}

		print("Incantation : " + tmp[active])
		if active:
			self.send_msg("Incantation")
		self.verify_answer(self.rcv_msg(), ["Elevation"])
		return (self.verify_answer(self.rcv_msg(), ["Current"]))

	### Getters Methods
	# Get Team Name
	def get_team_name(self):
		return (self.team_name)

	### Setters Methods
	# Set Team Name
	def set_team_name(self, team_name):
		self.team_name = team_name
