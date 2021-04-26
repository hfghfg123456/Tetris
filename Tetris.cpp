#include <iostream>
#include <SDL.h>
#include <time.h>
#include <SDL_ttf.h>
#include <string>
#include <fstream>
#include <SDL_image.h>
#include <SDL_mixer.h>

using namespace std;

SDL_Window* window = SDL_CreateWindow("1 + 1 = 3!", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 600, 650, SDL_WINDOW_SHOWN);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
TTF_Font* dlx = NULL;
TTF_Font* dlx_30 = NULL;
TTF_Font* dlx_60 = NULL;
TTF_Font* dlx_80 = NULL;

Mix_Chunk* sound_move = NULL;
Mix_Chunk* sound_score = NULL;
Mix_Chunk* drop = NULL;

SDL_Color white = {255,255,255};
SDL_Color red = {255, 0, 0, 255};
SDL_Color cyan = {0, 255, 255, 255};
SDL_Color green = {0, 255, 0, 255};
SDL_Color purple = {255, 0, 255, 255};
SDL_Color orange = {255, 180, 0, 255};
SDL_Color blue = {0, 0, 255, 255};
SDL_Color Yellow = {255, 255, 0, 255};

SDL_Texture* loadIMG(std::string path)
{

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );

    SDL_FreeSurface( loadedSurface );

	return newTexture;
}

SDL_Texture* loadText(TTF_Font* font, std::string text, SDL_Color color)
{
    SDL_Surface* loadedSurface = TTF_RenderText_Solid(font, text.c_str(), color);

    SDL_Texture* newTeture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    SDL_FreeSurface(loadedSurface);

    return newTeture;
}

void game_end_func();
void play_again();
void game_end_func_render();
void play_again_render();

int score = 0;

void score_render();

//////////////------MENU-WHEN-OPEN-GAME-----////////////////////

SDL_Texture* wanna_join_text = NULL;
SDL_Rect wanna_join_rect;

SDL_Texture* yes_text = NULL;
SDL_Rect yes_rect;

SDL_Texture* no_text = NULL;
SDL_Rect no_rect;

//SDL_Surface* highscore = NULL;
//SDL_Texture* highscore_text = NULL;
//SDL_Rect highscore_rect;

//SDL_Surface* back_highscore = NULL;
//SDL_Texture* back_highscore_text = NULL;
//SDL_Rect back_highscore_rect;

//SDL_Surface* render_highscore = NULL;
//SDL_Texture* render_highscore_text = NULL;
//SDL_Rect render_highscore_rect;

SDL_Texture* start_background = NULL;

bool play_game = false;

void close();

SDL_Event e;

bool start = true;
bool running = true;
bool highscore_next = false;

bool mouse_inside = false;

bool playing = false;

int mouse_x, mouse_y;

int score_max;

fstream f;

void menu_start_game()
{

    start_background = loadIMG("start.jpg");

    yes_text = loadText(dlx_30,"PLAY",white);
    yes_rect = {240,320,120,30};

//    highscore = TTF_RenderText_Solid(dlx_30,"Highscore", white);
//    highscore_text = SDL_CreateTextureFromSurface(renderer, highscore);
//    highscore_rect = {180,450,highscore->w,highscore->h};
//
    no_text = loadText(dlx_30,"EXIT",white);
    no_rect = {240,400,120,30};
//
//    back_highscore = TTF_RenderText_Solid(dlx_30,"Back", white);
//    back_highscore_text = SDL_CreateTextureFromSurface(renderer, back_highscore);
//    back_highscore_rect = {250,550,back_highscore->w,back_highscore->h};
//
//    std::string data = std::to_string(score_max);
//    render_highscore = TTF_RenderText_Solid(dlx_60,data.c_str(), white);
//    render_highscore_text = SDL_CreateTextureFromSurface(renderer, render_highscore);
//    render_highscore_rect = {(600-render_highscore->w)/2,225,render_highscore->w,render_highscore->h};



    while (start)
    {
        while (running)
        {
            SDL_RenderClear(renderer);

            SDL_RenderCopy(renderer, start_background, NULL, NULL);
            SDL_RenderCopy(renderer, yes_text, NULL, &yes_rect);
            SDL_RenderCopy(renderer, no_text, NULL, &no_rect);
//            SDL_RenderCopy(renderer, highscore_text, NULL, &highscore_rect);



            while(SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT) {running = false; start = false;};
                    if (e.type == SDL_MOUSEMOTION)
                        {
                            mouse_x, mouse_y;
                            SDL_GetMouseState(&mouse_x, &mouse_y);
                        }

                    if (e.type == SDL_MOUSEBUTTONDOWN)
                        {
                            if (mouse_x >= yes_rect.x && mouse_x <= yes_rect.x + yes_rect.w && mouse_y >= yes_rect.y && mouse_y <= yes_rect.y + yes_rect.h) {playing = true; running = false; start = false;}
                            if (mouse_x >= no_rect.x && mouse_x <= no_rect.x + no_rect.w && mouse_y >= no_rect.y && mouse_y <= no_rect.y + no_rect.h) {running = false; start = false;}
//                            if (mouse_x >= highscore_rect.x && mouse_x <= highscore_rect.x + highscore_rect.w && mouse_y >= highscore_rect.y && mouse_y <= highscore_rect.y + highscore_rect.h)
//                                {running = false; highscore_next = true;}
                        }


                }


        SDL_RenderPresent(renderer);
        }

//        while (highscore_next)
//        {
//            SDL_RenderClear(renderer);
//            SDL_RenderCopy(renderer, back_highscore_text, NULL, &back_highscore_rect);
//            SDL_RenderCopy(renderer, render_highscore_text, NULL, &render_highscore_rect);
//            while(SDL_PollEvent(&e) != 0)
//                {
//                    if (e.type == SDL_QUIT) {highscore_next = false; start = false;};
//                    if (e.type == SDL_MOUSEMOTION)
//                        {
//                            mouse_x, mouse_y;
//                            SDL_GetMouseState(&mouse_x, &mouse_y);
//                        }
//
//                    if (e.type == SDL_MOUSEBUTTONDOWN)
//                        {
//                            if (mouse_x >= back_highscore_rect.x && mouse_x <= back_highscore_rect.x + back_highscore_rect.w && mouse_y >= back_highscore_rect.y && mouse_y <= back_highscore_rect.y + back_highscore_rect.h)
//                                {running = true; highscore_next = false;}
//                        }
//
//
//                }
//            SDL_RenderPresent(renderer);
//        }

    }


}
//------------------------------------------------------------//

/////////////////////-----MAIN--GAME-----///////////////////////
SDL_Rect rect;
SDL_Rect pre_rect;



bool game_over = false;
int n;
int pre_num;

SDL_Texture *back_ground = loadIMG("map.png");

SDL_Texture* highscore_text_in = NULL;
SDL_Rect highscore_in_rect;

SDL_Surface* in_high = NULL;
SDL_Texture* in_high_text = NULL;
SDL_Rect highscore_ingame;

SDL_Texture* score_text = NULL;
SDL_Rect score_rect;

SDL_Surface* surfacemark = NULL;
SDL_Texture* mark = NULL;
SDL_Rect mark_rect;

SDL_Texture* next_pieces = NULL;
SDL_Rect next_pieces_rect;

SDL_Texture* level = NULL;
SDL_Rect level_rect;

SDL_Surface* s_level_class = NULL;
SDL_Texture* level_class = NULL;
SDL_Rect level_class_rect;


std::string class_level = "D";

void colordraw(int& color)
{
    if (color == 0) SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); // light blue
    if (color == 1) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);   // red
    if (color == 2) SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);   // green
    if (color == 3) SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // purple
    if (color == 4) SDL_SetRenderDrawColor(renderer, 255, 180, 0, 255); // orange
    if (color == 5) SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);   // blue
    if (color == 6) SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // yellow
}

void draw(SDL_Rect &rect, int& n)
{
    colordraw(n);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
}



const int M  = 25;
const int N = 11;

int score_bonus;

int field[M][N] = {0};

int figures[7][4] ={
    0,2,4,6, // I
    0,2,3,5, // Z
    1,3,2,4, // S
    1,3,2,5, // T
    0,2,4,5, // L
    1,3,5,4, // J
    0,1,2,3, // O
};

struct point{int x,y;} a[4], b[4], c[4];

int timer = 0;
int delay;
Uint32 starttime = 0;

bool check()
{
    for(int i=0;i<4;i++)
        if (a[i].x<1 || a[i].x >N-1 || a[i].y >M-1) return 0;
        else if (field[a[i].y][a[i].x]) return 0;
    return 1;
}

int dx;
int line = 0;
bool rotate;
bool music_score = false;
bool get_drop_music = false;

void main_game()
{
    while (playing)
        {
            while (play_game) {
                SDL_RenderClear(renderer);
                srand(time(NULL));

                if (score_max < score) {score_max = score;};
                if (score_max <= score) {f.open("highscore.txt"); f<<score; f.close();};

     while(SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                    {
                        playing = false;
                        play_game = false;
//                        for (int i=0;i<M;i++)
//                            for (int j=0;j<N;j++)
//                                field[i][j] = 0;
                    }
                if (e.type == SDL_KEYDOWN)
                {
                    if(e.key.keysym.sym == SDLK_LEFT) {dx = -1;Mix_PlayChannel( -1, sound_move, 0 );};
                    if(e.key.keysym.sym == SDLK_RIGHT) {dx = 1;Mix_PlayChannel( -1, sound_move, 0 );};
                    if(e.key.keysym.sym == SDLK_UP) {rotate = true;};
                    if(e.key.keysym.sym == SDLK_DOWN) delay = 10;
                }

            }


        if (playing) {
            if (!game_over ){
            for (int i=0;i<4;i++)
            {
                c[i].x = figures[pre_num][i] % 2 + 17;
                c[i].y = figures[pre_num][i] / 2 + 19;
            };

            for(int i=0;i<4;i++)
            {
                pre_rect.x = c[i].x * 25;
                pre_rect.y = c[i].y * 25;
                draw(pre_rect,pre_num);
            };};
            for(int i=0;i<4;i++)
        {
            b[i] = a[i];
            a[i].x += dx;
        };
        if (!check()) for (int i=0;i<4;i++) a[i] = b[i];


        if (rotate)
        {
            if (n != 6){point p = a[1]; // centre point of rotation
            for(int i=0;i<4;i++)
            {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }}
            if (!check()) for(int i=0;i<4;i++) a[i] = b[i];
        };

    timer = SDL_GetTicks() - starttime;

    if (timer>delay)
    {
        for(int i=0;i<4;i++)
        {
            b[i] = a[i];
            a[i].y+=1;
         };
         starttime = SDL_GetTicks();
//        timer = SDL_GetTicks() - starttime;
    };


        if (!check())
        {
            for(int i=0;i<4;i++) field[b[i].y][b[i].x] = n+1;

            n = pre_num;
            for (int i=0;i<4;i++)
            {
                a[i].x = figures[n][i] % 2 + 5;
                a[i].y = figures[n][i] / 2 + 1;
            }
            pre_num = rand() % 7;


            get_drop_music = true;
        }



        //-check-game-over-//
        for (int i=0;i<N;i++)
            {if (field[1][i] == 0) {continue;}
            else game_over = true;play_game = false;};
        //-----------------//

        score_bonus = 0;
        int k = M - 1;
        for (int i = M-1 ; i>1; i--)
        {
            int counte = 0;
            for (int j = 1; j<N; j++)
            {
                if (field[i][j]) counte++;
                field[k][j] = field[i][j];

            };
            if (counte < N-1)  k--;
            if (counte == N-1) {score_bonus++; line++;music_score = true;};


        };

        switch (score_bonus)
                {
                    case 1: {score = score + 40; break;}
                    case 2: {score = score + 100;break;}
                    case 3: {score = score + 300;break;}
                    case 4: {score = score + 1200;break;}
                };

        score_render();

        dx = 0; rotate = false;

        if (line<=1) {delay = 700;class_level = "D";}
            else if(line<=2) {delay = 600;class_level = "C";}
            else if(line<=3) {delay = 500;class_level = "B";}
            else if(line<=4) {delay = 400;class_level = "A";}
            else {delay = 300; class_level = "S";}



//        if(!game_over)
            for(int i=0;i<4;i++)
        {
            rect.x = a[i].x * 25;
            rect.y = a[i].y * 25;
            draw(rect,n);
        };

        for(int i =0;i<M;i++)
            for(int j =0;j<N;j++)
            {
                if (field[i][j] == 0) continue;
                rect.x = j*25;
                rect.y = i*25;
                int colornum = field[i][j] - 1;
                draw(rect,colornum);
            };

        if (music_score) {Mix_PlayChannel( -1, sound_score, 0 );};


        if (!music_score && get_drop_music) {Mix_PlayChannel( -1, drop, 0 );};
        get_drop_music = false;
        music_score = false;

        SDL_RenderCopy(renderer, back_ground, NULL, NULL);
        SDL_RenderCopy(renderer, highscore_text_in, NULL, &highscore_in_rect);
        SDL_RenderCopy(renderer, in_high_text, NULL, &highscore_ingame);
        SDL_RenderCopy(renderer, score_text, NULL, &score_rect);
        SDL_RenderCopy(renderer, mark, NULL, &mark_rect);
        SDL_RenderCopy(renderer, level, NULL, &level_rect);
        SDL_RenderCopy(renderer, level_class, NULL, &level_class_rect);
        SDL_RenderCopy(renderer, next_pieces, NULL, &next_pieces_rect);
        SDL_RenderPresent(renderer);
        }

        if (game_over && playing) {game_end_func();play_again();};


        while (game_over && playing)
        {
            SDL_RenderClear(renderer);
            if (score_max <= score) {f.open("highscore.txt"); f<<score; f.close();};
            game_end_func_render();
            play_again_render();
            SDL_RenderPresent(renderer);
        }

    }
}}
//---------------------------------------------------//



//////////////-----RENDER--SCORE-----//////////////////

void score_render()
{
    highscore_text_in = loadText(dlx,"highscore",white);
    highscore_in_rect = {353,25,200,25};

    std::string max_in = std::to_string(score_max);
    in_high = TTF_RenderText_Solid(dlx, max_in.c_str(), white);
    in_high_text = SDL_CreateTextureFromSurface(renderer, in_high);
    highscore_ingame = {550-in_high->w,75,in_high->w,in_high->h};

    score_text = loadText(dlx,"score",white);
    score_rect = {390,150,125,25};

    std::string s = std::to_string(score);
    surfacemark = TTF_RenderText_Solid(dlx,s.c_str(), white);
    mark = SDL_CreateTextureFromSurface(renderer, surfacemark);
    mark_rect = {550-surfacemark->w,200,surfacemark->w,surfacemark->h};

    level = loadText(dlx,"level",white);
    level_rect = {390,275,125,25};

    s_level_class = TTF_RenderText_Solid(dlx,class_level.c_str(),white);
    level_class = SDL_CreateTextureFromSurface(renderer, s_level_class);
    level_class_rect = {525,325,s_level_class->w,s_level_class->h};

    next_pieces = loadText(dlx,"next",white);
    next_pieces_rect = {407,400,100,25};


}

//---------------------------------------------------//



//////////////-----GAME--OVER-----////////////////////
SDL_Surface* g_end_1 = NULL;
SDL_Texture* g_end_text_1 = NULL;
SDL_Rect g_end_rect_1;

SDL_Surface* a_end_1 = NULL;
SDL_Texture* a_end_text_1 = NULL;
SDL_Rect a_end_rect_1;

SDL_Surface* m_end_1 = NULL;
SDL_Texture* m_end_text_1 = NULL;
SDL_Rect m_end_rect_1;

SDL_Surface* e_end_1 = NULL;
SDL_Texture* e_end_text_1 = NULL;
SDL_Rect e_end_rect_1;

SDL_Surface* o_end_2 = NULL;
SDL_Texture* o_end_text_2 = NULL;
SDL_Rect o_end_rect_2;

SDL_Surface* v_end_2 = NULL;
SDL_Texture* v_end_text_2 = NULL;
SDL_Rect v_end_rect_2;

SDL_Surface* e_end_2 = NULL;
SDL_Texture* e_end_text_2 = NULL;
SDL_Rect e_end_rect_2;

SDL_Surface* r_end_2 = NULL;
SDL_Texture* r_end_text_2 = NULL;
SDL_Rect r_end_rect_2;

SDL_Surface* s_text = NULL;
SDL_Texture* text = NULL;
SDL_Rect text_rect;

SDL_Surface* s_render_score_end = NULL;
SDL_Texture* render_score_end = NULL;
SDL_Rect mark_end_rect;

void game_end_func()
{
    g_end_1 = TTF_RenderText_Solid(dlx_60, "G", red);
    a_end_1 = TTF_RenderText_Solid(dlx_60, "a", cyan);
    m_end_1 = TTF_RenderText_Solid(dlx_60, "m", purple);
    e_end_1 = TTF_RenderText_Solid(dlx_60, "e", orange);

    g_end_text_1 = SDL_CreateTextureFromSurface(renderer,g_end_1);
    a_end_text_1 = SDL_CreateTextureFromSurface(renderer,a_end_1);
    m_end_text_1 = SDL_CreateTextureFromSurface(renderer,m_end_1);
    e_end_text_1 = SDL_CreateTextureFromSurface(renderer,e_end_1);

    g_end_rect_1 = {200,110,g_end_1->w,g_end_1->h};
    a_end_rect_1 = {260,110,a_end_1->w,a_end_1->h};
    m_end_rect_1 = {320,110,m_end_1->w,m_end_1->h};
    e_end_rect_1 = {380,110,e_end_1->w,e_end_1->h};

    o_end_2 = TTF_RenderText_Solid(dlx_60,"O",orange);
    v_end_2 = TTF_RenderText_Solid(dlx_60,"v",Yellow);
    e_end_2 = TTF_RenderText_Solid(dlx_60,"e",green);
    r_end_2 = TTF_RenderText_Solid(dlx_60,"r",red);

    o_end_text_2 = SDL_CreateTextureFromSurface(renderer,o_end_2);
    v_end_text_2 = SDL_CreateTextureFromSurface(renderer,v_end_2);
    e_end_text_2 = SDL_CreateTextureFromSurface(renderer,e_end_2);
    r_end_text_2 = SDL_CreateTextureFromSurface(renderer,r_end_2);

    o_end_rect_2 = {200,170,o_end_2->w,o_end_2->h};
    v_end_rect_2 = {260,170,v_end_2->w,v_end_2->h};
    e_end_rect_2 = {320,170,e_end_2->w,e_end_2->h};
    r_end_rect_2 = {380,170,r_end_2->w,r_end_2->h};

    s_text = TTF_RenderText_Solid(dlx_30, "Your score", red);
    text = SDL_CreateTextureFromSurface(renderer,s_text);
    text_rect = {160,300,s_text->w,s_text->h};

    std::string a = std::to_string(score);
    s_render_score_end = TTF_RenderText_Solid(dlx_30,a.c_str(),white);
    render_score_end = SDL_CreateTextureFromSurface(renderer, s_render_score_end);
    mark_end_rect = {(600-s_render_score_end->w)/2,360,s_render_score_end->w,s_render_score_end->h};
}

void game_end_func_render()
{
            SDL_RenderCopy(renderer,g_end_text_1,NULL,&g_end_rect_1);
            SDL_RenderCopy(renderer,a_end_text_1,NULL,&a_end_rect_1);
            SDL_RenderCopy(renderer,m_end_text_1,NULL,&m_end_rect_1);
            SDL_RenderCopy(renderer,e_end_text_1,NULL,&e_end_rect_1);
            SDL_RenderCopy(renderer,o_end_text_2,NULL,&o_end_rect_2);
            SDL_RenderCopy(renderer,v_end_text_2,NULL,&v_end_rect_2);
            SDL_RenderCopy(renderer,e_end_text_2,NULL,&e_end_rect_2);
            SDL_RenderCopy(renderer,r_end_text_2,NULL,&r_end_rect_2);

            SDL_RenderCopy(renderer, render_score_end, NULL, &mark_end_rect);
            SDL_RenderCopy(renderer, text, NULL, &text_rect);
}
//---------------------------------------------------//


///////////////----PLAY--AGAIN----/////////////////////
SDL_Texture* press_space = NULL;
SDL_Rect press_space_rect;

void play_again()
{
    press_space = loadText(dlx,"Press SPACE to play again",white);
    press_space_rect = {10,500,590,25};
}

void play_again_render()
{
    SDL_RenderCopy(renderer, press_space, NULL, &press_space_rect);
    while(SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT) {game_over = false; playing = false;}
                if (e.type == SDL_KEYDOWN)
                {
                    if(e.key.keysym.sym == SDLK_SPACE)
                        {
                            score = 0; line = 0;
                            game_over = false; play_game = true;
                            for (int i=0;i<M;i++)
                                for (int j=0;j<N;j++)
                                    field[i][j] = 0;
                        }
                }
            }
}



//---------------------------------------------------//


void close()
{
    renderer = NULL;
    window = NULL;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

}

int main(int argc, char* argv[])
{
    TTF_Init();

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        cout<<"SDL_mixer could not initialize! SDL_mixer Error: %s\n"<< Mix_GetError();
    };

    sound_move = Mix_LoadWAV( "move_sound.wav" );
    sound_score = Mix_LoadWAV( "score_reach.wav" );
    drop = Mix_LoadWAV("drop.wav");

    dlx = TTF_OpenFont("dlxfont.ttf", 23);
    dlx_30 = TTF_OpenFont("dlxfont.ttf", 30);
    dlx_60 = TTF_OpenFont("dlxfont.ttf", 60);
    dlx_80 = TTF_OpenFont("dlxfont.ttf", 80);


    f.open("highscore.txt");
    f>>score_max;
    f.close();


    rect = {0,0,25,25};
    pre_rect = {0,0,25,25};

    play_game = true;

        srand(time(NULL));
        n = rand() % 7;
        pre_num = rand() % 7;
        for (int i=0;i<4;i++)
        {
            a[i].x = figures[n][i] % 2 + 5;
            a[i].y = figures[n][i] / 2;
        };

        menu_start_game();


        main_game();



    close();
    return 0;



}

