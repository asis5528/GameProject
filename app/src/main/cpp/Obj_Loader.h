//
// Created by sergio on 2/27/2020.
//

#ifndef ANDROIDGAMEPROJECT_OBJ_LOADER_H
#define ANDROIDGAMEPROJECT_OBJ_LOADER_H

#include <vector>
#include "glm/glm/glm.hpp"
#include "Mesh.h"


class OBJ_Load{

    public:
        OBJ_Load(char* filePath) {
            AAsset* file = AAssetManager_open(mgr,filePath, AASSET_MODE_BUFFER);

            size_t fileLength = AAsset_getLength(file);

            char* modelData = new char[fileLength];
            AAsset_read(file, modelData, fileLength);
            std::string line;
            std::istringstream iss(modelData);

            Vertex vert;


            while(std::getline(iss,line)){
                std::istringstream in(line);

                std::string type;
                in>>type;
                
                float x,y,z;
                if(type == "v"){
                    in>>x;
                    in>>y;
                    in>>z;
                    vert.Position = glm::vec3(x,y,z);
                 //   __android_log_print(ANDROID_LOG_DEBUG,"print","%f",x);
                }
                else if(type == "vt"){
                    in>>x;
                    in>>y;
                    vert.TexCoords = glm::vec2(x,y);

                }
                else if(type == "vn"){
                    in>>x;
                    in>>y;
                    in>>z;
                    vert.Normal = glm::vec3(x,y,z);
                    
                }

            }

        }

};



#endif //ANDROIDGAMEPROJECT_OBJ_LOADER_H
