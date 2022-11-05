#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <string >
#include <cstdlib>

 using namespace std ;
 using namespace sf ;

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "7MO2A GAME");
    // frame rate
    app.setFramerateLimit(60);
    // create background image
        sf::Texture BackgroundTexture;
      sf::Sprite background;
      sf::Vector2u TextureSize;  //Added to store texture size.
      sf::Vector2u WindowSize;   //Added to store window size.

      if(!BackgroundTexture.loadFromFile("images/gameBackground.jpg"))
      {
        return -1;
      }
      else
      {
        TextureSize = BackgroundTexture.getSize(); //Get size of texture.
        WindowSize = app.getSize();             //Get size of window.

        float ScaleX = (float) WindowSize.x / TextureSize.x;
        float ScaleY = (float) WindowSize.y / TextureSize.y;     //Calculate scale.

        background.setTexture(BackgroundTexture);
        background.setScale(ScaleX, ScaleY);      //Set scale.
      }
      //create textures and sprites
        Texture candy1 ,candy2 , candy3 , water , milk , charImg;
        candy1.loadFromFile("candy1.png");
        candy2.loadFromFile("candy2.png");
        candy3.loadFromFile("candy3.png");
        water.loadFromFile("water.png");
        milk.loadFromFile("milk.png");
        charImg.loadFromFile("CandyChar.png");
        charImg.setSmooth(true);

        Sprite candy1Sprite , candy2Sprite ,candy3Sprite ,waterSprite,milkSprite , charImgSprite;
        candy1Sprite.setTexture(candy1);
        candy2Sprite.setTexture(candy2);
        candy3Sprite.setTexture(candy3);
        waterSprite.setTexture(water);
        milkSprite.setTexture(milk);

        Sprite candies [5] = {candy1Sprite , candy2Sprite ,candy3Sprite ,waterSprite,milkSprite};

        //create array for random candy ;
        struct point {
            Sprite sprite ;
            int x ;
            int y ;
        };

        point candies_xy [5] ;
        int xCandy = 170; //space between candies
        int yCandy = 0 ;
        float dyCandy = 4 ;

        for(int i=0 ; i<5 ; i++){
            candies_xy[i].sprite = candies[i];
            if(i < 1){
                candies_xy[i].x = 30 ;
                candies_xy[i].y = 0 ;
            }
            else{
                candies_xy[i].x = candies_xy[i-1].x + xCandy ;
                candies_xy[i].y = 0 ;
            }
        }
        //create character sprite
        int xP = 1;
        int yP = 0;
        int xChar = 350 ;
        int yChar = 430 ;
        float dx = 6;
        float scaleX = 0.7 ;
        float scaleY = 0.7 ;
        charImgSprite.setTexture(charImg);
        charImgSprite.setTextureRect(IntRect(xP,yP,100,199));
        charImgSprite.setScale(scaleX,scaleY);
        charImgSprite.setPosition(xChar , yChar);
        // Providing a seed value to generate rand value
        srand((unsigned) time(NULL));
        int random1 ,random2 ;
        int index =0 ;
        int DrinkCounter = 0;

        // Text for counter and winning
        Font font1 ;
        font1.loadFromFile("Halloween.ttf");
        Text counterValue ,counter , winning ;
        counterValue.setFont(font1) ;
        counter.setFont(font1) ;
        winning.setFont(font1) ;
        winning.setCharacterSize(50);
        winning.setColor(Color(200 ,10,10));
        counter.setColor(Color(0 ,0,10));
        counterValue.setColor(Color(0 ,0,10));
        counter.setString("You Drank :");
        counter.setPosition(600 , 400);
        counterValue.setString(to_string(DrinkCounter));
        counterValue.setPosition(620 , 450);
        winning.setString("Great Work ... You are Strong Now !!");
        winning.setPosition(50 , 300);



	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed){
                app.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                // left key is pressed: move our character
                xP+=110;
                if(xP > 850){
                    xP =0 ;
                }
                charImgSprite.setTextureRect(IntRect(xP,yP,100,199));
                charImgSprite.setScale(-scaleX,scaleY);
                xChar -= dx ;
                charImgSprite.setPosition(xChar , yChar);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                // Right key is pressed: move our character
                xP+=110;
                if(xP > 850){
                    xP =0 ;
                }
                charImgSprite.setTextureRect(IntRect(xP,yP,100,199));
                charImgSprite.setScale(scaleX,scaleY);
                xChar += dx ;
                charImgSprite.setPosition(xChar , yChar);
            }
        }
        /*logic code here */
        //touching milk and water condition
        //problem is touching for at most once
        if ((abs(charImgSprite.getPosition().y - candies_xy[3].y)<= 50) && (abs(charImgSprite.getPosition().x - candies_xy[3].x)<= 50)
            || (abs(charImgSprite.getPosition().y - candies_xy[4].y)<= 50) && (abs(charImgSprite.getPosition().x - candies_xy[4].x)<= 50)){
            scaleX = 0.8 ;
            scaleY = 0.9 ;
                dx = 7 ;
                DrinkCounter++ ;
                counterValue.setString(to_string(DrinkCounter));

        }
        else if (charImgSprite.getGlobalBounds().intersects(candies_xy[0].sprite.getGlobalBounds()) ||
                    charImgSprite.getGlobalBounds().intersects(candies_xy[1].sprite.getGlobalBounds()) ||
                 charImgSprite.getGlobalBounds().intersects(candies_xy[2].sprite.getGlobalBounds())){
                scaleX = 0.7 ;
                scaleY = 0.5 ;
                dx = 3 ;
        }
        if(candies_xy[index].sprite.getPosition().y > 500){
                random1 = rand() % 5 ; // for selecting sprites
                random2 = rand() % 700 ; // for their x locations
                index = random1 ;
                candies_xy[index].x = random2;
                for(int i=0 ;i < 5 ; i++){
                        candies_xy[i].y = 0 ;
                    }
        }
        candies_xy[index].y +=dyCandy ;
        candies_xy[index].sprite.setPosition(candies_xy[index].x , (candies_xy[index].y));

        // Clear screen
        app.clear();
        app.draw(background);
        app.draw(candies_xy[index].sprite);
        app.draw(charImgSprite);
        app.draw(counterValue) ;
        app.draw(counter) ;
        if(DrinkCounter > 200){
            app.draw(winning) ;
        }
        app.display();
    }

    return EXIT_SUCCESS;
}
