// soccer.c
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>

#define WIN_W 1200
#define WIN_H 1000

#define cols_start 198
#define cols_end 998
#define rows_start 198
#define rows_end 798
#define step 100
#define point_size 4

int graph[9][13] = {0};
int crow = 4;
int ccol = 6;
int orig, dest;



void fillGraph(){

    crow = 4;
    ccol = 6;

    for (int i=0;i<9;i++){
        for(int j = 0;j<13;j++){
            graph[i][j]=0;
        }
    }

    for (int i =0; i<9; i++){
        if (i==4){
            continue;
        }
        graph[i][0]=-1;
        graph[i][12]=-1;
    }

    graph[0][1]=1385670;
    graph[8][1]=3233230;
    graph[0][11]=746130;
    graph[8][11]=510510;

    for (int i =1; i<8; i++){
        if (i==4){
            continue;
        }
        if (i ==3){
            graph[i][1]=646;
            graph[i][11]=30;
            continue;
        }
        if (i ==5){
            graph[i][1]=2431;
            graph[i][11]=385;
            continue;
        }
        graph[i][1]=92378;
        graph[i][11]=2310;
    }

    for (int i =2; i<11; i++){
        graph[0][i]=9690;
        graph[8][i]=85085;
    }

    graph[4][6] = 1;

}

void drawPoints(SDL_Renderer *ren){
    SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 255);

    SDL_Rect r;

    r.x = 100; r.y = 95;  r.w = 1000; r.h = 5;   
    SDL_RenderFillRect(ren, &r);

    r.x = 100; r.y = 900; r.w = 1000; r.h = 5;  
    SDL_RenderFillRect(ren, &r);

    r.x = 95;  r.y = 95;  r.w = 5;    r.h = 305; 
    SDL_RenderFillRect(ren, &r);

    r.x = 1100; r.y = 95; r.w = 5;    r.h = 305; 
    SDL_RenderFillRect(ren, &r);

    r.x = 95;  r.y = 600; r.w = 5;    r.h = 305; 
    SDL_RenderFillRect(ren, &r);

    r.x = 1100; r.y = 600; r.w = 5;    r.h = 305; 
    SDL_RenderFillRect(ren, &r);

    r.x = 0;   r.y = 395; r.w = 95;   r.h = 5;   
    SDL_RenderFillRect(ren, &r);

    r.x = 0;   r.y = 600; r.w = 95;   r.h = 5;   
    SDL_RenderFillRect(ren, &r);

    r.x = 1105; r.y = 395; r.w = 95;  r.h = 5;   
    SDL_RenderFillRect(ren, &r);

    r.x = 1105; r.y = 600; r.w = 95;  r.h = 5;   
    SDL_RenderFillRect(ren, &r);

    r.x = 1195; r.y = 400; r.w = 5;   r.h = 200; 
    SDL_RenderFillRect(ren, &r);

    r.x = 0;    r.y = 400; r.w = 5;   r.h = 200;  
    SDL_RenderFillRect(ren, &r);

    SDL_Rect p;
    p.w = point_size; p.h = point_size;
    for (int x = cols_start; x <= cols_end; x += step) {
        for (int y = rows_start; y <= rows_end; y += step) {
            p.x = x; p.y = y;
            SDL_RenderFillRect(ren, &p);
        }
    }

    //SDL_RenderDrawLine(ren, 1098, 498, 98, 498);

    p.x = 1098; p.y = 498; SDL_RenderFillRect(ren, &p);
    p.x = 98;   p.y = 498; SDL_RenderFillRect(ren, &p);
}

void drawLine(SDL_Renderer *ren){
    int px, py;
    for (int row = 0; row<=7;row++){
        py = 100+(100*row);
        for (int col=1;col<=11;col++){
            px = 100*col;
            if ((graph[row][col+1] != 0) && (graph[row][col+1] % 17 == 0)) {
                SDL_RenderDrawLine(ren, px, py, px+100, py);
            }
            if ((graph[row+1][col+1] != 0) && (graph[row+1][col+1] % 19 == 0)) {
                SDL_RenderDrawLine(ren, px, py, px+100, py+100);
            }
            if ((graph[row+1][col] != 0) && (graph[row+1][col] % 2 == 0)) {
                SDL_RenderDrawLine(ren, px, py, px, py+100);
            }
            if ((graph[row+1][col-1] != 0) && (graph[row+1][col-1] % 3 == 0)) {
                SDL_RenderDrawLine(ren, px, py, px-100, py+100);
            }
        }
    }
    if (graph[4][0] % 5 == 0 && graph[4][0] != 0){
        SDL_RenderDrawLine(ren, 0, 500, 100, 500);
    }
    if (graph[4][0] % 7 == 0 && graph[4][0] != 0){
        SDL_RenderDrawLine(ren, 0, 500, 100, 600);
    }
    if (graph[4][12] % 13 == 0 && graph[4][12] != 0){
        SDL_RenderDrawLine(ren, 1200, 500, 1100, 600);
    }
}

void drawPlayer(SDL_Renderer *ren, bool player1, SDL_Texture* playerScore[]){   
    if (player1){
        SDL_Rect rect = {50,20,200,70};
        SDL_RenderCopy(ren,playerScore[0],NULL,&rect);
        rect = (SDL_Rect) {950,20,200,70};
        SDL_RenderCopy(ren,playerScore[3],NULL,&rect);
    } else {
        SDL_Rect rect = {50,20,200,70};
        SDL_RenderCopy(ren,playerScore[1],NULL,&rect);
        rect = (SDL_Rect) {950,20,200,70};
        SDL_RenderCopy(ren,playerScore[2],NULL,&rect);
    }
}

void drawScore(SDL_Renderer *ren, char* arr,TTF_Font* fnt1){
    
    char tempStr1[2] = {arr[0], '\0'}; 
    SDL_Color clr = {0xFF,0xFF,0xFF,0xFF};
    SDL_Surface* sfc = TTF_RenderText_Blended(fnt1,tempStr1,clr);
    assert(sfc != NULL);
    SDL_Texture* txt = SDL_CreateTextureFromSurface(ren, sfc);
    assert(txt != NULL);

    SDL_Rect rect = {270,20,70,70};
    SDL_RenderCopy(ren,txt,NULL,&rect);

    char tempStr2[2] = {arr[1], '\0'};
    sfc = TTF_RenderText_Blended(fnt1,tempStr2,clr);
    assert(sfc != NULL);
    txt = SDL_CreateTextureFromSurface(ren, sfc);
    assert(txt != NULL);

    rect = (SDL_Rect) {880,20,70,70};
    SDL_RenderCopy(ren,txt,NULL,&rect);

    SDL_FreeSurface(sfc);
    SDL_DestroyTexture(txt);
}

int main(int argc, char **argv) {

    SDL_Texture* playerScore[4];

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Soccer",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WIN_W, WIN_H,
                                       SDL_WINDOW_OPENGL);
    if (!win) {
        fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1,
                                           SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren) {
        fprintf(stderr, "SDL_CreateRenderer error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    TTF_Init();
    TTF_Font* fnt1 = TTF_OpenFont("tiny.ttf", 20);
    assert(fnt1 != NULL);
    TTF_Font* fnt2 = TTF_OpenFont("tiny.ttf", 30);
    assert(fnt2 != NULL);

    SDL_Color clr = {0xFF,0x00,0x00,0xFF};
    SDL_Surface* sfc = TTF_RenderText_Blended(fnt2,"Player 1",clr);
    assert(sfc != NULL);
    playerScore[0] = SDL_CreateTextureFromSurface(ren, sfc);
    assert(playerScore[0] != NULL);
    
    clr = (SDL_Color) {0x77,0x77,0x77,0xFF};
    sfc = TTF_RenderText_Blended(fnt1,"Player 1",clr);
    assert(sfc != NULL);
    playerScore[1] = SDL_CreateTextureFromSurface(ren, sfc);
    assert(playerScore[1] != NULL);

    clr = (SDL_Color) {0x00,0x00,0xFF,0xFF};
    sfc = TTF_RenderText_Blended(fnt1,"Player 2",clr);
    assert(sfc != NULL);
    playerScore[2] = SDL_CreateTextureFromSurface(ren, sfc);
    assert(playerScore[2] != NULL);

    clr = (SDL_Color) {0x77,0x77,0x77,0xFF};
    sfc = TTF_RenderText_Blended(fnt1,"Player 2",clr);
    assert(sfc != NULL);
    playerScore[3] = SDL_CreateTextureFromSurface(ren, sfc);
    assert(playerScore[3] != NULL);
    
    SDL_FreeSurface(sfc);

    clr = (SDL_Color) {0x00,0x00,0x00,0x00};

    char score[2] = {48,48};
    bool player1 = true;

    bool running = true;
    bool game = true;
    SDL_Event e;

    SDL_Rect pitch = {100, 100, 1000, 800};
    SDL_Rect left_goal_area = {5, 400, 100, 200};
    SDL_Rect right_goal_area = {1100, 400, 95, 200};

     
    printf("start\n");

    
    while (running){

        fillGraph();

        for (int r = 0; r < 9; r++) {
            printf("%2d|", r);
            for (int c = 0; c < 13; c++) {
                printf("%d ",graph[r][c]);
            }
            printf("\n");
        }

        while (game) {
            // events
            while (SDL_WaitEventTimeout(&e,5)) {
                if (e.type == SDL_QUIT) running = game = false;
                if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        orig = 2;
                        dest = 11;
                        if ((crow == 0)){
                            continue;
                        }
                        if (graph[crow-1][ccol] == -1){
                            continue;
                        }
                        if (graph[crow-1][ccol] == 0){
                            graph[crow][ccol] *= orig;
                            graph[crow-1][ccol] = dest;
                            crow--;
                            player1 = !player1;
                            continue;
                        }
                        if (graph[crow-1][ccol]%dest == 0){
                            continue;
                        }
                        else{
                            graph[crow][ccol] *= orig;
                            graph[crow-1][ccol] *= dest;
                            crow--;
                        }
                        break;
                    case SDLK_DOWN:
                        orig = 11;
                        dest = 2;
                        if ((crow == 8)){
                            continue;
                        }
                        if (graph[crow+1][ccol] == -1){
                            continue;
                        }
                        if (graph[crow+1][ccol] == 0){
                            graph[crow][ccol] *= orig;
                            graph[crow+1][ccol] = dest;
                            crow++;
                            player1 = !player1;
                            continue;
                        }
                        if (graph[crow+1][ccol]%dest == 0){
                            continue;
                        }
                        else{
                            graph[crow][ccol] *= orig;
                            graph[crow+1][ccol] *= dest;
                            crow++;
                        }
                        break;
                    case SDLK_LEFT:
                        orig = 17;
                        dest = 5;
                        if (graph[crow][ccol-1] == -1){
                            continue;
                        }
                        if (graph[crow][ccol-1] == 0){
                            graph[crow][ccol] *= orig;
                            graph[crow][ccol-1] = dest;
                            ccol--;
                            player1 = !player1;
                            continue;
                        }
                        if (graph[crow][ccol-1]%dest == 0){
                            continue;
                        }
                        else{
                            graph[crow][ccol] *= orig;
                            graph[crow][ccol-1] *= dest;
                            ccol--;
                        }
                        break;
                    case SDLK_RIGHT:
                        orig = 5;
                        dest = 17;
                        if (graph[crow][ccol+1] == -1){
                            continue;
                        }
                        if (graph[crow][ccol+1] == 0){
                            graph[crow][ccol] *= orig;
                            graph[crow][ccol+1] = dest;
                            ccol++;
                            player1 = !player1;
                            continue;
                        }
                        if (graph[crow][ccol+1]%dest == 0){
                            continue;
                        }
                        else{
                            graph[crow][ccol] *= orig;
                            graph[crow][ccol+1] *= dest;
                            ccol++;
                        }
                        break;
                    case SDLK_q:
                        orig = 19;
                        dest = 7;
                        if ((crow == 0)){
                            continue;
                        }
                        if (graph[crow-1][ccol-1] == -1){
                            continue;
                        }
                        if (graph[crow-1][ccol-1] == 0){
                            graph[crow][ccol] *= orig;
                            graph[crow-1][ccol-1] = dest;
                            crow--;
                            ccol--;
                            player1 = !player1;
                            continue;
                        }
                        if (graph[crow-1][ccol-1]%dest == 0){
                            continue;
                        }
                        else{
                            graph[crow][ccol] *= orig;
                            graph[crow-1][ccol-1] *= dest;
                            crow--;
                            ccol--;
                        }
                        break;
                    case SDLK_w:
                        orig = 3;
                        dest = 13;
                        if ((crow == 0)){
                            continue;
                        }
                        if (graph[crow-1][ccol+1] == -1){
                            continue;
                        }
                        if (graph[crow-1][ccol+1] == 0){
                            graph[crow][ccol] *= orig;
                            graph[crow-1][ccol+1] = dest;
                            crow--;
                            ccol++;
                            player1 = !player1;
                            continue;
                        }
                        if (graph[crow-1][ccol+1]%dest == 0){
                            continue;
                        }
                        else{
                            graph[crow][ccol] *= orig;
                            graph[crow-1][ccol+1] *= dest;
                            crow--;
                            ccol++;
                        }
                        break;
                    case SDLK_a:
                        orig = 13;
                        dest = 3;
                        if ((crow==8)){
                            continue;
                        }
                        if (graph[crow+1][ccol-1] == -1){
                            continue;
                        }
                        if (graph[crow+1][ccol-1] == 0){
                            graph[crow][ccol] *= orig;
                            graph[crow+1][ccol-1] = dest;
                            crow++;
                            ccol--;
                            player1 = !player1;
                            continue;
                        }
                        if (graph[crow+1][ccol-1]%dest == 0){
                            continue;
                        }
                        else{
                            graph[crow][ccol] *= orig;
                            graph[crow+1][ccol-1] *= dest;
                            crow++;
                            ccol--;
                        }
                        break;
                    case SDLK_s:
                        orig = 7;
                        dest = 19;
                        if ((crow == 8)){
                            continue;
                        }
                        if (graph[crow+1][ccol+1] == -1){
                            continue;
                        }
                        if (graph[crow+1][ccol+1] == 0){
                            graph[crow][ccol] *= orig;
                            graph[crow+1][ccol+1] = dest;
                            crow++;
                            ccol++;
                            player1 = !player1;
                            continue;
                        }
                        if (graph[crow+1][ccol+1]%dest == 0){
                            continue;
                        }
                        else{
                            graph[crow][ccol] *= orig;
                            graph[crow+1][ccol+1] *= dest;
                            crow++;
                            ccol++;
                        }
                        break;
                    }
                }
            }

            SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
            SDL_RenderClear(ren);

            SDL_SetRenderDrawColor(ren, 0x00, 0x88, 0x00, 255);
            SDL_RenderFillRect(ren, &pitch);
            SDL_RenderFillRect(ren, &left_goal_area);
            SDL_RenderFillRect(ren, &right_goal_area);

            drawPoints(ren);
            drawLine(ren);
            drawPlayer(ren,player1,playerScore);
            drawScore(ren,score,fnt1);

            SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 255);
            

            SDL_RenderPresent(ren);

            SDL_Delay(16);

            if (ccol == 0 || ccol == 12) {
                game = false;
                if (ccol == 0){
                    score[1]++;
                    player1 = true;
                    continue;
                } else {
                    score[0]++;
                    player1 = false;
                    continue;
                }
            }

            if (graph[crow][ccol] == 9699690){
                game = false;
                if (player1){
                    score[1]++;
                    player1 = true;
                    continue;
                } else{
                    score[0]++;
                    player1 = false;
                    continue;
                }
            }

            if (score[0] == 57 || score[1] == 57){
                game = running = false;
            }
        
        }

        if (running){
            while(!(game)){
                while (SDL_WaitEventTimeout(&e,15)){
                    if (e.type == SDL_QUIT) {
                        running = false;
                        game = true;
                    }
                    if (e.type == SDL_KEYDOWN){
                        if (e.key.keysym.sym == SDLK_SPACE){
                            game = true;
                        }
                    }
                }
            
                SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
                SDL_RenderClear(ren);

                SDL_SetRenderDrawColor(ren, 0x00, 0x88, 0x00, 255);
                SDL_RenderFillRect(ren, &pitch);
                SDL_RenderFillRect(ren, &left_goal_area);
                SDL_RenderFillRect(ren, &right_goal_area);

                drawPoints(ren);
                drawLine(ren);
            
                drawPlayer(ren,player1,playerScore);
                drawScore(ren,score,fnt1);

                SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 255);
            

                SDL_RenderPresent(ren);

                SDL_Delay(16);
                

            }
        }

    }

    for (int i = 0; i < 4; i++) {
        if (playerScore[i] != NULL) {
            SDL_DestroyTexture(playerScore[i]);
            playerScore[i] = NULL;
        }
    }

    TTF_CloseFont(fnt1);
    TTF_CloseFont(fnt2);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
    return 0;
    
}
