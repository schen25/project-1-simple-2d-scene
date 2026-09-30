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

// Global Constants
constexpr int SCREEN_WIDTH  = 800 * 1.5f,
              SCREEN_HEIGHT = 450 * 1.5f,
              FPS           = 60,
              SIZE = 1000;

constexpr char BG_COLOUR[] = "#B2AAC6";
constexpr Vector2 ORIGIN = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
constexpr Vector2 BASE_SIZE = {static_cast<float>(SIZE), static_cast<float>(SIZE)};

// images drawn by me, so no suing yay :'D
constexpr char WITCH_FP[] = "assets/witchMinusArms.png";
constexpr char STICK_FP[] = "assets/stickPlusArms.png";
constexpr char CAULDRON_FP[] = "assets/cauldron.png";

// Global Variables
AppStatus gAppStatus    = RUNNING;
float   gScaleFactor    = SIZE,
        gAngle          = 0.0f,
        gPulseTime      = 0.0f;
Vector2 gWitchOffset     = {-200, 0};
Vector2 gStickOffset     = {-110,100};
Vector2 gCauldronOffset = {25,145};
Vector2 gScale          = BASE_SIZE;
float gPreviousTicks = 0.0f;

Texture2D gWitchTexture;
Texture2D gStickTexture;
Texture2D gCauldronTexture;

// Function Declarations
void intialise();
void processInput();
void update();
void render();
void shutdown();

// Function Definitions
void initialise(){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Project 1 - Simple 2D Scene");
    
    // load textures
    gWitchTexture = LoadTexture(WITCH_FP);
    gStickTexture = LoadTexture(STICK_FP);
    gCauldronTexture = LoadTexture(CAULDRON_FP);


    SetTargetFPS(FPS);
}

void processInput(){
    if (WindowShouldClose()) gAppStatus = TERMINATED;
}

void update(){
    // Delta time
    float ticks = static_cast<float>(GetTime());
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks = ticks;

    // gPulseTime += 1.0f*deltaTime;

    // gScale = {
    //     BASE_SIZE.x + MAX_AMP * cos(gPulseTime),
    //     BASE_SIZE.y + MAX_AMP * cos(gPulseTime)
    // };
}

void render(){
    BeginDrawing();

    ClearBackground(ColorFromHex(BG_COLOUR));

    // witch (minus arms)
    Rectangle wTextureArea = {
        0.0f, 0.0f,
        static_cast<float>(gWitchTexture.width),
        static_cast<float>(gWitchTexture.height)
    };

    Rectangle wDestinationArea = {
        ORIGIN.x + gWitchOffset.x,
        ORIGIN.y + gWitchOffset.y,
        static_cast<float>(gWitchTexture.width),
        static_cast<float>(gWitchTexture.height)
    };

    Vector2 witchOrigin = {
        static_cast<float>(gWitchTexture.width) / 2.0f,
        static_cast<float>(gWitchTexture.height) / 2.0f
    };

    DrawTexturePro(
        gWitchTexture,
        wTextureArea,
        wDestinationArea,
        witchOrigin,
        gAngle,
        WHITE
    );

    // stick (plus arms)

    Rectangle sTextureArea = {
        0.0f, 0.0f,
        static_cast<float>(gStickTexture.width),
        static_cast<float>(gStickTexture.height)
    };

    Rectangle sDestinationArea = {
        ORIGIN.x + gStickOffset.x,
        ORIGIN.y + gStickOffset.y,
        static_cast<float>(gStickTexture.width),
        static_cast<float>(gStickTexture.height)
    };

    Vector2 stickOrigin = {
        static_cast<float>(gStickTexture.width) / 2,
        static_cast<float>(gStickTexture.height) /2
    };

    DrawTexturePro(
        gStickTexture,
        sTextureArea,
        sDestinationArea,
        stickOrigin,
        gAngle,
        WHITE
    );

    // cauldron
    Rectangle cTextureArea = {
        0.0f, 0.0f,
        static_cast<float>(gCauldronTexture.width),
        static_cast<float>(gCauldronTexture.height)
    };

    Rectangle cDestinationArea = {
        ORIGIN.x + gCauldronOffset.x,
        ORIGIN.y + gCauldronOffset.y,
        static_cast<float>(gCauldronTexture.width),
        static_cast<float>(gCauldronTexture.height)
    };

    Vector2 cauldronOrigin = {
        static_cast<float>(gCauldronTexture.width)/2,
        static_cast<float>(gCauldronTexture.height)/2
    };

    DrawTexturePro(
        gCauldronTexture,
        cTextureArea,
        cDestinationArea,
        cauldronOrigin,
        gAngle,
        WHITE
    );

    EndDrawing();
}

void shutdown(){
    CloseWindow();

    // unload textures
    UnloadTexture(gWitchTexture);
    UnloadTexture(gStickTexture);
    UnloadTexture(gCauldronTexture);

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
