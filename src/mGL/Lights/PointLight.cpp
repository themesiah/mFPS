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
        mRange = 0;
        dataElement->QueryFloatAttribute("range", &mRange);
    }

    PointLight::~PointLight() {}

    void PointLight::Set(const size_t &offset)
    {
        PointLightBuffer data;

        data.colorIntensity.x = mColor.x;
        data.colorIntensity.y = mColor.y;
        data.colorIntensity.z = mColor.z;
        data.colorIntensity.w = mIntensity;
        data.matrix = *mMatrix;

        glm::vec3 pos = glm::vec3((*mMatrix.get())[3]);
        data.positionRange = glm::vec4(pos.x, pos.y, pos.z, mRange);

        glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, sizeof(data), &data);
    }

#ifdef EDITOR_MODE
    bool PointLight::ShowImGui()
    {
        bool dirty = false;
        if (ImGui::SliderFloat("Range", &mRange, 0.0f, 50.0f))
        {
            dirty = true;
        }

        return dirty;
    }
#endif
}