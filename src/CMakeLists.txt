target_sources(${GLUCOSE_EXE_NAME}
PUBLIC
    Camera.h
    Camera.cpp
    Scene.h
    Scene.cpp
    Frame.h
    Frame.cpp
    Renderer.h
    Renderer.cpp
    Maths.h
    Maths.cpp
)

add_subdirectory(objects)
