#ifndef ASSISTANT_SERVICES_H
#define ASSISTANT_SERVICES_H

enum class VoiceCommand {
  Yes,
  No,
  Up,
  Down,
  Left,
  Right,
  On,
  Off,
  Stop,
  Go
};

enum class LightState {
  On,
  Off
};

class AssistantServices {
 public:
  AssistantServices();
  void interpretVoiceCommand(VoiceCommand command);

 private:
  const static int N_ACTIONS = 3;
  const static int ID_SHOW_CURRENT_TIME = 0;
  const static int ID_GET_WEATHER_STATUS = 1;
  const static int ID_SET_LIGHT = 2;
  char actionStr[N_ACTIONS][100] = {
    "Show current time", "Get weather status", "Set light"
  };

  void showCurrentTime() const;
  void getWeatherStatus() const;
  void setLight(LightState lightState);
  void printCurrentMenuState() const;

  int currentActionID;
  LightState currentLightState;
};

#endif  // ASSISTANT_SERVICES_H