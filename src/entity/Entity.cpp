#include "entity.hpp"

Entity::Entity(Object object, vector<ShaderInfo> shaders, vec4 color, mat4 fixedTransformation) {
	this->original = object;
	this->actual = object;
	this->color = color;

	this->fixedTransformation = fixedTransformation;
	this->kinematicTransformation = mat4(1);
	this->model = mat4(1);

	this->normalBuffer = new vector<vec3>(this->actual.getTriangles()->size() * 3);
	this->vertexBuffer = new vector<vec3>(this->actual.getTriangles()->size() * 3);
	this->info = {};
	this->info.shader = LoadShaders(&shaders.front());

	glGenVertexArrays(1, &this->info.VAO);
	glGenBuffers(1, &this->info.positionVBO);
	glGenBuffers(1, &this->info.normalVBO);
	glBindVertexArray(this->info.VAO);
}

OpenGLObjectInformation Entity::getOpenGLInformation() {
	return this->info;
}

void Entity::setKinematicTransformation(mat4 transformation) {
	this->kinematicTransformation = transformation;
}

mat4* Entity::getModel() {
	return &this->model;
}

Object* Entity::getObject() {
	return &this->actual;
}

vec4* Entity::getColor() {
	return &this->color;
}

void Entity::update() {
	// update position
	model = this->kinematicTransformation * this->fixedTransformation;
	
	const vector<vec3>* vertices = this->actual.getVertices();
	const vector<vec3>* normals = this->actual.getNormals();
	#pragma unroll
	for (size_t i = 0; i < this->actual.getTriangles()->size(); i++) {
		const Triangle triangle = this->actual.getTriangles()->at(i);
		auto v1 = vertices->at(triangle.vertices[0].position);
		auto v2 = vertices->at(triangle.vertices[1].position);
		auto v3 = vertices->at(triangle.vertices[2].position);
		auto p = glm::cross(v2 - v1, v3 - v1);
		vertexBuffer->at((i * 3) + 0) = v1;
		vertexBuffer->at((i * 3) + 1) = v2;
		vertexBuffer->at((i * 3) + 2) = v3;
		normalBuffer->at((i * 3) + 0) = v1 + glm::normalize(p);
		normalBuffer->at((i * 3) + 1) = v2 + glm::normalize(p);
		normalBuffer->at((i * 3) + 2) = v3 + glm::normalize(p);
	}
}

vector<vec3>* Entity::getRenderedVertices() {
	return vertexBuffer;
}

vector<vec3>* Entity::getRenderedNormals() {
	return normalBuffer;
}
