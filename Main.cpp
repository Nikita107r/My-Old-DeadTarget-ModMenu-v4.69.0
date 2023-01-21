#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include <Includes/Chams.h>
#include "KittyMemory/MemoryPatch.h"
#include "Menu.h"
#include "Hook.h"

#if defined(__aarch64__) //Compile for arm64 lib only
#include <And64InlineHook/And64InlineHook.hpp>
#else //Compile for armv7 lib only. Do not worry about greyed out highlighting code, it still works

#include <Substrate/SubstrateHook.h>
#include <Substrate/CydiaSubstrate.h>
#include "Includes/Chams.h"

#endif

// fancy struct for patches for kittyMemory
struct My_Patches {
    // let's assume we have patches for these functions for whatever game
    // like show in miniMap boolean function
    MemoryPatch GodMode, GodMode2, Ammos, SliderExample;
    // etc...
} hexPatches;

bool KillAllZomb = false, PlayerРазмер = false, Gold = false, Money = false, Diamonds = false, ПашолНахуйЕблан2 = false, AimBot = false, UnlockGunny = false, AutoKill = false, Attack = false, MissionShit = false;
bool RespawnEnemy = false;
float FOvVAlue = 0;
bool AimBot11 = false;
bool ANTCHEAT = false;
bool АнтиЧит = false;
bool REcoil = false;
bool EndMiss = false;
bool Ammo = false;
bool Grenades = false;
bool AidKit = false;
bool HideGun = false;
int FuckyouLeech = 0;
int Leech = 0;
bool Level1 = false;
bool MassAllKill = false;
bool ВзломКоинов = false;
int Index = 0;
int Gloves123 = 0;
float SpeedValx2 = 50;
bool Level2 = false;
bool Gloves = false;
bool Fovi = false;
bool funguns = false;
bool MassKill = false;
bool Siize = false;
bool BackFoard = false;
float EnSize = 0;
float EE = -1;
float EE2 = 0;
float EnemySize = 2.6;
bool chamstoggle = false;
bool EnemySizess = false;
bool RepairArmor = false;
bool ПриблизитьКамеру = false;
bool GodFalse = false;
float firstCamVal = 4;

enum E_MissionResult {
    Success = 0,
    PlayerKilled = 1,
    DoorDestroyed = 2,
};

// Function pointer splitted because we want to avoid crash when the il2cpp lib isn't loaded.
// If you putted getAbsoluteAddress here, the lib tries to read the address without il2cpp loaded,
// will result in a null pointer which will cause crash
// See https://guidedhacking.com/threads/android-function-pointers-hooking-template-tutorial.14771/
void (*FadeOutMusic)(void *instance, float fadeOutTime);
void (*IgnoreLayerCollision)(void *instance, int layer1, int layer2);
void (*UnlockGun)(void *instance, int guid, int skin);
void (*UnlockGloves)(void *instance, int guid);
void (*KillSAAL)(void *instance);
void (*ReArmor)(void *instance);
bool (*IsMine)(void *instance);
void (*KillAllPlayer)(void *_gay);
void (*NextGun)(void *_gay, int value);
void (*FindTargetZombie)(void *_gay);
void (*HP)(void *_gay);
void (*RightBtnOnClick)(void *_gay);
void (*Fov)(void *_gay, float amount);

//Target lib here
#define targetLibName OBFUSCATE("libil2cpp.so")

// we will run our patches in a new thread so our while loop doesn't block process main thread
// Don't forget to remove or comment out logs before you compile it.

//KittyMemory Android Example: https://github.com/MJx0/KittyMemory/blob/master/Android/test/src/main.cpp
//Use ARM Converter to convert ARM to HEX: https://armconverter.com/
//Note: We use OBFUSCATE_KEY for offsets which is the important part xD

// Hooking example. Please refer to online tutorials how to hook

void* mypositions;
void* enemyposition;

void (*old_ZombieBase)(void *zombi);
void get_ZombieBase(void *zombi) {
    if (zombi != NULL) {
        enemyposition = zombi;
    }
    old_ZombieBase(zombi);
}

void (*old_PlayerController)(void *player);
void get_PlayerController(void *player) {
    if (player != NULL) {
        if (PlayerРазмер) {
            void *_opa = Component_GetTransform(player);
            Vector3 MountTFs = Transform_INTERNAL_GetPosition(_opa) -
                               (GetForward(_opa) * -EnemySize);
            set_position(Component_GetTransform(player), MountTFs);
            PlayerРазмер = false;
        }
        if (BackFoard) {
            void *_opa = Component_GetTransform(player);
            Vector3 MountTFs = Transform_INTERNAL_GetPosition(_opa) -
                               (GetForward(_opa) * EnemySize);
            set_position(Component_GetTransform(player), MountTFs);
            BackFoard = false;
        }
        if (EnemySizess) {
            set_localScale(Component_GetTransform(enemyposition), Vector3(EnSize,EnSize,EnSize));
        }
        if (GodFalse) {
            HP(player);
        }
        if (AimBot) {
            FindTargetZombie(player);
        }
        if (MassKill) {
            void *_opa = Component_GetTransform(player);
            Vector3 MountTFs = Transform_INTERNAL_GetPosition(_opa) -
                               (GetForward(_opa) * -2.6f);
            set_position(Component_GetTransform(enemyposition), MountTFs);
        }
    }
    old_PlayerController(player);
}

void (*old_DSystem)(void *playerыы);
void get_DSystem(void *playerыы) {
    if (playerыы != NULL) {
        if (RepairArmor) {
            ReArmor(playerыы);
        }
        if (UnlockGunny) {
            UnlockGun(playerыы, FuckyouLeech, Leech);
        }
        if (Gloves) {
            UnlockGloves(playerыы, Gloves123);
        }
    }
    old_DSystem(playerыы);
}

void (*old_MainUIEvent)(void *playerыы);
void get_MainUIEvent(void *playerыы) {
    if (playerыы != NULL) {
        if (EndMiss) {
            RightBtnOnClick(playerыы);
        }
    }
    old_MainUIEvent(playerыы);
}

void (*old_Gameplay)(void *player);
void get_Gameplay(void *player) {
    if (player != NULL) {
        if (KillAllZomb) {
            KillSAAL(player);
        }
    }
    old_Gameplay(player);
}

int (*old_AmmoBull)(void *instance);
int get_AmmoBull(void *instance) {
    if (instance != NULL && Ammo) {
        return 107107107;
    }
    return old_AmmoBull(instance);
}

int (*old_maxAccuracy)(void *instance);
int get_maxAccuracy(void *instance) {
    if (instance != NULL && REcoil) {
        return 0x64;
    }
    return old_maxAccuracy(instance);
}

int (*old_Grena)(void *instance);
int get_Grena(void *instance) {
    if (instance != NULL && Grenades) {
        return 107107107;
    }
    return old_Grena(instance);
}

int (*old_AidK)(void *instance);
int get_AidK(void *instance) {
    if (instance != NULL && AidKit) {
        return 107107107;
    }
    return old_AidK(instance);
}

int (*old_Money)(void *instance);
int get_Money(void *instance) {
    if (instance != NULL && Money) {
        return 107107107;
    }
    return old_Money(instance);
}

int (*old_Gold)(void *instance);
int get_Gold(void *instance) {
    if (instance != NULL && Gold) {
        return 107107107;
    }
    return old_Gold(instance);
}

int (*old_Diamond)(void *instance);
int get_Diamond(void *instance) {
    if (instance != NULL && Diamonds) {
        return 107107107;
    }
    return old_Diamond(instance);
}

int (*old_Level)(void *instance);
int get_Level(void *instance) {
    if (instance != NULL && Level1) {
        return 99;
    }
    return old_Level(instance);
}

void *hack_thread(void *) {
    LOGI(OBFUSCATE("pthread created"));

    //Check if target lib is loaded
    do {
        sleep(1);
        setShader("_BumpMap");
        Wallhack();
        LogShaders();
        mlovinit();
    } while (!isLibraryLoaded(targetLibName) && mlovinit());

#if defined(__aarch64__) //Compile for arm64 lib only
    // New way to patch hex via KittyMemory without need to  specify len. Spaces or without spaces are fine
    // ARM64 assembly example
    // MOV X0, #0x0 = 00 00 80 D2
    // RET = C0 03 5F D6
    hexPatches.GodMode = MemoryPatch::createWithHex(targetLibName,
                                                    string2Offset(OBFUSCATE_KEY("0x123456", '3')),
                                                    OBFUSCATE("00 00 80 D2 C0 03 5F D6"));
    //You can also specify target lib like this
    hexPatches.GodMode2 = MemoryPatch::createWithHex("libtargetLibHere.so",
                                                     string2Offset(OBFUSCATE_KEY("0x222222", 'g')),
                                                     OBFUSCATE("20 00 80 D2 C0 03 5F D6"));

    // Offset Hook example
    //A64HookFunction((void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0x123456", 'l'))), (void *) get_BoolExample,
    //                (void **) &old_get_BoolExample);

    // Function pointer splitted because we want to avoid crash when the il2cpp lib isn't loaded.
    // See https://guidedhacking.com/threads/android-function-pointers-hooking-template-tutorial.14771/
    //AddMoneyExample = (void(*)(void *,int))getAbsoluteAddress(targetLibName, 0x123456);

#else //Compile for armv7 lib only. Do not worry about greyed out highlighting code, it still works

    // New way to patch hex via KittyMemory without need to specify len. Spaces or without spaces are fine
    // ARMv7 assembly example
    // MOV R0, #0x0 = 00 00 A0 E3
    // BX LR = 1E FF 2F E1
    hexPatches.Ammos = MemoryPatch("libil2cpp.so", 0x36C760,
                                   "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    //Can apply patches directly here without need to use switch
    //hexPatches.GodMode.Modify();
    //hexPatches.GodMode2.Modify();

    // Offset Hook example
////////////////////////////////////////////////////////////////////////////////////////////////////FLY && NOCLIP
//////////////////////////////////////////////////////////////////////////////////////////////////////////

    MSHookFunction((void *) getAbsoluteAddress(targetLibName, 0x1FE6888), (void *) get_PlayerController,
                   (void **) &old_PlayerController);
    MSHookFunction((void *) getAbsoluteAddress(targetLibName, 0x72C7E0), (void *) get_DSystem,
                   (void **) &old_DSystem);
    MSHookFunction((void *) getAbsoluteAddress(targetLibName, 0x72B980), (void *) get_ZombieBase,
                   (void **) &old_ZombieBase);
    MSHookFunction((void *) getAbsoluteAddress(targetLibName, 0x1CDC154), (void *) get_Gameplay,
                   (void **) &old_Gameplay);
    MSHookFunction((void *) getAbsoluteAddress(targetLibName, 0x1D2DE54), (void *) get_AmmoBull,
                   (void **) &old_AmmoBull);
    MSHookFunction((void *) getAbsoluteAddress(targetLibName, 0x1BFA29C), (void *) get_Grena,
                   (void **) &old_Grena);
    MSHookFunction((void *) getAbsoluteAddress(targetLibName, 0x1BFA534), (void *) get_AidK,
                   (void **) &old_AidK);
    MSHookFunction((void *) getAbsoluteAddress(targetLibName, 0x1BF05FC), (void *) get_Money,
                   (void **) &old_Money);
    MSHookFunction((void *) getAbsoluteAddress(targetLibName, 0x1BF14AC), (void *) get_Gold,
                   (void **) &old_Gold);
    MSHookFunction((void *) getAbsoluteAddress(targetLibName, 0x1BF1E48), (void *) get_Diamond,
                   (void **) &old_Diamond);
    MSHookFunction((void *) getAbsoluteAddress(targetLibName, 0x1BF97E4), (void *) get_Level,
                   (void **) &old_Level);
    MSHookFunction((void *) getAbsoluteAddress(targetLibName, 0x1CA6B54), (void *) get_MainUIEvent,
                   (void **) &old_MainUIEvent);
    // Symbol hook example (untested). Symbol/function names can be found in IDA if the lib are not stripped. This is not for il2cpp games
    //MSHookFunction((void *) ("__SymbolNameExample"), (void *) get_BoolExample, (void **) &old_get_BoolExample);

    // Function pointer splitted because we want to avoid crash when the il2cpp lib isn't loaded.
    // See https://guidedhacking.com/threads/android-function-pointers-hooking-template-tutorial.14771/
    FindTargetZombie = (void (*)(void *)) getAbsoluteAddress(targetLibName, 0x1FF0F90);
    KillAllPlayer = (void (*)(void *)) getAbsoluteAddress(targetLibName, 0x1CE86A4);
    HP = (void (*)(void *)) getAbsoluteAddress(targetLibName, 0x1FE4BE4);
    RightBtnOnClick = (void (*)(void *)) getAbsoluteAddress(targetLibName, 0x1CB2C54);
    ReArmor = (void (*)(void *)) getAbsoluteAddress(targetLibName, 0x1C2DF00);
    KillSAAL = (void (*)(void *)) getAbsoluteAddress(targetLibName, 0x1CE86A4);
    UnlockGun = (void (*)(void *,int,int)) getAbsoluteAddress(targetLibName, 0x1C30704);
    UnlockGloves = (void (*)(void *,int)) getAbsoluteAddress(targetLibName, 0x1C31388);


    LOGI(OBFUSCATE("Done"));
#endif

    return NULL;
}

//JNI calls
extern "C" {
// Note:
// Do not change or translate the first text unless you know what you are doing
// Assigning feature numbers is optional. Without it, it will automatically count for you, starting from 0
// Assigned feature numbers can be like any numbers 1,3,200,10... instead in order 0,1,2,3,4,5...
// ButtonLink, Category, RichTextView and RichWebView is not counted. They can't have feature number assigned
// Toggle, ButtonOnOff and Checkbox can be switched on by default, if you add True_. Example: CheckBox_True_The Check Box
// To learn HTML, go to this page: https://www.w3schools.com/

JNIEXPORT jobjectArray
JNICALL
Java_ac_activity_game_FloatingService_getFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;

    //Toasts added here so it's harder to remove it
    MakeToast(env, context, OBFUSCATE("MODDED By Nikita107r | Platinmods.com"), Toast::LENGTH_LONG);

    const char *features[] = {
            OBFUSCATE("Collapse_Player"),
            OBFUSCATE("CollapseAdd_CheckBox_GodMode"), // 0
            OBFUSCATE("CollapseAdd_CheckBox_KillPlayer"), // 1
            OBFUSCATE("CollapseAdd_CheckBox_Repair Armor"), // 2
            OBFUSCATE("CollapseAdd_Button2_Forward"), // 3
            OBFUSCATE("CollapseAdd_Button2_Back"), //4

            OBFUSCATE("Collapse_Drawing"),
            OBFUSCATE("CollapseAdd_CheckBox_CrossHairV1"), // 5
            OBFUSCATE("CollapseAdd_CheckBox_CrossHairV2"), // 6
            OBFUSCATE("CollapseAdd_CheckBox_DrawCircle"), // 7
            OBFUSCATE("CollapseAdd_SeekBar_Circle Size_0_500"), //8
            OBFUSCATE("CollapseAdd_SeekBar_Color_0_6"), //9
            OBFUSCATE("CollapseAdd_SeekBar_CrossHair Size_0_500"), //10

            OBFUSCATE("Collapse_Zombie"),
            OBFUSCATE("CollapseAdd_CheckBox_Chams"), // 11
            OBFUSCATE("CollapseAdd_CheckBox_SizeEnemy"), // 12
            OBFUSCATE("CollapseAdd_SeekBar_SizeEnemyValue_0_20"), //13
            OBFUSCATE("CollapseAdd_CheckBox_KillAllZom"), // 14
            OBFUSCATE("CollapseAdd_CheckBox_MassKill"), // 15

            OBFUSCATE("Collapse_Weapon"),
            OBFUSCATE("CollapseAdd_CheckBox_Ammo"), // 16
            OBFUSCATE("CollapseAdd_CheckBox_EndMission"), // 17
            OBFUSCATE("CollapseAdd_CheckBox_No Spread"), // 18

            OBFUSCATE("Collapse_Item"),
            OBFUSCATE("CollapseAdd_CheckBox_Grenades"), // 19
            OBFUSCATE("CollapseAdd_CheckBox_AidKit"), // 20

            OBFUSCATE("Collapse_Shop"),
            OBFUSCATE("CollapseAdd_CheckBox_Money"), // 21
            OBFUSCATE("CollapseAdd_CheckBox_Gold"), // 22
            OBFUSCATE("CollapseAdd_CheckBox_Diamond"), // 23
            OBFUSCATE("CollapseAdd_CheckBox_LeveL 99"), // 24
            OBFUSCATE("CollapseAdd_Spinner_UnlockGun_Weap1,Weap2,Weap3,Weap4,Weap5,Weap6,Weap7,Weap8,Weap9,Weap10,Weap11,Weap12,Weap13,Weap14,Weap15,Weap16,Weap17,Weap18,Weap19,Weap20,Weap21,Weap22,Weap23"), // 25
            OBFUSCATE("CollapseAdd_InputValue_SkinGunId"), // 26
            OBFUSCATE("CollapseAdd_CheckBox_UnlockGloves"), // 27
            OBFUSCATE("CollapseAdd_InputValue_UnlockGlovesId"), // 28


            OBFUSCATE("Collapse_Credits(СоздательЧита)"),
            OBFUSCATE("CollapseAdd_ButtonLink_Nikita107r_https://www.youtube.com/c/Nikita107r2"),
            OBFUSCATE("CollapseAdd_ButtonLink_Discord_https://discord.gg/NP2Tmzn")
    };

    //Now you dont have to manually update the number everytime;
    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    pthread_t ptid;
    pthread_create(&ptid, NULL, antiLeech, NULL);

    return (ret);
}

JNIEXPORT void JNICALL
Java_ac_activity_game_Preferences_Changes(JNIEnv *env, jclass clazz, jobject obj,
                                        jint featNum, jstring featName, jint value,
                                        jboolean boolean, jstring str) {
    //Convert java string to c++
    const char *featureName = env->GetStringUTFChars(featName, 0);
    const char *TextInput;
    if (str != NULL)
        TextInput = env->GetStringUTFChars(str, 0);
    else
        TextInput = "Empty";

    LOGD(OBFUSCATE("Feature name: %d - %s | Value: = %d | Bool: = %d | Text: = %s"), featNum,
         featureName, value,
         boolean, TextInput);

    //BE CAREFUL NOT TO ACCIDENTLY REMOVE break;

    switch (featNum) {
        ////////player////////
        case 0:
            GodFalse = boolean;
            break;
        case 1:
            AimBot = boolean;
            break;
        case 2:
            RepairArmor = boolean;
            break;
        case 3:
            PlayerРазмер = boolean;
            break;
        case 4:
            BackFoard = boolean;
            break;
     //////////Drawing//////////////
        case 5:
            isESP = boolean;
            break;
        case 6:
            Crosshire = boolean;
            break;
        case 7:
            DrawCircle = boolean;
            break;
        case 8:
            CirclesSize = value;
            break;
        case 9:
                ESP esp();
            //Speed hack in KittyMemory
            if (value == 0)
            {
                Color0 = true;
                Color5 = false;
                Color6 = false;
            }
            else if (value == 1)
            {
                Color0 = false;
                Color6 = false;
                Color5 = false;
                Color1 = true;
            }
            else if (value == 2)
            {
                Color1 = false;
                Color6 = false;
                Color5 = false;
                Color2 = true;
            }
            else if (value == 3)
            {
                Color2 = false;
                Color6 = false;
                Color5 = false;
                Color3 = true;
            }
            else if (value == 4)
            {
                Color3 = false;
                Color6 = false;
                Color5 = false;
                Color4 = true;
            }
            else if (value == 5)
            {
                Color4 = false;
                Color6 = false;
                Color5 = true;
            }
            else if (value == 6)
            {
                Color5 = false;
                Color6 = true;
            }
            //LOGD("feature 5");
            break;
        case 10:
            CrosshireSize = value;
            break;
        case 11:
            chamstoggle = boolean;
            if (chamstoggle) {
                SetWallhack2(true);
            } else {
                SetWallhack2(false);
            }
            break;
        case 12:
            EnemySizess = boolean;
            break;
        case 13:
            EnSize = value;
            break;
        case 14:
            KillAllZomb = boolean;
            break;
        case 15:
            MassKill = boolean;
            break;
        case 16:
            Ammo = boolean;
            break;
        case 17:
            EndMiss = boolean;
            break;
        case 18:
            REcoil = boolean;
            break;
        case 19:
            Grenades = boolean;
            break;
        case 20:
            AidKit = boolean;
            break;
        case 21:
            Money = boolean;
            break;
        case 22:
            Gold = boolean;
            break;
        case 23:
            Diamonds = boolean;
            break;
        case 24:
            Level1 = boolean;
            break;
        case 25:
            switch (value) {
                case 1:
                    LOGD(OBFUSCATE("Selected item 2"));
                    break;
                case 2:
                    LOGD(OBFUSCATE("Selected item 3"));
                    break;
                case 3:
                    UnlockGunny = true;
                    FuckyouLeech = 9;
                    LOGD(OBFUSCATE("Selected item 1"));
                    break;
                case 4:
                    UnlockGunny = true;
                    FuckyouLeech = 4;
                    LOGD(OBFUSCATE("Selected item 2"));
                    break;
                case 5:
                    UnlockGunny = true;
                    FuckyouLeech = 3;
                    LOGD(OBFUSCATE("Selected item 3"));
                    break;
                case 6:
                    UnlockGunny = true;
                    FuckyouLeech = 7;
                    LOGD(OBFUSCATE("Selected item 1"));
                    break;
                case 7:
                    UnlockGunny = true;
                    FuckyouLeech = 10;
                    LOGD(OBFUSCATE("Selected item 2"));
                    break;
                case 8:
                    LOGD(OBFUSCATE("Selected item 3"));
                    break;
                case 9:
                    UnlockGunny = true;
                    FuckyouLeech = 5;
                    LOGD(OBFUSCATE("Selected item 1"));
                    break;
                case 10:
                    UnlockGunny = true;
                    FuckyouLeech = 15;
                    LOGD(OBFUSCATE("Selected item 2"));
                    break;
                case 11:
                    UnlockGunny = true;
                    FuckyouLeech = 14;
                    LOGD(OBFUSCATE("Selected item 3"));
                    break;
                case 12:
                    LOGD(OBFUSCATE("Selected item 1"));
                    break;
                case 13:
                    UnlockGunny = true;
                    FuckyouLeech = 25;
                    LOGD(OBFUSCATE("Selected item 2"));
                    break;
                case 14:
                    UnlockGunny = true;
                    FuckyouLeech = 13;
                    LOGD(OBFUSCATE("Selected item 3"));
                    break;
                case 15:
                    UnlockGunny = true;
                    FuckyouLeech = 12;
                    LOGD(OBFUSCATE("Selected item 1"));
                    break;
                case 16:
                    UnlockGunny = true;
                    FuckyouLeech = 16;
                    LOGD(OBFUSCATE("Selected item 2"));
                    break;
                case 17:
                    UnlockGunny = true;
                    FuckyouLeech = 19;
                    LOGD(OBFUSCATE("Selected item 3"));
                    break;
                case 18:
                    UnlockGunny = true;
                    FuckyouLeech = 21;
                    LOGD(OBFUSCATE("Selected item 1"));
                    break;
                case 19:
                    UnlockGunny = true;
                    FuckyouLeech = 22;
                    LOGD(OBFUSCATE("Selected item 2"));
                    break;
                case 20:
                    UnlockGunny = true;
                    FuckyouLeech = 23;
                    LOGD(OBFUSCATE("Selected item 3"));
                    break;
                case 21:
                    UnlockGunny = true;
                    FuckyouLeech = 18;
                    break;
                case 22:
                    UnlockGunny = true;
                    FuckyouLeech = 19;
                    LOGD(OBFUSCATE("Selected item 3"));
                    break;
            }
            break;
        case 26:
            Leech = value;
        break;
        case 27:
           Gloves = boolean;
           break;
        case 28:
           Gloves123 = value;
           break;
}
}

//No need to use JNI_OnLoad, since we don't use JNIEnv
//We do this to hide OnLoad from disassembler
__attribute__((constructor))
void lib_main() {
    // Create a new thread so it does not block the main thread, means the game would not freeze
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}

/*
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *globalEnv;
    vm->GetEnv((void **) &globalEnv, JNI_VERSION_1_6);
    return JNI_VERSION_1_6;
}
 */}