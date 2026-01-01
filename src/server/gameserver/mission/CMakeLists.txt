# ============================================================================
# Mission/Quest info library
# ============================================================================

set(MISSION_SOURCES
    AnotherQuestRewardClass.cpp
    AnotherQuestRewardInfo.cpp
    DummyQuestStatus.cpp
    EventQuestAdvance.cpp
    EventQuestInfoManager.cpp
    EventQuestLootingManager.cpp
    EventQuestRewardManager.cpp
    GatherItemQuestInfo.cpp
    GatherItemQuestStatus.cpp
    ItemRewardInfo.cpp
    MeetNPCQuestInfo.cpp
    MeetNPCQuestStatus.cpp
    MiniGameQuestInfo.cpp
    MiniGameQuestStatus.cpp
    MonsterKillQuestInfo.cpp
    MonsterKillQuestStatus.cpp
    QuestAdvanceRewardInfo.cpp
    QuestInfo.cpp
    QuestInfoManager.cpp
    QuestManager.cpp
    QuestStatus.cpp
    RandomRewardClass.cpp
    RewardClass.cpp
    RewardClassInfoManager.cpp
    RewardInfo.cpp
    SimpleQuestInfoManager.cpp
    SimpleQuestRewardManager.cpp
    SlayerWeaponRewardClass.cpp
)

add_library(Mission STATIC ${MISSION_SOURCES})

# This code is only valid for the game server build
target_compile_definitions(Mission PRIVATE __GAME_SERVER__)

target_include_directories(Mission PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/Core
    ${CMAKE_SOURCE_DIR}/src/server
    ${CMAKE_SOURCE_DIR}/src/server/database
    ${CMAKE_SOURCE_DIR}/src/server/gameserver
)
