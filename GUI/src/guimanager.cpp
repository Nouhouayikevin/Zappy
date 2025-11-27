/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** guimanager.cpp
*/

#include "../include/guimanager.hpp"
#include "rlights.h"
static Light _lights[MAX_LIGHTS] =
                                {
                                    (Light){.type = 0, .enabled =false, .position= (Vector3) {0, 0, 0}, .target=(Vector3){0, 0,0}, .color= (Color) {0,0,0,0}, .attenuation= 0.0f, .enabledLoc = 0, .typeLoc = 0, .positionLoc = 0,.targetLoc = 0, .colorLoc = 0, .attenuationLoc = 0},
                                    (Light){.type = 0, .enabled =false, .position= (Vector3) {0, 0, 0}, .target=(Vector3){0, 0,0}, .color= (Color) {0,0,0,0}, .attenuation= 0.0f, .enabledLoc = 0, .typeLoc = 0, .positionLoc = 0,.targetLoc = 0, .colorLoc = 0, .attenuationLoc = 0},
                                    (Light){.type = 0, .enabled =false, .position= (Vector3) {0, 0, 0}, .target=(Vector3){0, 0,0}, .color= (Color) {0,0,0,0}, .attenuation= 0.0f, .enabledLoc = 0, .typeLoc = 0, .positionLoc = 0,.targetLoc = 0, .colorLoc = 0, .attenuationLoc = 0},
                                    (Light){.type = 0, .enabled =false, .position= (Vector3) {0, 0, 0}, .target=(Vector3){0, 0,0}, .color= (Color) {0,0,0,0}, .attenuation= 0.0f, .enabledLoc = 0, .typeLoc = 0, .positionLoc = 0,.targetLoc = 0, .colorLoc = 0, .attenuationLoc = 0}
                                };
static std::vector<Color> predefinedColors = {
    { 230, 41, 55, 255 },   // 1. Rouge (Original)
    { 0, 121, 241, 255 },   // 2. Bleu (Original)
    { 0, 228, 48, 255 },    // 3. Vert (Original)
    { 253, 249, 0, 255 },   // 4. Jaune (Original)
    { 255, 161, 0, 255 },   // 5. Orange (Original)
    { 173, 51, 255, 255 },  // 6. Violet (Original)
    { 25, 223, 190, 255 },  // 7. Turquoise
    { 242, 95, 43, 255 },   // 8. Corail
    { 61, 199, 242, 255 },  // 9. Cyan
    { 242, 61, 143, 255 },  // 10. Magenta
    { 145, 242, 61, 255 },  // 11. Vert Citron
    { 132, 61, 242, 255 },  // 12. Indigo
    { 242, 194, 61, 255 },  // 13. Or
    { 61, 74, 242, 255 },   // 14. Bleu Roi
    { 212, 61, 242, 255 },  // 15. Fuchsia
    { 61, 242, 129, 255 },  // 16. Vert Menthe
    { 242, 61, 61, 255 },   // 17. Rouge Tomate
    { 102, 242, 61, 255 },  // 18. Vert Chartreuse
    { 191, 61, 242, 255 },  // 19. Lavande
    { 61, 242, 224, 255 },  // 20. Aigue-marine
    { 242, 128, 61, 255 },  // 21. Mandarine
    { 61, 161, 242, 255 },  // 22. Bleu Ciel
    { 242, 61, 212, 255 },  // 23. Rose Vif
    { 61, 242, 71, 255 },   // 24. Vert Haricot
    { 92, 61, 242, 255 },   // 25. Bleu Violet
    { 242, 161, 61, 255 },  // 26. Ambre
    { 61, 105, 242, 255 },  // 27. Cobalt
    { 242, 61, 178, 255 },  // 28. Rose Bonbon
    { 128, 242, 61, 255 },  // 29. Vert Poire
    { 161, 61, 242, 255 },  // 30. Améthyste
    { 242, 224, 61, 255 },  // 31. Jaune Poussin
    { 61, 209, 242, 255 },  // 32. Bleu Clair
    { 199, 21, 133, 255 },  // 33. Rose Moyen
    { 34, 139, 34, 255 },   // 34. Vert Forêt
    { 255, 20, 147, 255 },  // 35. Rose Profond
    { 0, 255, 127, 255 },   // 36. Vert Printemps
    { 72, 61, 139, 255 },   // 37. Bleu Ardoise Foncé
    { 255, 105, 180, 255 }, // 38. Rose "Hot Pink"
    { 124, 252, 0, 255 },   // 39. Vert Pelouse
    { 138, 43, 226, 255 },  // 40. Violet Bleu
    { 255, 140, 0, 255 },   // 41. Orange Foncé
    { 70, 130, 180, 255 },  // 42. Bleu Acier
    { 218, 112, 214, 255 }, // 43. Orchidée
    { 173, 255, 47, 255 },  // 44. Vert Jaune
    { 255, 0, 255, 255 },   // 45. Magenta (pur)
    { 30, 144, 255, 255 },  // 46. Bleu Dodger
    { 219, 112, 147, 255 }, // 47. Mauve Pâle
    { 255, 215, 0, 255 },   // 48. Or (pur)
    { 128, 0, 128, 255 },   // 49. Pourpre
    { 85, 107, 47, 255 }    // 50. Vert Olive Foncé
};


                                /*
                                                         ,----,                                           ,----,                                                                                                                          ,----,                                           ,----,
               ,----..            ,--.                 ,/   .`|                                         ,/   .`|  ,----..                                              ,--.                                                             ,/   .`|                                         ,/   .`|  ,----..
  ,----..     /   /   \         ,--.'|  .--.--.      ,`   .'  :,-.----.                  ,----..      ,`   .'  : /   /   \  ,-.----.              ,---,              ,--.'|    ,---,                ,---,        ,---,.  .--.--.      ,`   .'  :,-.----.                  ,----..      ,`   .'  : /   /   \  ,-.----.
 /   /   \   /   .     :    ,--,:  : | /  /    '.  ;    ;     /\    /  \           ,--, /   /   \   ;    ;     //   .     : \    /  \            '  .' \         ,--,:  : |  .'  .' `\            .'  .' `\    ,'  .' | /  /    '.  ;    ;     /\    /  \           ,--, /   /   \   ;    ;     //   .     : \    /  \
|   :     : .   /   ;.  \,`--.'`|  ' :|  :  /`. /.'___,/    ,' ;   :    \        ,'_ /||   :     :.'___,/    ,'.   /   ;.  \;   :    \          /  ;    '.    ,`--.'`|  ' :,---.'     \         ,---.'     \ ,---.'   ||  :  /`. /.'___,/    ,' ;   :    \        ,'_ /||   :     :.'___,/    ,'.   /   ;.  \;   :    \
.   |  ;. /.   ;   /  ` ;|   :  :  | |;  |  |--` |    :     |  |   | .\ :   .--. |  | :.   |  ;. /|    :     |.   ;   /  ` ;|   | .\ :         :  :       \   |   :  :  | ||   |  .`\  |        |   |  .`\  ||   |   .';  |  |--` |    :     |  |   | .\ :   .--. |  | :.   |  ;. /|    :     |.   ;   /  ` ;|   | .\ :
.   ; /--` ;   |  ; \ ; |:   |   \ | :|  :  ;_   ;    |.';  ;  .   : |: | ,'_ /| :  . |.   ; /--` ;    |.';  ;;   |  ; \ ; |.   : |: |         :  |   /\   \  :   |   \ | ::   : |  '  |        :   : |  '  |:   :  |-,|  :  ;_   ;    |.';  ;  .   : |: | ,'_ /| :  . |.   ; /--` ;    |.';  ;;   |  ; \ ; |.   : |: |
;   | ;    |   :  | ; | '|   : '  '; | \  \    `.`----'  |  |  |   |  \ : |  ' | |  . .;   | ;    `----'  |  ||   :  | ; | '|   |  \ :         |  :  ' ;.   : |   : '  '; ||   ' '  ;  :        |   ' '  ;  ::   |  ;/| \  \    `.`----'  |  |  |   |  \ : |  ' | |  . .;   | ;    `----'  |  ||   :  | ; | '|   |  \ :
|   : |    .   |  ' ' ' :'   ' ;.    ;  `----.   \   '   :  ;  |   : .  / |  | ' |  | ||   : |        '   :  ;.   |  ' ' ' :|   : .  /         |  |  ;/  \   \'   ' ;.    ;'   | ;  .  |        '   | ;  .  ||   :   .'  `----.   \   '   :  ;  |   : .  / |  | ' |  | ||   : |        '   :  ;.   |  ' ' ' :|   : .  /
.   | '___ '   ;  \; /  ||   | | \   |  __ \  \  |   |   |  '  ;   | |  \ :  | | :  ' ;.   | '___     |   |  ''   ;  \; /  |;   | |  \         '  :  | \  \ ,'|   | | \   ||   | :  |  '        |   | :  |  '|   |  |-,  __ \  \  |   |   |  '  ;   | |  \ :  | | :  ' ;.   | '___     |   |  ''   ;  \; /  |;   | |  \
'   ; : .'| \   \  ',  / '   : |  ; .' /  /`--'  /   '   :  |  |   | ;\  \|  ; ' |  | ''   ; : .'|    '   :  | \   \  ',  / |   | ;\  \        |  |  '  '--'  '   : |  ; .''   : | /  ;         '   : | /  ; '   :  ;/| /  /`--'  /   '   :  |  |   | ;\  \|  ; ' |  | ''   ; : .'|    '   :  | \   \  ',  / |   | ;\  \
'   | '/  :  ;   :    /  |   | '`--'  '--'.     /    ;   |.'   :   ' | \.':  | : ;  ; |'   | '/  :    ;   |.'   ;   :    /  :   ' | \.'        |  :  :        |   | '`--'  |   | '` ,/          |   | '` ,/  |   |    \'--'.     /    ;   |.'   :   ' | \.':  | : ;  ; |'   | '/  :    ;   |.'   ;   :    /  :   ' | \.'
|   :    /    \   \ .'   '   : |        `--'---'     '---'     :   : :-'  '  :  `--'   \   :    /     '---'      \   \ .'   :   : :-'          |  | ,'        '   : |      ;   :  .'            ;   :  .'    |   :   .'  `--'---'     '---'     :   : :-'  '  :  `--'   \   :    /     '---'      \   \ .'   :   : :-'
 \   \ .'      `---`     ;   |.'                               |   |.'    :  ,      .-./\   \ .'                  `---`     |   |.'            `--''          ;   |.'      |   ,.'              |   ,.'      |   | ,'                           |   |.'    :  ,      .-./\   \ .'                  `---`     |   |.'
  `---`                  '---'                                 `---'       `--`----'     `---`                              `---'                             '---'        '---'                '---'        `----'                             `---'       `--`----'     `---`                              `---'
   */


GuiManager::GuiManager() {
    _gameState = STATE_LOADING;
    _loadingStage = 0;

    _isFreqInputActive = false;
    _freqInputCharCount = 0;
    memset(_freqInputBuffer, 0, sizeof(_freqInputBuffer));
    _audioManager.InitAudio();

    _gameTips = {
        "Tip: Food is essential for survival. One unit lasts for 126 time units.",
        "Tip: To win, 6 players of a team must reach level 8.",
        "Tip: The 'Look' command is your best friend to find resources.",
        "Tip: You can communicate with other players using 'Broadcast'.",
        "Tip: An Incantation requires a specific number of players and stones.",
        "Tip: Use 'Fork' to lay an egg and increase your team's size.",
        "Tip: Press 'P' to switch between camera perspectives."

        "Tip: The world of Trantor is a torus! Exiting on the right brings you back on the left.",
        "Tip: Feeling crowded? The 'Eject' command pushes all other players from your current tile.",
        "Tip: 'Eject' is powerful, but beware: it also destroys any eggs on the tile.",
        "Tip: Players from different teams can cooperate for an Incantation if they are the same level.",
        "Tip: During an Incantation, all participating players are frozen and cannot perform other actions.",
        "Tip: Each Trantorian starts with 10 units of food, enough to survive for 1260 time units.",
        "Tip: Your vision expands as you level up, allowing you to see further and plan better.",
        "Tip: Use the mouse wheel to zoom in and out. The 'C' key toggles the cursor.",
        "Tip: Broadcasts are directional. The number 'K' tells your AI exactly where the sound came from.",
        "Tip: Click on a player in the 'Teams' panel to follow them. Press 'U' to unfollow.",
        "Tip: New resources will periodically appear across the map. Keep exploring!",
        "Tip: The game's speed is controlled by the time unit 'f'. A higher 'f' means faster actions.",
        "Tip: When a player starves, their inventory is dropped on the ground for others to take."
    };

    initWindow();
    startRunGameLoop();
}

GuiManager::~GuiManager() {
    _audioManager.ShutdownAudio();
    stopRunGameLoop();

}




/******************************************************************************************

   ,---,                       ___                          ,--,                                       ___
,`--.' |              ,--,   ,--.'|_    ,--,              ,--.'|     ,--,                            ,--.'|_    ,--,
|   :  :      ,---, ,--.'|   |  | :,' ,--.'|              |  | :   ,--.'|                            |  | :,' ,--.'|    ,---.        ,---,
:   |  '  ,-+-. /  ||  |,    :  : ' : |  |,               :  : '   |  |,      .--.--.                :  : ' : |  |,    '   ,'\   ,-+-. /  |
|   :  | ,--.'|'   |`--'_  .;__,'  /  `--'_      ,--.--.  |  ' |   `--'_     /  /    '    ,--.--.  .;__,'  /  `--'_   /   /   | ,--.'|'   |
'   '  ;|   |  ,"' |,' ,'| |  |   |   ,' ,'|    /       \ '  | |   ,' ,'|   |  :  /`./   /       \ |  |   |   ,' ,'| .   ; ,. :|   |  ,"' |
|   |  ||   | /  | |'  | | :__,'| :   '  | |   .--.  .-. ||  | :   '  | |   |  :  ;_    .--.  .-. |:__,'| :   '  | | '   | |: :|   | /  | |
'   :  ;|   | |  | ||  | :   '  : |__ |  | :    \__\/: . .'  : |__ |  | :    \  \    `.  \__\/: . .  '  : |__ |  | : '   | .; :|   | |  | |
|   |  '|   | |  |/ '  : |__ |  | '.'|'  : |__  ," .--.; ||  | '.'|'  : |__   `----.   \ ," .--.; |  |  | '.'|'  : |_|   :    ||   | |  |/
'   :  ||   | |--'  |  | '.'|;  :    ;|  | '.'|/  /  ,.  |;  :    ;|  | '.'| /  /`--'  //  /  ,.  |  ;  :    ;|  | '.'\   \  / |   | |--'
;   |.' |   |/      ;  :    ;|  ,   / ;  :    ;  :   .'   \  ,   / ;  :    ;'--'.     /;  :   .'   \ |  ,   / ;  :    ;`----'  |   |/
'---'   '---'       |  ,   /  ---`-'  |  ,   /|  ,     .-./---`-'  |  ,   /   `--'---' |  ,     .-./  ---`-'  |  ,   /         '---'
                     ---`-'            ---`-'  `--`---'             ---`-'              `--`---'               ---`-'

*/


bool GuiManager::shouldClose() {
    return WindowShouldClose();
}

/*************************************************************************************************

                          ___      ___
                        ,--.'|_  ,--.'|_
                        |  | :,' |  | :,'             __  ,-.
  .--.--.               :  : ' : :  : ' :           ,' ,'/ /|  .--.--.
 /  /    '     ,---.  .;__,'  /.;__,'  /     ,---.  '  | |' | /  /    '
|  :  /`./    /     \ |  |   | |  |   |     /     \ |  |   ,'|  :  /`./
|  :  ;_     /    /  |:__,'| : :__,'| :    /    /  |'  :  /  |  :  ;_
 \  \    `. .    ' / |  '  : |__ '  : |__ .    ' / ||  | '    \  \    `.
  `----.   \'   ;   /|  |  | '.'||  | '.'|'   ;   /|;  : |     `----.   \
 /  /`--'  /'   |  / |  ;  :    ;;  :    ;'   |  / ||  , ;    /  /`--'  /
'--'.     / |   :    |  |  ,   / |  ,   / |   :    | ---'    '--'.     /
  `--'---'   \   \  /    ---`-'   ---`-'   \   \  /            `--'---'
              `----'                        `----'
*/


void GuiManager::setMapSize(int width, int height) {
    _width = width;
    _height = height;
    _map.resize(height);
    for (int y = 0; y < height; y++) {
        _map[y].resize(width);
        _platforms.push_back(std::deque<FloorModel>());
        _platforms.back().resize(width);

        for (int x = 0; x < width; x++) {
            int min = GetRandomValue(1, 10);
            int max = GetRandomValue(1, 10);
            int random_platform = GetRandomValue(std::min(min, max), std::max(min, max));
            _map[y][x] = elem();
            switch(random_platform) {
                case 1:
                    _platforms.back()[x]._model_platforms = _model_platforms_1;
                    _platforms.back()[x].obj_scale = PLATFORM1_SCALE ;
                    _platforms.back()[x].obj_first_position = PLATFORM1_FIRST_POS;
                    break;
                case 2:
                    _platforms.back()[x]._model_platforms = _model_platforms_2;
                    _platforms.back()[x].obj_scale = PLATFORM2_SCALE ;
                    _platforms.back()[x].obj_first_position = PLATFORM2_FIRST_POS;
                    break;
                case 3:
                    _platforms.back()[x]._model_platforms = _model_platforms_3;
                    _platforms.back()[x].obj_scale = PLATFORM3_SCALE ;
                    _platforms.back()[x].obj_first_position = PLATFORM3_FIRST_POS;
                    break;
                case 4:
                    _platforms.back()[x]._model_platforms = _model_platforms_4;
                    _platforms.back()[x].obj_scale = PLATFORM4_SCALE ;
                    _platforms.back()[x].obj_first_position = PLATFORM4_FIRST_POS;
                    break;
                case 5:
                    _platforms.back()[x]._model_platforms = _model_platforms_5;
                    _platforms.back()[x].obj_scale = PLATFORM5_SCALE ;
                    _platforms.back()[x].obj_first_position = PLATFORM5_FIRST_POS;
                    break;
                case 6:
                    _platforms.back()[x]._model_platforms = _model_platforms_6;
                    _platforms.back()[x].obj_scale = PLATFORM6_SCALE ;
                    _platforms.back()[x].obj_first_position = PLATFORM6_FIRST_POS;
                    break;
                case 7:
                    _platforms.back()[x]._model_platforms = _model_platforms_7;
                    _platforms.back()[x].obj_scale = PLATFORM7_SCALE ;
                    _platforms.back()[x].obj_first_position = PLATFORM7_FIRST_POS;
                    break;
                case 8:
                    _platforms.back()[x]._model_platforms = _model_platforms_8;
                    _platforms.back()[x].obj_scale = PLATFORM8_SCALE ;
                    _platforms.back()[x].obj_first_position = PLATFORM8_FIRST_POS;
                    break;
                case 9:
                    _platforms.back()[x]._model_platforms = _model_platforms_9;
                    _platforms.back()[x].obj_scale = PLATFORM9_SCALE ;
                    _platforms.back()[x].obj_first_position = PLATFORM9_FIRST_POS;
                    break;
                case 10:
                    _platforms.back()[x]._model_platforms = _model_platforms_10;
                    _platforms.back()[x].obj_scale = PLATFORM10_SCALE ;
                    _platforms.back()[x].obj_first_position = PLATFORM10_FIRST_POS;
                    break;
            }
        }
    }
    UnloadModel(model_floor);

    mesh_floor = GenMeshPlane( (_width == 0) ? 50: GET_PLATFORM_POSX(0, _width*3)*3 , GET_PLATFORM_POSZ(0, _height*3)*3, 50, 50);
    model_floor = LoadModelFromMesh(mesh_floor);
    model_floor.materials[0].shader = water_shader;

    floor_changed_size = true;
}

void GuiManager::setWinner(std::string winner) {
    _winner = winner + " wins!";
}

Color generateColorFromTeamName(const std::string& teamName) {
    size_t hash = std::hash<std::string>{}(teamName);

    float hue = hash % 360;

    float saturation = 0.75f;
    float value = 0.95f;

    return ColorFromHSV(hue, saturation, value);
}

void GuiManager:: setTna(std::string team_name) {
    _teams.insert(team_name);

    if (_teamColors.find(team_name) == _teamColors.end()) {
        _teamColors[team_name] = generateColorFromTeamName(team_name);
    }

}

void GuiManager::setBct(std::vector<std::vector<tile_s>> __map) {
    _map = __map;
}

void GuiManager::setSgt(float frequency){
    if (frequency > 0  && frequency > EPSILON) {
        _frequency = frequency;

        std::string msg = "Game speed wd to " + std::to_string(frequency);
        display_smg(msg, 5.0, SKYBLUE, DARKBLUE);
    }
}
void GuiManager::setSst(float newSpeed){
    std::string command = "sst " + std::to_string(newSpeed) + "\n";

    //ici joseph tu dois envoyer au serveur que tu veux faire sst, comme ca lui il fera sgt pour me forcer  a changer ma propre frequence
    _frequency = newSpeed;
    //sendCommand(command);
}

/************************************************************************************************
                                                   ___
              ,-.----.        ,---,              ,--.'|_
         ,--, \    /  \     ,---.'|              |  | :,'             __  ,-.
       ,'_ /| |   :    |    |   | :              :  : ' :           ,' ,'/ /|  .--.--.
  .--. |  | : |   | .\ :    |   | |   ,--.--.  .;__,'  /     ,---.  '  | |' | /  /    '
,'_ /| :  . ||  |   |   ,' ,'|   '  | |   ,' ,'| .' ,'/ /|  .--.--.
,'_ /| :  . | .   : |: |  ,--.__| |  /       \ |  |   |     /     \ |  |   ,'|  :  /`./
|  ' | |  . . |   |  \ : /   ,'   | .--.  .-. |:__,'| :    /    /  |'  :  /  |  :  ;_
|  | ' |  | | |   : .  |.   '  /  |  \__\/: . .  '  : |__ .    ' / ||  | '    \  \    `.
:  | : ;  ; | :     |`-''   ; |:  |  ," .--.; |  |  | '.'|'   ;   /|;  : |     `----.   \
'  :  `--'   \:   : :   |   | '/  ' /  /  ,.  |  ;  :    ;'   |  / ||  , ;    /  /`--'  /
:  ,      .-./|   | :   |   :    :|;  :   .'   \ |  ,   / |   :    |---'    '--'.     /
 `--`----'    `---'.|    \   \  /  |  ,     .-./  ---`-'   \   \  /            `--'---'
                `---`     `----'    `--`---'                `----'
*/

void GuiManager::updateTile(int x, int y, const elem_s& resources) {
    if (x >= 0 && x < _width && y >= 0 && y < _height) {
        _map[y][x] = resources;
    }
}

void GuiManager::updatePlayerPosition(int id, int x, int y, orient_e orientation) {
    auto it = _players.find(id);
    if (it != _players.end()) {
        it->second.pos.x = x;
        it->second.pos.y = y;
        it->second.orientation = orientation;
    }
}

void GuiManager::updatePlayerLevel(int id, int level) {
    auto it = _players.find(id);
    if (it != _players.end())
        it->second.level = level;

    std::string msg = "player ID:" + std::to_string(id) + " updated level to:"+ std::to_string(level);
    display_smg(msg, 3.0f, GREEN, BLUE);
}

void GuiManager::updatePlayerRessources(int id, elem_s ressources) {
    auto it = _players.find(id);
    if (it != _players.end())
        it->second.elements = ressources;
        
    std::string msg = "player ID:" + std::to_string(id) + " has inventory updated";
    display_smg(msg, 3.0f, GREEN, DARKGREEN);
}

// Forward, Right, Left, Look, Eject, Broadcast, Take, Set : coût de 7
// Fork : coût de 42
// Incantation : coût de 300
// Inventory : coût de 1
// (cout/frequence) -> 1
// (cout/x) -> A

//A = 
void GuiManager::update() {
   _dashboard.update(GetFrameTime());

    if (_dashboard.isPlayerFollowed()) {
        _followedPlayerId = _dashboard.getFollowedPlayerId();
        auto it = _players.find(_followedPlayerId);
        if (it != _players.end()) {

            camMode = CAMERA_THIRD_PERSON;
            trantorian_s& player = it->second;
            Vector3 playerPos3D = { (float)player.actualPosWithAnimation.x, 1.0f, (float)player.actualPosWithAnimation.y };

            _camera.target = playerPos3D;
            _camera.position = Vector3{ playerPos3D.x, playerPos3D.y + 10.0f, playerPos3D.z - 10.0f };
        } else {

            _dashboard.stopFollowing();
            _followedPlayerId = -1;
        }
    }

    if (!_dashboard.isPlayerFollowed() && !_cursor) {
        UpdateCamera(&_camera, camMode);
    }

   _levitateTime += GetFrameTime();
   _currentTime += GetFrameTime();
    _hour = (float) (_currentTime /MY_HOUR_TIME);
    if (_hour > 24) {_hour = 0; _currentTime = 0.0f;}

   updateFloor();
   updateShader();
   updateSkyRotation(GetFrameTime());

   for (auto& [id, player] : _players) {
        if (player.isMoving) {
            player.animationProgress += GetFrameTime()*_FREQ_VALUE(_frequency);

            if (player.animationProgress >= 1.0f) {
                player.pos = player.targetPos;
                player.isMoving = false;
                player.isWrap = false;
                player.isEstasy = false;

                player.current_animation = IDLE;
                player.animCurrentFrame = 0;
                player.animationProgress = 0;
            }
        }

        if (player.isBroadCast && player.level) {
            player.broadcastProgress += GetFrameTime()*_FREQ_VALUE(_frequency);

            if (player.broadcastProgress >= 1.0f) {
                player.isBroadCast = false;
                player.broadcastProgress = 0;
                player.isEstasy = false;
            }
        }

        if (player.isExpulse) {
            player.animationProgress += GetFrameTime()*_FREQ_VALUE(_frequency);

            if (player.id >0 && player.animationProgress >= 1.0f) {
                player.isExpulse = false;
                player.isEstasy = false;
                player.current_animation = IDLE;
                player.animCurrentFrame = 0;
                player.animationProgress = 0;
            }
        }

        if (player.isSpawn) {
            player.animationProgress += GetFrameTime()*_FREQ_VALUE(_frequency);

            if (player.id >0 && player.animationProgress >= 1.0f) {
                player.isMoving = false;
                player.isWrap = false;
                player.isSpawn = false;
                player.isEstasy = false;
                player.current_animation = IDLE;
                player.animCurrentFrame = 0;
                player.animationProgress = 0;
            }
            if (player.id == 0 && player.animationProgress >= 1.0f) {
                player.isMoving = false;
                player.isWrap = false;
                player.isSpawn = false;
                player.isEstasy = false;
                player.current_animation = IDLE;
                player.animCurrentFrame = 0;
                player.animationProgress = 0;
            }
        }

        if (player.isLayingEgg) {
            player.animationProgress += GetFrameTime()*_FREQ_VALUE(_frequency);

            if (player.id >0 && player.animationProgress >= 1.0f) {
                player.isMoving = false;
                player.isWrap = false;
                player.isSpawn = false;
                player.isLayingEgg = false;
                player.isEstasy = false;
                player.current_animation = IDLE;
                player.animCurrentFrame = 0;
                player.animationProgress = 0;
            }
        }

        if (player.isDroping) {
            player.animationProgress += GetFrameTime()*_FREQ_VALUE(_frequency);

            if (player.id >0 && player.animationProgress >= 1.0f) {
                player.isMoving = false;
                player.isWrap = false;
                player.isSpawn = false;
                player.isLayingEgg = false;
                player.isDroping = false;
                player.isEstasy = false;
                player.current_animation = IDLE;
                player.animCurrentFrame = 0;
                player.animationProgress = 0;
            }
        }

        if (player.isPicking) {
            player.animationProgress += GetFrameTime()*_FREQ_VALUE(_frequency);

            if (player.id >0 && player.animationProgress >= 1.0f) {
                player.isMoving = false;
                player.isWrap = false;
                player.isSpawn = false;
                player.isLayingEgg = false;
                player.isPicking = false;
                player.isEstasy = false;
                player.current_animation = IDLE;
                player.animCurrentFrame = 0;
                player.animationProgress = 0;
            }
        }

        if (player.isEstasy) {
            player.animationProgress += GetFrameTime()*_FREQ_VALUE(_frequency);

            if (player.id > 0 && player.animationProgress >= 1.0f) {
                player.animationProgress = 0;
                makePlayerStopExtasy(player.id);
            }
        }

        if (player.isdying) {
            player.animationProgress += GetFrameTime() / GLOBAL_ANIMATION_DURATION;
            if ( player.id > 0 && player.animationProgress >= 1.0) {
                removePlayer(id);
                break;
            }
            if ( player.id == 0 && player.animationProgress >= 1.0) {
                removePlayer(id);
                break;
            }
        }
    }

    for (auto& [id, player] : _eggs) {
        if (player.isSpawn) {
            player.animationProgress += GetFrameTime();

            if (player.id == 0 && player.animationProgress >= 1.0f) {
                player.isMoving = false;
                player.isWrap = false;
                player.isSpawn = false;
                player.isEstasy = false;
                player.current_animation = IDLE;
                player.animCurrentFrame = 0;
                player.animationProgress = 0;
            }
        }

        if (player.isdying) {
            player.animationProgress += GetFrameTime() / GLOBAL_ANIMATION_DURATION;
            if ( player.id > 0 && player.animationProgress >= 1.0) {
                removePlayer(id);
                break;
            }
            if ( player.id == 0 && player.animationProgress >= 1.0) {
                removePlayer(id);
                break;
            }
        }
    }
}

/*************************************************************************************************

                 ___               ,--,              ___
               ,--.'|_    ,--,   ,--.'|     ,--,   ,--.'|_
         ,--,  |  | :,' ,--.'|   |  | :   ,--.'|   |  | :,'
       ,'_ /|  :  : ' : |  |,    :  : '   |  |,    :  : ' :
  .--. |  | :.;__,'  /  `--'_    |  ' |   `--'_  .;__,'  /       .--,
,'_ /| :  . ||  |   |   ,' ,'|   '  | |   ,' ,'| |  |   |      /_ ./|
|  ' | |  . .:__,'| :   '  | |   |  | :   '  | | :__,'| :   , ' , ' :
|  | ' |  | |  '  : |__ |  | :   '  : |__ |  | :   '  : |__/___/ \: |
:  | : ;  ; |  |  | '.'|'  : |__ |  | '.'|'  : |__ |  | '.'|.  \  ' |
'  :  `--'   \ ;  :    ;|  | '.'|;  :    ;|  | '.'|;  :    ; \  ;   :
:  ,      .-./ |  ,   / ;  :    ;|  ,   / ;  :    ;|  ,   /   \  \  ;
 `--`----'      ---`-'  |  ,   /  ---`-'  |  ,   /  ---`-'     :  \  \
                         ---`-'            ---`-'               \  ' ;
                                                                 `--`
*/

void GuiManager::addPlayer(const trantorian_s& player) {
    _players[player.id] = player;
    
    std::string msg = "Added player ID:" + std::to_string(player.id) + 
                     " Level:" + std::to_string(player.level) + 
                     " Team:" + player.team+
                     " position: x=" + std::to_string(player.pos.x)+
                     " position: y=" + std::to_string(player.pos.y);
    display_smg(msg, 3.0f, GREEN, DARKGREEN);
}

void GuiManager::addEggPlayer(const trantorian_s& player) {
    _eggs[player.id] = player;
}

void GuiManager::removePlayer(int id) {
    _players.erase(id);
}

void GuiManager::removeEggPlayer(int id) {
    _eggs.erase(id);
}

void GuiManager::handleInput() {
    _dashboard.handleInput();
    if (_cursor && !_dashboard.isPlayerFollowed() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        
        Ray ray = GetMouseRay(GetMousePosition(), _camera);
        
        float closestCollisionDist = FLT_MAX;
        bool hasHit = false;

        int hitPlayerId = -1;

        for (auto& [id, player] : _players) {
            if (player.level <= 0) continue;

            Model playerModel = getPlayerModelByLevel(player.level);
            BoundingBox bb = GetModelBoundingBox(playerModel);
            
            Matrix transform = MatrixRotateXYZ({0, getPlayerRotationAngle(player.orientation) * DEG2RAD, 0});
            transform = MatrixMultiply(transform, MatrixTranslate(player.actualPosWithAnimation.x, 0.2f, player.actualPosWithAnimation.y));
            
            bb.min = Vector3Transform(bb.min, transform);
            bb.max = Vector3Transform(bb.max, transform);

            RayCollision collision = GetRayCollisionBox(ray, bb);

            if (collision.hit && collision.distance < closestCollisionDist) {
                closestCollisionDist = collision.distance;
                hitPlayerId = id;
            }
        }

        // Si on a touché un joueur, on le suit et on arrête tout.
        if (hitPlayerId != -1) {
            _dashboard.followPlayer(hitPlayerId);
            _isTileSelected = false;
            return;
        }


        for (int y = 0; y < _height; y++) {
            for (int x = 0; x < _width; x++) {
                Model platformModel = _platforms[y][x]._model_platforms;
                BoundingBox bb = GetModelBoundingBox(platformModel);
                
                Vector3 platformPos = {
                    GET_PLATFORM_POSX(_platforms[y][x].obj_first_position.x, x),
                    _platforms[y][x].obj_first_position.y,
                    GET_PLATFORM_POSZ(_platforms[y][x].obj_first_position.z, y)
                };
                
                bb.min = Vector3Add(bb.min, platformPos);
                bb.max = Vector3Add(bb.max, platformPos);

                RayCollision collision = GetRayCollisionBox(ray, bb);

                if (collision.hit && collision.distance < closestCollisionDist) {
                    closestCollisionDist = collision.distance;
                    _selectedTilePos = { (size_t)x, (size_t)y };
                    hasHit = true;
                }
            }
        }
        _isTileSelected = hasHit;
    }
    
    // Si on fait un clic droit, on désélectionne la tuile
    if (_isTileSelected && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        _isTileSelected = false;
    }

    if (_dashboard.isPlayerFollowed()) {

        if (IsKeyPressed(KEY_U)) {
            _dashboard.stopFollowing();
            _followedPlayerId = -1;

            float x_pos = GET_PLATFORM_POSX(_platforms[0][0].obj_first_position.x, _width)/4;
            float z_pos = GET_PLATFORM_POSZ(_platforms[0][0].obj_first_position.z, _height)/2;
            camMode = CAMERA_FREE;
            _camera.position = (Vector3){ x_pos, 10.0f,  z_pos};
            _camera.target = (Vector3){ 0.0f, -2.0f, 0.0f };
            _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
            _camera.projection = CAMERA_PERSPECTIVE;
            _camera.fovy = 60.0f;
        }
        return;
    }

    if (IsKeyPressed(KEY_C) && !_cursor) {
        EnableCursor();
        _cursor = !_cursor;
        return;
    }

    if (IsKeyPressed(KEY_C) && _cursor) {
        DisableCursor();
        _cursor = !_cursor;
    }


    if (IsKeyPressed(KEY_P)){
            if (_camera.projection == CAMERA_PERSPECTIVE)
            {
                camMode = CAMERA_THIRD_PERSON;

                float othographic_posx = 0.0f;
                float othographic_posy = 0.0f;
                if (_width > 0 && _height > 0) {
                    othographic_posx = GET_PLATFORM_POSX(_platforms[0][0].obj_first_position.x, _width)/2;
                    othographic_posy = GET_PLATFORM_POSZ(_platforms[0][0].obj_first_position.z, _height)/2;

                }

                _camera.position = (Vector3){ 0.0f , (float) (_width + _height), 0.0f};
                _camera.target = (Vector3){ othographic_posx, 1.0f, othographic_posy };
                _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
                _camera.projection = CAMERA_ORTHOGRAPHIC;
                _camera.fovy = 20.0f;
                CameraYaw(&_camera, -135 * DEG2RAD, true);
                CameraPitch(&_camera, -45 * DEG2RAD, true, true, false);
            }
            else if (_camera.projection == CAMERA_ORTHOGRAPHIC)
            {
                float x_pos = GET_PLATFORM_POSX(_platforms[0][0].obj_first_position.x, _width)/4;
                float z_pos = GET_PLATFORM_POSZ(_platforms[0][0].obj_first_position.z, _height)/2;
                camMode = CAMERA_FREE;
                _camera.position = (Vector3){ x_pos, 10.0f,  z_pos};
                _camera.target = (Vector3){ 0.0f, -2.0f, 0.0f };
                _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
                _camera.projection = CAMERA_PERSPECTIVE;
                _camera.fovy = 60.0f;
            }
    }
}

void GuiManager::drawDashBoard() {
    handleFrequencyInput();

    Rectangle freqButtonRect = { 10, (float)GetScreenHeight() - 50, 180, 40 };
    bool isHover = CheckCollisionPointRec(GetMousePosition(), freqButtonRect);

    if (isHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !_isFreqInputActive) {
        _isFreqInputActive = true;
        _freqInputCharCount = 0;
        memset(_freqInputBuffer, 0, sizeof(_freqInputBuffer));
        DisableCursor();
    }
    DrawRectangleRec(freqButtonRect, isHover ? Fade(BLACK, 0.75f) : Fade(BLACK, 0.5f));
    DrawText("Change Speed (f)", freqButtonRect.x + 10, freqButtonRect.y + 10, 20, WHITE);


    if (_isFreqInputActive) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));

        Rectangle inputBox = { (float)GetScreenWidth()/2 - 150, (float)GetScreenHeight()/2 - 50, 300, 50 };
        DrawRectangleRec(inputBox, LIGHTGRAY);
        DrawRectangleLinesEx(inputBox, 2, DARKGRAY);

        DrawText("Enter new frequency and press ENTER:", inputBox.x, inputBox.y - 30, 20, WHITE);

        DrawText(_freqInputBuffer, inputBox.x + 10, inputBox.y + 15, 20, BLACK);

        if ((int)(GetTime() * 2.0f) % 2 == 0) {
            float textWidth = MeasureText(_freqInputBuffer, 20);
            DrawRectangle(inputBox.x + 10 + textWidth, inputBox.y + 15, 2, 20, BLACK);
        }
    }
    _dashboard.draw(_teams, _players);
    if (!_dashboard.isPlayerFollowed() && !_cursor) {
        UpdateCamera(&_camera, camMode);
        std::string helpMessage =   "HELP TAGBOX:\n"
                                    "Press 'C' to toggle cursor\n"
                                    "Press 'P' to change camera view\n"
                                    "Press 'R' to move camera up\n"
                                    "Press 'T' to move camera down\n"
                                    "Press 'Z' to move the camera forward\n"
                                    "Press 'Q' to move the camera left\n"
                                    "Press 'S' to move the camera backwards\n"
                                    "Press 'D' to move the camera right\n"
                                    "Press 'A' to turn the camera to the right\n"
                                    "Press 'E' to turn the camera to the left\n"
                                    "Click on 'Teams' to open the dashboard";
        drawHelpBox(helpMessage);
    } else if (_dashboard.getFollowedPlayerId() == -1) {
        std::string helpMessage =   "HELP TAGBOX:\n"
                                    "Click on 'Teams' box\n"
                                    "Press 'C' to toggle cursor and continue navigation\n"
                                    "Select a team and touch a player to follow\n"
                                    "Press 'U' to unfollow";
        drawHelpBox(helpMessage);
    }
    else {
        std::string followHelp =    "HELP TAGBOX:\n"
                                    "Following Player ID: " + std::to_string(_dashboard.getFollowedPlayerId()) + "\n"
                                    "Press 'U' to unfollow";
        drawHelpBox(followHelp, true);
    }
}

void GuiManager::drawSelectedTileInfo() {
    if (!_isTileSelected) return;

    int x = _selectedTilePos.x;
    int y = _selectedTilePos.y;
    const tile_s& tile = _map[y][x];

    std::string content = TextFormat("Tile (%d, %d)\n\n", x, y);
    content += TextFormat(" Food: %d\n", tile.food);
    content += TextFormat(" Linemate: %d\n", tile.linemate);
    content += TextFormat(" Deraumere: %d\n", tile.deraumere);
    content += TextFormat(" Sibur: %d\n", tile.sibur);
    content += TextFormat(" Mendiane: %d\n", tile.mendiane);
    content += TextFormat(" Phiras: %d\n", tile.phiras);
    content += TextFormat(" Thystame: %d\n\n", tile.thystame);

    content += "Players on tile:\n";
    bool anyPlayer = false;
    for (const auto& pair : _players) {
        if (pair.second.pos.x == (std::size_t ) x && pair.second.pos.y == (std::size_t ) y) {
            content += TextFormat(" - ID: %d (Lvl %d)\n", pair.second.id, pair.second.level);
            anyPlayer = true;
        }
    }
    if (!anyPlayer) {
        content += " (none)\n";
    }

    Vector2 panelPosition = { GetScreenWidth() - 350.0f, 250.0f };
    std::string title = TextFormat("Tile (%d, %d) Content", x, y);
    if (_cursor)
        drawInfoPanel(title, content, panelPosition);
}

void GuiManager::render() {
    BeginDrawing();
        ClearBackground(RAYWHITE);
        drawScene();
        drawTempMessages();
        drawDashBoard();
        drawSelectedTileInfo();

        // Debug information
        std::string debugInfo = "Players: " + std::to_string(_players.size()) + 
                               " | Eggs: " + std::to_string(_eggs.size()) + 
                               " | Teams: " + std::to_string(_teams.size()) +
                               " | Map: " + std::to_string(_width) + "x" + std::to_string(_height);
        DrawText(debugInfo.c_str(), 10, 30, 20, BLACK);

        // Show player details
        int yOffset = 60;
        for (auto& [id, player] : _players) {
            std::string playerInfo = "ID:" + std::to_string(player.id) + 
                                   " Lvl:" + std::to_string(player.level) + 
                                   " Pos:(" + std::to_string(player.pos.x) + "," + std::to_string(player.pos.y) + ")" +
                                   " Team:" + player.team;
            DrawText(playerInfo.c_str(), 10, yOffset, 15, BLACK);
            yOffset += 20;
        }

        if (!_winner.empty()) {
            DrawRectangle(0, GetScreenHeight()/2 - 30, GetScreenWidth(), 60, Fade(LIGHTGRAY, 0.8f));
            DrawText(_winner.c_str(),
                     GetScreenWidth()/2 - MeasureText(_winner.c_str(), 30)/2,
                     GetScreenHeight()/2 - 15, 30, BLACK);
        }

        for (auto& [id, player] : _players) {
            if (player.level < 1) continue;

            Vector3 cubePosition = { (float) player.actualPosWithAnimation.x, 0.20f, (float) player.actualPosWithAnimation.y };
            Vector2 cubeScreenPosition = { 0.0f, 0.0f };
            cubeScreenPosition = GetWorldToScreen((Vector3){cubePosition.x, cubePosition.y + 2.5f, cubePosition.z}, _camera);

            // Temporarily disable view culling for debugging
            // if (!isPlayerInView(cubePosition) || _dashboard.getFollowedPlayerId() == -1) continue;

            std::string text = "Team: " + player.team + "\nID: " + std::to_string(player.id);
            DrawText(text.c_str(), (int)cubeScreenPosition.x - MeasureText(text.c_str(), 20)/2, (int)cubeScreenPosition.y, 20, BLACK);
        }
        DrawFPS(90, 0);
    EndDrawing();
}

void GuiManager::display_for_a_moment(std::string message, double duration, Color message_color, Color box_color, pos_t pos) {
    _tempMessages.push_back({message, duration, GetTime(), message_color,box_color, pos});
}

void GuiManager::display_smg(std::string message, double duration, Color message_color, Color box_color) {
    pos_t pos = { (std::size_t)(GetScreenWidth() / 2.0f - MeasureText(message.c_str(), FONT_TEMP_MESSAGE_SIZE)), 15 };
    _tempMessages.push_back({message, duration, GetTime(), message_color, box_color, pos});
}

bool GuiManager::isPlayerAnimating(int id)
{
    auto it = _players.find(id);
    if (it != _players.end()) {
        return it->second.isMoving || it->second.isLayingEgg || it->second.isPicking || 
               it->second.isDroping  || it->second.isExpulse;
    }
    return false;
}

void GuiManager::move_and_slide_animation(int id, pos_t start_pos, pos_t end_pos, orient_e new_orientation)
{
    auto it = _players.find(id);
    if (it == _players.end() || it->second.isMoving) return;

    trantorian_s& player = it->second;
    
    player.pos = start_pos;
    player.targetPos = end_pos;
    player.orientation = new_orientation;
    display_smg("Player is going from:(" + std::to_string(start_pos.x) + ", " + std::to_string(start_pos.y) +
                ") to :(" + std::to_string(end_pos.x) + ", " + std::to_string(end_pos.y)+ ")", 5.0, WHITE, MAROON) ;

    
    int dx = (int)end_pos.x - (int)start_pos.x;
    int dy = (int)end_pos.y - (int)start_pos.y;
    player.isWrap = (abs(dx) > 1 || abs(dy) > 1);
    if (player.isWrap) {
    }
    
    player.isMoving = true;
    player.current_animation = WALK;
    player.animationProgress = 0.0f;

    Vector3 soundPos = { player.actualPosWithAnimation.x, 0.5f, player.actualPosWithAnimation.y };
    _audioManager.PlaySoundAt(WALK, soundPos, _camera);
}

void GuiManager::makePlayerDie(int id) {
    auto it = _players.find(id);
    if (it == _players.end()) return;

    trantorian_s& player = it->second;
    display_smg("Player " + std::to_string(id) + " has died.", 5.0, RED, MAROON);

    if (player.isdying) return;
    player.isdying = true;
    player.current_animation = DIE;
    player.animationProgress = 0.0f;
    Vector3 soundPos = { player.actualPosWithAnimation.x, 0.5f, player.actualPosWithAnimation.y };
    _audioManager.PlaySoundAt(player.current_animation, soundPos, _camera);
}

void GuiManager::makeEggDie(int id) {
    auto it = _eggs.find(id);
    if (it == _eggs.end()) return;

    trantorian_s& player = it->second;
    display_smg("Egg " + std::to_string(id) + " has died.", 5.0, RED, MAROON);

    if (player.isdying) return;
    player.isdying = true;
    player.current_animation = DIE;
    player.animationProgress = 0.0f;
    Vector3 soundPos = { player.actualPosWithAnimation.x, 0.5f, player.actualPosWithAnimation.y };
    _audioManager.PlaySoundAt(player.current_animation, soundPos, _camera);
}

void GuiManager::makePlayerSpawn(int id){
    auto it = _players.find(id);
    if (it == _players.end()) return;

    trantorian_s& player = it->second;

    if (player.isSpawn) return;
    display_smg("Player " + std::to_string(id) + " has hatched!", 4.0, LIME, DARKGREEN);
    player.isSpawn = true;
    player.current_animation = SPAWN;
    player.animationProgress = 0.0f;
    Vector3 soundPos = { player.actualPosWithAnimation.x, 0.5f, player.actualPosWithAnimation.y };
    _audioManager.PlaySoundAt(player.current_animation, soundPos, _camera);
}

void GuiManager::makeEggSpawn(int id){
    auto it = _eggs.find(id);
    if (it == _eggs.end()) return;

    trantorian_s& player = it->second;

    if (player.isSpawn) return;
    display_smg("Egg " + std::to_string(id) + " has hatched!", 4.0, LIME, DARKGREEN);
    player.isSpawn = true;
    player.current_animation = SPAWN;
    player.animationProgress = 0.0f;
    Vector3 soundPos = { player.actualPosWithAnimation.x, 0.5f, player.actualPosWithAnimation.y };
    _audioManager.PlaySoundAt(player.current_animation, soundPos, _camera);
}

void GuiManager::makePlayerLayEgg(int id){
    auto it = _players.find(id);
    if (it == _players.end()) return;

    trantorian_s& player = it->second;

    if (player.isLayingEgg) return;
     display_smg("Player " + std::to_string(id) + " is laying an egg!", 4.0, SKYBLUE, DARKBLUE); 
    player.isLayingEgg = true;
    player.current_animation = LAY;
    player.animationProgress = 0.0f;
    Vector3 soundPos = { player.actualPosWithAnimation.x, 0.5f, player.actualPosWithAnimation.y };
    _audioManager.PlaySoundAt(player.current_animation, soundPos, _camera);
}

void GuiManager::makePlayerDrop(int id){
    auto it = _players.find(id);
    if (it == _players.end()) return;

    trantorian_s& player = it->second;

    if (player.isDroping) return;
    display_smg("Player " + std::to_string(id) + " dropped an item.", 3.0, WHITE, GRAY);
    player.isDroping = true;
    player.current_animation = DROP;
    player.animationProgress = 0.0f;
    Vector3 soundPos = { player.actualPosWithAnimation.x, 0.5f, player.actualPosWithAnimation.y };
    _audioManager.PlaySoundAt(player.current_animation, soundPos, _camera);
}

void GuiManager::makePlayerPick(int id){
    auto it = _players.find(id);
    if (it == _players.end()) return;

    trantorian_s& player = it->second;

    if (player.isPicking) return;
     display_smg("Player " + std::to_string(id) + " picked up an item.", 3.0, LIME, DARKGREEN);
    player.isPicking = true;
    player.current_animation = PICK;
    player.animationProgress = 0.0f;
    Vector3 soundPos = { player.actualPosWithAnimation.x, 0.5f, player.actualPosWithAnimation.y };
    _audioManager.PlaySoundAt(player.current_animation, soundPos, _camera);
}

void GuiManager::makePlayerBroadCast(int id){
    auto it = _players.find(id);
    if (it == _players.end()) return;

    trantorian_s& player = it->second;
    player.bcPos = player.pos;

    if (player.isBroadCast) return;
    display_smg("Player " + std::to_string(id) + " is broadcasting a message!", 4.0, LIME, DARKBLUE);
    player.isBroadCast = true;
    //player.current_animation = SPAWN;
    player.animationProgress = 0.0f;
    Vector3 soundPos = { player.actualPosWithAnimation.x, 0.5f, player.actualPosWithAnimation.y };
    _audioManager.PlaySoundAt(BROADCAST, soundPos, _camera);
}

void GuiManager::makePlayerToExpulseAnother(int id){
    auto it = _players.find(id);
    if (it == _players.end()) return;

    trantorian_s& player = it->second;

    if (player.isExpulse) return;
    display_smg("Player " + std::to_string(id) + " is expelling others!", 4.0, ORANGE, MAROON);
    player.isExpulse = true;
    player.bcPos = player.pos;
    player.current_animation = EXPULSE;
    player.animationProgress = 0.0f;
    Vector3 soundPos = { player.actualPosWithAnimation.x, 0.5f, player.actualPosWithAnimation.y };
    _audioManager.PlaySoundAt(player.current_animation, soundPos, _camera);
}

void GuiManager::makePlayerToIdle(int id){
    auto it = _players.find(id);
    if (it == _players.end()) return;

    trantorian_s& player = it->second;

    // if (player.isExpulse) return;
    // player.isExpulse = true;
    // player.bcPos = player.pos;
    player.current_animation = IDLE;
    player.animationProgress = 0.0f;
    Vector3 soundPos = { player.actualPosWithAnimation.x, 0.5f, player.actualPosWithAnimation.y };
    _audioManager.PlaySoundAt(player.current_animation, soundPos, _camera);
}

void GuiManager::makePlayerExtasy(int id){
    auto it = _players.find(id);
    if (it == _players.end()) return;

    trantorian_s& player = it->second;

    if (player.isEstasy) return;
    display_smg("Incantation started near player " + std::to_string(id) + "!", 5.0, GOLD, PURPLE);
    player.isEstasy = true;
    player.current_animation = ECSTASY;
    player.animationProgress = 0.0f;
    Vector3 soundPos = { player.actualPosWithAnimation.x, 0.5f, player.actualPosWithAnimation.y };
    _audioManager.PlaySoundAt(player.current_animation, soundPos, _camera);
}

void GuiManager::makePlayerStopExtasy(int id){//
    auto it = _players.find(id);
    if (it == _players.end()) return;

    trantorian_s& player = it->second;

 display_smg("Incantation has been cancelled.", 4.0, YELLOW, MAROON);
    player.isMoving = false;
    player.isWrap = false;
    player.isSpawn = false;
    player.isEstasy = false;
    player.current_animation = IDLE;
    player.animCurrentFrame = 0;
    player.animationProgress = 0;
    Vector3 soundPos = { player.actualPosWithAnimation.x, 0.5f, player.actualPosWithAnimation.y };
    _audioManager.PlaySoundAt(CANCEL, soundPos, _camera);
}



//  /$$$$$$$  /$$   /$$ /$$   /$$ /$$   /$$ /$$$$$$$$ /$$$$$$$
// | $$__  $$| $$  | $$| $$$ | $$| $$$ | $$| $$_____/| $$__  $$
// | $$  \ $$| $$  | $$| $$$$| $$| $$$$| $$| $$      | $$  \ $$
// | $$$$$$$/| $$  | $$| $$ $$ $$| $$ $$ $$| $$$$$   | $$$$$$$/
// | $$__  $$| $$  | $$| $$  $$$$| $$  $$$$| $$__/   | $$__  $$
// | $$  \ $$| $$  | $$| $$\  $$$| $$\  $$$| $$      | $$  \ $$
// | $$  | $$|  $$$$$$/| $$ \  $$| $$ \  $$| $$$$$$$$| $$  | $$
// |__/  |__/ \______/ |__/  \__/|__/  \__/|________/|__/  |__/


void GuiManager::UpdateAndDrawFrame() {
    if (!shouldClose() && _gameState == STATE_PLAYING) {

        switch (_gameState) {
            case STATE_LOADING:
            UpdateAndDrawLoadingScreen();
            break;
            case STATE_PLAYING:
            UpdateAndDrawPlayingScreen();
            break;
        }
    }
}

void GuiManager::startRunGameLoop() {
    while (!shouldClose() && _gameState == STATE_LOADING) {
        UpdateAndDrawLoadingScreen();
    }
}

void GuiManager::stopRunGameLoop() {
    for (int i = 0; i < 7; i++) {
        UnloadModel(_ressources_models[i]);
    }

    UnloadModel(model_floor);

    UnloadModel(_model_platforms_1);
    UnloadModel(_model_platforms_2);
    UnloadModel(_model_platforms_3);
    UnloadModel(_model_platforms_4);
    UnloadModel(_model_platforms_5);
    UnloadModel(_model_platforms_6);
    UnloadModel(_model_platforms_7);
    UnloadModel(_model_platforms_8);
    UnloadModel(_model_platforms_9);
    UnloadModel(_model_platforms_10);
    UnloadModel(_model_bridge);
    UnloadModel(_model_portal);

    UnloadShader(water_shader);
    UnloadTexture(water_perlinNoiseMap);
    UnloadShader(skybox.materials[0].shader);
    UnloadTexture(skyboxTextureDay);
    UnloadTexture(skyboxTextureDayBlue);
    UnloadTexture(skyboxTextureDaySunSet);
    UnloadTexture(skyboxTextureNight);
    UnloadTexture(skyboxTextureNightPurple);
    UnloadTexture(skyboxTextureNightSkySky);
    UnloadModel(skybox);
    UnloadShader(shdrCubemap);
    UnloadShader(light_shader);

    UnloadModel(_model_egg);
    UnloadModel(_char_level1);
    UnloadModel(_char_level2);
    UnloadModel(_char_level3);
    UnloadModel(_char_level4);
    UnloadModel(_char_level5);
    UnloadModel(_char_level6);
    UnloadModel(_char_level7);
    UnloadModel(_char_level8);

    UnloadFont(tempMessagesFont);

    // UnloadModelAnimations(_animation_level0, _animation_level0_count);
    UnloadModelAnimations(_animation_level1, _animation_level1_count);
    UnloadModelAnimations(_animation_level2, _animation_level2_count);
    UnloadModelAnimations(_animation_level3, _animation_level3_count);
    UnloadModelAnimations(_animation_level4, _animation_level4_count);
    UnloadModelAnimations(_animation_level5, _animation_level5_count);
    UnloadModelAnimations(_animation_level6, _animation_level6_count);
    UnloadModelAnimations(_animation_level7, _animation_level7_count);
    UnloadModelAnimations(_animation_level8, _animation_level8_count);


    CloseWindow();
}

// Dans guimanager.cpp

void GuiManager::handleFrequencyInput()
{
    if (!_isFreqInputActive) return;

    int key = GetCharPressed();

    while (key > 0) {
        if ((key >= '0' && key <= '9') || (key == '.' && strchr(_freqInputBuffer, '.') == NULL)) {
            if (_freqInputCharCount < 15) {
                _freqInputBuffer[_freqInputCharCount] = (char)key;
                _freqInputCharCount++;
                _freqInputBuffer[_freqInputCharCount] = '\0';
            }
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (_freqInputCharCount > 0) {
            _freqInputCharCount--;
            _freqInputBuffer[_freqInputCharCount] = '\0';
        }
    }

    if (IsKeyPressed(KEY_ENTER)) {
        try {
            float newFreq = std::stof(_freqInputBuffer);
            if (newFreq > 0) {
                setSst(newFreq);
                display_smg("Frequency change request sent: " + std::string(_freqInputBuffer), 5.0, LIME, DARKGREEN);
            } else {
                display_smg("Error: Frequency must be positive.", 5.0, YELLOW, MAROON);
            }
        } catch (const std::invalid_argument& e) {
            display_smg("Error: Invalid number format.", 5.0, YELLOW, MAROON);
        }

        _isFreqInputActive = false;
        EnableCursor();
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        _isFreqInputActive = false;
        EnableCursor();
    }
}

/***********************************************************************************************
      ,---,
    ,---.'|  __  ,-.                   .---.            __  ,-.
    |   | :,' ,'/ /|                  /. ./|          ,' ,'/ /|  .--.--.
    |   | |'  | |' | ,--.--.       .-'-. ' |   ,---.  '  | |' | /  /    '
  ,--.__| ||  |   ,'/       \     /___/ \: |  /     \ |  |   ,'|  :  /`./
 /   ,'   |'  :  / .--.  .-. | .-'.. '   ' . /    /  |'  :  /  |  :  ;_
.   '  /  ||  | '   \__\/: . ./___/ \:     '.    ' / ||  | '    \  \    `.
'   ; |:  |;  : |   ," .--.; |.   \  ' .\   '   ;   /|;  : |     `----.   \
|   | '/  '|  , ;  /  /  ,.  | \   \   ' \ |'   |  / ||  , ;    /  /`--'  /
|   :    :| ---'  ;  :   .'   \ \   \  |--" |   :    | ---'    '--'.     /
 \   \  /         |  ,     .-./  \   \ |     \   \  /            `--'---'
  `----'           `--`---'       '---"       `----'
*/



void GuiManager::drawScene() {
    std::map<pos_t, std::vector<int>> playersOnTiles;
    for (auto& [id, player] : _players) {
        playersOnTiles[player.pos].push_back(id);
    }

    std::map<int, Vector3> playerOffsets;

    const float TILE_SPREAD = 1.5f;
    std::vector<Vector3> gridPositions = {
        { 0.0f, 0.0f,  0.0f }, // 1. Centre
        { -TILE_SPREAD, 0.0f, -TILE_SPREAD }, // 2. Coin H-G
        { TILE_SPREAD, 0.0f, TILE_SPREAD }, // 3. Coin B-D
        { -TILE_SPREAD, 0.0f, TILE_SPREAD }, // 4. Coin B-G
        { TILE_SPREAD, 0.0f, -TILE_SPREAD }, // 5. Coin H-D
        { 0.0f, 0.0f, -TILE_SPREAD }, // 6. Milieu Haut
        { 0.0f, 0.0f, TILE_SPREAD }, // 7. Milieu Bas
        { -TILE_SPREAD, 0.0f, 0.0f }, // 8. Milieu Gauche
        { TILE_SPREAD, 0.0f, 0.0f }  // 9. Milieu Droite
    };

    const float PLAYER_STACK_HEIGHT = 2.0f;
    for (auto& [pos, playerIds] : playersOnTiles) {
        if (playerIds.size() > 1) {
            for (size_t i = 0; i < playerIds.size(); i++) {
                int playerId = playerIds[i];
                Vector3 offset = gridPositions[i % 9];
                int stackLevel = i/9;
                offset.y = stackLevel * PLAYER_STACK_HEIGHT;
                playerOffsets[playerId] = offset;
            }
        } else if (!playerIds.empty()) {
            playerOffsets[playerIds[0]] = {0.0f, 0.0f, 0.0f};
        }
    }

    BeginMode3D(_camera);
        drawShaderSkybox();
        drawShader();
        // DrawGrid(100, 1.0);

        BeginShaderMode(light_shader);
            drawLights();
            drawFloor();
                for (int x = 0; x < _height; x++) {
                    for (int y = 0; y < _width; y++) {
                        drawTile(_map[y][x], GET_PLATFORM_POSX(0, x) , GET_PLATFORM_POSZ(0, y));
                    }
                }
                
                // Debug: Count players being rendered
                int renderedPlayers = 0;
                for (auto& [id, player] : _players) {
                    Vector3 offset = playerOffsets.count(id) ? playerOffsets.at(id) : Vector3{0, 0, 0};
                    drawPlayer(player, offset );
                    renderedPlayers++;
                }
                
                // Debug: Count eggs being rendered
                int renderedEggs = 0;
                for (auto& [id, player] : _eggs) {
                    Vector3 offset = playerOffsets.count(id) ? playerOffsets.at(id) : Vector3{0, 0, 0};
                    drawPlayer(player, offset );
                    renderedEggs++;
                }
        EndShaderMode();
        
        // Debug: Display rendering info
        std::string renderInfo = "Rendered: " + std::to_string(renderedPlayers) + " players, " + 
                                std::to_string(renderedEggs) + " eggs";
        DrawText(renderInfo.c_str(), 10, 10, 15, RED);
        
        std::map<pos_t, float> incantations;
        for (auto& [id, player] : _players) {
            if (player.isEstasy) {
                incantations[player.pos] = player.animationProgress;
            }
        }

        for (auto& [pos, progress] : incantations) {
            Vector3 worldPos = { (float)GET_PLATFORM_POSX(0, pos.x), 0.2f, (float)GET_PLATFORM_POSZ(0, pos.y) };
            drawIncantationEffect(worldPos, progress);
        }
        for (auto& [id, player] : _players) {
            drawPlayerAura(player);
        }

    EndMode3D();
}

void GuiManager::drawFloor() {

    for (int j = 0; j < _height; j++) {
        for (int i = 0; i < _width; i++) {
            Vector3 floor_position = _platforms[j][i].obj_first_position;
            Vector3 scale_ = _platforms[j][i].obj_scale;
            Vector3 floor_axis = {0.0f, 0.0f, 0.0f};

            float offset = (sinf(_levitateTime * 4.0f + j + i) * 0.1f + 0.3f)/2.0;

            floor_position.x = GET_PLATFORM_POSX(floor_position.x, i);
            floor_position.z = GET_PLATFORM_POSZ(floor_position.z, j);
            floor_position.y += (sinf(_levitateTime * 4.0f + j + i) * 0.1f + 0.3f)/2.0;

            DrawModelEx(_platforms[j][i]._model_platforms, floor_position, floor_axis, 0.0f, scale_, WHITE);
            if (j + 1 != _height) {
                Vector3 bridge_position = BRIDGE_FIRST_POS;

                bridge_position = {
                    bridge_position.x + floor_position.x + (float) (GRID_SIZE/2.0),
                    bridge_position.y +  floor_position.y,
                    bridge_position.z+ floor_position.z + (float) (GRID_SIZE/2.0)
                };

                bridge_position.y = Clamp(bridge_position.y, -0.30f, 1.0f) + offset/2.0f;

                DrawModelEx(_model_bridge, bridge_position, floor_axis, 0.0f, BRIDGE_SCALE, WHITE);

            }
            if (j + 1 == _height) {//AB
                Vector3 portal_position = PORTAL_FIRST_POS;

                portal_position = {
                    portal_position.x + floor_position.x,
                    portal_position.y +  floor_position.y,
                    portal_position.z+ floor_position.z + GRID_SIZE*2
                };

                portal_position.y = Clamp(portal_position.y, -0.30f, 1.0f) + offset/2.0f;

                DrawModelEx(_model_portal, portal_position, (Vector3){0.0f, 1.0f, 0.0f} , 180.0f, PORTAL_SCALE, WHITE);
            }
            if (j >= 0 && i == 0) {//BC
                Vector3 portal_position = PORTAL_FIRST_POS;

                portal_position = {
                    portal_position.x + floor_position.x- GRID_SIZE*2,
                    portal_position.y +  floor_position.y,
                    portal_position.z+ floor_position.z
                };

                portal_position.y = Clamp(portal_position.y, -0.30f, 1.0f) + offset/2.0f;

                DrawModelEx(_model_portal, portal_position, (Vector3){0.0f, 1.0f, 0.0f} , 90.0f, PORTAL_SCALE, WHITE);
            }

            if (i + 1 == _height) {//AD
                Vector3 portal_position = PORTAL_FIRST_POS;

                portal_position = {
                    portal_position.x + floor_position.x + GRID_SIZE*2,
                    portal_position.y +  floor_position.y,
                    portal_position.z+ floor_position.z
                };

                portal_position.y = Clamp(portal_position.y, -0.30f, 1.0f) + offset/2.0f;

                DrawModelEx(_model_portal, portal_position, (Vector3){0.0f, 1.0f, 0.0f} , 270.0f, PORTAL_SCALE, WHITE);
            }
            if (i  >= 0 && j ==0) {
                Vector3 portal_position = PORTAL_FIRST_POS;

                portal_position = {
                    portal_position.x + floor_position.x ,
                    portal_position.y +  floor_position.y,
                    portal_position.z+ floor_position.z- GRID_SIZE*2
                };

                portal_position.y = Clamp(portal_position.y, -1.0f, 1.0f) + offset/2.0f;

                DrawModelEx(_model_portal, portal_position, (Vector3){0.0f, 1.0f, 0.0f} , 0.0f, PORTAL_SCALE, WHITE);
            }

            if (i != 0 && i != _width) {
                Vector3 bridge_axis = {0.0f, 1.0f, 0.0f};
                Vector3 bridge_position = BRIDGE_FIRST_POS;

                bridge_position = {
                    bridge_position.x + floor_position.x - (float) (GRID_SIZE/2.0),
                    bridge_position.y +  floor_position.y,
                    bridge_position.z + floor_position.z - (float) (GRID_SIZE/2.0)
                };

                bridge_position.y = Clamp(bridge_position.y, -1.0f, 1.0f) + offset/2.0f;

                DrawModelEx(_model_bridge, bridge_position, bridge_axis, 90.0f, BRIDGE_SCALE, WHITE);
            }
        }
    }

}

void GuiManager::drawShader() {
    rlActiveTextureSlot(2);
    rlEnableTexture(water_perlinNoiseMap.id);

    auto give_current_sky_index = [](float _hour) -> int {
        if (_hour >= 6 && _hour < 12) return 0;
        if (_hour >= 12 && _hour < 16) return 1;
        if (_hour >= 16 && _hour < 20) return 2;
        if (_hour >= 20 && _hour < 24) return 3;
        if (_hour >= 0 && _hour < 3) return 4;
        if (_hour >= 3 && _hour < 6) return 5;
        return 0;
    };
    auto give_blend_factor = [](float _hour) -> float {
        if (_hour >= 6 && _hour < 12) return (_hour - 6.0f) / 6.0f;
        if (_hour >= 12 && _hour < 16) return (_hour - 12.0f) / 4.0f;
        if (_hour >= 16 && _hour < 20) return (_hour - 16.0f) / 4.0f;
        if (_hour >= 20 && _hour < 24) return (_hour - 20.0f) / 4.0f;
        if (_hour >= 0 && _hour < 3) return _hour / 3.0f;
        if (_hour >= 3 && _hour < 6) return (_hour - 3.0f) / 3.0f;
        return 0.0f;
    };

    int currentIndex = give_current_sky_index(_hour);
    int nextIndex = (currentIndex + 1) % 6;
    float blend = give_blend_factor(_hour);

    TextureCubemap skyboxes[6] = {
        skyboxTextureDay, skyboxTextureDayBlue, skyboxTextureDaySunSet,
        skyboxTextureNightPurple, skyboxTextureNight, skyboxTextureNightSkySky
    };

    rlActiveTextureSlot(3);
    rlEnableTextureCubemap(skyboxes[currentIndex].id);

    rlActiveTextureSlot(4);
    rlEnableTextureCubemap(skyboxes[nextIndex].id);

    BeginShaderMode(water_shader);

        int perlinLoc = GetShaderLocation(water_shader, "perlinNoiseMap");
        int skybox1Loc = GetShaderLocation(water_shader, "skybox1");
        int skybox2Loc = GetShaderLocation(water_shader, "skybox2");
        int blendFactorLoc = GetShaderLocation(water_shader, "blendFactor");

        int perlinTexUnit = 2;
        int skybox1TexUnit = 3;
        int skybox2TexUnit = 4;

        SetShaderValue(water_shader, perlinLoc, &perlinTexUnit, SHADER_UNIFORM_INT);
        SetShaderValue(water_shader, skybox1Loc, &skybox1TexUnit, SHADER_UNIFORM_INT);
        SetShaderValue(water_shader, skybox2Loc, &skybox2TexUnit, SHADER_UNIFORM_INT);

        SetShaderValue(water_shader, blendFactorLoc, &blend, SHADER_UNIFORM_FLOAT);

        DrawModel(model_floor, (Vector3){ GET_PLATFORM_POSX(0, _width)/2.0f , -3.85f, GET_PLATFORM_POSZ(0, _height)/2.0f }, 1.0f, WHITE);

    EndShaderMode();

    rlActiveTextureSlot(0);
}

void GuiManager::drawLights() {
    float cameraPos[3] = { _camera.position.x, _camera.position.y, _camera.position.z };
    SetShaderValue(light_shader, light_shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
    for (int i = 0; i < MAX_LIGHTS; i++) UpdateLightValues(light_shader, _lights[i]);


    if ((_hour >= 4.0f) && (_hour < 18.0f-1.f)) {
        float t = (_hour - 8.0f) / 16.0f;     // 0 → 1
        float angle = t * 2*PI;

        Vector3 sunInitial = SUN_INITIAL_POSITION(_width/2, _height/2);

        _lights[_sunLightIndex].position.x = sunInitial.x + SUN_DISTANCE_ROTATION((_width+_height)/2) * cosf(angle);
        _lights[_sunLightIndex].position.y = sunInitial.y + SUN_DISTANCE_ROTATION((_width+_height)/2) * sinf(angle);
        _lights[_sunLightIndex].position.z = sunInitial.z;

        _lights[_sunLightIndex].enabled = true;
    } else {
        float angle = 0.0f;
        Vector3 sunInitial = SUN_INITIAL_POSITION(_width/2, _height/2);

        _lights[_sunLightIndex].position.x = sunInitial.x + SUN_DISTANCE_ROTATION((_width+_height)/2) * cosf(angle);
        _lights[_sunLightIndex].position.y = sunInitial.y + SUN_DISTANCE_ROTATION((_width+_height)/2) * sinf(angle);
        _lights[_sunLightIndex].position.z = sunInitial.z;

        _lights[_sunLightIndex].enabled = false;
    }

    if ((_hour >= 20.0f) || (_hour < 4.0f)) {
         float t = (_hour >= 20.0f) ? (_hour - 20.0f) / 8.0f : (_hour+4.0f) / 8.0f;
        float angle = t *PI;  // 0 → 180°

        Vector3 moonInitial = MOON_INITIAL_POSITION(_width/2, _height/2);

        _lights[_moonLightIndex].position.x = moonInitial.x + MOON_DISTANCE_ROTATION((_width+_height)/2) * cosf(angle);
        _lights[_moonLightIndex].position.y = moonInitial.y + MOON_DISTANCE_ROTATION((_width+_height)/2) * sinf(angle);
        _lights[_moonLightIndex].position.z = moonInitial.z;

        _lights[_moonLightIndex].enabled = true;
    } else {
        float angle = 0.0f;
        Vector3 moonInitial = MOON_INITIAL_POSITION(_width/2, _height/2);

        _lights[_moonLightIndex].position.x = moonInitial.x + MOON_DISTANCE_ROTATION((_width+_height)/2) * cosf(angle);
        _lights[_moonLightIndex].position.y = moonInitial.y + MOON_DISTANCE_ROTATION((_width+_height)/2) * sinf(angle);
        _lights[_moonLightIndex].position.z = moonInitial.z;

        _lights[_moonLightIndex].enabled = false;
    }


    for (int i = 0; i < MAX_LIGHTS; i++){
        if (_lights[i].enabled && i < MAX_LIGHTS/2) DrawSphereEx(_lights[i].position, SUN_RADIUS, 50, 50, _lights[i].color);
    }
}

void GuiManager:: drawShaderSkybox() {
    TextureCubemap skyboxes[6] = {
        skyboxTextureDay, skyboxTextureDayBlue, skyboxTextureDaySunSet,
        skyboxTextureNightPurple, skyboxTextureNight, skyboxTextureNightSkySky
    };
    auto give_blend_factor = [](float _hour) -> float {
        if (_hour >= 6 && _hour < 12) return (_hour - 6.0f) / 6.0f;
        if (_hour >= 12 && _hour < 16) return (_hour - 12.0f) / 4.0f;
        if (_hour >= 16 && _hour < 20) return (_hour - 16.0f) / 4.0f;
        if (_hour >= 20 && _hour < 24) return (_hour - 20.0f) / 4.0f;
        if (_hour >= 0 && _hour < 3) return _hour / 3.0f;
        if (_hour >= 3 && _hour < 6) return (_hour - 3.0f) / 3.0f;
        return 0.0f;
    };
    auto give_current_sky_index = [](float _hour) -> int {
        if (_hour >= 6 && _hour < 12) return 0;
        if (_hour >= 12 && _hour < 16) return 1;
        if (_hour >= 16 && _hour < 20) return 2;
        if (_hour >= 20 && _hour < 24) return 3;
        if (_hour >= 0 && _hour < 3) return 4;
        if (_hour >= 3 && _hour < 6) return 5;
        return 0;
    };
    float blend = give_blend_factor(_hour);
    int currentIndex = give_current_sky_index(_hour);
    int nextIndex = (currentIndex + 1) % 6;

    skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = skyboxes[currentIndex];
    skybox.materials[0].maps[MATERIAL_MAP_IRRADIANCE].texture = skyboxes[nextIndex];

    Shader shader = skybox.materials[0].shader;
    int loc_blendFactor = GetShaderLocation(shader, "blendFactor");
    int loc_rotAngle    = GetShaderLocation(shader, "rotationAngle");
    int loc_vflipped    = GetShaderLocation(shader, "vflipped");
    int loc_doGamma     = GetShaderLocation(shader, "doGamma");

    static bool samplers_set = false;
    if (!samplers_set) {
        int loc1 = GetShaderLocation(shader, "environmentMap");
        int loc2 = GetShaderLocation(shader, "environmentMap2");
        int slot1 = MATERIAL_MAP_CUBEMAP;
        int slot2 = MATERIAL_MAP_IRRADIANCE;
        SetShaderValue(shader, loc1, &slot1, SHADER_UNIFORM_INT);
        SetShaderValue(shader, loc2, &slot2, SHADER_UNIFORM_INT);
        samplers_set = true;
    }

    BeginShaderMode(shader);
        SetShaderValue(shader, loc_blendFactor, &blend, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, loc_rotAngle, &_skyRotation, SHADER_UNIFORM_FLOAT);
        int vflipped_int = _vflipped ? 1 : 0;
        int doGamma_int = value_dogamma ? 1 : 0;
        SetShaderValue(shader, loc_vflipped, &vflipped_int, SHADER_UNIFORM_INT);
        SetShaderValue(shader, loc_doGamma, &doGamma_int, SHADER_UNIFORM_INT);

        rlDisableBackfaceCulling();
        rlDisableDepthMask();
            DrawModelEx(skybox, (Vector3){0, 0, 0},(Vector3){0, 1, 0}, 0.0f, (Vector3){1000, 1000, 1000}, WHITE);
        rlEnableBackfaceCulling();
        rlEnableDepthMask();
    EndShaderMode();
}

void GuiManager::drawTile(const tile_s& tile, int p_x, int p_y) {
    Vector3 basePos = { (float)p_x +0.5f , 0.5f, (float)p_y +0.5f};

    float offset = 0.1f;
    for (int i = 0; i < 7; i++) {
        int count = i == 0 ? tile.food :
                    i == 1 ? tile.linemate :
                    i == 2 ? tile.deraumere :
                    i == 3 ? tile.sibur :
                    i == 4 ? tile.mendiane :
                    i == 5 ? tile.phiras :
                    tile.thystame;

        for (int j = 0; j < count && j < 20; j++) {
            float angle =  j * 90.0f * DEG2RAD;

            Vector3 pos = {
                basePos.x + cosf(angle) * offset,
                basePos.y + sinf(_levitateTime * 4.0f + j) * 0.1f + 0.3f,
                basePos.z + sinf(angle) * offset
            };

            Vector3 axis = { 0.0f, 1.0f, 0.0f }; // Rotation Y
            // float rotation = fmodf(_levitateTime * 45.0f, 360.0f); // 45°/sec

            DrawModelEx(_ressources_models[i], pos, axis, 0.0f, (Vector3){GET_DEFAULT_SCALE(i), GET_DEFAULT_SCALE(i), GET_DEFAULT_SCALE(i)}, WHITE);

            offset += 0.15f;
        }
    }
}

void GuiManager::drawPlayer(trantorian_s& player, Vector3 offset) {
    ModelAnimation *model_animation[] = {
        _animation_level1,_animation_level1, _animation_level2,
        _animation_level3,_animation_level4, _animation_level5,
        _animation_level6,_animation_level7, _animation_level8, nullptr
    };
    int level = player.level;
    Model model;
    ModelAnimation model_anim;
    Vector3 pos = { (float)GET_PLATFORM_POSX(0, player.pos.x), 0.2f, (float) GET_PLATFORM_POSZ(0, player.pos.y) };
    Vector3 tagpos = { (float)GET_PLATFORM_POSX(0, player.targetPos.x), 0.2f, (float) GET_PLATFORM_POSZ(0, player.targetPos.y) };
    Vector3 startpos = { (float)GET_PLATFORM_POSX(0, player.pos.x), 0.2f, (float) GET_PLATFORM_POSZ(0, player.pos.y) };
    Vector3 endpos = { (float)GET_PLATFORM_POSX(0, player.targetPos.x), 0.2f, (float) GET_PLATFORM_POSZ(0, player.targetPos.y) };

    if (player.isMoving) {
        float progress = player.animationProgress;
        if (!player.isWrap) {
            pos.x = Lerp(startpos.x, endpos.x, progress);
            pos.z = Lerp(startpos.z, endpos.z, progress);
        } else {
            if (player.orientation == NORTH) {
                    if (progress < 0.5f) {
                        pos.z = Lerp(pos.z, pos.z - GRID_SIZE*2.5, progress);
                    } else {
                        pos.z = Lerp(GET_PLATFORM_POSZ(0, _height), tagpos.z, progress);
                    }
            }
            if (player.orientation == SOUTH) { 
                    if (progress < 0.5f) {
                        pos.z = Lerp(startpos.z, startpos.z + GRID_SIZE*2.5, progress);
                    } else {
                        pos.z = Lerp(GET_PLATFORM_POSZ(0, -1), endpos.z, progress);
                    }
            }
            
            if (player.orientation == EAST) { 
                if (progress < 0.5f) {
                        pos.x = Lerp(startpos.x, startpos.x+GRID_SIZE*2.5, progress);
                    } else {
                        pos.x = Lerp(GET_PLATFORM_POSX(0, -1), endpos.x, progress);
                    }                

            }

            if (player.orientation == WEST) { 
                if (progress < 0.5f) {
                        pos.x = Lerp(pos.x, pos.x-GRID_SIZE*2.5, progress);
                    } else {
                        pos.x = Lerp(GET_PLATFORM_POSX(0, _width), tagpos.x, progress);
                    }                

            }

        }
    }

    Vector3 rotation_axis =(Vector3)  { 0.0f, 1.0f, 0.0f };
    Color color;
    float rotationAngle = 0.0f;

    auto give_model_anim = [](ModelAnimation *model_animation[], actions_e current_animation, int level){
        int anim_id = 0;
        std::string model_name = GIVE_3D_OBJECT_GLBACTER_MODEL_BY_LEVEL(level);

        switch (current_animation) {
            case actions_e::IDLE:
                anim_id = GIVE_ANIM_INDEX_BY_NAME(model_name, actions_e::IDLE);
                break;
            case actions_e::WALK:
                anim_id = GIVE_ANIM_INDEX_BY_NAME(model_name, actions_e::WALK);
                break;
            case actions_e::PICK:
                anim_id = GIVE_ANIM_INDEX_BY_NAME(model_name, actions_e::PICK);
                break;
            case actions_e::DROP:
                anim_id = GIVE_ANIM_INDEX_BY_NAME(model_name, actions_e::DROP);
                break;
            case actions_e::ECSTASY:
                anim_id = GIVE_ANIM_INDEX_BY_NAME(model_name, actions_e::ECSTASY);
                break;
            case actions_e::LAY:
                anim_id = GIVE_ANIM_INDEX_BY_NAME(model_name, actions_e::LAY);
                break;
            case actions_e::SPAWN:
                anim_id = GIVE_ANIM_INDEX_BY_NAME(model_name, actions_e::SPAWN);
                break;
            case actions_e::DIE:
                anim_id = GIVE_ANIM_INDEX_BY_NAME(model_name, actions_e::DIE);
                break;
            case actions_e::EXPULSE:
                anim_id = GIVE_ANIM_INDEX_BY_NAME(model_name, actions_e::EXPULSE);
                break;
            default:
                anim_id = GIVE_ANIM_INDEX_BY_NAME(model_name, actions_e::NO_ANIMATION);
                break;
        }
        return model_animation[level][anim_id];
    };

    switch (player.orientation) {
        case NORTH:
            color = RED;
            rotationAngle = 180.0f;
            break;
        case SOUTH:
            color = GREEN;
            rotationAngle = 0.0f;
            break;
        case EAST:
            color = BLUE;
            rotationAngle = 90.0f;
            break;
        case WEST:
            color = YELLOW;
            rotationAngle = 270.0f;
            break;
    }

    switch (level) {
        case 0:
            model = _model_egg;
            model_anim = give_model_anim(model_animation, player.current_animation, level);
            break;
        case 1:
            model = _char_level1;
            model_anim = give_model_anim(model_animation, player.current_animation, level);
            break;
        case 2:
            model = _char_level2;
            model_anim = give_model_anim(model_animation, player.current_animation, level);
            break;
        case 3:
            model = _char_level3;
            model_anim = give_model_anim(model_animation, player.current_animation, level);
            break;
        case 4:
            model = _char_level4;
            model_anim = give_model_anim(model_animation, player.current_animation, level);
            break;
        case 5:
            model = _char_level5;
            model_anim = give_model_anim(model_animation, player.current_animation, level);
            break;
        case 6:
            model = _char_level6;
            model_anim = give_model_anim(model_animation, player.current_animation, level);
            break;
        case 7:
            model = _char_level7;
            model_anim = give_model_anim(model_animation, player.current_animation, level);
            break;
        case 8:
            model = _char_level8;
            model_anim = give_model_anim(model_animation, player.current_animation, level);
            break;
    }

    if (player.animCurrentFrame >= model_anim.frameCount) {
        player.animCurrentFrame = 0;
    } else  {
        if (player.current_animation != IDLE && player.current_animation != WALK && player.current_animation != ECSTASY) {
            player.animCurrentFrame = ( (int) Lerp(0.0f, model_anim.frameCount, player.animationProgress)) %model_anim.frameCount;
        } else {
            player.animCurrentFrame = (player.animCurrentFrame+1) %model_anim.frameCount;
        }
    }

    if (level >0) {
        if (!player.isMoving || Vector3Equals(pos, tagpos) ) {
            pos = Vector3Add(pos, offset);
        }
        if (player.isEstasy) {
            pos.y += 0.4f + sin(GetTime() * 3.0f) * 0.2f;
        }
        player.actualPosWithAnimation = (Vector2) {(float) pos.x, (float) pos.z};
        UpdateModelAnimation(model, model_anim, player.animCurrentFrame);
        DrawModelEx(model, pos, rotation_axis, rotationAngle, (Vector3)  { 1.0f, 1.0f, 1.0f } , WHITE);
        if (player.isBroadCast) {
            float rayon = ((GET_PLATFORM_POSX(0, _width) + GET_PLATFORM_POSZ(0, _height)) / 2.0f) * player.broadcastProgress;
            Vector3 pos = { (float)GET_PLATFORM_POSX(0, player.bcPos.x), 0.2f, (float)GET_PLATFORM_POSZ(0, player.bcPos.y) };

            DrawCylinderWires(
                pos,
                rayon,
                rayon,
                0.1f * player.broadcastProgress,
                36,
                Fade(player.color, 1.0f - player.broadcastProgress)
            );
        }

    } else {
        float rotation = fmodf(_levitateTime * 45.0f, 360.0f);
        // pos = { (float) GET_PLATFORM_POSX(0.0, player.pos.x), 0.50f, (float) GET_PLATFORM_POSZ(2.250f, player.pos.y) };
        Vector3 scale = EGG_SCALE;
        if (player.isdying) scale = player.isdying ? EGG_SCALE_BY((1-player.animationProgress)): EGG_SCALE;
        if (player.isSpawn) scale = player.isSpawn ? EGG_SCALE_BY((player.animationProgress)): EGG_SCALE;

        pos = { (float) GET_PLATFORM_POSX(0.0, player.pos.x), 1.0f, (float) GET_PLATFORM_POSZ(0.0f, player.pos.y) };
        pos = Vector3Add(pos, offset);
        DrawModelEx(model, pos, (Vector3){1.0f, 1.0f, 1.0f}, rotation, scale , player.color);
    }
}

void GuiManager::drawIncantationEffect(Vector3 pos, float progress)
{

    Color haloColor = ColorAlpha(YELLOW, 0.5f * progress);
    DrawCircle3D(pos, 3.0f, {1, 0, 0}, 90.0f, haloColor);


    int particleCount = 50;
    for (int i = 0; i < particleCount; i++) {
        float angle = GetTime() * 2.0f + (i * (360.0f / particleCount));
        float radius = 1.5f + sinf(GetTime() * 1.5f + i) * 0.5f;
        float height = fmod(GetTime() * 3.0f + i * 0.1f, 5.0f) * progress;

        Vector3 particlePos = {
            pos.x + cosf(angle * DEG2RAD) * radius,
            pos.y + height,
            pos.z + sinf(angle * DEG2RAD) * radius
        };

        Color particleColor = ColorAlpha(GOLD, height / 5.0f * progress);
        DrawSphere(particlePos, 0.1f, particleColor);
    }
}

void GuiManager::drawPlayerAura(trantorian_s& player) {
    if (player.level > 0 && _teamColors.count(player.team)) {
        Color teamColor = _teamColors.at(player.team);
        float pulseSpeed = 2.0f;
        float pulse = (sinf(_levitateTime * pulseSpeed) + 1.0f) / 2.0f;

        float minRadius = 1.3f;
        float maxRadius = 1.7f;
        float currentRadius = Lerp(minRadius, maxRadius, pulse);

        float minHeight = 0.025f;
        float maxHeight = 0.035f;
        float currentHeight = Lerp(minHeight, maxHeight, pulse);

        float minAlpha = 0.2f;
        float maxAlpha = 0.5f;
        float currentAlpha = Lerp(minAlpha, maxAlpha, pulse);

        Vector3 startPos = { player.actualPosWithAnimation.x, 0.5f + minHeight, player.actualPosWithAnimation.y };
        Vector3 endPos   = { player.actualPosWithAnimation.x, 0.5f + currentHeight, player.actualPosWithAnimation.y };

        DrawCylinderEx(startPos, endPos, currentRadius, currentRadius, 24, Fade(teamColor, currentAlpha));
    }
}

void CustomLog(int msgType, const char *text, va_list args){ (void) msgType; (void)text;  (void)args;   return;}

// t: temps actuel (current time)
// b: valeur de début (beginning value)
// c: changement de valeur (change in value, i.e. end - start)
// d: durée (duration)
static inline float MyEaseCubicOut(float t, float b, float c, float d){
    float a  = (t/d)-1;
    return c * ( a * t * t + 1) + b;
}

void GuiManager::drawTempMessages() {
    double currentTime = GetTime();

    const int FONT_SIZE = 20;
    const int PADDING = 10;
    const float ANIM_DURATION = 0.5f;
    const float DESCEND_SPEED = 30.0f;

    float yOffset = 20.0f;

    for (auto it = _tempMessages.begin(); it != _tempMessages.end(); ) {
        double timeAlive = currentTime - it->startTime;

        if (timeAlive < it->duration) {
            float animProgress = 0.0f;

            if (timeAlive < ANIM_DURATION) {
                animProgress = timeAlive / ANIM_DURATION;
            }
            else if (timeAlive > it->duration - ANIM_DURATION) {
                animProgress = (it->duration - timeAlive) / ANIM_DURATION;
            }
            else {
                animProgress = 1.0f;
            }

            animProgress = Clamp(animProgress, 0.0f, 1.0f);
            float easedProgress = MyEaseCubicOut(animProgress, 0, 1, 1);

            int msgWidth = MeasureText(it->text.c_str(), FONT_SIZE);
            float fullHeight = FONT_SIZE + (PADDING * 2);
            float fullWidth = msgWidth + (PADDING * 2);

            float currentHeight = fullHeight * easedProgress;
            float currentAlpha = 255 * easedProgress;

            Rectangle boxRect;
            boxRect.width = fullWidth;
            boxRect.height = currentHeight;
            boxRect.x = GetScreenWidth() / 2.0f - boxRect.width / 2.0f;
            boxRect.y = yOffset + (timeAlive * DESCEND_SPEED);

            if (boxRect.height > 1) {
                DrawRectangleRec(boxRect, Fade(it->boxColor, currentAlpha / 255.0f));

                if (easedProgress > 0.5f) {
                    DrawText
                    (
                            it->text.c_str(),
                            boxRect.x + PADDING,
                            boxRect.y + PADDING,
                            FONT_SIZE,
                            Fade(it->color, currentAlpha / 255.0f)
                    );
                }
            }

            yOffset += currentHeight + 10;

            it++;
        } else {
            it = _tempMessages.erase(it);
        }
    }
}

std::vector<std::string> splitStringByLines(const std::string& text) {
    std::vector<std::string> lines;
    std::string currentLine;
    std::stringstream ss(text);

    while (std::getline(ss, currentLine, '\n')) {
        lines.push_back(currentLine);
    }
    return lines;
}

void GuiManager::drawInfoPanel(const std::string& title, const std::string& content, Vector2 position)
{
    const int FONT_SIZE = 20;
    const int PADDING = 10;
    const int LINE_SPACING = 5;
    const Color BG_COLOR = { 60, 60, 80, 210 };
    const Color TITLE_COLOR = GOLD;
    const Color TEXT_COLOR = WHITE;
    const Color BORDER_COLOR = GOLD;

    std::string fullText = title + "\n" + content;
    std::vector<std::string> lines = splitStringByLines(fullText);
    if (lines.empty()) return;

    
    float maxWidth = 0;
    for (const auto& line : lines) {
        maxWidth = std::max(maxWidth, (float)MeasureText(line.c_str(), FONT_SIZE));
    }
    float totalHeight = (lines.size() * FONT_SIZE) + ((lines.size() - 1) * LINE_SPACING) + (PADDING * 2);

    Rectangle boxRect;
    boxRect.width = maxWidth + (PADDING * 2);
    boxRect.height = totalHeight;
    boxRect.x = position.x; 
    boxRect.y = position.y; 

    DrawRectangleRec(boxRect, BG_COLOR);
    DrawRectangleLinesEx(boxRect, 2, BORDER_COLOR);

    float currentY = boxRect.y + PADDING;
    
    
    DrawText(title.c_str(), boxRect.x + PADDING, currentY, FONT_SIZE, TITLE_COLOR);
    currentY += FONT_SIZE + LINE_SPACING + 5; 

    
    std::vector<std::string> content_lines = splitStringByLines(content);
    for (const auto& line : content_lines) {
        DrawText(line.c_str(), boxRect.x + PADDING, currentY, FONT_SIZE, TEXT_COLOR);
        currentY += FONT_SIZE + LINE_SPACING;
    }
}

void GuiManager::drawHelpBox(const std::string& message, bool change_pos)
{
    const int FONT_SIZE = 20;
    const int PADDING = 10;
    const int LINE_SPACING = 5;
    const Color BG_COLOR = { 50, 50, 70, 200 };
    const Color TEXT_COLOR = WHITE;

    std::vector<std::string> lines = splitStringByLines(message);
    if (lines.empty()) return;
    float maxWidth = 0;
    for (const auto& line : lines) {
        float lineWidth = MeasureText(line.c_str(), FONT_SIZE);
        if (lineWidth > maxWidth) {
            maxWidth = lineWidth;
        }
    }

    float totalHeight = (lines.size() * FONT_SIZE) + ((lines.size() - 1) * LINE_SPACING);

    Rectangle boxRect;
    boxRect.width = maxWidth + (PADDING * 2);
    boxRect.height = totalHeight + (PADDING * 2);
    boxRect.x = !change_pos ? GetScreenWidth() - boxRect.width - 10: GetScreenWidth() - boxRect.width - 10 - 300;
    boxRect.y = 10;

    DrawRectangleRec(boxRect, BG_COLOR);
    DrawRectangleLinesEx(boxRect, 2, DARKGRAY);

    float currentY = boxRect.y + PADDING;
    for (const auto& line : lines) {
        DrawText(line.c_str(), boxRect.x + PADDING, currentY, FONT_SIZE, TEXT_COLOR);
        currentY += FONT_SIZE + LINE_SPACING;
    }
}
/**************************************************************************************************
                                                  ___
,-.----.             ,--,                        ,--.'|_                                  ,--,                 ,--,   ,--.'|_
\    /  \   __  ,-.,--.'|                        |  | :,'                               ,--.'|         ,---, ,--.'|   |  | :,'
|   :    |,' ,'/ /||  |,      .---.              :  : ' :             .--.--.           |  |,      ,-+-. /  ||  |,    :  : ' :  .--.--.
|   | .\ :'  | |' |`--'_    /.  ./|   ,--.--.  .;__,'  /     ,---.   /  /    '          `--'_     ,--.'|'   |`--'_  .;__,'  /  /  /    '
.   : |: ||  |   ,',' ,'| .-' . ' |  /       \ |  |   |     /     \ |  :  /`./          ,' ,'|   |   |  ,"' |,' ,'| |  |   |  |  :  /`./
|  ' | |  . .:__,'| :   '  | |   |  | :   '  | | :__,'| :   , ' , ' :
|  | ' |  | |  '  : |__ |  | :   '  : |__ |  | :   '  : |__/___/ \: |
:  | : ;  ; |  |  | '.'|'  : |__ |  | '.'|'  : |__ |  | '.'|.  \  ' |
'  :  `--'   \ ;  :    ;|  | '.'|;  :    ;|  | '.'|;  :    ; \  ;   :
:  ,      .-./ |  ,   / ;  :    ;|  ,   / ;  :    ;|  ,   /   \  \  ;
 `--`----'      ---`-'  |  ,   /  ---`-'  |  ,   /  ---`-'     :  \  \
                         ---`-'            ---`-'               \  ' ;
                                                                 `--`
*/

void GuiManager::initFloor() {
    mesh_floor = GenMeshPlane( (_width == 0) ? 50: GET_PLATFORM_POSX(0, _width*3)*3 , GET_PLATFORM_POSZ(0, _height*3)*3, 50, 50);
    model_floor = LoadModelFromMesh(mesh_floor);

    model_floor.materials[0].shader = water_shader;

        _model_platforms_1 = LoadModel(GIVE_3D_MODEL_PATH("platform1", ".gltf", "scene").c_str()     );
        _model_platforms_2 = LoadModel(GIVE_3D_MODEL_PATH("platform2", ".gltf", "scene").c_str()     );
        _model_platforms_3 = LoadModel(GIVE_3D_MODEL_PATH("platform3", ".gltf", "scene").c_str()     );
        _model_platforms_4 = LoadModel(GIVE_3D_MODEL_PATH("platform4", ".gltf", "scene").c_str()     );
        _model_platforms_5 = LoadModel(GIVE_3D_MODEL_PATH("platform5", ".gltf", "scene").c_str()     );
        _model_platforms_6 = LoadModel(GIVE_3D_MODEL_PATH("platform6", ".gltf", "scene").c_str()     );
        _model_platforms_7 = LoadModel(GIVE_3D_MODEL_PATH("platform7", ".gltf", "scene").c_str()     );
        _model_platforms_8 = LoadModel(GIVE_3D_MODEL_PATH("platform8", ".gltf", "scene").c_str()     );
        _model_platforms_9 = LoadModel(GIVE_3D_MODEL_PATH("platform9", ".gltf", "scene").c_str()     );
        _model_platforms_10 = LoadModel(GIVE_3D_MODEL_PATH("platform10", ".gltf", "scene").c_str()     );
    _model_bridge = LoadModel(GIVE_3D_MODEL_PATH("bridge", ".gltf", "scene").c_str()     );
    _model_portal = LoadModel(GIVE_3D_MODEL_PATH("portal", ".gltf", "scene").c_str()     );
}

void GuiManager::init3DCharacters() {

    _model_egg = LoadModel(GIVE_3D_OBJECT_GLB("egg1").c_str() );
    // _animation_level0 = LoadModelAnimations(GIVE_3D_OBJECT_GLB("egg1").c_str(), &_animation_level0_count );
    // if (!_animation_level0) exit(84);
    _char_level1 = LoadModel(GIVE_3D_OBJECT_GLB("skeleton").c_str() );
    _animation_level1 = LoadModelAnimations(GIVE_3D_OBJECT_GLB("skeleton").c_str(), &_animation_level1_count );
    _char_level2 = LoadModel(GIVE_3D_OBJECT_GLB("skeleton_rogue").c_str() );
    _animation_level2 = LoadModelAnimations(GIVE_3D_OBJECT_GLB("skeleton_rogue").c_str(), &_animation_level2_count );
    _char_level3 = LoadModel(GIVE_3D_OBJECT_GLB("skeleton_mage").c_str() );
    _animation_level3 = LoadModelAnimations(GIVE_3D_OBJECT_GLB("skeleton_mage").c_str(), &_animation_level3_count );
    _char_level4 = LoadModel(GIVE_3D_OBJECT_GLB("skeleton_knight").c_str() );
    _animation_level4 = LoadModelAnimations(GIVE_3D_OBJECT_GLB("skeleton_knight").c_str(), &_animation_level4_count );
    _char_level5 = LoadModel(GIVE_3D_OBJECT_GLB("human").c_str() );
    _animation_level5 = LoadModelAnimations(GIVE_3D_OBJECT_GLB("human").c_str(), &_animation_level5_count );
    _char_level6 = LoadModel(GIVE_3D_OBJECT_GLB("human_rogue").c_str() );
    _animation_level6 = LoadModelAnimations(GIVE_3D_OBJECT_GLB("human_rogue").c_str(), &_animation_level6_count );
    _char_level7 = LoadModel(GIVE_3D_OBJECT_GLB("human_mage").c_str() );
    _animation_level7 = LoadModelAnimations(GIVE_3D_OBJECT_GLB("human_mage").c_str(), &_animation_level7_count );
    _char_level8 = LoadModel(GIVE_3D_OBJECT_GLB("human_knight").c_str() );
    _animation_level8 = LoadModelAnimations(GIVE_3D_OBJECT_GLB("human_knight").c_str(), &_animation_level8_count );

}

void GuiManager::initShader() {

    water_shader = LoadShader(
        GIVE_SHADER("vertex_displacement.vs").c_str(),
        GIVE_SHADER("vertex_displacement.fs").c_str()
    );
    water_perlinNoiseImage = GenImagePerlinNoise(512, 512, 0, 0, 1.0f);
    water_perlinNoiseMap = LoadTextureFromImage(water_perlinNoiseImage);
    UnloadImage(water_perlinNoiseImage);

    perlinNoiseMapLoc = GetShaderLocation(water_shader, "perlinNoiseMap");
    rlEnableShader(water_shader.id);
    rlActiveTextureSlot(1);
    rlEnableTexture(water_perlinNoiseMap.id);
    rlSetUniformSampler(perlinNoiseMapLoc, 1);

    skybox_cube = GenMeshCube(1.0f, 1.0f, 1.0f);
    skybox = LoadModelFromMesh(skybox_cube);
    skybox.materials[0].shader = LoadShader(
        GIVE_SHADER("skybox.vs").c_str() ,
        GIVE_SHADER("skybox.fs").c_str()
    );
    SetShaderValue(skybox.materials[0].shader, GetShaderLocation(skybox.materials[0].shader, "environmentMap"), &value_environmentMap, SHADER_UNIFORM_INT);
    SetShaderValue(skybox.materials[0].shader, GetShaderLocation(skybox.materials[0].shader, "doGamma"), &value_dogamma, SHADER_UNIFORM_INT);
    SetShaderValue(skybox.materials[0].shader, GetShaderLocation(skybox.materials[0].shader, "vflipped"), &value_dogamma, SHADER_UNIFORM_INT);

    shdrCubemap = LoadShader(
        GIVE_SHADER("cubemap.vs").c_str(),
        GIVE_SHADER("cubemap.fs").c_str()
    );
    SetShaderValue(shdrCubemap, GetShaderLocation(shdrCubemap, "equirectangularMap"), &value_dogamma, SHADER_UNIFORM_INT);

    Image img = LoadImage(GIVE_RESSOURCE("skybox_day.png").c_str() );
    skyboxTextureDay = LoadTextureCubemap(img, CUBEMAP_LAYOUT_AUTO_DETECT);
    UnloadImage(img);
    img = LoadImage(GIVE_RESSOURCE("skybox_day_blue.png").c_str() );
    skyboxTextureDayBlue = LoadTextureCubemap(img, CUBEMAP_LAYOUT_AUTO_DETECT);
    UnloadImage(img);
    img = LoadImage(GIVE_RESSOURCE("skybox_day_sunset.png").c_str() );
    skyboxTextureDaySunSet = LoadTextureCubemap(img, CUBEMAP_LAYOUT_AUTO_DETECT);
    UnloadImage(img);
    img = LoadImage(GIVE_RESSOURCE("skybox_night.png").c_str() );
    skyboxTextureNight = LoadTextureCubemap(img, CUBEMAP_LAYOUT_AUTO_DETECT);
    UnloadImage(img);
    img = LoadImage(GIVE_RESSOURCE("skybox_night_purple.png").c_str() );
    skyboxTextureNightPurple = LoadTextureCubemap(img, CUBEMAP_LAYOUT_AUTO_DETECT);
    UnloadImage(img);
    img = LoadImage(GIVE_RESSOURCE("skybox_night_skysky.png").c_str() );
    skyboxTextureNightSkySky = LoadTextureCubemap(img, CUBEMAP_LAYOUT_AUTO_DETECT);
    UnloadImage(img);
    skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = skyboxTextureDay;

    light_shader = LoadShader(GIVE_SHADER("lighting.vs").c_str(),
                               GIVE_SHADER("lighting.fs").c_str());

    int ambientLoc = GetShaderLocation(light_shader, "ambient");
    float value[4] = { 1000.0f, 1000.0f, 1000.0f, 1000.0f };
    SetShaderValue(light_shader, ambientLoc, value, SHADER_UNIFORM_VEC4);

    for (int i = 0; i < MAX_LIGHTS; i++) {
        _lights[i] = CreateLight(LIGHT_POINT, (Vector3){0, 0, 0}, Vector3{10.0f, 10.0f, 10.0f}, WHITE, light_shader);
    }

    _lights[0].enabled = true;
    _lights[0].type = LIGHT_POINT;
    _lights[0].color = YELLOW;
    _lights[1].enabled = true;
    _lights[1].type = LIGHT_POINT;
    _lights[1].color = RAYWHITE;
    _lights[2].enabled = false;
    _lights[3].enabled = false;

}

void GuiManager::initFloorModels() {

    _ressources_models[0] = LoadModel(GIVE_3D_MODEL_PATH("food", ".gltf", "scene").c_str()     );     // FOOD
    _ressources_models[1] = LoadModel(GIVE_3D_MODEL_PATH("linemate", ".gltf", "scene").c_str() ); // LINEMATE
    _ressources_models[2] = LoadModel(GIVE_3D_MODEL_PATH("deraumere", ".gltf", "scene").c_str()); // DERAUMERE
    _ressources_models[3] = LoadModel(GIVE_3D_MODEL_PATH("sibur", ".gltf", "scene").c_str()    );    // SIBUR
    _ressources_models[4] = LoadModel(GIVE_3D_MODEL_PATH("mendiane", ".gltf", "scene").c_str() ); // MENDIANE
    _ressources_models[5] = LoadModel(GIVE_3D_MODEL_PATH("phiras", ".gltf", "scene").c_str()   );   // PHIRAS
    _ressources_models[6] = LoadModel(GIVE_3D_MODEL_PATH("thystame", ".gltf", "scene").c_str() ); // ThYSTAME
}

void GuiManager::initWindow() {
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(1920, 1080, WIN_TITLE);
    ToggleFullscreen();

    DisableCursor();
    SetTargetFPS(120);

    loadingBar.setCoord((size_t)1920, (size_t)1080);

    _camera.position = Vector3{ 10.0f, 10.0f, 10.0f };
    _camera.target = Vector3{0.0f, -1.0f, 0.0f};
    _camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    _camera.fovy = 60.0f;
    _camera.projection = CAMERA_PERSPECTIVE;
    camMode = CAMERA_FREE;

}

/*
.------..------..------..------..------..------..------.     .------..------..------..------..------..------..------..------.
|P.--. ||R.--. ||I.--. ||V.--. ||A.--. ||T.--. ||E.--. |.-.  |U.--. ||P.--. ||D.--. ||A.--. ||T.--. ||E.--. ||R.--. ||S.--. |
| :/\: || :(): || (\/) || :(): || (\/) || :/\: || (\/) ((5)) | (\/) || :/\: || :/\: || (\/) || :/\: || (\/) || :(): || :/\: |
| (__) || ()() || :\/: || ()() || :\/: || (__) || :\/: |'-.-.| :\/: || (__) || (__) || :\/: || (__) || :\/: || ()() || :\/: |
| '--'P|| '--'R|| '--'I|| '--'V|| '--'A|| '--'T|| '--'E| ((1)) '--'U|| '--'P|| '--'D|| '--'A|| '--'T|| '--'E|| '--'R|| '--'S|
`------'`------'`------'`------'`------'`------'`------'  '-'`------'`------'`------'`------'`------'`------'`------'`------'
*/

void GuiManager::updateSkyRotation(float deltaTime) {
    float rotationSpeed = (2.0f * PI) / DAY_TIME_IN_MY_HOUR;
    _skyRotation += deltaTime * rotationSpeed;
    if (_skyRotation > 2*M_PI) _skyRotation = 0.0f;

    int rotationLoc = GetShaderLocation(skybox.materials[0].shader, "rotationAngle");
    if (rotationLoc != -1) {
        SetShaderValue(skybox.materials[0].shader, rotationLoc, &_skyRotation, SHADER_UNIFORM_FLOAT);
    }
}

void GuiManager::updateFloor() {
    if (!floor_changed_size)
        return;
    floor_changed_size = false;
}

void GuiManager::updateShader() {
    _shaderChangingTime += GetFrameTime();
    SetShaderValue(water_shader, GetShaderLocation(water_shader, "time"), &_shaderChangingTime, SHADER_UNIFORM_FLOAT);
    SetShaderValue(water_shader, water_shader.locs[SHADER_LOC_VECTOR_VIEW], &_camera.position, SHADER_UNIFORM_VEC3);
    UpdateLightValues(water_shader, _lights[0]);
}


void GuiManager::UpdateAndDrawPlayingScreen() {
    _audioManager.UpdateMusicStreams();
    handleInput();
    update();
    render();
}

void GuiManager::UpdateAndDrawLoadingScreen() {
    _audioManager.UpdateMusicStreams();
    const int totalLoadingStages = 5;
    float progress = (float)_loadingStage / totalLoadingStages * 100.0f;


    std::string baseText = "";
    switch (_loadingStage) {
        case 0: baseText = "Loading resource models"; break;
        case 1: baseText = "Compiling shaders"; break;
        case 2: baseText = "Generating world platforms"; break;
        case 3: baseText = "Spawning Trantorians"; break;
        case 4: baseText = "Loading fonts"; break;
        default: baseText = "Finalizing"; break;
    }

    BeginDrawing();
    ClearBackground(BLACK);

        int dotCount = (int)(GetTime() * 2.5f) % 4;
        std::string dots = std::string(dotCount, '.');
        std::string animatedText = baseText + dots;

        static int tipIndex = 0;
        static double lastTipTime = 0.0;
        if (GetTime() - lastTipTime > 2.0) {
            tipIndex = GetRandomValue(0, _gameTips.size() - 1);
            lastTipTime = GetTime();
        }

        DrawText("ZAPPY", GetScreenWidth() / 2 - MeasureText("ZAPPY", 80) / 2, GetScreenHeight() / 2 - 100, 80, WHITE);
        DrawText(_gameTips[tipIndex].c_str(), GetScreenWidth() / 2 - MeasureText(_gameTips[tipIndex].c_str(), 20) / 2, GetScreenHeight() - 180, 20, LIGHTGRAY);
        loadingBar.draw(animatedText, DARKGRAY, CALCULATE_PROGRESS_COLOR(progress/100.0f));

    EndDrawing();
    if (_loadingStage < totalLoadingStages) {
        switch (_loadingStage) {
            case 0: initFloorModels(); break;
            case 1: initShader(); break;
            case 2: initFloor(); break;
            case 3: init3DCharacters(); break;
            case 4: tempMessagesFont = LoadFont(GIVE_FONT_PATH("toasty_milk", ".otf").c_str()); break;
        }
        _loadingStage++;

        loadingBar.update(progress);
        WaitTime(0.2);
    } else if (_gameState == STATE_LOADING) {
        WaitTime(0.5);
        _gameState = STATE_PLAYING;
        _audioManager.PlayMainMusic();
    }
}

//  ____  ____  _  _     ____  _____  _____   _     _____  _  _     _  _____ ___  _
// /  __\/  __\/ \/ \ |\/  _ \/__ __\/  __/  / \ /\/__ __\/ \/ \   / \/__ __\\  \//
// |  \/||  \/|| || | //| / \|  / \  |  \    | | ||  / \  | || |   | |  / \   \  /
// |  __/|    /| || \// | |-||  | |  |  /_   | \_/|  | |  | || |_/\| |  | |   / /
// \_/   \_/\_\\_/\__/  \_/ \|  \_/  \____\  \____/  \_/  \_/\____/\_/  \_/  /_/

bool GuiManager::isPlayerInView(Vector3& bodypos) {

    float verticalFovRad = _camera.fovy * DEG2RAD;
    float aspect = (float)GetScreenWidth() / (float)GetScreenHeight();
    float horizontalFovRad = 2.0f * atanf(tanf(verticalFovRad * 0.5f) * aspect);


    Vector3 campos = _camera.position;
    Vector3 camtarget = _camera.target;
    Vector3 camdir = Vector3Normalize(Vector3Subtract(camtarget, campos));


    Vector3 tobody = Vector3Normalize(Vector3Subtract(bodypos, campos));


    Vector3 tobody2d = tobody;
    tobody2d.z = 0.0f;
    tobody2d = Vector3Normalize(tobody2d);

    Vector3 camdir2d = camdir;
    camdir2d.z = 0.0f;
    camdir2d = Vector3Normalize(camdir2d);

    float dotHorizontal = Vector3DotProduct(tobody2d, camdir2d);
    if (dotHorizontal < cosf(horizontalFovRad * 0.5f)) return false;


    float tiltcam = asinf(camdir.y);
    float tilttobody = asinf(tobody.y);

    float verticalHalf = verticalFovRad * 0.5f;

    if (tilttobody < tiltcam - verticalHalf) return false;
    if (tilttobody > tiltcam + verticalHalf) return false;

    return true;
}


Model GuiManager::getPlayerModelByLevel(int level)
{
    switch (level) {
        case 1: return _char_level1;
        case 2: return _char_level2;
        case 3: return _char_level3;
        case 4: return _char_level4;
        case 5: return _char_level5;
        case 6: return _char_level6;
        case 7: return _char_level7;
        case 8: return _char_level8;
        default: return _char_level1; 
    }
}

float GuiManager::getPlayerRotationAngle(orient_e orientation)
{
    switch (orientation) {
        case NORTH: return 180.0f;
        case SOUTH: return 0.0f;
        case EAST: return 270.0f;
        case WEST: return 90.0f;
        default: return 0.0f;
    }
}
