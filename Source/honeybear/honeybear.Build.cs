using UnrealBuildTool;

public class honeybear : ModuleRules
{
    public honeybear(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // Добавьте необходимые модули в зависимости
        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "HTTP",
            "Json",             // Добавьте этот модуль
            "JsonUtilities"     // И этот также
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        // Установите порядок включения
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

        // Разкомментируйте, если вы используете Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Разкомментируйте, если вы используете онлайн-функции
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // Чтобы включить OnlineSubsystemSteam, добавьте его в раздел плагинов в файле uproject с установленным атрибутом Enabled
    }
}
