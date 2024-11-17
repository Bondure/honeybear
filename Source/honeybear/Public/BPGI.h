#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BPGI.generated.h"
UCLASS()
class HONEYBEAR_API UMyGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    UMyGameInstance();

    UPROPERTY(BlueprintReadWrite, Category = "Player Data")
    int PlayerMoney;

    UPROPERTY(BlueprintReadWrite, Category = "Honey Prices")
    TArray<float> HoneyPrices;

   /* UFUNCTION(BlueprintCallable, Category = "Initialization")
    void InitializeGameData();

    UFUNCTION(BlueprintCallable, Category = "Networking")
    void SendDataToServer(const FString& DataName, const FString& DataValue);

    UFUNCTION(BlueprintCallable, Category = "Networking")
    void GetDataFromServer(const FString& DataName);*/

    // Новые функции для работы с ресурсами
    UFUNCTION(BlueprintCallable, Category = "Resources")
    void UpdatePlayerResources(const FString& GameUUID, const FString& Username, float NewMoney, float NewHoneyPrice);

    UFUNCTION(BlueprintCallable, Category = "Resources")
    void GetResourcesFromServer(const FString& GameUUID, const FString& Username);

    void OnUpdateResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
    void OnGetResourcesResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};