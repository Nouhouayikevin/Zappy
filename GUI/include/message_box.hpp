/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** message_box.hpp
*/

#ifndef MESSAGE_BOX_
    #define MESSAGE_BOX_
    #include <cmath>
    #include "my_include.hpp"
    #include "my_define.hpp"
    #include "struct.hpp"

void DrawTextBoxed(Font font, std::string text, Rectangle ret,
    float fontSize, float spacing, Color color);

class SupaRect {
    private:
        Font datra;
        Color _color=  TRANSPARENT;
        Rectangle rec;
        Color _thColor {TRANSPARENT};
        Color _textColor {BLACK};
        std::string _text;
        float _textSize {3.f};
        float _thickness {0.f};
        std::size_t _posX {1};
        std::size_t _posY {1};
        std::size_t _width {1};
        std::size_t _height {1};
        void FontDestroyer();
    public:
        SupaRect(){};
        Rectangle &get();
        void setThickness(const float &thickness, Color color = WHITE);
        void updateColor(Color color);
        void updateTextColor(Color color);
        void updateRec(Rectangle &other);
        void setTextSize(float textSize);
        void setText(const std::string text, Font &font, Color color = BLACK);
        void updateRec();
        void updatePositions(int posX = 0, int posY = 0);
        void updateDimensions(int width = 0, int height = 0);
        void updateColorTransparency(int ){};
        SupaRect(const int &posX, const int &posY, const int &width, const int &height, const Color &color);
        void draw();
        ~SupaRect();
};

#endif
