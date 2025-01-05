
// SFMLSETUP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Compiler/Compiler.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Application.h"



int main()
{
	Application();
	

	/*
	
		std::string Input;
	std::getline(std::cin, Input);
	ASTNODE* node = NULL;
	try {
		node = Compiler::ParseExpression(Input);
		std::cout << Parser::NodetoString(node);
	}
	catch (ERROR_HANDLE handler) {

		for (int i = 0; i < handler.errorList.size(); i++) {
			std::cout << handler.errorList[i].Message << "\n";
		}
		return -1;
	}

	int width = 512;
	int height = 512;
	sf::RenderWindow window(sf::VideoMode(width, height), "Graphing Window");

	sf::Texture texture;
	texture.create(width, height);
	sf::Sprite sprite;
	sprite.setTexture(texture);


	sf::Font font;
	if (!font.loadFromFile("ti-calculator-font.ttf")) 
	{
		throw;
	};
	sf::Text numberRanges;
	numberRanges.setFont(font);
	sf::Shader GraphingShader;

	std::string GraphingShaderText = "";
	std::ifstream myfile("DefaultGrapher.frag");
	if (myfile.is_open())
	{
		std::string buff;
		while (std::getline(myfile, buff)) {
			GraphingShaderText += buff + "\n";
		}
		myfile.close();
	}
	float a = 1;
	GraphingShaderText += Compiler::GenerateGPUFunction(node, "SampleFunction");
	std::cout << GraphingShaderText;
	GraphingShader.loadFromMemory(GraphingShaderText, sf::Shader::Fragment);

	//10^zoomfactor
	float ZoomFactor = 0;
	sf::Vector2f Transform = sf::Vector2f(0,0);

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized) {
				window.setSize(sf::Vector2u(width, height));
			}
			if (event.type == sf::Event::MouseWheelScrolled) {
				ZoomFactor += event.mouseWheelScroll.delta * 0.1f;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			a += 0.001;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			a -= 0.001;
		}
		GraphingShader.setUniform("ZoomFactor", ZoomFactor);
		GraphingShader.setUniform("Transform", Transform);
		GraphingShader.setUniform("a", a);
		GraphingShader.setUniform("width", width);
		GraphingShader.setUniform("height", height);
		window.clear();
		window.draw(sprite, &GraphingShader);
		window.display();
	}

	
	*/

	//((x-4)^2+y^2-16)*((x+4)^2+y^2-16)*(16*x^2+(y-10)^2-100) = 0
}