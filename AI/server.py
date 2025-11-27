##
## EPITECH PROJECT, 2025
## B-YEP-400-COT-4-1-zappy-julcinia.oke
## File description:
## init
##

import socket
import select
from AI.message import MessageHandler

class ZappySocketAsync:
    def __init__(self, hostname, port, team_name):
        self.hostname = hostname
        self.port = port
        self.team_name = team_name
        self.socket = None
        self.connected = False
        self.client_num = 0
        self.world_width = 0
        self.world_height = 0
        self.message_handler = None
    
    def connect(self):
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect((self.hostname, self.port))

            welcome_msg = self.receiving()
            if not welcome_msg.startswith("WELCOME"):
                raise Exception(f"Expected WELCOME, got: {welcome_msg}")
            print(f"Server says: {welcome_msg}")

            self.sending(self.team_name)
            print(f"Sent team name: {self.team_name}")

            response = self.receiving()
            lines = response.split('\n')

            try:
                self.client_num = int(lines[0].strip())
                print(f"Available slots: {self.client_num}")
            except (ValueError, IndexError):
                raise Exception(f"Invalid client number in response: {response}")

            if len(lines) > 1:
                try:
                    dimensions = lines[1].strip().split()
                    if len(dimensions) != 2:
                        raise Exception(f"Invalid world dimensions format: {lines[1]}")
                    self.world_width = int(dimensions[0])
                    self.world_height = int(dimensions[1])
                    print(f"World size: {self.world_width} x {self.world_height}")
                except ValueError:
                    raise Exception(f"Invalid world dimensions: {lines[1]}")
            else:
                raise Exception("Missing world dimensions in server response")

            self.message_handler = MessageHandler(self.socket)
            self.message_handler.start()

            self.connected = True
            print("Successfully connected and authenticated!")
            return True

        except socket.error as e:
            print(f"Connection error: {e}")
            return False
        except Exception as e:
            print(f"Protocol error: {e}")
            return False

    def disconnect(self):
        if self.message_handler:
            self.message_handler.stop()
        if self.socket:
            self.socket.close()
            self.socket = None
        self.connected = False
        print("Disconnected from server")

    def sending(self, message):
        message = message + '\n'
        self.socket.send(message.encode())

    def receiving(self):
        data = ""
        while True:
            chunk = self.socket.recv(1024).decode()
            if not chunk:
                raise Exception("Server closed connection")
            data += chunk
            if '\n' in data:
                ready, _, _ = select.select([self.socket], [], [], 0.1)
                if not ready:
                    break
        return data.strip()

    def send_command(self, command):
        if not self.socket or not self.message_handler:
            raise Exception("Not connected to server")

        try:
            message = command + '\n'
            self.socket.send(message.encode())
            print(f"Sent: {command}")

            response = self.message_handler.wait_for_command_response()
            print(f"Received: {response}")
            return response

        except socket.error as e:
            print(f"Send error: {e}")
            self.connected = False
            raise
        except TimeoutError as e:
            print(f"Timeout error: {e}")
            raise

    def set_broadcast_handler(self, handler_func):
        if self.message_handler:
            self.message_handler.set_broadcast_callback(handler_func)

    def is_connected(self):
        return (self.connected and 
                self.socket is not None and 
                self.message_handler is not None and 
                self.message_handler.is_connected())
