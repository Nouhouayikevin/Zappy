/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** DashBoard.cpp
*/

#include "../include/Dashboard.hpp"

Dashboard::Dashboard()
    : _isMainPanelOpen(false), _selectedTeam(""), _followedPlayerId(-1), _mainPanelAnim(0.0f) , _playerInfoPanelAnim(0.0f){}

Dashboard::~Dashboard() {}

bool Dashboard::isPlayerFollowed() const {
    return _followedPlayerId != -1;
}

int Dashboard::getFollowedPlayerId() const {
    return _followedPlayerId;
}

void Dashboard::stopFollowing() {
    _followedPlayerId = -1;
    _isMainPanelOpen = false; 
    _selectedTeam = "";
}

void Dashboard::followPlayer(int playerId)
{
    _followedPlayerId = playerId;
    _isMainPanelOpen = false; 
    _selectedTeam = "";
}

void Dashboard::handleInput() {
    if (isPlayerFollowed()) {
        if (IsKeyPressed(KEY_U)) {
            stopFollowing();
        }
        return;
    }

    Rectangle mainTabRect = { 0, 0, 80, HEADER_HEIGHT };
    if (CheckCollisionPointRec(GetMousePosition(), mainTabRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        _isMainPanelOpen = !_isMainPanelOpen;
        _selectedTeam = "";
    }
}

void Dashboard::update(float deltaTime) {
    // Animation du panneau principal
    float targetMain = _isMainPanelOpen ? 1.0f : 0.0f;
    _mainPanelAnim = Lerp(_mainPanelAnim, targetMain, deltaTime * ANIM_SPEED);

    float targetPlayerInfo = isPlayerFollowed() ? 1.0f : 0.0f;
    _playerInfoPanelAnim = Lerp(_playerInfoPanelAnim, targetPlayerInfo, deltaTime * ANIM_SPEED);

    // Animation des panneaux d'équipe
    for (auto const& [teamName, anim] : _teamPanelAnim) {
        float targetTeam = (_selectedTeam == teamName) ? 1.0f : 0.0f;
        _teamPanelAnim[teamName] = Lerp(_teamPanelAnim[teamName], targetTeam, deltaTime * ANIM_SPEED);
    }
}

void Dashboard::draw(const std::set<std::string>& teams, const std::map<int, trantorian_s>& players) {
    if (abs(_mainPanelAnim) < 0.01f && !_isMainPanelOpen) {
        DrawRectangle(0, 0, 80, HEADER_HEIGHT, HEADER_COLOR);
        DrawText("Teams", 10, 10, 20, WHITE);
        return;
    }

    float currentPanelHeight = GetScreenHeight() * _mainPanelAnim;
    DrawRectangle(0, 0, PANEL_WIDTH, currentPanelHeight, BG_COLOR);

    if (_mainPanelAnim > 0.5f) {
       
        DrawRectangle(0, 0, PANEL_WIDTH, HEADER_HEIGHT, HEADER_COLOR);
        DrawText("Select a Team", 10, 10, 20, WHITE);

       
        float y_offset = HEADER_HEIGHT + 10;
        for (const auto& teamName : teams) {
            Rectangle teamRect = { 10, y_offset, PANEL_WIDTH - 20, ITEM_HEIGHT };
            bool isHover = CheckCollisionPointRec(GetMousePosition(), teamRect);

            if (isHover) DrawRectangleRec(teamRect, HIGHLIGHT_COLOR);

            DrawText(teamName.c_str(), 20, y_offset + 5, 20, _selectedTeam == teamName ? YELLOW : WHITE);

            if (isHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
               
                _selectedTeam = (_selectedTeam == teamName) ? "" : teamName;
                if (_teamPanelAnim.find(teamName) == _teamPanelAnim.end()) {
                    _teamPanelAnim[teamName] = 0.0f;
                }
            }

           
            if (_teamPanelAnim.count(teamName) && abs(_teamPanelAnim.at(teamName)) > 0.01f) {
               
                std::vector<trantorian_s*> teamPlayers;
                for (const auto& pair : players) {
                    if (pair.second.team == teamName) {
                        teamPlayers.push_back(const_cast<trantorian_s*>(&pair.second));
                    }
                }
                
                float teamPanelHeight = (ITEM_HEIGHT * teamPlayers.size() + 10) * _teamPanelAnim.at(teamName);
                DrawRectangle(20, y_offset + ITEM_HEIGHT, PANEL_WIDTH - 40, teamPanelHeight, {70, 70, 90, 200});

                if (_teamPanelAnim.at(teamName) > 0.5) {
                    float player_y = y_offset + ITEM_HEIGHT + 5;
                    for (trantorian_s* player : teamPlayers) {
                        Rectangle playerRect = { 30, player_y, PANEL_WIDTH - 60, ITEM_HEIGHT };
                        bool isPlayerHover = CheckCollisionPointRec(GetMousePosition(), playerRect);
                        if (isPlayerHover) DrawRectangleRec(playerRect, HIGHLIGHT_COLOR);

                        std::string playerText = "ID: " + std::to_string(player->id) + " - Lvl: " + std::to_string(player->level);
                        DrawText(playerText.c_str(), 40, player_y, 20, WHITE);
                         
                        
                        if (isPlayerHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                            _followedPlayerId = player->id;
                        }
                        player_y += ITEM_HEIGHT;
                    }
                }
                y_offset += teamPanelHeight;
            }
            
            if (isPlayerFollowed()) {
                auto it = players.find(_followedPlayerId);
                if (it != players.end()) {
                    drawFollowedPlayerPanel(it->second);
                }
            }
            
            y_offset += ITEM_HEIGHT + 5;
        }
    }
}


void Dashboard::drawFollowedPlayerPanel(const trantorian_s& player)
{
    if (abs(_playerInfoPanelAnim) < 0.01f) return;

    float currentWidth = INFO_PANEL_WIDTH * _playerInfoPanelAnim;
    float panelX = GetScreenWidth() - currentWidth;

    DrawRectangle(panelX, 0, currentWidth, GetScreenHeight(), INFO_BG_COLOR);

    
    if (_playerInfoPanelAnim > 0.7f) {
        float y_offset = 10.0f;
        float x_offset = panelX + 15.0f;

        
        DrawText(TextFormat("Following Player #%d", player.id), x_offset, y_offset, 25, YELLOW);
        y_offset += 40;

        
        DrawText(TextFormat("Team: %s", player.team.c_str()), x_offset, y_offset, 20, WHITE);
        y_offset += 25;
        DrawText(TextFormat("Level: %d", player.level), x_offset, y_offset, 20, WHITE);
        y_offset += 25;
        DrawText(TextFormat("Position: (%d, %d)", player.pos.x, player.pos.y), x_offset, y_offset, 20, WHITE);
        y_offset += 25;

        
        std::string orientationStr = "Unknown";
        switch (player.orientation) {
            case NORTH: orientationStr = "North"; break;
            case SOUTH: orientationStr = "South"; break;
            case EAST:  orientationStr = "East"; break;
            case WEST:  orientationStr = "West"; break;
        }
        DrawText(TextFormat("Orientation: %s", orientationStr.c_str()), x_offset, y_offset, 20, WHITE);
        y_offset += 40; 

        
        DrawLine(panelX + 10, y_offset, panelX + currentWidth - 10, y_offset, LIGHTGRAY);
        y_offset += 15;
        DrawText("Inventory:", x_offset, y_offset, 22, YELLOW);
        y_offset += 30;

        
        const std::vector<std::string> resourceNames = {"Food", "Linemate", "Deraumere", "Sibur", "Mendiane", "Phiras", "Thystame"};
        const std::size_t resources[] = {
            player.elements.linemate, player.elements.food, player.elements.deraumere,
            player.elements.sibur, player.elements.mendiane, player.elements.phiras,
            player.elements.thystame
        };

        for (int i = 0; i < 7; ++i) {
            DrawText(TextFormat("- %s: %d", resourceNames[i].c_str(), resources[i]), x_offset + 5, y_offset, 20, WHITE);
            y_offset += 25;
        }
    }
}
