//AssetManager.cpp

#include "AssetManager.h"

#include "FileLoader.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"

//-------------------------------------------------------------------------------------- -
//  Constructor
//-------------------------------------------------------------------------------------- -
AssetManager::AssetManager()
{
    //
}

//-------------------------------------------------------------------------------------- -
//  Destructor
//-------------------------------------------------------------------------------------- -
AssetManager::~AssetManager()
{
    //TODO: Make generic Resource class

    //Delete all the objects in meshes
    auto iteratorMesh = m_meshes.begin();
    while (iteratorMesh != m_meshes.end())
    {
        delete iteratorMesh->second;
        ++iteratorMesh;
    }

    //Deleting materials
    auto iteratorMat = m_materials.begin();
    while (iteratorMat != m_materials.end())
    {
        delete iteratorMat->second;
        ++iteratorMat;
    }

    //Deleting material instances
    auto iteratorMatInst = m_materialInstances.begin();
    while (iteratorMatInst != m_materialInstances.end())
    {
        delete (*iteratorMatInst);
        ++iteratorMatInst;
    }

    //Deleting textures
    auto iteratorTex = m_textures.begin();
    while (iteratorTex != m_textures.end())
    {
        delete iteratorTex->second;
        ++iteratorTex;
    }

    //Deleting material instances
    auto iteratorTexInst = m_textureInstances.begin();
    while (iteratorTexInst != m_textureInstances.end())
    {
        delete (*iteratorTexInst);
        ++iteratorTexInst;
    }
}

//***************************************************************************************
//  Mesh Functions
//***************************************************************************************
Mesh* AssetManager::LoadMesh(const char* const pFileName)
{
    //Search if the mesh already exists
    auto findIt = m_meshes.find(pFileName);
    if (findIt != m_meshes.end())
        return m_meshes[pFileName];

    Mesh* pNewMesh = new Mesh(pFileName);
    m_meshes.emplace(pFileName, pNewMesh);

    return pNewMesh;
}

Mesh* AssetManager::GetMesh(const char* const pFileName)
{
    return m_meshes[pFileName];
}

//***************************************************************************************
//  Material Functions
//***************************************************************************************
Material* AssetManager::LoadMaterial(std::string pMaterialName, std::string pVertFile, std::string pFragFile, Color color)
{
    return LoadMaterialInternal(pMaterialName, pVertFile, pFragFile, color, Color(0, 0, 0));
}

Material* AssetManager::LoadMaterial(std::string pMaterialName, std::string pVertFile, std::string pFragFile, Color color, Color ambientColor)
{
    return LoadMaterialInternal(pMaterialName, pVertFile, pFragFile, color, ambientColor);
}

//Redirect to this function
Material* AssetManager::LoadMaterialInternal(std::string pMaterialName, std::string pVertFile, std::string pFragFile, Color color, Color ambientColor)
{
    //Search if the material already exists
    auto findIt = m_materials.find(pMaterialName);
    if (findIt != m_materials.end())
        return m_materials[pMaterialName];

    Material* pNewMaterial = new Material(pVertFile, pFragFile, color, ambientColor);
    m_materials.emplace(pMaterialName, pNewMaterial);

    return pNewMaterial;
}

//--------------------------------------------------------------------------------------- -
//  Get Material Function
//--------------------------------------------------------------------------------------- -
Material* AssetManager::GetMaterial(std::string pMaterialName)
{
    return m_materials[pMaterialName];
}

//--------------------------------------------------------------------------------------- -
//  Create Material Instance Function
//--------------------------------------------------------------------------------------- -
Material* AssetManager::CreateMaterialInstance(std::string pMaterialName)
{
    //Create a copy of the template
    Material* pNewMaterialInstance = new Material(*(m_materials[pMaterialName]));

    m_materialInstances.push_back(pNewMaterialInstance);

    return pNewMaterialInstance;
}

Material* AssetManager::CreateMaterialInstance(std::string pMaterialName, Color newColor)
{
    //Create a copy of the template
    Material* pNewMaterialInstance = new Material(*(m_materials[pMaterialName]));
    pNewMaterialInstance->SetColor(newColor);

    m_materialInstances.push_back(pNewMaterialInstance);

    return pNewMaterialInstance;
}

Material* AssetManager::CreateMaterialInstance(std::string pMaterialName, Color newColor, Texture* pTexture)
{
    //Create a copy of the template
    Material* pNewMaterialInstance = new Material(*(m_materials[pMaterialName]));
    pNewMaterialInstance->SetColor(newColor);
    pNewMaterialInstance->SetTexture(pTexture);

    m_materialInstances.push_back(pNewMaterialInstance);

    return pNewMaterialInstance;
}

Material* AssetManager::CreateMaterialInstance(std::string pMaterialName, Texture* pTexture)
{
    //Create a copy of the template
    Material* pNewMaterialInstance = new Material(*(m_materials[pMaterialName]));
    pNewMaterialInstance->SetColor(Color(0.8f, 0.8f, 0.8f));
    pNewMaterialInstance->SetTexture(pTexture);

    m_materialInstances.push_back(pNewMaterialInstance);

    return pNewMaterialInstance;
}

//***************************************************************************************
//  Texture Functions
//***************************************************************************************
Texture* AssetManager::LoadTexture(std::string pTextureName, std::string pFileName)
{
    //Search if the material already exists
    auto findIt = m_textures.find(pTextureName);
    if (findIt != m_textures.end())
        return m_textures[pTextureName];

    Texture* pNewTexture = new Texture(pFileName);
    m_textures.emplace(pTextureName, pNewTexture);

    return pNewTexture;
}

Texture* AssetManager::CreateTextureInstance(std::string pTextureName)
{
    auto findIt = m_textures.find(pTextureName);
    if (findIt == m_textures.end())
        return nullptr; //Not found

    //Create a copy of the template
    Texture* pNewMaterialInstance = new Texture(*(m_textures[pTextureName]));

    m_textureInstances.push_back(pNewMaterialInstance);

    return pNewMaterialInstance;
}