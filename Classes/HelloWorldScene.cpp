#include "HelloWorldScene.h"
#include "AppMacros.h"
USING_NS_CC;
using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("TileMap", "Arial", TITLE_FONT_SIZE);

    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
   tileMap = CCTMXTiledMap::create("C:/Users/bisprasad/Desktop/TileMap1.tmx");
    this->addChild(tileMap);
    CCTMXLayer *background = tileMap->layerNamed("Background");
	CCTMXObjectGroup *objectGroup = tileMap->objectGroupNamed("Objects");
	/*CCDictionary *spawnPoint = objectGroup->objectNamed("SpawnPoint");
	
	CCString *pX = (CCString*)spawnPoint->objectForKey("x");
	CCString *pY = (CCString*)spawnPoint->objectForKey("y");
 */

	cocos2d::CCDictionary *spawnPoint = objectGroup->objectNamed("SpawnPoint");
	CCAssert(spawnPoint != NULL, "SpawnPoint object not found");
	CCString *pX = (CCString*)spawnPoint->objectForKey("x");
	CCString *pY = (CCString*)spawnPoint->objectForKey("y");
	 
	 int x = pX->intValue();
	 int y = pY->intValue();
	y = (tileMap->getMapSize().height*tileMap->getTileSize().height)-y-24;
	 this->addChild(tileMap );

	player = CCSprite::create("C:/Users/bisprasad/Desktop/Player.png");
	
	 player->setPosition(ccp(x,y ));
	
	 this->addChild(player);
		
	this->setTouchEnabled(true);

	this->setViewPointCenter(player->getPosition());
	 meta = tileMap->layerNamed("Meta");
	 meta->setVisible(false);
	_numCollected = 0;

    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::setViewPointCenter(CCPoint position)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int x = MIN(position.x,winSize.width/2);
	int y = MIN(position.y,winSize.height/2);
	x = MIN(x,(tileMap->getMapSize().width * tileMap->getTileSize().width)-winSize.width/2);
	y = MIN(y,(tileMap->getMapSize().height * tileMap->getTileSize().height)-winSize.height/2);
	CCPoint actualPosition = ccp(x,y);
	int x1 = winSize.width/2;
	int y1 = winSize.height/2;
	CCPoint centerofView = ccp(x1,y1); 
	int X11 = centerofView.x-  position.x  ;
	int Y11	= position.y - centerofView.y  ;
	this->setPosition(ccp(123,-53));
 
	//this->setPosition(ccp(X11,Y11));
}



bool HelloWorld::CCTouchesBegan(CCTouch *touch, CCEvent *event)
{
	return true;
}
void HelloWorld::CCTouchesEnded(CCTouch *touch, CCEvent *event)
{
	CCPoint touchLocation  = touch ->getLocationInView();
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	touchLocation = this->convertToNodeSpace(touchLocation);
	touchLocation = this->convertToWorldSpace(touchLocation);

	CCPoint playerPos = player->getPosition();
	CCPoint diff = ccpSub(touchLocation,playerPos);
	if(fabs(diff.x) > fabs(diff.y))
	{
		if(diff.x > 0)
		{
			playerPos.x += tileMap->getTileSize().width;
		}
		else
		{
			playerPos.x -= tileMap->getTileSize().width;
		}
	}
	else
	{
		if(diff.y > 0)
		{
			playerPos.y += tileMap->getTileSize().height;
		}
		else
		{
			playerPos.y -= tileMap->getTileSize().height;
		}
	}
	CCLOG("%d", (playerPos));

	if ( playerPos.x <= (tileMap->getMapSize().width * tileMap->getMapSize().width) &&
        playerPos.y <= (tileMap->getMapSize().height * tileMap->getMapSize().height) &&
        playerPos.y >= 0 &&
        playerPos.x >= 0 )
	{
		this->setPlayerPosition(playerPos);
	}
	this->setViewPointCenter(player->getPosition());
}

	



void HelloWorld::setPlayerPosition(CCPoint position)
{
	  CCPoint tileCoord = this->tileCoordForPosition(position);
	int tileGid =  meta->tileGIDAt(tileCoord);
	if (tileGid)
	{
		CCDictionary  *properties = tileMap->propertiesForGID(tileGid);
		if (properties)
		{
			CCString *collision = (CCString*)properties->valueForKey("Collidable");
			if (collision && (collision->compare ("True") == 0))
			{
				 
				return;
			}

			
		}

		CCString *collectible = (CCString*)properties->valueForKey("Collectable");
		if (collectible && (collectible->compare ("True") == 0))
		{
			meta->removeTileAt(tileCoord);
			foreground->removeTileAt(tileCoord);
			_numCollected++;
			_hud->numCollectedChanged(_numCollected);
		}
	}

	 
	 player->setPosition(position);
}


void HelloWorld::registerWithTouchDispatcher()
{
    // CCDirector::getTouchDispatcher()->addTargetedDelegate(this, INT_MIN, true);
	CCDirector::sharedDirector()->getTouchDispatcher( )->addTargetedDelegate(this,-129,false);
	
}


CCPoint HelloWorld::tileCoordForPosition(CCPoint position)
{
	int x = position.x /tileMap->getTileSize().width;
	int y  = ((tileMap->getMapSize().height * tileMap->getTileSize().height) - position.y) / tileMap->getTileSize().height;
	return ccp(x,y);
}
