//
// Created by sergio on 3/25/2020.
//

#ifndef MY_APPLICATION_OBJECT_H
#define MY_APPLICATION_OBJECT_H


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

    Object(Model model,Shader shader,TransformData transformData){
        this->model = model;
        this->shader = shader;
        this->data = transformData;
    }
    Object(){

    }
    void Draw(Camera camera){
        this->shader.use();
        this->shader.setMat4("view",camera.viewMatrix);
        this->model.Draw(this->shader);
    }
};

class ObjectInit{

    public:
        Object object;
        ObjectInit(char* modelPath,char* vertexShaderPath,char* fragmentShaderPath,TransformData data,char* texturePath = nullptr){
            Model model = Model(modelPath);
           Shader shader = Shader(vertexShaderPath,fragmentShaderPath);
           object = Object(model,shader,data);
        }
};
#endif //MY_APPLICATION_OBJECT_H
