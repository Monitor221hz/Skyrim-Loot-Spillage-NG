#include "loot.h"


namespace LootSpillage
{
    
    
    void LootHandler::DropInventory(Actor *actor)
    {

        using Count = std::int32_t;
        using InventoryItemMap = std::map<TESBoundObject*, std::pair<Count, std::unique_ptr<InventoryEntryData>>>;
        

        if (actor->IsPlayerRef()) return;
        if (CreatureFaction && !Settings::IncludeCreatures() && actor->GetFactionRank(CreatureFaction, false) > -1) return;
        InventoryItemMap inventory = actor->GetInventory(); 
        NiPoint3 position = actor->GetPosition(); 
        NiPoint3 angle = actor->GetAngle(); 
        for(auto const& [key, val] : inventory)
        {
             
            DropLoot(actor, key, val);      
            
        }
        //testing hazards
        
    }

    bool LootHandler::CanDrop(TESBoundObject *loot)
    {
        if (Settings::ShouldDropAll()) return true; 

        std::string Name = loot->GetName(); 
        if (!Settings::ShouldDropUnplayable() && (!loot->GetPlayable() || Name.empty() ) ) return false;
        switch(loot->GetFormType())
        {
            case FormType::Weapon:
            return Settings::ShouldDropWeapons(); 

            case FormType::Armor:
            return Settings::ShouldDropArmor(); 
        }
        return Settings::ShouldDropOther(); 
    }

    


    
    void LootHandler::DropLoot(Actor *actor, TESBoundObject *loot, const std::pair<int32_t, std::unique_ptr<InventoryEntryData>> &inventoryData)
    {
        using Count = std::int32_t;
        using InventoryDropMap = std::map<TESBoundObject*, std::pair<Count, std::vector<ObjectRefHandle>>>;


        if (!CanDrop(loot)) return; 
        if (inventoryData.first < 1) return; 
        NiPoint3 position = actor->GetPosition();
        NiPoint3 angle = actor->GetAngle();
        
        float offsetX = Util::Numbers::GenerateRandomFloat(5.0f, 10.0f);
        float offsetY = Util::Numbers::GenerateRandomFloat(5.0f, 10.0f);

        int flipX = Util::Numbers::GenerateRandomInt(0,1);  
        int flipY = Util::Numbers::GenerateRandomInt(0,1); 

        offsetX = (flipX == 1) ? offsetX * -1: offsetX; 
        offsetY = (flipY == 1) ? offsetY * -1 : offsetY; 
        position.x += offsetX; 
        position.y += offsetY;
        position.z += actor->GetHeight() / 2.0f; 

        auto handle = actor->RemoveItem(loot, inventoryData.first, ITEM_REMOVE_REASON::kDropping, nullptr, actor, &position, &angle);
        
        std::vector<ObjectRefHandle> arr; 
        arr.emplace_back(handle); 

        std::pair<Count, std::vector<ObjectRefHandle>> pair(inventoryData.first, arr); 
        actor->GetDroppedInventory().emplace(loot, pair);
        //artobj  = 0xaa01
        
        // auto *obj = FormUtil::Form::GetFormFromMod("LootSpillage.esp", 0x5900)->As<BGSHazard>();
        SKSE::log::info("Dropping item {} with count {} from actor {}", loot->GetName(), inventoryData.first, actor->GetActorBase()->GetName());
        auto* refr = handle.get().get(); 
        LootShaders::AddLootReference(refr); 
        // FormUtil::Reference::PlaceAtReference(refr, obj, false);
        LootShaders::QueueLootShader(refr);

        // AttachMarker(actor, handle);
    }

}