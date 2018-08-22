#include "Engine.h"

int main()
{
//========================================================================
// Create Objects (Camera is a singular entity)
//========================================================================

	Window window("3D-Engine", 960, 540);
	Shader* colorShader = Shader::FromFile("Color", "shaders/Color.shader");
	Shader* textureShader = Shader::FromFile("Textured", "shaders/TexturedCube.shader");

	

	
	m_Renderer = new ForwardRenderer();
	Material* material1 = new Material(Shader::FromFile("Scene", "shaders/scene.shader"));
	Material* material2 = new Material(Shader::FromFile("Default", "shaders/default.shader"));
	Material* material3 = new Material(Shader::FromFile("Color", "shaders/Color.shader"));
	Material* material4 = new Material(Shader::FromFile("Textured", "shaders/TexturedCube.shader"));
	

	VertexArray* va = CreateQuad(0, 0, 10, 10);
	IndexBuffer* ib = new IndexBuffer(new uint[6]{ 0,1,2,2,3,0 }, 6);

	m_CubeMaterial = new MaterialInstance(material1);
	m_PlantMaterial = new MaterialInstance(material1);
	m_DefaultMaterial = new MaterialInstance(material2);

	//Mesh* plane = new Mesh(va, ib,	m_DefaultMaterial);
	//Mesh* cubetest = CreateCube(3.0f, m_CubeMaterial);
	Model* cube = new Model("objects/cube.obj", m_CubeMaterial);
	Model* houseplant = new Model("objects/eb_house_plant_01.obj", m_PlantMaterial);

	Scene* scene1 = new Scene();

	

	scene1->Add(cube->GetMesh());
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

	
	//material2->SetUniform("pr_matrix", glm::perspective(65.0f, 16.0f / 9.0f, 0.1f, 1000.0f));
	//material1->SetUniform("vw_matrix", glm::translate(glm::mat4(), glm::vec3(0, 0, -10.0f)));
	std::string name = "colour";
	GLint loc = glGetUniformLocation(colorShader->getShaderID(), name.c_str());
	if (loc == -1) std::cout << "cant find" << std::endl;

	glm::mat4 modelMatrix(1.0);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-6, -2, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.3, 0.3));

	m_PlantMaterial->SetUniform("ml_matrix", modelMatrix);
	m_PlantMaterial->SetUniform("vw_matrix", camera.getVP());

	m_CubeMaterial->SetUniform("ml_matrix", glm::translate(glm::mat4(), glm::vec3(6, 3, 0)));
	m_CubeMaterial->SetUniform("vw_matrix", camera.getVP());

	

	Texture crateTexture("textures/crate.bmp");
	Texture sandTexture("textures/Sand_Texture.bmp");

	const glm::vec4 colors(1, 0.5, 1, 1);
	glm::vec4 green(0, 1, 0, 1);
	
	const glm::vec4 colorSkyBlue(0.4863, 0.6798, 1.0000,1.0);
	StaticSprite sprite1(1, 0, -1, 2, 2, 2, crateTexture.getID(),*textureShader);

	StaticSprite sprite2(-4, -1, -1, 2, 2, colors, *colorShader);

	StaticSprite groundSprite1(-25, -2, 25 ,50,0.1,50, sandTexture.getID(), *textureShader);

	StaticSprite skyBox(-50, -50, -50, 100, 100, 100, colorSkyBlue, *colorShader);

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
		
		
		textureShader->Bind();
		textureShader->SetUniformMat4("VP", camera.getVP());
		colorShader->Bind();
		colorShader->SetUniformMat4("VP", camera.getVP());

		//Camera returns View and Projection matrix multiplied together, not included in shader
		m_CubeMaterial->SetUniform("vw_matrix", camera.getVP());
		m_PlantMaterial->SetUniform("vw_matrix", camera.getVP());

		

		//send objects to renderer and flush all render jobs

		scene1->Render(*m_Renderer);
		m_Renderer->Present();

		renderer.submit(&sprite1);
		renderer.submit(&sprite2);
		renderer.submit(&groundSprite1);
		renderer.submit(&skyBox);
		
		
		
		renderer.flush();
		
		window.update();
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			//std::cout << err << std::endl;
		}
		
		
	}
	//textureShader.~Shader();
	//colorShader.~Shader();
	//crateTexture.~Texture();

	return 0;
}


