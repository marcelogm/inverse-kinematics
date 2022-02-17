#include "scene.hpp"
#include <glm/gtx/norm.hpp>
#include <glm/gtx/polar_coordinates.hpp>


Scene::Scene(vector<Entity*> fixed, Entity* target, HierarchicalKinematic* hierarchical, Camera* camera) {
	this->entities = fixed;
	this->target = target;
	this->targetPosition = nextPosition();
	this->hierarchical = hierarchical;
	this->camera = camera;
	this->renderer = new Renderer();
	this->r = 0;
	this->hierarchical->setTranslation(
		glm::translate(mat4(1.f), vec3(0.f, 2.f, 0.f)),
		glm::translate(mat4(1.f), vec3(0.f, 2.f, 0.f)),
		glm::translate(mat4(1.f), vec3(0.f, 2.f, 0.f))
	);
}

void Scene::render() {
	this->renderer->clear();
	this->renderer->prepare();
	target->setKinematicTransformation(glm::translate(mat4(1.f), targetPosition));

	auto distance = Jacobian().IK(hierarchical, targetPosition);

	if (distance < 0.5 || r > 1000) {
		targetPosition = nextPosition();
		r = 0;
	}

	r++;
	for (Entity* entity : this->entities) {
		this->updateAndRender(entity, camera);
	}
}

void Scene::updateAndRender(Entity* entity, Camera* camera) {
	entity->update();
	renderer->render(entity, camera, Configuration::getInstance()->getLight());
}

Camera* Scene::getCamera() {
	return camera;
}

float rand(float M, float N)
{
	return M + (rand() / (RAND_MAX / (N - M)));
}

vec3 Scene::nextPosition() {
	auto radio = 4.0f;
	auto azimuth = rand(0.f, 360.f);
	auto polar = rand(0.f, 180.f);

	return radio * glm::euclidean(glm::vec2(azimuth, polar));
}
