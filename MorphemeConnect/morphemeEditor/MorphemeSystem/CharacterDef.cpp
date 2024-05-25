// Copyright (c) 2010 NaturalMotion.  All Rights Reserved.
// Not to be copied, adapted, modified, used, distributed, sold,
// licensed or commercially exploited in any manner without the
// written consent of NaturalMotion.
//
// All non public elements of this software are the confidential
// information of NaturalMotion and may not be disclosed to any
// person nor used for any purpose not expressly approved by
// NaturalMotion in writing.

//----------------------------------------------------------------------------------------------------------------------
#include "CharacterDef.h"

#include "MorphemeSystem.h"
#include "AssetLoader.h"
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
CharacterDefBasic* CharacterDefBasic::create(const char* filename)
{
  //----------------------------
  // Create and initialise an instance of our character definition
  CharacterDefBasic* const instance = static_cast<CharacterDefBasic*>(NMPMemoryAlloc(sizeof(CharacterDefBasic)));
  new(instance) CharacterDefBasic();

  //----------------------------
  // Load the given bundle file into memory and load the bundle.
  NMP_STDOUT("Loading: %s", filename);

  //----------------------------
  // In this tutorial we no longer hold bundle information in GameCharacterDef as the unloading is handled
  // by the GameAssetLoader.
  void* bundle = NULL;
  int64_t bundleSize = 0;

  //----------------------------
  // Load binary bundle into memory
  int64_t fileSize = NMP::NMFile::allocAndLoad(filename, &bundle, &bundleSize);
  if (fileSize <= -1)
  {
    NMP_ASSERT_FAIL();
    NMP_STDOUT("Failed to load file: '%s'", filename);
    NMP_STDOUT("Perhaps the assets have not been processed.");

    return NULL;
  }
  else
  {
    NMP_ASSERT(bundleSize >= fileSize);
    NMP_STDOUT("Loaded file: '%s", filename);
    NMP_STDOUT("Initialising GameCharacterDef");

    //----------------------------
    // Allocate memory and unpack bundle
    if(!(instance->init(bundle, (size_t)bundleSize)))
    {
      CharacterDefBasic::destroy(instance);

      NMP_ASSERT_FAIL();
      NMP_STDOUT("Failed to initialise gameCharacterDef");
    }

    NMP_STDOUT("GameCharacterDef created");
  }

  //----------------------------
  // We have loaded the information in the buffer now so we can free it.
  NMP::Memory::memFree(bundle);

  return instance;
}

//--------------------------------------------------------------------------------------------------------------------
bool CharacterDefBasic::destroy(CharacterDefBasic* characterDef)
{
  NMP_ASSERT(characterDef);

  characterDef->term();

  NMP::Memory::memFree(characterDef);
  characterDef = NULL;

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
bool CharacterDefBasic::loadAnimations()
{  
  //----------------------------
  // Load animations listed in this network definition
  for (UINT i = 0; i < m_netDef->getNumAnimSets(); ++i)
  {
      m_netDef->loadAnimations((MR::AnimSetIndex)i, m_animFileLookUp);
      /*
    if (!m_netDef->loadAnimations((MR::AnimSetIndex)i, m_animFileLookUp))
    {
      return false;
    }
    */
  }

  NMP_STDOUT("Animations successfully loaded");
  return true;
}

MR::AnimRigDef* CharacterDefBasic::getAnimRigDef(int idx) const
{
    if (idx < m_animRigDefs.size())
        return m_animRigDefs[idx];

    return nullptr;
}

MR::RigToAnimMap* CharacterDefBasic::getRigToAnimMap(int idx) const
{
    if (idx < m_rigToAnimMaps.size())
        return m_rigToAnimMaps[idx];

    return nullptr;
}

//----------------------------------------------------------------------------------------------------------------------
bool CharacterDefBasic::init(void* bundle, size_t bundleSize)
{  
  if (!bundle || !bundleSize)
  {
    NMP_STDOUT("error: Valid bundle expected!");
    return NULL;
  }

  //----------------------------
  // Evaluate the number of registered (core) and client assets and allocate appropriate storage.
  AssetLoaderBasic::evalBundleRequirements(m_numRegisteredAssets,
    m_numClientAssets,
    bundle,
    bundleSize);

  NMP_ASSERT(m_numRegisteredAssets > 0);

  //----------------------------
  // Allocate arrays for storing asset information based on the bundle requirements
  m_registeredAssetIDs = (UINT*)NMPMemoryCalloc(m_numRegisteredAssets * sizeof(UINT));
  m_clientAssets = (void**)NMPMemoryCalloc(m_numClientAssets * sizeof(void*));

  //----------------------------
  // Process the bundle and extract the contents into memory
  NMP_STDOUT("Loading bundle:");
  bool status = AssetLoaderBasic::loadBundle(
                   bundle,
                   bundleSize,
                   m_registeredAssetIDs,
                   m_clientAssets,
                   m_numRegisteredAssets,
                   m_numClientAssets,
                   m_netDef,
                   m_animRigDefs,
                   m_rigToAnimMaps,
                   m_animFileLookUp);

  if (!m_netDef)
  {
    NMP_STDOUT("error: Failed to unpack the bundle!");
    return false;
  }
  NMP_STDOUT("Bundle successfully loaded");

  m_isLoaded = true;

  return true;
}

// --------------------------------------------------------------------------------------------------------------------
bool CharacterDefBasic::term()
{
  if( m_isLoaded )
  {
    for (UINT i = 0; i < m_netDef->getNumAnimSets(); ++i)
    {
      if (!m_netDef->unloadAnimations((MR::AnimSetIndex)i, NULL))
      {
        return false;
      }
    }

    //----------------------------
    // In the same theme as loadBundle above we call a function that can be cut-and-paste into any program.
    AssetLoaderBasic::unLoadBundle(m_registeredAssetIDs, m_numRegisteredAssets, m_clientAssets, m_numClientAssets);
  }

  if (m_registeredAssetIDs)
  {
    NMP::Memory::memFree(m_registeredAssetIDs);
  }

  if(m_clientAssets)
  {
    NMP::Memory::memFree(m_clientAssets);
  }
  //----------------------------
  // Free any memory that may be allocated in this class here
  return true;
}