#include <Geode/modify/LevelSelectLayer.hpp>

using namespace geode::prelude;

class $modify(CoolerLSLayer, LevelSelectLayer) {
	struct Fields {
		int m_levelPageNum = 0;
	};
	
	bool init(int page) {
		if (!LevelSelectLayer::init(page)) return false;

		FMODAudioEngine::sharedEngine()->stopAllMusic();
		CoolerLSLayer::startMusic();

		m_fields->m_levelPageNum = page;

		return true;
	}

	void onNext(CCObject* sender) {
		LevelSelectLayer::onNext(nullptr);
		m_fields->m_levelPageNum = m_fields->m_levelPageNum + 1;
		if (m_fields->m_levelPageNum >= 24) {
			m_fields->m_levelPageNum = 0;
		};
		
		geode::log::debug("yeah", m_fields->m_levelPageNum);
		CoolerLSLayer::startMusic();
	}

	void onPrev(CCObject* sender) {
		LevelSelectLayer::onPrev(nullptr);
		m_fields->m_levelPageNum = m_fields->m_levelPageNum - 1;
		if (m_fields->m_levelPageNum < 0) {
			m_fields->m_levelPageNum = 23;
		};

		geode::log::debug("yeah", m_fields->m_levelPageNum);
		CoolerLSLayer::startMusic();
	}

	void startMusic() {
		switch (m_fields->m_levelPageNum) {
			case 22:
			FMODAudioEngine::sharedEngine()->playMusic("tower01.mp3", true, 1.0, 1);
			break;
			case 23:
			break;
			default:
			FMODAudioEngine::sharedEngine()->playMusic(LevelTools::getAudioFileName(m_fields->m_levelPageNum), true, 1.0, 1);
			break;
		};
	}
};