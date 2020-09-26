#pragma once

#include <Ess3D/definitions.h>
#include <map>
#include <string>
#include <Ess3D/3d/model/Model.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Ess3D {
  class API ModelCache {
    public:
      ~ModelCache();

      /**
       * Get the Model object at the specified path. If it does not exist it loads and caches it first
       *
       * @param filePath
       * @return
       */
      Model* getModel(const std::string& filePath);

      static ModelCache* getInstance();

    protected:
      ModelCache();

    private:
      std::map<std::string, Model*> _models;

      /**
       * Loads a model from the specified filePath using Assimp into an Ess3D:Model class
       *
       * @param filePath
       * @return
       */
      Model* loadModelFromFile(const std::string& filePath);

      /**
       * Recursive method which processes each assimp scene node and mutates the model object
       *
       * @param node
       * @param scene
       * @param model
       */
      void processAssimpNode(const aiNode* node, const aiScene* scene, const std::string& texturesDirectory, Model* model);

      /**
       * Mutates the model object, adding an Ess3D::Mesh to it based on the aiMesh provided
       *
       * @param mesh
       * @param scene
       * @param model
       */
      void processAssimpMesh(const aiMesh* mesh, const aiScene* scene, const std::string& texturesDirectory, Model* model);

      /**
       * Mutates the mesh object, adding the specified material's textures to it
       *
       * @param material
       * @param type
       * @param mesh
       */
      void processAssimpTextures(const aiMaterial* material, aiTextureType type, const std::string& texturesDirectory, Mesh* mesh);

      static glm::vec3 vec3AssimpToGlm(const aiVector3D& vector3D);

      static ModelCache* _instance;
  };
};