#include <Geode/modify/PlayLayer.hpp>
#include <random>

using namespace geode::prelude;

int justALittleTreat(int min, int max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);
	return distrib(gen);
}

class $modify(YesTobyWeSeeTheFit, PlayLayer) {
	struct Fields {
		bool triggeredOnce = false;
		int chosenPercentage;
		CCSprite* aLittleTreat = nullptr;
	};
	
	void setupHasCompleted() {
		PlayLayer::setupHasCompleted();

		auto fields = m_fields.self();
		auto winSize = CCDirector::sharedDirector()->getWinSize();

		float x = winSize.width / 2.f;
		float y = winSize.height / 2.f;

		fields->aLittleTreat = CCSprite::create("radiation.png"_spr);
		fields->chosenPercentage = justALittleTreat(10, 90);

		fields->aLittleTreat->setPosition({x, y - 20.f});
		fields->aLittleTreat->setOpacity(0);
		fields->aLittleTreat->setScale(0.7);

		log::info("gonna give u guys a lil treat at {}%", fields->chosenPercentage);

		this->addChild(fields->aLittleTreat, 1000);
	}

	void postUpdate(float p0) {
		PlayLayer::postUpdate(p0);

		auto fields = m_fields.self();

		if (fields->triggeredOnce) return;

		int percent = this->getCurrentPercentInt();
		if (percent == fields->chosenPercentage) {
			auto hehe = CCSequence::create(
				CCSpawn::create(
					CCEaseInOut::create(CCMoveBy::create(0.65f, {0.f, 20.f}), 2.f),
					CCEaseInOut::create(CCFadeIn::create(0.65f), 2.f),
					nullptr
				),
				CCDelayTime::create(4.f),
				CCSpawn::create(
					CCEaseInOut::create(CCMoveBy::create(0.65f, {0.f, -20.f}), 2.f),
					CCEaseInOut::create(CCFadeOut::create(0.65f), 2.f),
					nullptr
				),
				nullptr
			);

			fields->aLittleTreat->runAction(hehe);
			fields->triggeredOnce = true;
		}
		
	}
};