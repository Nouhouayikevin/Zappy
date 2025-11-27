/*
** my.hpp for B-YEP-400-COT-zappy-julcinia.oke
**
** Made by ShadowedSlayer01
** Login <joseph.behanzin@epitech.eu>
**
** Started on  Wed June 25 3:05:10 AM 2025 ShadowedSlayer01
** Last update Wed June 25 3:30:41 AM 2025 ShadowedSlayer01
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

#include "struct.hpp"
#include "guimanager.hpp"
#include <vector>
// #include "my_include.hpp"

// Dans my.hpp

struct Command {
    std::string name; // "ppo", "pdi", etc.
    std::vector<std::string> args;
};

class Client {
    private:
        int _clientSock;
        std::vector<std::vector<tile_s>> _map;
        // std::vector<trantorian_s> _eggs;
        std::map<std::size_t, trantorian_s> _eggs;
        std::map<std::size_t, trantorian_s> _players;
        pos_s map_pos;
        std::deque<Command> _commandQueue;
    public:
        GuiManager _gui;
        // std::pair<std::string, std::any> data;
        bool is_open() {return (fcntl(_clientSock, F_GETFD) != -1 || errno != EBADF);};
        Client(int port = 8080, std::string host = "localhost");

        void msz();
        void bct(std::size_t x, std::size_t y);
        void mct(void);
        void tna(void);
        void ppo(std::size_t id);
        void plv(std::size_t id);
        void pin(std::size_t id);
        void sgt();
        void sst(float T);
        void write_to_server(char *message);
        std::vector<std::vector<tile_s>> &get_map() { return _map; };
        std::vector<trantorian_s> get_players();
        void in_loop_regulator();
};

#endif
