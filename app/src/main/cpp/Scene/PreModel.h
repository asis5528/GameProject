//
// Created by sergio on 3/27/2020.
//

#ifndef MY_APPLICATION_PREMODEL_H
#define MY_APPLICATION_PREMODEL_H

class PreModel{
public:
    std::vector<Object> objects;
    PreModel(){
        TransformData data = { vec3(0.0,0.0,0.0),vec3(0.0),vec3(0.2)};
        ObjectInit tr = ObjectInit("Models/terrain.obj","Shaders/terrain.vert","Shaders/terrain.frag",data,"Textures/terrain.png");
        objects.push_back(tr.object);
        ObjectInit tre = ObjectInit("Models/tree.obj","Shaders/tree.vert","Shaders/tree.frag",data,"Textures/tree.png");
        objects.push_back(tre.object);
    }

};

#endif //MY_APPLICATION_PREMODEL_H
