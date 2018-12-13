
#ifndef _3D_MESH_MANAGER_H_
#define _3D_MESH_MANAGER_H_

#include <unordered_map>

#include "base/CCVector.h"
#include "base/ccTypes.h"
#include "base/CCProtocols.h"
#include "renderer/CCGLProgramState.h"
#include "3d/CCBundle3DData.h"
#include "3d/CCMeshVertexIndexData.h"

NS_CC_BEGIN

///////////////////////////////////////////////////////
/**
 * Sprite3DCache
 * @brief the cache data of Sprite3D, use to speed up Sprite3D::create
 */
class CC_DLL Sprite3DCache
{
public:
    struct Sprite3DData
    {
        Vector<MeshVertexData*>   meshVertexDatas;
        Vector<GLProgramState*>   glProgramStates;
        NodeDatas*      nodedatas;
        MaterialDatas*  materialdatas;
        ~Sprite3DData()
        {
            if (nodedatas)
                delete nodedatas;
            if (materialdatas)
                delete materialdatas;
            meshVertexDatas.clear();
            glProgramStates.clear();
        }
    };
    
    /**get & destroy*/
    static Sprite3DCache* getInstance();
    static void destroyInstance();

    /**
     * get the SpriteData struct
     *
     * @lua NA
     */
    Sprite3DData* getSpriteData(const std::string& key) const;
    
    /**
     * add the SpriteData into Sprite3D by given the specified key
     *
     * @lua NA
     */
    bool addSprite3DData(const std::string& key, Sprite3DData* spritedata);
    
    /**remove the SpriteData from Sprite3D by given the specified key*/
    void removeSprite3DData(const std::string& key);
    
    /**remove all the SpriteData from Sprite3D*/
    void removeAllSprite3DData();
    
    Sprite3DCache();
    ~Sprite3DCache();
    
protected:
    
    
    static Sprite3DCache*                        _cacheInstance;
    std::unordered_map<std::string, Sprite3DData*> _spriteDatas; //cached sprite data
};

NS_CC_END

#endif