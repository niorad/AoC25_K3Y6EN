#include "raylib.h"
#include <raymath.h>
#include <string>
#include <cmath>
#include <iostream>
#include "reader.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include <raygui.h>
#include <style_cyber.h>

std::string day_one_one();
std::string day_one_two();


struct backgroundPoint {
    Vector2 position;
    Color color;
    float opacity;
    float speed;
    float hspeed;
};
std::array<backgroundPoint, 500> backgroundPoints;

// Let it snow let it snow let it snow
void initializeBackgroundPoints() {
    for(backgroundPoint& point : backgroundPoints) {
        point.position = Vector2(GetRandomValue(-200, 640), GetRandomValue(0, 480));
        point.color = WHITE;
        point.opacity = (float)GetRandomValue(0,100) / 100;
        point.speed = point.opacity;
        point.hspeed = (float)GetRandomValue(0,100) / 100;
    }
}

void updateBackgroundPoints() {
    for(backgroundPoint& point : backgroundPoints) {
        point.position.y += point.speed;
        point.position.x += point.hspeed;
        if(point.position.y > 640) {
            point.position.y = 0;
            point.position.x = GetRandomValue(-200, 640);
        }
    }
}

int main() {

    int screenWidth = 480;
    int screenHeight = 640;
    float btnMargin = 10;
    float btn1Left = btnMargin;
    float btn2Left = 245;
    float btnWidth = 225;
    float btnHeight = 40;
    initializeBackgroundPoints();

    std::string day_1_1 = "<not solved>";
    std::string day_1_2 = "<not solved>";
    bool textbox_1_1 = false;
    bool textbox_1_2 = false;

    InitWindow(screenWidth, screenHeight, "AoC25_K3Y6eN");
    SetTargetFPS(60);
    GuiLoadStyleCyber();

    // Main game loop
    while (!WindowShouldClose()) {

    updateBackgroundPoints();

        // Draw
        BeginDrawing();
            ClearBackground(BLACK);

            for(backgroundPoint& point : backgroundPoints) {
                DrawPixelV(point.position, Fade(WHITE, point.opacity));
            }

            GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

            // DAY 1 ------------------------------------------------------------
            // ------------------------------------------------------------------
            if (GuiButton((Rectangle){ btn1Left, btnMargin, btnWidth, btnHeight }, "Calculate Day 1 Puzzle 1")) {
                day_1_1 = day_one_one();
            }
            if (GuiTextBox((Rectangle){ btn1Left, 60, btnWidth, btnHeight }, day_1_1.data(), 64, textbox_1_1)) textbox_1_1 = !textbox_1_1;

            if (GuiButton((Rectangle){ btn2Left, btnMargin, btnWidth, btnHeight }, "Calculate Day 1 Puzzle 2")) {
                day_1_2 = day_one_two();
            };
            if (GuiTextBox((Rectangle){ btn2Left, 60, btnWidth, btnHeight }, day_1_2.data(), 64, textbox_1_2)) textbox_1_2 = !textbox_1_2;
            // ------------------------------------------------------------------
            // ------------------------------------------------------------------

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

std::string day_one_one() {

    struct Movement {
        int steps;
        std::string direction;
    };

    const auto reader = Reader();
    const auto linesStrings = reader.readFile("./src/inputs/1/input.txt");

    std::vector<Movement> movements;

    for(std::string s : linesStrings) {
        std::string dir({&s[0],1});
        auto len = s.length();
        std::string amountString = {&s[1], len-1};
        auto amount = std::stoi(amountString);
        Movement m = {amount, dir};
        movements.push_back(m);
    }

    int dial = 50;
    int zeros = 0;

    for(Movement m : movements) {

        if(m.direction == "R") {
            dial += (m.steps % 100);
            dial = dial % 100;
        } else {
            auto value = m.steps % 100;
            if(dial >= value) {
                dial = dial - value;
            } else {
                dial = 100 - (std::abs(dial - value));
            };
        }
        if(dial == 100) dial = 0;
        if(dial == 0) zeros++;
    };

    return std::to_string(zeros);
}


std::string day_one_two() {

    struct Movement {
        int steps;
        std::string direction;
    };

    const auto reader = Reader();
    const auto linesStrings = reader.readFile("./src/inputs/1/input.txt");

    std::vector<Movement> movements;

    for(std::string s : linesStrings) {
        std::string dir({&s[0],1});
        auto len = s.length();
        std::string amountString = {&s[1], len-1};
        auto amount = std::stoi(amountString);
        Movement m = {amount, dir};
        movements.push_back(m);
    }

    int dial = 50;
    int zeros = 0;

    for(Movement m : movements) {

        int extraZeros = 0;
        bool dialWasZero = dial == 0;

        if(m.direction == "R") {
            dial += m.steps;
        } else {
            dial -= m.steps;
        }

        // dial is always positive, so when it goes negative, we had one safe zero-pass
        if(dial < 0) {
            if(!dialWasZero) {
                // if dial was zero before turning negative, it wouldn't count
                zeros++;
            }
            if(dial <= -100) {
                zeros += dial / -100;
            }

        } else if(dial == 0) {
            //after dialing is exactly 0 add one zero
            zeros++;
        } else {
            //after dialing is positive
            zeros += dial / 100;
        }

        //reset the dial
        if(dial < 0) {
            dial = 100 - (std::abs(dial % 100));
        } else {
            dial = dial % 100;
        }

        if(dial == 100) dial = 0;
    };

    return std::to_string(zeros);
}