#include "Model.hpp"
#include "Mesh_.hpp"
#include "Texture_.hpp"
#include <assimp/postprocess.h>
#include <iostream>
#include "GameObject_.hpp"
#include "Transform.hpp"
#include "Material_.hpp"

namespace Engine
{
	using namespace Core;
	using namespace Rendering;
	GameObject_* Model::loadModel(const std::string& path)
	{
		std::cout << "Loading model at " + path << std::endl;
		Assimp::Importer import;
		const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
			return nullptr;
		}
		//this->path = path.substr(0, path.find_last_of('/'));

		GameObject_* go = processNode(scene->mRootNode, scene);
		std::cout << "Loaded model at " + path << std::endl;
		return go;
	}

	GameObject_* Model::processNode(aiNode *node, const aiScene *scene)
	{
		std::cout << "Processing node " << node->mName.C_Str() << std::endl;
		GameObject_* go;// = new GameObject_(node->mName.C_Str(), "");
		// process all the node's meshes (if any)
		std::cout << "Has " << node->mNumMeshes << " amount of meshes." << std::endl;
		std::cout << "Has " << node->mNumChildren << " amount of children." << std::endl;

		// then do the same for each of its children
		if (node->mNumChildren == 1)
			go = processNode(node->mChildren[0], scene);
		else
			go = new GameObject_(node->mName.C_Str(), "");

		go->getTransform()->setWorldMatrix4X4(convert(node->mTransformation));

		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			Material_* mymat = nullptr;
			Mesh_* mymesh = nullptr;
			const RenderQueue queue = processMesh(mesh, scene, mymesh, mymat);
			//std::cout << "Wrong" << std::endl;
			//std::cout << "My Mesh: " + std::to_string(mymesh != nullptr) << std::endl;
			//std::cout << "My Material: " + std::to_string(mymat != nullptr) << std::endl;
			go->addComponent(mymesh);
			go->addComponent(mymat);
			go->addComponent(new Renderer_(mymat, mymesh, queue, true));
			//go->addComponent<Renderer_>();
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			GameObject_* childGO = processNode(node->mChildren[i], scene);
			childGO->getTransform()->setParent(go->getTransform(), true);
		}

		std::cout << "Processed node " << node->mName.C_Str() << std::endl;

		return go;
	}

	RenderQueue Model::processMesh(aiMesh *mesh, const aiScene *scene, Mesh_*& outMesh, Material_*& outMaterial)
	{
		std::vector<Vertex> vertices;
		std::vector<int> indices;
		//std::vector<Texture_*> textures;
		//outMaterial = new Material_();

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			// process vertex positions, normals and texture coordinates
			glm::vec3 vector;

			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;

			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;

			if (mesh->mTextureCoords[0]) // do you even UV, bruh?
			{
				glm::vec2 uv;
				uv.x = mesh->mTextureCoords[0][i].x;
				uv.y = mesh->mTextureCoords[0][i].y;
				vertex.textureCoordinate = uv;
			}
			else
				vertex.textureCoordinate = glm::vec2(0.0f, 0.0f);

			//std::cout << "Vertex " + std::to_string(i) + " " + glm::to_string(vertex.position) + " " << std::endl;
			vertices.push_back(vertex);
		}
		//std::cout << std::endl;

		// process indices
		//int index = 0;
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			const aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				//index++;
				//std::cout << "Index " + std::to_string(index) + " " + std::to_string(face.mIndices[j]) + " " << std::endl;
				indices.push_back(face.mIndices[j]);
			}
		}
		std::cout << std::endl;

		// process material
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		outMaterial = loadMaterial(material);
		outMesh = new Mesh_(vertices, indices);

		RenderQueue queue = RenderQueue::Transparent;
		float opacity;
		material->Get(AI_MATKEY_OPACITY, opacity);
		if (glm::epsilonEqual(opacity, 1.0f, glm::epsilon<float>()))
			queue = RenderQueue::Opaque;

		//std::cout << "Out Mesh: " + std::to_string(outMesh != nullptr) << std::endl;
		//std::cout << "Out Material: " + std::to_string(outMaterial != nullptr) << std::endl;
		return queue;
	}

	Material_* Model::loadMaterial(aiMaterial* material)
	{
		//float opacity;
		//material->Get(AI_MATKEY_OPACITY, opacity);

		Material_* outMaterial = new Material_();
		aiString str;
		if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
			outMaterial->setDiffuseMap(Texture_::load(str.C_Str()));
		}

		if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			material->GetTexture(aiTextureType_SPECULAR, 0, &str);
			outMaterial->setSpecularMap(Texture_::load(str.C_Str()));
		}

		if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			material->GetTexture(aiTextureType_EMISSIVE, 0, &str);
			outMaterial->setEmissionMap(Texture_::load(str.C_Str()));
		}

		return outMaterial;
	}

	glm::mat4 Model::convert(aiMatrix4x4 aiMatrix)
	{
		return glm::mat4(
			aiMatrix.a1, aiMatrix.a2, aiMatrix.a3, aiMatrix.a4,
			aiMatrix.b1, aiMatrix.b2, aiMatrix.b3, aiMatrix.b4,
			aiMatrix.c1, aiMatrix.c2, aiMatrix.c3, aiMatrix.c4,
			aiMatrix.d1, aiMatrix.d2, aiMatrix.d3, aiMatrix.d4
		);
	}
}
