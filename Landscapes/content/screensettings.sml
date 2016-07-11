<?xml version="1.0" encoding="UTF-8"?>
<Settings rootContent="..\..\landscapes\content" rootContentIsRelative="true">

  <Screen name="main">
    <SceneOptions>
      <DefaultCml> main.cml </DefaultCml>
      <ShowTouchPoints> false </ShowTouchPoints>
	    <DirectInput> false </DirectInput>
      <TcpMessages listen="false" ip="localhost" port="9902"/>
      <EditorConnection listen="false" ip="localhost" port="9902"/>
	  <GestureWorks enableGestureWorks="false" manualInput="false"/>
    </SceneOptions>

    <ScreenOptions>
      <WindowSize width="1920" height="1080" fullscreen="true" x="0" y="-32" scale="1.0"/>
      <WindowOptions hideTitleBar="true" windowTitle="Landscapes" enableSceneGestures="true" escKeyExits="true"/>
      <WindowStart show="true" loadAsMat="false" />
      <Graphics viewUpdateMode="full" enabled="false"/>
    </ScreenOptions>
  </Screen>

  <Screen name="mat" create="false">
    <SceneOptions>
      <DefaultCml> mat.cml </DefaultCml>
      <ShowTouchPoints> false </ShowTouchPoints>
      <TcpMessages listen="false" ip="localhost" port="9902"/>
      <EditorConnection listen="false" ip="localhost" port="9902"/>
    </SceneOptions>

    <ScreenOptions>
      <WindowSize width="1024" height="768" fullscreen="false" />
      <WindowOptions hideTitleBar="true" windowTitle="Mat" escKeyExits="true"/>
      <WindowStart show="true" loadAsMat="true" />
    </ScreenOptions>
  </Screen>

</Settings>
