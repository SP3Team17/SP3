#include "myapplication.h"
#include <mmsystem.h>

myApplication * myApplication::s_pInstance = NULL;

//Constructor
myApplication::myApplication()
	: theCamera(NULL)
	, theMap(NULL)
	, theBorder(NULL)
	, AGCredits(NULL)
{
	bGameOver = heroInit = bComplete = programInit
    = stopMovement = gameStart = startDialogue2 
	= bFlash = gamePause = bTutorial = tutorialEnd
	= trigger8 = trigger9 = setting = pause = soundinit
	= allowGamePause = false;

	counterFlash = counterTime = 0;

	dTrans7 = dTrans8 = dTrans9 = 
	dTrans1 = dTrans3 = dTrans5 = -600;
	dTrans2 = dTrans4 = dTrans6 = 610;

	theSound = new Sound;
}

//Destructor
myApplication::~myApplication()
{
	//Delete Hero
	if (theHero != NULL)
	{
		delete theHero;
		theHero = NULL;
	}

	//Delete Map
	if (theMap != NULL)
	{
		delete theMap;
		theMap = NULL;
	}

	//Delete Border
	if (theBorder != NULL)
	{
		delete theBorder;
		theBorder = NULL;
	}

	//Delete Camera
	if (theCamera != NULL)
	{
		delete theCamera;
		theCamera = NULL;
	}

	//Delete Shop
	if (theShop != NULL)
	{
		delete theShop;
		theShop = NULL;
	}

	//Delete UI
	if (theUI != NULL)
	{
		delete theUI;
		theUI = NULL;
	}
}

//Return only one instance of myApplication
myApplication* myApplication::getInstance()
{
	if(s_pInstance == NULL)
		s_pInstance = new myApplication();

	return s_pInstance;
}

void myApplication::Update(void) 
{
	//Update Time
	mvcTime* timer=mvcTime::getInstance();
	
		timer->updateTime();

	if ((timeGetTime()-timelastcall)>1000.f/frequency)
	{
		//Calculate the framerate

		timelastcall=timeGetTime();

		//Update Function
		if (gameStart && !gamePause)
		{
			int MobNo=0;
			for(vector<MobInfo*>::iterator it=infoList.begin();it!=infoList.end();++it)
			{
				MobInfo* temp=*it;
				if(temp->active)
					MobNo++;
			}
			if(MobNo==0)
			{
				currentLevel++;
				changeLevel(currentLevel);
			}
			//Check for Game Over
			if (theHero->getAttributes()->getHp() <= 0)
				bGameOver = true;

			//Update Hero
			HeroUpdate();

			//Update Exp System
			theHero->getExp()->Update();

			//Update Stats
			theHero->getAttributes()->Update();

			//Constrain Hero to middle of screen (unless he reaches the border)
			theHero->ConstrainHero(MAP_SCREEN_WIDTH*0.5+LEFT_BORDER, MAP_SCREEN_WIDTH*0.5+LEFT_BORDER, 
								   MAP_SCREEN_HEIGHT*0.5+BOTTOM_BORDER, MAP_SCREEN_HEIGHT*0.5+BOTTOM_BORDER,
								   1.0f, mapOffset_x, mapOffset_y);
	
			testSkill.Update(infoList,theHero->GetPos(),theHero->getDir(),mapOffset_x,mapOffset_y,*theMap);
	
	
			for(vector<Monster*>::iterator it=mobList.begin();it!=mobList.end();++it)
			{
				Monster* temp=*it;
				temp->update(mvcTime::getInstance()->getDelta(),infoList,wallList,mapOffset_x,mapOffset_y,*theMap);
			}

			//testMob.update(mvcTime::getInstance()->getDelta(),infoList,*theHero,wallList,mapOffset_x,mapOffset_y,*theMap);
			//Update Tile Offset
			tileOffset_x = (int)(mapOffset_x / TILE_SIZE);
			tileOffset_y = (int)(mapOffset_y / TILE_SIZE);

			if (tileOffset_x+theMap->getNumOfTiles_ScreenWidth() > theMap->getNumOfTiles_MapWidth())
				tileOffset_x = theMap->getNumOfTiles_MapWidth() - theMap->getNumOfTiles_ScreenWidth();

			if (tileOffset_y+theMap->getNumOfTiles_ScreenHeight() > theMap->getNumOfTiles_MapHeight())
				tileOffset_y = theMap->getNumOfTiles_MapHeight() - theMap->getNumOfTiles_ScreenHeight();
		}
	}
}


void myApplication::HeroUpdate()
{
	Vector3D temp;
	mvcTime* timer=mvcTime::getInstance();
	//Check Collision of the hero before moving Up
	if (!physics::testColMap(theHero->GetPos()-Vector3D(0,5,0), true, false, false, false, theMap,mapOffset_x,mapOffset_y))
	{
		//Do not allow movement when stopMovement is true
		if((myKeys['w'] || myKeys['W']) && !stopMovement)
		{
			moveMeUpDown(true, timer->getDelta());
			bMoving = true;
			temp.y=-1;
		}

		//Check if the user is standing still
		else
			bMoving = false;
	}

	//Check Collision of the hero before moving down
	if (!physics::testColMap(theHero->GetPos()+Vector3D(0,5,0), false, true, false, false, theMap,mapOffset_x,mapOffset_y))
	{
		//Do not allow movement when stopMovement is true
		if((myKeys['s'] || myKeys['S']) && !stopMovement)
		{
			moveMeUpDown(false, timer->getDelta());
			bMoving = true;
			temp.y=1;
		}

		//Check if the user is standing still
		else
			bMoving = false;
	}

	//Check Collision of the hero before moving left
	Vector3D posL; //Fixes the Collision 
	posL.Set(theHero->GetPos().x-7, theHero->GetPos().y); //Buffer of 5
	if (!physics::testColMap(posL, false, false, true, false, theMap,mapOffset_x,mapOffset_y))
	{
		//Do not allow movement when stopMovement is true
		if((myKeys['a'] || myKeys['A']) && !stopMovement)
		{
			moveMeLeftRight(true, timer->getDelta());
			bMoving = true;
			temp.x=-1;
		}

		//Check if the user is standing still
		else
			bMoving = false;
	}

	//Check Collision of the hero before moving right
	Vector3D posR; //Fixes the Collision 
	posR.Set(theHero->GetPos().x+7, theHero->GetPos().y); //Buffer of 5
	if (!physics::testColMap(posR, false, false, false, true, theMap,mapOffset_x,mapOffset_y))
	{
		//Do not allow movement when stopMovement is true
		if((myKeys['d'] || myKeys['D']) && !stopMovement)
		{
			moveMeLeftRight(false, timer->getDelta());
			bMoving = true;
			temp.x=1;
		}
		
		//Check if the user is standing still
		else
			bMoving = false;
	}
	if(temp.Length()!=0)
		theHero->setDir(temp);
}

void myApplication::menuSequence(void)
{
		if (setting && !pause)
		{	
			renderPause();
			if (theUI->getSettingButton(0)->hover)
				theUI->getSettingButton(0)->Render(true, 360, 250, 360, 300);
			else if (theUI->getSettingButton(1)->hover)
				theUI->getSettingButton(1)->Render(true, 360, 250, 360, 300);
			else if (theUI->getSettingButton(2)->hover)
				theUI->getSettingButton(2)->Render(true, 360, 250, 360, 300);
			else
				theUI->getSettingButton(0)->Render(false, 360, 250, 360, 300);
		}
		else if (pause && !setting)
		{
			renderPause();
			if (theUI->getPauseButton(0)->hover)
				theUI->getPauseButton(0)->Render(true, 360, 250, 360, 300);
			else if (theUI->getPauseButton(1)->hover)
				theUI->getPauseButton(1)->Render(true, 360, 250, 360, 300);
			else if (theUI->getPauseButton(2)->hover)
				theUI->getPauseButton(2)->Render(true, 360, 250, 360, 300);
			else
				theUI->getPauseButton(0)->Render(false, 360, 250, 360, 300);
		}
		else
			renderPause();
}

void myApplication::renderScene(void)
{
	//Clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	theCamera->Update();
	calculateFPS();

	//Enable 2D text display and HUD
	theCamera->SetHUD(true);

	//Game has yet to start
	if (!gameStart && programInit)
	{
		renderStartScene();
		if(!soundinit)
		{
			theSound->Stop();
			theSound->PlayMusic(SOUND_DIALOGUE, true, false);
			soundinit = true;
		}
	}

	//Render Start Screen
	if (!programInit)//this one for sound only, feel free to merge with original when you are done.
	{	
		if(!soundinit)
		{
			theSound->PlayMusic(SOUND_BGM, true, false);
			soundinit = true;
		}
	}
	if (!programInit)
	{

		if (!theUI->getStartButton()->hover)
			theUI->getStartButton()->Render(false, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
		else
			theUI->getStartButton()->Render(true, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
	}

	//Game has Started
	if (gameStart)
	{
		//Load Level 1
		if (currentLevel == 1)
			LoadLevel(1);

		//Load Level 2
		else if (currentLevel == 2)
			LoadLevel(2);

		for(vector<Monster*>::iterator it=mobList.begin();it!=mobList.end();++it)
		{
			Monster* temp=*it;
			temp->render();
		}
		//Render Hero
		theHero->RenderHero();
		//testMob.render();
		testSkill.render();

		theUI->renderBackpanel();
		RenderMapBorder();
		glPushMatrix();
			glTranslatef(RESOLUTION_WIDTH*0.8,RESOLUTION_HEIGHT*0.8,0);
			RenderMiniMap(theMap);
		glPopMatrix();
	}
	
	//Game is Paused
	if (gamePause)
	{
		menuSequence();
	}

	//Stacey's Tutorial
	if (bTutorial)
		renderTutorial();

	//Display Game Over Screen
	if (bGameOver)
		renderGameOver();

	//Level Complete Screen
	if (bComplete)
		renderComplete();

	//Open Shop
	if (theShop->open)
		theShop->renderShop();

	//Open Inventory
	if (theHero->getInventory()->open)
		theHero->getInventory()->renderInventory();

	//Do not render over these screens
	if (!bGameOver && !bComplete && gameStart)
	{
		//Display Text On Screen
		DisplayText();
	}

	theCamera->SetHUD(false);

	//Flush off any entity which is not drawn yet, so that we maintain the frame rate.
	glFlush();

	//Swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
	glutPostRedisplay();
}

void myApplication::LoadLevel(short level)
{
	//Init Hero
	if (!heroInit)
	{
		theHero->Init();
		heroInit = true;
	}

	//Load Level 1
	if (level == 1)
	{
		RenderBackground();
		renderGround();

		//Re-Init Map 
		RenderTileMap(theMap);

		RenderHpBar();
	}

	//Load Level 2
	else if (level == 2)
	{
		RenderBackground();
		renderGround();

		//Re-Init Map 
		RenderTileMap(theMap);

		RenderHpBar();
	}
}

void myApplication::changeSize(int w, int h) 
{
	//Prevent a divide by zero, when window is too short
	//you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = (float) (1.0f* w / h);

	//Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	//Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}

void myApplication::KeyboardDown(unsigned char key, int x, int y)
{
	myKeys[key]= true;

	//Keyboard
	switch(key) {

	//Skip Start Scene
	case ' ':
		if (programInit)
		{
			gameStart = allowGamePause = true;
			gamePause = setting = pause = false;
			soundinit = false;
			if(!soundinit)
			{
				theSound->Stop();
				theSound->PlayMusic(SOUND_LEVEL1, true, false);
				soundinit = true;
			}
		}
		break;

	//Increase Player Level
	case '=':
		if (theHero->getAttributes()->getLevel() < 100)
			//theHero->getExp()->setExp(theHero->getExp()->getExpToLevel());
			theHero->getAttributes()->setLevel(theHero->getAttributes()->getLevel()+1);
		break;

	//Pause the game
	case 27:
		if (gameStart && programInit && allowGamePause)
		{
			gamePause = !gamePause;
			pause = true;
			setting = false;
		}
		break;
		
	//Open Shop
	case 'u':
	case 'U':
		if (!bTutorial && gameStart && !theHero->getInventory()->open)
		{
			//Stop movement when Shop is open
			if (theShop->open)
				gamePause = false;
			else
				gamePause = true;

			theShop->open = !theShop->open;
			//Reset Text Toggling
			theShop->healthBought = theShop->invincBought = theShop->NotEnoughCredits =
			theShop->levelBought = theShop->armorBought = false;
		}
		break;

	//Inventory
	case 'i':
	case 'I':
		if (!bTutorial && gameStart && !theShop->open)
		{
			//Stop movement when Inventory is open
			if (theHero->getInventory()->open)
			{
				gamePause = false;
				if(theHero->getInventory()->invincUsed)
				{
					mvcTime* timer=mvcTime::getInstance();
					if(theHero->getInventory()->invincRef==-1)
					{
						theHero->getInventory()->invincRef=timer->insertNewTime(3000);
					}
					else
					{
						timer->changeLimit(theHero->getInventory()->invincRef,3000);
						timer->resetTime(theHero->getInventory()->invincRef);
					}
				}
			}
			else
			{
				gamePause = true;
			}
			theHero->getInventory()->open = !theHero->getInventory()->open;

			//Reset booleans
			if (theHero->getInventory()->open)
				theHero->getInventory()->armorUsed = theHero->getInventory()->levelUsed = 
				theHero->getInventory()->invincUsed = theHero->getInventory()->potionUsed = false;
		}
		break;

	//Load Level 1
	case '1':
		{
			//Do not load level if inventory or shop is opened
			if (!theShop->open && !theHero->getInventory()->open)
			{
				//Trigger Hero Init
				heroInit = false;

				//Re-Init Map
				mapOffset_x = mapOffset_y = tileOffset_x = tileOffset_y = mapFineOffset_x = mapFineOffset_y = 0;
				theMap->Init(MAP_SCREEN_HEIGHT, MAP_SCREEN_WIDTH, RESOLUTION_HEIGHT*2, RESOLUTION_WIDTH*2, TILE_SIZE);
				theMap->LoadMap("MapDesign1.csv");
				processTiles();

				//Set Level to 1
				currentLevel = 1;
			}
			//Item in slot 1 used
			if (theHero->getInventory()->open)
			{
				//Check for Empty Slot
				if (theHero->getInventory()->itemsArray[0]->GetType() != CGoodies::GOODIE_NONE)
				{
					//Check if player Hp is max if type is HEALTH
					if (theHero->getInventory()->itemsArray[0]->GetType() == CGoodies::HEALTH)
					{
						if (theHero->getAttributes()->getHp() < MAX_PLAYER_HP*HP_MULTIPLIER)
						{
							//Execute Item Bonus
							theHero->getInventory()->itemsArray[0]->ExecuteBonus(CGoodies::HEALTH);

							//Delete the Item in slot 1
							theHero->getInventory()->deleteItem(theHero->getInventory()->itemsArray[0]);
						}
					}

					//Exeute Bonus and delete item from Slot
					else
					{
						//Execute Item Bonus
						theHero->getInventory()->itemsArray[0]->ExecuteBonus(theHero->getInventory()->itemsArray[0]->GetType());

						//Delete the Item in slot 1
						theHero->getInventory()->deleteItem(theHero->getInventory()->itemsArray[0]);
					}

					//Toggle Used Text
					switch (theHero->getInventory()->itemsArray[0]->GetType())
					{
					case CGoodies::HEALTH:
						theHero->getInventory()->potionUsed = true;
						theHero->getInventory()->armorUsed = theHero->getInventory()->levelUsed = 
						theHero->getInventory()->invincUsed = false;
						break;
					case CGoodies::ARMOR:
						theHero->getInventory()->armorUsed = true;
						theHero->getInventory()->potionUsed = theHero->getInventory()->levelUsed = 
						theHero->getInventory()->invincUsed = false;
						break;
					case CGoodies::LEVEL:
						theHero->getInventory()->levelUsed = true;
						theHero->getInventory()->armorUsed = theHero->getInventory()->potionUsed = 
						theHero->getInventory()->invincUsed = false;
						break;
					case CGoodies::INVINC:
						theHero->getInventory()->invincUsed = true;
						theHero->getInventory()->armorUsed = theHero->getInventory()->levelUsed = 
						theHero->getInventory()->potionUsed = false;
						break;
					}
				}
			}

			//Health is bought
			if (theShop->open)
			{
				//Create Temp CGoodie
				CGoodies* health = theGoodiesFactory->Create(CGoodies::HEALTH);

				//Check if Credits are enough
				if (theHero->getAttributes()->getAGC() >= health->getCredit())
				{
					//Credits are enough
					theShop->NotEnoughCredits = false;

					//Add item
					theHero->getInventory()->addItem(health);

					//Reduce Credits
					theHero->getAttributes()->setAGC(theHero->getAttributes()->getAGC()-health->getCredit());

					//Toggle Bought Text
					theShop->healthBought = true;
					theShop->invincBought = theShop->levelBought = theShop->armorBought = false;
				}

				//The player has not enough credits
				else
				{
					theShop->NotEnoughCredits = true;
					theShop->healthBought = theShop->invincBought = theShop->levelBought = theShop->armorBought = false;
				}

				//Delete temp Goodie
				delete health;
			}
		}
		break;

	//Load Level 2
	case '2':
		{
			//Do not load level if inventory or shop is opened
			if (!theShop->open && !theHero->getInventory()->open)
			{
				//Trigger Hero Init
				heroInit = false;
				//Re-Init Map
				mapOffset_x = mapOffset_y = tileOffset_x = tileOffset_y = mapFineOffset_x = mapFineOffset_y = 0;
				theMap->Init(MAP_SCREEN_HEIGHT, MAP_SCREEN_WIDTH, RESOLUTION_HEIGHT*2, RESOLUTION_WIDTH*2, TILE_SIZE);
				theMap->LoadMap("MapDesign2.csv");
				processTiles();

				//Set Level to 2
				currentLevel = 2;
			}

			//Item in slot 2 used
			if (theHero->getInventory()->open)
			{
				//Check for Empty Slot
				if (theHero->getInventory()->itemsArray[1]->GetType() != CGoodies::GOODIE_NONE)
				{
					//Check if player Hp is max if type is HEALTH
					if (theHero->getInventory()->itemsArray[1]->GetType() == CGoodies::HEALTH)
					{
						if (theHero->getAttributes()->getHp() < MAX_PLAYER_HP*HP_MULTIPLIER)
						{
							//Execute Item Bonus
							theHero->getInventory()->itemsArray[1]->ExecuteBonus(CGoodies::HEALTH);

							//Delete the Item in slot 2
							theHero->getInventory()->deleteItem(theHero->getInventory()->itemsArray[1]);
						}
					}

					//Exeute Bonus and delete item from Slot
					else
					{
						//Execute Item Bonus
						theHero->getInventory()->itemsArray[1]->ExecuteBonus(theHero->getInventory()->itemsArray[1]->GetType());

						//Delete the Item in slot 1
						theHero->getInventory()->deleteItem(theHero->getInventory()->itemsArray[1]);
					}

					//Toggle Used Text
					switch (theHero->getInventory()->itemsArray[1]->GetType())
					{
					case CGoodies::HEALTH:
						theHero->getInventory()->potionUsed = true;
						theHero->getInventory()->armorUsed = theHero->getInventory()->levelUsed = 
						theHero->getInventory()->invincUsed = false;
						break;
					case CGoodies::ARMOR:
						theHero->getInventory()->armorUsed = true;
						theHero->getInventory()->potionUsed = theHero->getInventory()->levelUsed = 
						theHero->getInventory()->invincUsed = false;
						break;
					case CGoodies::LEVEL:
						theHero->getInventory()->levelUsed = true;
						theHero->getInventory()->armorUsed = theHero->getInventory()->potionUsed = 
						theHero->getInventory()->invincUsed = false;
						break;
					case CGoodies::INVINC:
						theHero->getInventory()->invincUsed = true;
						theHero->getInventory()->armorUsed = theHero->getInventory()->levelUsed = 
						theHero->getInventory()->potionUsed = false;
						break;
					}
				}
			}

			//Armor is bought
			if (theShop->open)
			{
				//Create Temp CGoodie
				CGoodies* armor = theGoodiesFactory->Create(CGoodies::ARMOR);

				//Check if Credits are enough
				if (theHero->getAttributes()->getAGC() >= armor->getCredit())
				{
					//Credits are enough
					theShop->NotEnoughCredits = false;

					//Add item
					theHero->getInventory()->addItem(armor);

					//Reduce Credits
					theHero->getAttributes()->setAGC(theHero->getAttributes()->getAGC()-armor->getCredit());

					//Toggle Bought Text
					theShop->armorBought = true;
					theShop->invincBought = theShop->levelBought = theShop->healthBought = false;
				}

				//The player has not enough credits
				else
				{
					theShop->NotEnoughCredits = true;
					theShop->healthBought = theShop->invincBought = theShop->levelBought = theShop->armorBought = false;
				}

				//Delete temp Goodie
				delete armor;
			}
		}
		break;

	//Load Level 3
	case '3':
		{
			//Do not load level if inventory or shop is opened
			if (!theShop->open && !theHero->getInventory()->open)
			{
				//Trigger Hero Init
				heroInit = false;

				//Re-Init Map
				mapOffset_x = mapOffset_y = tileOffset_x = tileOffset_y = mapFineOffset_x = mapFineOffset_y = 0;
				theMap->Init(MAP_SCREEN_HEIGHT, MAP_SCREEN_WIDTH, RESOLUTION_HEIGHT*2, RESOLUTION_WIDTH*2, TILE_SIZE);
				theMap->LoadMap("MapDesign1.csv");

				//Set Level to 3
				currentLevel = 3;
			}

			//Item in slot 3 used
			if (theHero->getInventory()->open)
			{
				//Check for Empty Slot
				if (theHero->getInventory()->itemsArray[2]->GetType() != CGoodies::GOODIE_NONE)
				{
					//Check if player Hp is max if type is HEALTH
					if (theHero->getInventory()->itemsArray[2]->GetType() == CGoodies::HEALTH)
					{
						if (theHero->getAttributes()->getHp() < MAX_PLAYER_HP*HP_MULTIPLIER)
						{
							//Execute Item Bonus
							theHero->getInventory()->itemsArray[2]->ExecuteBonus(CGoodies::HEALTH);

							//Delete the Item in slot 3
							theHero->getInventory()->deleteItem(theHero->getInventory()->itemsArray[2]);
						}
					}

					//Exeute Bonus and delete item from Slot
					else
					{
						//Execute Item Bonus
						theHero->getInventory()->itemsArray[2]->ExecuteBonus(theHero->getInventory()->itemsArray[2]->GetType());

						//Delete the Item in slot 1
						theHero->getInventory()->deleteItem(theHero->getInventory()->itemsArray[2]);
					}

					//Toggle Used Text
					switch (theHero->getInventory()->itemsArray[2]->GetType())
					{
					case CGoodies::HEALTH:
						theHero->getInventory()->potionUsed = true;
						theHero->getInventory()->armorUsed = theHero->getInventory()->levelUsed = 
						theHero->getInventory()->invincUsed = false;
						break;
					case CGoodies::ARMOR:
						theHero->getInventory()->armorUsed = true;
						theHero->getInventory()->potionUsed = theHero->getInventory()->levelUsed = 
						theHero->getInventory()->invincUsed = false;
						break;
					case CGoodies::LEVEL:
						theHero->getInventory()->levelUsed = true;
						theHero->getInventory()->armorUsed = theHero->getInventory()->potionUsed = 
						theHero->getInventory()->invincUsed = false;
						break;
					case CGoodies::INVINC:
						theHero->getInventory()->invincUsed = true;
						theHero->getInventory()->armorUsed = theHero->getInventory()->levelUsed = 
						theHero->getInventory()->potionUsed = false;
						break;
					}
				}
			}

			//Level is bought
			if (theShop->open)
			{
				//Create Temp CGoodie
				CGoodies* level = theGoodiesFactory->Create(CGoodies::LEVEL);

				//Check if Credits are enough
				if (theHero->getAttributes()->getAGC() >= level->getCredit())
				{
					//Credits are enough
					theShop->NotEnoughCredits = false;

					//Add item
					theHero->getInventory()->addItem(level);

					//Reduce Credits
					theHero->getAttributes()->setAGC(theHero->getAttributes()->getAGC()-level->getCredit());

					//Toggle Bought Text
					theShop->levelBought = true;
					theShop->invincBought = theShop->armorBought = theShop->healthBought = false;
				}

				//The player has not enough credits
				else
				{
					theShop->NotEnoughCredits = true;
					theShop->healthBought = theShop->invincBought = theShop->levelBought = theShop->armorBought = false;
				}

				//Delete temp Goodie
				delete level;
			}
		}
		break;

	//4
	case '4':
		{
			//Item in slot 4 used
			if (theHero->getInventory()->open)
			{
				//Check for Empty Slot
				if (theHero->getInventory()->itemsArray[3]->GetType() != CGoodies::GOODIE_NONE)
				{
					//Check if player Hp is max if type is HEALTH
					if (theHero->getInventory()->itemsArray[3]->GetType() == CGoodies::HEALTH)
					{
						if (theHero->getAttributes()->getHp() < MAX_PLAYER_HP*HP_MULTIPLIER)
						{
							//Execute Item Bonus
							theHero->getInventory()->itemsArray[3]->ExecuteBonus(CGoodies::HEALTH);

							//Delete the Item in slot 4
							theHero->getInventory()->deleteItem(theHero->getInventory()->itemsArray[3]);
						}
					}

					//Exeute Bonus and delete item from Slot
					else
					{
						//Execute Item Bonus
						theHero->getInventory()->itemsArray[3]->ExecuteBonus(theHero->getInventory()->itemsArray[3]->GetType());

						//Delete the Item in slot 1
						theHero->getInventory()->deleteItem(theHero->getInventory()->itemsArray[3]);
					}

					//Toggle Used Text
					switch (theHero->getInventory()->itemsArray[3]->GetType())
					{
					case CGoodies::HEALTH:
						theHero->getInventory()->potionUsed = true;
						theHero->getInventory()->armorUsed = theHero->getInventory()->levelUsed = 
						theHero->getInventory()->invincUsed = false;
						break;
					case CGoodies::ARMOR:
						theHero->getInventory()->armorUsed = true;
						theHero->getInventory()->potionUsed = theHero->getInventory()->levelUsed = 
						theHero->getInventory()->invincUsed = false;
						break;
					case CGoodies::LEVEL:
						theHero->getInventory()->levelUsed = true;
						theHero->getInventory()->armorUsed = theHero->getInventory()->potionUsed = 
						theHero->getInventory()->invincUsed = false;
						break;
					case CGoodies::INVINC:
						theHero->getInventory()->invincUsed = true;
						theHero->getInventory()->armorUsed = theHero->getInventory()->levelUsed = 
						theHero->getInventory()->potionUsed = false;
						break;
					}
				}
			}

			//Invinc is bought
			if (theShop->open)
			{
				//Create Temp CGoodie
				CGoodies* invinc = theGoodiesFactory->Create(CGoodies::INVINC);

				//Check if Credits are enough
				if (theHero->getAttributes()->getAGC() >= invinc->getCredit())
				{
					//Credits are enough
					theShop->NotEnoughCredits = false;

					//Add item
					theHero->getInventory()->addItem(invinc);

					//Reduce Credits
					theHero->getAttributes()->setAGC(theHero->getAttributes()->getAGC()-invinc->getCredit());

					//Toggle Bought Text
					theShop->invincBought = true;
					theShop->levelBought = theShop->armorBought = theShop->healthBought = false;
				}

				//The player has not enough credits
				else
				{
					theShop->NotEnoughCredits = true;
					theShop->healthBought = theShop->invincBought = theShop->levelBought = theShop->armorBought = false;
				}

				//Delete temp Goodie
				delete invinc;
			}
		}
		break;

	//Skills
	case 'z':
		testSkill.procSkills(theHero->GetPos(),theHero->getDir(),Skills::ATTACK);
		break;
	case 'x':
		testSkill.procSkills(theHero->GetPos(),theHero->getDir(),Skills::RANGEAOE);
		break;
	}
}

void myApplication::changeLevel(short nlevel)
{
	if(nlevel>0&&nlevel<4)
	{
		currentLevel=nlevel;
	}
	heroInit = false;

	//Re-Init Map
	mapOffset_x = mapOffset_y = tileOffset_x = tileOffset_y = mapFineOffset_x = mapFineOffset_y = 0;
	theMap->Init(MAP_SCREEN_HEIGHT, MAP_SCREEN_WIDTH, RESOLUTION_HEIGHT*2, RESOLUTION_WIDTH*2, TILE_SIZE);
	char* test=new char;
	sprintf(test,"MapDesign%d.csv",nlevel);
	theMap->LoadMap(test);
	processTiles();
}

void myApplication::KeyboardUp(unsigned char key, int x, int y)
{
	myKeys[key]= false;

	//Keyboard
	switch(key) {
	}
}

void myApplication::MouseMove (int x, int y)
{
	mouseInfo.lastX = x;
	mouseInfo.lastY = y;

	//Check if user is hovering over Button
	for(std::vector<CButton*>::iterator it = theUI->buttonsList.begin(); it != theUI->buttonsList.end(); ++it)
	{
		CButton* theButton = *it;

		//Check if mouse is within Region
		if (x > theButton->getRegionPosX().x && x < theButton->getRegionPosX().y &&
			y > theButton->getRegionPosY().x && y < theButton->getRegionPosY().y)
		{
			//Set Hover to true if mouse is within Region
			theButton->hover = true;
		}
		else
			//Set Hover to false if mouse is not within Region
			theButton->hover = false;
	}
}

void myApplication::MouseClick(int button, int state, int x, int y) 
{
	switch (button) {

		case GLUT_LEFT_BUTTON:

			mouseInfo.mLButtonUp = state;
			mouseInfo.lastX = x;
			mouseInfo.lastY = y;

			cout << "Mouse Clicked!" << endl
				 << "X: " << x << " | " << "Y: " << y << endl << endl;

			if (mouseInfo.mLButtonUp) {

				//Exit program upon mouse click
				//when game is over
				if (bGameOver)
					exit(0);

				//Initiate Program if user clicks Start
				if (theUI->getStartButton()->hover && !programInit)
				{
					programInit = true;
					soundinit = false;
				}

				if (pause == true)
				{
					//Resume Game
					if (theUI->getPauseButton(0)->hover && !setting)
					{
						theSound->PlayMusic(SOUND_CLICK, false, false);
						gamePause = false;
						pause = false;
					}

					//Enter Settings
					if (theUI->getPauseButton(1)->hover)
					{
						theSound->PlayMusic(SOUND_CLICK, false, false);
						setting = true;
						pause = false;
					}

					//Exit Program
					if (theUI->getPauseButton(2)->hover)
					{
						theSound->PlayMusic(SOUND_CLICK, false, false);
						exit(0);
					}
				}
				if(setting == true)
				{
					//sound1
					if (theUI->getSettingButton(0)->hover)
					{
						theSound->PlayMusic(SOUND_CLICK, false, false);
						//gamePause = false;
						if(muteOn == false)
						{
							theSound->Mute(true);
							muteOn = true;
						}
						else if(muteOn == true)
						{
							theSound->Mute(false);
							muteOn = false;
						}
					}

					//sound2
					if (theUI->getSettingButton(1)->hover)
					{
						theSound->PlayMusic(SOUND_CLICK, false, false);
						//setting = true;
					}

					//back
					if (theUI->getSettingButton(2)->hover)
					{
						theSound->PlayMusic(SOUND_CLICK, false, false);
						pause = true;
						setting = false;
						//menuSequence();
					}
				}

				//Start Dialogue Scene 2
				if (dTrans4 == 0)
					startDialogue2 = true;

				//Trigger Dialogue8
				if (dTrans7 == 0)
					trigger8 = true;

				//Trigger Dialogue9
				if (dTrans8 == 0)
				{
					trigger8 = false;
					trigger9 = true;
				}

				//Remove Dialogue9
				if (dTrans9 == 0)
				{
					trigger9 = false;
					tutorialEnd = true;
				}
			}

			break;

		case GLUT_RIGHT_BUTTON:

			mouseInfo.mRButtonUp = state;
			mouseInfo.lastX = x;
			mouseInfo.lastY = y;

			if (mouseInfo.mRButtonUp) {
			}

			break;

		case GLUT_MIDDLE_BUTTON:
			break;
	}
}

bool myApplication::Init(void)
{
	//Set camera position
	theCamera = Camera::getInstance();
	theCamera->SetPosition( 0.0, 2.0, -5.0 );
	theCamera->SetDirection( 0.0, 0.0, 1.0 );

	//Create Goodies Factory
	theGoodiesFactory = CGoodiesFactory::getInstance();

	//Enable Texture Mapping
	glEnable(GL_TEXTURE_2D); 

	//Init Random Seed
	Math::InitRNG();

	//testMob.init(Vector3D(180,200),MobType::DEFAULT,Vector3D(150,200),Vector3D(250,200));
	//LoadTGA(&testMob.MobTex,"images/placeplaceholder2.tga");
	
	//Load Textures
	LoadTGA(&BackgroundTexture[0], "images/background4.tga");
	LoadTGA(&TileMapTexture[0], "images/tile0_blank.tga");
	LoadTGA(&TileMapTexture[1], "images/rocktexture1.tga");
	LoadTGA(&GameOver[0], "images/gameover.tga");
	LoadTGA(&LevelComplete[0], "images/levelcomplete.tga");
	LoadTGA(&border[0], "images/border.tga");
	LoadTGA(&ground[0], "images/ground.tga");
	LoadTGA(&PauseTex[0], "images/gamePause.tga");

	//Dialogue
	LoadTGA(&dialogueBG[0], "images/dialogueBG.tga");
	LoadTGA(&Stacey[0], "images/staceyDialogue1.tga");
	LoadTGA(&Stacey[1], "images/staceyDialogue2.tga");
	LoadTGA(&Stacey[2], "images/staceyDialogue3.tga");
	LoadTGA(&Stacey[3], "images/staceyDialogue4.tga");
	LoadTGA(&Stacey[4], "images/staceyDialogue5.tga");
	LoadTGA(&Patient[0], "images/patientDialogue1.tga");
	LoadTGA(&Patient[1], "images/patientDialogue2.tga");
	LoadTGA(&Patient[2], "images/patientDialogue3.tga");
	LoadTGA(&Troy[0], "images/troyDialogue1.tga");
	LoadTGA(&Flash[0], "images/flashRed.tga");

	//Hp Bar Textures
	LoadTGA(&HpBar[0], "images/HP_0.tga");
	LoadTGA(&HpBar[1], "images/HP_1.tga");
	LoadTGA(&HpBar[2], "images/HP_2.tga");
	LoadTGA(&HpBar[3], "images/HP_3.tga");
	LoadTGA(&HpBar[4], "images/HP_4.tga");
	LoadTGA(&HpBar[5], "images/HP_5.tga");
	LoadTGA(&HpBar[6], "images/HP_6.tga");

	//UI
	theUI = CUI::getInstance();

	//Create Hero
	theHero = CPlayerInfo::getInstance();
	theHero->Init();
	LoadTGA(&(theHero->HeroTexture[0]), "images/keldeo.tga");

	//Inventory Texture
	LoadTGA(&(theHero->getInventory()->Inventory[0]), "images/placeholderInventory.tga");

	//Shop
	theShop = CShop::getInstance();
	LoadTGA(&(theShop->shopTex[0]), "images/placeholderInventory.tga");

	//Set up Map
	theMap = CMap::getInstance();
	theMap->Init(MAP_SCREEN_HEIGHT, MAP_SCREEN_WIDTH, RESOLUTION_HEIGHT*2, RESOLUTION_WIDTH*2, TILE_SIZE);
	theMap->LoadMap("mapDesign1.csv");
	//theMap->LoadMap("test.csv");

	processTiles();
	
	muteOn = false;

	//Set up Border
	theBorder = new CMap;
	theBorder->Init(MAP_SCREEN_HEIGHT, MAP_SCREEN_WIDTH, RESOLUTION_HEIGHT*2, RESOLUTION_WIDTH*2, TILE_SIZE);
	theBorder->LoadMap("Border.csv");

	if(!LoadTGA(&testSkill.skillTex[0],"images/placeholder.tga"))
		return false;
	if(!LoadTGA(&testSkill.skillTex[1],"images/placeholder2.tga"))
		return false;

	//Init Timer
	mvcTime* timer=mvcTime::getInstance();
	timer->init();

	//infoList.push_back(&testMob.stats);

	//Initialise Level to 1
	currentLevel = 1;

	//The number of frames
	frameCount = 0;
	//Number of frames per second
	fps = 0;
	//currentTime - previousTime is the time elapsed
	//between every call of the Idle function
	currentTime = 0, previousTime = 0;
	//Pointer to a font style..
	//Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13, 
	//GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10, 
	//GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
	//GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.
	//GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	font_style = GLUT_BITMAP_TIMES_ROMAN_24;

	//Realtime loop control
	timelastcall=timeGetTime();
	frequency = 70.0f;

	for(int i=0; i<255; i++)
		myKeys[i] = false;

	angle = 0.0f;
	mouseInfo.lastX = RESOLUTION_WIDTH >> 1;
	mouseInfo.lastY = RESOLUTION_HEIGHT >> 1;

	mapOffset_x = mapOffset_y = tileOffset_x = tileOffset_y = mapFineOffset_x = mapFineOffset_y = 0;

	return true;
}

void myApplication::moveMeJump()
{
	if (theHero->isOnGround())
		theHero->SetToJumpUpwards(true);
}

bool myApplication::processTiles()
{
	int theNumOfTiles_MapHeight=theMap->getNumOfTiles_MapHeight();
	int theNumOfTiles_MapWidth=theMap->getNumOfTiles_MapWidth();
	Vector3D temp;
	physicObj* temp2;
	Monster* temp3;
	bool move=false;
	int current;
	int temp4;
	while(wallList.size()>0)
	{
		delete wallList.back();
		wallList.pop_back();
	}
	while(mobList.size()>0)
	{
		delete mobList.back();
		mobList.pop_back();
		infoList.pop_back();
	}
	for(int j=0;j<theNumOfTiles_MapHeight;++j)
	{
		for(int i=0;i<theNumOfTiles_MapWidth;++i)
		{
			current=theMap->theScreenMap[j][i];
			switch(current)
			{
			case 1:
				temp.Set((i)*TILE_SIZE+LEFT_BORDER,j*TILE_SIZE+BOTTOM_BORDER);
				temp2=new physicObj(temp,Vector3D(TILE_SIZE,TILE_SIZE));
				wallList.push_back(temp2);
				break;
			default://default is for mobs
				temp4=current*0.1;
				while(current>9)
				{
					current=current%10;
				}
				move=false;
				switch(temp4)//determines which
				{
				case 1:
					for(vector<Monster*>::iterator it=mobList.begin();it!=mobList.end();++it)//for 2ed patrol point
					{
						temp3=*it;
						if(temp3->ID==current&&temp3->stats.type==COIN_RANGED)//checks if the monster id already exist
						{
							temp3->AIstates.point1.Set((i)*TILE_SIZE+LEFT_BORDER,j*TILE_SIZE+BOTTOM_BORDER);
							temp3->stats.active=true;
							move=true;
						}
					}
					if(move==false)
					{
						temp3=new Monster;
						temp3->stats.type=COIN_RANGED;
						//set the monster type here
						temp3->stats.setStats(0,50);
						temp3->stats.setStats(1,50);
						temp3->stats.setPos(Vector3D((i)*TILE_SIZE+LEFT_BORDER+16,j*TILE_SIZE+BOTTOM_BORDER+16));
						temp3->AIstates.point2.Set((i)*TILE_SIZE+LEFT_BORDER,j*TILE_SIZE+BOTTOM_BORDER);
						temp3->ID=current;
						infoList.push_back(&temp3->stats);
						mobList.push_back(temp3);
					}
					break;
				case 2:
					for(vector<Monster*>::iterator it=mobList.begin();it!=mobList.end();++it)//for 2ed patrol point
					{
						temp3=*it;
						if(temp3->ID==current&&temp3->stats.type==COIN_MELEE)//checks if the monster id already exist
						{
							temp3->AIstates.point1.Set((i)*TILE_SIZE+LEFT_BORDER,j*TILE_SIZE+BOTTOM_BORDER);
							temp3->stats.active=true;
							move=true;
						}
					}
					if(move==false)
					{
						temp3=new Monster;
						temp3->stats.type=COIN_MELEE;
						//set the monster type here
						temp3->stats.setStats(0,80);
						temp3->stats.setStats(1,80);
						temp3->stats.setPos(Vector3D((i)*TILE_SIZE+LEFT_BORDER+16,j*TILE_SIZE+BOTTOM_BORDER+16));
						temp3->AIstates.point2.Set((i)*TILE_SIZE+LEFT_BORDER,j*TILE_SIZE+BOTTOM_BORDER);
						temp3->ID=current;
						infoList.push_back(&temp3->stats);
						mobList.push_back(temp3);
					}
					break;
				case 3:
					for(vector<Monster*>::iterator it=mobList.begin();it!=mobList.end();++it)//for 2ed patrol point
					{
						temp3=*it;
						if(temp3->ID==current&&temp3->stats.type==FIEND_CLEAVE)//checks if the monster id already exist
						{
							temp3->AIstates.point1.Set((i)*TILE_SIZE+LEFT_BORDER,j*TILE_SIZE+BOTTOM_BORDER);
							temp3->stats.active=true;
							move=true;
						}
					}
					if(move==false)
					{
						temp3=new Monster;
						temp3->stats.type=FIEND_CLEAVE;
						//set the monster type here
						temp3->stats.setStats(0,200);
						temp3->stats.setStats(1,200);
						temp3->stats.setPos(Vector3D((i)*TILE_SIZE+LEFT_BORDER+16,j*TILE_SIZE+BOTTOM_BORDER+16));
						temp3->AIstates.point2.Set((i)*TILE_SIZE+LEFT_BORDER,j*TILE_SIZE+BOTTOM_BORDER);
						temp3->ID=current;
						infoList.push_back(&temp3->stats);
						mobList.push_back(temp3);
					}
					break;
				case 4:
					for(vector<Monster*>::iterator it=mobList.begin();it!=mobList.end();++it)//for 2ed patrol point
					{
						temp3=*it;
						if(temp3->ID==current&&temp3->stats.type==FIEND_RANGED)//checks if the monster id already exist
						{
							temp3->AIstates.point1.Set((i)*TILE_SIZE+LEFT_BORDER,j*TILE_SIZE+BOTTOM_BORDER);
							temp3->stats.active=true;
							move=true;
						}
					}
					if(move==false)
					{
						temp3=new Monster;
						temp3->stats.type=FIEND_RANGED;
						//set the monster type here
						temp3->stats.setStats(0,150);
						temp3->stats.setStats(1,150);
						temp3->stats.setPos(Vector3D((i)*TILE_SIZE+LEFT_BORDER+16,j*TILE_SIZE+BOTTOM_BORDER+16));
						temp3->AIstates.point2.Set((i)*TILE_SIZE+LEFT_BORDER,j*TILE_SIZE+BOTTOM_BORDER);
						temp3->ID=current;
						infoList.push_back(&temp3->stats);
						mobList.push_back(temp3);
					}
					break;
				case 5:
					temp3=new Monster;
					temp3->stats.type=BOSS;
					//set the monster type here
					temp3->stats.setStats(0,500);
					temp3->stats.setStats(1,500);
					temp3->stats.setPos(Vector3D((i)*TILE_SIZE+LEFT_BORDER+16,j*TILE_SIZE+BOTTOM_BORDER+16));
					temp3->AIstates.point2.Set((i)*TILE_SIZE+LEFT_BORDER,j*TILE_SIZE+BOTTOM_BORDER);
					temp3->ID=current;
					infoList.push_back(&temp3->stats);
					mobList.push_back(temp3);
					break;
				}
				break;
			}
		}
	}
	return true;
}

void myApplication::moveMeUpDown(bool mode, float timeDiff)
{
	//Down
	if (mode)
	{
		theHero->SetPosY(theHero->GetPos().y-(int)(200.0f * timeDiff));

		theHero->SetAnimationCounter(theHero->GetAnimationCounter()-1);
		if (theHero->GetAnimationCounter()==0)
			theHero->SetAnimationCounter(SPRITE_FRAMES_PLAYER-1);
	}

	//Up
	else
	{
		theHero->SetPosY(theHero->GetPos().y+(int)(200.0f * timeDiff));

		theHero->SetAnimationCounter(theHero->GetAnimationCounter()-1);
		if (theHero->GetAnimationCounter()==0)
			theHero->SetAnimationCounter(SPRITE_FRAMES_PLAYER-1);
	}
}

void myApplication::moveMeLeftRight(bool mode, float timeDiff)
{
	//Left
	if (mode)
	{
		bLeft = true;
		bRight = false;

		theHero->SetPosX(theHero->GetPos().x - (int) (200.0f * timeDiff));

		theHero->SetAnimationInvert(true);
		theHero->SetAnimationCounter(theHero->GetAnimationCounter()-1);
		if (theHero->GetAnimationCounter()==0)
			theHero->SetAnimationCounter(SPRITE_FRAMES_PLAYER-1);
	}

	//Right
	else
	{
		bLeft = false;
		bRight = true;

		theHero->SetPosX(theHero->GetPos().x + (int) (200.0f * timeDiff));

		theHero->SetAnimationInvert(false);
		theHero->SetAnimationCounter(theHero->GetAnimationCounter()+1);
		if (theHero->GetAnimationCounter() > SPRITE_FRAMES_PLAYER)
			theHero->SetAnimationCounter(0);
	}
}

void myApplication::DisplayText()
{
	glLoadIdentity();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	mvcTime* timer=mvcTime::getInstance();
		//Do not render these texts over screens
	    if (!bComplete && !bGameOver && !theShop->open && !theHero->getInventory()->open)
		{
			//FPS
			drawFPS();

			//Display Health Bar Text
			glColor3f(1.0f, 0.0f, 0.0f);
			printw (35.0, 23.0, 0, "Health Bar");

			//Display Level
			glColor3f(0.0f, 1.0f, 1.0f);
			printw (870.0, 40.0, 0, "Level: %d", currentLevel);

			//Display Stats 
			glColor3f(0.0f, 1.0f, 0.0f);
			printw (790.0, 290.0, 0, "Player Level: %d", theHero->getAttributes()->getLevel());
			printw (790.0, 320.0, 0, "Player Attack: %d", theHero->getAttributes()->getAttack());
			printw (790.0, 350.0, 0, "Player Defense: %d", theHero->getAttributes()->getDefense());
			printw (790.0, 380.0, 0, "Player Exp: %d", theHero->getExp()->getExp());
			printw (790.0, 440.0, 0, "AGC Credits: %d", theHero->getAttributes()->getAGC());

			//Print Level
			if (theHero->getAttributes()->getLevel() < 100)
				printw (790.0, 410.0, 0, "Exp To Next Level: %d", theHero->getExp()->getExpToLevel());
			else
				printw (790.0, 410.0, 0, "Exp To Next Level: -");

			//Print Skills
			printw (790.0, 500.0, 0, "Z: Skill 1");
			printw (790.0, 530.0, 0, "X: Skill 2");

			//Print Skills
			printw (790.0, 590.0, 0, "U: Open Shop");
			printw (790.0, 620.0, 0, "I:  Open Inventory");
		}

		//Render Inventory Info
		if (theHero->getInventory()->open)
		{
			theHero->getInventory()->DisplayInfo();
		}

		//Render Shop Info
		if (theShop->open)
		{
			theShop->DisplayInfo();
		}

	glColor3f(1.0f, 1.0f, 1.0f);
	glPopAttrib();
}

void myApplication::renderGameOver()
{
	glEnable(GL_TEXTURE_2D);

	//Draw Game Over Scren
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, GameOver[0].texID);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0,0); glVertex2f(0,RESOLUTION_HEIGHT);
				glTexCoord2f(1,0); glVertex2f(RESOLUTION_WIDTH,RESOLUTION_HEIGHT);
				glTexCoord2f(1,1); glVertex2f(RESOLUTION_WIDTH,0);
				glTexCoord2f(0,1); glVertex2f(0,0);				
			glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void myApplication::renderComplete()
{
	glEnable(GL_TEXTURE_2D);

	//Draw Game Over Scren
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, LevelComplete[0].texID);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0,0); glVertex2f(0,RESOLUTION_HEIGHT);
				glTexCoord2f(1,0); glVertex2f(RESOLUTION_WIDTH,RESOLUTION_HEIGHT);
				glTexCoord2f(1,1); glVertex2f(RESOLUTION_WIDTH,0);
				glTexCoord2f(0,1); glVertex2f(0,0);				
			glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void myApplication::renderPause() {
	glEnable(GL_TEXTURE_2D);

	
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Draw Pause Image
		glBindTexture(GL_TEXTURE_2D, PauseTex[0].texID);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0,0); glVertex2f(0, RESOLUTION_HEIGHT);
				glTexCoord2f(1,0); glVertex2f(RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
				glTexCoord2f(1,1); glVertex2f(RESOLUTION_WIDTH, 0);
				glTexCoord2f(0,1); glVertex2f(0, 0);				
			glEnd();
		glPopMatrix();

	glDisable(GL_BLEND);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void myApplication::renderStartScene()
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int height = 163.6;
	int width = 600;

		//Draw Background
		glBindTexture(GL_TEXTURE_2D, dialogueBG[0].texID);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0,0); glVertex2f(0,RESOLUTION_HEIGHT);
				glTexCoord2f(1,0); glVertex2f(RESOLUTION_WIDTH,RESOLUTION_HEIGHT);
				glTexCoord2f(1,1); glVertex2f(RESOLUTION_WIDTH,0);
				glTexCoord2f(0,1); glVertex2f(0,0);				
			glEnd();
		glPopMatrix();

		if (dTrans1 != -600)
		{
			//Draw Patient Dialogue 1
			glBindTexture(GL_TEXTURE_2D, Patient[0].texID);
			glPushMatrix();
				glTranslatef(0+dTrans1,0,0);
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(0,height);
					glTexCoord2f(1,0); glVertex2f(width,height);
					glTexCoord2f(1,1); glVertex2f(width,0);
					glTexCoord2f(0,1); glVertex2f(0,0);				
				glEnd();
			glPopMatrix();

			//Draw Stacey Dialogue 1
			glBindTexture(GL_TEXTURE_2D, Stacey[0].texID);
			glPushMatrix();
				glTranslatef(423+dTrans2,200,0);
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(0,height);
					glTexCoord2f(1,0); glVertex2f(width,height);
					glTexCoord2f(1,1); glVertex2f(width,0);
					glTexCoord2f(0,1); glVertex2f(0,0);				
				glEnd();
			glPopMatrix();

			//Draw Patient Dialogue 2
			glBindTexture(GL_TEXTURE_2D, Patient[1].texID);
			glPushMatrix();
				glTranslatef(0+dTrans3,400,0);
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(0,height);
					glTexCoord2f(1,0); glVertex2f(width,height);
					glTexCoord2f(1,1); glVertex2f(width,0);
					glTexCoord2f(0,1); glVertex2f(0,0);				
				glEnd();
			glPopMatrix();

			//Draw Troy Dialogue 1
			glBindTexture(GL_TEXTURE_2D, Troy[0].texID);
			glPushMatrix();
				glTranslatef(423+dTrans4,600,0);
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(0,height);
					glTexCoord2f(1,0); glVertex2f(width,height);
					glTexCoord2f(1,1); glVertex2f(width,0);
					glTexCoord2f(0,1); glVertex2f(0,0);				
				glEnd();
			glPopMatrix();
		}

		if (startDialogue2)
		{
			//Draw Stacey Dialogue 2
			glBindTexture(GL_TEXTURE_2D, Stacey[1].texID);
			glPushMatrix();
				glTranslatef(0+dTrans5,200,0);
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(0,height);
					glTexCoord2f(1,0); glVertex2f(width,height);
					glTexCoord2f(1,1); glVertex2f(width,0);
					glTexCoord2f(0,1); glVertex2f(0,0);				
				glEnd();
			glPopMatrix();

			//Draw Patient Dialogue 3
			glBindTexture(GL_TEXTURE_2D, Patient[2].texID);
			glPushMatrix();
				glTranslatef(423+dTrans6,400,0);
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(0,height);
					glTexCoord2f(1,0); glVertex2f(width,height);
					glTexCoord2f(1,1); glVertex2f(width,0);
					glTexCoord2f(0,1); glVertex2f(0,0);				
				glEnd();
			glPopMatrix();
		}

		if (bFlash && counterFlash <= 175)
		{
			//Draw Flash
			glBindTexture(GL_TEXTURE_2D, Flash[0].texID);
			glPushMatrix();
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(0,RESOLUTION_HEIGHT);
					glTexCoord2f(1,0); glVertex2f(RESOLUTION_WIDTH,RESOLUTION_HEIGHT);
					glTexCoord2f(1,1); glVertex2f(RESOLUTION_WIDTH,0);
					glTexCoord2f(0,1); glVertex2f(0,0);				
				glEnd();
			glPopMatrix();
		}

	glDisable(GL_BLEND);
	glPopMatrix();


	 /****************************************************************************************************
	   Dialogue Transition Update
	 ****************************************************************************************************/
	//Patient 1 Trans
	mvcTime* timer = mvcTime::getInstance();
	float dt=timer->getDelta();

	//Movement Speed
	int speed1 = 350;
	int speed2 = 650;

	//Dialogue Scene 1
	if (!startDialogue2)
	{
		if (dTrans1 >= 0)
			dTrans1 = 0;
		else
			dTrans1 += speed1*dt;
		//Stacey 1 Trans
		if (dTrans1 == 0)
		{
			if (dTrans2 <= 0)
				dTrans2 = 0;
			else
				dTrans2 -= speed1*dt;
		}
		//Patient 2 Trans
		if (dTrans2 == 0)
		{
			if (dTrans3 >= 0)
				dTrans3 = 0;
			else
				dTrans3 += speed1*dt;
		}
		//Troy 1 Trans
		if (dTrans3 == 0)
		{
			if (dTrans4 <= 0)
				dTrans4 = 0;
			else
				dTrans4 -= speed1*dt;
		}
	}

	//Dialogue Scene 2
	if (startDialogue2)
	{
		//Remove previous Dialogue Scenes upon Mouse Click
		if (dTrans4 >= 610)
			dTrans4 = 610;
		else
			dTrans4 += speed2*dt;
		if (dTrans2 >= 610)
			dTrans2 = 610;
		else
			dTrans2 += speed2*dt;
		if (dTrans3 <= -600)
			dTrans3 = -600;
		else 
			dTrans3 -= speed2*dt;
		if (dTrans1 <= -600)
			dTrans1 = -600;
		else
			dTrans1 -= speed2*dt;

		//Transition
		if (dTrans1 == -600)
		{
			//Stacey Dialogue 2 Trans
			if (dTrans5 >= 0)
				dTrans5 = 0;
			else
				dTrans5 += speed1*dt;

			//Patient Dialogue 3 Trans
			if (dTrans5 == 0)
			{
				if (dTrans6 <= 0)
					dTrans6 = 0;
				else
					dTrans6 -= speed1*dt;
			}
		}
	}

	//Triger Flash
	if (dTrans6 == 0)
		bFlash = true;

	//Flash Effect
	if (bFlash)
	{
		int dt2=dt*1000;
		counterFlash+=dt2;
		counterTime+=dt2;
		if (counterFlash >= 350)
			counterFlash = 0;

		//Stop flash after some time
		if (counterTime >= 3000)
		{
			bFlash = false;
			gamePause = bTutorial = gameStart = true;
			soundinit = false;
			if(!soundinit)
			{
				theSound->Stop();
				theSound->PlayMusic(SOUND_LEVEL1, true, false);
				soundinit = true;
			}
		}
	}	
}

void myApplication::renderTutorial()
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int height = 163.6;
	int width = 600;

		//Draw Stacey Dialogue 3
		glBindTexture(GL_TEXTURE_2D, Stacey[2].texID);
		glPushMatrix();
			glTranslatef(0+dTrans7,600,0);
			glBegin(GL_QUADS);
				glTexCoord2f(0,0); glVertex2f(0,height);
				glTexCoord2f(1,0); glVertex2f(width,height);
				glTexCoord2f(1,1); glVertex2f(width,0);
				glTexCoord2f(0,1); glVertex2f(0,0);				
			glEnd();
		glPopMatrix();

		//Draw Stacey Dialogue 4
		glBindTexture(GL_TEXTURE_2D, Stacey[3].texID);
		glPushMatrix();
			glTranslatef(0+dTrans8,600,0);
			glBegin(GL_QUADS);
				glTexCoord2f(0,0); glVertex2f(0,height);
				glTexCoord2f(1,0); glVertex2f(width,height);
				glTexCoord2f(1,1); glVertex2f(width,0);
				glTexCoord2f(0,1); glVertex2f(0,0);				
			glEnd();
		glPopMatrix();

		//Draw Stacey Dialogue 5
		glBindTexture(GL_TEXTURE_2D, Stacey[4].texID);
		glPushMatrix();
			glTranslatef(0+dTrans9,600,0);
			glBegin(GL_QUADS);
				glTexCoord2f(0,0); glVertex2f(0,height);
				glTexCoord2f(1,0); glVertex2f(width,height);
				glTexCoord2f(1,1); glVertex2f(width,0);
				glTexCoord2f(0,1); glVertex2f(0,0);				
			glEnd();
		glPopMatrix();

	glDisable(GL_BLEND);
	glPopMatrix();

	 /****************************************************************************************************
	   Dialogue (Tutorial) Transition Update
	 ****************************************************************************************************/
	//Stacey Tutorial Dialogue (3)
	if (!trigger8 && !trigger9 && !tutorialEnd)
	{
		if (dTrans7 >= 0)
			dTrans7 = 0;
		else 
			dTrans7 += 2;
	}

	//Stacey Tutorial Dialogue (4)
	if (trigger8)
	{
		//Translate Previous Dialogue Back
		if (dTrans7 <= -600)
			dTrans7 = -600;
		else
			dTrans7 -= 2;

		//Translate Current Dialogue Forward
		if (dTrans7 == -600)
		{
			if (dTrans8 >= 0)
				dTrans8 = 0;
			else
				dTrans8 += 2;
		}
	}

	//Stacey Tutorial Dialogue (5)
	if (trigger9)
	{
		//Translate Previous Dialogue Back
		if (dTrans8 <= -600)
			dTrans8 = -600;
		else
			dTrans8 -= 2;

		//Translate Current Dialogue Forward
		if (dTrans8 == -600)
		{
			if (dTrans9 >= 0)
				dTrans9 = 0;
			else
				dTrans9 += 2;
		}
	}

	//End Tutorial
	if (tutorialEnd)
	{
		//Translate Previous Dialogue Back
		if (dTrans9 <= -600)
			dTrans9 = -600;
		else
			dTrans9 -= 2;

		//End Tutorial
		if (dTrans9 == -600)
		{
			bTutorial = gamePause = setting = pause = false;
			allowGamePause = true;
		}
	}
}

void myApplication::renderGround()
{
	glEnable(GL_TEXTURE_2D);

	//Draw Ground
	glPushMatrix();
	glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(LEFT_BORDER, BOTTOM_BORDER, 0);
		glBindTexture(GL_TEXTURE_2D, ground[0].texID);
		glPushMatrix();
		int height = 700;
		int width = 700;
			glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex2f(0,height);
				glTexCoord2f(1,0); glVertex2f(width,height);
				glTexCoord2f(1,1); glVertex2f(width,0);
				glTexCoord2f(0,1); glVertex2f(0,0);				
			glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

/****************************************************************************************************
   Draw the background
 ****************************************************************************************************/
void myApplication::RenderBackground() {
	glEnable(GL_TEXTURE_2D);

	
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Draw Background image
		glBindTexture(GL_TEXTURE_2D, BackgroundTexture[0].texID);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0,0); glVertex2f(0, RESOLUTION_HEIGHT);
				glTexCoord2f(1,0); glVertex2f(RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
				glTexCoord2f(1,1); glVertex2f(RESOLUTION_WIDTH, 0);
				glTexCoord2f(0,1); glVertex2f(0, 0);				
			glEnd();
		glPopMatrix();

	glDisable(GL_BLEND);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

/****************************************************************************************************
   Draw the Hp Bar
 ****************************************************************************************************/
void myApplication::RenderHpBar()
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (theHero->getAttributes()->getHp() <= 0)
			glBindTexture(GL_TEXTURE_2D, HpBar[0].texID);
		else if (theHero->getAttributes()->getHp() <= 1 * HP_MULTIPLIER)
			glBindTexture(GL_TEXTURE_2D, HpBar[1].texID);
		else if (theHero->getAttributes()->getHp() <= 2 * HP_MULTIPLIER)
			glBindTexture(GL_TEXTURE_2D, HpBar[2].texID);
		else if (theHero->getAttributes()->getHp() <= 3 * HP_MULTIPLIER)
			glBindTexture(GL_TEXTURE_2D, HpBar[3].texID);
		else if (theHero->getAttributes()->getHp() <= 4 * HP_MULTIPLIER)
			glBindTexture(GL_TEXTURE_2D, HpBar[4].texID);
		else if (theHero->getAttributes()->getHp() <= 5 * HP_MULTIPLIER)
			glBindTexture(GL_TEXTURE_2D, HpBar[5].texID);
		else if (theHero->getAttributes()->getHp() <= 6 * HP_MULTIPLIER)
			glBindTexture(GL_TEXTURE_2D, HpBar[6].texID);
		else glBindTexture(GL_TEXTURE_2D, HpBar[6].texID);

		short height = 55; 
		short width = 300;
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0,0); glVertex2f(TILE_SIZE, height);
				glTexCoord2f(1,0); glVertex2f(width, height);
				glTexCoord2f(1,1); glVertex2f(width,TILE_SIZE);
				glTexCoord2f(0,1); glVertex2f(TILE_SIZE,TILE_SIZE);				
			glEnd();
		glPopMatrix();

		glDisable(GL_BLEND);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

/****************************************************************************************************
   Draw the tile map
 ****************************************************************************************************/
void myApplication::RenderTileMap(CMap* map) {

	//Initialise mapFineOffset
	mapFineOffset_x = mapOffset_x % TILE_SIZE;
	mapFineOffset_y = mapOffset_y % TILE_SIZE;

	glPushMatrix();

	//Loop through column
	for(int i = 0; i < map->getNumOfTiles_ScreenHeight(); ++i)
	{
		//Loop through row
		for(int k = 0; k < map->getNumOfTiles_ScreenWidth()+1; k ++)
		{
			//if we have reached the right side of the Map, then do not display the extra column of tiles.
			if ((tileOffset_x+k) >= map->getNumOfTiles_MapWidth())
				break;

			//if we have reached the top side of the Map, then do not display the extra row of tiles.
			if ((tileOffset_y+i) >= map->getNumOfTiles_MapHeight())
				break;

			//Wall texture
			if (map->theScreenMap[tileOffset_y+i][tileOffset_x+k] == 1)
			{
				glPushMatrix();
				glTranslatef(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER, i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER, 0);
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_BLEND);
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture(GL_TEXTURE_2D, TileMapTexture[map->theScreenMap[tileOffset_y+i][tileOffset_x+k]].texID);
				glBegin(GL_QUADS);
					glTexCoord2f(0,1); glVertex2f(0,0);
					glTexCoord2f(0,0); glVertex2f(0,TILE_SIZE);
					glTexCoord2f(1,0); glVertex2f(TILE_SIZE,TILE_SIZE);
					glTexCoord2f(1,1); glVertex2f(TILE_SIZE,0);
				glEnd();
				glDisable(GL_BLEND);
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
		}
	}

	glPopMatrix();
}

void myApplication::RenderMiniMap(CMap* map) {
	glPushMatrix();
	int miniTileSize=2;
	int yStart=-10;
	int renderExtraY=0;
	if(yStart+tileOffset_y<0)
	{
		yStart=-tileOffset_y;
	}
	renderExtraY=20+yStart;
	int xStart=-10;
	int renderExtraX=0;
	if(xStart+tileOffset_x<0)
	{
		xStart=-tileOffset_x;
	}
	renderExtraX=20+xStart;
	//Loop through column
	for(int i = yStart; i < map->getNumOfTiles_ScreenHeight()+renderExtraY; ++i)
	{
		//Loop through row
		for(int k = xStart; k < map->getNumOfTiles_ScreenWidth()+1+renderExtraX; ++k)
		{
			bool stop=false;
			//if we have reached the right side of the Map, then do not display the extra column of tiles.
			if ((tileOffset_x+k) >= map->getNumOfTiles_MapWidth())
				stop=true;

			//if we have reached the top side of the Map, then do not display the extra row of tiles.
			if ((tileOffset_y+i) >= map->getNumOfTiles_MapHeight())
				stop=true;

			if(!stop)
			{
				//Wall texture
				if (map->theScreenMap[tileOffset_y+i][tileOffset_x+k] == 1)
				{
					glColor3f(0,0,0);
				}
				else
				{
					glColor3f(1,1,1);
				}
				glPushMatrix();
					glTranslatef((k-xStart)*miniTileSize, (i-yStart)*miniTileSize, 0);
					//glEnable(GL_TEXTURE_2D);
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					//glBindTexture(GL_TEXTURE_2D, TileMapTexture[map->theScreenMap[tileOffset_y+i][tileOffset_x+k]].texID);
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,miniTileSize);
						glTexCoord2f(1,0); glVertex2f(miniTileSize,miniTileSize);
						glTexCoord2f(1,1); glVertex2f(miniTileSize,0);
					glEnd();
					glDisable(GL_BLEND);
					//glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
			else
			{
				glColor3f(0,0,0);
				glPushMatrix();
					glTranslatef((k-xStart)*miniTileSize, (i-yStart)*miniTileSize, 0);
					//glEnable(GL_TEXTURE_2D);
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					//glBindTexture(GL_TEXTURE_2D, TileMapTexture[map->theScreenMap[tileOffset_y+i][tileOffset_x+k]].texID);
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,miniTileSize);
						glTexCoord2f(1,0); glVertex2f(miniTileSize,miniTileSize);
						glTexCoord2f(1,1); glVertex2f(miniTileSize,0);
					glEnd();
					glDisable(GL_BLEND);
					//glDisable(GL_TEXTURE_2D);
				glPopMatrix();

			}
		}
	}
	int miniOffset_y=yStart+tileOffset_y;
	int miniOffset_x=xStart+tileOffset_x;
	glColor3f(1,0,0);
	for(vector<MobInfo*>::iterator it=infoList.begin();it!=infoList.end();++it)
	{
		bool stop=false;
		MobInfo* temp=*it;
		if(temp->active)
		{
			float MxTranslate=(((temp->getPos().x-LEFT_BORDER+mapFineOffset_x)/32)+tileOffset_x-miniOffset_x)*2;
			float MyTranslate=(((temp->getPos().y-BOTTOM_BORDER+mapFineOffset_y)/32)+tileOffset_y-miniOffset_y)*2;
			if(MyTranslate/2>map->getNumOfTiles_ScreenHeight()+renderExtraY+tileOffset_y-1||MyTranslate/2<0)
				stop=true;
			else if(MxTranslate/2>map->getNumOfTiles_ScreenWidth()+renderExtraX+tileOffset_x-6||MxTranslate/2<0)
				stop=true;

			if(!stop)
			{
				glPushMatrix();
					glTranslatef(MxTranslate,MyTranslate,0);
					//glEnable(GL_TEXTURE_2D);
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					//glBindTexture(GL_TEXTURE_2D, TileMapTexture[map->theScreenMap[tileOffset_y+i][tileOffset_x+k]].texID);
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,miniTileSize);
						glTexCoord2f(1,0); glVertex2f(miniTileSize,miniTileSize);
						glTexCoord2f(1,1); glVertex2f(miniTileSize,0);
					glEnd();
					glDisable(GL_BLEND);
					//glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
		}
	}
	float xTranslate=(((theHero->GetPos().x-LEFT_BORDER)/32)+tileOffset_x-miniOffset_x)*2;
	float yTranslate=(((theHero->GetPos().y-BOTTOM_BORDER)/32)+tileOffset_y-miniOffset_y)*2;
	glColor3f(0,0.6,1);
	glPushMatrix();
		glTranslatef(xTranslate,yTranslate,0);
		//glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glBindTexture(GL_TEXTURE_2D, TileMapTexture[map->theScreenMap[tileOffset_y+i][tileOffset_x+k]].texID);
		glBegin(GL_QUADS);
			glTexCoord2f(0,1); glVertex2f(0,0);
			glTexCoord2f(0,0); glVertex2f(0,miniTileSize);
			glTexCoord2f(1,0); glVertex2f(miniTileSize,miniTileSize);
			glTexCoord2f(1,1); glVertex2f(miniTileSize,0);
		glEnd();
		glDisable(GL_BLEND);
		//glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glColor3f(1,1,1);
	glPopMatrix();
}

/****************************************************************************************************
   Draw the map border
 ****************************************************************************************************/
void myApplication::RenderMapBorder()
{
	glPushMatrix();

	//Loop through column
	for(int i = 0; i < theBorder->getNumOfTiles_ScreenHeight()+3; ++i)
	{
		//Loop through row
		for(int k = 0; k < theBorder->getNumOfTiles_ScreenWidth()+2; k ++)
		{
			//Border texture
			if (theBorder->theScreenMap[i][k] == 1)
			{
				glPushMatrix();
				glTranslatef(k*TILE_SIZE+LEFT_BORDER-TILE_SIZE, i*TILE_SIZE+BOTTOM_BORDER-2*TILE_SIZE, 0);
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_BLEND);
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture(GL_TEXTURE_2D, border[0].texID);
				glBegin(GL_QUADS);
					glTexCoord2f(0,1); glVertex2f(0,0);
					glTexCoord2f(0,0); glVertex2f(0,TILE_SIZE);
					glTexCoord2f(1,0); glVertex2f(TILE_SIZE,TILE_SIZE);
					glTexCoord2f(1,1); glVertex2f(TILE_SIZE,0);
				glEnd();
				glDisable(GL_BLEND);
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
		}
	}

	glPopMatrix();
}

//-------------------------------------------------------------------------
// Calculates the frames per second
//-------------------------------------------------------------------------
void myApplication::calculateFPS()
{
	//Increase frame count
	frameCount++;

	//Get the number of milliseconds since glutInit called
	//(or first call to glutGet(GLUT ELAPSED TIME)).
	currentTime = glutGet(GLUT_ELAPSED_TIME);

	//Calculate time passed
	int timeInterval = currentTime - previousTime;

	if(timeInterval > 1000)
	{
		//calculate the number of frames per second
		fps = frameCount / (timeInterval / 1000.0f);

		//Set time
		previousTime = currentTime;

		//Reset frame count
		frameCount = 0;
	}
}

//-------------------------------------------------------------------------
//  Draw FPS
//-------------------------------------------------------------------------
void myApplication::drawFPS()
{
	//Load the identity matrix so that FPS string being drawn
	//won't get animates
	glLoadIdentity();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		//Print the FPS to the window
		glColor3f(0.0f, 1.0f, 0.0f);
		printw (490, 27.0, 0, "FPS: %4.2f", fps);
		glColor3f(1.0f, 1.0f, 1.0f);
	glPopAttrib();
}

//-------------------------------------------------------------------------
//  Draws a string at the specified coordinates.
//-------------------------------------------------------------------------
void myApplication::printw (float x, float y, float z, char* format, ...)
{
	va_list args;	//  Variable argument list
	int len;		//	String length
	short i;		//  Iterator
	char * text;	//	Text

	//  Initialize a variable argument list
	va_start(args, format);

	//  Return the number of characters in the string referenced the list of arguments.
	//  _vscprintf doesn't count terminating '\0' (that's why +1)
	len = _vscprintf(format, args) + 1; 

	//  Allocate memory for a string of the specified size
	text = (char *)malloc(len * sizeof(char));

	//  Write formatted output using a pointer to the list of arguments
	vsprintf_s(text, len, format, args);

	//  End using variable argument list 
	va_end(args);

	//  Specify the raster position for pixel operations.
	glRasterPos3f (x, y, z);


	//  Draw the characters one by one
	for (i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(font_style, text[i]);

	//  Free the allocated memory for the string
	free(text);
}

bool myApplication::LoadTGA(TextureImage *texture, char *filename) // Loads A TGA File Into Memory
{   
	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
	GLubyte		TGAcompare[12];								// Used To Compare TGA Header
	GLubyte		header[6];									// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;								// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;									// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;										// Temporary Variable
	GLuint		type=GL_RGBA;								// Set The Default GL Mode To RBGA (32 BPP)

	FILE *file = fopen(filename, "rb");						// Open The TGA File

	if(	file==NULL ||										// Does File Even Exist?
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	// Does The Header Match What We Want?
		fread(header,1,sizeof(header),file)!=sizeof(header))				// If So Read Next 6 Header Bytes
	{
		if (file == NULL)									// Did The File Even Exist? *Added Jim Strong*
			return false;									// Return False
		else
		{
			fclose(file);									// If Anything Failed, Close The File
			return false;									// Return False
		}
	}

	texture->width  = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)

	if(	texture->width	<=0	||								// Is The Width Less Than Or Equal To Zero
		texture->height	<=0	||								// Is The Height Less Than Or Equal To Zero
		(header[4]!=24 && header[4]!=32))					// Is The TGA 24 or 32 Bit?
	{
		fclose(file);										// If Anything Failed, Close The File
		return false;										// Return False
	}

	texture->bpp	= header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel	= texture->bpp/8;						// Divide By 8 To Get The Bytes Per Pixel
	imageSize		= texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	texture->imageData=(GLubyte *)malloc(imageSize);		// Reserve Memory To Hold The TGA Data

	if(	texture->imageData==NULL ||							// Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file)!=imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if(texture->imageData!=NULL)						// Was Image Data Loaded
			free(texture->imageData);						// If So, Release The Image Data

		fclose(file);										// Close The File
		return false;										// Return False
	}

	for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)		// Loop Through The Image Data
	{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp=texture->imageData[i];							// Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose (file);											// Close The File

	// Build A Texture From The Data
	glGenTextures(1, &texture[0].texID);					// Generate OpenGL texture IDs

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);			// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered

	if (texture[0].bpp==24)									// Was The TGA 24 Bits
	{
		type=GL_RGB;										// If So Set The 'type' To GL_RGB
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);

	return true;											// Texture Building Went Ok, Return True
}
