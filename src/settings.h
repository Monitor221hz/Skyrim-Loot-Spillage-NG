#pragma once

#include "SimpleIni.h"

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

            SKSE::log::info("DropOptions | DropAll: {} | DropArmor: {} | DropWeapons: {} | DropOther {}", DropOptions.DropAll, DropOptions.DropArmor, DropOptions.DropWeapons, DropOptions.DropOther); 
        }


        [[nodiscard]] static bool ShouldDropAll() { return DropOptions.DropAll; }

        [[nodiscard]] static bool ShouldDropArmor() { return DropOptions.DropArmor; }

        [[nodiscard]] static bool ShouldDropWeapons() { return DropOptions.DropWeapons; }

        [[nodiscard]] static bool ShouldDropOther() { return DropOptions.DropOther; }



        private: 

        static inline DroppedLoot DropOptions; 

    };   
}