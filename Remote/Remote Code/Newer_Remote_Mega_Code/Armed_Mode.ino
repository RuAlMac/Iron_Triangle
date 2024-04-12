void runArmedRemote() {
  if (inputKey) {
    run_basic_ui_navigation();
  }

  if (activeSettingPage == 33) { //Remote main menu armed
    if (inputKey) {
      switch (inputKey) {
        case '1':
          activeSetting(35);
          waitForNoPress();
          break;
      }
    }
  }

  if (activeSettingPage == 35){ //Disarm system - alarm not triggered
    runInputPinFeature();
  }

  /*if (/*alarm tripped){
    activeSetting(36);
  }*/

  if (activeSettingPage == 36){
    /*show countdown until alarm, controlled by Sentry*/
  }
}
