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
                break; 
            case FormType::KeyMaster:
                shader = ValuableShader; 
                break;
            default:
            shader = BaseShader; 
            
        }
        if (baseObject->IsGold() || baseObject->IsSoulGem()) shader = ValuableShader; 
        
       
         
        // shader = WeaponShader; 
        auto* effect = refr->ApplyEffectShader(shader, Duration, nullptr, false, false);
    //    SKSE::log::info("Shader applied to object {} of type {} | Edge Color {}", baseObject->GetName(), baseObject->GetFormType(), shader->data.edgeColor.ToHex());  
        
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

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        ApplyLootShader(refr); 
    }
    void LootShaders::ConfigureShader(TESEffectShader *shader, Color color, float fallOff)
    {

        shader->data.edgeEffectFallOff = fallOff; 
        // color.alpha = 1; 
        // SKSE::log::info("Shader {}", shader->GetFormEditorID()); 
        // SKSE::log::info("Color Key 1 {}",shader->data.colorKey1.ToHex());
        // SKSE::log::info("Color Key 2 {}", shader->data.colorKey2.ToHex());
        // SKSE::log::info("Color Key 3 {}", shader->data.colorKey3.ToHex());
        // SKSE::log::info("Edge color {}", shader->data.edgeColor.ToHex()); 
        // SKSE::log::info("Fill Color Key 1 {}",shader->data.fillTextureEffectColorKey1.ToHex());
        // SKSE::log::info("Fill Color Key 2 {}", shader->data.fillTextureEffectColorKey2.ToHex());
        // SKSE::log::info("Fill Color Key 3 {}", shader->data.fillTextureEffectColorKey3.ToHex());
        auto& edgeColor = shader->data.edgeColor;
        edgeColor.red = 0;
        edgeColor.blue = 0; 
        edgeColor.green = 0; 
        // shader->data.colorKey1 = color; 
        // shader->data.colorKey2 = color; 
        // shader->data.colorKey3 = color; 

        // SKSE::log::info("Color Key 1 {}",shader->data.colorKey1.ToHex());
        // SKSE::log::info("Color Key 2 {}", shader->data.colorKey2.ToHex());
        // SKSE::log::info("Color Key 3 {}", shader->data.colorKey3.ToHex());
        // SKSE::log::info("Edge color {}", shader->data.edgeColor.ToHex());

        shader->SaveObjectBound();  
        // shader->data.fillTextureEffectColorKey1 = color; 
        // shader->data.fillTextureEffectColorKey2 = color; 
        // shader->data.fillTextureEffectColorKey3 = color; 

        // shader->data.colorKey1ColorAlpha = 100.0;
        // shader->data.colorKey2ColorAlpha = 100.0; 
        // shader->data.colorKey3ColorAlpha = 100.0;  


        
    }
}