#
# parser.py
#

# Imports
from src.ai.usage import usage

# Help Flag
def help_flag(av):
	for flag in av:
		if flag == "-help":
			usage(av[0])
			return (True)
	return (False)

# Get Info
def get_info(infos, av, i):
	keys = {
		"-p": "port",
		"-n": "name",
		"-h": "host"
	}
	args = ["-p", "-n", "-h"]

	for arg in args:
		if av[i] == arg:
			infos[keys[arg]] = av[i + 1]
			return (infos)
	return (None)

# Parse
def parse(av):
	infos = {
		"host": "localhost",
		"name": "",
		"port": 0
	}

	if (len(av) == 1):
		return (None)
	if help_flag(av):
		exit(0)
	for i in range(1, len(av)):
		if i % 2 == 1:
			infos = get_info(infos, av, i)
		if infos == None:
			usage(av[0])
			return (None)
	return (infos)
