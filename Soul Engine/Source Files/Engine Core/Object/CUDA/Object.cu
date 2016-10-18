#include "Object.cuh"
#include "Utility\CUDA\CUDAHelper.cuh"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

Object::Object(){

	verticeAmount = 0;
	faceAmount = 0;
	materialSize = 0;
	localSceneIndex = 0;
	ready = false;

	xyzPosition = glm::vec3(0);

	vertices = NULL;
	faces = NULL;
	materialP = NULL;
}
Object::Object(glm::vec3 pos, std::string name, Material* mat){

	verticeAmount = 0;
	faceAmount = 0;
	materialSize = 1;
	localSceneIndex = 0;
	ready = false;

	xyzPosition = glm::vec3(0);

	vertices = NULL;
	faces = NULL;
	CudaCheck(cudaMallocManaged((void**)&materialP, materialSize*sizeof(Material*)));
	materialP[0] = mat;

	xyzPosition = pos;
	ExtractFromFile(name.c_str());
}

void Object::AddVertices(Vertex* vertices, uint vSize){

}
void Object::AddFaces(Face* vertices, uint fSize){

}
void Object::ExtractFromFile(const char* name){



	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, name)) {
		throw std::runtime_error(err);
	}

	std::unordered_map<Vertex, int> uniqueVertices = {};

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			Vertex vertex = {};

			vertex.pos = {
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			};

			vertex.texCoord = {
				attrib.texcoords[2 * index.texcoord_index + 0],
				1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
			};

			if (uniqueVertices.count(vertex) == 0) {
				uniqueVertices[vertex] = vertices.size();
				vertices.push_back(vertex);
			}

			indices.push_back(uniqueVertices[vertex]);
		}
	}






















	uint overallSize = 0;
	uint faceOverallSize = 0;
	for (uint i = 0; i < shapes.size(); i++){
		overallSize += shapes[i].mesh.positions.size();
		faceOverallSize += shapes[i].mesh.indices.size();
	}


	verticeAmount = overallSize;
	faceAmount = faceOverallSize / 3;

	glm::vec3 max = glm::vec3(shapes[0].mesh.positions[0], shapes[0].mesh.positions[1], shapes[0].mesh.positions[2]);
	glm::vec3 min = glm::vec3(shapes[0].mesh.positions[0], shapes[0].mesh.positions[1], shapes[0].mesh.positions[2]);

	cudaDeviceSynchronize();

	CudaCheck(cudaMallocManaged((void**)&vertices,
		verticeAmount*sizeof(Vertex)));

	CudaCheck(cudaMallocManaged((void**)&faces,
		faceAmount*sizeof(Face)));

	cudaDeviceSynchronize();

	uint overallOffset = 0;
	uint faceOffset = 0;

	for (uint i = 0; i < shapes.size(); i++){
		for (uint v = 0; v < verticeAmount / 3; v++){
			vertices[overallOffset + v].SetData(
				glm::vec3(shapes[i].mesh.positions[3 * v + 0], shapes[i].mesh.positions[3 * v + 1], shapes[i].mesh.positions[3 * v + 2])*METER,
				glm::vec2(shapes[i].mesh.texcoords[2 * v + 0], shapes[i].mesh.texcoords[2 * v + 1]),
				glm::vec3(shapes[i].mesh.normals[3 * v + 0], shapes[i].mesh.normals[3 * v + 1], shapes[i].mesh.normals[3 * v + 2]));

			vertices[overallOffset + v].position += xyzPosition;
			max = glm::max(vertices[overallOffset + v].position, max);
			min = glm::min(vertices[overallOffset + v].position, min);

		}
		overallOffset += shapes[i].mesh.positions.size();

		for (uint f = 0; f < faceAmount; f++){
			faces[faceOffset + f].SetData(
				glm::uvec3(shapes[i].mesh.indices[3 * f + 0], shapes[i].mesh.indices[3 * f + 1], shapes[i].mesh.indices[3 * f + 2]),
				materialP[0]);
			//shapes[i].mesh.material_ids[f]);
		}
		faceOffset += shapes[i].mesh.indices.size();
	}

	box.max = max;
	box.min = min;
	cudaDeviceSynchronize();




}
//std::string Object::ResourcePath(std::string fileName) {
//		return  fileName;
//}
//

//void Object::GetVertices(GLuint& buffer, GLuint& sizeVert){
//	buffer = storageVertices;
//	sizeVert = verticeAmount;
//}
//void Object::GetIndices(GLuint& buffer, GLuint& sizeIn){
//	buffer = storageIndices;
//	sizeIn = indiceAmount;
//}
//void Object::GetTextureCoords(GLuint& buffer, GLuint& sizeVert){
//	buffer = storageTextureCoords;
//	sizeVert = verticeAmount;
//}
//void Object::GetNormals(GLuint& buffer, GLuint& sizeVert){
//	buffer = storageNormals;
//	sizeVert = verticeAmount;
//}
//void Object::GetMaterials(std::list<Material*>& material){
//	for (std::list<Material>::iterator itr = materials.begin(); itr != materials.end(); itr++){
//		material.push_back(&*itr);
//	}
//}
//void Object::GetPhysics(glm::vec3& pos, glm::vec3& vel,bool& isStat){
//	pos = xyzPosition;
//	vel = velocity;
//	isStat = isStatic;
//}
//void Object::SetPhysics(glm::vec3& pos, glm::vec3& vel, bool& isStat){
//	xyzPosition = pos;
//	velocity = vel;
//	isStatic = isStat;
//}
//Object::Mesh::VertexHandle Object::AddVertex(float x, float y, float z){
//	return mesh.add_vertex(Mesh::Point(x, y, z));
//}
//Object::Mesh::VertexHandle Object::AddVertex(glm::vec3 data){
//	return mesh.add_vertex(Mesh::Point(data.x, data.y, data.z));
//}
//Object::Mesh::VertexHandle Object::AddVertex(glm::vec4 data){
//	return mesh.add_vertex(Mesh::Point(data.x, data.y, data.z));
//}
//void Object::AddFace(Object::Mesh::VertexHandle x, Object::Mesh::VertexHandle y, Object::Mesh::VertexHandle z){
//	std::vector<Mesh::VertexHandle>  face_vhandles;
//	face_vhandles.resize(3);
//	face_vhandles[0] = x;
//	face_vhandles[1] = y;
//	face_vhandles[2] = z;
//	mesh.add_face(face_vhandles);
//}