// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameMod.h"
#include "TextureMod.generated.h"
UCLASS()
class BEEGAME_API UTextureMod : public UGameMod
{
    GENERATED_BODY()
public:
    virtual void ApplyMod() override;
    virtual void ResetToDefault() override;

    UPROPERTY(BlueprintReadWrite, Category = "Texture Mod")
    UTexture2D* CustomTexture;
};