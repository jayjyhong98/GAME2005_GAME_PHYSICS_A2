#include "PlayScene.h"
#include "Game.h"
#include "Util.h"
#include "EventManager.h"

#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

#define FLOOR 470

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("background", 0, 0, 0, 255, false);

	GUI_Function();

	// Drawing the ramp
	Util::DrawLine({ m_pRamp->getPosition() }, { m_pRamp->getEndPoint(), FLOOR }, {1,0,0,0}); // bottom
	Util::DrawLine({ m_pRamp->getPosition().x, FLOOR - m_pRamp->getRise() }, { m_pRamp->getEndPoint(), FLOOR }, {1,0,0,0}); // ramp
	Util::DrawLine({ m_pRamp->getPosition().x, FLOOR - m_pRamp->getRise() }, { m_pRamp->getPosition() }, {1,0,0,0}); // side

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	std::string labelText = "";

	labelText = "RAMP: Rise(m) = " + std::to_string(m_pRamp->getRise() / 100.0f) + ",  Run(m) = " + std::to_string(m_pRamp->getRun() / 100.0f);
	m_pRampLabel->setText(labelText);

	labelText = "BOX: Net Force(J) = " + std::to_string(m_pBall->getNetForce());
	m_pNetForceLabel->setText(labelText);

	labelText = "Acceleration(m/s^2) = " + std::to_string(m_pBall->getAccelTotal());
	m_pAccelLabel->setText(labelText);
<<<<<<< Updated upstream
=======

	labelText = "Distance(m)= " + std::to_string((m_pBall->getTransform()->position.x - m_pRamp->getPosition().x) / 100.0f);
	m_pDistanceLabel->setText(labelText);

	labelText = "Velocity.x(m/s) = " + std::to_string(m_pBall->getRigidBody()->velocity.x);
	m_pVelocityLabel->setText(labelText);

	labelText = "Mass(kg) = " + std::to_string(m_pBall->getMass());
	m_pMassLabel->setText(labelText);
>>>>>>> Stashed changes
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	m_pBall->stopMoving();

	if (EventManager::Instance().getMouseButton(RIGHT))	// set up start by click here!
	{
	}
	// Player movement by keyboard
	//if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A) || EventManager::Instance().isKeyDown(SDL_SCANCODE_D) ||
	//	EventManager::Instance().isKeyDown(SDL_SCANCODE_W) || EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	//{
	//	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A)) // Check x in put and y input seperately
	//	{
	//		m_pPlayer->moveLeft();
	//	}
	//	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	//	{
	//		m_pPlayer->moveRight();
	//	}
	//	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	//	{
	//		m_pPlayer->moveUp();
	//	}
	//	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	//	{
	//		m_pPlayer->moveDown();
	//	}
	//}
	//else {
	//	m_pPlayer->stopMoving();
	//}
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void PlayScene::start()
{
	// Background Sprite
	TextureManager::Instance()->load("../Assets/textures/background.png", "background");

	// Set GUI Title
	m_guiTitle = "Play Scene";

	// Ramp Object
	m_pRamp = new Ramp();

	// Trooper Sprite
	m_pTrooper = new Trooper();
	addChild(m_pTrooper);

	// Projectile Sprite
	m_pBall = new Ball();
	addChild(m_pBall);

	// Wookie Sprite
	m_pWookie = new Wookie();
	addChild(m_pWookie);

	// Labels
	const SDL_Color red = { 255, 0, 0, 255 };

	m_pScaleLabel = new Label("Scale = 100PPM         Assuming gravity is 9.8m/s^2", "Consolas", 15, red, glm::vec2(250.0f, 10.0f));
	m_pScaleLabel->setParent(this);
	addChild(m_pScaleLabel);

	// TO DO LABELS!!!

	m_pRampLabel = new Label("Ramp", "Consolas", 20, red, glm::vec2(250.0f, 40.0f));
	m_pRampLabel->setParent(this);
	addChild(m_pRampLabel);

	m_pNetForceLabel = new Label("Initial Velocity", "Consolas", 20, red, glm::vec2(250.0f, 70.0f));
	m_pNetForceLabel->setParent(this);
	addChild(m_pNetForceLabel);

	m_pAccelLabel = new Label("Acceleration", "Consolas", 20, red, glm::vec2(250.0f, 100.0f));
	m_pAccelLabel->setParent(this);
	addChild(m_pAccelLabel);
<<<<<<< Updated upstream
=======

	m_pVelocityLabel = new Label("Velocity", "Consolas", 20, red, glm::vec2(250.0f, 130.0f));
	m_pVelocityLabel->setParent(this);
	addChild(m_pVelocityLabel);

	m_pDistanceLabel = new Label("Distance", "Consolas", 20, red, glm::vec2(250.0f, 160.0f));
	m_pDistanceLabel->setParent(this);
	addChild(m_pDistanceLabel);

	m_pMassLabel = new Label("Mass", "Consolas", 20, red, glm::vec2(250.0f, 190.0f));
	m_pMassLabel->setParent(this);
	addChild(m_pMassLabel);
>>>>>>> Stashed changes
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	ImGui::Begin("Scenerio Adjuster", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	//if (ImGui::Button("Set to Original Problem <Question 1.a>"))
	//{
	//	m_pBall->setState(0);
	//	m_pWookie->getTransform()->position.x = 275;
	//	m_pBall->getTransform()->position.x = m_pWookie->getTransform()->position.x;
	//	m_pBall->getTransform()->position.y = m_pWookie->getTransform()->position.y;
	//}

	//if (ImGui::Button("Set to Furthest Distance <Question 1.b>"))
	//{
	//	m_pBall->setState(1);
	//	m_pBall->getTransform()->position.x = m_pWookie->getTransform()->position.x;
	//	m_pBall->getTransform()->position.y = m_pWookie->getTransform()->position.y;
	//}

	ImGui::Separator();

	static int xPosition = 150;
	if (ImGui::SliderInt("Position X", &xPosition, 0, 700))
	{
	}
	static int xRun = 400.0f;
	if (ImGui::SliderInt("Run (cm)", &xRun, 0, 700))
	{
	}
	static int yRise = 300.0f;
	if (ImGui::SliderInt("Rise (cm)", &yRise, 0, 500))
	{
	}
<<<<<<< Updated upstream
	static float weight = 12.8f;
	if (ImGui::SliderFloat("Box Weight", &weight, 1.0f, 50.0f))
=======
	static float mass = 12.8f;
	if (ImGui::SliderFloat("Box Weight (kg)", &mass, 1.0f, 50.0f))
>>>>>>> Stashed changes
	{
	}
	static float friction = 0.0f;
	if (ImGui::SliderFloat("Coefficient of Friction", &friction, 0.0f, 1.0f))
	{
	}

	if (ImGui::Button("Set"))
	{
		m_pRamp->setPositionX(xPosition);
		m_pRamp->setRun(xRun);
		m_pRamp->setRise(yRise);
		m_pRamp->refresh();

		m_pBall->setWeight(weight);
		m_pBall->setf_angle(m_pRamp->getAngle());
		m_pBall->setFriction(friction);
		m_pBall->getTransform()->position.x = m_pRamp->getPosition().x;
		m_pBall->getTransform()->position.y = m_pRamp->getPosition().y - m_pRamp->getRise();

		m_pBall->setState(0);
	}
	//if (ImGui::Button("Throw to Trooper Based off Angle"))
	//{
	//	m_pBall->setf_angle(yRise);
	//	m_pBall->setf_meter(m_pTrooper->getTransform()->position.x - m_pWookie->getTransform()->position.x);
	//	m_pBall->setState(3);
	//	m_pBall->getTransform()->position.x = m_pWookie->getTransform()->position.x;
	//	m_pBall->getTransform()->position.y = m_pWookie->getTransform()->position.y;
	//}

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
