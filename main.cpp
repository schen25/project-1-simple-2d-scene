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
#include <vector>

// Global Constants
constexpr int SCREEN_WIDTH  = 800 * 1.5f,
              SCREEN_HEIGHT = 450 * 1.5f,
              FPS           = 60,
              SIZE = 75;

constexpr float MAX_ROW_AMP     = 10.0f,
                MAX_RAND_RANGE  = 90.0f,
                BUBBLE_SPACING = 175.0f;

constexpr char BG_COLOUR[] = "#B2AAC6";
constexpr Vector2 ORIGIN = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
constexpr Vector2 BUBBLE_BASE_SIZE = {static_cast<float>(SIZE),
                                      static_cast<float>(SIZE)};
constexpr Vector2 WITCH_OFFSET = {-200, 0};
constexpr Vector2 STICK_OFFSET = {-120, 100};
constexpr Vector2 CAULDRON_OFFSET = {25, 145};
constexpr Vector2 BUBBLE_SWIRL_OFFSET = {0, 140};

// images drawn by me, so no suing yay :'D
constexpr char WITCH_FP[] = "assets/witchMinusArms.png";
constexpr char STICK_FP[] = "assets/stickPlusArms.png";
constexpr char CAULDRON_FP[] = "assets/cauldron.png";
constexpr char BUBBLE_FP[] = "assets/bubble.png";
constexpr char SWIRL_FP[] = "assets/swirl.png";

// Global Variables
AppStatus gAppStatus    = RUNNING;
float   gScaleFactor    = SIZE,
        gAngle          = 0.0f,
        gPulseTime      = 0.0f,
        gStickRowTime   = 0.0f,
        gRowFreq        = 2.5f,
        gPreviousTicks  = 0.0f,
        gBubbleSpeed    = 20.0f,
        gBubbleTime     = 0.0f;
Vector2 gWitchPos = {ORIGIN.x + WITCH_OFFSET.x, ORIGIN.y + WITCH_OFFSET.y};
Vector2 gStickPos = {ORIGIN.x + STICK_OFFSET.x, ORIGIN.y + STICK_OFFSET.y};
Vector2 gCauldronPos = {ORIGIN.x + CAULDRON_OFFSET.x,
                            ORIGIN.y + CAULDRON_OFFSET.y};
Vector2 gBubbleScale          = BUBBLE_BASE_SIZE;

std::vector<Vector2> gBubblePosList = { // lowest to highest
    {ORIGIN.x + BUBBLE_SWIRL_OFFSET.x + 70,
     ORIGIN.y + BUBBLE_SWIRL_OFFSET.y},
    {ORIGIN.x + BUBBLE_SWIRL_OFFSET.x + 25,
     ORIGIN.y + BUBBLE_SWIRL_OFFSET.y - BUBBLE_SPACING},
    {ORIGIN.x + BUBBLE_SWIRL_OFFSET.x + 55,
     ORIGIN.y + BUBBLE_SWIRL_OFFSET.y - 2*BUBBLE_SPACING}
};

Texture2D gWitchTexture;
Texture2D gStickTexture;
Texture2D gCauldronTexture;
Texture2D gBubbleTexture;
Texture2D gSwirlTexture;

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
    gBubbleTexture = LoadTexture(BUBBLE_FP);
    gSwirlTexture = LoadTexture(SWIRL_FP);


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

    // stirring/rowing motion
    gStickRowTime += 1.0f*deltaTime;
    gStickPos = {
        ORIGIN.x + STICK_OFFSET.x + MAX_ROW_AMP * cos(gRowFreq*gStickRowTime),
        ORIGIN.y + STICK_OFFSET.y + 0.5f * MAX_ROW_AMP * sin(gRowFreq*gStickRowTime)
    };

    // bubbling
    // gBubbleTime += 1.0f*deltaTime;
    for (int i = 0; i < 3; i++){
        gBubblePosList[i].y -= gBubbleSpeed*deltaTime; // check for wrap later
    }


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
        gWitchPos.x,
        gWitchPos.y,
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
        gStickPos.x,
        gStickPos.y,
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
        gCauldronPos.x,
        gCauldronPos.y,
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

    // bubbles
    Rectangle bTextureArea = {
        0.0f, 0.0f,
        static_cast<float>(gBubbleTexture.width),
        static_cast<float>(gBubbleTexture.height)
    };

    Rectangle bDestinationArea = {
        gBubblePosList[0].x,
        gBubblePosList[0].y,
        static_cast<float>(gBubbleScale.x),
        static_cast<float>(gBubbleScale.y)
    };

    Vector2 bubbleOrigin = {
        static_cast<float>(gBubbleScale.x)/2,
        static_cast<float>(gBubbleScale.y)/2
    };

    for (int i = 0; i < 3; i++){
        Rectangle bDestinationArea = {
            gBubblePosList[i].x,
            gBubblePosList[i].y,
            static_cast<float>(gBubbleScale.x),
            static_cast<float>(gBubbleScale.y)
        };

        DrawTexturePro(
            gBubbleTexture,
            bTextureArea,
            bDestinationArea,
            bubbleOrigin,
            gAngle,
            WHITE
        );
    }

    EndDrawing();
}

void shutdown(){
    CloseWindow();

    // unload textures
    UnloadTexture(gWitchTexture);
    UnloadTexture(gStickTexture);
    UnloadTexture(gCauldronTexture);
    UnloadTexture(gBubbleTexture);
    UnloadTexture(gSwirlTexture);

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
