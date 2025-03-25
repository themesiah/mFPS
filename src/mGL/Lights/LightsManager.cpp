#include "LightsManager.h"
#include "Light.h"

#include "Logger.h"

namespace mGL
{
    LightsManager::LightsManager() : mBase::TemplatedMapVector<Light>(), mDirty(false) {}

    LightsManager::~LightsManager() {}

    void LightsManager::Set() const
    {
        for (std::shared_ptr<Light> light : m_ResourcesVector)
        {
            light->Set();
        }
    }

    bool LightsManager::Add(const std::string &aName, std::shared_ptr<Light> aLight)
    {
        bool result = TemplatedMapVector::Add(aName, aLight);
        if (result)
            mDirty = true;
        return result;
    }

    void LightsManager::Clear()
    {
        TemplatedMapVector::Clear();
        mDirty = true;
    }

    void LightsManager::Destroy()
    {
        TemplatedMapVector::Destroy();
        mDirty = true;
    }

    void LightsManager::Remove(const std::string &aName)
    {
        TemplatedMapVector::Remove(aName);
        mDirty = true;
    }

    void LightsManager::Update()
    {
        Logger::Log("LightsManager", "UPDATE!");
        if (mDirty)
        {
            Logger::Log("LightsManager", "DIRTY!");
            Set();
            mDirty = false;
        }
    }

#ifdef EDITOR_MODE
    void LightsManager::ShowImGui()
    {
        for (std::shared_ptr<Light> light : m_ResourcesVector)
        {
            if (light->StartImGui())
                mDirty = true;
        }
    }
#endif
}