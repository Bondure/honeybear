// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameMod.h"
#include "SoundMod.generated.h"

/**
 * 
 */
UCLASS()
class BEEGAME_API USoundMod : public UGameMod
{
    GENERATED_BODY()
public:
    virtual void ApplyMod() override;
    virtual void ResetToDefault() override;

    UPROPERTY(BlueprintReadWrite, Category = "Sound Mod")
    USoundWave* CustomSound;
};