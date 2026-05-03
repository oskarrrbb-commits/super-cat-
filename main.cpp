    #include <stdio.h>
    #include <SDL2/SDL.h>
    #include <conio.h>
    #include <cstdlib>
    #include <time.h>

    #define mapx 20
    #define mapy 12
    #define rooms 4
    #define Lifes 3
    #define cat_speed 10
    #define LEG_HITBOX_X 57
    #define birdspeed 20
    #define enable_bird_to_spawn_since_map 1
    #define DEATH_TIMER 60
    #define GOD_MODE_TIMER 100
    #define CAT_RESP_X 100
    #define CAT_RESP_Y 100
    #define CAT_W 200
    #define CAT_H 200
    #define SWORD_W 100
    #define SWORD_H 200
    #define SWORD_DURATION 10
    #define SWORD_COOLDOWN 50
    struct ogcat
    {
        SDL_Texture* texture=nullptr;
        SDL_Surface* catload=nullptr;
        SDL_Texture* texture_dead=nullptr;
        SDL_Surface* catload_dead=nullptr;
        SDL_Texture* texture_sword=nullptr;
        SDL_Surface* catload_sword=nullptr;      
        int x=CAT_RESP_X,y=CAT_RESP_Y,w=CAT_W,h=CAT_H;
        SDL_Rect pos{x,y,w,h};
        int vecx, vecy;
        bool jump_possible=true;
        bool isdying=false;
        bool canmove=true;
        bool isattacking=false;
        int attacktick=SWORD_DURATION;
        int time_lastjump=0;
        int lifes=Lifes;
        int death_timer=DEATH_TIMER;
        int godmode=false;
        int godmodetimer=GOD_MODE_TIMER;
        SDL_Rect swordpos{x+w,y,SWORD_W,SWORD_H};
    };
    struct frog
    {
        SDL_Texture* frogtexture=nullptr;
        SDL_Surface* frogload=nullptr;
        SDL_Texture* kingfrogtexture=nullptr;
        SDL_Surface* kingfrogload=nullptr;
        int x,y,w=100,h=100;
        SDL_Rect pos{x,y,w,h};
        int vecx=0, vecy=0;
        int old_y=0;
        int jumptick=0;
        bool active=false;
        bool jump=true;
        bool iskingfrog=false;


    };
    struct bird
    {
        SDL_Texture* texture=nullptr;
        SDL_Surface* load=nullptr;
        int x,y,w,h;
        SDL_Rect pos{x,y,w,h};
        int vecx, vecy;
        bool active=false;
        int spawnChance=0;
        int tick=0;
    };


    struct map
    {
        SDL_Texture* dirttexture=nullptr;
        SDL_Surface* dirtload=nullptr;
        SDL_Texture* dirt_undertexture=nullptr;
        SDL_Surface* dirt_underload=nullptr;
        SDL_Texture* spikestexture=nullptr;
        SDL_Surface* spikesload=nullptr;
        SDL_Texture* elixirtexture=nullptr;
        SDL_Surface* elixirload=nullptr;
        int maptab[rooms][mapy][mapx]={{
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0},
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
                                 {0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,5,0,0,0,1},
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
        bool swapped=false;
    };
    struct background
    {
        SDL_Texture* texture=nullptr;
        SDL_Surface* load=nullptr;
    };
    struct Stats{
        SDL_Texture* boxtexture=nullptr;
        SDL_Surface* boxload=nullptr;

    };
    void Statsloader(Stats *stats, SDL_Renderer *renderer) {
        stats->boxload=SDL_LoadBMP("assets/map/stats.bmp");
        stats->boxtexture = SDL_CreateTextureFromSurface(renderer, stats->boxload);
    }
   void statsdraw(Stats *stats, SDL_Renderer *renderer) {
        SDL_Rect pos{0,0,400,300};
        SDL_RenderCopy(renderer, stats->boxtexture, NULL, &pos);
    }
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

        map->elixirload=SDL_LoadBMP("assets/map/elixir.bmp");
        Uint32 colorkey_2 = SDL_MapRGB(map->elixirload->format, 0, 255, 0);
        SDL_SetColorKey(map->elixirload, SDL_TRUE, colorkey_2);
        map->elixirtexture = SDL_CreateTextureFromSurface(renderer, map->elixirload);        
       
    }
    void frogloader(frog *frog, SDL_Renderer *renderer) {
        frog->frogload=SDL_LoadBMP("assets/frog/frog.bmp");
        Uint32 colorkey = SDL_MapRGB(frog->frogload->format, 0, 255, 0);
        SDL_SetColorKey(frog->frogload, SDL_TRUE, colorkey);
        frog->frogtexture = SDL_CreateTextureFromSurface(renderer, frog->frogload);
        frog->kingfrogload=SDL_LoadBMP("assets/frog/kingfrog.bmp");
        Uint32 colorkey_2 = SDL_MapRGB(frog->kingfrogload->format, 0, 255, 0);
        SDL_SetColorKey(frog->kingfrogload, SDL_TRUE, colorkey_2);
        frog->kingfrogtexture = SDL_CreateTextureFromSurface(renderer, frog->kingfrogload);

    }
    void birdloader(bird *bird, SDL_Renderer *renderer) {
        bird->load=SDL_LoadBMP("assets/bird/bird.bmp");
        Uint32 colorkey = SDL_MapRGB(bird->load->format, 0, 255, 0);
        SDL_SetColorKey(bird->load, SDL_TRUE, colorkey);
        bird->texture = SDL_CreateTextureFromSurface(renderer, bird->load);
    }
    void birdkiller(bird* bird){
        if(bird->active==false){
            bird->x=0;
            bird->y=0;
            bird->vecx=0;
        }
    }
    bool spawnbird(bird *bird,map *map){
        if(bird->active){
            return false;
        }

        if(map->activeroom>=enable_bird_to_spawn_since_map&&!bird->active){

            if(bird->tick>=150){
                int bird_start_pos_y=rand()%4;
                bird->y=bird_start_pos_y*100;
                bird->x=2000;
                bird->vecx=-birdspeed;
                bird->w=100;
                bird->h=100;
                bird->tick=0;
                bird->active=true;
                return true;
                }else{
                bird->tick++;
                return false;
                }
        }
        
            return false;
        
    }
    bool swaproom(map *map,ogcat *cat){
        if(cat->x+cat->w>=2000){
            map->activeroom++;
            cat->x=0;
            printf("room +");
            return true;
        }
        if(cat->x<0){
            map->activeroom--;
            cat->x=1750;
                        printf("room -");

            return true;
        }
        return false;
    }
    void birddraw(bird *bird, SDL_Renderer *renderer,map *map,ogcat *cat) {
        birdkiller(bird);
        spawnbird(bird,map);
        if(map->swapped){
                bird->active=false;
        }
        if(bird->active){
            bird->x=bird->x+bird->vecx;
            bird->pos = {bird->x, bird->y, bird->w, bird->h};
            SDL_RenderCopy(renderer, bird->texture, NULL, &bird->pos);
            if(bird->x<-100){
                bird->active=false;
            }else bird->active=true;
        }
        }
    
    
  
    bool catcollision_down(ogcat *cat,map *map) {
        
        if(map->maptab[map->activeroom][((cat->y+cat->h)/100)][(cat->x+LEG_HITBOX_X)/100]==1 || map->maptab[map->activeroom][((cat->y+cat->h)/100)][((cat->x-LEG_HITBOX_X)+cat->w)/100]==1){
            return true;
        }else return false;
        
             
        
    }
    bool catcollision_left(ogcat *cat,map *map){
        if(map->maptab[map->activeroom][((cat->y+((cat->h)/2))/100)][(cat->x+LEG_HITBOX_X)/100]==1|| map->maptab[map->activeroom][((cat->y+((cat->h)/2))/100)][(cat->x+LEG_HITBOX_X)/100]==2){
            return true;
        }else return false;
    }
    bool catcollision_right(ogcat *cat,map *map){
        if(map->maptab[map->activeroom][((cat->y+((cat->h)/2))/100)][(cat->x+cat->w-LEG_HITBOX_X)/100]==1||map->maptab[map->activeroom][((cat->y+((cat->h)/2))/100)][(cat->x+cat->w-LEG_HITBOX_X)/100]==2 ){
            return true;
        }else return false;
    }
    bool catcollison_up(ogcat *cat,map*map){
        if(map->maptab[map->activeroom][((cat->y+50)/100)][(cat->x+LEG_HITBOX_X)/100]==1 || map->maptab[map->activeroom][((cat->y+50)/100)][((cat->x-LEG_HITBOX_X)+cat->w)/100]==1){
            return true;
        }else return false;
        
    }
    void frogdrawnew(frog *frog, SDL_Renderer *renderer,map *map,ogcat *cat){ 
        
                for(int i=0;i<mapy;i++){
                    for(int j=0;j<mapx;j++){
                           
                            if(map->maptab[map->activeroom][i][j]==4||map->maptab[map->activeroom][i][j]==5){
                                if(frog->active){
                                    return;
                                }
                                if(map->maptab[map->activeroom][i][j]==5){
                                    frog->iskingfrog=true;
                                }else{
                                frog->iskingfrog=false;

                                }
                                frog->x=j*100;
                                frog->y=i*100;
                                frog->old_y=frog->y;
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
            frog->y=frog->old_y;
            
        }
        }
        frog->jumptick++;
            if(frog->iskingfrog){
                frog->pos = {frog->x, frog->y, frog->w, frog->h};
                SDL_RenderCopy(renderer, frog->kingfrogtexture, NULL, &frog->pos);
            }else{
                frog->pos = {frog->x, frog->y, frog->w, frog->h};
                SDL_RenderCopy(renderer, frog->frogtexture, NULL, &frog->pos);
            }
        
    }
    }
    void drawmap(map *map, SDL_Renderer *renderer,ogcat *cat) {            
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
                            if(map->maptab[map->activeroom][i][j]==8){
                                  SDL_Rect pos{j*100,i*100,100,100};
                                  SDL_RenderCopy(renderer, map->elixirtexture, NULL, &pos);
                            }
                    }
                }
                


    }

    void catloader(ogcat *cat, SDL_Renderer *renderer) {
        SDL_Surface *catload = SDL_LoadBMP("assets/cat/ogcat.bmp");
        SDL_Surface *catload_dead = SDL_LoadBMP("assets/cat/ogcat_dead.bmp");
        SDL_Surface *catload_sword = SDL_LoadBMP("assets/cat/sword.bmp");
        Uint32 colorkey_1 = SDL_MapRGB(catload->format, 0, 255, 0);
        Uint32 colorkey_2 = SDL_MapRGB(catload_dead->format, 0, 255, 0);
        Uint32 colorkey_3 = SDL_MapRGB(catload_sword->format, 0, 255, 0);

        SDL_SetColorKey(catload, SDL_TRUE, colorkey_1);
        SDL_SetColorKey(catload_dead, SDL_TRUE, colorkey_2);
        SDL_SetColorKey(catload_sword, SDL_TRUE, colorkey_3);
        cat->catload = catload;
        cat->texture = SDL_CreateTextureFromSurface(renderer, cat->catload);
        cat->catload_dead = catload_dead;
        cat->texture_dead = SDL_CreateTextureFromSurface(renderer, cat->catload_dead);
        cat->catload_sword = catload_sword;
        cat->texture_sword = SDL_CreateTextureFromSurface(renderer, cat->catload_sword);
        cat->vecx = 0;
        cat->vecy = 0;
        cat->pos = {cat->x, cat->y, cat->w, cat->h}; 
    }
    bool cat_dies(ogcat *cat,map *map,bird *bird,frog *frog){
        SDL_Rect bird_rect = bird->pos;
        SDL_Rect cat_rect = cat->pos;
        SDL_Rect frog_rect = frog->pos;

        if(bird->active)   
        {
            if(SDL_HasIntersection(&bird_rect, &cat_rect)) return true;
        }  
        if(frog->active) 
        {
            if(SDL_HasIntersection(&frog_rect, &cat_rect)) return true;
        }

        if((map->maptab[map->activeroom][((cat->y+cat->h-10)/100)][(cat->x+LEG_HITBOX_X)/100]==3 || map->maptab[map->activeroom][((cat->y+cat->h-10)/100)][((cat->x-LEG_HITBOX_X)+cat->w)/100]==3))
            return true;
            
        
         return false;
    }
    void sword_draw(ogcat *cat,map *map,SDL_Renderer *renderer){
        cat->swordpos={cat->x+cat->w-LEG_HITBOX_X,cat->y,SWORD_W,SWORD_H};

        if(cat->isattacking){

        if(cat->attacktick<=0){
                cat->attacktick=SWORD_DURATION;
                cat->isattacking=false;
        }
        SDL_RenderCopy(renderer, cat->texture_sword, NULL, &cat->swordpos);
        cat->attacktick--;
        }
    }
    void drawcat(ogcat *cat, SDL_Renderer *renderer,map *map) {
        if(cat->isdying){
                SDL_RenderCopy(renderer, cat->texture_dead, NULL, &cat->pos);
                cat->death_timer--;
                cat->canmove=false;
                if(cat->death_timer<=0){
                cat->isdying = false;
                cat->canmove=true;
                cat->x = 300;  
                cat->y = 100;
                cat->vecy = 0;       
             }
        }else{
        SDL_RenderCopy(renderer, cat->texture, NULL, &cat->pos);
        }
        if(cat->godmodetimer>0) cat->godmodetimer--;
        if(cat->godmodetimer==0) cat->godmode=false;
    }
    void destroyer(ogcat *cat,map *map, background *bg,frog *frog,bird *bird,Stats *stats) {
        SDL_DestroyTexture(cat->texture);
        SDL_DestroyTexture(cat->texture_dead);
        SDL_FreeSurface(cat->catload);
        SDL_FreeSurface(cat->catload_dead);
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
        SDL_FreeSurface(frog->kingfrogload);
        SDL_DestroyTexture(frog->kingfrogtexture);
        SDL_DestroyTexture(bird->texture);
        SDL_FreeSurface(bird->load);
        SDL_FreeSurface(map->elixirload);
        SDL_DestroyTexture(map->elixirtexture);
        SDL_FreeSurface(stats->boxload);
        SDL_DestroyTexture(stats->boxtexture);
        SDL_DestroyTexture(cat->texture_sword);
        SDL_FreeSurface(cat->catload_sword);
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
            cat->jump_possible=true;
            cat->time_lastjump=time_now;
        }
            
        
        if(cat->jump_possible==true&&catcollision_down(cat,map)){
        cat->vecy = -25;
        cat->jump_possible=false;
        }

    }

    bool game_over(ogcat *cat){
        if(cat->lifes<=0){
            return true;
        }else return false;
    }
    void cat_death_check(ogcat *cat,map *map,bird *bird,frog *frog){
        if(cat_dies(cat,map,bird,frog)&&!cat->isdying&&!cat->godmode){
        cat->isdying=true;
        cat->death_timer=DEATH_TIMER;
        cat->godmodetimer=GOD_MODE_TIMER;
        cat->godmode=true;
        cat->lifes--;
    }
    }
    void catmover(ogcat *cat,map *map,SDL_Renderer *renderer,frog *frog,bird *bird){
        if(!cat->canmove) return;
        gravity(cat,map);
        if(catcollision_left(cat,map)){cat->x += 10;}
        if(catcollision_right(cat,map)){cat->x -= 10;}
        if(swaproom(map,cat)){
            map->swapped=true;
        }else map->swapped=false;
        
        cat_death_check(cat,map,bird,frog);
        
        const Uint8* keyboard = SDL_GetKeyboardState(NULL);
        if ((keyboard[SDL_SCANCODE_SPACE])) {
            catjump(cat,map);
        }
        if (keyboard[SDL_SCANCODE_A]) {
            cat->x -= cat_speed;
        }
        if (keyboard[SDL_SCANCODE_D]) {
            cat->x += cat_speed;
        }
        if (keyboard[SDL_SCANCODE_K]) {
            cat->isattacking=true;
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
        bird bird;
        Stats stats;
        catloader(&cat,renderer);
        maploader(&map,renderer);
        backgroundloader(&bg,renderer);
        frogloader(&frog,renderer);
        birdloader(&bird,renderer);
        Statsloader(&stats,renderer);
        SDL_Event e;
        srand(time(NULL));
        while (true)
        {
        while (SDL_PollEvent(&e))
        {
            
            if (e.type == SDL_QUIT)
                return 0;
                
        }
        SDL_RenderClear(renderer);
        catmover(&cat,&map,renderer,&frog,&bird);
        
        backgrounddraw(&bg,renderer);
        drawcat(&cat, renderer,&map);
        sword_draw(&cat,&map,renderer);
        drawmap(&map, renderer,&cat);
        frogdrawnew(&frog,renderer,&map,&cat);
        frogdraw(&frog,renderer);
        birddraw(&bird,renderer,&map,&cat);
        statsdraw(&stats,renderer);
        SDL_RenderPresent(renderer);


        if(game_over(&cat)){
            break;
        }
        SDL_Delay(30);
    }
        SDL_DestroyWindow(window);
        destroyer(&cat,&map,&bg,&frog,&bird,&stats);

        SDL_Quit();
        return 1;
    }