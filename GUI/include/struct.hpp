/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** struct.hpp
*/

#ifndef MY_STRUCT___
    #define MY_STRUCT___
    #include "my_include.hpp"


/** celui qui touchera a cette enum doit garder son ordre, car j'utilise cet ordre qlq part
    dans les give_animations ....
*/
typedef enum {
    IDLE,
    WALK,
    PICK,
    DROP,
    ECSTASY,
    LAY,
    SPAWN,
    DIE,
    EXPULSE,
    NO_ANIMATION = -1,

    //Joseph n'y touches pas, c'est juste pour le bruitage
    BROADCAST = 9,
    CANCEL

} actions_e;

typedef struct elem{
    enum elema {
        FOOD, // Ressource id 0
        LINEMATE, // Ressource id 1
        DERAUMERE, // Ressource id 2
        SIBUR, // Ressource id 3
        MENDIANE, // Ressource id 4
        PHIRAS, // Ressource id 5
        THYSTAME // Ressource id 6
    };

    std::size_t food;
    std::size_t linemate;
    std::size_t deraumere;
    std::size_t sibur;
    std::size_t mendiane;
    std::size_t phiras;
    std::size_t thystame;
    elem() { food = 0; linemate = 0; deraumere = 0; sibur = 0; mendiane = 0;
        phiras = 0; thystame = 0; };
    elem(std::vector<std::size_t> arr) { food = arr[0]; linemate = arr[1]; deraumere = arr[2]; sibur = arr[3]; mendiane = arr[4];
        phiras = arr[5]; thystame = arr[6]; };
    elem(std::vector<std::string> arr) { food = std::stoi(arr[0]); linemate = std::stoi(arr[1]); deraumere = std::stoi(arr[2]); sibur = std::stoi(arr[3]); mendiane = std::stoi(arr[4]);
        phiras = std::stoi(arr[5]); thystame = std::stoi(arr[6]); };
    std::size_t get(std::size_t id) {return id == 0 ? food : id == 1 ? linemate : id == 2 ? deraumere : id == 3 ? sibur :
        id == 4 ? mendiane : id == 5 ? phiras : id == 6 ? thystame : 0; } ;
} elem_s;

std::ostream & operator << (std::ostream &out, elem obj);

template <typename T>
std::vector<T> map_to_vector(std::map<std::size_t, T> l);

typedef enum {
    NORTH = 1,
    EAST,
    SOUTH,
    WEST
} orient_e;

typedef struct pos_s {
    std::size_t x;
    std::size_t y;

    bool operator == (struct pos_s &other) {
        return (other.x == x && other.y == y);
    };
    bool operator != (struct pos_s &other) {
        return !(other == *this);
    };
    pos_s() {x = 0; y= 0;}
    pos_s(std::size_t _x, std::size_t _y) {x= _x; y= _y;}
    bool operator<(const pos_s& other) const {
        return std::tie(y, x) < std::tie(other.y, other.x);
    }
} pos_t;

typedef struct {
    std::size_t id;
    pos_t pos;
    orient_e orientation;
    std::size_t level;
    elem_s elements;
    std::string team;
    enum state {
        EGG,
        ADULT
    };
    state development;

    actions_e current_animation{actions_e :: NO_ANIMATION};
    int animCurrentFrame{0};
    pos_t targetPos {0, 0};
    pos_t bcPos {0, 0};
    Vector2 actualPosWithAnimation {0, 0};
    float animationProgress = 0.0f; // Progrès du déplacement (0.0 → 1.0)
    float broadcastProgress = 0.0f; // Progrès du déplacement (0.0 → 1.0)
    bool isMoving = false; //if moves
    bool isWrap = false;
    bool isdying = false;
    bool isSpawn = false;
    bool isBroadCast = false;
    bool isExpulse = false;
    bool isEstasy = false;
    bool isLayingEgg = false;
    bool isDroping = false;
    bool isPicking = false;
    Color color = (Color) WHITE;
} trantorian_s;


#define tile_s elem_s

class client {
    private:
        int _clientSock;
        std::vector<std::vector<tile_s>> _map;
        std::map<std::size_t, trantorian_s> _players;
        pos_s map_pos;
    public:
        std::pair<std::string, std::any> data;
        bool is_open() {return fcntl(_clientSock, F_GETFD) != -1 || errno != EBADF;};
        client(int port = 8080);
        ~client(){};
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
        bool in_loop_regulator();
};

#include "loadingBar.hpp"

typedef struct FloorModel {
    Model _model_platforms;
    Vector3  obj_scale;
    Vector3  obj_first_position;
} FloorModel;

#endif
