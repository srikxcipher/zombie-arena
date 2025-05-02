#include<iostream>
#include<SFML/Graphics.hpp>

using namespace sf;
using namespace std;
int createBackground(VertexArray& rVA, IntRect arena);
int main()
{
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    
    Texture textureBackground;
    textureBackground.loadFromFile("res/graphics/background_sheet.png");
    
    VertexArray background;
    //background.resize(10*10*4);
    //background.setPrimitiveType(Quads);
    
    IntRect arena;
    arena.width=500;
    arena.height=500;
    
    arena.left=0;
    arena.top=0;
    
    int tilesize = createBackground(background, arena);
    
    
    
    // Setting View
    
    View mainView(FloatRect(0,0,resolution.x,resolution.y));
    
    
    
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
    
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type==Event::Closed){
                window.close();
            }
        } // Event loop close
        

        // Handle players exit
        if(Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        } //End of Escape        
        
        //$------------------------------Update Frame------------------------------$//
        
        
        
        //$------------------------------Update Scene------------------------------$//
        window.clear();
        
        //Drawing Vertex Array
        window.draw(background,&textureBackground);
        
        //Set View
        window.setView(mainView);
        mainView.setCenter(Vector2f(arena.width/2,arena.height/2)); //Set Arena to Center
        window.display();
        
    }// End of game loop
        
    return 0;
  }
  int createBackground(VertexArray& rVA, IntRect arena){ //rVA -> alias - original arr-> background  
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
          
          cv=cv+VERT_IN_QUAD;
             
       }
           
   }
   return TILE_SIZE;
   } // End of function
