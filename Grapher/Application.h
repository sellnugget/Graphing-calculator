#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <float.h>
#include <stdio.h>
#include <ttmath.h>
#include "Compiler/Compiler.h"
#include "NodeExecutor.h"
#include "Compiler/GS_COMPILER.h"
#include <fstream>
class Application
{
public:
	sf::RenderWindow window;
	sf::RenderWindow UIwindow;
	sf::RenderTexture UI;
	sf::RenderTexture Background;
	sf::RenderTexture Graph;
	Application();
	void MainUpdate();
	void DrawGraph();
	void DrawBackground();
	void DrawUI();
	void EventHandler(sf::Event event);
private:

	sf::View view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(2.0, 2.0));
	float Zoom = 0;


	void DrawLine(const sf::Vector2f& start, const sf::Vector2f& end, float thickness, sf::Color color, sf::RenderTexture& texture);
	sf::Shader GraphingShader;
	sf::Vector2i LastMousePos;
	sf::Font textFont;
	sf::Text text;
	sf::Text InputBox;
	int Cursor;
	std::string Equation;
	std::string ActiveExecute;
	NodeExecutor executer;
	ASTNODE* equationNode = NULL;
};

