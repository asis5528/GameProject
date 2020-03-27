//
// Created by sergio on 3/27/2020.
//

#ifndef MY_APPLICATION_SCENE_H
#define MY_APPLICATION_SCENE_H

#include "PreModel.h"
class Scene{
public:
    Camera cam;
    std::vector<Object> objects;
    Scene(Camera camera){
        cam = camera;
        objects = PreModel().objects;
    }
    Scene(){

    }

    void Draw(){
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
        for(Object object:objects){
            object.Draw(cam);

        }

    }
};
#endif //MY_APPLICATION_SCENE_H
