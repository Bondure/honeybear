#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Http.h"  // ���������� ������ HTTP
#include "YourGameInstance.generated.h"

/**
 * ����� ��� ���������� ������� ���������� � HTTP ���������
 */
UCLASS()
class HONEYBEAR_API UYourGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    // �����������
    UYourGameInstance();  // ���������� ������������

    // ����������
    UPROPERTY(BlueprintReadWrite, Category = "Default", Meta = (MultiLine = "true"))
    FString BodyTest = "";

    UPROPERTY(BlueprintReadWrite, Category = "Default", Meta = (MultiLine = "true"))
    FString Comment;

    UPROPERTY(BlueprintReadWrite, Category = "Default", Meta = (MultiLine = "true"))
    FString UserName;

    UPROPERTY(BlueprintReadWrite, Category = "Default", Meta = (MultiLine = "true"))
    FString UUID="f9b4bd0c-9da6-45e7-9885-e475cd80ad74";

    UPROPERTY(BlueprintReadWrite, Category = "Default")
    int32 A;

    UPROPERTY(BlueprintReadWrite, Category = "Default")
    int Money=0;

    UPROPERTY(BlueprintReadWrite, Category = "Default")
    TArray<int> HoneyPrice = { 0,333,0,0,0 };

    UPROPERTY(BlueprintReadWrite, Category = "Default")
    float TPlusU;

    UPROPERTY(BlueprintReadWrite, Category = "Default", Meta = (MultiLine = "true"))
    FString Str;

    UPROPERTY(BlueprintReadWrite, Category = "Default")
    TMap<FString, FString> Headers; // ���������� ���������� ����������

    UPROPERTY(BlueprintReadWrite, Category = "Default")
    int32 Integer;

    // ����������� ����������
    UPROPERTY(BlueprintReadWrite, Category = "Default")
    int HP0;

    UPROPERTY(BlueprintReadWrite, Category = "Default")
    int HP1;

    UPROPERTY(BlueprintReadWrite, Category = "Default")
    int HP2;

    UPROPERTY(BlueprintReadWrite, Category = "Default")
    int HP3;

    UPROPERTY(BlueprintReadWrite, Category = "Default")
    int HP4;

    UPROPERTY(BlueprintReadWrite, Category = "Default")
    int CurrentResolutionIndex=0;

    UPROPERTY(BlueprintReadWrite, Category = "Default")
    int FullScrinMode=0;

    UPROPERTY(BlueprintReadWrite, Category = "Default")
    int VsynchAnti_Al=0;

    UPROPERTY(BlueprintReadWrite, Category = "Default")
    bool Vsynch=true;

    UPROPERTY(BlueprintReadWrite, Category = "Default")
    int Shadow = 0;


    UPROPERTY(BlueprintReadWrite, Category = "Default")
    int Lenght = 0;

    // ������
    UFUNCTION(BlueprintCallable, Category = "HTTP")
    void MakeHttpRequest();

    UFUNCTION(BlueprintCallable, Category = "HTTP")
    void RegPlayer();  // ��������� ����� ��� ����������� ������

    UFUNCTION(BlueprintCallable, Category = "Logging")
    void PrintMessage(FString Message, FLinearColor TextColor, float Duration, bool bPrintToScreen = true, bool bPrintToLog = true);

    UFUNCTION(BlueprintCallable, Category = "HTTP")
    void GetPlayerResources(FString PlayerUsername);  // �������� ��� ���������

    UFUNCTION(BlueprintCallable, Category = "HTTP")
    void PutPlayerResources(FString PlayerName);

    UFUNCTION(BlueprintCallable, Category = "HTTP")
    void CreateLog(FString Price, int NVar,FString Name);
private:
    // ��������� ������ �� HTTP ������
    void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
    void OnPlayerResourcesResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
