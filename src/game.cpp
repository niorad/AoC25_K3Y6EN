#include "raylib.h"
#include <raymath.h>
#include <string>
#include <cmath>
#include <iostream>
#include <numeric>
#include <thread>
#include <chrono>
#include <algorithm>
#include "reader.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include <raygui.h>
#include <style_cyber.h>

// Definitions.. geez
struct HighestListNumber;
struct LowestListNumber;

void day_one_one(std::string& resultString);
void day_one_two(std::string& resultString);

void day_two_one(std::string& resultString);
void day_two_two(std::string& resultString);
bool checkRepeatingPattern(std::string s);

void day_three(std::string& resultString, int part);
HighestListNumber getHighestNumber(std::vector<int> v);
// end of definitions.. geez

auto globalTimerStart = std::chrono::high_resolution_clock::now();
auto globalTimerStop = std::chrono::high_resolution_clock::now();
std::string globalLogString = "2025 by ni0r4d";
bool useTestData = true;

struct HighestListNumber {
    int number;
    int position;
};

struct BackgroundPoint {
    Vector2 position;
    Color color;
    float opacity;
    float speed;
    float hspeed;
};
std::array<BackgroundPoint, 500> backgroundPoints;

// Let it snow let it snow let it snow
void initializeBackgroundPoints() {
    for(BackgroundPoint& point : backgroundPoints) {
        point.position = Vector2(GetRandomValue(-200, 640), GetRandomValue(0, 480));
        point.color = WHITE;
        point.opacity = (float)GetRandomValue(0,100) / 100;
        point.speed = point.opacity;
        point.hspeed = (float)GetRandomValue(0,100) / 100;
    }
}

void updateBackgroundPoints() {
    for(BackgroundPoint& point : backgroundPoints) {
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
    float btnHeight = 26;
    initializeBackgroundPoints();

    std::string day_1_1 = "<not solved>";
    std::string day_1_2 = "<not solved>";
    bool textbox_1_1 = false;
    bool textbox_1_2 = false;

    std::string day_2_1 = "<not solved>";
    std::string day_2_2 = "<not solved>";
    bool textbox_2_1 = false;
    bool textbox_2_2 = false;

    std::string day_3_1 = "<not solved>";
    std::string day_3_2 = "<not solved>";
    bool textbox_3_1 = false;
    bool textbox_3_2 = false;

    InitWindow(screenWidth, screenHeight, "AoC25_K3Y6eN");
    SetTargetFPS(60);
    GuiLoadStyleCyber();

    // Main game loop
    while (!WindowShouldClose()) {
        updateBackgroundPoints();

        // Draw
        BeginDrawing();
            ClearBackground(BLACK);

            for(BackgroundPoint& point : backgroundPoints) {
                DrawPixelV(point.position, Fade(WHITE, point.opacity));
            }

            //GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

            GuiLine((Rectangle){ 10, 15, 460, 1 }, "DAY ONE: DIALS");

            // DAY 1 ------------------------------------------------------------
            // ------------------------------------------------------------------
            if (GuiButton((Rectangle){ btn1Left, 30, btnWidth, btnHeight }, "Puzzle 1")) {
                day_1_1 = "Ok let's do this...";
                std::thread(day_one_one, std::ref(day_1_1)).detach();
            }
            if (GuiTextBox((Rectangle){ btn1Left, 66, btnWidth, btnHeight }, day_1_1.data(), 64, textbox_1_1)) textbox_1_1 = !textbox_1_1;

            if (GuiButton((Rectangle){ btn2Left, 30, btnWidth, btnHeight }, "Puzzle 2")) {
                day_1_2 = "working on it...";
                std::thread(day_one_two, std::ref(day_1_2)).detach();
            };
            if (GuiTextBox((Rectangle){ btn2Left, 66, btnWidth, btnHeight }, day_1_2.data(), 64, textbox_1_2)) textbox_1_2 = !textbox_1_2;
            // ------------------------------------------------------------------
            // ------------------------------------------------------------------

            GuiLine((Rectangle){ 10, 115, 460, 1 }, "DAY TWO: INVALID IDs #");

            // DAY 2 ------------------------------------------------------------
            // ------------------------------------------------------------------
            if (GuiButton((Rectangle){ btn1Left, 130, btnWidth, btnHeight }, "Puzzle 1")) {
                day_2_1 = "let's see...";
                std::thread(day_two_one, std::ref(day_2_1)).detach();
            }
            if (GuiTextBox((Rectangle){ btn1Left, 166, btnWidth, btnHeight }, day_2_1.data(), 64, textbox_2_1)) textbox_2_1 = !textbox_2_1;

            if (GuiButton((Rectangle){ btn2Left, 130, btnWidth, btnHeight }, "Puzzle 2")) {
                day_2_2 = "sifting through ranges...";
                std::thread(day_two_two, std::ref(day_2_2)).detach();
            };
            if (GuiTextBox((Rectangle){ btn2Left, 166, btnWidth, btnHeight }, day_2_2.data(), 64, textbox_2_2)) textbox_2_2 = !textbox_2_2;
            // ------------------------------------------------------------------
            // ------------------------------------------------------------------

            GuiLine((Rectangle){ 10, 215, 460, 1 }, "DAY THREE: JOLTAGE!");

            // DAY 2 ------------------------------------------------------------
            // ------------------------------------------------------------------
            if (GuiButton((Rectangle){ btn1Left, 230, btnWidth, btnHeight }, "Puzzle 1")) {
                day_3_1 = "calcing the calc...";
                std::thread(day_three, std::ref(day_3_1), 1).detach();
            }
            if (GuiTextBox((Rectangle){ btn1Left, 266, btnWidth, btnHeight }, day_3_1.data(), 64, textbox_3_1)) textbox_3_1 = !textbox_3_1;

            if (GuiButton((Rectangle){ btn2Left, 230, btnWidth, btnHeight }, "Puzzle 2")) {
                day_3_2 = "calcy mccalcface";
                std::thread(day_three, std::ref(day_3_2), 2).detach();
            };
            if (GuiTextBox((Rectangle){ btn2Left, 266, btnWidth, btnHeight }, day_3_2.data(), 64, textbox_3_2)) textbox_3_2 = !textbox_3_2;
            // ------------------------------------------------------------------
            // ------------------------------------------------------------------

            GuiGroupBox((Rectangle){ 10, 590, 220, 40 }, "LOG");
            GuiLabel((Rectangle){ 20, 590, 220, 40 }, globalLogString.data());
            GuiCheckBox((Rectangle){ 240, 600, 20, 20 }, "use test data", &useTestData);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void startStopwatch() {
    globalTimerStart = std::chrono::high_resolution_clock::now();
}

void stopStopwatch() {
    globalTimerStop = std::chrono::high_resolution_clock::now();
    auto timerResult = std::chrono::duration_cast<std::chrono::milliseconds>(globalTimerStop - globalTimerStart);
    globalLogString = "Operation took " + std::to_string(timerResult.count()) + "ms";
}

void day_one_one(std::string& resultString) {

    startStopwatch();
    struct Movement {
        int steps;
        std::string direction;
    };

    const auto reader = Reader();
    const auto filename = useTestData ? "./src/inputs/1/test.txt" : "./src/inputs/1/input.txt";
    const auto linesStrings = reader.readFile(filename);

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

    resultString = std::to_string(zeros);
    stopStopwatch();
}

void day_one_two(std::string& resultString) {

    startStopwatch();
    struct Movement {
        int steps;
        std::string direction;
    };

    const auto reader = Reader();
    const auto filename = useTestData ? "./src/inputs/1/test.txt" : "./src/inputs/1/input.txt";
    const auto linesStrings = reader.readFile(filename);

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

    resultString = std::to_string(zeros);
    stopStopwatch();
}

void day_two_one(std::string& resultString) {
    startStopwatch();
    struct Range {
        int64_t min;
        int64_t max;
    };

    std::vector<int64_t> invalidIds;

    const auto reader = Reader();
    const auto filename = useTestData ? "./src/inputs/2/test.txt" : "./src/inputs/2/input.txt";
    const auto linesStrings = reader.readFile(filename);

    std::vector<Range> ranges;

    for(int i = 0; i < linesStrings.size(); i+=2) {
        auto r = Range{std::stoll(linesStrings[i]), std::stoll(linesStrings[i+1])};
        ranges.push_back(r);
    };

    for(Range r : ranges) {
        //  if both min and max are same-length and can't be split in the middle, there can be no invalid IDs
        if(std::to_string(r.min).length() % 2 == 1 && std::to_string(r.min).length() == std::to_string(r.max).length()) {
            continue;
        }

        // look at one range
        for(int64_t i = r.min; i <= r.max; i++) {
            std::string s = std::to_string(i);
            if(s.length() % 2 == 0) {
                auto half1 = s.substr(0, s.length() / 2);
                auto half2 = s.substr(s.length() / 2);
                if(half1 == half2) {
                    invalidIds.push_back(i);
                }
            }
        }
    }

    int64_t sum = std::reduce(invalidIds.begin(), invalidIds.end());
    std::string strSum = std::to_string(sum);
    resultString = strSum;

    stopStopwatch();
}

void day_two_two(std::string& resultString) {

    startStopwatch();

    struct Range {
        int64_t min;
        int64_t max;
    };

    std::vector<int64_t> invalidIds;

    const auto reader = Reader();
    const auto filename = useTestData ? "./src/inputs/2/test.txt" : "./src/inputs/2/input.txt";
    const auto linesStrings = reader.readFile(filename);

    std::vector<Range> ranges;

    for(int i = 0; i < linesStrings.size(); i+=2) {
        auto r = Range{std::stoll(linesStrings[i]), std::stoll(linesStrings[i+1])};
        ranges.push_back(r);
    };

    for(Range r : ranges) {
        // look at one range
        for(int64_t i = r.min; i <= r.max; i++) {
            std::string s = std::to_string(i);
            if(i < 11) continue;
            if(checkRepeatingPattern(s)) {
                invalidIds.push_back(i);
            }
        }
    }

    //int64_t sum = std::reduce(invalidIds.begin(), invalidIds.end());
    int64_t sum = 0;
    for(int i = 0; i < invalidIds.size(); i++) {
        sum += invalidIds[i];
    }
    std::string strSum = std::to_string(sum);
    resultString = strSum;

    stopStopwatch();
}

void day_three(std::string& resultString, int part) {

    startStopwatch();
    const auto reader = Reader();
    const auto filename = useTestData ? "./src/inputs/3/test.txt" : "./src/inputs/3/input.txt";
    const auto linesStrings = reader.readFile(filename);
    uint64_t acc = 0;
    int maxLength = part == 1 ? 2 : 11;

    for(std::string s : linesStrings) {

        std::vector<char> lineAsCharVector = std::vector(s.begin(), s.end());
        std::vector<int> lineAsIntVector;
        std::vector<int> solutionVector;
        uint64_t solution = 0;
        auto length = s.length();

        for(char c : lineAsCharVector) {
            lineAsIntVector.push_back(atoi(&c));
        }

        int currentLeftBorder = 0;
        for(int i = maxLength - 1; i >= 0; i--) {
            std::vector<int> legalList(lineAsIntVector.begin() + currentLeftBorder, lineAsIntVector.end() - i);
            HighestListNumber h = getHighestNumber(legalList);
            solutionVector.push_back(h.number);
            currentLeftBorder += h.position + 1;
        }

        for(auto num : solutionVector) {
            solution = solution * 10 + num;
        }

        acc += solution;
    }

    resultString = std::to_string(acc);
    stopStopwatch();
}


// UTILITIES

// Used for 2_2, checks for repeating patterns in a string up to a length of ten
bool checkRepeatingPattern(std::string s) {
    auto length = s.length();

    // length 1 can go fly a kite
    if(length == 1) return false;

    // lengths 2, 3, 5, 7 can only be invalid if every char is identical
    // 4 = groups of 1 and 2
    // 6 = groups of 1, 2, 3
    // 8 = groups of 1, 2, 4
    // 9 = groups of 1, 3
    // 10 = groups of 1, 2, 5


    // check groups of 4 and 5
    // can only happen on one occasion so lets leave out the loop
    if(length == 8) {
        if(s.substr(0,4) == s.substr(4, 4)) return true;
    }

    if(length == 10) {
        if(s.substr(0,5) == s.substr(5, 5)) return true;
    }

    // check groups of 2
    if(length == 4 || length == 6 || length == 8 || length == 10) {
        bool groupsOfTwoSame = true;
        for(int i = 2; i < length; i+=2) {
            if(s.substr(i-2, 2) != s.substr(i, 2)) {
                groupsOfTwoSame = false;
                break;
            }
        }
        if(groupsOfTwoSame) return true;
    }

    // check groups of 3
    if(length == 6 || length == 9) {
        bool groupsOfThreeSame = true;
        for(int i = 3; i < length; i+=3) {
            if(s.substr(i-3, 3) != s.substr(i, 3)) {
                groupsOfThreeSame = false;
                break;
            }
        }
        if(groupsOfThreeSame) return true;
    }

    // check every single char
    // this check can be done on every string longer than 1
    bool everySingleCharSame = true;
    for(int i = 1; i < length; i++) {
        if(s[i-1] != s[i]) {
            everySingleCharSame = false;
            break;
        }
    }
    if(everySingleCharSame) return true;

    return false;
}

// Used for 3_1, get the highest int from a vector of ints, returns position and the int that is hightest
// Returns Vector2 {number, position}
HighestListNumber getHighestNumber(std::vector<int> v) {
    auto result = std::max_element(v.begin(), v.end());
    auto index = std::distance(v.begin(), result);
    auto number = *result;
    return HighestListNumber{number, (int)index};
}