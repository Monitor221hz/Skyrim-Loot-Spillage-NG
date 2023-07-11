#pragma once 
using namespace RE;

#include "util.h"
#include <shared_mutex>
#include "settings.h"
#include <unordered_set>
namespace LootSpillage
{


    class LootShaders 
    {
        using Shader = TESEffectShader; 

        public: 
        
        static void Load();


        static void QueueLootShader(TESObjectREFR* refr); 
        static void ApplyLootShader(TESObjectREFR* refr); 

        static void Configure(); 


        static void AddLootReference(TESObjectREFR* refr)
        {
            WriteLocker locker(dataLock); 

            activeReferences.emplace(refr); 
        }
        static void ApplyDelayedShader(TESObjectREFR* refr); 

        static bool IsLootReference(TESObjectREFR* refr)
        {
            ReadLocker rLocker(dataLock); 
            
            bool isLoot = activeReferences.contains(refr); 
            if (isLoot)
            {
                rLocker.unlock();
                WriteLocker wLocker(dataLock); 
                activeReferences.erase(refr); 
            }
            return isLoot; 
        }


        private: 


        static void ConfigureShader(TESEffectShader* shader, Color color, float fallOff); 
        
        using Lock = std::shared_mutex;
        using ReadLocker = std::shared_lock<Lock>;
        using WriteLocker = std::unique_lock<Lock>;

        static inline Lock dataLock;
    

        static inline Shader* BaseShader; 
        static inline Shader* ConsumableShader; 

        static inline Shader* ValuableShader; 
        //keyword 0008F95A
        
        static inline Shader* WeaponShader; 

        static inline Shader* ArmorShader; 

        static inline std::vector<BGSKeyword*> ValuableKeywords; 

        static inline float Duration; 

        static inline std::unordered_set<TESObjectREFR*> activeReferences; 
    };
}