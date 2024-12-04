#include "YourGameInstance.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Json.h"
#include "JsonUtilities.h"

UYourGameInstance::UYourGameInstance()
{
    // Инициализация HP переменных
    HP0 = HoneyPrice[0];
    HP1 = HoneyPrice[1];
    HP2 = HoneyPrice[2];
    HP3 = HoneyPrice[3];
    HP4 = HoneyPrice[4];
}

// Метод для отправки HTTP запроса
void UYourGameInstance::MakeHttpRequest()
{
    // Создание и настройка HTTP запроса
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetURL("https://2025.nti-gamedev.ru/api/games/f9b4bd0c-9da6-45e7-9885-e475cd80ad74/players/");
    HttpRequest->SetVerb("POST");

    // Установка заголовка Content-Type
    HttpRequest->SetHeader("Content-Type", "application/json");

    // Формирование JSON-объекта для создания игрока с ресурсами
    FString RequestBody = FString::Printf(TEXT("{\"name\": \"%s\", \"resources\": {\"Money\": %d, \"HP0\": %d, \"HP1\": %d, \"HP2\": %d, \"HP3\": %d, \"HP4\": %d}}"),
        *UserName, Money, HP0, HP1, HP2, HP3, HP4);
    // Преобразование строки в массив байтов
    TArray<uint8> RequestData;
    RequestData.Append((uint8*)TCHAR_TO_UTF8(*RequestBody), RequestBody.Len());

    // Установка содержимого запроса
    HttpRequest->SetContent(RequestData);

    // Обработка ответа
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UYourGameInstance::OnResponseReceived);

    // Отправка запроса
    HttpRequest->ProcessRequest();
}

// Метод для регистрации игрока
void UYourGameInstance::RegPlayer()
{
    // Здесь вы можете установить значения переменных, если необходимо
    UserName = "N";  // Пример, замените на реальное имя игрока
    UUID = "f9b4bd0c-9da6-45e7-9885-e475cd80ad74"; // Пример, замените на реальный UUID игрока
    Money = 100; // Пример, замените на реальную сумму

    // Вызываем метод для отправки HTTP запроса
    MakeHttpRequest();
}

// Метод для вывода сообщения
void UYourGameInstance::PrintMessage(FString Message, FLinearColor TextColor, float Duration, bool bPrintToScreen, bool bPrintToLog)
{
    if (bPrintToScreen)
    {
        UKismetSystemLibrary::PrintString(this, Message, true, true, TextColor, Duration);
    }

    if (bPrintToLog)
    {
        UE_LOG(LogTemp, Log, TEXT("%s"), *Message);
    }
}

// Обработка ответа на HTTP запрос
void UYourGameInstance::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid())
    {
        // Обработка успешного ответа
        FString ResponseString = Response->GetContentAsString();
        PrintMessage("Response: " + ResponseString, FLinearColor::Green, 5.0f, true, true); //Added boolean parameters for printing
    }
    else
    {
        // Обработка ошибки
        FString ErrorString = Response.IsValid() ? Response->GetContentAsString() : "Unknown Error"; //Handle potential null response
        PrintMessage("Request failed! " + ErrorString, FLinearColor::Red, 5.0f, true, true); //Added boolean parameters for printing
    }
}
void UYourGameInstance::GetPlayerResources(FString PlayerUsername)
{
    // Создание и настройка HTTP запроса
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

    // Формирование URL с UUID игры и именем пользователя
    FString URL = FString::Printf(TEXT("https://2025.nti-gamedev.ru/api/games/%s/players/%s/"), *UUID, *PlayerUsername);
    HttpRequest->SetURL(URL);
    HttpRequest->SetVerb("GET");

    // Обработка ответа
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UYourGameInstance::OnPlayerResourcesResponseReceived);

    // Отправка запроса
    HttpRequest->ProcessRequest();

}
void UYourGameInstance::OnPlayerResourcesResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid())
    {
        // Получаем ответ как строку
        FString ResponseString = Response->GetContentAsString();
        BodyTest = ResponseString;

        // Парсинг JSON-ответа
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(ResponseString);

        if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
        {
            // Получаем объект ресурсов
            TSharedPtr<FJsonObject> ResourcesObject = JsonObject->GetObjectField("resources");
            if (ResourcesObject.IsValid())
            {
                Money = ResourcesObject->GetNumberField("Money");
                HP0 = ResourcesObject->GetNumberField("HP0");
                HP1 = ResourcesObject->GetNumberField("HP1");
                HP2 = ResourcesObject->GetNumberField("HP2");
                HP3 = ResourcesObject->GetNumberField("HP3");
                HP4 = ResourcesObject->GetNumberField("HP4");

                PrintMessage(
                    FString::Printf(TEXT("Received player resources: Money=%d, HP0=%d, HP1=%d, HP2=%d, HP3=%d, HP4=%d"),
                        Money, HP0, HP1, HP2, HP3, HP4),
                    FLinearColor::Green,
                    5.0f
                );
            }
            else
            {
                PrintMessage("Failed to find resources object", FLinearColor::Red, 5.0f);
            }
        }
        else
        {
            PrintMessage("Failed to parse JSON response", FLinearColor::Red, 5.0f);
        }
    }
    else
    {
        // Обработка ошибки запроса
        PrintMessage("Failed to get player resources", FLinearColor::Red, 5.0f);
    }
}
void UYourGameInstance::PutPlayerResources(FString PlayerName)
{
    // Создание и настройка HTTP запроса
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

    // Формирование URL с UUID игры и именем пользователя
    FString URL = FString::Printf(TEXT("https://2025.nti-gamedev.ru/api/games/%s/players/%s/"), *UUID, *PlayerName);
    HttpRequest->SetURL(URL);
    HttpRequest->SetVerb("PUT");
    // Установка заголовка Content-Type
    HttpRequest->SetHeader("Content-Type", "application/json");

    // Формирование JSON-объекта для создания игрока с ресурсами
    FString RequestBody = FString::Printf(TEXT("{\"name\": \"%s\", \"resources\": {\"Money\": %d, \"HP0\": %d, \"HP1\": %d, \"HP2\": %d, \"HP3\": %d, \"HP4\": %d}}"),
        *PlayerName, Money, HP0, HP1, HP2, HP3, HP4);
    // Преобразование строки в массив байтов
    TArray<uint8> RequestData;
    RequestData.Append((uint8*)TCHAR_TO_UTF8(*RequestBody), RequestBody.Len());

    // Установка содержимого запроса
    HttpRequest->SetContent(RequestData);
    // Отправка запроса
    HttpRequest->ProcessRequest();
}
void UYourGameInstance::CreateLog(FString Price, int NVar,FString Name) {
    // Создание и настройка HTTP запроса
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

    // Формирование URL с UUID игры и именем пользователя
    FString URL = FString::Printf(TEXT("https://2025.nti-gamedev.ru/api/games/%s/logs/"), *UUID);
    HttpRequest->SetURL(URL);
    HttpRequest->SetVerb("POST");
    // Установка заголовка Content-Type
    HttpRequest->SetHeader("Content-Type", "application/json");
    FString NewComment = "change in the price of honey " + Price;
    FString RequestBody = FString::Printf(TEXT("{\"comment\": \"%s\", \"player_name\": \"%s\", \"resources_changed\": {\"%s\": \"%d\"}}"),
       *NewComment, *Name, *Price, NVar);
}