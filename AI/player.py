#!/usr/bin/env python3
##
## EPITECH PROJECT, 2025
## B-YEP-400-COT-4-1-zappy-julcinia.oke
## File description:
## player
##

from AI.server import ZappySocketAsync
from AI.parsers import Response_parser
from AI.broadcast import ElevationState, BroadcastManager
import sys
import time

class Position:
    x: int
    y: int

class Inventory:
    def __init__(self):
        self.food = 0
        self.linemate = 0
        self.deraumere = 0
        self.sibur = 0
        self.mendiane = 0
        self.phiras = 0
        self.thystame = 0

    def update_from_dict(self, data: dict):
        for key, value in data.items():
            if hasattr(self, key):
                setattr(self, key, value)

    def __repr__(self):
        return (f"Inventory (food={self.food}, linemate={self.linemate}, deraumere={self.deraumere}, "
                f"sibur={self.sibur}, mendiane={self.mendiane}, phiras={self.phiras}, thystame={self.thystame})")

LEVEL_REQUIREMENTS = [
    {},
    {"players": 1, "linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}, # niv 1-> niv 2
    {"players": 2, "linemate": 1, "deraumere": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0}, # niv 2-> niv 3
    {"players": 2, "linemate": 2, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 2, "thystame": 0}, # niv 3-> niv 4
    {"players": 4, "linemate": 1, "deraumere": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0}, # niv 4-> niv 5
    {"players": 4, "linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0}, # niv 5-> niv 6
    {"players": 6, "linemate": 1, "deraumere": 2, "sibur": 3, "mendiane": 0, "phiras": 1, "thystame": 0}, # niv 6-> niv 7
    {"players": 6, "linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1}  # niv 7-> niv 8
]

class SurvivalState:
    EMERGENCY = "emergency"
    CRITICAL = "critical"
    LOW = "low"
    SAFE = "safe"

class Player:
    def __init__(self):
        self.serveur: ZappySocketAsync = None
        self.inventory: Inventory = Inventory()
        self.parser: Response_parser = Response_parser()
        self.level = 1
        self.items_needed = LEVEL_REQUIREMENTS[self.level]
        self.is_alive = True
        self.food_emergency = 5
        self.food_critical = 8
        self.food_low = 12
        self.food_safe = 15

        self.spiral_state = {'direction': 0, 'steps_in_direction': 0, 'max_steps': 1}
        self.exploration_mode = "spiral"
        self.last_exploration_look = {}
        self.egg_waiting_for_connection = False

        self.survival_state = SurvivalState.SAFE
        self.elevation_state = ElevationState.COLLECTING
        self.last_food_check = 0
        self.last_broadcast_time = 0
        self.broadcast_cooldown = 5
        self.waiting_for_players = False
        self.ready_players_count = 0

    def connection(self, hostname, port, team_name):
        self.serveur = ZappySocketAsync(hostname, port, team_name)
        if self.serveur.connect():
            self.broadcast_manager = BroadcastManager(self)
            self.serveur.set_broadcast_handler(self.broadcast_manager.handle_broadcast)

            print("Player successfully connected to the server.")
            self.cmd_inventory()
            print(f"Initial Inventory: {self.inventory}")
            self.update_survival_state()
            self.update_items_needed()
        else:
            print("Failed to connect to the server.")
            sys.exit(84)

    def update_items_needed(self):
        self.items_needed = LEVEL_REQUIREMENTS[self.level].copy()
        print(f"Updated items needed for level {self.level} -> {self.level + 1}: {self.items_needed}")

    def start(self):
        print("The game can now start baby :)")
        while self.is_alive and self.level < 8:
            if not self.serveur.is_connected():
                print("Connection lost, stopping AI")
                self.is_alive = False
                return
            self.run_ai_logic()
            time.sleep(0.1)

        if self.level == 8:
            print("AI win! Victory!")
        elif not self.is_alive:
            print("AI died.")

    def update_survival_state(self):
        if self.inventory.food <= self.food_emergency:
            self.survival_state = SurvivalState.EMERGENCY
        elif self.inventory.food <= self.food_critical:
            self.survival_state = SurvivalState.CRITICAL
        elif self.inventory.food <= self.food_low:
            self.survival_state = SurvivalState.LOW
        else:
            self.survival_state = SurvivalState.SAFE

    def run_ai_logic(self):
        current_time = time.time()
        if current_time - self.last_food_check > 1.0:
            self.cmd_inventory()
            self.update_survival_state()
            self.last_food_check = current_time

        print(f"Level: {self.level} | Food: {self.inventory.food} | State: {self.survival_state} | Elevation: {self.broadcast_manager.elevation_state}")

        if self.survival_state == SurvivalState.EMERGENCY:
            print("EMERGENCY - Abandon de toute activité, recherche intensive de nourriture")
            if self.broadcast_manager.continuous_broadcast:
                self.broadcast_manager.abandon_current_session()
            self.emergency_food_search()
            return

        elif self.survival_state == SurvivalState.CRITICAL:
            print("CRITICAL - Priorité absolue à la nourriture")
            if self.broadcast_manager.am_leader and self.broadcast_manager.continuous_broadcast:
                self.broadcast_manager.abandon_current_session()
            if self.urgent_food_search():
                return

        elif self.survival_state == SurvivalState.LOW:
            print("LOW - Intégrer recherche de nourriture")
            self.integrated_food_search()

        if self.should_fork() and self.inventory.food > self.food_critical:
            print("Fork needed to ensure enough players for future levels")
            self.cmd_fork()
            return

        if self.broadcast_manager.manage_elevation_process():
            print("Elevation process completed successfully!")
            self.update_items_needed()
            return

        if self.broadcast_manager.elevation_state == ElevationState.COLLECTING:
            self.resource_search()

    def should_fork(self):
        if self.broadcast_manager.elevation_state != ElevationState.COLLECTING:
            print("Not forking: currently in elevation process")
            return False

        if (self.broadcast_manager.moving_to_leader or 
            self.broadcast_manager.elevation_state in [ElevationState.MOVING_TO_LEADER, 
                                                      ElevationState.WAITING_ON_TILE]):
            print("Not forking: moving to leader or waiting on tile")
            return False

        current_time = time.time()
        if (self.broadcast_manager.last_ready_for_level_received > 0 and 
            current_time - self.broadcast_manager.last_ready_for_level_received < 30):
            print(f"Not forking: recently received leader broadcast ({current_time - self.broadcast_manager.last_ready_for_level_received:.1f}s ago)")
            return False

        multi_player_levels = [2, 3, 4, 5, 6, 7]
        
        if self.level in multi_player_levels:
            required_players = LEVEL_REQUIREMENTS[self.level].get("players", 1)
            current_players = self.cmd_connect_nbr()

            if (current_players < required_players and 
                self.serveur.client_num > 0 and 
                self.inventory.food > self.food_safe):
                print(f"Need {required_players} players, only {current_players} available, forking...")
                return True
        return False

    def check_players_on_tile(self):
        look_data = self.cmd_look()
        current_tile_content = look_data.get(0, [])
        player_count = current_tile_content.count('player')
        required_players = self.items_needed.get("players", 1)
        print(f"Players on tile: {player_count}, Required: {required_players}")

        return player_count >= required_players

    def resource_search(self):
        print("Starting resource search...")

        look_data = self.cmd_look()
        self.last_exploration_look = look_data

        targets = self.find_resources(look_data)
        if targets:
            best_target = self.choose_target(targets)
            print(f"Found target: {best_target['type']} on tile {best_target['tile']}")
            self.move_towards_tile(best_target['tile'])
        else:
            print("No targets found, using exploration strategy")
            self.execute_exploration_strategy()

    def find_resources(self, look_data):
        targets = []
        missing_resources = self.has_missing_resources() or {}

        for tile_index, content in look_data.items():
            if tile_index == 0:
                for item in content:
                    if item == 'food' and self.survival_state != SurvivalState.SAFE:
                        self.cmd_take(item)
                    elif item in missing_resources:
                        self.cmd_take(item)
                continue

            for item in content:
                priority = self.is_priority(item, missing_resources)
                if priority > 0:
                    targets.append({
                        'type': item,
                        'tile': tile_index,
                        'priority': priority,
                        'distance': self.distance(tile_index)
                    })

        return targets

    def is_priority(self, item, missing_resources):
        if item == 'food':
            if self.survival_state == SurvivalState.EMERGENCY:
                return 1000
            elif self.survival_state == SurvivalState.CRITICAL:
                return 500
            elif self.survival_state == SurvivalState.LOW:
                return 100
            else:
                return 10
        if item in missing_resources:
            return 200
        return 0

    def choose_target(self, targets):
        if not targets:
            return None
        targets.sort(key=lambda x: (-x['priority'], x['distance']))
        return targets[0]

    def distance(self, tile_index):
        distance_map = {
            0: 0,
            1: 2, 2: 1, 3: 2,
            4: 4, 5: 3, 6: 2, 7: 3, 8: 4,
        }
        return distance_map.get(tile_index, tile_index // 2 + 1)

    def execute_exploration_strategy(self):
        if self.exploration_mode == "spiral":
            self.execute_spiral_movement()
        else:
            self.execute_movement_strategy()

    def execute_spiral_movement(self):
        if self.spiral_state['steps_in_direction'] < self.spiral_state['max_steps']:
            self.cmd_forward()
            self.spiral_state['steps_in_direction'] += 1
            print(f"Spiral: Forward (step {self.spiral_state['steps_in_direction']}/{self.spiral_state['max_steps']})")
        else:
            self.cmd_right()
            self.spiral_state['direction'] = (self.spiral_state['direction'] + 1) % 4
            self.spiral_state['steps_in_direction'] = 0

            if self.spiral_state['direction'] % 2 == 0:
                self.spiral_state['max_steps'] += 1

            print(f"Spiral: Changed direction, new max_steps: {self.spiral_state['max_steps']}")

    def emergency_food_search(self):
        look_data = self.cmd_look()

        if 'food' in look_data.get(0, []):
            self.cmd_take("food")
            self.cmd_inventory()
            if self.inventory.food > self.food_emergency:
                print("Emergency resolved!")
                return

        food_targets = []
        for tile_index, content in look_data.items():
            if 'food' in content and tile_index > 0:
                food_targets.append({
                    'tile': tile_index,
                    'distance': self.distance(tile_index)
                })

        if food_targets:
            closest_food = min(food_targets, key=lambda x: x['distance'])
            print(f"Emergency: Moving to food on tile {closest_food['tile']}")
            self.move_towards_tile(closest_food['tile'])
        else:
            self.execute_exploration_strategy()

    def urgent_food_search(self):
        look_data = self.cmd_look()

        if 'food' in look_data.get(0, []):
            print("Food on current tile, taking it.")
            self.cmd_take("food")
            return True

        for tile_index, content in look_data.items():
            if 'food' in content and tile_index > 0:
                print(f"Food found on tile {tile_index}, moving towards it.")
                self.move_towards_tile(tile_index)
                return True

        print("No food visible, exploring...")
        self.execute_exploration_strategy()
        return False

    def integrated_food_search(self):
        look_data = self.cmd_look()
        if 'food' in look_data.get(0, []):
            self.cmd_take("food")

    def collect_missing_resources(self):
        missing_resources = self.has_missing_resources()
        if not missing_resources:
            return

        print(f"Missing resources for level {self.level + 1}: {missing_resources}")

    def move_towards_tile(self, tile_index):
        if tile_index == 1:  # Devant-gauche
            self.cmd_forward()
            self.cmd_left()
            self.cmd_forward()
        elif tile_index == 2:  # Devant
            self.cmd_forward()
        elif tile_index == 3:  # Devant-droite
            self.cmd_forward()
            self.cmd_right()
            self.cmd_forward()
        elif tile_index == 4:  # Devant-Devant-gauche-gauche
            self.cmd_forward()
            self.cmd_forward()
            self.cmd_left()
            self.cmd_forward()
            self.cmd_forward()
        elif tile_index == 5:  # Devant-Devant-gauche
            self.cmd_forward()
            self.cmd_forward()
            self.cmd_left()
            self.cmd_forward()
        elif tile_index == 6:  # Devant-Devant
            self.cmd_forward()
            self.cmd_forward()
        elif tile_index == 7:  # Devant-Devant-droite
            self.cmd_forward()
            self.cmd_forward()
            self.cmd_right()
            self.cmd_forward()
        elif tile_index == 8:  # Devant-Devant-droite-droite
            self.cmd_forward()
            self.cmd_forward()
            self.cmd_right()
            self.cmd_forward()
            self.cmd_forward()

    def execute_movement_strategy(self):
        if not hasattr(self, 'movement_strategy'):
            self.movement_strategy = ["Forward", "Forward", "Right", "Forward", "Forward", "Left"]
            self.movement_index = 0

        command = self.movement_strategy[self.movement_index]
        if command == "Forward":
            self.cmd_forward()
        elif command == "Right":
            self.cmd_right()
        elif command == "Left":
            self.cmd_left()
        self.movement_index = (self.movement_index + 1) % len(self.movement_strategy)

    def check_incantation_prerequisites(self):
        if self.inventory.food < self.food_critical:
            print(f"Not enough food for incantation ({self.inventory.food} < {self.food_critical})")
            return False

        look_data = self.cmd_look()
        current_tile_content = look_data.get(0, [])

        current_tile_resources = {res: 0 for res in self.parser.ressources + ['player']}
        for item in current_tile_content:
            if item in current_tile_resources:
                current_tile_resources[item] += 1

        actual_players_on_tile = current_tile_resources.get('player', 0) + 1

        for item, required_quantity in self.items_needed.items():
            if item == "players":
                if actual_players_on_tile < required_quantity:
                    print(f"Not enough players: {actual_players_on_tile} < {required_quantity}")
                    return False
            else:
                if getattr(self.inventory, item, 0) < required_quantity:
                    print(f"Not enough {item}: {getattr(self.inventory, item, 0)} < {required_quantity}")
                    return False
        return True

    def has_missing_resources(self):
        missing = {}
        for item, required in self.items_needed.items():
            if item != "players":
                current_amount = getattr(self.inventory, item, 0)
                if current_amount < required:
                    missing[item] = required - current_amount
        return missing if missing else None

    def cmd_take(self, obj_name: str):
        if obj_name == "food" and self.inventory.food >= 25:
            return True
        try:
            response = self.serveur.send_command(f"Take {obj_name}")
            if response.strip() == "ok":
                print(f"Successfully took {obj_name}")
                return True
            else:
                print(f"Failed to take {obj_name}: {response.strip()}")
                return False
        except Exception as e:
            print(f"Error taking {obj_name}: {e}")
            return False

    def cmd_set(self, obj_name: str):
        try:
            response = self.serveur.send_command(f"Set {obj_name}")
            if response.strip() == "ok":
                print(f"Successfully set {obj_name}")
                return True
            else:
                print(f"Failed to set {obj_name}: {response.strip()}")
                return False
        except Exception as e:
            print(f"Error setting {obj_name}: {e}")
            return False

    def cmd_incantation(self):
        try:
            response = self.serveur.send_command("Incantation")
            print(f"Incantation response: {response}")
            if "Elevation underway" not in response:
                self.broadcast_manager.recover_dropped_resources()
                return False
            start_time = time.time()
            while time.time() - start_time < 60:
                notification = self.serveur.message_handler.get_notification(timeout=10)
                if notification and "current level:" in notification.lower():
                    self.level += 1
                    print(f"Level up to {self.level}!")
                    self.broadcast_manager.dropped_resources.clear()
                    self.broadcast_manager.reset_elevation_state()
                    return True
                time.sleep(0.1)

            print("Timeout waiting for level notification")
            self.broadcast_manager.recover_dropped_resources()
            return False

        except Exception as e:
            print(f"Incantation error: {e}")
            self.broadcast_manager.recover_dropped_resources()
            return False

    def cmd_fork(self):
        try:
            response = self.serveur.send_command("Fork")
            if response.strip() == "ok":
                print("Successfully forked, an egg has been laid.")
                self.egg_waiting_for_connection = True
                return True
            else:
                print(f"Failed to fork: {response.strip()}")
                return False
        except Exception as e:
            print(f"Error forking: {e}")
            return False

    def cmd_eject(self):
        try:
            response = self.serveur.send_command("Eject")
            if response.strip() == "ok":
                print("Successfully ejected players from this tile.")
                return True
            else:
                print(f"Failed to eject: {response.strip()}")
                return False
        except Exception as e:
            print(f"Error ejecting: {e}")
            return False

    def cmd_broadcast(self, message: str):
        try:
            response = self.serveur.send_command(f"Broadcast {message}")
            if response.strip() == "ok":
                print(f"Successfully broadcasted: '{message}'")
                return True
            else:
                print(f"Failed to broadcast: {response.strip()}")
                return False
        except Exception as e:
            print(f"Error broadcasting: {e}")
            return False

    def cmd_connect_nbr(self):
        try:
            response = self.serveur.send_command("Connect_nbr")
            slots = int(response.strip())
            print(f"Available connection slots for team: {slots}")
            return slots
        except ValueError:
            print(f"Error parsing connect_nbr response: {response}")
            return 0
        except Exception as e:
            print(f"Error getting connect_nbr: {e}")
            return 0

    def cmd_inventory(self):
        try:
            response = self.serveur.send_command("Inventory")
            if response and self.is_inventory_response(response):
                inventory_data = self.parser.parse_inventory(response)
                if inventory_data:
                    self.inventory.update_from_dict(inventory_data)
                    return True
            else:
                print(f"Warning: Received unexpected response for Inventory: {response}")
                return False
        except Exception as e:
            print(f"Error getting inventory: {e}")
            return False

    def is_inventory_response(self, response):
        if not response:
            return False
        return (response.startswith('[') and response.endswith(']') and 
                any(item in response.lower() for item in ['food', 'linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame']))

    def cmd_look(self):
        try:
            response = self.serveur.send_command("Look")
            if response and self.is_look_response(response):
                return self.parser.parse_look(response)
            else:
                print(f"Warning: Received unexpected response for Look: {response}")
                return {}
        except Exception as e:
            print(f"Error looking around: {e}")
            return {}

    def is_look_response(self, response):
        if not response:
            return False
        return response.startswith('[') and response.endswith(']') and ',' in response

    def cmd_forward(self):
        try:
            response = self.serveur.send_command("Forward")
            success = response.strip() == "ok"
            if not success:
                print(f"Forward failed: {response.strip()}")
            return success
        except Exception as e:
            print(f"Error moving forward: {e}")
            return False

    def cmd_left(self):
        try:
            response = self.serveur.send_command("Left")
            success = response.strip() == "ok"
            if not success:
                print(f"Left failed: {response.strip()}")
            return success
        except Exception as e:
            print(f"Error turning left: {e}")
            return False

    def cmd_right(self):
        try:
            response = self.serveur.send_command("Right")
            success = response.strip() == "ok"
            if not success:
                print(f"Right failed: {response.strip()}")
            return success
        except Exception as e:
            print(f"Error turning right: {e}")
            return False
