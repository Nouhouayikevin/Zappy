##
## EPITECH PROJECT, 2025
## B-YEP-400-COT-4-1-zappy-julcinia.oke
## File description:
## message
##

import threading
import queue
import time
import select
import socket
from enum import Enum

class MessageType(Enum):
    COMMAND_RESPONSE = "command_response"
    BROADCAST = "broadcast"
    NOTIFICATION = "notification"

class Message:
    def __init__(self, message_type, content, timestamp=None):
        self.type = message_type
        self.content = content
        self.timestamp = timestamp or time.time()

class MessageHandler:
    def __init__(self, socket_obj):
        self.socket = socket_obj
        self.running = False
        self.receive_thread = None
        self.disconnected = False

        self.command_responses = queue.Queue()
        self.broadcasts = queue.Queue()
        self.notifications = queue.Queue()

        self.buffer = ""
        self.lock = threading.Lock()

        self.broadcast_callback = None

    def start(self):
        if not self.running:
            self.running = True
            self.receive_thread = threading.Thread(target=self.receive_loop, daemon=True)
            self.receive_thread.start()
            print("MessageHandler started")

    def stop(self):
        self.running = False
        if self.receive_thread:
            self.receive_thread.join(timeout=1.0)
        print("MessageHandler stopped")

    def set_broadcast_callback(self, callback):
        self.broadcast_callback = callback

    def receive_loop(self):
        while self.running:
            try:
                ready, _, error = select.select([self.socket], [], [self.socket], 0.1)
                if error:
                    print("Socket error detected")
                    break
                if ready:
                    data = self.socket.recv(1024).decode('utf-8')
                    if not data:
                        print("Server closed connection")
                        self.disconnected = True
                        break
                    with self.lock:
                        self.buffer += data
                        self.process_buffer()
            except socket.error as e:
                print(f"Socket error in receive loop: {e}")
                self.disconnected = True
                break
            except Exception as e:
                print(f"Unexpected error in receive loop: {e}")
                self.disconnected = True
                break

    def process_buffer(self):
        while '\n' in self.buffer:
            line, self.buffer = self.buffer.split('\n', 1)
            line = line.strip()

            if line:
                message_type, content = self.classify_message(line)
                message = Message(message_type, content)
                self.route_message(message)

    def classify_message(self, line):
        if line.startswith("message "):
            return MessageType.BROADCAST, line
        elif any(keyword in line.lower() for keyword in ["dead", "current level", "eject", "incantation"]):
            return MessageType.NOTIFICATION, line
        else:
            return MessageType.COMMAND_RESPONSE, line
    
    def route_message(self, message):
        if message.type == MessageType.BROADCAST:
            self.broadcasts.put(message)
            if self.broadcast_callback:
                threading.Thread(target=self.handle_broadcast, args=(message,), daemon=True).start()
        elif message.type == MessageType.NOTIFICATION:
            self.notifications.put(message)
            print(f"[NOTIFICATION] {message.content}")
            if "dead" in message.content.lower():
                self.disconnected = True
        elif message.type == MessageType.COMMAND_RESPONSE:
            self.command_responses.put(message)

    def handle_broadcast(self, message):
        try:
            self.broadcast_callback(message.content)
        except Exception as e:
            print(f"Error handling broadcast: {e}")

    def wait_for_command_response(self, timeout=10.0):
        try:
            message = self.command_responses.get(timeout=timeout)
            return message.content
        except queue.Empty:
            raise TimeoutError(f"No command response received within {timeout} seconds")

    def get_broadcast(self, timeout=0.1):
        try:
            message = self.broadcasts.get(timeout=timeout)
            return message.content
        except queue.Empty:
            return None

    def get_notification(self, timeout=0.1):
        try:
            message = self.notifications.get(timeout=timeout)
            return message.content
        except queue.Empty:
            return None

    def is_connected(self):
        return not self.disconnected and self.running
