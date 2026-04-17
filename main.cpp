    #include <stdio.h>
    #include <SDL2/SDL.h>
    #include <conio.h>
    #define mapx 20
    #define mapy 12
    struct ogcat
    {
        SDL_Texture* texture=nullptr;
        SDL_Surface* catload=nullptr;
        int x,y,w,h;
        int newx,newy;
        SDL_Rect pos{x,y,w,h};
        int vecx, vecy;
        int isstanding;
    };
    struct map
    {
        SDL_Texture* dirttexture=nullptr;
        SDL_Surface* dirtload=nullptr;
        SDL_Texture* dirt_undertexture=nullptr;
        SDL_Surface* dirt_underload=nullptr;
        int maptab[mapy][mapx]={ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1},
                                 {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},


                                };
    };
    struct background
    {
        SDL_Texture* texture=nullptr;
        SDL_Surface* load=nullptr;
    };
    void backgroundloader(background *bg, SDL_Renderer *renderer) {
        bg->load=SDL_LoadBMP("assets/map/background.bmp");
        bg->texture = SDL_CreateTextureFromSurface(renderer, bg->load);

    }
    void backgrounddraw(background *bg, SDL_Renderer *renderer) {
        SDL_Rect pos{0,0,2000,1200};
        SDL_RenderCopy(renderer, bg->texture, NULL, &pos);
    }
    void maploader(map *map, SDL_Renderer *renderer) {
        map->dirtload=SDL_LoadBMP("assets/map/dirt.bmp");
        map->dirttexture = SDL_CreateTextureFromSurface(renderer, map->dirtload);
        map->dirt_underload=SDL_LoadBMP("assets/map/dirt_under.bmp");
        map->dirt_undertexture = SDL_CreateTextureFromSurface(renderer, map->dirt_underload);

    }
    void drawmap(map *map, SDL_Renderer *renderer) {
                for(int i=0;i<mapy;i++){
                    for(int j=0;j<mapx;j++){
                           if(map->maptab[i][j]==1){
                                SDL_Rect pos{j*100,i*100,100,100};
                                SDL_RenderCopy(renderer, map->dirttexture, NULL, &pos);
                           } 
                            if(map->maptab[i][j]==2){
                                  SDL_Rect pos{j*100,i*100,100,100};
                                  SDL_RenderCopy(renderer, map->dirt_undertexture, NULL, &pos);
                            }
                    }
                }
                


    }
   
    
    void catloader(ogcat *cat, SDL_Renderer *renderer) {
        SDL_Surface *catload = SDL_LoadBMP("assets/cat/ogcat.bmp");
        Uint32 colorkey = SDL_MapRGB(catload->format, 0, 255, 0);
        SDL_SetColorKey(catload, SDL_TRUE, colorkey);
        cat->catload = catload;
        cat->texture = SDL_CreateTextureFromSurface(renderer, cat->catload);
        cat->x = 100;
        cat->y = 100;

        cat->w = 200;
        cat->h = 200;
        cat->vecx = 0;
        cat->vecy = 0;
        cat->pos = {cat->x, cat->y, cat->w, cat->h}; 
        cat->isstanding = 0;

    }
    void drawcat(ogcat *cat, SDL_Renderer *renderer) {
        SDL_RenderCopy(renderer, cat->texture, NULL, &cat->pos);
    }
    void destroyer(ogcat *cat,map *map, background *bg) {
        SDL_DestroyTexture(cat->texture);
        SDL_FreeSurface(cat->catload);
        SDL_FreeSurface(map->dirtload);
        SDL_DestroyTexture(map->dirttexture);
        SDL_DestroyTexture(bg->texture);
        SDL_FreeSurface(bg->load);
        SDL_FreeSurface(map->dirt_underload);
        SDL_DestroyTexture(map->dirt_undertexture);

    }

    bool catcollision_down(ogcat *cat,map *map) {
        
        if(map->maptab[((cat->y+cat->h)/100)][(cat->x-42)/100]==1 || map->maptab[((cat->y+cat->h)/100)][((cat->x-42)+cat->w)/100]==1){
            return true;
        }else return false;
        
             
        
    }
    bool catcollision_left(ogcat *cat,map *map){
        if(map->maptab[((cat->y)/100)][(cat->x)/100]==1 || map->maptab[((cat->y+cat->h)/100)][((cat->x))/100]==1){
            return true;
        }else return false;
    }
    
    void gravity(ogcat *cat,map *map) {
        if(!catcollision_down(cat,map))
        {
         cat->vecy += 1;
        }else{
            //fix?
             cat->vecy = 0;
             
        }
    }
    void catjump(ogcat *cat,map *map) {
        if(catcollision_down(cat,map)){
        cat->vecy = -30;
        }

    }
    void catmover(ogcat *cat,map *map) {
        gravity(cat,map);
        const Uint8* keyboard = SDL_GetKeyboardState(NULL);
        if (keyboard[SDL_SCANCODE_SPACE]) {
            catjump(cat,map);
            
        }
        if (keyboard[SDL_SCANCODE_A]) {
           // if(!catcollision_left(cat,map))
            cat->x -= 10;
        }
        if (keyboard[SDL_SCANCODE_D]) {
            cat->x += 10;
        }

        cat->x += cat->vecx;
        cat->y += cat->vecy;
        cat->pos = {cat->x, cat->y, cat->w, cat->h};
    }
    int main(int argv, char **args) {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Window *window = SDL_CreateWindow("SDL2 okno", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 2000,1200,0);
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
        ogcat cat;
        map map;
        background bg;
        catloader(&cat,renderer);
        maploader(&map,renderer);
        backgroundloader(&bg,renderer);

        SDL_Event e;
    while (true)
    {
        while (SDL_PollEvent(&e))
        {
            
            if (e.type == SDL_QUIT)
                return 0;
                
        }
        SDL_RenderClear(renderer);
        catmover(&cat,&map);
        
        backgrounddraw(&bg,renderer);
        drawcat(&cat, renderer);
        drawmap(&map, renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(30);
    }
        SDL_DestroyWindow(window);
        destroyer(&cat,&map,&bg);

        SDL_Quit();
        return 1;
    }