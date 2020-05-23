#include "assistant_services.h"

#include <kernel.h>
#include <sys/printk.h>

AssistantServices::AssistantServices()
    : currentActionID(ID_GET_WEATHER_STATUS),
      currentLightState(LightState::Off) {
  printCurrentMenuState();
}

void AssistantServices::interpretVoiceCommand(VoiceCommand command) {
  if (command == VoiceCommand::Left || command == VoiceCommand::Right) {
    switch (command) {
      case VoiceCommand::Left:
        if (currentActionID > 0) {
          --currentActionID;
        }
      case VoiceCommand::Right:
        if (currentActionID < N_ACTIONS - 1) {
          ++currentActionID;
        }
      default:
        break;
    }
    printCurrentMenuState();
    return;
  }

  if (currentActionID == ID_SHOW_CURRENT_TIME && command == VoiceCommand::Go) {
    showCurrentTime();
  } else if (currentActionID == ID_GET_WEATHER_STATUS &&
             command ==
                 VoiceCommand::Yes) {  // temp Yes to see an effect in the UART
                                       // -> should be VoiceCommand:Go
    getWeatherStatus();
  } else if (currentActionID == ID_SET_LIGHT) {
    if (command == VoiceCommand::On) {
      setLight(LightState::On);
    } else if (command == VoiceCommand::Off) {
      setLight(LightState::Off);
    }
  }
}

void AssistantServices::printCurrentMenuState() const {
  printk("Current action: %s\n", actionStr[currentActionID]);
}

void AssistantServices::showCurrentTime() const {
  printk("Current system time: %ds\n", static_cast<int>(k_uptime_get() / 1000));
}

void AssistantServices::getWeatherStatus() const {
  printk("Weather in %s: %s\n", "Wroclaw", "cloudy");
}

char* lightState2Str(LightState state) {
  switch (state) {
    case LightState::On:
      return "on";
    case LightState::Off:
      return "off";
  }
  return "something went wrong";
}

void AssistantServices::setLight(LightState lightState) {
  currentLightState = lightState;
  printk("The light has been turned %s", lightState2Str(currentLightState));
}
