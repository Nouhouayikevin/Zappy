/*
** EPITECH PROJECT, 2025
** B-NWP-400-COT-4-1-jetpack-joseph.behanzin
** File description:
** client
*/

#include "my.hpp"

template <typename T>
std::vector<T> map_to_vector(std::map<std::size_t, T> l) {
    std::vector<T> arr;

    for (auto &i : l)
        arr.push_back(i.second);
    return arr;
}

std::ostream & operator << (std::ostream &out, elem obj) {
    out << "Food: " << obj.food << "\nLinemate: " << obj.linemate
        << "\nDeraumere: " << obj.deraumere << "\nSibur: " <<
        obj.sibur << "\nMendiane: " << obj.mendiane << "\nphiras: " <<
        obj.phiras << "\nThystame: " << obj.thystame << std::endl;
    return out;
}

Client::Client(int port, std::string host) {
        _clientSock = socket(AF_INET, SOCK_STREAM, 0);

        // specifying address
        host = host == "localhost" ? "127.0.0.1" : host;
        port = !port || port < 0 ? 8080 : port;
        sockaddr_in serverAddress;
        memset(&serverAddress, 0, sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(port);
        // serverAddress.sin_addr.s_addr = INADDR_ANY;

        if (inet_pton(AF_INET, host.c_str(), &serverAddress.sin_addr) <= 0) {
            std::cerr << "Invalid Address" << std::endl;
            std::exit(84);
        }
        if (connect(_clientSock, (struct sockaddr*)&serverAddress,
            sizeof(serverAddress)) == -1) {
                std::cout << "Unable to Connect!\n" << std::endl;
                std::exit(0);
            }
        write(_clientSock, "GRAPHIC\n", 8);
        // close(_clientSock);
}

std::vector<std::string> split(const std::string &str, std::string delimiter) {
    std::vector<std::string> result;

    int end = -delimiter.size();
    do {
        auto start = end + delimiter.size();
        end = str.find(delimiter, start);
        result.push_back(str.substr(start, end - start));
    } while (end != -1);
    return result;
}

void Client::msz() {
    write(_clientSock, "msz\n", 4);
}

void Client::bct(std::size_t x, std::size_t y)
{
    std::string to_s = "bct ";

    to_s = std::to_string(x) + " " + std::to_string(y) + "\n";
    write(_clientSock, to_s.c_str(), to_s.size());
}

void Client::mct() {
    for (std::size_t x = 0; x < _map.size(); x++)
        for (std::size_t y = 0; y < _map[x].size(); y++)
            bct(x, y);
}

void Client::tna() {
    write(_clientSock, "tna\n", 4);
}

void Client::ppo(std::size_t id) {
    std::string l = "ppo ";

    l += std::to_string(id) + "\n";
    write(_clientSock, l.c_str(), l.size());
}

void Client::plv(std::size_t id) {
    std::string l = "plv ";

    l += std::to_string(id) + "\n";
    write(_clientSock, l.c_str(), l.size());
}

void Client::pin(std::size_t id) {
    std::string l = "pin ";

    l += std::to_string(id) + "\n";
    write(_clientSock, l.c_str(), l.size());
}

void Client::sgt() {
    write(_clientSock, "sgt\n", 4);
}

void Client::sst(float T) {
    std::string l = "sst ";

    l += std::to_string(T) + "\n";
    write(_clientSock, l.c_str(), l.size());
}

std::vector<trantorian_s> Client::get_players() { return map_to_vector<trantorian_s>(_players); }

void Client::write_to_server(char *message) {
    std::string t(message);
    t += "\n";
    write(_clientSock, t.c_str(), t.size());
};

// tna

// std::string temp_func(int _clientSock) {
//     char buffer;
//     std::string s_te;
//     while (read(_clientSock, &buffer, 1) && buffer != '\r')
//         s_te += buffer;
//     return s_te;
// }

void Client::in_loop_regulator() {
    bool isGuiBusy = false;
    for(const auto& pair : _players) {
        if (_gui.isPlayerAnimating(pair.first)) {
            isGuiBusy = true;
            break;
        }
    }
    if (isGuiBusy) {
        return;
    }

    char buffer[30 * 30 * 9 * 100];
    struct pollfd llp = {_clientSock, POLLIN, 0};
    poll(&llp, 1, 1);
    if (llp.revents != llp.events)
        return;
    int ret = read(_clientSock, buffer, sizeof(buffer));

    buffer[ret] = 0;
    // std::string s_te;
    // if (_gui.shouldClose())
    //     std::exit(0);
    // while (read(_clientSock, &buffer, 1))
    //      s_te += buffer;
    auto arr = split(std::string(buffer), "\n");
    for (auto temp : arr) {
        if (temp.empty()) continue;

        auto sed = split(temp);
        if (sed.empty()) continue;

        auto f = sed.front();
        sed.erase(sed.begin());

        _commandQueue.push_back({f, sed});
    }
    if (_commandQueue.empty()) {
        return;
    }

    while (!_commandQueue.empty()) {
    Command cmd = _commandQueue.front();
    _commandQueue.pop_front();

    std::string f = cmd.name;
    std::vector<std::string> sed = cmd.args;

    try {
        if (f == "msz") {
            if (sed.size() < 2) return;
            std::size_t x = std::stoul(sed[1]);
            std::size_t y = std::stoul(sed[0]);
            _map.resize(x);
            for (auto &t : _map)
                t.resize(y);
            _gui.setMapSize(x, y);
        } else if (f == "bct") {
            std::size_t server_x = std::stoul(sed[0]);
            std::size_t server_y = std::stoul(sed[1]);
            sed.erase(sed.begin(), sed.begin() + 2);
            _map[server_x][server_y] = sed;
            _gui.updateTile(server_y, server_x, _map[server_x][server_y]);
        } else if (f == "tna") {
            if (sed.empty()) return;
            _gui.setTna(sed.front());
        }
        else if (f == "pnw") {
            trantorian_s play_y;
            if (_players.find(0) != _players.end()) {
                auto existingPlayer = _players.find(0);
                trantorian_s temp_player = existingPlayer->second;
                temp_player.id = std::stoul(sed[0]);
                temp_player.level = 1;//std::stoul(sed[4]);
                temp_player.team = sed[5];
                temp_player.pos.x = std::stoul(sed[2]);
                temp_player.pos.y = std::stoul(sed[1]);
                temp_player.orientation = (orient_e)std::stoul(sed[3]);
                temp_player.team = sed[5];
                temp_player.elements = elem_s();
                _players.erase(0);
                _players.insert({std::stoul(sed[0]), temp_player});
                play_y = temp_player;
            } else {
                trantorian_s newPlayer;
                newPlayer.id = std::stoul(sed[0]);
                newPlayer.pos.x = std::stoul(sed[2]);
                newPlayer.pos.y = std::stoul(sed[1]);
                newPlayer.orientation = (orient_e)std::stoul(sed[3]);
                newPlayer.level = std::stoul(sed[4]);
                newPlayer.team = sed[5]; 
                newPlayer.development = trantorian_s::state::ADULT;
                newPlayer.elements = elem_s();

                _players.insert({newPlayer.id, newPlayer});
                play_y = newPlayer;
            }

            _gui.addPlayer(play_y);
            _gui.makePlayerSpawn(play_y.id);
        } else if (f == "ppo") {

            std::size_t id = std::stoul(sed[0]);


            pos_t server_new_pos = {std::stoul(sed[1]), std::stoul(sed[2])};
            orient_e server_orientation = (orient_e)std::stoul(sed[3]);


            pos_t old_pos_gui = _players[id].pos;


            pos_t new_pos_gui = {server_new_pos.y, server_new_pos.x};


            _gui.move_and_slide_animation(id, old_pos_gui, new_pos_gui, server_orientation);


            _players[id].pos = new_pos_gui;
            _players[id].orientation = server_orientation;
        } else if (f == "plv") {
            auto &l = _players[std::stoul(sed[0])];
            l.level = l.level < std::stoul(sed[1]) ? std::stoul(sed[1]) : l.level;
            _gui.updatePlayerLevel(std::stoul(sed[0]), l.level);
        } else if (f == "pin") {
            std::vector<std::size_t> elems;
            auto &l = _players[std::stoul(sed[0])];
            std::size_t x = std::stoul(sed[2]);
            std::size_t y = std::stoul(sed[1]);
            sed.erase(sed.begin(), sed.begin() + 2);
            l.pos = {x, y};
            const std::size_t resources[] = {
                std::stoul(sed[0]), std::stoul(sed[1]), std::stoul(sed[2]),
                std::stoul(sed[3]), std::stoul(sed[4]), std::stoul(sed[5]),
                std::stoul(sed[6])
            };
            l.elements.food = resources[0];
            l.elements.linemate = resources[1];
            l.elements.deraumere = resources[2];
            l.elements.sibur = resources[3];
            l.elements.mendiane = resources[4];
            l.elements.phiras = resources[5];
            l.elements.thystame = resources[6];
            _gui.updatePlayerRessources(l.id, l.elements);
        } else if (f == "pex") {
            _gui.makePlayerToExpulseAnother(std::stoul(sed[0]));
        } else if (f == "pbc") {
            _gui.makePlayerBroadCast(std::stoul(sed[0]));
        } else if (f == "pic") {
            std::size_t x = std::stoul(sed[1]);
            std::size_t y = std::stoul(sed[0]);
            std::size_t level = std::stoul(sed[2]);
            sed.erase(sed.begin(), sed.begin() + 2);
            std::vector<trantorian_s> tabl;
            for (auto &i : sed) {
                auto index = std::stoul(i);
                if (i == sed.front())
                    _players[index].pos = {x, y};
                if (_players[index].level == level) {
                    _players[index].current_animation = ECSTASY;
                    _gui.makePlayerExtasy(index);
                }
            }
        } else if (f == "pie") {
            for (auto si : _players) {
                if (si.second.current_animation == ECSTASY) {
                    auto pgdldflv =  (pos_t){std::stoul(sed[1]), std::stoul(sed[0])};
                    if (si.second.pos == pgdldflv)
                        _gui.makePlayerStopExtasy(si.first);
                }
            }
        } else if (f == "pfk")
            _gui.makePlayerLayEgg(std::stoul(sed[0]));
        else if (f == "pdr")
            _gui.makePlayerDrop(std::stoul(sed[0]));
        else if (f == "pgt")
            _gui.makePlayerPick(std::stoul(sed[0]));
        else if (f == "pdi") {
            _gui.makePlayerDie(std::stoul(sed[0]));
            _players.erase(std::stoul(sed[0]));
        } else if (f == "enw") {////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            std::cerr << "bamboclat!!!" << std::endl;
            _eggs.insert({std::stoul(sed[0]), {0,
                {std::stoul(sed[3]), std::stoul(sed[2])},
                _players[std::stoul(sed[1])].orientation, 0, elem(), _players[std::stoul(sed[1])].team, trantorian_s::state::ADULT}});
            // _eggs.push_back({0,
            //     {std::stoul(sed[3]), std::stoul(sed[2])},
            //     _players[std::stoul(sed[1])].orientation, 0, elem(), _players[std::stoul(sed[1])].team, trantorian_s::state::ADULT}});

            _gui.addEggPlayer(_eggs[std::stoul(sed[0])]);
            _gui.makeEggSpawn(std::stoul(sed[0]));
        } else if (f == "ebo") {
            _players.insert({0, _eggs[std::stoul(sed[0])]});
            _eggs.erase(std::stoul(sed[0]));
            _gui.makeEggDie(std::stoul(sed[0]));
        } else if (f == "edi") {
            _gui.makeEggDie(std::stoul(sed[0]));
            _eggs.erase(std::stoul(sed[0]));
        }
        else if (f == "sgt")
            _gui.setSgt(std::stof(sed.front()));
        else if (f == "sst")
            sst(0.1);
        else if (f == "seg")
            _gui.setWinner(sed.front());
        else if (f == "smg")
            _gui.display_smg(sed.front(), 3.f, BLACK, WHITE);
        else if (f == "suc") {
            _gui.display_smg("unknown command", 5.0, RED, MAROON);
            // data.first = "std::string";
            // std::any_cast<std::string>(data.second) = "unknown command";
        } else if (f == "sbp") {
            _gui.display_smg("command parameter", 5.0, RED, MAROON);
            // data.first = "std::string";
            // std::any_cast<std::string>(data.second) = "command parameter";
        }
    } catch (const std::invalid_argument &e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::out_of_range &e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
    }
    }
    return;
}
