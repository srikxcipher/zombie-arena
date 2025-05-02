#include<SFML/Graphics.hpp>

using namespace sf;

class Player{
    private:
        const float START_SPEED=200;
        const float START_HEALTH=100;
        Vector2f m_Position;
        Texture m_Texture;
        Sprite m_Sprite;
        float m_Speed;
        float m_Health;
        float m_MaxHealth;
        IntRect m_Arena;
        Vector2f m_Resolution;
        int m_TileSize;
        bool m_UpPressed;
        bool m_DownPressed;
        bool m_LeftPressed;
        bool m_RightPressed;
        Time m_LastHit;
        
    public:
        Player(); // Constructor
        void spawn(IntRect arena, Vector2f resolution, int tileSize);
        FloatRect getPosition();
        Sprite getSprite();
        Vector2f getCenter();
        float getRotation();
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
        void stopLeft();
        void stopRight();
        void stopUp();
        void stopDown();
        void update(float elapsedTime, Vector2i mousePosition); // As mouse position takes pixels position so pixels can not be fraction, it will be only in integers.
        
    };
    
    
    Player::Player(){
       m_Speed = START_SPEED;
       m_Health = START_HEALTH;
       m_MaxHealth = START_HEALTH;
       m_Texture.loadFromFile("res/graphics/player.png");
       m_Sprite.setTexture(m_Texture);
       m_Sprite.setOrigin(25,25);
       
   }
   
   void Player::spawn(IntRect arena, Vector2f resolution, int tileSize){
   
       m_Arena.left = arena.left;
       m_Arena.top = arena.top;
       m_Arena.width = arena.width;
       m_Arena.height = arena.height;
       
       m_Resolution.x = resolution.x;
       m_Resolution.y = resolution.y;
       
       m_TileSize = tileSize;
       
       m_Position.x = arena.width/2;
       m_Position.y = arena.height/2;
       m_Sprite.setPosition(m_Position); //Move this to Update part.
   }
   
  FloatRect Player::getPosition(){
       return m_Sprite.getGlobalBounds();
  }
  
  Sprite Player::getSprite(){
       return m_Sprite;
  }
  
  float Player::getRotation(){
       return m_Sprite.getRotation();
  }
  
  Vector2f Player::getCenter(){
       return m_Position;
  }
