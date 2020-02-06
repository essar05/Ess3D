#include "ModelCache.h"
#include "errors/RuntimeException.cpp"
#include "TextureCache.h"

namespace Ess3D {

  ModelCache::~ModelCache() {
    auto it = _models.begin();
    while (it != _models.end()) {
      delete it->second;
      it++;
    }
  }

  Model* ModelCache::getModel(const std::string& filePath) {
    auto it = _models.find(filePath);

    if (it == _models.end()) {
      Model* model = this->loadModelFromFile(filePath);

      _models.insert(make_pair(filePath, model));

      return model;
    }

    return it->second;
  }

  ModelCache* ModelCache::_instance = nullptr;

  ModelCache* ModelCache::getInstance() {
    if (_instance == nullptr) {
      _instance = new ModelCache();
    }

    return _instance;
  }

  ModelCache::ModelCache() {}

  Model* ModelCache::loadModelFromFile(const std::string& filePath) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        filePath,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace
    );

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
      throw ERuntimeException("Error loading model at '" + filePath + "': " + importer.GetErrorString());
    }

    auto* model = new Model();

    std::string texturesDirectory = filePath.substr(0, filePath.find_last_of('/'));

    this->processAssimpNode(scene->mRootNode, scene, texturesDirectory, model);

    model->initialize();

    return model;
  }

  void ModelCache::processAssimpNode(const aiNode* node, const aiScene* scene, const std::string& texturesDirectory, Model* model) {
    for (unsigned int meshIndex = 0; meshIndex < node->mNumMeshes; meshIndex++) {
      this->processAssimpMesh(
          scene->mMeshes[node->mMeshes[meshIndex]],
          scene,
          texturesDirectory,
          model
      );
    }

    for (unsigned int childNodeIndex = 0; childNodeIndex < node->mNumChildren; childNodeIndex++) {
      this->processAssimpNode(
          node->mChildren[childNodeIndex],
          scene,
          texturesDirectory,
          model
      );
    }
  }

  void ModelCache::processAssimpMesh(const aiMesh* mesh, const aiScene* scene, const std::string& texturesDirectory, Model* model) {
    auto* essMesh = new Mesh();

    // Process vertices
    for (unsigned int vertexIndex = 0; vertexIndex < mesh->mNumVertices; vertexIndex++) {
      Vertex3D vertex;
      vertex.position = vec3AssimpToGlm(mesh->mVertices[vertexIndex]);
      vertex.normal = vec3AssimpToGlm(mesh->mNormals[vertexIndex]);
      vertex.tangent = vec3AssimpToGlm(mesh->mTangents[vertexIndex]);
      vertex.bitangent = vec3AssimpToGlm(mesh->mBitangents[vertexIndex]);

      if (mesh->HasTextureCoords(0)) {
        glm::vec3 textureCoords = vec3AssimpToGlm(mesh->mTextureCoords[0][vertexIndex]);
        vertex.uv = glm::vec2(textureCoords.x, textureCoords.y);
      } else {
        vertex.uv = glm::vec2(0.0f, 0.0f);
      }

      essMesh->addVertex(vertex);
    }

    // Process faces/indices
    for (unsigned int faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++) {
      aiFace face = mesh->mFaces[faceIndex];

      for (unsigned int indexIndex = 0; indexIndex < face.mNumIndices; indexIndex++) {
        essMesh->addIndex(face.mIndices[indexIndex]);
      }
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    this->processAssimpTextures(
        material,
        aiTextureType_DIFFUSE,
        texturesDirectory,
        essMesh
    );
    this->processAssimpTextures(
        material,
        aiTextureType_SPECULAR,
        texturesDirectory,
        essMesh
    );
    this->processAssimpTextures(
        material,
        aiTextureType_NORMALS,
        texturesDirectory,
        essMesh
    );
    this->processAssimpTextures(
        material,
        aiTextureType_HEIGHT,
        texturesDirectory,
        essMesh
    );

    model->addMesh(essMesh);
  }

  void ModelCache::processAssimpTextures(const aiMaterial* material, aiTextureType type, const std::string& texturesDirectory, Mesh* mesh) {
    for (unsigned int textureIndex = 0; textureIndex < material->GetTextureCount(type); textureIndex++) {
      aiString aiFilePath;

      material->GetTexture(type, textureIndex, &aiFilePath);

      Texture* texture = TextureCache::getInstance()->getTexture(
          texturesDirectory + "/" + std::string(aiFilePath.C_Str())
      );

      TextureType textureType;

      switch(type) {
        case aiTextureType_DIFFUSE:
          textureType = ESS_TEX_TYPE_DIFFUSE;
          break;
        case aiTextureType_SPECULAR:
          textureType = ESS_TEX_TYPE_SPECULAR;
          break;
        case aiTextureType_HEIGHT:
          textureType = ESS_TEX_TYPE_HEIGHT;
          break;
        case aiTextureType_NORMALS:
          textureType = ESS_TEX_TYPE_NORMAL;
          break;
      }

      texture->setType(textureType);

      mesh->addTexture(texture);
    }
  }

  glm::vec3 ModelCache::vec3AssimpToGlm(const aiVector3D& vector3D) {
    return glm::vec3(vector3D.x, vector3D.y, vector3D.z);
  }

};