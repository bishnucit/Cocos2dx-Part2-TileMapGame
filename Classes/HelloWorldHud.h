#ifndef __HELLOWORLD_HUD_H__
#define __HELLOWORLD_HUD_H__

#include "cocos2d.h"

class HelloWorldHud : public cocos2d::CCLayer
{
	cocos2d::CCLabelTTF *_label;
public:
	virtual bool init();
	void numCollectedChanged(int numCollected);

	CREATE_FUNC(HelloWorldHud);
};

#endif