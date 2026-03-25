  #include <Chrono.h> //external library ito na ginamit natin para mapadali ang code ng mga timer na need natin para sa project

  //ito yung mga pins na ginamit natin, pins para sa LED, Buttons at Buzzer
  #define LED_DRIVER 12
  #define LED_STOP 13
  #define LED_1 11
  #define LED_2 10
  #define LED_3 9
  #define LED_4 8
  #define PASS_BUTTON_STOP 3
  #define PASS_BUTTON_1 4
  #define PASS_BUTTON_2 5
  #define PASS_BUTTON_3 6
  #define PASS_BUTTON_4 7
  #define DRIVER_BUTTON_STOP A4
  #define DRIVER_BUTTON_1 A3
  #define DRIVER_BUTTON_2 A2
  #define DRIVER_BUTTON_3 A1
  #define DRIVER_BUTTON_4 A0

  //dito natin sinasabi kung meron sa station or wala, true kung meron, tas false ay wala, initial value natin ay wala
  bool station1 = false;
  bool station2 = false;
  bool station3 = false;
  bool station4 = false;

  Chrono stopChrono; //dito natin ginamit yung external library na chrono, bali yung timer na ito ay gagamitin natin para sa bili ng blink ng stop at buzzer natin 
  int stopLedCnt = 0; //para malaman kung ilan beses pa dapat mag blink ang LED at buzzer para sa stop 
  bool isStopOn = false; //para malaman kung naka ON or OFF yung LED at buzzer natin sa stop
  bool isPassPress = false; //para malaman kung napress ang stop sa passenger

  void setup() { //ito function na ito una ginagawa ni arduino pagkabuhay tas isang beses lang niya gagawin.
    //lahat ng LED ay gagawin natin as OUTPUT yung config natin sa pin
    pinMode(LED_DRIVER, OUTPUT);
    pinMode(LED_STOP, OUTPUT);
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);
    pinMode(LED_3, OUTPUT);
    pinMode(LED_4, OUTPUT);
    
    //lahat ng button ay gagawin natin INPUT_PULLUP yung config natin sa pin, PULLUP lagi ginagamit pag switch siya na two pins lang, para ok yung signal
    pinMode(PASS_BUTTON_STOP, INPUT_PULLUP);
    pinMode(PASS_BUTTON_1, INPUT_PULLUP);
    pinMode(PASS_BUTTON_2, INPUT_PULLUP);
    pinMode(PASS_BUTTON_3, INPUT_PULLUP);
    pinMode(PASS_BUTTON_4, INPUT_PULLUP);
    pinMode(DRIVER_BUTTON_STOP, INPUT_PULLUP);
    pinMode(DRIVER_BUTTON_1, INPUT_PULLUP);
    pinMode(DRIVER_BUTTON_2, INPUT_PULLUP);
    pinMode(DRIVER_BUTTON_3, INPUT_PULLUP);
    pinMode(DRIVER_BUTTON_4, INPUT_PULLUP);
  }

  void loop() { //ito function na ito ang gagawin ni arduino after matapos yung void setup(), tas paulit ulit niya ito gagawin hanggang buhay si arduino
    //pag napindot yung stop(reset) button sa driver, papatayin lahat ng ilaw at balik sa wala na pagbiblink yung buzzer at led stop
    if (isDriverStop()) { 
      allOff();
      stopLedCnt = 0;
    }
    //pag napindot yung stop sa passenger ay gagawin natin yung variable na isPassPress as true
    if (isPassStop()) {//pag napindot yung
      isPassPress = true;
    }
    //pag napindot ang stop sa passenger or
    //pag napindot station1 sa driver na bukas ang LED ng station 1 or
    //pag napindot station2 sa driver na bukas ang LED ng station 2 or
    //pag napindot station3 sa driver na bukas ang LED ng station 3 or
    //pag napindot station4 sa driver na bukas ang LED ng station 4 or
    //kahit ano sa condition na yun, natin gagawin ay ang mabiblink ng 10 times yung stop(on and off ay consider as 2 count)
    //tas papatayin yung led doon sa napindot na button
    if (isPassStop() || (station1 && isDriver1()) || (station2 && isDriver2()) || (station3 && isDriver3()) || (station4 && isDriver4())) {
      stopLedCnt = 10;
      if (isDriver1()) {
        led1Off();
      }

      if (isDriver2()) {
        led2Off();
      }
      if (isDriver3()) {
        led3Off();
      }

      if (isDriver4()) {
        led4Off();
      }
    }

    //pag napindot yung pass1 button mabubuhay yung LED1 natin sa driver
    if (isPass1()) {
      led1On();
    }
    //pag napindot yung pass2 button mabubuhay yung LED2 natin sa driver
    if (isPass2()) {
      led2On();
    }
    //pag napindot yung pass3 button mabubuhay yung LED3 natin sa driver
    if (isPass3()) {
      led3On();
    }
    //pag napindot yung pass4 button mabubuhay yung LED4 natin sa driver
    if (isPass4()) {
      led4On();
    }

    //ito function natin sa blinking ng stop
    //pag more than 0 ang stopLedCnt, babaguhin natin state ng stop LED at buzzer, from ON to OFF or OFF to ON for every 300millisecond
    //kada change natin ng state, minus 1 tayo sa stopLedCnt
    //pag equal to 0 ang stopLedCnt patayin na natin si Stop LED at buzzer
    if (stopLedCnt > 0) {
      if (stopChrono.hasPassed(300)) {
        stopChrono.restart();
        --stopLedCnt;
        if (isStopOn) {
          ledStopOff();
          if (isPassPress)
            ledDriverOff();
        } else {
          ledStopOn();
          if (isPassPress)
            ledDriverOn();
        }
      }
    } else {
      ledStopOff();
      ledDriverOff();
      isPassPress = false;
    }
  }


  //mga function sa baba ay ginawa ko para yun na lang icacall ko sa void loop at para masmabilis maintindihan
  //ito ay para patayin lang lahat ng LED
  void allOff() {
    ledDriverOff();
    ledStopOff();
    led1Off();
    led2Off();
    led3Off();
    led4Off();
  }

  //ito ay para iON yung LED sa driver stop
  void ledDriverOn() {
    digitalWrite(LED_DRIVER, HIGH);
  }
  //ito ay para iOFF yung LED sa driver stop
  void ledDriverOff() {
    digitalWrite(LED_DRIVER, LOW);
  }
  //ito ay para iON yung LED sa passenger stop
  void ledStopOn() {
    digitalWrite(LED_STOP, HIGH);
    isStopOn = true;
  }
  //ito ay para iOFF yung LED sa passenger stop
  void ledStopOff() {
    digitalWrite(LED_STOP, LOW);
    isStopOn = false;
  }
  //ito ay para iON yung LED sa station1
  void led1On() {
    digitalWrite(LED_1, HIGH);
    station1 = true;
  }
  //ito ay para iOFF yung LED sa station1
  void led1Off() {
    digitalWrite(LED_1, LOW);
    station1 = false;
  }
  //ito ay para iON yung LED sa station2
  void led2On() {
    digitalWrite(LED_2, HIGH);
    station2 = true;
  }
  //ito ay para iOFF yung LED sa station2
  void led2Off() {
    digitalWrite(LED_2, LOW);
    station2 = false;
  }
  //ito ay para iON yung LED sa station3
  void led3On() {
    digitalWrite(LED_3, HIGH);
    station3 = true;
  }
  //ito ay para iOFF yung LED sa station3
  void led3Off() {
    digitalWrite(LED_3, LOW);
    station3 = false;
  }

  //ito ay para iON yung LED sa station4
  void led4On() {
    digitalWrite(LED_4, HIGH);
    station4 = true;
  }
  //ito ay para iOFF yung LED sa station4
  void led4Off() {
    digitalWrite(LED_4, LOW);
    station4 = false;
  }
  //ito para malaman kung napress ang stop sa pasengger, value niya ay true pag napress tas false pag hindi
  bool isPassStop() {
    return !digitalRead(PASS_BUTTON_STOP);
  }
  //ito para malaman kung napress ang station1, value niya ay true pag napress tas false pag hindi
  bool isPass1() {
    return !digitalRead(PASS_BUTTON_1);
  }
  //ito para malaman kung napress ang station2, value niya ay true pag napress tas false pag hindi
  bool isPass2() {
    return !digitalRead(PASS_BUTTON_2);
  }
  //ito para malaman kung napress ang station3, value niya ay true pag napress tas false pag hindi
  bool isPass3() {
    return !digitalRead(PASS_BUTTON_3);
  }
  //ito para malaman kung napress ang station4, value niya ay true pag napress tas false pag hindi
  bool isPass4() {
    return !digitalRead(PASS_BUTTON_4);
  }
  //ito para malaman kung napress ang stop sa driver, value niya ay true pag napress tas false pag hindi
  bool isDriverStop() {
    return !digitalRead(DRIVER_BUTTON_STOP);
  }
  //ito para malaman kung napress ang station1 sa driver, value niya ay true pag napress tas false pag hindi
  bool isDriver1() {
    return !digitalRead(DRIVER_BUTTON_1);
  }
  //ito para malaman kung napress ang station2 sa driver, value niya ay true pag napress tas false pag hindi
  bool isDriver2() {
    return !digitalRead(DRIVER_BUTTON_2);
  }
  //ito para malaman kung napress ang station3 sa driver, value niya ay true pag napress tas false pag hindi
  bool isDriver3() {
    return !digitalRead(DRIVER_BUTTON_3);
  }
  //ito para malaman kung napress ang station4 sa driver, value niya ay true pag napress tas false pag hindi
  bool isDriver4() {
    return !digitalRead(DRIVER_BUTTON_4);
  }
