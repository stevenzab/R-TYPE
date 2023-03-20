/*
** EPITECH PROJECT, 2023
** TextField.cpp
** File description:
** TextField
*/

#include "TextField.hpp"

//! Constructor class Textfield
TextField::TextField(const std::string text, float x, float y)
{
    _pos_x = x;
    _pos_y = y;
    _text = text;
    mouseOnText = false;
    textfield = { x/2.0f - 100, y/2, 225, 50 };
    letterCount = 0;
}

//! Deconstructor class Textfield
TextField::~TextField()
{
}

//! draw the textfield
void TextField::draw()
{
    DrawText(_text.c_str(), _pos_x/2, _pos_y/2 - 22, 20, GRAY);
    DrawRectangleRec(textfield, LIGHTGRAY);
    
    if (mouseOnText)
        DrawRectangleLines((int)textfield.x, (int)textfield.y, (int)textfield.width, (int)textfield.height, RED);
    else
        DrawRectangleLines((int)textfield.x, (int)textfield.y, (int)textfield.width, (int)textfield.height, DARKGRAY);
    
    DrawText(name.c_str(), (int)textfield.x + 5, (int)textfield.y + 8, 40, MAROON);

    if (mouseOnText) {
        if (letterCount < 15) {
            if (((framesCounter/20)%2) == 0)
                DrawText("_", (int)textfield.x + 8 + MeasureText(name.c_str(), 40), (int)textfield.y + 12, 40, MAROON);
        } else
                DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
        }
}

//! check the collision between the mouse and the textfield and get the input
std::string TextField::CheckCollisionTextField(Vector2 mousePos)
{
    if (CheckCollisionPointRec(GetMousePosition(), textfield)) mouseOnText = true;
    else mouseOnText = false;

    if (mouseOnText) {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0) {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < 15)) {
                    letterCount++;
                    name.push_back((char)key);
                }
                key = GetCharPressed();  // Check next character in the queue
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                    letterCount--;
                if (letterCount < 0) letterCount = 0;
                else name.pop_back();
            }
        } else
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText) framesCounter++;
        else framesCounter = 0;
    return name;
}