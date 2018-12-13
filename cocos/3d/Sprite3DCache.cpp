#include "Sprite3DCache.h"
#include "3d/CCSprite3DMaterial.h"

NS_CC_BEGIN

Sprite3DCache* Sprite3DCache::_cacheInstance = nullptr;
Sprite3DCache* Sprite3DCache::getInstance()
{
    if (_cacheInstance == nullptr)
        _cacheInstance = new (std::nothrow) Sprite3DCache();
    return _cacheInstance;
}
void Sprite3DCache::destroyInstance()
{
    if (_cacheInstance)
    {
        delete _cacheInstance;
        _cacheInstance = nullptr;
    }
}

Sprite3DCache::Sprite3DData* Sprite3DCache::getSpriteData(const std::string& key) const
{
    auto it = _spriteDatas.find(key);
    if (it != _spriteDatas.end())
        return it->second;
    return nullptr;
}

bool Sprite3DCache::addSprite3DData(const std::string& key, Sprite3DCache::Sprite3DData* spritedata)
{
    auto it = _spriteDatas.find(key);
    if (it == _spriteDatas.end())
    {
        _spriteDatas[key] = spritedata;
        return true;
    }
    return false;
}

void Sprite3DCache::removeSprite3DData(const std::string& key)
{
    auto it = _spriteDatas.find(key);
    if (it != _spriteDatas.end())
    {
        delete it->second;
        _spriteDatas.erase(it);
    }
}

void Sprite3DCache::removeAllSprite3DData()
{
    for (auto& it : _spriteDatas) {
        delete it.second;
    }
    _spriteDatas.clear();
}

Sprite3DCache::Sprite3DCache()
{
    
}
Sprite3DCache::~Sprite3DCache()
{
    removeAllSprite3DData();
}

NS_CC_END