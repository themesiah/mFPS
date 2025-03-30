#include "LightsManager.h"

#include <GL/glew.h>

#include "Light.h"
#include "Logger.h"

namespace mGL
{
    LightsManager::LightsManager() : mBase::TemplatedMapVector<Light>(), mDirty(false) {}

    LightsManager::~LightsManager() {}

    void LightsManager::InitBuffers()
    {
        for (size_t i = 0; i < mSSBOs.size(); ++i)
        {
            glGenBuffers(1, &mSSBOs[i]);
        }
    }

    void LightsManager::Set() const
    {
        std::array<size_t, LIGHT_TYPES_AMOUNT> sizes = {0};
        std::array<size_t, LIGHT_TYPES_AMOUNT> offsets = {0};

        // Get size of buffers
        for (std::shared_ptr<Light> light : m_ResourcesVector)
        {
            sizes[light->GetBindBufferTarget() - FIRST_LIGHT_TYPE] += light->GetBufferSize();
        }

        // Bind light buffers
        for (size_t i = 0; i < LIGHT_TYPES_AMOUNT; ++i)
        {
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, mSSBOs[i]);
            glBufferData(GL_SHADER_STORAGE_BUFFER, sizes[i], nullptr, GL_STATIC_DRAW);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, i + FIRST_LIGHT_TYPE, mSSBOs[i]);

            // Update data on buffer
            for (std::shared_ptr<Light> light : m_ResourcesVector)
            {
                if (light->GetBindBufferTarget() - FIRST_LIGHT_TYPE == i)
                {
                    light->Set(offsets[i]);
                    offsets[i] += light->GetBufferSize();
                }
            }
        }

        // Unbind buffer
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
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
        if (mDirty)
        {
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