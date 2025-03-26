#include "TextureMod.h"
#include "bpchar_bee.h"
#include "Materials/MaterialInstanceDynamic.h"

void UTextureMod::ApplyMod()
{
    if (!CustomTexture) return;

    // Создаем динамический материал
    UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(BeeBaseMaterial, this);
    DynMaterial->SetTextureParameterValue("BeeTexture", CustomTexture);

    // Применяем материал
    TArray<AActor*> Bees;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABeeCharacter::StaticClass(), Bees);

    for (AActor* BeeActor : Bees)
    {
        if (ABeeCharacter* Bee = Cast<ABeeCharacter>(BeeActor))
        {
            Bee->GetMesh()->SetMaterial(0, DynMaterial);
        }
    }
}