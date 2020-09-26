#include "SimulationController.h"
#include "EventManager.h"
#include "Map.h"
#include "Window.h"
#include "ContentRegionInventory.h"
#include "ContentRegionCharacterAttributes.h"
#include "ContentRegionMenu.h"
#include "ContentRegionTextBox.h"
#include "Creature.h"
#include "Constants.h"
#include "MousePointer.h"
#include "ActionHelper.h"
#include "ActionPickUpItem.h"
#include "ActionGotoTile.h"
#include "GoalsControllable.h"
#include <SFML/Graphics/RenderTarget.hpp>

static sf::RenderTarget* mWindow;
static EventManager* mEventManager;
static MousePointer* mMousePointer;

static const int TempDist = 130;
static const int TempTime = 1;

static const size_t RightClickCols = 3;

static const std::string TEXT = "TEXT: Yes this is a text.\n\n\nA lot can be said in a text, especially one as long as this.\n\n\nBut even if a lot is said, it doesn't mean it has to mean shit.\n\n\n\nMore.";

SimulationController::SimulationController()
{
    setStaticEventPosition(false);
    mInterestedEvents.push_back(sf::Event::MouseButtonPressed);
    mInterestedEvents.push_back(sf::Event::KeyPressed);
}

SimulationController::~SimulationController()
{

}

void SimulationController::initalize(Map * map, Creature * controllableEntity)
{
    mCurrentMap = map;
    mControllableEntity = controllableEntity;
    mCurrentMap->updateVertexArray(mControllableEntity->getMovementComponent()->getCurrentTarget(), TempDist, TempTime);
    mControllableEntity->getMovementComponent()->registerMovementListener(this);
    mControllableEntity->getMovementComponent()->setCurrentMap(mCurrentMap);
    Inventory* inv = mControllableEntity->getInventory();
    mEntityGoals = new GoalsControllable(mControllableEntity);
    mControllableEntity->setGoals(mEntityGoals);

    bool success = true;

    success = Window::createWindow(&mInventoryWin, "Inventory", sf::Vector2f(100.0f, 50.0f));
    ContentRegionInventory*  cr = new ContentRegionInventory(inv, 5);
    mInventoryWin->setWindowContentSize(cr->getRegionSize());
    mInventoryWin->addContentRegion(cr);
    mInventoryWin->setVisibility(false);
    mInventoryWin->setWindowListener(this);

    success = Window::createWindow(&mCharacterWin, "Character", sf::Vector2f(100.0f, 100.0f));
    ContentRegionCharacterAttributes* cr2 = new ContentRegionCharacterAttributes();
    mCharacterWin->setWindowContentSize(cr2->getRegionSize());
    mCharacterWin->addContentRegion(cr2);
    mCharacterWin->setVisibility(false);
    mCharacterWin->setWindowListener(this);

    success = Window::createWindow(&mRightClickWindow, "Menu");
    mRightClickCRI = new ContentRegionInventory();
    mRightClickCRM = new ContentRegionMenu(this);
    mRightClickWindow->setVisibility(false);
    mRightClickWindow->setWindowListener(this);
    mRightClickWindow->addContentRegion(mRightClickCRM);
    mRightClickWindow->addContentRegion(mRightClickCRI);

    success = Window::createWindow(&mDialogueWindow, "Dialogue", sf::Vector2f(100.0f, 150.0f));
    ContentRegionTextBox* cr3 = new ContentRegionTextBox(TEXT, sf::Vector2f(400.0f, 150.0f));
    mDialogueWindow->addContentRegion(cr3);
    //cr3->setRegionSize();
    mDialogueWindow->setWindowContentSize(cr3->getRegionSize());
    mDialogueWindow->setWindowListener(this);
    mDialogueWindow->setVisibility(false);
}

bool SimulationController::observe(const sf::Event & _event)
{
    bool retVal = false;
    sf::Vector2f mousePos;
    sf::Vector2i targetPos;

    switch (_event.type)
    {
    case sf::Event::MouseButtonPressed:
        mousePos = mWindow->mapPixelToCoords(sf::Vector2i(_event.mouseButton.x, _event.mouseButton.y));
        targetPos = mCurrentMap->getTileIndexFromCoords(mousePos);
        mRightClickMenuEntityRef = nullptr;
        if (_event.mouseButton.button == sf::Mouse::Left)
        {
            if (!mControllableEntity || !mCurrentMap || !mMousePointer) break;
            mRightClickWindow->setVisibility(false);
            retVal = true;
            sf::Vector2i currentPos = getCurrentPos();

            if (mMousePointer->getItem() == nullptr) // No item on cursor, try to move
            {
                doMoveToTile(targetPos);
            }
            else
            {
                mCurrentMap->getTileFromIndex(currentPos)->addItem(mMousePointer->switchItem(nullptr));
            }
        }
        else if (_event.mouseButton.button == sf::Mouse::Right)
        {
            // Populate rightlick menu items from the tile
            Tile* tile = mCurrentMap->getTileFromIndex(targetPos);
            if (tile != nullptr)
            {
                sf::Vector2f winSize;
                mRightClickTile = targetPos;
                size_t size = tile->getNrItems();
                if (tile->getVisible())
                {
                    mRightClickCRI->createNewSlots(size, 3);
                    if (size != 0)
                    {
                        for (size_t i = 0; i < size; i++)
                        {
                            mRightClickCRI->getInventorySlot(i)->setItem(tile->getItem(i));
                            mRightClickCRI->getInventorySlot(i)->setTileReference(tile);
                        }
                    }
                }
                else
                    mRightClickCRI->createNewSlots(0, 3);

                mRightClickWindow->setVisibility(true);

                // Populate rightclick menu buttons from the entity
                mRightClickCRM->clearButtons();
                mRightClickCRM->addButton("Move", MenuButtons::Move);
                mRightClickMenuTileRefPos = targetPos;

                if (tile->getVisible() &&
                    (mRightClickMenuEntityRef = tile->getOccupant()) != nullptr)
                {
                    mRightClickCRM->addButton("Attack", MenuButtons::Attack);
                    mRightClickCRM->addButton("Interact", MenuButtons::Interact);
                    mRightClickCRM->addButton("Examine", MenuButtons::Examine);
                }

                float CRMHeight = mRightClickCRM->getRegionSize().y;
                mRightClickCRI->setPosition(0.0f, CRMHeight);
                winSize.x = mRightClickCRI->getRegionSize().x;
                winSize.x = std::max(winSize.x, mRightClickCRM->getRegionSize().x);
                winSize.y = CRMHeight + mRightClickCRI->getRegionSize().y;
                mRightClickWindow->setWindowContentSize(winSize);
            }
        }
        break;

    case sf::Event::KeyPressed:
        if (_event.key.code == sf::Keyboard::Space)
        {
            mControllableEntity->getMovementComponent()->halt();
        }
        else if (_event.key.code == sf::Keyboard::I)
        {
            bool vis = !mInventoryWin->getVisible();
            //(vis ? mInventoryWin->registerEvents() : mInventoryWin->unregisterEvents());
            mInventoryWin->setVisibility(vis);
        }
        else if (_event.key.code == sf::Keyboard::C)
        {
            bool vis = !mCharacterWin->getVisible();
            //(vis ? mCharacterWin->registerEvents() : mCharacterWin->unregisterEvents());
            mCharacterWin->setVisibility(vis);
        }
        else if (_event.key.code == sf::Keyboard::M)
        {
            bool vis = !mDialogueWindow->getVisible();
            mDialogueWindow->setVisibility(vis);
        }
        break;

    default:
        break;
    }

    return retVal;
}

void SimulationController::registerEvents()
{
    mEventManager->registerObserver(this, mInterestedEvents);
}

void SimulationController::unregisterEvents()
{
    mEventManager->unregisterObserver(this, mInterestedEvents);
}

void SimulationController::onReachTile(const sf::Vector2f & clientPos)
{
    mCurrentMap->updateVertexArray(clientPos, TempDist, TempTime);
}

void SimulationController::onDestinationReached()
{

}

void SimulationController::onWindowClose(Window * window)
{
    window->setVisibility(false);
}

void SimulationController::buttonAction(Item * item, Inventoryslot * invSlot)
{
    Item* temp = mMousePointer->getItem();
    Inventory* invRef = invSlot->getInventoryReference();
    Tile* tileRef = invSlot->getTileReference();
    if (invRef)
    {
        if (invSlot->getInventoryReference() == mControllableEntity->getInventory() &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        {
            mCurrentMap->getTileFromIndex(getCurrentPos())->
                addItem(invRef->switchItemsInSlot(temp, invSlot->getID()));
        }
        else
        {
            temp = invRef->switchItemsInSlot(temp, invSlot->getID());
            mMousePointer->switchItem(temp);
        }
    }
    else if (tileRef && !mMousePointer->getItem())
    {
        // Set action parameters
        auto ga = mControllableEntity->getGoapAgent();
        auto apui = dynamic_cast<ActionPickUpItem*> (ga->getAvailableAction(Action::PickUpItem));
        if (apui)
        {
            apui->setTargetItem(item);
            apui->setTargetTile(tileRef);
            apui->setFromInv(mRightClickCRI);
            mEntityGoals->addToGoalState(ActionHelper::Conditions::DoFetchItem);
        }
    }
}

void SimulationController::buttonAction(unsigned int action)
{
    switch (action)
    {
    case MenuButtons::Move:
        mRightClickWindow->setVisibility(false);
        doMoveToTile(mRightClickMenuTileRefPos);

        break;

    case MenuButtons::Attack:

        break;

    case MenuButtons::Interact:

        break;

    case MenuButtons::Examine:

        break;

    default:
        break;
    }
}

void SimulationController::setup(sf::RenderTarget * target, EventManager * eventManager, MousePointer* mouseP)
{
    mWindow = target;
    mEventManager = eventManager;
    mMousePointer = mouseP;
}

void SimulationController::doMoveToTile(const sf::Vector2i& targetPos)
{
    // Set action parameters
    auto ga = mControllableEntity->getGoapAgent();
    auto apui = dynamic_cast<ActionGotoTile*> (ga->getAvailableAction(Action::GotoTile));
    Tile* tileRef = mCurrentMap->getTileFromIndex(targetPos);
    if (apui)
    {
        apui->setTargetTile(tileRef);
        mEntityGoals->addToGoalState(ActionHelper::Conditions::DoGotoTile);
    }

    //std::stack<TileNode*> path;

    //mCurrentMap->findPath(getCurrentPos(), targetPos, path);
    //mControllableEntity->getMovementComponent()->setPath(path);
}

sf::Vector2i SimulationController::getCurrentPos()
{
    sf::Vector2f entityPos = mControllableEntity->getMovementComponent()->getCurrentTarget();
    return mCurrentMap->getTileIndexFromCoords(entityPos);
}
