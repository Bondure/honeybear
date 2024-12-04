#include "MD5Final.h"
#include "Misc/ArchiveMD5.h"


FString UMD5Final::ComputeMD5Hash(const FString& Input)
{
    // Создаем объект MD5
    FMD5 MD5;
    MD5.Update((const uint8*)TCHAR_TO_UTF8(*Input), Input.Len());

    // Получаем хэш
    uint8 Digest[16];
    MD5.Final(Digest);

    // Преобразуем хэш в шестнадцатеричную строку
    FString HashString;
    for (int32 i = 0; i < 16; ++i)
    {
        HashString += FString::Printf(TEXT("%02x"), Digest[i]);
    }

    return HashString;
}
