#!/usr/bin/env python3
##
## EPITECH PROJECT, 2025
## B-YEP-400-COT-4-1-zappy-julcinia.oke
## File description:
## broadcast
##

import threading
import time

class ElevationState:
    COLLECTING = "collecting"
    BROADCASTING = "broadcasting" 
    WAITING_RESPONSES = "waiting_responses"
    MOVING_TO_LEADER = "moving_to_leader"
    WAITING_ON_TILE = "waiting_on_tile"
    READY_TO_INCANT = "ready_to_incant"
    INCANTING = "incanting"

class BroadcastManager:
    def __init__(self, player):
        self.player = player
        self.team_broadcasts = {}
        self.last_broadcast_time = 0
        self.broadcast_cooldown = 2.0
        self.elevation_state = ElevationState.COLLECTING
        self.current_leader = None
        self.leader_direction = None
        self.elevation_session_id = None
        self.confirmed_players = set()
        self.dropped_resources = {}
        self.last_elevation_broadcast = 0
        self.waiting_for_responses_since = 0
        self.response_timeout = 15.0
        self.active_elevation_sessions = {}
        self.am_leader = False
        self.continuous_broadcast = False
        self.broadcast_until_food_level = 10
        self.moving_to_leader = False
        self.last_ready_for_level_received = 0
        self.ready_for_level_count = 0
        self.no_response_timeout = 15.0
        self.leader_timeout = 0
        self.session_abandoned = False
        self.movement_attempts = 0
        self.max_movement_attempts = 30
        self.movement_direction = None
        self.coming_broadcast_active = False
        self.broadcast_message_template = None
        self.last_movement_time = 0
        self.movement_cooldown = 1.0
        self.leader_exists_for_level = False
        self.leader_exists_timeout = 0
        self.leader_detection_timeout = 10.0

    def handle_broadcast(self, broadcast_message):
        print(f"[BROADCAST RECEIVED]: {broadcast_message}")
        if broadcast_message.startswith("message "):
            try:
                content = broadcast_message[8:]
                if ',' in content:
                    direction_str, message = content.split(',', 1)
                    direction = int(direction_str)
                    message = message.strip()
                    print(f"Broadcast from direction {direction}: '{message}'")

                    if message.startswith("ready_for_level_"):
                        self.handle_leader_broadcast(direction, message)
                    elif message.startswith("i_am_coming_"):
                        self.handle_coming_broadcast(direction, message)
                    elif message.startswith("session_full"):
                        self.handle_session_full_broadcast(direction, message)
                    elif message.startswith("elevation_complete"):
                        self.handle_elevation_complete_broadcast(direction, message)
                    elif message.startswith("session_abandoned"):
                        self.handle_session_abandoned_broadcast(direction, message)
            except (ValueError, IndexError) as e:
                print(f"Error parsing broadcast: {e}")

    def handle_leader_broadcast(self, direction, message):
        try:
            parts = message.split('_')
            if len(parts) >= 4:
                level = int(parts[3])
                current_time = time.time()
                if level == self.player.level:
                    print(f"Received ready_for_level_{level} - Leader detected for my level!")
                    self.leader_exists_for_level = True
                    self.leader_exists_timeout = current_time + self.leader_detection_timeout
                    if (self.am_leader or 
                        self.elevation_state == ElevationState.BROADCASTING or
                        self.continuous_broadcast):
                        print("I was trying to become leader, but another leader exists - ABANDONING LEADERSHIP")
                        self.abandon_leadership_immediately()
                    if (self.elevation_state == ElevationState.COLLECTING and 
                        not self.session_abandoned and
                        not self.moving_to_leader and
                        self.player.inventory.food > self.player.food_critical):
                        print(f"Switching to passive mode and joining leader for level {level}")
                        if not self.player_has_required_resources():
                            print("Don't have required resources, ignoring broadcast")
                            return
                        print(f"Responding to leader with i_am_coming_{level}")

                        if self.send_coming_response(level):
                            print(f"Successfully sent i_am_coming_{level}")

                            self.leader_direction = direction
                            self.movement_direction = direction
                            self.elevation_state = ElevationState.MOVING_TO_LEADER
                            self.moving_to_leader = True
                            self.coming_broadcast_active = True
                            self.last_ready_for_level_received = current_time
                            self.ready_for_level_count = 1
                            self.movement_attempts = 0
                            self.leader_timeout = current_time + self.no_response_timeout
                            self.last_movement_time = current_time

                            print(f"Started moving towards leader at direction {direction}")
                        else:
                            print("Failed to send i_am_coming response")

                    elif (self.elevation_state == ElevationState.MOVING_TO_LEADER and 
                          direction == self.leader_direction):
                        self.last_ready_for_level_received = current_time
                        self.ready_for_level_count += 1
                        self.leader_timeout = current_time + self.no_response_timeout
                        print(f"Still receiving broadcasts from leader (count: {self.ready_for_level_count})")

        except (ValueError, IndexError) as e:
            print(f"Error parsing leader broadcast: {e}")

    def abandon_leadership_immediately(self):
        print("IMMEDIATELY abandoning leadership - another leader detected!")

        self.am_leader = False
        self.continuous_broadcast = False

        if self.elevation_state == ElevationState.BROADCASTING:
            self.elevation_state = ElevationState.COLLECTING

        self.confirmed_players.clear()
        self.broadcast_message_template = None

        print("Leadership abandoned, switching to passive mode")

    def can_become_leader(self):
        current_time = time.time()

        if (self.leader_exists_for_level and 
            current_time < self.leader_exists_timeout):
            print(f"Cannot become leader: another leader exists for level {self.player.level}")
            return False

        if (self.leader_exists_for_level and 
            current_time >= self.leader_exists_timeout):
            print("Leader existence timeout reached, can try to become leader again")
            self.leader_exists_for_level = False
            self.leader_exists_timeout = 0

        if not (self.player_has_required_resources() and 
                self.player.inventory.food > self.player.food_low and
                self.elevation_state == ElevationState.COLLECTING):
            return False

        print(f"Can become leader: Resources={self.player_has_required_resources()}, Food={self.player.inventory.food}, State={self.elevation_state}, NoLeaderExists={not self.leader_exists_for_level}")
        return True

    def should_abandon_due_to_food(self):
        if self.player.inventory.food <= self.player.food_emergency:
            print(f"Food emergency level reached ({self.player.inventory.food} <= {self.player.food_emergency})")
            return True
        if (self.am_leader and 
            self.player.inventory.food <= self.player.food_critical):
            print(f"Leader abandoning due to critical food ({self.player.inventory.food} <= {self.player.food_critical})")
            return True
        if (self.elevation_state == ElevationState.MOVING_TO_LEADER and 
            self.player.inventory.food <= self.player.food_low):
            print(f"Abandoning movement to leader due to low food ({self.player.inventory.food} <= {self.player.food_low})")
            return True

        return False

    def handle_coming_broadcast(self, direction, message):
        try:
            parts = message.split('_')
            if len(parts) >= 4:
                level = int(parts[3])

                if (level == self.player.level and
                    self.am_leader and
                    self.elevation_state in [ElevationState.BROADCASTING, ElevationState.WAITING_RESPONSES]):
                    print(f"Player confirmed for level {level} from direction {direction}")
                    self.confirmed_players.add(f"player_{direction}_{time.time()}")
                    required_players = self.player.items_needed.get("players", 1)
                    current_players_on_tile = self.count_players_on_tile()
                    total_players = current_players_on_tile

                    print(f"Players confirmed: {len(self.confirmed_players)}, Players on tile: {current_players_on_tile}, Total: {total_players}, Required: {required_players}")

                    if total_players >= required_players:
                        print("Enough players on tile, stopping broadcast and preparing incantation")
                        self.continuous_broadcast = False
                        self.elevation_state = ElevationState.READY_TO_INCANT

        except (ValueError, IndexError) as e:
            print(f"Error parsing coming broadcast: {e}")

    def handle_session_abandoned_broadcast(self, direction, message):
        try:
            parts = message.split('_')
            if len(parts) >= 3:
                level = int(parts[2])

                if (level == self.player.level and 
                    self.elevation_state in [ElevationState.MOVING_TO_LEADER, ElevationState.WAITING_ON_TILE]):
                    print(f"Session abandoned for level {level}, returning to collecting")
                    self.abandon_current_session()

        except (ValueError, IndexError) as e:
            print(f"Error parsing session abandoned broadcast: {e}")

    def check_leader_timeout(self):
        current_time = time.time()

        if (self.elevation_state == ElevationState.MOVING_TO_LEADER and 
            self.leader_timeout > 0 and 
            current_time > self.leader_timeout):

            print(f"Leader timeout reached, no broadcasts received for {self.no_response_timeout}s")
            self.abandon_current_session()
            return True

        return False

    def abandon_current_session(self):
        print("Abandoning current elevation session")

        if self.am_leader:
            self.broadcast_session_abandoned()

        self.session_abandoned = True
        self.reset_elevation_state()

        def reset_abandoned_flag():
            time.sleep(10)
            self.session_abandoned = False
            print("Session abandoned flag reset, can become leader again")

        threading.Thread(target=reset_abandoned_flag, daemon=True).start()

    def broadcast_session_abandoned(self):
        if self.am_leader:
            message = f"session_abandoned_{self.player.level}"
            if self.player.cmd_broadcast(message):
                print(f"Broadcasted session abandoned: {message}")
                return True
        return False

    def handle_session_full_broadcast(self, direction, message):
        try:
            if self.elevation_state == ElevationState.MOVING_TO_LEADER:
                print("Session is full, stopping movement and waiting")
                self.elevation_state = ElevationState.WAITING_ON_TILE
        except Exception as e:
            print(f"Error parsing session full broadcast: {e}")

    def handle_elevation_complete_broadcast(self, direction, message):
        print("Elevation completed by another group")
        if self.elevation_state != ElevationState.COLLECTING:
            self.reset_elevation_state()

    def manage_elevation_process(self):
        current_time = time.time()

        if self.should_abandon_due_to_food():
            print("Abandoning elevation due to critical food level")
            self.abandon_current_session()
            return False

        if self.check_leader_timeout():
            return False

        if self.elevation_state == ElevationState.COLLECTING:
            if self.can_become_leader() and not self.session_abandoned:
                required_players = self.player.items_needed.get("players", 1)
                if required_players > 1:
                    print(f"All resources collected, starting leadership broadcast for level {self.player.level}")
                    if self.start_leadership_broadcast():
                        print("Successfully started continuous broadcasting as leader")
                    else:
                        print("Failed to start leadership broadcast")
                        return False
                else:
                    print("No other players needed, ready for incantation")
                    self.elevation_state = ElevationState.READY_TO_INCANT
                    self.am_leader = True

        elif self.elevation_state == ElevationState.BROADCASTING:
            if self.should_abandon_leadership():
                print("Abandoning leadership due to unfavorable conditions")
                self.abandon_current_session()
                return False

            if self.should_continue_broadcasting():
                message = f"ready_for_level_{self.player.level}"
                if self.player.cmd_broadcast(message):
                    self.last_elevation_broadcast = current_time
                    print(f"Broadcasting: {message}")
                else:
                    print("Failed to continue broadcasting")

        elif self.elevation_state == ElevationState.MOVING_TO_LEADER:
            if (self.coming_broadcast_active and 
                current_time - self.last_elevation_broadcast >= self.broadcast_cooldown):
                coming_message = f"i_am_coming_{self.player.level}"
                if self.player.cmd_broadcast(coming_message):
                    self.last_elevation_broadcast = current_time
                    print(f"Broadcasting while moving: {coming_message}")

            if current_time - self.last_movement_time >= self.movement_cooldown:
                if self.move_towards_leader():
                    print("Successfully reached leader!")
                    self.elevation_state = ElevationState.WAITING_ON_TILE
                    self.coming_broadcast_active = False
                    self.moving_to_leader = False
                    return False
                else:
                    self.last_movement_time = current_time
                    self.movement_attempts += 1

                    if self.movement_attempts > self.max_movement_attempts:
                        print(f"Too many movement attempts ({self.movement_attempts}), abandoning session")
                        self.abandon_current_session()
                        return False

        elif self.elevation_state == ElevationState.WAITING_ON_TILE:
            print("Waiting on tile for leader to start incantation")

            if current_time - self.last_ready_for_level_received > self.no_response_timeout:
                print("Leader inactive for too long, abandoning session")
                self.abandon_current_session()
                return False

        elif self.elevation_state == ElevationState.READY_TO_INCANT:
            if self.am_leader:
                print(f"I am the leader, dropping resources and starting incantation to level {self.player.level + 1}")
                if self.drop_resources_for_incantation():
                    self.elevation_state = ElevationState.INCANTING
                    success = self.player.cmd_incantation()
                    if success:
                        self.broadcast_elevation_complete()
                        self.reset_elevation_state()
                        return True
                    else:
                        print("Incantation failed, abandoning session")
                        self.abandon_current_session()
                        return False
            else:
                print("Waiting for leader to start incantation")

        return False

    def should_abandon_leadership(self):
        current_time = time.time()

        if self.player.inventory.food <= self.player.food_critical:
            print(f"Food critical ({self.player.inventory.food}), abandoning leadership")
            return True

        if (self.am_leader and 
            current_time - self.last_elevation_broadcast > 25.0 and
            len(self.confirmed_players) == 0):
            print("No players responding after 25 seconds of broadcasting")
            return True

        return False

    def has_reached_leader(self):
        current_players_on_tile = self.count_players_on_tile()
        required_players = self.player.items_needed.get("players", 1)
        total_players = current_players_on_tile

        if total_players >= required_players:
            print(f"Reached leader! {total_players} players on tile (required: {required_players})")
            return True
        return False

    def move_towards_leader(self):
        if self.movement_direction is None:
            return False

        if self.has_reached_leader():
            print("Reached leader successfully!")
            return True

        success = self.make_efficient_movement(self.movement_direction)

        if success:
            print(f"Made movement towards direction {self.movement_direction} (attempt {self.movement_attempts})")
        else:
            print(f"Failed to move towards direction {self.movement_direction}")

        return False

    def make_efficient_movement(self, direction):
        if direction == 0:  # Même tile
            return True
        elif direction == 1:  # Nord
            return self.player.cmd_forward()
        elif direction == 2:  # Nord-Est
            success = self.player.cmd_forward()
            if success and self.movement_attempts % 3 == 0:
                self.player.cmd_right()
            return success
        elif direction == 3:  # Est
            success = self.player.cmd_right()
            if success:
                success = self.player.cmd_forward()
            return success
        elif direction == 4:  # Sud-Est
            success = self.player.cmd_right()
            if success:
                success = self.player.cmd_forward()
                if success and self.movement_attempts % 3 == 0:
                    self.player.cmd_right()
            return success
        elif direction == 5:  # Sud
            success = self.player.cmd_right()
            if success:
                success = self.player.cmd_right()
                if success:
                    success = self.player.cmd_forward()
            return success
        elif direction == 6:  # Sud-Ouest
            success = self.player.cmd_left()
            if success:
                success = self.player.cmd_forward()
                if success and self.movement_attempts % 3 == 0:
                    self.player.cmd_left()
            return success
        elif direction == 7:  # Ouest
            success = self.player.cmd_left()
            if success:
                success = self.player.cmd_forward()
            return success
        elif direction == 8:  # Nord-Ouest
            success = self.player.cmd_forward()
            if success and self.movement_attempts % 3 == 0:
                self.player.cmd_left()
            return success
        return False

    def should_continue_broadcasting(self):
        current_time = time.time()

        if not self.continuous_broadcast:
            return False

        if self.am_leader:
            if self.player.inventory.food <= self.player.food_critical:
                print(f"Food level critical ({self.player.inventory.food}), stopping leadership broadcast")
                self.continuous_broadcast = False
                self.abandon_current_session()
                return False

            required_players = self.player.items_needed.get("players", 1)
            current_players_on_tile = self.count_players_on_tile()
            total_players = current_players_on_tile
            
            if total_players >= required_players:
                print(f"Enough players on tile ({total_players}/{required_players}), stopping broadcast")
                self.continuous_broadcast = False
                self.elevation_state = ElevationState.READY_TO_INCANT
                return False

        if current_time - self.last_elevation_broadcast >= self.broadcast_cooldown:
            return True

        return False

    def reset_elevation_state(self):
        print("Resetting elevation state to COLLECTING")
        self.elevation_state = ElevationState.COLLECTING
        self.current_leader = None
        self.leader_direction = None
        self.movement_direction = None
        self.confirmed_players.clear()
        self.dropped_resources.clear()
        self.am_leader = False
        self.continuous_broadcast = False
        self.moving_to_leader = False
        self.coming_broadcast_active = False
        self.broadcast_message_template = None
        self.last_ready_for_level_received = 0
        self.ready_for_level_count = 0
        self.leader_timeout = 0
        self.movement_attempts = 0
        self.last_movement_time = 0

    def player_has_required_resources(self):
        missing = self.player.has_missing_resources()
        if missing:
            print(f"Player is missing resources: {missing}")
            return False
        print("Player has all required resources")
        return True

    def send_coming_response(self, level):
        message = f"i_am_coming_{level}"
        if self.player.cmd_broadcast(message):
            print(f"Sent coming response: {message}")
            return True
        return False

    def count_players_on_tile(self):
        look_data = self.player.cmd_look()
        current_tile_content = look_data.get(0, [])
        player_count = current_tile_content.count('player')
        print(f"Players on current tile: {player_count}")
        return player_count

    def start_leadership_broadcast(self):
        if not self.can_become_leader():
            print("Cannot become leader, conditions not met")
            return False

        print("Starting leadership broadcast process")
        self.am_leader = True
        self.confirmed_players.clear()
        self.continuous_broadcast = True
        self.broadcast_message_template = f"ready_for_level_{self.player.level}"
        self.elevation_state = ElevationState.BROADCASTING

        if self.player.cmd_broadcast(self.broadcast_message_template):
            self.last_broadcast_time = time.time()
            self.last_elevation_broadcast = time.time()
            print(f"Started continuous leadership broadcast: {self.broadcast_message_template}")
            return True
        else:
            print("Failed to send initial leadership broadcast")
            self.reset_elevation_state()
            return False

    def drop_resources_for_incantation(self):
        try:
            print("Dropping resources for incantation...")
            for item, required in self.player.items_needed.items():
                if item != "players":
                    dropped_count = 0
                    current_amount = getattr(self.player.inventory, item, 0)
                    to_drop = min(required, current_amount)

                    for _ in range(to_drop):
                        if self.player.cmd_set(item):
                            dropped_count += 1
                        else:
                            print(f"Failed to drop {item}")
                            return False

                    self.dropped_resources[item] = dropped_count
                    print(f"Dropped {dropped_count} {item} (required: {required})")

            print("All resources dropped successfully")
            return True
        except Exception as e:
            print(f"Error dropping resources: {e}")
            return False

    def recover_dropped_resources(self):
        print("Recovering dropped resources after failed incantation")
        for item, count in self.dropped_resources.items():
            for _ in range(count):
                if self.player.cmd_take(item):
                    print(f"Recovered {item}")
                else:
                    print(f"Failed to recover {item}")
        self.dropped_resources.clear()
        self.reset_elevation_state()

    def broadcast_elevation_complete(self):
        message = f"elevation_complete_{self.player.level}"
        if self.player.cmd_broadcast(message):
            print(f"Broadcasted elevation complete: {message}")
            return True
        return False
