//
// Created by sergio on 2/13/2020.
//
#define STB_IMAGE_IMPLEMENTATION
#include "Renderer.h"
#include <GLES3/gl3.h>
#include <iostream>
#include <android/log.h>
#include <android/asset_manager_jni.h>
#include <string>
#include <vector>
#include "shader_manager.h"
#include "OBJFileLoader.h"
#include <glm/gtx/component_wise.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "objloader.hpp"
#include "vboindexer.hpp"
#include "Renderer/Mesh.h"
#include "Renderer/ModelLoader.h"
#include "Renderer/Camera.h"
#include "Object/Object.h"
#include "Renderer/FBO.h"
#include "Scene/Scene.h"

using namespace glm;

float tim;
mat4 proj;

float width,height;
Camera cam;


Scene scene;
FBO framebuffer;
FBO fbo2;
Quad quad;
Quad quad1;
void Renderer::init() {







   scene = Scene(Camera(glm::vec3(0.0,-0.9,0.0),proj));
    Shader quadShader = Shader("Shaders/quad.vert","Shaders/quad.frag");
    framebuffer = FBO(width,height,2);
    fbo2 = FBO(width/15,height/15);

    quad = Quad(quadShader);
    quad.setTexture(framebuffer.textures[0]);
    quad.setTexture(framebuffer.textures[1]);

    quad1 = Quad(quadShader);
    quad1.setTexture(fbo2.textures[0]);

}

void Renderer::render() {
    //cam.pos.z=3.0;
    scene.cam.pos.y=1.6;
    scene.cam.pos.z = sin(tim*0.5)*3.0;
    scene.cam.pos.x = cos(tim*0.5)*3.0;
    scene.cam.update();
    tim+=0.07;


    framebuffer.bind();
    scene.Draw();
    framebuffer.ubind();
    fbo2.bind();
    quad.Draw();
    fbo2.ubind();
    glViewport(0,0,width,height);
     quad1.Draw();
}

void Renderer::surfaceChanged(int w,int h) {
     proj = glm::perspective(glm::radians(90.0f),(float)w/(float)h,0.02f,100.f);
     cam.projMatrix = proj;
     cam.update();
    width = w;
    height = h;
    glViewport(0,0,w,h);


}

