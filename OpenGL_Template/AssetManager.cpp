//AssetManager.cpp

#include "AssetManager.h"

#include "FileLoader.h"
#include "Mesh.h"
#include "Material.h"

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
}

//--------------------------------------------------------------------------------------- -
//  Mesh Functions
//--------------------------------------------------------------------------------------- -
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

//--------------------------------------------------------------------------------------- -
//  Material Functions
//--------------------------------------------------------------------------------------- -
Material* AssetManager::LoadMaterial(const char* const pMaterialName, const char* const pVertFile, const char* const pFragFile, Color color)
{
    return LoadMaterialInternal(pMaterialName, pVertFile, pFragFile, color, Color(0, 0, 0));
}

Material* AssetManager::LoadMaterial(const char* const pMaterialName, const char* const pVertFile, const char* const pFragFile, Color color, Color ambientColor)
{
    return LoadMaterialInternal(pMaterialName, pVertFile, pFragFile, color, ambientColor);
}

//Redirect to this function
Material* AssetManager::LoadMaterialInternal(const char* const pMaterialName, const char* const pVertFile, const char* const pFragFile, Color color, Color ambientColor)
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
Material* AssetManager::GetMaterial(const char* const pMaterialName)
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