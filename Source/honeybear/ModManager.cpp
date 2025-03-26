#include "ModManager.h"
#include "SoundMod.h"
#include "TextureMod.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"

void UModManager::LoadAllMods()
{
    LoadedMods.Empty();

    // Загрузка звуков
    LoadModsFromDirectory(FPaths::ProjectContentDir() + "/Mods/Sounds/", USoundMod::StaticClass());

    // Загрузка текстур
    LoadModsFromDirectory(FPaths::ProjectContentDir() + "/Mods/Textures/", UTextureMod::StaticClass());
}

void UModManager::LoadModsFromDirectory(const FString& Directory, TSubclassOf<UGameMod> ModClass)
{
    TArray<FString> Files;
    IFileManager::Get().FindFiles(Files, *Directory, TEXT("*"));

    for (const FString& File : Files)
    {
        const FString FullPath = Directory + File;
        
        UGameMod* NewMod = NewObject<UGameMod>(this, ModClass);
        NewMod->FilePath = FullPath;
        NewMod->ModName = FPaths::GetBaseFilename(File);

        // Загрузка ассета
        if (ModClass == USoundMod::StaticClass())
        {
            USoundMod* SoundMod = Cast<USoundMod>(NewMod);
            SoundMod->CustomSound = LoadObject<USoundWave>(nullptr, *FullPath);
        }
        else if (ModClass == UTextureMod::StaticClass())
        {
            UTextureMod* TextureMod = Cast<UTextureMod>(NewMod);
            TextureMod->CustomTexture = LoadObject<UTexture2D>(nullptr, *FullPath);
        }

        LoadedMods.Add(NewMod);
    }
}