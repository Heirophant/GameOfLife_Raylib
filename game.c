#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<unistd.h>
/*

TODOs:

[x] Draw Grid

[x] Game logic

[x] Mouse Integration

[x] Title Screen

[ ] Maybe for NxM screen

*/



const int ALIVE = 1;
const int DEAD = 0;



#define CELL_SIZE 30


#define SCREEN_SIZE 1200

#define DIM (SCREEN_SIZE / CELL_SIZE)


int grid[DIM][DIM] = {{DEAD}};



void grid_init_random(){
    srand(time(0));
    for(int i=0;i<4*DIM;++i){

        int cellX = rand() % DIM;
        int cellY = rand() % DIM;
        grid[cellX][cellY] = ALIVE;
    }
}



void fill_color(){
    for(size_t i=0;i<DIM;++i){
        for(size_t j=0;j<DIM;++j){
            if(grid[i][j] == ALIVE){
                DrawRectangle(i*CELL_SIZE,j*CELL_SIZE,CELL_SIZE,CELL_SIZE,BLACK);
            }
        }
    }
}




void draw_grid(){

    for(size_t i=0;i<DIM;++i){
        DrawLine(0,i*CELL_SIZE,SCREEN_SIZE,i*CELL_SIZE,BLACK); // Horizontal line
        DrawLine(i*CELL_SIZE,0,i*CELL_SIZE,SCREEN_SIZE,BLACK); // Vertical line
    }

    fill_color();


}



const int dir[8][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}};

/*

4 Rules (wiki):

1. Any live cell with fewer than two live neighbours dies
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies
4. Any dead cell with exactly three live neighbours becomes a live cell.


*/
void logic(){
    int nextState[DIM][DIM];
    for(size_t i=0;i<DIM;++i){
        for(size_t j=0;j<DIM;++j){
            int alive_cells = 0;
            for(size_t k=0;k<8;++k){
                int new_x = i+dir[k][0];
                int new_y = j+dir[k][1];
                if(new_x < 0 || new_y < 0 || new_x >= SCREEN_SIZE || new_y >= SCREEN_SIZE){
                    continue;
                }

                if(grid[new_x][new_y]==ALIVE){
                    alive_cells++;
                }

            }
            if(grid[i][j]==ALIVE){
                if(alive_cells < 2 || alive_cells > 3){
                    nextState[i][j] = DEAD;
                }
                else{
                    nextState[i][j] = ALIVE;
                }
            }
            else{

                if(alive_cells == 3){
                    nextState[i][j] = ALIVE;
                }
                else{
                    nextState[i][j] = DEAD;
                }

            }
        }
    }
    for(int i=0;i<DIM;++i){
        for(int j=0;j<DIM;++j){
            grid[i][j] = nextState[i][j];
        }
    }
}



void mouseLogic(){

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        int X = (int)GetMouseX() / CELL_SIZE;
        int Y = (int)GetMouseY() / CELL_SIZE;
        grid[X][Y] = !grid[X][Y];
    }

}



typedef enum MODE{
    RANDOM,
    MOUSE,
    TITLE
}MODE;


int main()
{

    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Game of Life");
    Font fontTitle = LoadFontEx("./Iosevka/Iosevka-Bold.ttf",32,0,250);
    Font fontDesc = LoadFontEx("./Iosevka/Iosevka-Medium.ttf",32,0,250);
    SetTargetFPS(10);
    bool start = false;
    MODE mode = TITLE;
    bool sceneActive = true;
    double sceneStartTime = 0;
    while (!WindowShouldClose())
    {




        if(mode == TITLE){

            if(IsKeyPressed(KEY_R)){
                mode = RANDOM;
                grid_init_random();

            }
            else if(IsKeyPressed(KEY_M)){
                mode = MOUSE;
            }
            else{
                mode = TITLE;
            }
        }

        if (sceneActive && (mode == RANDOM)) {
            sceneStartTime = GetTime();
            sceneActive = false;
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch(mode){
            case RANDOM:{
                if(GetTime()-sceneStartTime >= 2.0f){

                    draw_grid();
                    logic();
                }
                else{
                    draw_grid();
                }
            }break;
            case MOUSE:{
                mouseLogic();
                if (IsKeyPressed(KEY_ENTER))
                {
                    sleep(1);
                    start = true;
                }
                if(start){

                    draw_grid();
                    logic();
                }
                else{

                    draw_grid();
                }

            }break;
            case TITLE:{
                char *title = "TITLE SCREEN";
                char *desc = "Type R for Random or M for Manual inital condition";
                float fontSize_title = fontTitle.baseSize;
                float spacing_title = 2;
                Vector2 title_calc = MeasureTextEx(fontTitle,title,fontSize_title,spacing_title);
                float fontSize_desc = fontDesc.baseSize;
                float spacing_desc = 2;
                Vector2 desc_calc = MeasureTextEx(fontDesc,desc,fontSize_desc,spacing_desc);

                DrawTextEx(fontTitle,title,(Vector2){ (float)(SCREEN_SIZE - title_calc.x)/2, (float)(SCREEN_SIZE - title_calc.y-200)/2 },fontSize_title,spacing_title, LIME);
                DrawTextEx(fontDesc,desc,(Vector2){ (float)(SCREEN_SIZE - desc_calc.x)/2, (float)(SCREEN_SIZE - desc_calc.y)/2 },fontSize_desc,spacing_desc, RED);
            }break;

            default: break;

        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

