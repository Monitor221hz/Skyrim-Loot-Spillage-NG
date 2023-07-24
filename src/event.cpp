
#include "event.h"

namespace LootSpillage
{
    RE::BSEventNotifyControl DeathEventHandler::ProcessEvent(const TESDeathEvent *a_event, RE::BSTEventSource<TESDeathEvent> *a_eventSource)
    {

        using Result = RE::BSEventNotifyControl; 


        auto* ref = a_event->actorDying.get(); 
        if (ref->GetFormType() != FormType::ActorCharacter || !ref->Is3DLoaded()) return Result::kContinue; 
        auto* actor = ref->As<Actor>(); 
        if (actor->IsEssential()) return Result::kContinue; 
        // SKSE::log::info("Actor {} dead", actor->GetActorBase()->GetName()); 
        LootHandler::DropInventory(actor); 

        return Result::kContinue; 
    }

}