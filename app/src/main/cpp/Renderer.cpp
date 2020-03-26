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



using namespace glm;

Shader shader;
float tim;
mat4 proj;
Shader terrainShader;
Shader treeShader;
Model model;
Model terrain;
Model tree;
Camera cam;
ObjectInit tr;
ObjectInit tre;
std::vector<Object> objects;
void Renderer::init() {




    cam = Camera(glm::vec3(0.0,-0.9,0.0),proj);
    TransformData data;
    data.Position = vec3(0.0,0.0,0.0);
    data.Rotation = vec3(0.0);
    data.Scale = vec3(0.2);
     tr = ObjectInit("Models/terrain.obj","Shaders/terrain.vert","Shaders/terrain.frag",data,"Textures/terrain.png");
     objects.push_back(tr.object);
    tre = ObjectInit("Models/tree.obj","Shaders/tree.vert","Shaders/tree.frag",data,"Textures/tree.png");
    objects.push_back(tre.object);
    glEnable(GL_DEPTH_TEST);


}

void Renderer::render() {
    cam.pos.z=3.0;
    cam.pos.y=1.6;
    cam.update();
    tim+=0.07;
    unsigned int fbo;
    glGenBuffers(1,&fbo);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
    glm::mat4 mod = glm::mat4(1.0);
    mod = glm::scale(mod,glm::vec3(0.2,0.2,0.2));
    time+=0.01;


   for(Object object:objects){
       object.Draw(cam);
   }
}

void Renderer::surfaceChanged(int w,int h) {
     proj = glm::perspective(glm::radians(90.0f),(float)w/(float)h,0.02f,100.f);
     cam.projMatrix = proj;
     cam.update();

    glViewport(0,0,w,h);


}

