// SoundMod.cpp
#include "SoundMod.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "ConstructorHelpers.h"

// Инициализация статической переменной для класса пчелы
TSubclassOf<AActor> USoundMod::GetBeeBlueprintClass()
{
    // УКАЖИТЕ ПРАВИЛЬНЫЙ ПУТЬ К ВАШЕМУ BLUEPRINT!
    static ConstructorHelpers::FClassFinder<AActor> BeeClassFinder(
        TEXT("/Game/Path/To/Your/Blueprint/bpchar_bee") // Пример: "/Game/Characters/BP_Bee"
    );
    return BeeClassFinder.Class;
}

void USoundMod::ApplyMod()
{
    if (!CustomSound) return;

    // Получаем класс пчелы из Blueprint
    UClass* BeeClass = GetBeeBlueprintClass().Get();
    if (!BeeClass)
    {
        UE_LOG(LogTemp, Error, TEXT("Bee blueprint class not found!"));
        return;
    }

    // Ищем всех пчел в мире
    TArray<AActor*> BeeActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), BeeClass, BeeActors);

    for (AActor* BeeActor : BeeActors)
    {
        // Получаем аудио компонент (убедитесь, что в Blueprint он называется "AudioComponent")
        UAudioComponent* AudioComp = Cast<UAudioComponent>(
            BeeActor->GetComponentByClass(UAudioComponent::StaticClass())
        );

        if (AudioComp)
        {
            AudioComp->SetSound(CustomSound);
            AudioComp->Play();
        }
    }
}

void USoundMod::ResetToDefault()
{
    // Здесь должна быть логика восстановления оригинального звука
    // Например, загрузка дефолтного звука из ссылки
}