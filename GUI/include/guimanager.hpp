/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** guimanager.hpp
*/

#ifndef MY_GUIMANAGER_
    #define MY_GUIMANAGER_
    #include "my_include.hpp"
    #include "my_define.hpp"
    #include "struct.hpp"
    #include "message_box.hpp"
    #include "Dashboard.hpp"
    #include "AudioManager.hpp"


//sgt, sst

class GuiManager {
    public:
        GuiManager();
        ~GuiManager();

        // Initialisation
        bool shouldClose();

        // Mises à jour via setters
        void setMapSize(int width, int height); //msz
        void setWinner(std::string winner);
        void setTna(std::string team_name);
        void setBct(std::vector<std::vector<tile_s>> __map);
        void setSgt(float frequency); //sgt
        void setSst(float frequency); //sst

        //updaters
        void updateTile(int x, int y, const elem_s& resources); //bct
        void updatePlayerPosition(int id, int x, int y, orient_e orientation);
        void updatePlayerLevel(int id, int level);
        void updatePlayerRessources(int id, elem_s ressources);
        
        //utility
        void addPlayer(const trantorian_s& player);
        void removePlayer(int id);
        void display_for_a_moment(std::string message, double time, Color message_color, Color box_color,pos_t pos= (pos_t) {0, 0});
        void display_smg(std::string message, double duration, Color message_color, Color box_color);//smg
        
        //animation
        void move_and_slide_animation(int id, pos_t start_pos, pos_t end_pos, orient_e new_orientation);
        bool isPlayerAnimating(int id);
        void makePlayerDie(int id); //edi && pdi
        void makePlayerSpawn(int id); //ebo
        void makePlayerLayEgg(int id); //pfk -> je fais juste l'animation, tu dois faire un addplayer de egg, et faire un makePlayerSpwan
        void makePlayerDrop(int id); //pdr
        void makePlayerPick(int id); //pgt
        void makePlayerBroadCast(int id); //ebo
        void makePlayerToExpulseAnother(int id); //pex
        void makePlayerToIdle(int id); //to become idle
        void makePlayerExtasy(int id); //to Extasy
        void makePlayerStopExtasy(int id); //to stop Ecstasy
        
        //run the loop
        void UpdateAndDrawFrame();
        
        //for eggs ...
        void makeEggSpawn(int id); //ebo
        void makeEggDie(int id); //edi && pdi
        void addEggPlayer(const trantorian_s& player);
        void removeEggPlayer(int id);
        
        
        
        private:
        // Données internes
    int _width = 0;
    int _height = 0;
    std::vector<std::vector<tile_s>> _map;
    std::map<int, trantorian_s> _players;
    std::map<int, trantorian_s> _eggs;
    float _hour = 6;
    float _currentTime = 0.0f;
    float _levitateTime = 0.0f;
    float _shaderChangingTime = 0.0f;
    std::string _winner;
    bool floor_changed_size = false;
    Loading_bar loadingBar;
    std::set <std::string> _teams;
    float _skyRotation = 0.0f;
    bool _cursor = false;
    std::map<std::string, Color> _teamColors;
    float _frequency = 100.0f;
    bool _isFreqInputActive;      // Le panneau de saisie est-il ouvert ?
    char _freqInputBuffer[16];    // Buffer pour stocker le texte de la fréquence
    int _freqInputCharCount;

    bool _isTileSelected = false;  
    pos_t _selectedTilePos = {0, 0};
    
    
    // Raylib configurations and floor models
    int perlinNoiseMapLoc = 0;
    Camera3D _camera;
    CameraMode camMode;
    Model model_floor;
    Mesh mesh_floor;
    Model _ressources_models[7];
    Model _model_platforms_1;
    Model _model_platforms_2;
    Model _model_platforms_3;
    Model _model_platforms_4;
    Model _model_platforms_5;
    Model _model_platforms_6;
    Model _model_platforms_7;
    Model _model_platforms_8;
    Model _model_platforms_9;
    Model _model_platforms_10;
    Model _model_bridge;
    Model _model_portal;
    // Model _auraModel;
    
    //shaders for water
    Shader water_shader;
    Image water_perlinNoiseImage;
    Texture water_perlinNoiseMap;
    int value_environmentMap{ MATERIAL_MAP_CUBEMAP };
    int value_environmentMap2{ MATERIAL_MAP_CUBEMAP};
    int _vflipped { 0 };
    int value_dogamma { 0 };
    
    //shaders for skyboxes
    Mesh skybox_cube;
    Model skybox;
    Shader shdrCubemap;
    Texture skyboxTextureDay;
    Texture skyboxTextureDayBlue;
    Texture skyboxTextureDaySunSet;
    Texture skyboxTextureNight;
    Texture skyboxTextureNightPurple;
    Texture skyboxTextureNightSkySky;
    
    //shaders for lights
    Shader light_shader;
    int _sunLightIndex = 0;
    int _moonLightIndex = 1;
    
    //characters
    Model _model_egg;
    Model _char_level1;
    Model _char_level2;
    Model _char_level3;
    Model _char_level4;
    Model _char_level5;
    Model _char_level6;
    Model _char_level7;
    Model _char_level8;
    
    //animations counts and animations containers
    int _animation_level0_count = 0;
    ModelAnimation *_animation_level0;
    int _animation_level1_count = 0;
    ModelAnimation *_animation_level1;
    int _animation_level2_count = 0;
    ModelAnimation *_animation_level2;
    int _animation_level3_count = 0;
    ModelAnimation *_animation_level3;
    int _animation_level4_count = 0;
    ModelAnimation *_animation_level4;
    int _animation_level5_count = 0;
    ModelAnimation *_animation_level5;
    int _animation_level6_count = 0;
    ModelAnimation *_animation_level6;
    int _animation_level7_count = 0;
    ModelAnimation *_animation_level7;
    int _animation_level8_count = 0;
    ModelAnimation *_animation_level8;
    
    std::deque<std::deque<FloorModel>> _platforms;
    
    struct TempMessage {
        std::string text;
        double duration = 0;
        double startTime = 0;
        Color color= TRANSPARENT;
        Color boxColor= TRANSPARENT; 
        pos_t pos = (pos_t) {0, 0};
        // int width = 0;
        // int heigth = 0;
    };
    
    std::vector<TempMessage> _tempMessages;
    
    Font tempMessagesFont;
    
    Dashboard _dashboard;
    int _followedPlayerId = -1;

    //audio
    AudioManager _audioManager;
    
    
    
    
    // Méthodes
    void initFloor();
    void init3DCharacters();
    void initShader();
    void initFloorModels();
    void initWindow();
    
    
    //drawers
    void drawScene();
    void drawFloor();
    void drawShader();
    void drawLights();
    void drawShaderSkybox();
    void drawTile(const tile_s& tile, int x, int y);
    void drawPlayer(trantorian_s& player, Vector3 offset);
    void drawIncantationEffect(Vector3 pos, float progress);
    void drawPlayerAura(trantorian_s& player);
    void drawTempMessages();
    void drawInfoPanel(const std::string& title, const std::string& content, Vector2 position);
    void drawHelpBox(const std::string& message, bool change_pos = false);
    void drawDashBoard();
    void drawSelectedTileInfo();

    
    //private updates
    void updateSkyRotation(float deltaTime);
    void updateFloor();
    void updateShader();
    
    enum GameState {
        STATE_LOADING,
        STATE_PLAYING
    };
    GameState _gameState;
    int _loadingStage;
    std::vector<std::string> _gameTips;
    void UpdateAndDrawLoadingScreen();
    void UpdateAndDrawPlayingScreen();
    
    //private utility
    bool isPlayerInView(Vector3& playerPos);
    void handleInput();
    void update();
    void render();
    void startRunGameLoop();
    void stopRunGameLoop();
    void handleFrequencyInput();

    //givers
    Model getPlayerModelByLevel(int level);
    float getPlayerRotationAngle(orient_e orientation);

};
#endif