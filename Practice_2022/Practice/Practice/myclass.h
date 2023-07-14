#ifndef MYCLASS_H_
#define MYCLASS_H_

class User_Sprite
{
public:
	int x, y = 0;
	sf::String File;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	User_Sprite(sf::String F, int X, int Y)
	{
		File = F;
		x = X; y = Y;
		image.loadFromFile("images/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setPosition(x, y);
	}

	~User_Sprite() {};
};

#endif /* MYCLASS_H_*/
