#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "tilemap_parallax_nodes\CCTMXTiledMap.h"
#include "tilemap_parallax_nodes\CCTMXLayer.h"
#include "tilemap_parallax_nodes\CCTMXObjectGroup.h"
#include "tilemap_parallax_nodes\CCParallaxNode.h"
#include "tilemap_parallax_nodes\CCTileMapAtlas.h"
#include "tilemap_parallax_nodes\CCTMXXMLParser.h"
#include "HelloWorldHud.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
	//cocos2d::CCSprite *player;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
	 
	cocos2d::CCTMXTiledMap *tileMap;
	cocos2d::CCTMXLayer *background;
	void  setViewPointCenter(cocos2d::CCPoint position);
	 void registerWithTouchDispatcher();
	bool  CCTouchesBegan (cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	void CCTouchesEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	cocos2d::CCSprite *player;
	void setPlayerPosition(cocos2d::CCPoint position);
	 cocos2d::CCDictionary *spawnPoint;
	cocos2d::CCPoint *centerofView;
	cocos2d::CCTMXLayer *meta;
	cocos2d::CCTMXLayer *foreground;
	cocos2d::CCPoint  tileCoordForPosition(cocos2d::CCPoint position);
	CC_SYNTHESIZE(int, _numCollected, NumCollected);CC_SYNTHESIZE(HelloWorldHud *, _hud, Hud);
};

enum
{tag = 1};

#endif // __HELLOWORLD_SCENE_H__
