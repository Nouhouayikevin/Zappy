# 🎮 Zappy - Multi-Platform Networked Game Engine

<div align="center">

![Zappy Logo](https://img.shields.io/badge/Zappy-Game%20Engine-667eea?style=for-the-badge&logo=gamemaker&logoColor=white)

[![Language C](https://img.shields.io/badge/Server-C-00599C?style=flat-square&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Language Python](https://img.shields.io/badge/AI-Python-3776AB?style=flat-square&logo=python&logoColor=white)](https://python.org)
[![Language C++](https://img.shields.io/badge/GUI-C++-00599C?style=flat-square&logo=cplusplus&logoColor=white)](https://isocpp.org)
[![Raylib](https://img.shields.io/badge/Graphics-Raylib-FF6B6B?style=flat-square&logo=raylib&logoColor=white)](https://raylib.com)

*A sophisticated networked game engine showcasing advanced concepts in network programming, artificial intelligence, and real-time graphics rendering*

[🎯 Overview](#-overview) • [🚀 Quick Start](#-quick-start) • [🔧 Components](#-components) • [📖 Documentation](#-documentation) • [🎮 Usage](#-usage)

</div>

---

## 🎯 Overview

**Zappy** is an ambitious multi-component game engine developed as part of the Epitech curriculum. It demonstrates mastery of various advanced programming concepts including network protocols, artificial intelligence, 3D graphics, and system architecture across multiple programming languages.

### 🎮 Game Concept

Zappy simulates a competitive survival environment where AI-controlled players (Trantorians) must:
- 🔍 **Explore** a dynamic 2D world
- 📦 **Collect** seven types of resources
- 🤝 **Collaborate** within teams
- 📈 **Level up** through complex incantation ceremonies
- 🏆 **Compete** for ultimate dominance

### ✨ Key Features

- 🏗️ **Multi-language Architecture**: C server, Python AI, C++ GUI
- 🌐 **Real-time Networking**: Custom TCP protocol with efficient message handling
- 🤖 **Advanced AI Behaviors**: Team coordination, strategic planning, adaptive learning
- 🎨 **Beautiful 3D Visualization**: Raylib-powered graphics with smooth animations
- 💎 **Complex Resource Economy**: Seven distinct resource types with strategic value
- 🎭 **Team Dynamics**: Collaborative elevation ceremonies and broadcast systems
- ⚙️ **Highly Configurable**: Scalable world sizes and team configurations

---

## 🚀 Quick Start

### 📋 Prerequisites

```bash
# System Requirements
- Linux (Ubuntu 18.04+, Mint, Fedora, etc.)
- GCC/G++ compiler
- Make build system
- Python 3.8+
- Git

# For GUI component
- Raylib 4.0+ library
- OpenGL support
```

### ⚡ Installation

```bash
# 1. Clone the repository
git clone git@github.com:Nouhouayikevin/Zappy.git zappy
cd zappy

# 2. Install Raylib (required for GUI)
git clone --depth 1 https://github.com/raysan5/raylib.git raylib
cd raylib/src/
make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED
sudo make install RAYLIB_LIBTYPE=SHARED
cd ../..

# 3. Build all components
make all

# 4. Verify installation
ls -la zappy_server zappy_ai zappy_gui
```

### 🎯 Launch a Game Session

```bash
# Terminal 1: Start the server
./zappy_server -p 4242 -x 20 -y 20 -n red blue green -c 5 -f 100

# Terminal 2: Launch GUI (recommended)
./zappy_gui -p 4242 -h localhost

# Terminal 3-5: Connect AI players
./zappy_ai -p 4242 -n red &
./zappy_ai -p 4242 -n blue &
./zappy_ai -p 4242 -n green &
```

---

## 🔧 Components

<table>
<tr>
<td width="33%" align="center">

### 🖥️ **Zappy Server**
**Language:** C  
**Role:** Core Game Engine

- World generation & simulation
- Player lifecycle management  
- Command processing & validation
- Real-time state synchronization
- Physics simulation
- Resource distribution algorithms

</td>
<td width="33%" align="center">

### 🤖 **AI Client**
**Language:** Python 3  
**Role:** Intelligent Game Agents

- Advanced pathfinding algorithms
- Resource collection strategies
- Team coordination protocols
- Elevation ceremony management
- Broadcast communication system
- Adaptive behavior patterns

</td>
<td width="33%" align="center">

### 🎨 **GUI Visualizer**
**Language:** C++ with Raylib  
**Role:** Real-time 3D Visualization

- Dynamic 3D world rendering
- Smooth player animations
- Resource visualization
- Real-time statistics dashboard
- Interactive camera controls
- Immersive audio feedback

</td>
</tr>
</table>

### 🔄 System Architecture

```
┌─────────────┐    TCP    ┌─────────────┐    TCP    ┌─────────────┐
│             │◄─────────►│             │◄─────────►│             │
│ AI Clients  │ Commands  │   Server    │Game State │  GUI Client │
│  (Python)   │Responses  │     (C)     │ Updates   │    (C++)    │
└─────────────┘           └─────────────┘           └─────────────┘
                                 │
                                 ▼
                          ┌─────────────┐
                          │ World State │
                          │ Management  │
                          └─────────────┘
```

---

## 📖 Documentation

### 🗺️ World Resources

| Resource | Icon | Purpose | Rarity |
|----------|------|---------|--------|
| **Food** | 🍕 | Essential for survival - consumed over time | Common |
| **Linemate** | 💎 | Basic mineral for early level advancement | Common |
| **Deraumere** | 🔶 | Precious stone for mid-level incantations | Uncommon |
| **Sibur** | 🔷 | Rare crystal for advanced ceremonies | Rare |
| **Mendiane** | 🟢 | Mystical gem for high-level transformations | Rare |
| **Phiras** | 🔮 | Ancient artifact for master-level rituals | Very Rare |
| **Thystame** | ⭐ | Legendary material for ultimate elevation | Legendary |

### 📈 Level Progression System

```
Level 1 → 2: 1 player,  1 linemate
Level 2 → 3: 2 players, 1 linemate, 1 deraumere, 1 sibur
Level 3 → 4: 2 players, 2 linemate, 1 deraumere, 1 sibur, 2 phiras
Level 4 → 5: 4 players, 1 linemate, 1 deraumere, 2 sibur, 1 mendiane
Level 5 → 6: 4 players, 1 linemate, 2 deraumere, 1 sibur, 3 mendiane
Level 6 → 7: 6 players, 1 linemate, 2 deraumere, 3 sibur, 1 phiras
Level 7 → 8: 6 players, 2 linemate, 2 deraumere, 2 sibur, 2 mendiane, 2 phiras, 1 thystame
```

---

## 🎮 Usage

### 🖥️ Server Commands

```bash
./zappy_server -p [port] -x [width] -y [height] -n [teams...] -c [clients] -f [frequency]
```

**Parameters:**
- `-p port`: Network port (1024-65535)
- `-x width`: World width in tiles (minimum 10)
- `-y height`: World height in tiles (minimum 10)  
- `-n teams`: Space-separated team names
- `-c clients`: Maximum clients per team
- `-f frequency`: Game speed/frequency (default: 100)

**Example:**
```bash
./zappy_server -p 4242 -x 25 -y 25 -n warriors mages rogues -c 6 -f 150
```

### 🤖 AI Client Commands

```bash
./zappy_ai -p [port] -n [team_name] -h [hostname]
```

**Parameters:**
- `-p port`: Server port number
- `-n name`: Team name (must exist on server)
- `-h machine`: Server hostname (default: localhost)

**Example:**
```bash
./zappy_ai -p 4242 -n warriors -h localhost
```

### 🎨 GUI Commands

```bash
./zappy_gui -p [port] -h [hostname]
```

**Parameters:**
- `-p port`: Server port number
- `-h machine`: Server hostname (default: localhost)

**Example:**
```bash
./zappy_gui -p 4242 -h localhost
```

---

## 🎯 AI Player Commands

| Command | Category | Description |
|---------|----------|-------------|
| `Forward` | Movement | Move one tile forward |
| `Left` | Movement | Rotate 90° counter-clockwise |
| `Right` | Movement | Rotate 90° clockwise |
| `Look` | Perception | Examine surrounding tiles |
| `Inventory` | Perception | Check personal resources |
| `Take [resource]` | Interaction | Pick up resource from tile |
| `Set [resource]` | Interaction | Drop resource on tile |
| `Broadcast [msg]` | Communication | Send directional message |
| `Incantation` | Advanced | Initiate level-up ceremony |
| `Fork` | Advanced | Create new team member |
| `Eject` | Advanced | Expel players from tile |

---

## 🛠️ Development

### 📁 Project Structure

```
zappy/
├── 🖥️ Serveur/          # C server implementation
│   ├── src/             # Source files
│   ├── include/         # Header files
│   └── Makefile         # Build configuration
├── 🤖 AI/               # Python AI client
│   ├── main.py          # Entry point
│   ├── player.py        # Core AI logic
│   ├── server.py        # Network communication
│   └── Makefile         # Build configuration
├── 🎨 GUI/              # C++ GUI with Raylib
│   ├── src/             # Source files
│   ├── include/         # Header files
│   ├── ressources/      # 3D models, textures, audio
│   └── Makefile         # Build configuration
├── 📄 Makefile          # Main build file
└── 📋 requirements.txt  # Dependencies
```

### 🔨 Build Commands

```bash
# Build all components
make all

# Build individual components
make SERVER    # Build zappy_server
make AI        # Build zappy_ai  
make GUI       # Build zappy_gui

# Clean build files
make clean

# Full clean (remove executables)
make fclean

# Rebuild everything
make re
```

---

## 🏆 Victory Conditions

The game continues until one team achieves dominance through:

- 🎯 **Level Mastery**: Having 6 players reach maximum level (Level 8)
- 👑 **Strategic Control**: Dominating high-level positions
- 💎 **Resource Monopoly**: Effective resource management and denial

---

## 🤝 Team Coordination Features

- 📡 **Directional Broadcast System**: Smart messaging with spatial awareness
- 🎯 **Resource Sharing Protocols**: Strategic resource distribution
- 🎭 **Elevation Ceremonies**: Coordinated multi-player rituals
- 👑 **Dynamic Leadership**: Emergent leadership for complex operations
- 🧭 **Intelligent Pathfinding**: Advanced navigation algorithms
- 🧠 **Behavior Trees**: Complex AI state management

---

## 🎓 Educational Value

This project demonstrates mastery of:

- **Network Programming**: Socket programming, protocol design, concurrent connections
- **Artificial Intelligence**: Behavior trees, state machines, multi-agent coordination  
- **Graphics Programming**: 3D rendering, animation systems, real-time visualization
- **System Architecture**: Multi-component design, inter-process communication
- **Software Engineering**: Clean code, documentation, testing, version control

---

## 👥 Team

This project was crafted by a talented team of Epitech students, each bringing their unique expertise:

<div align="center">

| 👤 Developer | 🎯 Role | 📧 Contact |
|--------------|---------|-----------|
| **Kevin Nouhouayi** | 🎨 Graphics & Rendering Lead | [kevin.nouhouayi@epitech.eu](mailto:kevin.nouhouayi@epitech.eu) |
| **Joseph Behanzin** | 🌐 Network Architecture Lead & Graphics (GUI) | [joseph.behanzin@epitech.eu](mailto:joseph.behanzin@epitech.eu) |
| **Julcinia Oke** | 🤖 AI Development | [julcinia.oke@epitech.eu](mailto:julcinia.oke@epitech.eu) |
| **Bill Adjagboni** | 🤖 AI Development | [bill.adjagboni@epitech.eu](mailto:bill.adjagboni@epitech.eu) |
| **Ramdon Ogouyomi** | 🖥️ Server Development | [ramdon.ogouyomi@epitech.eu](mailto:ramdon.ogouyomi@epitech.eu) |
| **Tobi Agongbonon** | 🖥️ Server Development | [tobi.agongbonon@epitech.eu](mailto:tobi.agongbonon@epitech.eu) |

</div>

### 🎯 Contributions Breakdown

<table>
<tr>
<td width="33%" align="center">

#### 🎨 Graphics Team
**Kevin Nouhouayi**
- 3D Rendering Pipeline
- Custom Shaders
- Animation System
- Visual Effects

**Joseph Behanzin**
- Network Protocol (GUI)
- Client-Server Communication
- Real-time Data Sync

</td>
<td width="33%" align="center">

#### 🤖 AI Team
**Julcinia Oke & Bill Adjagboni**
- AI Logic & Behavior
- State Machine Design
- Team Coordination
- Pathfinding Algorithms
- Resource Management
- Strategic Planning

</td>
<td width="33%" align="center">

#### 🖥️ Server Team
**Ramdon Ogouyomi & Tobi Agongbonon**
- Core Game Engine
- World Generation
- Command Processing
- Network Protocol
- Player Management
- Resource Distribution

</td>
</tr>
</table>

---

## 📜 License & Copyright

<div align="center">

### 🔒 Copyright Notice

```
Copyright © 2025 Zappy Development Team
All Rights Reserved

This project and its source code are protected under educational use.
Unauthorized copying, distribution, or modification is prohibited
without explicit permission from the development team.
```

### 📋 License Information

This project was developed as part of the **Epitech curriculum** (B-YEP-400) and is intended for **educational purposes only**.

**Permitted Use:**
- ✅ Viewing and studying the code for educational purposes
- ✅ Forking for personal learning and experimentation
- ✅ Citing in academic work with proper attribution

**Prohibited Use:**
- ❌ Commercial use without permission
- ❌ Plagiarism or claiming as original work
- ❌ Redistribution without attribution

**Attribution Required:**
When referencing this project, please cite:
```
Zappy Simulator Engine (2025)
Developed by: K. Nouhouayi, J. Behanzin, J. Oke, B. Adjagboni, R. Ogouyomi, T. Agongbonon
Institution: Epitech
Repository: https://github.com/Nouhouayikevin/Zappy
```

</div>

---

## 🌟 Acknowledgments

Special thanks to:
- **Epitech** for the project framework and educational support
- **Raylib Community** for the excellent graphics library
- **Open Source Contributors** whose tools made this project possible

---

<div align="center">

### 🚀 Built with Passion and Code

![Made with Love](https://img.shields.io/badge/Made%20with-❤️-red?style=for-the-badge)
![Epitech](https://img.shields.io/badge/Epitech-2025-blue?style=for-the-badge)
![Team](https://img.shields.io/badge/Team-6%20Developers-green?style=for-the-badge)

**Technologies:** C • Python • C++ • Raylib • OpenGL • TCP/IP • Network Programming • AI Development

---

**© 2025 Zappy Development Team | Epitech Project**

*Crafted with dedication, debugged with patience, deployed with pride* ✨

[⬆ Back to Top](#-zappy---multi-platform-networked-game-engine)

</div>
