#include <iostream>
#include <cmath>
#include <raylib.h>

#define TEXTC CLITERAL(Color){195, 235, 255, 255}
#define GRAY1 CLITERAL(Color){11, 16, 20, 255}
#define GRAY2 CLITERAL(Color){23, 36, 43, 255}
#define GRAY3 CLITERAL(Color){29, 42, 48, 255}
#define GRAY4 CLITERAL(Color){38, 50, 56, 255}
#define GRAY5 CLITERAL(Color){55, 71, 79, 255}

#define BLUE1 CLITERAL(Color){56, 33, 208, 255}
#define BLUE2 CLITERAL(Color){33, 65, 208, 255}
#define BLUE3 CLITERAL(Color){33, 109, 208, 255}
#define BLUE4 CLITERAL(Color){33, 150, 208, 255}
#define BLUE5 CLITERAL(Color){45, 171, 235, 255}
#define BLUE6 CLITERAL(Color){105, 205, 255, 255}

int fps = 60;
const int width = 540;
const int height = 720;

using std::string;
using std::cout;
using std::endl;
using std::to_string;;

class Button{
public:
    Rectangle button = {0,0,0,0};
    bool pressed = false;
    string text = "";
    Color cFore;
    Color cBackDark;
    Color cBackLight;

    Button(float x, float y, float w, float h, 
            string name="test", 
            Color backdark = GRAY2, 
            Color backlight = GRAY3, 
            Color fore = TEXTC
        ){
    
        button = {x,y,w,h};
        text = name;
        cBackDark = backdark;
        cBackLight = backlight;
        cFore = fore;
    }

    void centerx(){
        button.x += (width/2-button.width/2)-2.5;
    }
    void centery(){
        button.y += (height/2-button.height/2)-2.5;
    }

    void update(){
        DrawRectangleRec(button, cBackDark);
        DrawRectangleLinesEx(button,10, cBackLight);

        DrawText(text.c_str(), button.x+15, button.y+15, 32, cFore);
        pressed = IsMouseButtonReleased(0) && CheckCollisionPointRec(GetMousePosition(), button);
    }
};


int main(){
    SetTraceLogLevel(LOG_DEBUG);
    InitWindow(width, height, "Olawe");
    SetTargetFPS(fps);
    SetExitKey(KEY_Q);
    int mode = 0;

    // Label
    Button bLabel(0,0,540,60,"Menu");

    // Main menu, 0
    Button bLogin(1,600,200,100,"\t\tLogin",BLUE4,BLUE5,BLACK);
    bLogin.centerx();
    Button bEnter(1,450,300,100,"\t\t\t\tEnter \n\t(No account)");
    bEnter.centerx();

    // Map , 1
    Texture tMap = LoadTexture("img/map.png");
    Vector2 mapPos = {0,0};
    float sizeMap = 1.0f;
    Button bSearch(1,15,520,60,"Search Bar");
    bSearch.centerx();

    // Login page, 2
    Button bMail(1,150,520,60,"example@gmail.com");
    bMail.centerx();
    Button bPass(1,250,520,60,"password123");
    bPass.centerx();
    Button bSubmit(1,350,520,60,"Submit",BLUE4,BLUE5,BLACK);
    bSubmit.centerx();

    while(!WindowShouldClose()){
        if(bEnter.pressed){
            mode = 1;
            bEnter.pressed = false;
        }
        if(bLogin.pressed){
            mode = 2;
            bLogin.pressed = false;
        }
        if(bSubmit.pressed){
            mode = 0;
            bSubmit.pressed = false;
        }

        BeginDrawing();


        switch(mode){
            case 0: // Menu
                bLabel.text = "App Name";
                bLabel.update();
                ClearBackground(GRAY1);
                bLogin.update();
                bEnter.update();
    
                DrawText("\t\t App\nPrototype\n\t\t(Logo)", 180, 180, 32, TEXTC);
    
                break;
    
            case 1: // Map
                ClearBackground(GRAY1);
                if(IsKeyDown(KEY_ESCAPE)) mode = 0;
                if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                    mapPos.x += GetMouseDelta().x;
                    mapPos.y += GetMouseDelta().y;
                }
    
                sizeMap += GetMouseWheelMove()*0.1;
                mapPos.x -= GetMouseWheelMove()*10;
                mapPos.y -= GetMouseWheelMove()*10;
    
                DrawTextureEx(tMap, mapPos, 0.0f, sizeMap, WHITE);
                bSearch.update();
    
                break;
    
            case 2: // Login Page
                bLabel.text = "Login";
                bLabel.update();
                if(IsKeyDown(KEY_ESCAPE)) mode = 0;
                ClearBackground(GRAY1);
                bMail.update();
                bPass.update();
                bSubmit.update();
    
                break;
    
            default:
                mode = 0;
        }

        EndDrawing();   
    }
    UnloadTexture(tMap);
    CloseWindow();
    return 0;
}