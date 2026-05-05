    #include <stdio.h>
    #include <SDL2/SDL.h>
    #include <conio.h>
    #include <cstdlib>
    #include <time.h>

    #define mapx 20
    #define mapy 12
    #define rooms 11
    #define Lifes 7
    #define cat_speed 10
    #define LEG_HITBOX_X 57
    #define birdspeed 20
    #define enable_bird_to_spawn_since_map 4
    #define DEATH_TIMER 60
    #define GOD_MODE_TIMER 100
    #define CAT_RESP_X 0
    #define CAT_RESP_Y 200
    #define CAT_W 200
    #define CAT_H 200
    #define SWORD_W 100
    #define SWORD_H 200
    #define SWORD_DURATION 10
    #define SWORD_COOLDOWN 50
    #define NUMBER_IN_STATS_SIZE 50
    struct ogcat
    {
        SDL_Texture* texture_stand=nullptr;
        SDL_Surface* catload_stand=nullptr;
        SDL_Texture* texture_dead=nullptr;
        SDL_Surface* catload_dead=nullptr;
        SDL_Texture* texture_sword=nullptr;
        SDL_Surface* catload_sword=nullptr;      
        SDL_Texture* texture_left=nullptr;
        SDL_Surface* catload_left=nullptr;
        SDL_Texture* texture_right=nullptr;
        SDL_Surface* catload_right=nullptr;
        SDL_Texture* texture_walk1=nullptr;
        SDL_Surface* catload_walk1=nullptr;
        SDL_Texture* texture_walk2=nullptr;
        SDL_Surface* catload_walk2=nullptr;

        int x=CAT_RESP_X,y=CAT_RESP_Y,w=CAT_W,h=CAT_H;
        SDL_Rect pos{x,y,w,h};
        int vecx, vecy;
        bool jump_possible=true;
        bool isdying=false;
        bool canmove=true;
        bool isattacking=false;
        bool has_sword=false;
        bool faceleft=false;
        bool walked=false;
        int attacktick=SWORD_DURATION;
        int swordcooldown=SWORD_COOLDOWN;
        int time_lastjump=0;
        int lifes=Lifes;
        int death_timer=DEATH_TIMER;
        int godmode=false;
        int godmodetimer=GOD_MODE_TIMER;
        int elixirs=0;
        int hearts=0;
        int current_step=0;
        int steptick=0;
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
        int tileX,tileY;
        int oldtileX,oldtileY;
        bool swap=false;

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
        SDL_Texture* swordtexture=nullptr;
        SDL_Surface* swordload=nullptr;        
        SDL_Texture* hearttexture=nullptr;
        SDL_Surface* heartload=nullptr;      
        SDL_Texture* sign1texture=nullptr;
        SDL_Surface* sign1load=nullptr;
        SDL_Texture* sign2texture=nullptr;
        SDL_Surface* sign2load=nullptr;
        SDL_Texture* sign3texture=nullptr;
        SDL_Surface* sign3load=nullptr;
        SDL_Texture* sign4texture=nullptr;
        SDL_Surface* sign4load=nullptr;
        SDL_Texture* ladybugtexture=nullptr;
        SDL_Surface* ladybugload=nullptr;
        /*
        0-air
        1-dirt
        2-dirt under 
        3-spikes
        4-frog
        5-kingfrog
        6-heart
        8-elixir
        9-sword  
        67-ladybug
        11,12,13,14-signs 
        */    

        /*
                                {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,0,0,0,0,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                 {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
        
        
        */
        int maptab[rooms][mapy][mapx]={
                                 {
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,0,0,0,0,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                 {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
                                 },
                                 {
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,1,1,2,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,1,2,2,2,0,0,0,0,0,1,0,0,0,0},
                                 {0,0,0,0,1,1,2,2,2,2,0,0,0,1,1,2,1,0,0,0},
                                 {1,1,1,1,2,2,2,2,2,2,1,1,1,2,2,2,2,1,1,1},
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
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,12,0,0,1,1,1,0,0,0,0,0,0,0,0,0},
                                 {1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1},
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
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,1,0,0,3,3,3,1,0,0,0,0,0,0,0,0},
                                 {1,1,1,1,1,2,0,0,2,2,2,2,1,1,1,1,1,1,1,1},
                                 {2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2}
                                 },{
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
                                 {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,13,0,1,1,8,0,0,0,0,0,0,0,0,0},
                                 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                 {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
                                 },
                                {
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,3,0,0,0,1,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,14,0,0,0,0,4,2,0,0,0,0,0,0,0,0,0},
                                 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                 {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
                                 },
                                 {
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,3,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0},
                                 {0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,2,0,8,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0},
                                 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
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
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,1,4,3,3,3,3,1,0,0,0,0,3,0,0,0,0},
                                 {1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1},
                                 {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
                                 },
                                 {
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,3,0,9,0,3,0,0,0,0,0},
                                 {0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,5,0,0,0,0,0,3,3,3,3,3,3,3,3,0,0,0},
                                 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                 {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
                                 },
                                 {
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0},
                                 {0,0,0,1,0,0,3,3,0,0,0,0,0,0,0,1,0,0,1,0},
                                 {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,2,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0},
                                 {0,0,1,0,0,0,0,0,0,0,3,3,3,3,3,0,0,0,2,0},
                                 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,0,2,1},
                                 {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2}
                                 },
                                 {
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,2},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,2},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                                 {0,0,0,0,3,3,3,0,0,0,0,3,5,0,0,3,0,0,67,2},
                                 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                 {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
                                 }

                                };

        int activeroom=0;
        bool swapped=false;
        SDL_Rect ladybug_pos={0,0,0,0};

    };
    struct background
    {
        SDL_Texture* texture=nullptr;
        SDL_Surface* load=nullptr;
    };
    struct Stats{
        SDL_Texture* boxtexture=nullptr;
        SDL_Surface* boxload=nullptr;

        SDL_Texture* yestexture=nullptr;
        SDL_Surface* yesload=nullptr;

        SDL_Texture* notexture=nullptr;
        SDL_Surface* noload=nullptr;

        SDL_Texture* nr0texture=nullptr;
        SDL_Surface* nr0load=nullptr;        

        SDL_Texture* nr1texture=nullptr;
        SDL_Surface* nr1load=nullptr;       

        SDL_Texture* nr2texture=nullptr;
        SDL_Surface* nr2load=nullptr; 

        SDL_Texture* nr3texture=nullptr;
        SDL_Surface* nr3load=nullptr;        
    };
    void Statsloader(Stats *stats, SDL_Renderer *renderer) {
        stats->boxload=SDL_LoadBMP("assets/map/stats.bmp");
        stats->boxtexture = SDL_CreateTextureFromSurface(renderer, stats->boxload);

        stats->nr0load=SDL_LoadBMP("assets/map/ziobro.bmp");
        stats->nr0texture = SDL_CreateTextureFromSurface(renderer, stats->nr0load);

        stats->nr1load=SDL_LoadBMP("assets/map/number1.bmp");
        stats->nr1texture = SDL_CreateTextureFromSurface(renderer, stats->nr1load);

        stats->nr2load=SDL_LoadBMP("assets/map/number2.bmp");
        stats->nr2texture = SDL_CreateTextureFromSurface(renderer, stats->nr2load);

        stats->nr3load=SDL_LoadBMP("assets/map/number3.bmp");
        stats->nr3texture = SDL_CreateTextureFromSurface(renderer, stats->nr3load);

        stats->yesload=SDL_LoadBMP("assets/map/yes.bmp");
        stats->yestexture = SDL_CreateTextureFromSurface(renderer, stats->yesload);

        stats->noload=SDL_LoadBMP("assets/map/no.bmp");
        stats->notexture = SDL_CreateTextureFromSurface(renderer, stats->noload);
    }
   void statsdraw(Stats *stats, SDL_Renderer *renderer,ogcat *cat) {
        SDL_Rect pos{0,0,400,300};
        SDL_RenderCopy(renderer, stats->boxtexture, NULL, &pos);

        SDL_Rect lifespos{25,85,NUMBER_IN_STATS_SIZE,NUMBER_IN_STATS_SIZE};
        SDL_Rect elixirspos{125,85,NUMBER_IN_STATS_SIZE,NUMBER_IN_STATS_SIZE};
        SDL_Rect heartspos{225,85,NUMBER_IN_STATS_SIZE,NUMBER_IN_STATS_SIZE};
        SDL_Rect hasswordpos{325,85,NUMBER_IN_STATS_SIZE,NUMBER_IN_STATS_SIZE};


        switch (cat->lifes)
        {
        case 0:
        SDL_RenderCopy(renderer, stats->nr0texture, NULL, &lifespos);
            break;

        case 1:
        SDL_RenderCopy(renderer, stats->nr1texture, NULL, &lifespos);
            break;
        case 2:
        SDL_RenderCopy(renderer, stats->nr2texture, NULL, &lifespos);
            break;
   
        case 3:
        SDL_RenderCopy(renderer, stats->nr3texture, NULL, &lifespos);
            break;
        }

        switch (cat->elixirs)
        {
        case 0:
        SDL_RenderCopy(renderer, stats->nr0texture, NULL, &elixirspos);
            break;

        case 1:
        SDL_RenderCopy(renderer, stats->nr1texture, NULL, &elixirspos);
            break;
        case 2:
        SDL_RenderCopy(renderer, stats->nr2texture, NULL, &elixirspos);
            break;
   
        case 3:
        SDL_RenderCopy(renderer, stats->nr3texture, NULL, &elixirspos);
            break;
        }

        switch (cat->hearts)
        {
        case 0:
        SDL_RenderCopy(renderer, stats->nr0texture, NULL, &heartspos);
            break;

        case 1:
        SDL_RenderCopy(renderer, stats->nr1texture, NULL, &heartspos);
            break;
        case 2:
        SDL_RenderCopy(renderer, stats->nr2texture, NULL, &heartspos);
            break;
   
        case 3:
        SDL_RenderCopy(renderer, stats->nr3texture, NULL, &heartspos);
            break;
        }
        if(cat->has_sword){
        SDL_RenderCopy(renderer, stats->yestexture, NULL, &hasswordpos);
        }else       SDL_RenderCopy(renderer, stats->notexture, NULL, &hasswordpos);

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

        map->swordload=SDL_LoadBMP("assets/map/sword.bmp");
        Uint32 colorkey_3 = SDL_MapRGB(map->swordload->format, 0, 255, 0);
        SDL_SetColorKey(map->swordload, SDL_TRUE, colorkey_3);
        map->swordtexture = SDL_CreateTextureFromSurface(renderer, map->swordload);       
        
        
        map->heartload=SDL_LoadBMP("assets/map/heart.bmp");
        Uint32 colorkey_4 = SDL_MapRGB(map->heartload->format, 0, 255, 0);
        SDL_SetColorKey(map->heartload, SDL_TRUE, colorkey_4);
        map->hearttexture = SDL_CreateTextureFromSurface(renderer, map->heartload);     
        
        map->sign1load=SDL_LoadBMP("assets/map/sign1.bmp");
        Uint32 colorkey_5 = SDL_MapRGB(map->sign1load->format, 0, 255, 0);
        SDL_SetColorKey(map->sign1load, SDL_TRUE, colorkey_5);
        map->sign1texture = SDL_CreateTextureFromSurface(renderer, map->sign1load);

        map->sign2load=SDL_LoadBMP("assets/map/sign2.bmp");
        Uint32 colorkey_6 = SDL_MapRGB(map->sign2load->format, 0, 255, 0);
        SDL_SetColorKey(map->sign2load, SDL_TRUE, colorkey_6);
        map->sign2texture = SDL_CreateTextureFromSurface(renderer, map->sign2load);

        map->sign3load=SDL_LoadBMP("assets/map/sign3.bmp");
        Uint32 colorkey_7 = SDL_MapRGB(map->sign3load->format, 0, 255, 0);
        SDL_SetColorKey(map->sign3load, SDL_TRUE, colorkey_6);
        map->sign3texture = SDL_CreateTextureFromSurface(renderer, map->sign3load);

        map->sign4load=SDL_LoadBMP("assets/map/sign4.bmp");
        Uint32 colorkey_8 = SDL_MapRGB(map->sign4load->format, 0, 255, 0);
        SDL_SetColorKey(map->sign4load, SDL_TRUE, colorkey_8);
        map->sign4texture = SDL_CreateTextureFromSurface(renderer, map->sign4load);

        map->ladybugload=SDL_LoadBMP("assets/map/ladybug.bmp");
        Uint32 colorkey_9 = SDL_MapRGB(map->ladybugload->format, 0, 255, 0);
        SDL_SetColorKey(map->ladybugload, SDL_TRUE, colorkey_9);
        map->ladybugtexture = SDL_CreateTextureFromSurface(renderer, map->ladybugload);
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
            return true;
        }
        if(cat->x<0){
            map->activeroom--;
            cat->x=1750;
            return true;
        }
        return false;
    }
    void bird_killed_sword(bird *bird,ogcat *cat){
    if(SDL_HasIntersection(&bird->pos, &cat->swordpos)&&cat->isattacking){
            bird->active=false;
       }
    }
    void birddraw(bird *bird, SDL_Renderer *renderer,map *map,ogcat *cat) {
        birdkiller(bird);
        bird_killed_sword(bird,cat);
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

    void forg_killed(frog *frog,ogcat *cat,map *map){
       if(SDL_HasIntersection(&frog->pos, &cat->swordpos)&&cat->isattacking&&frog->active){
        if(frog->iskingfrog){
            map->maptab[map->activeroom][frog->tileY][frog->tileX]=6;
            frog->active=false;
        }
        if(!frog->iskingfrog){
            map->maptab[map->activeroom][frog->tileY][frog->tileX]=0;
            frog->active=false;
        }
       }
        

    }

    void frogdrawnew(frog *frog, SDL_Renderer *renderer,map *map,ogcat *cat){ 
                forg_killed(frog,cat,map);
                for(int i=0;i<mapy;i++){
                    for(int j=0;j<mapx;j++){
                           
                            if(map->maptab[map->activeroom][i][j]==4||map->maptab[map->activeroom][i][j]==5){
                                if(map->maptab[map->activeroom][i][j]==5){
                                    frog->iskingfrog=true;
                                }else{
                                frog->iskingfrog=false;

                                }
                                
                                frog->tileX=j;
                                frog->tileY=i;

                                if(frog->tileX!=frog->oldtileX||frog->tileY!=frog->oldtileY){

                                }else{

                                    if(frog->active||frog->swap){
                                    frog->swap=false;
                                    return;
                                }
                                }
                               
                                frog->oldtileX=j;
                                frog->oldtileY=i;
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
            frog->y-=15;
        }else{
             if(frog->jumptick<75){
            frog->y+=10;
        
        }else{
            if(frog->jumptick>125)
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
                            if(map->maptab[map->activeroom][i][j]==9){
                                  SDL_Rect pos{j*100,i*100,100,100};
                                  SDL_RenderCopy(renderer, map->swordtexture, NULL, &pos);
                            }
                            if(map->maptab[map->activeroom][i][j]==6){
                                  SDL_Rect pos{j*100,i*100,100,100};
                                  SDL_RenderCopy(renderer, map->hearttexture, NULL, &pos);
                            }
                            if(map->maptab[map->activeroom][i][j]==11){
                                  SDL_Rect pos{j*100,i*100,100,100};
                                  SDL_RenderCopy(renderer, map->sign1texture, NULL, &pos);
                            }
                            if(map->maptab[map->activeroom][i][j]==12){
                                  SDL_Rect pos{j*100,i*100,100,100};
                                  SDL_RenderCopy(renderer, map->sign2texture, NULL, &pos);
                            }
                            if(map->maptab[map->activeroom][i][j]==13){
                                  SDL_Rect pos{j*100,i*100,100,100};
                                  SDL_RenderCopy(renderer, map->sign3texture, NULL, &pos);
                            }
                            if(map->maptab[map->activeroom][i][j]==14){
                                  SDL_Rect pos{j*100,i*100,100,100};
                                  SDL_RenderCopy(renderer, map->sign4texture, NULL, &pos);
                            }
                            if(map->maptab[map->activeroom][i][j]==67){
                                  SDL_Rect pos{j*100,i*100,100,100};
                                  SDL_RenderCopy(renderer, map->ladybugtexture, NULL, &pos);
                                  map->ladybug_pos={j*100,i*100,100,100};
                            }
                    }
                }
                


    }

    void catloader(ogcat *cat, SDL_Renderer *renderer) {
        SDL_Surface *catload_stand = SDL_LoadBMP("assets/cat/ogcat.bmp");
        SDL_Surface *catload_dead = SDL_LoadBMP("assets/cat/ogcat_dead.bmp");
        SDL_Surface *catload_sword = SDL_LoadBMP("assets/cat/sword.bmp");
        SDL_Surface *catload_left = SDL_LoadBMP("assets/cat/ogcat_left.bmp");
        SDL_Surface *catload_right = SDL_LoadBMP("assets/cat/ogcat_right.bmp");
        SDL_Surface *catload_walk1 = SDL_LoadBMP("assets/cat/walk1.bmp");
        SDL_Surface *catload_walk2 = SDL_LoadBMP("assets/cat/walk2.bmp");

        Uint32 colorkey_1 = SDL_MapRGB(catload_stand->format, 0, 255, 0);
        Uint32 colorkey_2 = SDL_MapRGB(catload_dead->format, 0, 255, 0);
        Uint32 colorkey_3 = SDL_MapRGB(catload_sword->format, 0, 255, 0);
        Uint32 colorkey_4 = SDL_MapRGB(catload_left->format, 0, 255, 0);
        Uint32 colorkey_5 = SDL_MapRGB(catload_right->format, 0, 255, 0);
        Uint32 colorkey_6 = SDL_MapRGB(catload_walk1->format, 0, 255, 0);
        Uint32 colorkey_7 = SDL_MapRGB(catload_walk2->format, 0, 255, 0);

        SDL_SetColorKey(catload_stand, SDL_TRUE, colorkey_1);
        SDL_SetColorKey(catload_dead, SDL_TRUE, colorkey_2);
        SDL_SetColorKey(catload_sword, SDL_TRUE, colorkey_3);
        SDL_SetColorKey(catload_left, SDL_TRUE, colorkey_4);
        SDL_SetColorKey(catload_right, SDL_TRUE, colorkey_5);
        SDL_SetColorKey(catload_walk1, SDL_TRUE, colorkey_6);
        SDL_SetColorKey(catload_walk2, SDL_TRUE, colorkey_7);


        cat->catload_stand = catload_stand;
        cat->texture_stand = SDL_CreateTextureFromSurface(renderer, cat->catload_stand);

        cat->catload_dead = catload_dead;
        cat->texture_dead = SDL_CreateTextureFromSurface(renderer, cat->catload_dead);

        cat->catload_sword = catload_sword;
        cat->texture_sword = SDL_CreateTextureFromSurface(renderer, cat->catload_sword);

        cat->catload_left = catload_left;
        cat->texture_left = SDL_CreateTextureFromSurface(renderer, cat->catload_left);

        cat->catload_right = catload_right;
        cat->texture_right = SDL_CreateTextureFromSurface(renderer, cat->catload_right);

        cat->catload_walk1 = catload_walk1;
        cat->texture_walk1 = SDL_CreateTextureFromSurface(renderer, cat->catload_walk1);

        cat->catload_walk2 = catload_walk2;
        cat->texture_walk2 = SDL_CreateTextureFromSurface(renderer, cat->catload_walk2);

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
            if(SDL_HasIntersection(&bird->pos, &cat->pos)) return true;
        }  
        if(frog->active) 
        {
            if(SDL_HasIntersection(&frog->pos, &cat->pos)) return true;
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
        cat->swordcooldown=SWORD_COOLDOWN;
        }
        cat->swordcooldown--;
    }
    void cat_collect(map *map, SDL_Renderer *renderer,ogcat *cat) {            
                for(int i=0;i<mapy;i++){
                    for(int j=0;j<mapx;j++){
                                         
                            if(map->maptab[map->activeroom][i][j]==8){
                                  SDL_Rect pos{j*100,i*100,100,100};
                                  if(SDL_HasIntersection(&cat->pos, &pos)){
                                    cat->elixirs++;
                                    map->maptab[map->activeroom][i][j]=0;
                                  }
                            }
                            if(map->maptab[map->activeroom][i][j]==9){
                                  SDL_Rect pos{j*100,i*100,100,100};
                                  if(SDL_HasIntersection(&cat->pos, &pos)){
                                    cat->has_sword=true;
                                    map->maptab[map->activeroom][i][j]=0;
                                  }
                            }
                            if(map->maptab[map->activeroom][i][j]==6){
                                   SDL_Rect pos{j*100,i*100,100,100};
                                  if(SDL_HasIntersection(&cat->pos, &pos)){
                                    cat->hearts++;
                                    map->maptab[map->activeroom][i][j]=0;
                                  }
                            }
                    }
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
            if(!catcollision_down(cat,map)){
                if(cat->faceleft){

                            SDL_RenderCopy(renderer, cat->texture_left, NULL, &cat->pos);

                }else       SDL_RenderCopy(renderer, cat->texture_right, NULL, &cat->pos);
            }else{
                if(cat->walked)
                {

                if(cat->steptick>=0) cat->current_step=0;
                if(cat->steptick>=4) cat->current_step=1;
                if(cat->steptick>=8) cat->current_step=0;
                if(cat->steptick>=12) cat->current_step=2; 

                if(cat->steptick>=16)  cat->steptick=0;

                cat->steptick++;

                switch(cat->current_step){
                case 0:
                    SDL_RenderCopy(renderer, cat->texture_stand, NULL, &cat->pos);
                    break;
                
                case 1:
                SDL_RenderCopy(renderer, cat->texture_walk1, NULL, &cat->pos);
                    break;

                    case 2:
                SDL_RenderCopy(renderer, cat->texture_walk2, NULL, &cat->pos);
                    break;
                }

                }else 
                {
                    SDL_RenderCopy(renderer, cat->texture_stand, NULL, &cat->pos);
                    cat->steptick=0;
                    cat->current_step=0;
                }

            }
        }
        if(cat->godmodetimer>0) cat->godmodetimer--;
        if(cat->godmodetimer==0) cat->godmode=false;
    }
    void destroyer(ogcat *cat,map *map, background *bg,frog *frog,bird *bird,Stats *stats) {
        SDL_DestroyTexture(cat->texture_stand);
        SDL_DestroyTexture(cat->texture_dead);
        SDL_FreeSurface(cat->catload_stand);
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
        SDL_FreeSurface(map->heartload);
        SDL_DestroyTexture(map->hearttexture);
        SDL_FreeSurface(stats->nr0load);
        SDL_DestroyTexture(stats->nr0texture);
        SDL_FreeSurface(stats->nr1load);
        SDL_DestroyTexture(stats->nr1texture);
        SDL_FreeSurface(stats->nr2load);
        SDL_DestroyTexture(stats->nr2texture);
        SDL_FreeSurface(stats->nr3load);
        SDL_DestroyTexture(stats->nr3texture);
        SDL_FreeSurface(stats->noload);
        SDL_DestroyTexture(stats->notexture);
        SDL_FreeSurface(stats->yesload);
        SDL_DestroyTexture(stats->yestexture);
        SDL_FreeSurface(cat->catload_left);
        SDL_DestroyTexture(cat->texture_left);
        SDL_FreeSurface(cat->catload_right);
        SDL_DestroyTexture(cat->texture_right);
        SDL_FreeSurface(cat->catload_walk1);
        SDL_DestroyTexture(cat->texture_walk1);
        SDL_FreeSurface(cat->catload_walk2);
        SDL_DestroyTexture(cat->texture_walk2);
        SDL_FreeSurface(map->sign1load);
        SDL_DestroyTexture(map->sign1texture);
        SDL_FreeSurface(map->sign2load);
        SDL_DestroyTexture(map->sign2texture);
        SDL_FreeSurface(map->sign3load);
        SDL_DestroyTexture(map->sign3texture);
        SDL_FreeSurface(map->sign4load);
        SDL_DestroyTexture(map->sign4texture);
        SDL_FreeSurface(map->ladybugload);
        SDL_DestroyTexture(map->ladybugtexture);
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
    bool game_won(ogcat *cat,map *map){
        if(SDL_HasIntersection(&cat->pos,&map->ladybug_pos)&&cat->elixirs==3&&cat->hearts==3){
            return true;
        }
        return false;
    }
    bool game_over(ogcat *cat){
        if(cat->lifes<=-1){
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
        
        cat->walked=false;

        const Uint8* keyboard = SDL_GetKeyboardState(NULL);
        if ((keyboard[SDL_SCANCODE_SPACE])) {
            catjump(cat,map);
        }
        if (keyboard[SDL_SCANCODE_A]) {
            cat->x -= cat_speed;
            cat->faceleft=true;
            cat->walked=true;
        }
        if (keyboard[SDL_SCANCODE_D]) {
            cat->x += cat_speed;
            cat->faceleft=false;
            cat->walked=true;
        }
        if (keyboard[SDL_SCANCODE_K]) {
            if(cat->has_sword&&cat->swordcooldown<=0)
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
        statsdraw(&stats,renderer,&cat);
        cat_collect(&map,renderer,&cat);
        SDL_RenderPresent(renderer);


        if(game_over(&cat)){
                        printf("LOST");

            break;
        }

        if(game_won(&cat,&map)){
            printf("WON");
            break;
        }
        SDL_Delay(30);
    }
        SDL_DestroyWindow(window);
        destroyer(&cat,&map,&bg,&frog,&bird,&stats);

        SDL_Quit();
        return 1;
    }