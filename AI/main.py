#!/usr/bin/env python3
##
## EPITECH PROJECT, 2025
## B-YEP-400-COT-4-1-zappy-julcinia.oke
## File description:
## main
##

from AI.usage import usage
from AI.parsers import parser_arg
from AI.player import Player
import sys

def main():
    if len(sys.argv) == 2 and sys.argv[1] == "--help":
        usage()
        exit(0)

    player = None
    try:
        player = Player()
        cmd = parser_arg(sys.argv)
        player.connection(cmd.machine, cmd.port, cmd.name)
        player.start()

    except KeyboardInterrupt:
        print("\nProgram interrupted")
        if player.serveur.connected:
            player.serveur.disconnect()
        exit(0)
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        if player.serveur and player.serveur.connected:
            player.serveur.disconnect()
            print("Disconnectedd !")
        exit(84)

if __name__ == "__main__":
    main()
