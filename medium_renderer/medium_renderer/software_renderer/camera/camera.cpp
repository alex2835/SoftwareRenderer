
#include "camera.h"


namespace renderer
{

    // Constructor with vectors
    Camera::Camera(const gm::vec3& position, float yaw, float pitch, const gm::vec3& up)
        :
        MovementSpeed(SPEED),
        MouseSensitivity(SENSITIVTY),
        Fov(FOV)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }


    // Constructor with scalar values
    Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
        :
        MovementSpeed(SPEED),
        MouseSensitivity(SENSITIVTY),
        Fov(Fov)
    {
        Position = gm::vec3(posX, posY, posZ);
        WorldUp = gm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }


    // Returns the view matrix calculated using Eular Angles and the LookAt Matrix
    gm::mat4 Camera::get_lookat()
    {
        return gm::lookat(Position, Position + Front, Up);
    }

    gm::mat4 Camera::get_projection(int width, int height)
    {
        float aspect = (float)width / height;
        return gm::projection(aspect, Fov, 0.1f, 100.0f);
    }


    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position -= Front * velocity;
        if (direction == BACKWARD)
            Position += Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }


    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void Camera::ProcessMouseMovement(float xMousePos, float yMousePos)
    {
        float xoffset = (Mouse_x - xMousePos) * MouseSensitivity;
        float yoffset = (Mouse_y - yMousePos) * MouseSensitivity;

        Mouse_x = xMousePos;
        Mouse_y = yMousePos;

        Yaw -= xoffset;
        Pitch -= yoffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (Pitch > 89.0f)
            Pitch = 89.0f;

        if (Pitch < -89.0f)
            Pitch = -89.0f;

        // Update Front, Right and Up Vectors using the updated Eular angles
        updateCameraVectors();
    }

    void Camera::ProcessMouseMovementShift(float xoffset, float yoffset)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw -= xoffset;
        Pitch -= yoffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        
        if (Pitch < -89.0f)
            Pitch = -89.0f;

        // Update Front, Right and Up Vectors using the updated Eular angles
        updateCameraVectors();
    }


    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void Camera::ProcessMouseScroll(float yoffset)
    {
        if (Fov >= 1.0f && Fov <= 90.0f)
            Fov -= yoffset;

        if (Fov <= 1.0f)
            Fov = 1.0f;

        if (Fov >= 90.0f)
            Fov = 90.0f;
    }


    // Calculates the front vector from the Camera's (updated) Eular Angles
    void Camera::updateCameraVectors()
    {
        // Calculate the new Front vector
        gm::vec3 front;
        front.x = cosf(gm::radians(Yaw)) * cosf(gm::radians(Pitch));
        front.y = sinf(gm::radians(Pitch));
        front.z = sinf(gm::radians(Yaw)) * cosf(gm::radians(Pitch));
        Front = front.get_normalized();
        // Also re-calculate the Right and Up vector
        Right = (Front ^ WorldUp).get_normalized();  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = (Right ^ Front).get_normalized();
    }

}