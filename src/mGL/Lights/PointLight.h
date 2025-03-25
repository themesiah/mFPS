#ifndef MGL_POINTLIGHT
#define MGL_POINTLIGHT

#include "Light.h"

namespace mGL
{
    class PointLight : public Light
    {
    public:
        PointLight(tinyxml2::XMLElement *element);
        virtual ~PointLight();
        void Set() override;

    protected:
#ifdef EDITOR_MODE
        virtual bool ShowImGui() override;
#endif
    private:
        float mRange;
        float mMinIntensity;
    };
}

#endif