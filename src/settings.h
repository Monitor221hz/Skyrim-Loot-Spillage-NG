#pragma once

#include "SimpleIni.h"


using namespace RE; 
namespace LootSpillage
{
    class Settings
    {


        public: 

        struct DroppedLoot
        {

            bool DropAll = true; 

            bool DropArmor = false; 

            bool DropWeapons = false; 

            bool DropOther = false; 

            bool DropUnplayable = false; 

            bool AutoLootGold = false; 
        };

        struct ActorTargets
        {
            bool IncludeCreatures = false; 

        };

        struct Shaders
        {
            float Duration = 60.0f; 
            float FallOff = 1.0f; 

            uint32_t BaseColor = 0xffffff;
            uint32_t WeaponColor = 0xfa6502; 
            uint32_t ArmorColor = 0x02e5fa;
            uint32_t ConsumableColor = 0x02fa8b;
            uint32_t ValuableColor = 0xfad502;

        };


        static void Load()
        {
            constexpr auto path = L"Data/SKSE/Plugins/LootSpillage/Settings.ini";

            CSimpleIniA ini;
            ini.SetUnicode();

            SI_Error status = ini.LoadFile(path);

            if (status < 0) 
            {
                SKSE::log::info("Settings load failed"); 
            }
            else 
            {
                SKSE::log::info("Settings loaded successfully");
            }
            
            DropOptions.DropAll = ini.GetBoolValue("Drops", "DropAll", true);
            DropOptions.DropArmor = ini.GetBoolValue("Drops", "DropArmor", false); 
            DropOptions.DropWeapons  = ini.GetBoolValue("Drops", "DropWeapons", false);  
            DropOptions.DropOther = ini.GetBoolValue("Drops", "DropOther", false);
            DropOptions.DropUnplayable = ini.GetBoolValue("Drops", "DropUnplayable", false); 
            // DropOptions.AutoLootGold = ini.GetBoolValue("Drops", "AutoLootGold", true);

            ActorOptions.IncludeCreatures = ini.GetBoolValue("Actors", "CreatureDrops", false);  

            ShaderOptions.Duration = static_cast<float>(ini.GetDoubleValue("Shaders", "VfxDuration", 60.0)); 
            ShaderOptions.FallOff = static_cast<float>(ini.GetDoubleValue("Shaders", "VfxFallOff", 1.0)); 
            
            // ShaderOptions.BaseColor = ini.GetLongValue("Shaders", "BaseColor", 0xffffff);
            // ShaderOptions.ArmorColor = ini.GetLongValue("Shaders", "ArmorColor", 0x02e5fa);
            // ShaderOptions.WeaponColor = ini.GetLongValue("Shaders", "WeaponColor", 0xfa6502);
            // ShaderOptions.ConsumableColor = ini.GetLongValue("Shaders", "ConsumableColor", 0x02fa8b);
            // ShaderOptions.ValuableColor = ini.GetLongValue("Shaders", "ValuableColor", 0xfad502);
            

            SKSE::log::info("DropOptions | DropAll: {} | DropArmor: {} | DropWeapons: {} | DropOther {}", DropOptions.DropAll, DropOptions.DropArmor, DropOptions.DropWeapons, DropOptions.DropOther); 
        }


        [[nodiscard]] static bool ShouldDropAll() { return DropOptions.DropAll; }

        [[nodiscard]] static bool ShouldDropArmor() { return DropOptions.DropArmor; }

        [[nodiscard]] static bool ShouldDropWeapons() { return DropOptions.DropWeapons; }

        [[nodiscard]] static bool ShouldDropUnplayable() { return DropOptions.DropUnplayable; }

        [[nodiscard]] static bool ShouldDropOther() { return DropOptions.DropOther; }

        [[nodiscard]] static bool ShouldLootGold() { return DropOptions.AutoLootGold; }

        [[nodiscard]] static bool IncludeCreatures() { return ActorOptions.IncludeCreatures; }

        [[nodiscard]] static float GetShaderDuration() { return ShaderOptions.Duration; }

        [[nodiscard]] static float GetShaderFallOff() { return ShaderOptions.FallOff; }

        [[nodiscard]] static Color GetBaseShaderColor() { return Color(ShaderOptions.BaseColor); }

        [[nodiscard]] static Color GetArmorShaderColor() { return Color(ShaderOptions.ArmorColor); }

        [[nodiscard]] static Color GetWeaponShaderColor() { return Color(ShaderOptions.WeaponColor); }

        [[nodiscard]] static Color GetConsumableShaderColor() { return Color(ShaderOptions.ConsumableColor); }

        [[nodiscard]] static Color GetValuableShaderColor() { return Color(ShaderOptions.ValuableColor); }

        private: 

        static inline DroppedLoot DropOptions; 
        static inline Shaders ShaderOptions; 
        static inline ActorTargets ActorOptions; 
// BaseColor = 0xffffff

// ArmorColor = 0x7602fa
// ;cc2302
// ;3244a8
// WeaponColor = 0xffffff

// ConsumableColor = 0x4ee004

// ValuableColor = 0xfad502
    };   
}