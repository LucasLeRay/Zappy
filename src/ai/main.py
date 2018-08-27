#
# main.py
#

# Imports
from include.ai.Player import Player
from src.ai.parser import parse
import sys

# Global
player = Player()

# Launch Game
def launch_game():
	player.preliminaries()
	player.play()

# Main
def main():
	infos = parse(sys.argv)
	if infos == None:
		return (84)
	player.set_team_name(infos["name"])
	if player.connect(infos) == -1:
		return (84)
	launch_game()
