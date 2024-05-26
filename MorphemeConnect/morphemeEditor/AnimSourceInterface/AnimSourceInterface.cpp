#include "AnimSourceInterface.h"
#include <string>
#include <filesystem>

AnimSourceInterface::AnimSourceInterface()
{
}

AnimSourceInterface::AnimSourceInterface(MR::AnimRigDef* rig, MR::RigToAnimMap* rigToAnimMap, const char* filename, int id)
{	
    void* animData = NULL;
    int64_t animSize = 0;
    int64_t fileSize = NMP::NMFile::allocAndLoad(filename, &animData, &animSize);
    MR::AnimationSourceHandle* animHandle = new MR::AnimationSourceHandle;

    std::filesystem::path name = std::filesystem::path(filename).filename();

    bool found = false;

    if (fileSize > -1)
    {
        animHandle->openAnimation((unsigned char*)animData, fileSize, "nsa");
        found = true;
    }

    while (true)
    {
        if (found)
            break;

        std::filesystem::path parent_path = std::filesystem::path(filename).parent_path().parent_path().string() + "\\c0001\\";

        for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(parent_path))
        {
            std::string filepath = dirEntry.path().string() + "\\" + name.string();

            fileSize = NMP::NMFile::allocAndLoad(filepath.c_str(), &animData, &animSize);

            if (fileSize > -1)
            {
                animHandle->openAnimation((unsigned char*)animData, fileSize, "nsa");
                found = true;
                break;
            }
        }

        break;
    }

    if (!found)
    {
        delete animHandle;
        animHandle = nullptr;
    }

    if (animHandle != nullptr)
    {
        animHandle->setRigToAnimMap(rigToAnimMap);
        animHandle->setRig(rig);
        animHandle->setTime(0.f);
    }

	this->m_animHandle = animHandle;
	this->m_id = id;

    strcpy(this->m_animName, name.string().c_str());
}

AnimSourceInterface::~AnimSourceInterface()
{
}

bool AnimSourceInterface::lessThan(AnimSourceInterface* a, AnimSourceInterface* b)
{
    return std::string(a->m_animName) < std::string(b->m_animName);
}