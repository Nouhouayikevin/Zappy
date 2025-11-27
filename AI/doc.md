# Documentation Complète - Zappy AI

## Vue d'ensemble du projet

Zappy AI est un client intelligent pour le jeu Zappy, un jeu multijoueur où des agents autonomes évoluent dans un monde 2D pour collecter des ressources, survivre et monter de niveau à travers des rituels d'incantation collaborative.

## Architecture générale

Le programme est structuré en plusieurs modules interconnectés :

- **main.py** : Point d'entrée du programme
- **player.py** : Logique principale de l'IA
- **broadcast.py** : Gestion des communications entre joueurs
- **server.py** : Interface réseau avec le serveur
- **message.py** : Gestionnaire de messages asynchrones
- **parsers.py** : Analyseurs de commandes et réponses
- **usage.py** : Affichage de l'aide

---

## Module main.py

### Fonction `main()`
**Rôle** : Point d'entrée principal du programme.

**Fonctionnement** :
1. Vérifie si l'utilisateur demande l'aide (`--help`)
2. Crée une instance de `Player`
3. Parse les arguments de ligne de commande
4. Établit la connexion au serveur
5. Lance la logique de l'IA
6. Gère les exceptions (interruption clavier, erreurs)

**Gestion d'erreurs** :
- Interruption clavier (Ctrl+C) : déconnexion propre
- Exceptions générales : déconnexion et sortie avec code d'erreur 84

---

## Module usage.py

### Fonction `usage()`
**Rôle** : Affiche l'aide d'utilisation du programme.

**Format attendu** :
```
./zappy_ai -p port -n name -h machine
```

**Paramètres** :
- `-p port` : Numéro de port du serveur
- `-n name` : Nom de l'équipe
- `-h machine` : Adresse du serveur (localhost par défaut)

---

## Module parsers.py

### Classe `Arguments`
**Rôle** : Structure de données pour stocker les arguments parsés.

**Attributs** :
- `port` : Numéro de port (obligatoire)
- `name` : Nom de l'équipe (obligatoire)
- `machine` : Adresse du serveur (défaut: "localhost")

### Classe `Response_parser`
**Rôle** : Parse les réponses du serveur en structures de données utilisables.

#### Méthode `__init__()`
**Rôle** : Initialise la liste des ressources disponibles dans le jeu.

#### Méthode `parse_look(response)`
**Rôle** : Parse la réponse de la commande "Look" qui décrit l'environnement visible.

**Entrée** : Chaîne au format `[tile0,tile1,tile2,...]`

**Sortie** : Dictionnaire `{index_tile: [liste_objets]}`

**Exemple** :
```python
# Entrée: "[player food, linemate, , food player]"
# Sortie: {0: ['player', 'food'], 1: ['linemate'], 2: [], 3: ['food', 'player']}
```

#### Méthode `parse_inventory(response)`
**Rôle** : Parse l'inventaire du joueur.

**Entrée** : Chaîne au format `[food 10, linemate 2, ...]`

**Sortie** : Dictionnaire `{objet: quantité}`

#### Méthode `parse_broadcast(response)`
**Rôle** : Parse les messages de diffusion reçus d'autres joueurs.

**Entrée** : `"message direction,contenu_message"`

**Sortie** : `{"direction": int, "message": str}` ou `None` si erreur

### Fonction `parser_arg(argv)`
**Rôle** : Parse les arguments de ligne de commande.

**Validations** :
- Vérification du nombre d'arguments minimum
- Validation du port (1-65535)
- Vérification que le nom d'équipe n'est pas vide
- Options obligatoires : `-p` et `-n`

**Sortie** : Instance d'`Arguments` ou exit(84) en cas d'erreur

---

## Module message.py

### Énumération `MessageType`
**Rôle** : Définit les types de messages possibles.

**Valeurs** :
- `COMMAND_RESPONSE` : Réponse à une commande
- `BROADCAST` : Message diffusé par un autre joueur
- `NOTIFICATION` : Notification du serveur (mort, niveau, etc.)

### Classe `Message`
**Rôle** : Encapsule un message avec son type et timestamp.

**Attributs** :
- `type` : Type de message (MessageType)
- `content` : Contenu du message
- `timestamp` : Horodatage de réception

### Classe `MessageHandler`
**Rôle** : Gestionnaire asynchrone des messages entrants du serveur.

#### Méthode `__init__(socket_obj)`
**Rôle** : Initialise le gestionnaire avec trois queues séparées pour chaque type de message.

#### Méthode `start()`
**Rôle** : Lance le thread de réception des messages.

#### Méthode `stop()`
**Rôle** : Arrête proprement le thread de réception.

#### Méthode `receive_loop()`
**Rôle** : Boucle principale de réception des données du serveur.

**Fonctionnement** :
1. Utilise `select()` pour une réception non-bloquante
2. Accumule les données dans un buffer
3. Traite les messages ligne par ligne
4. Gère les erreurs de socket

#### Méthode `process_buffer()`
**Rôle** : Traite le buffer accumulé pour extraire les messages complets.

#### Méthode `classify_message(line)`
**Rôle** : Détermine le type d'un message selon son contenu.

**Règles de classification** :
- Commence par "message " → BROADCAST
- Contient "dead", "current level", etc. → NOTIFICATION
- Autre → COMMAND_RESPONSE

#### Méthode `route_message(message)`
**Rôle** : Dirige chaque message vers la queue appropriée.

#### Méthode `wait_for_command_response(timeout=5.0)`
**Rôle** : Attend une réponse de commande avec timeout.

**Lève** : `TimeoutError` si pas de réponse dans le délai

---

## Module server.py

### Classe `ZappySocketAsync`
**Rôle** : Interface de communication avec le serveur Zappy.

#### Méthode `__init__(hostname, port, team_name)`
**Rôle** : Initialise les paramètres de connexion.

#### Méthode `connect()`
**Rôle** : Établit la connexion et effectue l'authentification.

**Protocole de connexion** :
1. Connexion TCP au serveur
2. Réception du message "WELCOME"
3. Envoi du nom d'équipe
4. Réception du nombre de slots disponibles
5. Réception des dimensions du monde
6. Initialisation du gestionnaire de messages

**Retour** : `True` si succès, `False` sinon

#### Méthode `disconnect()`
**Rôle** : Ferme proprement la connexion.

#### Méthode `send_command(command)`
**Rôle** : Envoie une commande et attend la réponse.

**Fonctionnement** :
1. Envoie la commande avec '\n'
2. Utilise le MessageHandler pour attendre la réponse
3. Gère les timeouts et erreurs de socket

#### Méthode `set_broadcast_handler(handler_func)`
**Rôle** : Définit le callback pour traiter les broadcasts reçus.

---

## Module player.py

### Classe `Position`
**Rôle** : Structure pour les coordonnées (non utilisée dans le code actuel).

### Classe `Inventory`
**Rôle** : Représente l'inventaire du joueur.

**Attributs** :
- `food` : Nourriture (essentielle pour la survie)
- `linemate`, `deraumere`, `sibur`, `mendiane`, `phiras`, `thystame` : Ressources pour les incantations

#### Méthode `update_from_dict(data)`
**Rôle** : Met à jour l'inventaire depuis un dictionnaire.

### Constante `LEVEL_REQUIREMENTS`
**Rôle** : Définit les ressources nécessaires pour chaque niveau d'élévation.

**Structure** : Index = niveau actuel, valeur = ressources pour passer au niveau suivant

### Classe `SurvivalState`
**Rôle** : États de survie basés sur le niveau de nourriture.

**États** :
- `EMERGENCY` : ≤ 5 nourriture - Abandon de toute activité
- `CRITICAL` : ≤ 8 nourriture - Priorité absolue à la nourriture
- `LOW` : ≤ 12 nourriture - Intégration de recherche de nourriture
- `SAFE` : > 15 nourriture - Fonctionnement normal

### Classe `Player`
**Rôle** : Contrôleur principal de l'IA.

#### Méthode `__init__()`
**Rôle** : Initialise tous les systèmes du joueur.

**Systèmes initialisés** :
- État de survie et seuils de nourriture
- Stratégie d'exploration (spirale)
- État d'élévation
- Statistiques et métriques

#### Méthode `connection(hostname, port, team_name)`
**Rôle** : Établit la connexion et initialise les managers.

**Séquence** :
1. Création de `ZappySocketAsync`
2. Connexion au serveur
3. Initialisation du `BroadcastManager`
4. Configuration du callback de broadcast
5. Récupération de l'inventaire initial

#### Méthode `start()`
**Rôle** : Boucle principale de l'IA.

**Condition d'arrêt** : Niveau 8 atteint ou mort du joueur

#### Méthode `update_survival_state()`
**Rôle** : Met à jour l'état de survie selon le niveau de nourriture.

#### Méthode `run_ai_logic()`
**Rôle** : Logique principale de décision de l'IA.

**Priorités (par ordre décroissant)** :
1. **EMERGENCY** : Recherche intensive de nourriture uniquement
2. **CRITICAL** : Priorité absolue à la nourriture
3. **LOW** : Recherche intégrée de nourriture
4. Fork si nécessaire pour les niveaux futurs
5. Gestion du processus d'élévation
6. Recherche de ressources

#### Méthode `should_fork()`
**Rôle** : Détermine s'il faut créer un œuf pour augmenter l'équipe.

**Conditions** :
- Niveau nécessitant plusieurs joueurs (4, 5, 6, 7)
- Pas assez de joueurs disponibles
- Nombre de slots de connexion insuffisant

#### Méthode `resource_search()`
**Rôle** : Recherche et collecte des ressources nécessaires.

**Algorithme** :
1. Observation de l'environnement (`cmd_look`)
2. Identification des cibles (ressources manquantes)
3. Sélection de la meilleure cible (priorité + distance)
4. Déplacement vers la cible ou exploration

#### Méthode `find_resources(look_data)`
**Rôle** : Identifie les ressources intéressantes dans l'environnement.

**Logique de priorité** :
- Nourriture : priorité selon l'état de survie
- Ressources manquantes : priorité élevée (200)
- Collecte immédiate sur la case actuelle

#### Méthode `is_priority(item, missing_resources)`
**Rôle** : Calcule la priorité d'un objet.

**Barème de priorité** :
- Nourriture en EMERGENCY : 1000
- Nourriture en CRITICAL : 500
- Nourriture en LOW : 100
- Ressources manquantes : 200
- Nourriture normale : 10

#### Méthode `choose_target(targets)`
**Rôle** : Sélectionne la meilleure cible parmi les options.

**Critères** : Priorité décroissante, puis distance croissante

#### Méthode `distance(tile_index)`
**Rôle** : Calcule la distance relative d'une case.

#### Méthodes d'exploration
- `execute_exploration_strategy()` : Choisit la stratégie d'exploration
- `execute_spiral_movement()` : Mouvement en spirale croissante
- `execute_movement_strategy()` : Mouvement selon un pattern prédéfini

#### Méthodes de recherche de nourriture
- `emergency_food_search()` : Recherche désespérée de nourriture
- `urgent_food_search()` : Recherche prioritaire de nourriture
- `integrated_food_search()` : Collecte opportuniste

#### Méthode `move_towards_tile(tile_index)`
**Rôle** : Déplace le joueur vers une case spécifique.

**Mapping des cases** : Conversion index → séquence de mouvements

#### Méthodes de vérification d'incantation
- `check_incantation_prerequisites()` : Vérifie toutes les conditions
- `has_missing_resources()` : Identifie les ressources manquantes

#### Commandes du jeu (cmd_*)
**Rôle** : Interface avec le serveur pour les actions du jeu.

**Commandes disponibles** :
- `cmd_take(obj_name)` : Ramasser un objet
- `cmd_set(obj_name)` : Poser un objet
- `cmd_incantation()` : Lancer une incantation
- `cmd_fork()` : Créer un œuf
- `cmd_eject()` : Éjecter les joueurs de la case
- `cmd_broadcast(message)` : Diffuser un message
- `cmd_connect_nbr()` : Nombre de slots de connexion
- `cmd_inventory()` : Obtenir l'inventaire
- `cmd_look()` : Observer l'environnement
- `cmd_forward()`, `cmd_left()`, `cmd_right()` : Mouvements

---

## Module broadcast.py

### Classe `ElevationState`
**Rôle** : États du processus d'élévation collaborative.

**États** :
- `COLLECTING` : Collecte des ressources
- `BROADCASTING` : Diffusion en tant que leader
- `WAITING_RESPONSES` : Attente des réponses des joueurs
- `MOVING_TO_LEADER` : Déplacement vers le leader
- `WAITING_ON_TILE` : Attente sur la case du leader
- `READY_TO_INCANT` : Prêt pour l'incantation
- `INCANTING` : En cours d'incantation

### Classe `BroadcastManager`
**Rôle** : Gère toute la communication et coordination entre joueurs.

#### Méthode `__init__(player)`
**Rôle** : Initialise tous les systèmes de communication.

**Paramètres importants** :
- `broadcast_cooldown` : 3s entre les broadcasts
- `response_timeout` : 15s pour attendre les réponses
- `no_response_timeout` : 10s sans signal du leader
- `max_movement_attempts` : 20 tentatives de mouvement maximum

#### Méthode `handle_broadcast(broadcast_message)`
**Rôle** : Point d'entrée pour tous les broadcasts reçus.

**Types de messages gérés** :
- `ready_for_level_X` : Appel du leader
- `i_am_coming_X` : Réponse d'un suiveur
- `session_full` : Session complète
- `elevation_complete` : Élévation terminée
- `session_abandoned` : Session abandonnée

#### Méthode `handle_leader_broadcast(direction, message)`
**Rôle** : Traite les appels de leadership.

**Logique de réponse** :
1. Vérification du niveau correspondant
2. Vérification de la disponibilité (état COLLECTING)
3. Envoi immédiat de la réponse `i_am_coming`
4. Transition vers MOVING_TO_LEADER
5. Initialisation du suivi du leader

#### Méthode `handle_coming_broadcast(direction, message)`
**Rôle** : Traite les réponses des suiveurs (côté leader).

**Fonctionnement** :
1. Enregistrement du joueur confirmé
2. Vérification du nombre de joueurs sur la case
3. Arrêt du broadcast si assez de joueurs

#### Méthode `manage_elevation_process()`
**Rôle** : Machine à états principale du processus d'élévation.

**Gestion des états** :
- **COLLECTING** : Vérification des conditions de leadership
- **BROADCASTING** : Diffusion continue d'appels
- **MOVING_TO_LEADER** : Navigation vers le leader
- **WAITING_ON_TILE** : Attente passive
- **READY_TO_INCANT** : Préparation de l'incantation

#### Méthodes de leadership
- `can_become_leader()` : Vérification des conditions de leadership
- `start_leadership_broadcast()` : Début de la diffusion d'appels
- `should_continue_broadcasting()` : Logique de continuation
- `should_abandon_leadership()` : Conditions d'abandon

#### Méthodes de suivi
- `move_towards_leader()` : Navigation vers le leader
- `move_towards_direction(direction)` : Conversion direction → mouvements
- `has_reached_leader()` : Vérification d'arrivée

#### Méthodes de gestion d'erreurs
- `check_leader_timeout()` : Détection de leader inactif
- `check_movement_progress()` : Détection de blocage de mouvement
- `abandon_current_session()` : Abandon propre de session

#### Méthodes d'incantation
- `drop_resources_for_incantation()` : Pose des ressources nécessaires
- `recover_dropped_resources()` : Récupération après échec
- `broadcast_elevation_complete()` : Notification de succès

#### Méthodes utilitaires
- `count_players_on_tile()` : Compte des joueurs sur la case actuelle
- `reset_elevation_state()` : Remise à zéro complète
- `should_abandon_due_to_food()` : Vérification des ressources critiques

---

## Flux de données et interactions

### Cycle de vie d'une élévation

1. **Phase de collecte** : Le joueur rassemble les ressources nécessaires
2. **Initiation du leadership** : Si conditions remplies, devient leader et diffuse
3. **Réponse des suiveurs** : Les autres joueurs répondent et se déplacent
4. **Convergence** : Les joueurs se rassemblent sur la case du leader
5. **Incantation** : Le leader pose les ressources et lance l'incantation
6. **Résolution** : Succès (niveau +1) ou échec (récupération des ressources)

### Gestion des erreurs et timeouts

- **Leader timeout** : Si pas de broadcast du leader pendant 10s
- **Movement timeout** : Si plus de 20 tentatives de mouvement
- **Food emergency** : Abandon immédiat si nourriture critique
- **Session abandonnée** : Flag temporaire de 15s pour éviter les boucles

### Stratégies d'exploration

- **Spirale** : Mouvement en spirale croissante pour couvrir efficacement la zone
- **Pattern fixe** : Séquence prédéfinie de mouvements

### Priorisation des ressources

Le système utilise un score de priorité pour optimiser la collecte :
- Urgence de survie (nourriture)
- Ressources manquantes pour l'élévation
- Proximité des ressources

## Points techniques importants

### Thread safety
- `MessageHandler` utilise des queues thread-safe
- Locks pour protéger le buffer de réception
- Callbacks exécutés dans des threads séparés

### Gestion des états
- Machine à états claire pour l'élévation
- États de survie basés sur des seuils de nourriture
- Transitions d'état explicites et documentées

### Robustesse
- Parsing défensif avec gestion des erreurs
- Timeouts sur toutes les opérations réseau
- Récupération automatique après échecs

### Optimisations
- Réutilisation des données de `look` pour éviter les appels redondants
- Broadcast conditionnel basé sur les cooldowns
- Algorithmes de pathfinding simples mais efficaces

Cette architecture modulaire permet une maintenance facile et des extensions futures du comportement de l'IA.
