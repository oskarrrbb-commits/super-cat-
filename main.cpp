    #include <stdio.h>
    #include <SDL2/SDL.h>
    #include <conio.h>
    #define mapx 20
    #define mapy 12
    #define rooms 4
    struct ogcat
    {
        SDL_Texture* texture=nullptr;
        SDL_Surface* catload=nullptr;
        int x,y,w,h;
        int newx,newy;
        SDL_Rect pos{x,y,w,h};
        int vecx, vecy;
        int isstanding;
        int jump_possible=1;
        int time_lastjump=0;
        int lifes=3;

    };
    struct frog
    {
        SDL_Texture* frogtexture=nullptr;
        SDL_Surface* frogload=nullptr;
        int x,y,w=100,h=100;
        SDL_Rect pos{x,y,w,h};
        int vecx=0, vecy=0;
        int ogy=0;
        bool active=false;
        bool jump=true;
        int jumptick=0;


    };
    struct map
    {
        SDL_Texture* dirttexture=nullptr;
        SDL_Surface* dirtload=nullptr;
        SDL_Texture* dirt_undertexture=nullptr;
        SDL_Surface* dirt_underload=nullptr;
        SDL_Texture* spikestexture=nullptr;
        SDL_Surface* spikesload=nullptr;
        int maptab[rooms][mapy][mapx]={{
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                 {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1},
                                 {0,0,0,0,0,0,1,1,1,2,1,3,3,3,3,3,2,0,0,1},
                                 {1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,2,1,1,1},
                                 {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
                                 },
                                 {
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                 {0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,4,0,0,0,1},
                                 {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1},
                                 {1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1},
                                 {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
                                },
                                {
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                 {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1},
                                 {0,0,0,0,0,0,1,1,1,2,1,3,3,3,3,3,2,0,0,1},
                                 {1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,2,1,1,1},
                                 {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
                                 },
                                 {
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                 {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1},
                                 {0,0,0,0,0,0,1,1,1,2,1,3,3,3,3,3,2,0,0,1},
                                 {1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,2,1,1,1},
                                 {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
                                 }


                                };

        int activeroom=0;
        bool roomswitch=false;
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

        map->spikesload=SDL_LoadBMP("assets/map/spikes.bmp");
        Uint32 colorkey = SDL_MapRGB(map->spikesload->format, 0, 255, 0);
        SDL_SetColorKey(map->spikesload, SDL_TRUE, colorkey);
        map->spikestexture = SDL_CreateTextureFromSurface(renderer, map->spikesload);

       
    }
    void frogloader(frog *frog, SDL_Renderer *renderer) {
        frog->frogload=SDL_LoadBMP("assets/frog/frog.bmp");
        Uint32 colorkey = SDL_MapRGB(frog->frogload->format, 0, 255, 0);
        SDL_SetColorKey(frog->frogload, SDL_TRUE, colorkey);
        frog->frogtexture = SDL_CreateTextureFromSurface(renderer, frog->frogload);

    }


        void swaproom(map *map,ogcat *cat){
        if(cat->x+cat->w>=2000){
            map->activeroom++;
            cat->x=0;
        }
        if(cat->x<0){
            map->activeroom--;
            cat->x=1750;
        }
    }

        bool catcollision_down(ogcat *cat,map *map) {
        
        if(map->maptab[map->activeroom][((cat->y+cat->h)/100)][(cat->x+57)/100]==1 || map->maptab[map->activeroom][((cat->y+cat->h)/100)][((cat->x-57)+cat->w)/100]==1){
            return true;
        }else return false;
        
             
        
    }
    bool catcollision_left(ogcat *cat,map *map){
        if(map->maptab[map->activeroom][((cat->y+((cat->h)/2))/100)][(cat->x+57)/100]==1|| map->maptab[map->activeroom][((cat->y+((cat->h)/2))/100)][(cat->x+57)/100]==2){
            return true;
        }else return false;
    }
    bool catcollision_right(ogcat *cat,map *map){
        if(map->maptab[map->activeroom][((cat->y+((cat->h)/2))/100)][(cat->x+cat->w-57)/100]==1||map->maptab[map->activeroom][((cat->y+((cat->h)/2))/100)][(cat->x+cat->w-57)/100]==2 ){
            return true;
        }else return false;
    }
    bool catcollison_up(ogcat *cat,map*map){
        if(map->maptab[map->activeroom][((cat->y+50)/100)][(cat->x+57)/100]==1 || map->maptab[map->activeroom][((cat->y+50)/100)][((cat->x-57)+cat->w)/100]==1){
            return true;
        }else return false;
        
    }
    void frogdrawnew(frog *frog, SDL_Renderer *renderer,map *map,ogcat *cat){ 
        
                for(int i=0;i<mapy;i++){
                    for(int j=0;j<mapx;j++){
                           
                            if(map->maptab[map->activeroom][i][j]==4){
                                if(frog->active){
                                    return;
                                }
                                frog->x=j*100;
                                frog->y=i*100;
                                frog->ogy=frog->y;
                                frog->w=100;
                                frog->h=100;
                                frog->pos = {frog->x, frog->y, frog->w, frog->h};
                                frog->active=true;
                                return;
                            }                               
                            
                    }
                }
        frog->active=false;
    }
    
    void frogdraw(frog *frog, SDL_Renderer *renderer) {
        if(frog->active){
        if(frog->jumptick<30){
            frog->y-=10;
        }else{
             if(frog->jumptick<60){
            frog->y+=10;
        
        }else{
            if(frog->jumptick>100)
            frog->jumptick=0;
            frog->y=frog->ogy;
            
        }
        }
        frog->jumptick++;

            frog->pos = {frog->x, frog->y, frog->w, frog->h};
            SDL_RenderCopy(renderer, frog->frogtexture, NULL, &frog->pos);


        
    }
    }
    void drawmap(map *map, SDL_Renderer *renderer,ogcat *cat) {
                swaproom(map,cat);
                for(int i=0;i<mapy;i++){
                    for(int j=0;j<mapx;j++){
                           if(map->maptab[map->activeroom][i][j]==1){
                                SDL_Rect pos{j*100,i*100,100,100};
                                SDL_RenderCopy(renderer, map->dirttexture, NULL, &pos);
                           } 
                            if(map->maptab[map->activeroom][i][j]==2){
                                  SDL_Rect pos{j*100,i*100,100,100};
                                  SDL_RenderCopy(renderer, map->dirt_undertexture, NULL, &pos);
                            }
                            if(map->maptab[map->activeroom][i][j]==3){
                                  SDL_Rect pos{j*100,i*100,100,100};
                                  SDL_RenderCopy(renderer, map->spikestexture, NULL, &pos);
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
        cat->x = 300;
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
    void destroyer(ogcat *cat,map *map, background *bg,frog *frog) {
        SDL_DestroyTexture(cat->texture);
        SDL_FreeSurface(cat->catload);
        SDL_FreeSurface(map->dirtload);
        SDL_DestroyTexture(map->dirttexture);
        SDL_DestroyTexture(bg->texture);
        SDL_FreeSurface(bg->load);
        SDL_FreeSurface(map->dirt_underload);
        SDL_DestroyTexture(map->dirt_undertexture);
        SDL_FreeSurface(map->spikesload);
        SDL_DestroyTexture(map->spikestexture);
        SDL_FreeSurface(frog->frogload);
        SDL_DestroyTexture(frog->frogtexture);
    }


    void cat_correct(ogcat *cat,map *map){
         int cat_correction = (cat->y + cat->h) %100;
            cat->y -= cat_correction;
            cat->vecy = 0;
            
        
    }
    void gravity(ogcat *cat,map *map) {
        if(catcollison_up(cat,map)){
            if(cat->vecy<0){
            cat->vecy = (cat->vecy*(-1))/2;
        }
        }
        if(!catcollision_down(cat,map))
        {
         cat->vecy += 1;
        }else{
            cat_correct(cat,map);
            
        }

    }

    void catjump(ogcat *cat,map *map) {
        int time_now=SDL_GetTicks();
        if(((time_now-(cat->time_lastjump)>1200))){
            cat->jump_possible=1;
            cat->time_lastjump=time_now;
        }
            
        
        if(cat->jump_possible==1&&catcollision_down(cat,map)){
        cat->vecy = -25;
        cat->jump_possible=0;
        }

    }
    void cat_death_animaiton(ogcat *cat,map *map){
        cat->x=300;
        cat->y=100;
        cat->vecy=0;
        SDL_Delay(1000);

    }
    bool cat_dead(ogcat *cat,map *map){
        if(map->maptab[map->activeroom][((cat->y+cat->h-10)/100)][(cat->x+57)/100]==3 || map->maptab[map->activeroom][((cat->y+cat->h-10)/100)][((cat->x-57)+cat->w)/100]==3){
            return true;
        }else return false;
    }
    bool game_over(ogcat *cat){
        if(cat->lifes<=0){
            return true;
        }else return false;
    }
    void catmover(ogcat *cat,map *map) {
        gravity(cat,map);
        if(catcollision_left(cat,map)){cat->x += 10;}
        if(catcollision_right(cat,map)){cat->x -= 10;}
        swaproom(map,cat);
        if(cat_dead(cat,map)){
        cat->lifes--;
        cat_death_animaiton(cat,map);
        }
        const Uint8* keyboard = SDL_GetKeyboardState(NULL);
        if ((keyboard[SDL_SCANCODE_SPACE])) {
            catjump(cat,map);
        }
        if (keyboard[SDL_SCANCODE_A]) {
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
        frog frog;
        catloader(&cat,renderer);
        maploader(&map,renderer);
        backgroundloader(&bg,renderer);
        frogloader(&frog,renderer);
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
        drawmap(&map, renderer,&cat);
        frogdrawnew(&frog,renderer,&map,&cat);
        frogdraw(&frog,renderer);

        SDL_RenderPresent(renderer);


        if(game_over(&cat)){
            break;
        }
        SDL_Delay(30);
    }
        SDL_DestroyWindow(window);
        destroyer(&cat,&map,&bg,&frog);

        SDL_Quit();
        return 1;
    }