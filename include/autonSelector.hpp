#include "liblvgl/lvgl.h"

// Globals
extern unsigned short int autonSelect;
extern lv_obj_t * menuRectangle;
extern void CreateMenuRectangle();
extern void MenuDropdownCB(lv_event_t * e);
extern void CreateMenuDropdown();

// Auton Menu
extern lv_obj_t * autonScr;
extern lv_obj_t * autonList;

extern void AutonListCB(lv_event_t * e);
extern void CreateAutonList();
extern void OpenAutonSelectMenu();

// Motor Menu
extern lv_obj_t * motorScr;
extern void OpenMotorMenu();
extern lv_obj_t * motorTable;
extern void CreateMotorTable();
extern void UpdateRedColumn(bool showTemp);
extern void UpdateBlueColumn(bool showVelocity);
extern void UpdateYellowColumn(bool showTorque);
extern lv_obj_t * telemetryRect;
extern void CreateTelemetryRectangle();
extern void ButtonMatrixCB(lv_event_t * e);
extern void RedButtonMatrixStyleCB(lv_event_t * e);
extern void BlueButtonMatrixStyleCB(lv_event_t * e);
extern void YellowButtonMatrixStyleCB(lv_event_t * e);
extern const char * RedButtonMap[];
extern const char * BlueButtonMap[];
extern const char * YellowButtonMap[];
extern void CreateTelemetryButtons();

// Sensor Menu
extern lv_obj_t * sensorScr;
extern void OpenSensorMenu();
void CreateBatteryRect();

// Keybind Menu
extern lv_obj_t * keybindScr;
extern void OpenKeybindMenu();

// Notes Menu
extern lv_obj_t * notesScr;
extern void OpenNotesMenu();
extern lv_obj_t * teamSelectRect;
extern void CreateTeamSelectRectangle();