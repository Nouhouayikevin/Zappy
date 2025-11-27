/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** loadingBar.hpp
*/

#ifndef LOADING_BAR_HPP
#define LOADING_BAR_HPP

#include <string>
#include "raylib.h"
#include "raymath.h"

class Loading_bar {
private:
    float _currentProgress; // Progrès de 0.0f à 100.0f
    size_t _posX;
    size_t _posY;

public:
    Loading_bar();
    ~Loading_bar();

    void setCoord(size_t pos_x, size_t pos_y);
    void update(float progress); // Met à jour le pourcentage de progression
    void draw(const std::string& text, Color linesColor, Color contentColor);
};

#endif // LOADING_BAR_HPP