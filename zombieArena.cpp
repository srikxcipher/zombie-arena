#include<iostream>
#include<SFML/Graphics.hpp>
#include "player.cpp"
#include "zombie_class.cpp"

using namespace sf;
using namespace std;

int createBackground(VertexArray& rVA, IntRect arena);
Zombie *createHorde(int numZombies, IntRect arena);

int main()
{
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    
    Texture textureBackground;
    textureBackground.loadFromFile("res/graphics/background_sheet.png");
    
    
    
    Texture textureCrossHair;
    textureCrossHair.loadFromFile("res/graphics/crosshair.png");
    
    Sprite spriteCrossHair;
    spriteCrossHair.setTexture(textureCrossHair);
    spriteCrossHair.setOrigin(25,25);
    
    int wave = 0;
    
    //Screen
    Vector2i mouseScreenPosition;
    //Game - Arena
    Vector2f mouseWorldPosition;
    
    
    VertexArray background;
    //background.resize(10*10*4);
    //background.setPrimitiveType(Quads);
    
    // Game States
    enum class State{GAME_OVER, LEVELING_UP, PAUSED, PLAYING};
    State state = State::GAME_OVER; // Initial State
    
    
    IntRect arena;
    
    
    int tilesize = createBackground(background, arena);
    
    Clock clock;
    
    
    // Setting View - Camera
    
    View mainView(FloatRect(0,0,resolution.x,resolution.y));
    
    
    // Creating Player
    Player player;
    
    // Creating Zombies
    //Zombie z1,z2,z3;
    
    Zombie *zombies=nullptr;
    
    int numZombies = 5;
    
    int numZombiesAlive;
    
    
    
    //Setting 4 screen pos.
    
    //background[0].position = Vector2f(100,150);
    //background[1].position = Vector2f(150,150);
    //background[2].position = Vector2f(150,200);    
    //background[3].position = Vector2f(100,200);
    //background[4].position = Vector2f(100,200);
    //background[5].position = Vector2f(150,200);
    //background[6].position = Vector2f(150,250);
    //background[7].position = Vector2f(100,250);
   
    
    //Texture Coordinates.
    
    //background[0].texCoords = Vector2f(0,150);
    //background[1].texCoords = Vector2f(50,150);
    //background[2].texCoords = Vector2f(50,200);    
    //background[3].texCoords = Vector2f(0,200);
    //background[4].texCoords = Vector2f(0,50);
    //background[5].texCoords = Vector2f(50,50);
    //background[6].texCoords = Vector2f(50,100);
    //background[7].texCoords = Vector2f(0,100);
    

    
    cout<<resolution.x<<" "<<resolution.y<<endl;
    RenderWindow window(VideoMode(resolution.x,resolution.y),"~~~ZOMBIE-ARENA~~~");
    
    
    
    //Main Game-Loop
    while(window.isOpen()){
        Event event;
        // Event loop
        while(window.pollEvent(event)){
            if(event.type==Event::Closed){
                window.close();
            }
            if(event.type==Event::KeyPressed){
            
                if(event.key.code==Keyboard::Return && state == State::PAUSED){
                   state=State::PLAYING;
                   clock.restart();
                }
                if(event.key.code==Keyboard::Return && state == State::PLAYING){
                   state=State::PAUSED;
                   
                }
                if(event.key.code==Keyboard::Return && state == State::GAME_OVER){
                   state=State::LEVELING_UP;
                   
                }
            }
        } // Event loop close
        
        // Handle play using WASD keys while playing
        if(state==State::PLAYING){
            if(Keyboard::isKeyPressed(Keyboard::W)){
                player.moveUp();
            }
            else{
                player.stopUp();
            }
            
            if(Keyboard::isKeyPressed(Keyboard::A)){
                player.moveLeft();
            }
            else{
                player.stopLeft();
            }
            
            if(Keyboard::isKeyPressed(Keyboard::S)){
                player.moveDown();
            }
            else{
                player.stopDown();
            }
            
            if(Keyboard::isKeyPressed(Keyboard::D)){
                player.moveRight();
            }
            else{
                player.stopRight();
            }
        }
        //State -> LEVELING_UP
        
        if(state==State::LEVELING_UP){ //Handle Leveling Up state
            if(event.key.code==Keyboard::Num1){
                state = State::PLAYING;
            }
            if(event.key.code==Keyboard::Num2){
                state = State::PLAYING;
            }
            if(event.key.code==Keyboard::Num3){
                state = State::PLAYING;
            }
            if(event.key.code==Keyboard::Num4){
                state = State::PLAYING;
            }
            if(event.key.code==Keyboard::Num5){
                state = State::PLAYING;
            }
            if(event.key.code==Keyboard::Num6){
                state = State::PLAYING;
            }
            if(state==State::PLAYING){
                wave++;
                arena.width=wave*500;
                arena.height=wave*500;
                arena.left=0;
                arena.top=0;
                int tileSize = createBackground(background, arena);
                player.spawn(arena, resolution, tileSize);
                //zombies[0].spawn(100,0,0,10);
                //zombies[1].spawn(0,100,1,3);
                //zombies[2].spawn(500,100,2,10);
                numZombies = wave * 2; 
                zombies = createHorde(numZombies, arena);
            }
            
        
        } // End of Leveling Up
        
        //$------------------------------Update Frame------------------------------$//
        
        if(state==State::PLAYING){
           
           Time dt = clock.restart();
           float dtAsSeconds = dt.asSeconds();
           mouseScreenPosition = Mouse::getPosition();
           mouseWorldPosition=window.mapPixelToCoords(Mouse::getPosition(),mainView);
           player.update(dtAsSeconds,mouseScreenPosition);
           spriteCrossHair.setPosition(mouseWorldPosition);
           mainView.setCenter(player.getCenter());
           //mainView.setCenter(Vector2f(arena.width/2,arena.height/2)); //Set Arena to Center
           Vector2f playerPosition(player.getCenter());
           for(int i=0; i < numZombies; i++){
              if(zombies[i].isAlive()){
                 zombies[i].update(dtAsSeconds,playerPosition);
              }
           }
        }
        
        
        
        
        // Handle players exit
        if(Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        } //End of Escape        
        
        
        
        //$------------------------------Update Scene------------------------------$//
        if(state==State::PLAYING){
              window.clear();
              window.setView(mainView);
              window.setMouseCursorVisible(false);
              window.draw(background,&textureBackground);
              window.draw(player.getSprite()); 
              //window.draw(zombies[0].getSprite());
              //window.draw(zombies[1].getSprite());
              for(int i = 0; i < numZombies; i++){
              window.draw(zombies[i].getSprite());
              }
              window.draw(spriteCrossHair);  
            }
        if(state==State::GAME_OVER){
                //code 
            }
            
        
        if(state==State::PAUSED){
               //code
            }
       
        if(state==State::LEVELING_UP){
              //code  
            }
        
        window.display();
           
    }// End of game loop    
    return 0;
  }
  
  // Game Functions
  
  
  int createBackground(VertexArray& rVA, IntRect arena){ //rVA -> alias - original arr-> background  || First param -> reference
    const int TILE_SIZE=50;
    const int TILE_TYPE=3;
    const int VERT_IN_QUAD=4;
    int worldWidth=arena.width/TILE_SIZE;
    int worldHeight=arena.height/TILE_SIZE;
    rVA.resize(worldWidth*worldHeight*VERT_IN_QUAD);
    rVA.setPrimitiveType(Quads);
    
    int cv=0;

    for(int w=0; w<worldWidth; w++){
        for(int h=0; h<worldHeight; h++){
           rVA[cv+0].position=Vector2f(w*TILE_SIZE,h*TILE_SIZE);
           rVA[cv+1].position=Vector2f((w*TILE_SIZE)+TILE_SIZE,(h*TILE_SIZE));
           rVA[cv+2].position=Vector2f((w*TILE_SIZE)+TILE_SIZE,(h*TILE_SIZE)+TILE_SIZE);
           rVA[cv+3].position=Vector2f((w*TILE_SIZE),(h*TILE_SIZE)+TILE_SIZE);
           if(h==0||w==0||h==worldHeight-1||w==worldWidth-1){ // wall
                rVA[cv+0].texCoords=Vector2f(0,(TILE_SIZE*TILE_TYPE)); // 0,150
                rVA[cv+1].texCoords=Vector2f(TILE_SIZE,(TILE_SIZE*TILE_TYPE)); // 50,150
                rVA[cv+2].texCoords=Vector2f(TILE_SIZE,(TILE_SIZE*TILE_TYPE)+TILE_SIZE); // 50,200
                rVA[cv+3].texCoords=Vector2f(0,(TILE_SIZE*TILE_TYPE)+TILE_SIZE);// 0,200
           }
           else {
                   srand((int)time(0)+h*w-h);
                   int mOrG = rand()%TILE_TYPE;
                   int vOffset = mOrG * TILE_SIZE;
                   rVA[cv+0].texCoords = Vector2f(0,vOffset);
                   rVA[cv+1].texCoords = Vector2f(TILE_SIZE,vOffset);
                   rVA[cv+2].texCoords = Vector2f(TILE_SIZE,vOffset+TILE_SIZE);
                   rVA[cv+3].texCoords = Vector2f(0,vOffset+TILE_SIZE);
          }
          // Position ready for the next vertices
          cv=cv+VERT_IN_QUAD;
             
       }
           
   }
   return TILE_SIZE;
   } // End of function
   
   
   Zombie *createHorde(int numZombies, IntRect arena){
   
   Zombie *zombies = new Zombie[numZombies];
   int maxX = arena.width - 20;
   int maxY = arena.height - 20;
   int minX = arena.left + 20;
   int minY = arena.top + 20;
   
   for(int i = 0; i < numZombies; i++){
       srand((int)time(0)*i);
       int side = (rand()%4);
       float x,y;
       switch(side){
           case 0:
              x = minX;
              y = (rand()%maxY-minY)+minY;
              break;
           case 1:
              x = minX;
              y = (rand()%maxY-minY)+minY;
              break;
           case 2:
              y = minY;
              x = (rand()%maxX-minX)+minX;
              break;
           case 3:
              y = minY;
              x = (rand()%maxX-minX)+minX;
              break;   
        }
        srand((int)time(0)*i*2);
        int type = (rand()%3);
        zombies[i].spawn(x,y,type,i);
    }
    return zombies;
 }
   
 
 
 
