#include "Engine.h"

using namespace entity;
using namespace component;
int main()
{

	Window* window = new Window("3D-Engine", 960, 540);

	m_Renderer = new ForwardRenderer();
	Scene* scene1 = new Scene();
	

	Material* material1 = new Material(Shader::CreateFromFile("scene", "shaders/scene.shader"));
	Material* material2 = new Material(Shader::CreateFromFile("Default", "shaders/default.shader"));
	//Material* material3 = new Material(Shader::FromFile("Color", "shaders/Color.shader"));
	//Material* material4 = new Material(Shader::FromFile("Textured", "shaders/TexturedCube.shader"));
	
	VertexArray* va = CreateQuad(0, 0, 20, 20);
	IndexBuffer* ib = new IndexBuffer(new uint[6]{ 0,1,2,2,3,0 }, 6);

	m_CubeMaterial = new MaterialInstance(material1);
	m_PlantMaterial = new MaterialInstance(material1);
	m_DefaultMaterial = new MaterialInstance(material2);
	m_SphereMaterial = new MaterialInstance(material1);

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

	m_Sphere = new Entity();
	Model* sphere = new Model("objects/Sphere.obj", m_SphereMaterial);
	m_Sphere->AddComponent(new MeshComponent(sphere->GetMesh()));
	m_Sphere->AddComponent(new TransformComponent(glm::mat4(1)));

	/*Entity* sponza = new Entity();
	Model* sponzamodel = new Model("objects/sponza/sponza.obj", m_SphereMaterial);
	sponza->AddComponent(new MeshComponent(sponzamodel->GetMesh()));
	sponza->AddComponent((new TransformComponent(glm::mat4(1))));
	*/
	
	scene1->Add(m_Cube);
	scene1->Add(m_HousePlant);
	scene1->Add(m_Quad);
	scene1->Add(m_Sphere);
	//scene1->Add(sponza);


	Texture crateTexture("textures/crate.bmp");
	Texture sandTexture("textures/Sand_Texture.bmp");


	InputHandler inputHandler(window, scene1->GetCamera());


	scene1->Render(*m_Renderer);

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << err << std::endl;
	}

	while (!window->Closed() && (!window->IsKeyPressed(GLFW_KEY_ESCAPE)))
	{
		window->Clear();
		inputHandler.Listen();
		m_Renderer->Present();
		window->Update();
		
	}

	return 0;
}
