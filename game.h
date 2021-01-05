#ifndef __GAME_H__
#define __GAME_H__

#define SECOND 1000.0
#define FRAME 60.0

namespace Game{
    class GameObject{
    protected:
    public:
        GameObject(){}
        virtual void Render(SDL_Renderer*)=0;
        virtual void Update()=0;
        virtual void Init()=0;
    };

    int GetInputKey(int);
    int IsKeyPressed();

    class Animation{

    };

    class Player:public GameObject{
        private:
            SDL_Rect position;
            b2Body* body;
            b2Vec2 currentVelocity;
            float jumpSpeed;
            SDL_Texture** textures;
            int direction;
            int anim;
            int delay;
            int r;
            float vX;
        public:
            Player(b2World&,SDL_Rect,SDL_Texture**);
            void Render(SDL_Renderer*);
            void Update();
            void EventHandler(SDL_Event);
            void Init();
    };
    
}


namespace Map{
    class Map: public Game::GameObject{
        private:
            tmx_map* map;
        public:
            Map(tmx_map*);
            void Render(SDL_Renderer*);
            void Update();
            void Init();
            void LoadCollision(tmx_layer*,b2World&);
    };
}
#endif