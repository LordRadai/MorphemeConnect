#include "AnimSourceInterface.h"
#include <string>
#include <filesystem>

AnimSourceInterface::AnimSourceInterface()
{
}

AnimSourceInterface::AnimSourceInterface(const char* filename, int id)
{	
    void* animData = NULL;
    int64_t animSize = 0;
    int64_t fileSize = NMP::NMFile::allocAndLoad(filename, &animData, &animSize);
    MR::AnimationSourceHandle* animHandle = new MR::AnimationSourceHandle;

    std::filesystem::path name = std::filesystem::path(filename).filename();

    if (fileSize > -1)
        animHandle->openAnimation((unsigned char*)animData, fileSize, "nsa");
    else
    {
        delete animHandle;
        animHandle = nullptr;
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