/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** loadingbar.cpp
*/

#include "../include/loadingBar.hpp"
#include <cmath>

Loading_bar::Loading_bar()
    : _currentProgress(0.0f), _posX(1920), _posY(1080) {}

Loading_bar::~Loading_bar() {}

void Loading_bar::setCoord(size_t pos_x, size_t pos_y) {
    _posX = pos_x;
    _posY = pos_y;
}

void Loading_bar::update(float progress) {
    _currentProgress = Clamp(progress, 0.0f, 100.0f);
}

void Loading_bar::draw(const std::string& text, Color linesColor, Color contentColor) {
    float barWidth = _posX - 40;
    float currentBarWidth = barWidth * (_currentProgress / 100.0f);

    DrawRectangle(20, _posY - 100, barWidth, 40, {20, 20, 20, 255});
    DrawRectangleLinesEx({20, (float) _posY - 100, barWidth, 40}, 2, linesColor);

    if (currentBarWidth > 0) {
        DrawRectangle(22, _posY - 98, currentBarWidth - 4, 36, contentColor);
    }
    
    DrawText(text.c_str(), 30, _posY - 130, 25, LIGHTGRAY);
}
