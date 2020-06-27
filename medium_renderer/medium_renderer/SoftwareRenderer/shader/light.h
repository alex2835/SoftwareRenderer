#pragma once

#include "../geometry/geometry.h"

using namespace gm;

//namespace renderer
//{

    enum class LightType
    {
        DirLight,
        PointLight,
        FloodLight
    };

    struct Light
    {
        LightType type = LightType::PointLight;

        gm::vec3 position;
        gm::vec3 direction;

        float cutOff;

        float constant;
        float linear;
        float quadratic;
    };
    

    inline Light create_spot_lighter(const vec3& position, 
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

    inline Light create_dir_lighter(const vec3& direction)
    {
        Light out;
        out.type = LightType::DirLight;
        out.direction = direction;
        return out;
    }

//}

