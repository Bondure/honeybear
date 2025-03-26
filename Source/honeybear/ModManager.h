// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/NoExportTypes.h"
#include "ModManager.generated.h"

class UGameMod;

UCLASS()
class BEEGAME_API UModManager : public UObject
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "Mods")
    void LoadAllMods();

    UFUNCTION(BlueprintCallable, Category = "Mods")
    void ApplyMod(UGameMod* Mod);

    UPROPERTY(BlueprintReadOnly, Category = "Mods")
    TArray<UGameMod*> LoadedMods;

private:
    void LoadModsFromDirectory(const FString& Directory, TSubclassOf<UGameMod> ModClass);
};