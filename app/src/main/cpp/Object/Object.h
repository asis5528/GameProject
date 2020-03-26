//
// Created by sergio on 3/25/2020.
//

#ifndef MY_APPLICATION_OBJECT_H
#define MY_APPLICATION_OBJECT_H


#include <GLES3/gl3.h>

using namespace glm;

struct TransformData{
    vec3 Position;
    vec3 Rotation;
    vec3 Scale;
};
class Object{

public:
    Model model;
    Shader shader;
    mat4 modelMat;
    TransformData data;
    bool transformFlag = 0;
    Object(Model model,Shader shader,TransformData transformData){
        this->model = model;
        this->shader = shader;
        this->data = transformData;
        modelMat = mat4(1.0);
        modelMat = glm::translate(modelMat,data.Position);
        modelMat = glm::rotate(modelMat,data.Rotation.x,vec3(1,0,0));
        modelMat = glm::rotate(modelMat,data.Rotation.y,vec3(0,1,0));
        modelMat = glm::rotate(modelMat,data.Rotation.z,vec3(0,0,1));
        modelMat = glm::scale(modelMat,data.Scale);
    }
    Object(){

    }
    void Draw(Camera camera){
        this->shader.use();

        if(transformFlag){
        modelMat = mat4(1.0);
        modelMat = glm::translate(modelMat,data.Position);
        modelMat = glm::rotate(modelMat,data.Rotation.x,vec3(1,0,0));
        modelMat = glm::rotate(modelMat,data.Rotation.y,vec3(0,1,0));
        modelMat = glm::rotate(modelMat,data.Rotation.z,vec3(0,0,1));
        modelMat = glm::scale(modelMat,data.Scale);
        }
        this->shader.setMat4("view",camera.viewMatrix);
        this->shader.setMat4("proj",camera.projMatrix);
        this->shader.setMat4("model",modelMat);
        if(model.texture.id){
            glActiveTexture(GL_TEXTURE0);
            glUniform1i(glGetUniformLocation(this->shader.ID, "tex"), 0);

            glBindTexture(GL_TEXTURE_2D, this->model.texture.id);
        }

        this->model.Draw(this->shader);
    }
};

class ObjectInit{

    public:
        Object object;
        ObjectInit(char* modelPath,char* vertexShaderPath,char* fragmentShaderPath,TransformData data,char* texturePath = nullptr){
            Model model = Model(modelPath);
            if(texturePath!= nullptr){
                model.LoadTexture(texturePath);
            }
           Shader shader = Shader(vertexShaderPath,fragmentShaderPath);
           object = Object(model,shader,data);

        }
        ObjectInit(){

        }
};
#endif //MY_APPLICATION_OBJECT_H
