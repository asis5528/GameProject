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
void Renderer::init() {


    model = Model("Models/model.obj");
    terrain = Model("Models/terrain.obj");
    tree = Model("Models/tree.obj");


     shader = Shader("Shaders/shader.vert","Shaders/shader.frag");
    terrainShader = Shader("Shaders/terrain.vert","Shaders/terrain.frag");
    treeShader = Shader("Shaders/tree.vert","Shaders/tree.frag");


    terrain.LoadTexture("Textures/terrain.png");
    tree.LoadTexture("Textures/tree.png");
    cam = Camera(glm::vec3(0.0,-0.9,0.0),proj);

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

    shader.use();

    shader.setMat4("model",mod);
    shader.setMat4("view",cam.viewMatrix);
    shader.setFloat("time",time);
    shader.setMat4("proj",proj);

    model.Draw(shader);
    shader.ubind();

    terrainShader.use();
    terrainShader.setMat4("model",mod);
    terrainShader.setMat4("view",cam.viewMatrix);
    terrainShader.setFloat("time",time);
    terrainShader.setMat4("proj",proj);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(terrainShader.ID, "tex"), 0);

    glBindTexture(GL_TEXTURE_2D, terrain.texture.id);
    terrain.Draw(terrainShader);
    terrainShader.ubind();

    treeShader.use();
    treeShader.setMat4("model",mod);
    treeShader.setMat4("view",cam.viewMatrix);
    treeShader.setFloat("time",time);
    treeShader.setMat4("proj",proj);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(treeShader.ID, "tex"), 0);
    glBindTexture(GL_TEXTURE_2D, tree.texture.id);
    tree.Draw(treeShader);
    treeShader.ubind();


}

void Renderer::surfaceChanged(int w,int h) {
     proj = glm::perspective(glm::radians(90.0f),(float)w/(float)h,0.02f,100.f);
     cam.projMatrix = proj;
     cam.update();

    glViewport(0,0,w,h);


}

