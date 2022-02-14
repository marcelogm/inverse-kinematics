#include "scene.hpp"

Scene* InverseKinematicSceneFactory::build() {
	Entity* root = new Entity(
		provider.get("resources/box.obj"),
		shaders,
		vec4(1.0f, 1.0f, 0.0f, 1.0f),
		glm::scale(mat4(1.f), vec3(0.1f, 1.0f, 0.1f))
	);
	Entity* child = new Entity(
		provider.get("resources/box.obj"),
		shaders,
		vec4(0.0f, 1.0f, 1.0f, 1.0f),
		glm::scale(mat4(1.f), vec3(0.1f, 1.0f, 0.1f))
	);
	Entity* child_2 = new Entity(
		provider.get("resources/box.obj"),
		shaders,
		vec4(1.0f, 0.0f, 1.0f, 1.0f),
		glm::scale(mat4(1.f), vec3(0.1f, 1.0f, 0.1f))
	);
	Entity* joint_1 = new Entity(
		provider.get("resources/sphere.obj"),
		shaders,
		vec4(1.0f, 1.0f, 0.0f, 1.0f),
		glm::scale(mat4(1.f), vec3(0.2f, 0.2f, 0.2f))
	);
	Entity* joint_2 = new Entity(
		provider.get("resources/sphere.obj"),
		shaders,
		vec4(0.0f, 1.0f, 1.0f, 1.0f),
		glm::scale(mat4(1.f), vec3(0.2f, 0.2f, 0.2f))
	);
	Entity* joint_3 = new Entity(
		provider.get("resources/sphere.obj"),
		shaders,
		vec4(1.0f, 0.0f, 1.0f, 1.0f),
		glm::scale(mat4(1.f), vec3(0.2f, 0.2f, 0.2f))
	);

	vector<Entity*> fixed = {
		root,
		child,
		child_2,
		joint_1,
		joint_2,
		joint_3
	};

	vector<HierarchicalEntity*> hierarchical = {
		new HierarchicalEntity(root, joint_1, vec3(0.f, 1.0f, 0.f), {
			new HierarchicalEntity(child, joint_2, vec3(0.f, 1.0f, 0.f), {
				new HierarchicalEntity(child_2, joint_3, vec3(0.f, 1.0f, 0.f), {
				})
			})
		})
	};

	return new Scene(
		fixed,
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
