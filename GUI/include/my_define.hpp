/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** mydefine.hpp
*/

#ifndef KEV_DEFINE_
    #define KEV_DEFINE_

    

    #define WIN_TITLE "ZAPPY - SIMULATION"
    #define GIVE_RESSOURCE(x) (std::string("./GUI/ressources/") + x)
    #define GIVE_FONT_PATH(x, ext) (GIVE_RESSOURCE( ((std::string("font/") + x)) ) + ext)
    #define GIVE_SHADER(x) (std::string(GIVE_RESSOURCE("shaders/") + x))
    #define GIVE_3D_MODEL_PATH(fileDir, extension, fileName ) (GIVE_RESSOURCE(std::string("gltf/") + fileDir + std::string("/")) + fileName + extension)
    #define GIVE_3D_OBJECT_GLB(x) (std::string(GIVE_RESSOURCE("glb/")) + x + ".glb")
    #define GIVE_AUDIO_OBJECT(x, ext) (std::string(GIVE_RESSOURCE("audio/")) + x +"."+ ext)

    #define TRANSFORM_NUM_TO_PERCENTAGE(actual, max) ((double)(actual *100 /(max? max: 1)))
    #define TRANSFORM_PERCENTAGE_TO_NUM(percentage, max) ((double) (percentage * max /100))


    //ressources scale
    #define FOOD_SCALE 1.2f
    #define LINEMATE_SCALE 0.1f
    #define DERAUMERE_SCALE 0.15f
    #define SIBUR_SCALE 0.003f
    #define MENDIANE_SCALE 0.035f
    #define phiras_SCALE 0.035f
    #define THYSTAME_SCALE 0.3f
    #define GET_DEFAULT_SCALE(res_id) (res_id == 0 ? FOOD_SCALE : res_id == 1 ? LINEMATE_SCALE : res_id == 2 ? DERAUMERE_SCALE : res_id == 3 ? SIBUR_SCALE : res_id == 4 ? MENDIANE_SCALE : res_id == 5 ? phiras_SCALE : res_id == 6 ? THYSTAME_SCALE : 1.0f)
    #define GRID_SIZE 3

    #define PLATFORM1_SCALE (Vector3){(float)1.0f/5, 1.0f/5, 1.0f/5}
    #define PLATFORM2_SCALE (Vector3){(float)1.0f/3, 1.0f/3, 1.0f/3}
    #define PLATFORM3_SCALE (Vector3){(float)1.0f*3.0, 1.0f*3.0, 1.0f*3.0}
    #define PLATFORM4_SCALE (Vector3){(float)1.0f/15, 1.0f/15, 1.0f/15}
    #define PLATFORM5_SCALE (Vector3){(float)1.0f/160, 1.0f/180, 1.0f/160}
    #define PLATFORM6_SCALE (Vector3){(float)1.0f*3, 1.0f*3, 1.0f*3}
    #define PLATFORM7_SCALE (Vector3){(float)1.0f/15, 1.0f/15, 1.0f/15}
    #define PLATFORM8_SCALE (Vector3){(float)1.0f*3, 1.0f*3, 1.0f*3}
    #define PLATFORM9_SCALE (Vector3){(float)1.0f, 1.0f, 1.0f}
    #define PLATFORM10_SCALE (Vector3){(float)1.0f/130.0f, 1.0f/130.0f, 1.0f/130.0f}
    #define BRIDGE_SCALE (Vector3){(float)1.0f/4, 1.0f/4, 1.0f/4}
    // #define EGG_SCALE (Vector3){(float)1.0f/400.0f, 1.0f/400.0f, 1.0f/400.0f}
    #define EGG_SCALE (Vector3){(float)1.0f/100.0f, 1.0f/100.0f, 1.0f/100.0f}
    #define EGG_SCALE_BY(ft) (Vector3){(float)EGG_SCALE.x*ft, EGG_SCALE.y*ft, EGG_SCALE.z*ft}
    #define PORTAL_SCALE (Vector3) {1.0f, 1.0f, 1.0f}

    #define PLATFORM1_FIRST_POS (Vector3){(float)(0.0) , (float)  0.0f, (float) (0.0)}
    #define PLATFORM2_FIRST_POS (Vector3){(float)(0.0) , (float)  0.0f, (float) (0.0)}
    #define PLATFORM3_FIRST_POS (Vector3){(float)(0.0) , (float)  0.0f, (float) (0.0)}
    #define PLATFORM4_FIRST_POS (Vector3){(float)(0.0) , (float)  -0.4f, (float) (0.0)}
    #define PLATFORM5_FIRST_POS (Vector3){(float)(0.0) , (float)  -2.0f, (float) (0.0)}
    #define PLATFORM6_FIRST_POS (Vector3){(float)(0.0) , (float)  0.0f, (float) (0.0)}
    #define PLATFORM7_FIRST_POS (Vector3){(float)(0.0) , (float)  -0.1f, (float) (0.0)}
    #define PLATFORM8_FIRST_POS (Vector3){(float)(-1.0) , (float)  0.4f, (float) (-1.0)}
    #define PLATFORM9_FIRST_POS (Vector3){(float)(0.0) , (float)  0.0f, (float) (0.0)}
    #define PLATFORM10_FIRST_POS (Vector3){(float)(0.0) , (float)  -4.4f, (float) (0.0)}
    #define BRIDGE_FIRST_POS (Vector3){(float)(-2.50) , (float)  -0.5f, (float) (3.0)}
    #define PORTAL_FIRST_POS (Vector3) {0.0f,-0.20f,0.0f}

    #define EGG_3D_MODEL                "egg"
    
    
    #define SKELETON_3D_MODEL           "skeleton"
    #define SKELETON_ANIM_IDLE          41 - 1
    #define SKELETON_ANIM_WALK          91 - 1
    #define SKELETON_ANIM_PICK          54 - 1
    #define SKELETON_ANIM_DROP          84 - 1
    #define SKELETON_ANIM_ECSTASY       83 - 1
    #define SKELETON_ANIM_LAY           61 - 1
    #define SKELETON_ANIM_SPAWN         70 - 1
    #define SKELETON_ANIM_DIE           30 - 1
    #define SKELETON_ANIM_EXPULSE       38 - 1
    #define SKELETON_ANIM_NO_ANIMATION  65 - 1
    #define GIVE_SKELETON_ANIM(x) \
        ( \
            x ==-1 ? SKELETON_ANIM_NO_ANIMATION :\
            x == 0 ? SKELETON_ANIM_IDLE :\
            x == 1 ? SKELETON_ANIM_WALK :\
            x == 2 ? SKELETON_ANIM_PICK :\
            x == 3 ? SKELETON_ANIM_DROP :\
            x == 4 ? SKELETON_ANIM_ECSTASY :\
            x == 5 ? SKELETON_ANIM_LAY :\
            x == 6 ? SKELETON_ANIM_SPAWN :\
            x == 7 ? SKELETON_ANIM_DIE :\
            SKELETON_ANIM_EXPULSE \
        )

    #define SKELETON_ROGUE_3D_MODEL             "skeleton_rogue"
    #define SKELETON_ROGUE_ANIM_IDLE            42 - 1
    #define SKELETON_ROGUE_ANIM_WALK            91 - 1
    #define SKELETON_ROGUE_ANIM_PICK            54 - 1
    #define SKELETON_ROGUE_ANIM_DROP            84 - 1
    #define SKELETON_ROGUE_ANIM_ECSTASY         83 - 1
    #define SKELETON_ROGUE_ANIM_LAY             61 - 1
    #define SKELETON_ROGUE_ANIM_SPAWN           70 - 1
    #define SKELETON_ROGUE_ANIM_DIE             27 - 1
    #define SKELETON_ROGUE_ANIM_EXPULSE         38 - 1
    #define SKELETON_ROGUE_ANIM_NO_ANIMATION    65 - 1
    #define GIVE_SKELETON_ROGUE_ANIM(x) \
        ( \
            x ==-1 ? SKELETON_ROGUE_ANIM_NO_ANIMATION:\
            x == 0 ? SKELETON_ROGUE_ANIM_IDLE :\
            x == 1 ? SKELETON_ROGUE_ANIM_WALK :\
            x == 2 ? SKELETON_ROGUE_ANIM_PICK :\
            x == 3 ? SKELETON_ROGUE_ANIM_DROP :\
            x == 4 ? SKELETON_ROGUE_ANIM_ECSTASY :\
            x == 5 ? SKELETON_ROGUE_ANIM_LAY :\
            x == 6 ? SKELETON_ROGUE_ANIM_SPAWN :\
            x == 7 ? SKELETON_ROGUE_ANIM_DIE :\
            SKELETON_ROGUE_ANIM_EXPULSE \
        )

    #define SKELETON_MAGE_3D_MODEL          "skeleton_mage"
    #define SKELETON_MAGE_ANIM_IDLE         15 - 1
    #define SKELETON_MAGE_ANIM_WALK         92 - 1
    #define SKELETON_MAGE_ANIM_PICK         54 - 1
    #define SKELETON_MAGE_ANIM_DROP         84 - 1
    #define SKELETON_MAGE_ANIM_ECSTASY      83 - 1
    #define SKELETON_MAGE_ANIM_LAY          61 - 1
    #define SKELETON_MAGE_ANIM_SPAWN        70 - 1
    #define SKELETON_MAGE_ANIM_DIE          30 - 1
    #define SKELETON_MAGE_ANIM_EXPULSE      14 - 1
    #define SKELETON_MAGE_ANIM_NO_ANIMATION 65 - 1
    #define GIVE_SKELETON_MAGE_ANIM(x) \
        ( \
            x == -1 ? SKELETON_MAGE_ANIM_NO_ANIMATION:\
            x == 0 ? SKELETON_MAGE_ANIM_IDLE :\
            x == 1 ? SKELETON_MAGE_ANIM_WALK :\
            x == 2 ? SKELETON_MAGE_ANIM_PICK :\
            x == 3 ? SKELETON_MAGE_ANIM_DROP :\
            x == 4 ? SKELETON_MAGE_ANIM_ECSTASY :\
            x == 5 ? SKELETON_MAGE_ANIM_LAY :\
            x == 6 ? SKELETON_MAGE_ANIM_SPAWN :\
            x == 7 ? SKELETON_MAGE_ANIM_DIE :\
            SKELETON_MAGE_ANIM_EXPULSE \
        )

    #define SKELETON_KNIGHT_3D_MODEL            "skeleton_knight"
    #define SKELETON_KNIGHT_ANIM_IDLE           15 - 1
    #define SKELETON_KNIGHT_ANIM_WALK           92 - 1
    #define SKELETON_KNIGHT_ANIM_PICK           54 - 1
    #define SKELETON_KNIGHT_ANIM_DROP           84 - 1
    #define SKELETON_KNIGHT_ANIM_ECSTASY        83 - 1
    #define SKELETON_KNIGHT_ANIM_LAY            61 - 1
    #define SKELETON_KNIGHT_ANIM_SPAWN          70 - 1
    #define SKELETON_KNIGHT_ANIM_DIE            30 - 1
    #define SKELETON_KNIGHT_ANIM_EXPULSE        14 - 1
    #define SKELETON_KNIGHT_ANIM_NO_ANIMATION   65 - 1
    #define GIVE_SKELETON_KNIGHT_ANIM(x) \
        ( \
            x ==-1 ? SKELETON_KNIGHT_ANIM_NO_ANIMATION:\
            x == 0 ? SKELETON_KNIGHT_ANIM_IDLE :\
            x == 1 ? SKELETON_KNIGHT_ANIM_WALK :\
            x == 2 ? SKELETON_KNIGHT_ANIM_PICK :\
            x == 3 ? SKELETON_KNIGHT_ANIM_DROP :\
            x == 4 ? SKELETON_KNIGHT_ANIM_ECSTASY :\
            x == 5 ? SKELETON_KNIGHT_ANIM_LAY :\
            x == 6 ? SKELETON_KNIGHT_ANIM_SPAWN :\
            x == 7 ? SKELETON_KNIGHT_ANIM_DIE :\
            SKELETON_KNIGHT_ANIM_EXPULSE \
        )

    #define HUMAN_3D_MODEL          "human"
    #define HUMAN_ANIM_IDLE         41 - 1
    #define HUMAN_ANIM_WALK         55 - 1
    #define HUMAN_ANIM_PICK         54 - 1
    #define HUMAN_ANIM_DROP         84 - 1
    #define HUMAN_ANIM_ECSTASY      24 - 1
    #define HUMAN_ANIM_LAY          61 - 1
    #define HUMAN_ANIM_SPAWN        74 - 1
    #define HUMAN_ANIM_DIE          27 - 1
    #define HUMAN_ANIM_EXPULSE      87 - 1
    #define HUMAN_ANIM_NO_ANIMATION 51 - 1
    #define GIVE_HUMAN_ANIM(x) \
        ( \
            x ==-1 ? HUMAN_ANIM_NO_ANIMATION: \
            x == 0 ? HUMAN_ANIM_IDLE :\
            x == 1 ? HUMAN_ANIM_WALK :\
            x == 2 ? HUMAN_ANIM_PICK :\
            x == 3 ? HUMAN_ANIM_DROP :\
            x == 4 ? HUMAN_ANIM_ECSTASY :\
            x == 5 ? HUMAN_ANIM_LAY :\
            x == 6 ? HUMAN_ANIM_SPAWN :\
            x == 7 ? HUMAN_ANIM_DIE :\
            HUMAN_ANIM_EXPULSE \
        )

    #define HUMAN_ROGUE_3D_MODEL            "human_rogue"
    #define HUMAN_ROGUE_ANIM_IDLE           37 - 1
    #define HUMAN_ROGUE_ANIM_WALK           49 - 1
    #define HUMAN_ROGUE_ANIM_PICK           48 - 1
    #define HUMAN_ROGUE_ANIM_DROP           66 - 1
    #define HUMAN_ROGUE_ANIM_ECSTASY        23 - 1
    #define HUMAN_ROGUE_ANIM_LAY            54 - 1
    #define HUMAN_ROGUE_ANIM_SPAWN          47 - 1
    #define HUMAN_ROGUE_ANIM_DIE            24 - 1
    #define HUMAN_ROGUE_ANIM_EXPULSE        68 - 1
    #define HUMAN_ROGUE_ANIM_NO_ANIMATION   45 - 1
    #define GIVE_HUMAN_ROGUE_ANIM(x) \
        ( \
            x ==-1 ? HUMAN_ROGUE_ANIM_NO_ANIMATION:\
            x == 0 ? HUMAN_ROGUE_ANIM_IDLE :\
            x == 1 ? HUMAN_ROGUE_ANIM_WALK :\
            x == 2 ? HUMAN_ROGUE_ANIM_PICK :\
            x == 3 ? HUMAN_ROGUE_ANIM_DROP :\
            x == 4 ? HUMAN_ROGUE_ANIM_ECSTASY :\
            x == 5 ? HUMAN_ROGUE_ANIM_LAY :\
            x == 6 ? HUMAN_ROGUE_ANIM_SPAWN :\
            x == 7 ? HUMAN_ROGUE_ANIM_DIE :\
            HUMAN_ROGUE_ANIM_EXPULSE \
        )

    #define HUMAN_MAGE_3D_MODEL             "human_mage"
    #define HUMAN_MAGE_ANIM_IDLE            41 - 1
    #define HUMAN_MAGE_ANIM_WALK            50 - 1
    #define HUMAN_MAGE_ANIM_PICK            48 - 1
    #define HUMAN_MAGE_ANIM_DROP            66 - 1
    #define HUMAN_MAGE_ANIM_ECSTASY         23 - 1
    #define HUMAN_MAGE_ANIM_LAY             54 - 1
    #define HUMAN_MAGE_ANIM_SPAWN           47 - 1
    #define HUMAN_MAGE_ANIM_DIE             24 - 1
    #define HUMAN_MAGE_ANIM_EXPULSE         68 - 1
    #define HUMAN_MAGE_ANIM_NO_ANIMATION    45 - 1
    #define GIVE_HUMAN_MAGE_ANIM(x) \
        ( \
            x ==-1 ? HUMAN_MAGE_ANIM_NO_ANIMATION:\
            x == 0 ? HUMAN_MAGE_ANIM_IDLE :\
            x == 1 ? HUMAN_MAGE_ANIM_WALK :\
            x == 2 ? HUMAN_MAGE_ANIM_PICK :\
            x == 3 ? HUMAN_MAGE_ANIM_DROP :\
            x == 4 ? HUMAN_MAGE_ANIM_ECSTASY :\
            x == 5 ? HUMAN_MAGE_ANIM_LAY :\
            x == 6 ? HUMAN_MAGE_ANIM_SPAWN :\
            x == 7 ? HUMAN_MAGE_ANIM_DIE :\
            HUMAN_MAGE_ANIM_EXPULSE \
        )

    #define HUMAN_KNIGHT_3D_MODEL           "human_knight"
    #define HUMAN_KNIGHT_ANIM_IDLE          14 - 1
    #define HUMAN_KNIGHT_ANIM_WALK          76 - 1
    #define HUMAN_KNIGHT_ANIM_PICK          48 - 1
    #define HUMAN_KNIGHT_ANIM_DROP          66 - 1
    #define HUMAN_KNIGHT_ANIM_ECSTASY       23 - 1
    #define HUMAN_KNIGHT_ANIM_LAY           54 - 1
    #define HUMAN_KNIGHT_ANIM_SPAWN         47 - 1
    #define HUMAN_KNIGHT_ANIM_DIE           24 - 1
    #define HUMAN_KNIGHT_ANIM_EXPULSE       68 - 1
    #define HUMAN_KNIGHT_ANIM_NO_ANIMATION  45 - 1
    #define GIVE_HUMAN_KNIGHT_ANIM(x) \
        ( \
            x ==-1 ? HUMAN_KNIGHT_ANIM_NO_ANIMATION:\
            x == 0 ? HUMAN_KNIGHT_ANIM_IDLE :\
            x == 1 ? HUMAN_KNIGHT_ANIM_WALK :\
            x == 2 ? HUMAN_KNIGHT_ANIM_PICK :\
            x == 3 ? HUMAN_KNIGHT_ANIM_DROP :\
            x == 4 ? HUMAN_KNIGHT_ANIM_ECSTASY :\
            x == 5 ? HUMAN_KNIGHT_ANIM_LAY :\
            x == 6 ? HUMAN_KNIGHT_ANIM_SPAWN :\
            x == 7 ? HUMAN_KNIGHT_ANIM_DIE :\
            HUMAN_KNIGHT_ANIM_EXPULSE \
        )

    #define GIVE_ANIM_INDEX_BY_NAME(model, anim_index) \
        ( \
            (model == EGG_3D_MODEL) ? 0 : \
            (model == SKELETON_3D_MODEL) ? GIVE_SKELETON_ANIM(anim_index) : \
            (model == SKELETON_ROGUE_3D_MODEL) ? GIVE_SKELETON_ROGUE_ANIM(anim_index) : \
            (model == SKELETON_MAGE_3D_MODEL) ? GIVE_SKELETON_MAGE_ANIM(anim_index) : \
            (model == SKELETON_KNIGHT_3D_MODEL) ? GIVE_SKELETON_KNIGHT_ANIM(anim_index) : \
            (model == HUMAN_3D_MODEL) ? GIVE_HUMAN_ANIM(anim_index) : \
            (model == HUMAN_ROGUE_3D_MODEL) ? GIVE_HUMAN_ROGUE_ANIM(anim_index) : \
            (model == HUMAN_MAGE_3D_MODEL) ? GIVE_HUMAN_MAGE_ANIM(anim_index) : \
            (model == HUMAN_KNIGHT_3D_MODEL) ? GIVE_HUMAN_KNIGHT_ANIM(anim_index) :\
            0\
        )

    #define GIVE_3D_OBJECT_GLBACTER_MODEL_BY_LEVEL(level) \
        ( \
            (level == 0) ? EGG_3D_MODEL : \
            (level == 1) ? SKELETON_3D_MODEL : \
            (level == 2) ? SKELETON_ROGUE_3D_MODEL : \
            (level == 3) ? SKELETON_MAGE_3D_MODEL : \
            (level == 4) ? SKELETON_KNIGHT_3D_MODEL : \
            (level == 5) ? HUMAN_3D_MODEL : \
            (level == 6) ? HUMAN_ROGUE_3D_MODEL : \
            (level == 7) ? HUMAN_MAGE_3D_MODEL : \
            (level == 8) ? HUMAN_KNIGHT_3D_MODEL : \
            "skeleton"\
        )


    // Calcules pour facilement obetnir une tile spécifique
    #define GET_PLATFORM_POSX(first_posx, x) \
        (\
            first_posx + \
            (float)x * GRID_SIZE + \
            GRID_SIZE / 2.0f + \
            ((x != 0) ? x * GRID_SIZE * 2.0f : 0.0f) \
        )

    #define GET_PLATFORM_POSZ(first_posz, z) \
    (\
        first_posz + \
        (float)z * GRID_SIZE + \
        GRID_SIZE / 2.0f + \
        ((z != 0) ? z * GRID_SIZE * 2.0f : 0.0f)\
    )

    #define CALCULATE_PROGRESS_COLOR(p) \
    ([](float progress) -> Color { \
        progress = Clamp(progress, 0.0f, 1.0f); \
        Color result; \
            if (progress < 0.5f) { \
                float scale = progress * 2.0f; \
                result = (Color){ 255, (unsigned char)Lerp(0.0f, 255.0f, scale), 0, 255 }; \
            } \
            else { \
                float scale = (progress - 0.5f) * 2.0f; \
                result = (Color){ (unsigned char)Lerp(255.0f, 0.0f, scale), 255, 0, 255 }; \
            } \
            return result; \
        } \
    )((p))

    #define DAY_TIME_IN_MY_HOUR 24
    #define MY_HOUR_TIME 2
    #define SUN_RADIUS 50.5
    #define MOON_RADIUS (int)(SUN_RADIUS*1/4)
    #define SUN_DISTANCE_ROTATION(height) (float)(10*height + SUN_RADIUS*1.5)
    #define MOON_DISTANCE_ROTATION(height) (float)((SUN_DISTANCE_ROTATION(height)*3/4) + MOON_RADIUS*1.5)
    #define SUN_INITIAL_POSITION(width, heigth) (Vector3){(float) GET_PLATFORM_POSX(SUN_RADIUS, width), SUN_DISTANCE_ROTATION((width+heigth)/2), (float) GET_PLATFORM_POSZ(SUN_RADIUS, heigth)}
    #define MOON_INITIAL_POSITION(width, heigth) (Vector3){(float) GET_PLATFORM_POSX(MOON_RADIUS, width), MOON_DISTANCE_ROTATION((width+heigth)/2), (float) GET_PLATFORM_POSZ(MOON_RADIUS, heigth)}

    #define GLOBAL_ANIMATION_DURATION 2.5
    #define GLOBAL_FREQ_DEFAULT_VALUE 1.0f
    #define _FREQ_VALUE(actual_frequency) (GLOBAL_FREQ_DEFAULT_VALUE/(FloatEquals(actual_frequency, 0.0f) ? GLOBAL_FREQ_DEFAULT_VALUE : actual_frequency))


    #define TRANSPARENT (Color) {0, 0, 0, 0}
    #define FONT_TEMP_MESSAGE_SIZE 30

    #define FLT_MAX  30.0f


#endif