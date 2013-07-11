#include "HelloWorldHud.h"
#include "cocos2d.h"

USING_NS_CC;

bool HelloWorldHud::init()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_label = cocos2d::CCLabelTTF::create("0","Verdana-Bold", 18.0);
	_label->setColor(ccc3(0, 0, 0));

	int margin = 10;

	_label->setPosition(ccp(winSize.width - (_label->getContentSize().width / 2) - margin, 
							_label->getContentSize().height / 2 + margin));

	this->addChild(_label);

	return true;
}

void HelloWorldHud::numCollectedChanged(int numCollected)
{
	char *str = (char *)malloc(sizeof(str) * 10);
	sprintf(str, "%d", numCollected);
	_label->setString(str);
	free(str);
}