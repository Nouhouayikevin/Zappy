/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** loadingbar.cpp
*/

#include "message_box.hpp"

void DrawTextBoxed(Font font, std::string text, Rectangle ret, float fontSize, float spacing, Color color) {
    float posY = ret.y + spacing;
    auto arr = split(text);
    std::string keeper;

    for (auto temp : arr) {
        if (((float)(MeasureText(keeper.c_str(), fontSize) + MeasureText(temp.c_str(), fontSize) + 1) + ret.x + spacing) <= ((ret.x + ret.width) - spacing)) keeper += !keeper.empty() ? " " + temp : temp;
        else {
            DrawTextEx(font, keeper.c_str(), (Vector2){ret.x + spacing, posY}, fontSize, spacing, color);
            keeper.erase(keeper.begin(), keeper.end());
            posY += fontSize + spacing;
            if (posY > ((ret.y + ret.height)  - spacing))
                break;
            keeper += temp;
        }
    }
    DrawTextEx(font, keeper.c_str(), (Vector2){ret.x + spacing, posY}, fontSize, spacing, color);
}

Rectangle &SupaRect::get() {
    return rec;
}

void SupaRect::setThickness(const float &thickness, Color color) {
    _thickness = thickness;
    _thColor = color;
}

void SupaRect::updateColor(Color color) {
    _color = color;
}

void SupaRect::updateTextColor(Color color) {
    _textColor = color;
}

void SupaRect::updateRec(Rectangle &other) {
    rec = other;
}

void SupaRect::setTextSize(float textSize) {
    _textSize = textSize;
}

void SupaRect::setText(const std::string text, Font &font, Color color) {
    _text = text;
    _textColor = color;
    datra = font;
    
}



void SupaRect::updateRec() {
    rec = {(float)_posX, (float)_posY, (float)_width, (float)_height};
}

void SupaRect::updatePositions(int posX, int posY) {
    _posX = posX >= 1 ? posX : 1; _posY = posY >= 1 ? posY : 1;
    updateRec();
}

void SupaRect::updateDimensions(int width, int height) {
    _width = width >= 1 ? width : 1; _height = height >= 1 ? height : 1;
    updateRec();
}

SupaRect::SupaRect(const int &posX, const int &posY, const int &width, const int &height, const Color &color) : _color(color),
    _posX(posX >= 1 ? posX : 1), _posY(posY >= 1 ? posY : 1), _width(width >= 1 ? width : 1),
    _height(height >= 1 ? height : 1) {
        updateRec();
}

void SupaRect::FontDestroyer(){}

SupaRect::~SupaRect(){
    FontDestroyer();
}

void SupaRect::draw() {
    BeginDrawing();
        DrawRectangleRec(rec, _color);
        DrawTextBoxed(datra, _text, rec, _textSize, 1.f, _textColor);
    EndDrawing();
}
