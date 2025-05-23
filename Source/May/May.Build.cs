// Red Beat, 2023

using UnrealBuildTool;

public class May : ModuleRules {
	public May(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"HeadMountedDisplay",
			"NavigationSystem",
			"AIModule",
			"Niagara",
			"EnhancedInput",
			"GameplayAbilities",
			"UMG",
			"GameplayTasks"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"GameplayTags",
			"Niagara"
		});
	}
}