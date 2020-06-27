#pragma once

#include "../geometry/geometry.h"

enum class LightType
{
    DirLight,
    PointLight,
    FloodLight
};

namespace renderer
{
    using namespace gm;
    
    struct Light
    {
        LightType type = LightType::PointLight;
    
        float intensity = 1.0f;
    
        vec3 position;
        vec3 direction;
    
        float cutOff;
    
        float constant;
        float linear;
        float quadratic;
    };

    inline Light create_spot_lighter(const vec3& position,
        float in_intensity = 1.0f,
        float linear = 0.007f,
        float quadratic = 0.017f)
    {
        Light out;
        out.type = LightType::PointLight;
        out.position = position;
        out.linear = linear;
        out.quadratic = quadratic;
        return out;
    }

    inline Light create_dir_lighter(const vec3& direction, float in_intensity = 0.3f)
    {
        Light out;
        out.type = LightType::DirLight;
        out.intensity = in_intensity;
        out.direction = normalize(direction);
        return out;
    }
}