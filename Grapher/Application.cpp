#include "Application.h"
Application::Application()
{

	std::string a = "fn run(var a, var b){ var a = 2; }";

	GS_COMPILER compiler;
	ASTNODE* node = compiler.Compile(a);
	std::cout << Parser::NodetoString(node, 0);

	window.create(sf::VideoMode(1080, 1080), "Grapher");
	UIwindow.create(sf::VideoMode(640, 640), "UI");
	UI.create(1080, 1080);
	Background.create(1080, 1080);
	Graph.create(1080, 1080);


	

	sf::View DefaultView;

	

	if (!textFont.loadFromFile("ARIAL.TTF")) {
		throw;
	}
	
	text.setFont(textFont);
	InputBox.setFont(textFont);

	sf::Clock clock;
	float LastTime = 0;


	while (true) {
		float currentTime = clock.getElapsedTime().asSeconds();
		float fps = 1.f / (currentTime - LastTime);
		LastTime = currentTime;
		if (window.isOpen()) {
			window.setTitle("Grapher fps:" + std::to_string((int)fps));
			sf::Event event;
			while (window.pollEvent(event)) {
				if (window.hasFocus()) {
					EventHandler(event);
				}
			}
			MainUpdate();
		}
		if (UIwindow.isOpen()) {
			UIwindow.setTitle("FPS " + std::to_string((int)fps));
			sf::Event event;
			while (UIwindow.pollEvent(event)) {
				if (UIwindow.hasFocus()) {
				
				}
			}
		}

	}
}


void Application::MainUpdate()
{
	
	UI.clear(sf::Color::Transparent);
	Background.clear(sf::Color::White);
	Graph.clear(sf::Color::Transparent);
	window.clear(sf::Color::White);

	DrawGraph();
	DrawBackground();
	DrawUI();

	
	sf::Sprite SpriteTexture;



	Background.display();
	Graph.display();
	UI.display();

	SpriteTexture.setTexture(Background.getTexture());
	window.draw(SpriteTexture);
	SpriteTexture.setTexture(Graph.getTexture());
	window.draw(SpriteTexture);
	SpriteTexture.setTexture(UI.getTexture());
	window.draw(SpriteTexture);

	window.display();

	if (window.hasFocus()) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			sf::Vector2f offset = Background.mapPixelToCoords(LastMousePos) - Background.mapPixelToCoords(sf::Mouse::getPosition());


			view.setCenter(view.getCenter() + offset);

		}

	}

	view.setSize(sf::Vector2f(pow(10, Zoom), -pow(10, Zoom)));
	LastMousePos = sf::Mouse::getPosition();
	Graph.setView(view);
	Background.setView(view);
}

void Application::DrawGraph()
{


	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(view.getSize().x, view.getSize().y));
	shape.setPosition(sf::Vector2f(view.getCenter() - (view.getSize()/2.0f)));
	GraphingShader.setUniform("ZoomFactor", Zoom);
	sf::Vector2f offset = view.getCenter();
	GraphingShader.setUniform("Transform", offset);
	GraphingShader.setUniform("width", (int)window.getSize().x);
	GraphingShader.setUniform("height", (int)window.getSize().y);
	GraphingShader.setUniform("ViewSize", view.getSize());
	Graph.draw(shape, &GraphingShader);
	/*
	sf::Vector2f Prev;
	float Angle = 0;
	int Subpixel = 1;
	for (int i = 0; i < window.getSize().x * Subpixel; i++) {

		ASTNODE* node = new ASTNODE();
		float OneUnit = Graph.mapPixelToCoords(sf::Vector2i(0, 0)).x - Graph.mapPixelToCoords(sf::Vector2i(1, 0)).x;;
		float pixelcord = Graph.mapPixelToCoords(sf::Vector2i(i / Subpixel, 0)).x;
		float X = pixelcord + OneUnit * (i % Subpixel)/Subpixel;

		node->tokens.push_back({ Token::CONST, std::to_string(X) });
		executer.Identifiers["x"] = node;
		float Y = executer.ExecuteNode(equationNode);
		if (Y == NAN) {
			std::cout << "Compile error\n";
			break;
		}
		sf::Vector2f angle = sf::Vector2f(X, Y) - Prev;



		if (i > 0 && abs(Angle - atanf(angle.y / angle.x)) < (3.14159 / 2.0)) {
			DrawLine(Prev, sf::Vector2f(X, Y), pow(10, Zoom - 2) / 2, sf::Color::Red, Graph);
		}
		Prev = sf::Vector2f(X, Y);
		Angle = atanf(angle.y / angle.x);

	}
	
	
	*/
	
}

void Application::DrawBackground()
{
	//which one is best nearest 10^Zoom or (10^Zoom)/4 or (10^Zoom)/2 
	float Range = pow(10, ceil(Zoom));
	if (abs(Range / 2 - pow(10, Zoom)) < abs(Range - pow(10, Zoom))) {
		Range /= 2;
	}
	if (abs(Range / 2 - pow(10, Zoom)) < abs(Range - pow(10, Zoom))) {
		Range /= 2;
	}

	sf::VertexArray lines(sf::LinesStrip, 2);

	float offsetx = round(view.getCenter().x / Range) * Range;
	float offsety = round(view.getCenter().y / Range) * Range;

	Range *= 2;
	for (float i = -Range; i < Range; i += Range / (25 * 2)) {


		lines[0].color = sf::Color(256 / 4, 256 / 4, 256 / 4);

		lines[0].position = sf::Vector2f(-Range + offsetx, i + offsety);
		lines[1].position = sf::Vector2f(Range + offsetx, i + offsety);
		Background.draw(lines);

		lines[0].position = sf::Vector2f(i + offsetx, Range + offsety);
		lines[1].position = sf::Vector2f(i + offsetx, -Range + offsety);
		Background.draw(lines);
	}
	for (float i = -Range; i <= Range; i += Range / (5 * 2)) {

		DrawLine(sf::Vector2f(-Range + offsetx, i + offsety), sf::Vector2f(Range + offsetx, i + offsety), pow(10, Zoom - 2) * 0.5, sf::Color(256 / 2, 256 / 2, 256 / 2), Background);
		DrawLine(sf::Vector2f(i + offsetx, Range + offsety), sf::Vector2f(i + offsetx, -Range + offsety), pow(10, Zoom - 2) * 0.5, sf::Color(256 / 2, 256 / 2, 256 / 2), Background);


		std::stringstream stream;



		stream << std::setprecision(5) << i + offsetx;

		text.setFillColor(sf::Color::Black);
		text.setScale(view.getSize() / 1024.0f);
		sf::Vector2f charSize = (float)text.getCharacterSize() * (view.getSize() / 1024.0f);
		if (abs(i + offsetx) < Range / (5 * 2) / 2.0f) {
			text.setString("0");
			text.setPosition(sf::Vector2f(i + offsetx - (charSize.x), 0));
		}
		else {
			text.setString(stream.str());
			text.setPosition(sf::Vector2f(i + offsetx - (stream.str().size() / 4.0f * charSize.x), 0));
		}


		Background.draw(text);
		stream.str("");
		stream << std::setprecision(5) << i + offsety;
		if (abs(i + offsety) >= Range / (5 * 2) / 2.0f) {
			text.setString(stream.str());
			text.setPosition(sf::Vector2f(-(stream.str().size() / 2.0f * charSize.x), i + offsety));
			Background.draw(text);
			stream.clear();
		}





	}

	DrawLine(sf::Vector2f(-Range + offsetx, 0), sf::Vector2f(Range + offsetx, 0), pow(10, Zoom - 2), sf::Color::Black, Background);
	DrawLine(sf::Vector2f(0, -Range + offsety), sf::Vector2f(0, Range + offsety), pow(10, Zoom - 2), sf::Color::Black, Background);
}

void Application::DrawUI()
{
	InputBox.setString(Equation);
	InputBox.setColor(sf::Color::Black);
	InputBox.scale(sf::Vector2f(1, 1));
	UI.draw(InputBox);
}


uint64_t count_representable_numbers(float a, float b) {
	// Ensure a is less than or equal to b
	if (a > b) {
		double temp = a;
		a = b;
		b = temp;
	}

	unsigned long long count = 0;
	float fa = (float)a;
	float fb = (float)b;
	unsigned int ua, ub;

	memcpy(&ua, &fa, sizeof(float));
	memcpy(&ub, &fb, sizeof(float));

	// Handle the case where range includes zero
	if (fa < 0 && fb > 0) {
		fb = -1.175494351E-38;
		return count_representable_numbers(nextafterf(0, fb), fb) + count_representable_numbers(fa, nextafterf(0, fa));
	}
	if (ua > ub) {
		unsigned int temp = ua;
		ua = ub;
		ub = temp;
	}
	count = ub - ua;
	return count;
}
void Application::EventHandler(sf::Event event)
{
	if (event.type == sf::Event::Closed)
		window.close();
	if (event.type == sf::Event::Resized) {

	}
	if (event.type == sf::Event::MouseWheelScrolled) {

		float zoomSpeed = 0.05;
	
		sf::Vector2f prev = view.getCenter();


		
		uint64_t Precision = count_representable_numbers(view.getCenter().x - view.getSize().x / 2, view.getCenter().x + view.getSize().x / 2) + 1;
		
		if ((Precision >= 1000 && Zoom > -18.5) || (event.mouseWheelScroll.delta * zoomSpeed) > 0) {

			Zoom += event.mouseWheelScroll.delta * zoomSpeed;
			std::cout << Precision << "\n";

			view.setSize(sf::Vector2f(pow(10, Zoom), -pow(10, Zoom)));
			float zoomfactor = (float)(pow(10, Zoom) / pow(10, Zoom - event.mouseWheelScroll.delta * zoomSpeed));

			sf::Vector2f newCenter = Background.mapPixelToCoords(sf::Mouse::getPosition(window)) - (Background.mapPixelToCoords(sf::Mouse::getPosition(window)) - view.getCenter()) * zoomfactor;
			view.setCenter(newCenter);

			Graph.setView(view);
			Background.setView(view);

		}
	}
	if (event.type == sf::Event::TextEntered) {
		char key = event.text.unicode ;
		if (key == 8) {
			Equation = Equation.substr(0, Equation.size() - 1);
		}
		else if (key == 13) {
			ASTNODE* equation = Compiler::ParseExpression(Equation);
			if (equation != NULL) {
				std::cout << "AST:" << Parser::NodetoString(equation);
				ActiveExecute = Equation;
				delete equationNode;
				equationNode = equation;

			}
			else {
				delete equation;
			}
			std::cout << Compiler::error_handle.GetErrorList();

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
			GraphingShaderText += Compiler::GenerateGPUFunction(equation, "SampleFunction");
			std::cout << GraphingShaderText;
			GraphingShader.loadFromMemory(GraphingShaderText, sf::Shader::Fragment);
			myfile.close();
		}
		else {
			Equation += static_cast<char>(event.text.unicode);
		}
	
		
	}
}

void Application::DrawLine(const sf::Vector2f& start, const sf::Vector2f& end, float thickness, sf::Color color, sf::RenderTexture& texture)
{
	sf::Vector2f direction = end - start;
	float length = std::hypot(direction.x, direction.y);

	sf::RectangleShape line(sf::Vector2f(length, thickness));
	line.setFillColor(color);
	line.setOrigin(0, thickness / 2);
	line.setPosition(start);
	line.setRotation(std::atan2(direction.y, direction.x) * 180 / 3.14159265358979323846);
	texture.draw(line);
}
