//============================================================================
// Name        : Sandbox.cpp
// Author      : Constantin Sandmann
// Version     :
// Copyright   : (c) check
// Description : Main Application
//============================================================================

#include <iostream>
#include <thread>
//plugins
#include "PlayerPlugins/PlayerSpotify.h"
#include "ReaderPlugins/ReaderFile.h"
//main stuff
#include "AudioDatabase.h"
#include "Manager.h"
#include "Webserver.h"
#include "Configuration.h"
#include "./Logging/BaseLogger.h"

int main() {
	//initialize config and logging
	ClConfiguration oConfig;
	ClBaseLogger::init(oConfig.getLoggerConfig());
	//initialize components
	ClWebserver oWebserver;
	ClAudioDatabase oAudioDb;
	ClPlayerSpotify oSpotifyPlayer(oConfig.getSpotifyConfig());
	ClReaderFile oReader(oConfig.getReaderConfig());
	//create manager
	ClManager oManager(&oReader, &oAudioDb);
	oManager.registerPlayer(&oSpotifyPlayer);
	//start threads
	std::thread oReaderThread = std::thread(&ClReaderFile::start, &oReader);
	std::thread oManagerThread = std::thread(&ClManager::start, &oManager);
	//wait for threads to finish
	oManagerThread.join();
	oReaderThread.join();
	return 0;
}
