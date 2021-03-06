//AssetManager.h

#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <unordered_map>
#include <string>

#include "Color.h"

class Mesh;
class Material;
class Texture;

typedef std::unordered_map<std::string, Mesh*> MeshContainer;
typedef std::unordered_map<std::string, Material*> MaterialContainer;
typedef std::unordered_map<std::string, Texture*> TextureContainer;

class AssetManager
{
private:
    MeshContainer m_meshes;
    MaterialContainer m_materials;
    TextureContainer m_textures;

    std::vector<Material*> m_materialInstances;
    std::vector<Texture*> m_textureInstances;

public:
    AssetManager();
    ~AssetManager();

    // Meshes //
    Mesh* LoadMesh(const char* const pFileName);
    Mesh* GetMesh(const char* const pFileName);

    // Materials //
    Material* LoadMaterial(std::string pMaterialName, std::string pVertFile, std::string pFragFile, Color color);
    Material* LoadMaterial(std::string pMaterialName, std::string pVertFile, std::string pFragFile, Color color, Color ambientColor);
    Material* GetMaterial(std::string pMaterialName);

    Material* CreateMaterialInstance(std::string pMaterialName);
    Material* CreateMaterialInstance(std::string pMaterialName, Color newColor);
    Material* CreateMaterialInstance(std::string pMaterialName, Color newColor, Texture* pTexture);
    Material* CreateMaterialInstance(std::string pMaterialName, Texture* pTexture);

    // Textures //
    Texture* LoadTexture(std::string pTextureName, std::string pFileName);
    Texture* CreateTextureInstance(std::string pTextureName);

private:
    Material* LoadMaterialInternal(std::string pMaterialName, std::string pVertFile, std::string pFragFile, Color color, Color ambientColor);
};

#endif // !ASSETMANAGER_H
