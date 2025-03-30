#ifndef MGL_POINTLIGHT
#define MGL_POINTLIGHT

#include "Light.h"

namespace mGL
{

    struct PointLightBuffer
    {
        glm::vec4 colorIntensity;
        glm::vec4 positionRange;
        glm::mat4 matrix;
    };

    class PointLight : public Light
    {
    public:
        PointLight(tinyxml2::XMLElement *element);
        virtual ~PointLight();
        void Set(const size_t &offset) override;
        virtual BindBufferTarget GetBindBufferTarget() const override { return BindBufferTarget::Point; };
        virtual size_t GetBufferSize() const override { return sizeof(PointLightBuffer); };

    protected:
#ifdef EDITOR_MODE
        virtual bool ShowImGui() override;
#endif
    private:
        float mRange;
    };
}

#endif