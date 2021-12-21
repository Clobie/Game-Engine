/////////////////////////////////////////////////////////////////////////
// aaVersion_and_Notes.h
/////////////////////////////////////////////////////////////////////////
#pragma once

#define FRAMEWORK_VERSION "1.01"

/////////////////////////////////////////////////////////////////////////
// Structure
/////////////////////////////////////////////////////////////////////////
// 
// 
// 
// 
// 
// 
//  D3DClass     SpriteClass      FontClass
//     |            \			  /
//     ```````````GraphicsClass````  InputClass      TimerClass       PlayerClass
//				   \					|				 /				 /
//					`````````````````GameClass```````````````````````````
//										|
//									SystemClass
//										|
//									   Main


// 
// 
//       AnimatedSpriteClass   FontClass			 
//                   \          /							   
//  D3DClass		  SpriteClass							    PlayerClass       ObjectClass     LevelClass
//		|				   |											   \	  /					  /
//		``````````````GraphicsClass	    SoundClass      InputClass			GameClass`````````````````
//						   |			    |				|					|
//			                ```````````````````SystemClass```````````````````````
//										            |
//									               Main




// SystemClass -> GraphicsClass -> D3DClass
// SystemClass -> SoundClass
// SystemClass -> InputClass
// SystemClass -> TimerClass
// SystemClass -> FileClass
// SystemClass -> GameClass
// SystemClass -> NetClass -> ServerClass
// SystemClass -> NetClass -> ClientClass
// 
// GameClass -> PlayerClass -> ObjectClass -> StatsClass
// GameClass -> LevelClass -> ProgressionClass
// GameClass -> 
// GameClass -> 
// 
// 
// 
// 
// 
// GraphicsClass -> D3DClass
// GraphicsClass -> AnimatedSpriteClass -> SpriteClass
// GraphicsClass -> FontClass
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
