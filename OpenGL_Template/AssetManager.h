//AssetManager.h

#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <unordered_map>
#include <string>

class Mesh;
class Material;

class AssetManager
{
private:
    std::unordered_map<const char*, Mesh*> m_meshes;
    std::unordered_map<const char*, Material*> m_materials;

public:
    AssetManager();
    ~AssetManager();

    Mesh* LoadMesh(const char* const pFileName);
    Mesh* GetMesh(const char* const pFileName);

    Material* LoadMaterial(const char* const pMaterialName, const char* const pVertFile, const char* const pFragFile);
    Material* GetMaterial(const char* const pMaterialName);
};

#endif // !ASSETMANAGER_H
