// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Win_TestSideScrollerTarget : TargetRules
{
	public Win_TestSideScrollerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Win_TestSideScroller" } );
	}
}
