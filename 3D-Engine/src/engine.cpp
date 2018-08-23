#include "Engine.h"

using namespace entity;
using namespace component;
int main()
{
//========================================================================
// Create Objects (Camera is a singular entity)
//========================================================================

	Window window("3D-Engine", 960, 540);

	m_Renderer = new ForwardRenderer();
	Scene* scene1 = new Scene();
	
	
	Material* material1 = new Material(Shader::FromFile("Scene", "shaders/scene.shader"));
	Material* material2 = new Material(Shader::FromFile("Default", "shaders/default.shader"));
	Material* material3 = new Material(Shader::FromFile("Color", "shaders/Color.shader"));
	Material* material4 = new Material(Shader::FromFile("Textured", "shaders/TexturedCube.shader"));
	
	VertexArray* va = CreateQuad(0, 0, 20, 20);
	IndexBuffer* ib = new IndexBuffer(new uint[6]{ 0,1,2,2,3,0 }, 6);

	m_CubeMaterial = new MaterialInstance(material1);
	m_PlantMaterial = new MaterialInstance(material1);
	m_DefaultMaterial = new MaterialInstance(material2);


	m_Cube = new Entity();
	Model* cubeModel = new Model("objects/cube.obj", m_CubeMaterial);
	m_Cube->AddComponent(new MeshComponent(cubeModel->GetMesh()));
	m_Cube->AddComponent(new TransformComponent(glm::translate(glm::mat4(), glm::vec3(4, 0, 0))));


	glm::mat4 modelMatrix(1.0);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-4, -2, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.3, 0.3));
	m_HousePlant = new Entity();
	Model* houseplant = new Model("objects/eb_house_plant_01.obj", m_PlantMaterial);
	m_HousePlant->AddComponent(new MeshComponent(houseplant->GetMesh()));
	m_HousePlant->AddComponent(new TransformComponent(modelMatrix));


	glm::mat4 planeMatrix(1.0);
	planeMatrix = glm::translate(planeMatrix, glm::vec3(-10, -2.2, -10));
	planeMatrix = glm::rotate(planeMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));
	m_Quad = new Entity();
	Mesh* plane = new Mesh(va, ib, m_DefaultMaterial);
	m_Quad->AddComponent(new MeshComponent(plane));
	m_Quad->AddComponent(new TransformComponent(planeMatrix));
	
	
	scene1->Add(m_Cube);
	scene1->Add(m_HousePlant);
	scene1->Add(m_Quad);

	//material2->SetUniform("pr_matrix", glm::perspective(65.0f, 16.0f / 9.0f, 0.1f, 1000.0f));
	//material1->SetUniform("vw_matrix", glm::translate(glm::mat4(), glm::vec3(0, 0, -10.0f)));


	Texture crateTexture("textures/crate.bmp");
	Texture sandTexture("textures/Sand_Texture.bmp");

	//m_DefaultMaterial->SetTexture("Crate",&crateTexture);



	InputHandler inputHandler(window);

//========================================================================
// Global vars for update loop
//========================================================================

	float lastTime = glfwGetTime();
	auto nbFrames = 0;
	auto FPSToggle = false;
	auto deltaTime = 0.0f;	// Time between current frame and last frame
	auto lastFrame = 0.0f; // Time of last frame

	double mouseX = 0;
	double mouseY = 0;
	window.GetMousePosition(mouseX, mouseY);
	double lastX = 0;
	double lastY = 0;
	window.GetMousePosition(lastX, lastY);
	const auto mouseSensitivity = 0.05f;
	
	scene1->Render(*m_Renderer);

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << err << std::endl;
	}

	Camera* camera = (scene1->GetCamera());
//========================================================================
// While Loop
//========================================================================
	while (!window.Closed() && (!window.IsKeyPressed(GLFW_KEY_ESCAPE)))
	{
		window.Clear();
		
		const auto currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		auto cameraSpeed = 2.5f * deltaTime;
		glm::vec3 cameraPos = camera->GetPos();


		//Callback - modifies values of cameraPos & FPSToggle
		inputHandler.Listen(*camera, cameraPos, cameraSpeed, FPSToggle, lastTime);

		//========================================================================
		// Mouse Controller TODO: abstract to inputhandler
		//========================================================================		
		auto xoffset = mouseX - lastX;
		auto yoffset = lastY - mouseY;
		lastX = mouseX;
		lastY = mouseY;
		window.GetMousePosition(mouseX, mouseY);
		xoffset *= mouseSensitivity;
		yoffset *= mouseSensitivity;

		
		float cameraYaw = camera->GetYaw() + xoffset;
		float cameraPitch = camera->GetPitch() +  yoffset;

		//Update all camera values
		camera->UpdatePos(cameraPos.x, cameraPos.y, cameraPos.z, cameraPitch, cameraYaw);
		//========================================================================
		// FPS Toggler
		//========================================================================
		if (FPSToggle)
		{
			// ReSharper disable once CppLocalVariableMayBeConst
			double currentTime = glfwGetTime();
			nbFrames++;
			if (currentTime - lastTime >= 1.0)
			{   // If last prinf() was more than 1 sec ago
				// printf and reset timer
				printf("%f ms/frame\n", 1000.0 / double(nbFrames));
				nbFrames = 0;
				lastTime += 1.0;
			}
		}


		//m_CubeMaterial->SetUniform("vw_matrix", camera->GetVP());
		//m_PlantMaterial->SetUniform("vw_matrix", camera->GetVP());
		//m_DefaultMaterial->SetUniform("vw_matrix", camera->GetVP());

	
		m_Renderer->Present();


		
		window.Update();
		
		
		
	}
	//textureShader.~Shader();
	//colorShader.~Shader();
	//crateTexture.~Texture();

	return 0;
}


/*
const glm::vec4 colors(1, 0.5, 1, 1);
glm::vec4 green(0, 1, 0, 1);

const glm::vec4 colorSkyBlue(0.4863, 0.6798, 1.0000, 1.0);
StaticSprite sprite1(1, 0, -1, 2, 2, 2, crateTexture.getID(), *textureShader);

StaticSprite sprite2(-4, -1, -1, 2, 2, colors, *colorShader);

StaticSprite groundSprite1(-25, -2, 25, 50, 0.1, 50, sandTexture.getID(), *textureShader);

StaticSprite skyBox(-50, -50, -50, 100, 100, 100, colorSkyBlue, *colorShader);


textureShader->Bind();
textureShader->SetUniformMat4("VP", camera.GetVP());
colorShader->Bind();
colorShader->SetUniformMat4("VP", camera.GetVP());


renderer.submit(&sprite1);
renderer.submit(&sprite2);
renderer.submit(&groundSprite1);
renderer.submit(&skyBox);



renderer.flush();
*/