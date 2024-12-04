#include "MD5Final.h"
#include "Misc/ArchiveMD5.h"


FString UMD5Final::ComputeMD5Hash(const FString& Input)
{
    // ������� ������ MD5
    FMD5 MD5;
    MD5.Update((const uint8*)TCHAR_TO_UTF8(*Input), Input.Len());

    // �������� ���
    uint8 Digest[16];
    MD5.Final(Digest);

    // ����������� ��� � ����������������� ������
    FString HashString;
    for (int32 i = 0; i < 16; ++i)
    {
        HashString += FString::Printf(TEXT("%02x"), Digest[i]);
    }

    return HashString;
}
