#include "QuestiaDev/Application.h"

Application::Application():
	mStatisticsUpdateTime(sf::Time::Zero)
	, mStatisticsFramesCount(0)
	, saveFile()
	, inputBuffer()
{
	Data_Desktop::getInstance().changeFont(saveFile.getFont());

	switch(saveFile.getWindowMode())
	{
	case 0:
		window_main.create(sf::VideoMode(1920, 1080), "Questia", sf::Style::Fullscreen);
		break;
	case 1:
		window_main.create(sf::VideoMode(1280, 720), "Questia", sf::Style::Default);
		break;
	default:
		window_main.create(sf::VideoMode(1920, 1080), "Questia", sf::Style::Default);
		break;
	}

	std::cout << "--------------------" << std::endl;
	std::cout << "  Questia Executed  " << std::endl;
	std::cout << "--------------------" << std::endl;
}

void Application::run()
{
	Data_Desktop::getInstance().setDesktopResolution(
	    sf::Vector2i(window_main.getSize().x, window_main.getSize().y), window_main.getPosition());

	if(saveFile.getFps() == 0)
	{
		window_main.setVerticalSyncEnabled(true);
	}
	else if(saveFile.getFps() == -1)
	{
		window_main.setFramerateLimit(100000);
		window_main.setVerticalSyncEnabled(false);
	}
	else
	{
		window_main.setFramerateLimit(saveFile.getFps());
		window_main.setVerticalSyncEnabled(false);
	}

	sf::View beginningView;
	beginningView.setSize(1920, 1080);
	beginningView.setCenter(960, 540);
	window_main.setView(beginningView);

	StateManager::getInstance().createState(new State_Transition(window_main, 1));

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while(window_main.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while(timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;

			processEvents();
			update(timePerFrame);
			if(!window_main.isOpen())
			{
				return;
			}
		}
		render();
		updateStatistics(elapsedTime);
	}
}

void Application::processEvents()
{
	sf::Event event;

	while(window_main.pollEvent(event))
	{
		switch(event.type)
		{
		case sf::Event::TextEntered:
			{
				//TODO remove, depreciated
				if(event.text.unicode <= 126 && event.text.unicode >= 32 || event.text.unicode == 8)
				{
					Data_Desktop::getInstance().setMostRecentChar(static_cast<char>(event.text.unicode));
				}
				
				inputBuffer.enqueue(event.text.unicode);
			}
			break;
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::MouseWheelMoved:
			Data_Desktop::getInstance().setMouseWheelDelta(event.mouseWheel.delta);
			break;
		case sf::Event::Closed:
			window_main.close();
			break;
		case sf::Event::Resized:
			Data_Desktop::getInstance().setDesktopResolution(
			    sf::Vector2i(window_main.getSize().x, window_main.getSize().y), window_main.getPosition());
			break;
		case sf::Event::MouseButtonReleased:
			Data_Desktop::getInstance().setMouseReleased(true);
			break;
		case sf::Event::MouseButtonPressed:
			Data_Desktop::getInstance().setMousePressed(true);
			break;
		default:
			break;
		}
	}
}

void Application::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	StateManager::getInstance().processImputState(key, isPressed);
}

void Application::update(sf::Time elapsedTime)
{
	StateManager::getInstance().updateState(elapsedTime);
}

void Application::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsFramesCount += 1;

	if(mStatisticsUpdateTime >= sf::seconds(1))
	{
		Data_Desktop::getInstance().set_FPS(mStatisticsFramesCount);

		mStatisticsUpdateTime -= sf::seconds(1);
		mStatisticsFramesCount = 0;
	}
}

void Application::render()
{
	window_main.clear(sf::Color::White);
	StateManager::getInstance().displayTexturesState();
	window_main.display();
}

Application::~Application()
{
	StateManager::getInstance().deleteState();
	std::cout << "--------------------" << std::endl;
	std::cout << " Questia Terminated " << std::endl;
	std::cout << "--------------------" << std::endl;
}
