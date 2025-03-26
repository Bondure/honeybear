// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/NoExportTypes.h"
#include "GameMod.generated.h"

UCLASS(Abstract)
class BEEGAME_API UGameMod : public UObject
{
    GENERATED_BODY()
public:
    virtual void ApplyMod() PURE_VIRTUAL(UGameMod::ApplyMod, );
    virtual void ResetToDefault() PURE_VIRTUAL(UGameMod::ResetToDefault, );

    UPROPERTY(BlueprintReadOnly, Category = "Mod")
    FString ModName = "Unnamed Mod";

    UPROPERTY(BlueprintReadOnly, Category = "Mod")
    FString Author = "Unknown";

    UPROPERTY(BlueprintReadOnly, Category = "Mod")
    FString FilePath;
};