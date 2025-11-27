##
## EPITECH PROJECT, 2025
## B-YEP-400-COT-4-1-zappy-julcinia.oke
## File description:
## parsers
##

from AI.usage import usage
import sys

class Arguments:
    def __init__(self):
        self.port = None
        self.name = None
        self.machine = "localhost"

class Response_parser:
    def __init__(self):
        self.ressources = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]
                                        
    def parse_look(self, response):
        content = response.strip()[1:-1]
        tiles = content.split(',')
        vue = {}
        for i, j in enumerate(tiles):
            j = j.strip()
            if j == '': vue[i] = []
            else: vue[i] = j.split()

        return vue

    def parse_inventory(self, response):
        content = response.strip()[1:-1]
        elems = content.split(',')
        invent = {}
        for i in elems:
            i = i.strip()
            if i:
                obj = i.split()
                if len(obj) == 2:
                    invent[obj[0]] = int(obj[1])

        return invent

    def parse_broadcast(self, response):
        if not response.startswith("message "):
            return None
        try:
            parts = response.split(',', 1)
            if len(parts) < 2:
                return None
            direction_str = parts[0].replace("message ", "").strip()
            message_content = parts[1].strip()
            direction = int(direction_str)
            return {"direction": direction, "message": message_content}
        except ValueError:
            print(f"Error parsing broadcast direction: {direction_str}", file=sys.stderr)
            return None
        except Exception as e:
            print(f"Error parsing broadcast message '{response}': {e}", file=sys.stderr)
            return None

def parser_arg(argv):
    args = Arguments()

    if len(argv) < 5:
        print("Error: Missing required arguments", file=sys.stderr)
        usage()
        exit(84)
    
    i = 1
    while i < len(argv):
        if i + 1 >= len(argv):
            print(f"Error: Option {argv[i]} requires a value", file=sys.stderr)
            exit(84)

        option = argv[i]
        value = argv[i + 1]
        
        if option == "-p":
            try:
                args.port = int(value)
                if args.port <= 0 or args.port > 65535:
                    print(f"Error: Invalid port number {args.port}", file=sys.stderr)
                    exit(84)
            except ValueError:
                print(f"Error: Port must be a number, got '{value}'", file=sys.stderr)
                exit(84)

        elif option == "-n":
            if not value.strip():
                print("Error: Team name cannot be empty", file=sys.stderr)
                exit(84)
            args.name = value

        elif option == "-h":
            args.machine = value

        else:
            print(f"Error: Unknown option {option}", file=sys.stderr)
            usage()
            exit(84)

        i += 2
    
    if args.port is None:
        print("Error: Missing required option -p", file=sys.stderr)
        sys.exit(84)
    
    if args.name is None:
        print("Error: Missing required option -n", file=sys.stderr)
        sys.exit(84)
    
    return args
