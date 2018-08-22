#include <iostream>

#include "../graphics/Texture.h"
#include "../graphics/StaticSprite.h"
#include "../src/InputHandler.h"
#include "../renderer/Renderer.h"
#include "../graphics/MeshCreator.h"
#include "../graphics/Scene.h"
#include "../renderer/ForwardRenderer.h"
#include "../graphics/Model.h"


int main()
{
//========================================================================
// Create Objects (Camera is a singular entity)
//========================================================================

	Window window("3D-Engine", 960, 540);
	Shader colorShader("shaders/Color.vertexshader", "shaders/Color.fragmentshader");
	Shader textureShader("shaders/TexturedCube.vertexshader", "shaders/TexturedCube.fragmentshader");
	
	Renderer3D* renderertest = new ForwardRenderer();
	Material* material1 = new Material(new Shader("shaders/scene.vertexshader", "shaders/scene.fragmentshader"));
	Material* material2 = new Material(new Shader("shaders/default.vertexshader", "shaders/default.fragmentshader"));
	

	VertexArray* va = CreateQuad(0, 0, 10, 10);
	IndexBuffer* ib = new IndexBuffer(new uint[6]{ 0,1,2,2,3,0 }, 6);

	Mesh* plane = new Mesh(va, ib, new MaterialInstance(material2));
	Mesh* cubetest = CreateCube(3.0f, new MaterialInstance(material1));
	Scene* scene1 = new Scene();

	Model* houseplant = new Model("objects/eb_house_plant_01.obj", new MaterialInstance(material1));

	//scene1->Add(cubetest);
	//scene1->Add(plane);
	scene1->Add(houseplant->GetMesh());
	
	const int projection_Width = 4;
	const int projection_Height = 3;
	const float FOV = 45.0f;
	const float cameraX = 0;
	const float cameraY = 2;
	const float cameraZ = 5;
	//These values change with mouse-callback
	float cameraPitch = 0.0f;
	float cameraYaw = -90.0f;

	Camera camera(projection_Width, projection_Height, FOV, cameraX, cameraY, cameraZ, cameraPitch, cameraYaw);

	
	//material1->SetUniform("pr_matrix", glm::perspective(65.0f, 16.0f / 9.0f, 0.1f, 1000.0f));
	//material1->SetUniform("vw_matrix", glm::translate(glm::mat4(), glm::vec3(0, 0, -10.0f)));
	glm::mat4 modelMatrix(1.0);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-6, -2, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.3, 0.3));

	material1->Bind();
	material1->SetUniform("ml_matrix", modelMatrix);
	material1->SetUniform("vw_matrix", camera.getVP());

	material2->Bind();
	material2->SetUniform("ml_matrix", glm::translate(glm::mat4(), glm::vec3(0, 5, 0)));
	material2->SetUniform("vw_matrix", camera.getVP());

	

	Texture crateTexture("textures/crate.bmp");
	Texture sandTexture("textures/Sand_Texture.bmp");

	const glm::vec4 colors(1, 0.5, 1, 1);
	glm::vec4 green(0, 1, 0, 1);
	
	const glm::vec4 colorSkyBlue(0.4863, 0.6798, 1.0000,1.0);
	StaticSprite sprite1(1, 0, -1, 2, 2, 2, crateTexture.getID(),textureShader);

	StaticSprite sprite2(-4, -1, -1, 2, 2, colors, colorShader);

	StaticSprite groundSprite1(-25, -2, 25 ,50,0.1,50, sandTexture.getID(), textureShader);

	StaticSprite skyBox(-50, -50, -50, 100, 100, 100, colorSkyBlue, colorShader);

	Renderer renderer;

	InputHandler inputHandler(window);

//========================================================================
// Global vars for update loop
//========================================================================

	auto lastTime = glfwGetTime();
	auto nbFrames = 0;
	auto FPSToggle = false;
	auto deltaTime = 0.0f;	// Time between current frame and last frame
	auto lastFrame = 0.0f; // Time of last frame

	double mouseX = 0;
	double mouseY = 0;
	window.getMousePosition(mouseX, mouseY);
	double lastX = 0;
	double lastY = 0;
	window.getMousePosition(lastX, lastY);
	const auto mouseSensitivity = 0.05f;
	
	
//========================================================================
// While Loop
//========================================================================

	while (!window.closed() && (!window.isKeyPressed(GLFW_KEY_ESCAPE)))
	{
		window.clear();
		

		scene1->Render(*renderertest);
		renderertest->Present();

		const auto currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		auto cameraSpeed = 2.5f * deltaTime;
		glm::vec3 cameraPos = camera.getPos();


		//Callback - modifies values of cameraPos & FPSToggle
		inputHandler.listen(camera, cameraPos, cameraSpeed, FPSToggle);

		//========================================================================
		// Mouse Controller TODO: abstract to inputhandler
		//========================================================================		
		auto xoffset = mouseX - lastX;
		auto yoffset = lastY - mouseY;
		lastX = mouseX;
		lastY = mouseY;
		window.getMousePosition(mouseX, mouseY);
		xoffset *= mouseSensitivity;
		yoffset *= mouseSensitivity;

		cameraYaw += xoffset;
		cameraPitch += yoffset;

		//Update all camera values
		camera.updatePos(cameraPos.x, cameraPos.y, cameraPos.z, cameraPitch, cameraYaw);
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

		//Update camera pos for each shader (change this later)
		
		
		textureShader.enable();
		textureShader.setUniformMat4("VP", camera.getVP());
		colorShader.enable();
		colorShader.setUniformMat4("VP", camera.getVP());
		material1->Bind();
		material1->SetUniform("vw_matrix", camera.getVP());
		material2->Bind();
		material2->SetUniform("vw_matrix", camera.getVP());

		//send objects to renderer and flush all render jobs
		
		renderer.submit(&sprite1);
		renderer.submit(&sprite2);
		renderer.submit(&groundSprite1);
		renderer.submit(&skyBox);
		
		
		
		renderer.flush();
		
		window.update();
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			std::cout << err << std::endl;
		}
		
		
	}
	textureShader.~Shader();
	colorShader.~Shader();
	crateTexture.~Texture();

	return 0;
}


