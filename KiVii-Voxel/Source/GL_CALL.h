#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"
#include <queue>
#include <iostream>
#include <string>
#include <unordered_map>

typedef glm::vec2 Vector2f;
typedef glm::ivec2 Vector2i;
typedef glm::vec3 Vector3f;
typedef glm::ivec3 Vector3i;
typedef glm::vec4 Vector4f;

using namespace std;




#define THROW_ERROR(x) cout << "Error on: " << __FILE__ << " at line: " << __LINE__ << " " << x << endl; 


#define ASSERT(x) if(!(x))  __debugbreak();
#define ASSERTWITHMSG(x,strg) AssertAndPrint(x,strg); 

static void AssertAndPrint(bool teste, string msg) {
    if (!teste) {
        cerr << msg;
        __debugbreak();
    }
}


#define GL_CALL(x) GLClearError(); x; ASSERT(gl_Log_Call(#x,__FILE__,__LINE__))

static void GLClearError() {

    while (glGetError() != GL_NO_ERROR) {};
};

static bool gl_Log_Call(const char* function, const char* file, int line) {


    while (GLenum error = glGetError()) {
        string errorType = "";
        switch (error) {
        case 1280:
            errorType = "INVALID_ENUM";
            break;
        case 1281:
            errorType = "INVALID_VALUE";
            break;
        case 1282:
            errorType = "INVALID_OPERATION";
            break;
        case 1283:
            errorType = "INVALID_FRAMEBUFFER_OPERATION";
            break;
        case 1284:
            errorType = "OUT_OF_MEMORY";
            break;
        case 1285:
            errorType = "STACK_UNDERFLOW";
            break;
        case 1286:
            errorType = "STACK_OVERFLOW";
            break;
        }
        cout << "[OpenGl Error]: (" << errorType << ") in function -> " << function << ", at (" << file << ") on line: " << line << endl;
        return false;
    };
    return true;

}

#define GL_SIZEOF(x) TestSize(x)


static unsigned int TestSize(unsigned int dataType) {
    switch (dataType) {
    case GL_FLOAT:
        return sizeof(float);
    case GL_UNSIGNED_INT:
        return sizeof(unsigned int);
    case GL_UNSIGNED_BYTE:
        return sizeof(char);
    default:
        return 0;
    }
}

