#include "scene.hpp"

Entity* InverseKinematicSceneFactory::getArm(glm::vec4 color) {
	return new Entity(
		provider.get("resources/box.obj"),
		shaders,
		color,
		glm::scale(mat4(1.f), vec3(0.1f, 1.0f, 0.1f))
	);
}

Entity* InverseKinematicSceneFactory::getJoint(vec4 color) {
	return new Entity(
		provider.get("resources/sphere.obj"),
		shaders,
		color,
		glm::scale(mat4(1.f), vec3(0.2f, 0.2f, 0.2f))
	);
}

Scene* InverseKinematicSceneFactory::build() {
	/*
	Entity* floor = new Entity(
		provider.get("resources/plane.obj"),
		shaders,
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::scale(mat4(1.f), vec3(10.0f, 10.0f, 10.0f))
	);
	*/
	Entity* root = getArm(vec4(1.0f, 1.0f, 0.0f, 1.0f));
	Entity* root_joint = getJoint(vec4(1.0f, 1.0f, 0.0f, 1.0f));

	Entity* child_1 = getArm(vec4(0.0f, 1.0f, 1.0f, 1.0f));
	Entity* joint_1 = getJoint(vec4(0.0f, 1.0f, 1.0f, 1.0f));

	Entity* child_2 = getArm(vec4(1.0f, 0.0f, 1.0f, 1.0f));
	Entity* joint_2 = getJoint(vec4(1.0f, 0.0f, 1.0f, 1.0f));

	Entity* endEffector = getJoint(vec4(0.0f, 1.0f, 0.0f, 1.0f));
	Entity* target = getJoint(vec4(1.0f, 0.0f, 0.0f, 1.0f));

	vector<Entity*> entities = {
		floor,
		root,
		root_joint,
		child_1,
		joint_1,
		child_2,
		joint_2,
		endEffector,
		target
	};

	auto origin = glm::translate(mat4(1.f), vec3(0.f, 1.f, 0.f));
	HierarchicalKinematic* hierarchical = new HierarchicalKinematic(
		{ root, child_1, child_2 },
		{ root_joint, joint_1, joint_2 },
		endEffector,
		{ origin, origin, origin }
	);

	return new Scene(
		entities,
		target,
		hierarchical,
		new Camera(vec3(16.0f, 6.0f, -3.0f), vec3(-0.9f, -0.35f, 0.25f), -195, -20)
	);
}

InverseKinematicSceneFactory::InverseKinematicSceneFactory() {
	provider = ObjectProvider();
	shaders = {
			{ GL_VERTEX_SHADER, "resources/shaders/shader.vert" },
			{ GL_FRAGMENT_SHADER, "resources/shaders/shader.frag" },
			{ GL_NONE, NULL }
	};
}
