/**

* Author: Stacey Chen

* Assignment: Pong Clone

* Date due: 10/5/2026

* I pledge that I have completed this assignment without

* collaborating with anyone else, in conformance with the

* NYU School of Engineering Policies and Procedures on

* Academic Misconduct.

**/

#include "CS3113/cs3113.h"
#include <math.h>

// Enums
enum AppStatus {TERMINATED, RUNNING};

// Global Constants
constexpr int SCREEN_WIDTH  = 800 * 1.5f,
              SCREEN_HEIGHT = 450 * 1.5f,
              FPS           = 60;
const char BG_COLOUR[] = "#B2AAC6";

// Global Variables
AppStatus gAppStatus = RUNNING;

// Function Declarations
void intialise();
void processInput();
void update();
void render();
void shutdown();

// Function Definitions
void initialise(){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Project 1 - Simple 2D Scene");
    
    SetTargetFPS(FPS);
}

void processInput(){
    if (WindowShouldClose()) gAppStatus = TERMINATED;
}

void update(){

}

void render(){
    BeginDrawing();

    ClearBackground(ColorFromHex(BG_COLOUR));

    EndDrawing();
}

void shutdown(){
    CloseWindow();
}

int main(void){
    initialise();

    while (gAppStatus == RUNNING){
        processInput();
        update();
        render();
    }

    shutdown();

    return 0;
}
