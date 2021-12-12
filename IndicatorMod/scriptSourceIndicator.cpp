/*
	EN: CREATED BY PAULO HENRIQUE KAVA DE SOUZA - PHK 2015 APRIL 28
	THIS MOD IS IN THE ALPHA STAGE AND DON'T REPRESENT THE MOD IN THE LAST STAGE.
	CREATED USING ALEXANDER BLADE'S CODE
	ONLY FOR GTA V.

	BRAZIL 2015

	PT-BR: CRIADO POR PAULO HENRIQUE KAVA DE SOUZA - PHK 28 DE ABRIL DE 2015
	ESTE MOD ESTA EM SUA FASE ALPHA E NAO REPRESENTA O MOD EM ULTIMO ESTAGIO.
	CRIADO USANDO CODIGO DE ALEXANDER BLADE.
	SOMENTE PARA GTA V.

	BRASIL 2015

*/

#include "scriptSourceIndicator.h"

#include <string>
#include <ctime>

#pragma warning(disable : 4244 4305) 


// KEYS AREA - START
bool get_key_pressed(int nVirtKey) {
	return (GetAsyncKeyState(nVirtKey) & 0x8000) != 0;
}

DWORD trainerResetTime = 0;

bool key_pressed(Any key) {
	return (GetTickCount() > trainerResetTime + 1000) && get_key_pressed(key);
}

void reset_key_switch() {
	trainerResetTime = GetTickCount();
}
// KEYS AREA - END
// GRAPH AREA - START
std::string statusText;
DWORD statusTextDrawTicksMax;
bool statusTextGxtEntry;

void update_status_text() {
	if (GetTickCount() < statusTextDrawTicksMax) {
		UI::SET_TEXT_FONT(0);
		UI::SET_TEXT_SCALE(0.55, 0.55);
		UI::SET_TEXT_COLOUR(255, 255, 255, 255);
		UI::SET_TEXT_WRAP(0.0, 1.0);
		UI::SET_TEXT_CENTRE(1);
		UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
		if (statusTextGxtEntry) {
			UI::_SET_TEXT_ENTRY((char *)statusText.c_str());
		}
		else {
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING((char *)statusText.c_str());
		}
		UI::_DRAW_TEXT(0.5, 0.5);
	}
}

void set_status_text(std::string str, DWORD time = 2500, bool isGxtEntry = false) {
	statusText = str;
	statusTextDrawTicksMax = GetTickCount() + time;
	statusTextGxtEntry = isGxtEntry;
}

void update_features() {
	update_status_text();
}
// GRAPH AREA - END

// VARIABLES
Any keyActiveMod = VK_F5;
Any keyAlert = VK_F6;
Any keyLeft = VK_F7;
Any keyRight = VK_F8;
Any desativa = VK_F9;
LPCSTR versao = "0.01 ALPHA";

bool scriptStarted = false;
bool alertStarted = false;
bool leftStarted = false, rightStarted = false;

void deactivateAllIndicators() {
	

	if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
		//VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), false, false);

		VEHICLE::SET_VEHICLE_FIXED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
		VEHICLE::SET_VEHICLE_ALARM(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true);
		VEHICLE::START_VEHICLE_ALARM(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
		

		DWORD time = GetTickCount() + 1000;
		while (GetTickCount() < time) {
			char text[256];
			sprintf_s(text, "-= FALSE FALSE =-");
			set_status_text(text);
			update_features();
			WAIT(0);
		}
	}
}

void reconheceTeclas() {
	if (scriptStarted == true) {
		if (key_pressed(keyAlert) && alertStarted == false) {
			deactivateAllIndicators();
			alertStarted = true;

			if(ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
				VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true, true);
				VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), false, true);

				DWORD time = GetTickCount() + 1000;
				while (GetTickCount() < time) {
					char text[256];
					sprintf_s(text, "-= [F5] TRUE TRUE (ALERTA) =-");
					set_status_text(text);
					update_features();
					WAIT(0);
				}
			}
		} else if (key_pressed(keyAlert) && alertStarted == true) {
			alertStarted = false;
			deactivateAllIndicators();
		} else if (key_pressed(keyLeft) && leftStarted == false) {
			deactivateAllIndicators();
			leftStarted = true;

			if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
				VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true, false);

				DWORD time = GetTickCount() + 1000;
				while (GetTickCount() < time) {
					char text[256];
					sprintf_s(text, "-= [F6] TRUE TRUE (ESQUERDA) =-");
					set_status_text(text);
					update_features();
					WAIT(0);
				}
			}
		} else if (key_pressed(keyLeft) && leftStarted == true) {
			leftStarted = false;
			deactivateAllIndicators();
		} else if (key_pressed(keyRight) && rightStarted == false) {
			deactivateAllIndicators();
			rightStarted = true;

			if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
				VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), false, true);

				DWORD time = GetTickCount() + 1000;
				while (GetTickCount() < time) {
					char text[256];
					sprintf_s(text, "-= [F7] FALSE TRUE (DIREITA) =-");
					set_status_text(text);
					update_features();
					WAIT(0);
				}
			}
		}
		else if (key_pressed(keyRight) && rightStarted == true) {
			rightStarted = false;
			deactivateAllIndicators();
		}
		else if (key_pressed(desativa)) {
			deactivateAllIndicators();
		}

	}
}

void main() {
	while (true) {
		reconheceTeclas();
		if (key_pressed(keyActiveMod) && scriptStarted == false) {
			scriptStarted = true;

			reset_key_switch();


			DWORD time = GetTickCount() + 1000;
			while (GetTickCount() < time) {
				char text[256];
				sprintf_s(text, "-= INDICATOR MOD ACTIVATED [v %s] =-", versao);
				set_status_text(text);
				update_features();
				WAIT(0);
			}
			reset_key_switch();
		} else if (key_pressed(keyActiveMod) && scriptStarted == true) {
			scriptStarted = false;
			deactivateAllIndicators();

			reset_key_switch();

			DWORD time = GetTickCount() + 1000;
			while (GetTickCount() < time) {
				char text[256];
				sprintf_s(text, "-= INDICATOR MOD DEACTIVATED [THANKS] =-");
				set_status_text(text);
				update_features();
				WAIT(0);
			}
			reset_key_switch();
		}
		update_features();

		WAIT(0);
	}
}

void ScriptMain() {
	srand(GetTickCount());
	main();
}
