// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MayEditorTarget : TargetRules
{
	public MayEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("May");
	}
}
