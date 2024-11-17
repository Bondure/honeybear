#include "BPGI.h"
#include "HttpModule.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "Logging/LogMacros.h"
#include "Interfaces/IHttpResponse.h" 
UMyGameInstance::UMyGameInstance()
{
    PlayerMoney = 0; // Инициализация денег
}

// Функция для обновления ресурсов игрока
void UMyGameInstance::UpdatePlayerResources(const FString& GameUUID, const FString& Username, float NewMoney, float NewHoneyPrice)
{
    // Создаем JSON объект для обновления ресурсов
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    JsonObject->SetNumberField(TEXT("money"), NewMoney);
    JsonObject->SetNumberField(TEXT("honey_price"), NewHoneyPrice);

    // Преобразуем JSON объект в строку
    FString OutputString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

    // Формируем URL для обновления ресурсов игрока
    FString URL = FString::Printf(TEXT("https://2025.nti-gamedev.ru/api/games/%s/players/%s/"), *GameUUID, *Username);

    // Создаем HTTP запрос
    TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &UMyGameInstance::OnUpdateResponseReceived);
    Request->SetURL(URL);
    Request->SetVerb(TEXT("PUT"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    Request->SetContentAsString(OutputString);
    Request->ProcessRequest();
}

// Обработчик ответа после обновления ресурсов
void UMyGameInstance::OnUpdateResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid())
    {
        FString ResponseContent = Response->GetContentAsString();
        UE_LOG(LogTemp, Log, TEXT("Resources updated successfully: %s"), *ResponseContent);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to update resources: %s"), *Request->GetURL());
    }
}

// Функция для получения ресурсов с сервера
void UMyGameInstance::GetResourcesFromServer(const FString& GameUUID, const FString& Username)
{
    // Формируем URL для получения ресурсов
    FString URL = FString::Printf(TEXT("https://2025.nti-gamedev.ru/api/games/%s/players/%s/resources/"), *GameUUID, *Username);

    // Создаем HTTP запрос
    TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &UMyGameInstance::OnGetResourcesResponseReceived);
    Request->SetURL(URL);
    Request->SetVerb(TEXT("GET"));
    Request->ProcessRequest();
}

// Обработчик ответа после получения ресурсов
void UMyGameInstance::OnGetResourcesResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid())
    {
        // Обработка JSON-ответа
        TSharedPtr<FJsonObject> JsonResponse;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(*Response->GetContentAsString());

        if (FJsonSerializer::Deserialize(Reader, JsonResponse))
        {
            // Извлечение денег и цены на мед
            PlayerMoney = JsonResponse->GetNumberField(TEXT("money"));
            HoneyPrices.Add(JsonResponse->GetNumberField(TEXT("honey_price")));

            UE_LOG(LogTemp, Log, TEXT("Money: %d, Honey Price: %f"), PlayerMoney, HoneyPrices.Last());
        }
        
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get resources: %s"), *Request->GetURL());
    }
}