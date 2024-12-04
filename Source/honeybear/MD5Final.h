#pragma once

#include "CoreMinimal.h"
#include "MD5Final.generated.h"

UCLASS()
class HONEYBEAR_API UMD5Final : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Hashing")
    static FString ComputeMD5Hash(const FString& Input);
};
