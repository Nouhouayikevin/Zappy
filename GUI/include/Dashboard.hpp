/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** Dashboard.hpp
*/

#ifndef DASHBOARD_HPP_
#define DASHBOARD_HPP_

#include "my_include.hpp"
#include "struct.hpp"
#include <string>
#include <vector>
#include <map>

class Dashboard {
public:
    Dashboard();
    ~Dashboard();

    void handleInput();
    void update(float deltaTime);
    void draw(const std::set<std::string>& teams, const std::map<int, trantorian_s>& players);

    bool isPlayerFollowed() const;
    int getFollowedPlayerId() const;
    void stopFollowing();
    void followPlayer(int playerId);

private:
    bool _isMainPanelOpen;      // Le panneau principal est-il déplié ?
    std::string _selectedTeam;  // Quelle équipe est sélectionnée ?
    int _followedPlayerId;      // L'ID du joueur actuellement suivi (-1 si aucun)

    float _mainPanelAnim;       // 0.0 (fermé) à 1.0 (ouvert)
    std::map<std::string, float> _teamPanelAnim; // Animation pour chaque panneau d'équipe

    float _playerInfoPanelAnim;

    const float INFO_PANEL_WIDTH = 300.0f;
    const Color INFO_BG_COLOR = { 40, 60, 80, 230 }; // Un bleu/gris un peu différent

    void drawFollowedPlayerPanel(const trantorian_s& player);

    const float ANIM_SPEED = 5.0f;
    const float PANEL_WIDTH = 250.0f;
    const float HEADER_HEIGHT = 40.0f;
    const float ITEM_HEIGHT = 30.0f;
    const Color BG_COLOR = { 50, 50, 70, 200 };
    const Color HEADER_COLOR = { 80, 80, 110, 220 };
    const Color HIGHLIGHT_COLOR = { 120, 120, 150, 255 };

    // void drawMainPanel(const std::set<std::string>& teams);
    // void drawTeamPanel(const std::string& teamName, const std::vector<trantorian_s*>& teamPlayers);
};

#endif
