#pragma once

#include "../configuration/config.hpp"
#include "../camera/camera.hpp"
#include "../entity/entity.hpp"
#include "../math/math.hpp"
#include "../kinematic/kinematic.hpp"

using glm::mat4;
using std::vector;

class Renderer {
private:
	float aspect;
	mat4 projection;
	float lightPosition;
	float ambientLightStrength;
	float diffuseLightStrength;
public:
	void clear();
	void prepare();
	void render(Entity*, Camera*, LightConfiguration*);
};

class Scene {
private:
	vector<Entity*> entities;
	vector<HierarchicalEntity*> hierarchicalEntities;
	Entity* character;
	Renderer* renderer;
	Camera* camera;
	vector<vec3>* controls;
	float currentStep;
	float lastStep;
	int r;
public:
	Scene(vector<Entity*> fixed, vector<HierarchicalEntity*> hierarchicalEntities, Camera* camera);
	void render();
	void updateAndRender(Entity* entity, Camera* camera);
	Camera* getCamera();
};

class InverseKinematicSceneFactory {
private:
	ObjectProvider provider;
	vector<ShaderInfo> shaders;
public:
	Scene* build();
	InverseKinematicSceneFactory();
};

class Frametime {
private:
	static Frametime* instance;
	Frametime();

	double framerate;
	double frametime;

	double lastFrameTime = 0.0;
	double currentFrameTime = 0.0;
	double timeFrameDiff = 0.0;
	size_t frameCounter = 0;
public:
	static Frametime* getInstance();
	void countFrame();
	double getFramerate();
	double getFrametime();
	double getDelta();
};
