#include "math.hpp"

vec3 Jacobian::getJacobianAtAxis(Entity* joint, vec3 target, vec3 axis) {
	auto model = *joint->getModel();
	auto position = vec3(model[3]);
	auto jointAxis = vec3(model * vec4(axis, 0.f));

	auto diff = target - position;
	return glm::cross(jointAxis, diff);
}

float Jacobian::IK(HierarchicalKinematic* hierarchical, vec3 target) {
	auto h = 0.05;
	auto endEffectorPosition = hierarchical->getEndEffectorPosition();
	auto distance = target - endEffectorPosition;
	vector<vec3> delta = vector<vec3>(3);

	if (length(distance) > 0.1f) {
		auto joints = hierarchical->getJoints();

		int i = 0;
		for (auto joint : joints) {
			float x = h * glm::dot(getJacobianAtAxis(joint, target, vec3(1.f, 0.f, 0.f)), distance);
			float y = h * glm::dot(getJacobianAtAxis(joint, target, vec3(0.f, 1.f, 0.f)), distance);
			float z = h * glm::dot(getJacobianAtAxis(joint, target, vec3(0.f, 0.f, 1.f)), distance);

			delta.at(i) = vec3(x, y, z);
			i++;
		}
		hierarchical->addToJointPosition(delta.at(0), delta.at(1), delta.at(2));
		hierarchical->update();
	}
	return length(distance);
}