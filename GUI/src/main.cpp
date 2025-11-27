/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** main.cpp
*/

#include "../include/my.hpp"
#include <csignal>
#include <cstring>
#include <signal.h>


void myhandler(int signum) {
    if (signum == SIGSEGV) {
        std::cout << "Caught signal " << signum << ", exiting gracefully..." << std::endl;
        std::exit(84);
    }
    if (signum == SIGINT) {
        std::cout << "Interrupting the program..." << std::endl;
        std::exit(0);
    }
}
//joseph tu dois tester comme ca
int main(int ac, char **av) {
    int port = 0;
    std::string machine;

    signal(SIGINT, myhandler);
    signal(SIGSEGV, myhandler);
    try {
        if (ac != 3 && ac != 5) {
            throw ParsingError("Invalid number of arguments.");
        }
        for (int i = 1; i <  ac; i++) {
                if (!strcmp(av[i - 1], "-p")) {
                    port = atoi(av[i]);
                    if (port <= 0) {
                        throw ParsingError("Missing value for a flag");
                    }
                }
                if (!strcmp(av[i - 1], "-h"))
                    machine = av[i];
                // else {
                //     std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
                //     std::exit(84);
                // }
        }
        Client client(port, machine);
        while(!client._gui.shouldClose()){
            client.in_loop_regulator();
            client._gui.UpdateAndDrawFrame();
            if(!client.is_open())
                break;
        }
    } catch (const ParsingError& e) {
        std::cerr << "Error parsing arguments: " << e.what() << std::endl;
        std::cerr << "USAGE: ./zappy_gui -p port [-h machine]" << std::endl;
        return 84;
    }
    // return 0;
    // GuiManager gui;
    //  while (!gui.shouldClose()) {
    //     gui.RunGameLoop();
    // }

    return 0;
}

// //joseph
// int main(/*int argc, char* argv[]*/) {
//     GuiManager gui;

//     gui.setMapSize(2, 2);

//     for (int x = 0; x < 10; x++) {
//         for (int y = 0; y < 10; y++) {
//             elem_s res;
//             if ((x + y) % 5 == 0) res.phiras = 2;
//             if ((x + y) % 5 == 0) res.food = 2;
//             if ((x * y) % 6 == 0) res.linemate = 1;
//             if (x == y) res.deraumere = 1;
//             if ((x * y) % 7 == 0) res.sibur = 1;
//             if ((x * y) % 7 == 0) res.thystame = 1;
//             gui.updateTile(x, y, res);
//         }
//     }

    // trantorian_s player;
    // player.id = 0;
    // player.pos = {0, 0};
    // player.orientation = EAST;
    // player.level = 0;
    // player.team = "Team1";
    // player.animCurrentFrame = 0;
    // player.current_animation = actions_e::WALK;
    // gui.setTna("Team1");
    // gui.addPlayer(player);

    // player.id = 2;
    // player.level = 2;
    // player.pos = {0, 0};
    // player.current_animation = actions_e::PICK;
    // player.isdying =true;
//     gui.addPlayer(player);
//     gui.makePlayerBroadCast(2);
// gui.display_smg("Bonjour les amis comme Kaeloo!", 10.0, BLACK, LIME);

// gui.display_smg("ATTENTION", 5.0, YELLOW, RED);

// gui.display_smg("Info", 5.0, SKYBLUE, DARKBLUE);
    // player.level = 3;
    // player.pos = {2, 2};
    // player.id = 3;
    // gui.addPlayer(player);
    // player.pos = {3, 3};
    // player.level = 4;
    // player.id = 4;
    // gui.addPlayer(player);
    // player.level = 5;
    // player.pos = {4, 4};
    // player.id = 5;
    // gui.addPlayer(player);
    // player.level = 6;
    // player.pos = {5, 5};
    // player.id = 6;
    // gui.addPlayer(player);
    // player.level = 7;
    // player.pos = {6, 6};
    // player.id = 7;
    // gui.addPlayer(player);
    // player.pos = {7, 7};
    // player.level = 8;
    // player.id = 8;
    // gui.addPlayer(player);
    // gui.move_and_slide_animation(2, EAST );
    // gui.setWinner("poiuytrerty iuytrfghjk");

    // while (!gui.shouldClose()) {
    //     gui.RunGameLoop();
    // }


//     return 0;
// }
