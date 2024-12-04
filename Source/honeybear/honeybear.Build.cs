using UnrealBuildTool;

public class honeybear : ModuleRules
{
    public honeybear(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // �������� ����������� ������ � �����������
        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "HTTP",
            "Json",             // �������� ���� ������
            "JsonUtilities"     // � ���� �����
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        // ���������� ������� ���������
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

        // ����������������, ���� �� ����������� Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // ����������������, ���� �� ����������� ������-�������
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // ����� �������� OnlineSubsystemSteam, �������� ��� � ������ �������� � ����� uproject � ������������� ��������� Enabled
    }
}
