#pragma once


#include "../geometry/geometry.h"


namespace renderer
{

    // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };


    // Default camera values
    const static float YAW = 0.0f;
    const static float PITCH = 0.0f;
    const static float SPEED = 3.0f;
    const static float SENSITIVTY = 0.25f;
    const static float ZOOM = 45.0f;


    // An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
    struct Camera
    {
        // Camera Attributes
        gm::vec3 Position;
        gm::vec3 Front;
        gm::vec3 Up;
        gm::vec3 Right;
        gm::vec3 WorldUp;
        // Eular Angles
        float Yaw;
        float Pitch;
        // Camera options
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;


        // Constructor with vectors
        Camera(const gm::vec3& position = gm::vec3(0.0f, 0.0f, 0.0f),
               const gm::vec3& up = gm::vec3(0.0f, 1.0f, 0.0f),
               float yaw = YAW,
               float pitch = PITCH);


        // Constructor with scalar values
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);


        // Returns the view matrix calculated using Eular Angles and the LookAt Matrix
        gm::mat4 get_lookat();


        // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
        void ProcessKeyboard(Camera_Movement direction, float deltaTime);


        // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
        void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);


        // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
        void ProcessMouseScroll(float yoffset);

    private:
        // Calculates the front vector from the Camera's (updated) Eular Angles
        void updateCameraVectors();

    };

}