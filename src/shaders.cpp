#include "shaders.h"


namespace LootSpillage
{
    void LootShaders::Load()
    {
        BaseShader =  FormUtil::Form::GetFormFromMod("LootSpillage.esp", 0x5900)->As<TESEffectShader>(); 
        WeaponShader = FormUtil::Form::GetFormFromMod("LootSpillage.esp", 0x14C03)->As<TESEffectShader>(); 
        ValuableShader = FormUtil::Form::GetFormFromMod("LootSpillage.esp", 0x14C02)->As<TESEffectShader>(); 
        ConsumableShader = FormUtil::Form::GetFormFromMod("LootSpillage.esp", 0x14C01)->As<TESEffectShader>(); 
        ArmorShader = FormUtil::Form::GetFormFromMod("LootSpillage.esp", 0x14C04)->As<TESEffectShader>(); 
        
    }
    void LootShaders::QueueLootShader(TESObjectREFR *refr)
    {

        std::jthread wait(ApplyDelayedShader, refr); 
        wait.detach(); 
    }
    void LootShaders::ApplyLootShader(TESObjectREFR *refr)
    {
        

        if (!refr) return; 
        
        // if (!refr->Is3DLoaded()) return;
        ReadLocker locker(dataLock); 
        auto* baseObject = refr->GetBaseObject(); 
        SKSE::log::info("Shader applied to object {} of type {}", baseObject->GetName(), baseObject->GetFormType()); 

        TESEffectShader* shader; 

        switch(baseObject->GetFormType())
        {
            case FormType::AlchemyItem:
                shader = ConsumableShader; 
                break;
            case FormType::Ingredient:
                shader = ConsumableShader; 
            case FormType::Armor:
                shader = ArmorShader; 
                break;
            case FormType::Weapon:
                shader = WeaponShader; 
            case FormType::KeyMaster:
                shader = ValuableShader; 
                break;
            
            
            default:
            shader = BaseShader; 
            
        }
        if (baseObject->IsGold() || baseObject->IsSoulGem()) shader = ValuableShader; 
        
        
         
        // shader = WeaponShader; 
        refr->InstantiateHitShader(shader, Duration, nullptr, false, false); 
    }
    void LootShaders::Configure()
    {
        WriteLocker locker(dataLock); 
        float fallOff = Settings::GetShaderFallOff(); 
        Duration = Settings::GetShaderDuration(); 

        // BaseShader->data.edgeEffectFallOff = fallOff; 
        // WeaponShader->data.edgeEffectFallOff = fallOff; 
        // ValuableShader->data.edgeEffectFallOff = fallOff; 
        // ConsumableShader->data.edgeEffectFallOff = fallOff; 
        // ArmorShader->data.edgeEffectFallOff = fallOff;

        ConfigureShader(BaseShader, Settings::GetBaseShaderColor(), fallOff); 
        ConfigureShader(WeaponShader, Settings::GetWeaponShaderColor(), fallOff); 
        ConfigureShader(ValuableShader, Settings::GetValuableShaderColor(), fallOff); 
        ConfigureShader(ConsumableShader, Settings::GetConsumableShaderColor(), fallOff); 
        ConfigureShader(ArmorShader, Settings::GetArmorShaderColor(), fallOff); 
        

        // BaseShader->data.edgeColor = Settings::GetBaseShaderColor(); 
        // WeaponShader->data.edgeColor = Settings::GetWeaponShaderColor(); 
        // ValuableShader->data.edgeColor = Settings::GetValuableShaderColor(); 
        // ConsumableShader->data.edgeColor = Settings::GetConsumableShaderColor(); 
        // ArmorShader->data.edgeColor = Settings::GetArmorShaderColor(); 
    }
    void LootShaders::ApplyDelayedShader(TESObjectREFR *refr)
    {

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        ApplyLootShader(refr); 
    }
    void LootShaders::ConfigureShader(TESEffectShader *shader, Color color, float fallOff)
    {

        shader->data.edgeEffectFallOff = fallOff; 
        shader->data.edgeColor = color; 
        shader->data.colorKey1 = color; 
        shader->data.colorKey2 = color; 
        shader->data.colorKey3 = color; 
    }
}