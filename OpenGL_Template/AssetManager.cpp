//AssetManager.cpp

#include "AssetManager.h"

#include "FileLoader.h"
#include "Mesh.h"
#include "Material.h"

AssetManager::AssetManager()
{
    //
}

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
}

//--------------------------------------------------------------------------------------- -
//  Mesh Functions
//--------------------------------------------------------------------------------------- -
Mesh* AssetManager::LoadMesh(const char* const pFileName)
{
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
Material* AssetManager::LoadMaterial(const char* const pMaterialName, const char* const pVertFile, const char* const pFragFile)
{
    Material* pNewMaterial = new Material(pVertFile, pFragFile);
    m_materials.emplace(pMaterialName, pNewMaterial);

    return pNewMaterial;
}

Material* AssetManager::GetMaterial(const char* const pMaterialName)
{
    return m_materials[pMaterialName];
}