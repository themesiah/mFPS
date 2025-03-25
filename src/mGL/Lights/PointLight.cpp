#include "PointLight.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <GL/glew.h>

#include "XML/tinyxml2.h"
#include "XML/XML.h"

#ifdef EDITOR_MODE
#include "ImGui/imgui.h"
#endif

namespace mGL
{
    PointLight::PointLight(tinyxml2::XMLElement *element) : Light(element)
    {
        tinyxml2::XMLElement *dataElement = element->FirstChildElement("data");
        mMinIntensity = 0;
        mRange = 0;
        dataElement->QueryFloatAttribute("minIntensity", &mMinIntensity);
        dataElement->QueryFloatAttribute("range", &mRange);
    }

    PointLight::~PointLight() {}

    void PointLight::Set()
    {
        struct
        {
            float range;
            float minIntensity;
            glm::vec4 colorIntensity;
            glm::vec3 position;
        } data;

        data.range = mRange;
        data.minIntensity = mMinIntensity;
        data.colorIntensity.x = mColor.x;
        data.colorIntensity.y = mColor.y;
        data.colorIntensity.z = mColor.z;
        data.colorIntensity.w = mIntensity;

        data.position = glm::vec3((*mMatrix.get())[3]);

        glBindBuffer(GL_SHADER_STORAGE_BUFFER, mSSBO);
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, mSSBO);
    }

#ifdef EDITOR_MODE
    bool PointLight::ShowImGui()
    {
        return false;
    }
#endif
}