#include "log.h"
#include "event.h"
#include "settings.h"
#include "shaders.h"
#include "hook.h"
void OnDataLoaded()
{
   
}

void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
{
	switch (a_msg->type) {
	case SKSE::MessagingInterface::kDataLoaded:
        LootSpillage::DeathEventHandler::GetSingleton()->Install(); 
		LootSpillage::Settings::Load(); 
		LootSpillage::LootShaders::Load(); 
		LootSpillage::LootShaders::Configure(); 
		break;
	case SKSE::MessagingInterface::kPostLoad:
		break;
	case SKSE::MessagingInterface::kPreLoadGame:
		break;
	case SKSE::MessagingInterface::kPostLoadGame:
		LootSpillage::Settings::Load(); 
		LootSpillage::LootShaders::Configure(); 
        break;
	case SKSE::MessagingInterface::kNewGame:
		
		LootSpillage::LootShaders::Configure(); 
		break;
	}
}

SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    SKSE::Init(skse);
	SetupLog();


    auto messaging = SKSE::GetMessagingInterface();
	if (!messaging->RegisterListener("SKSE", MessageHandler)) {
		return false;
	}

	

	
    return true;
}