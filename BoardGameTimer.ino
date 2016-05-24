int ledPin = 13;
int sensorPin = A0;

int greenLed = 9;
int redLed = 10;
int blueLed = 11;

int totalPlayers = 4;
float playerTimes[4] = {0, 0, 0, 0};
int currentPlayer = 0;

int resumeOnPlayer = currentPlayer;

bool wasPassing = false;
bool wasPaused = true;
bool wasTiming = false;

int lastPassingSensorValue = 1000;
int maxLight = 0;

int * currentPlayerColor;

void setupOutputs() {
  pinMode(ledPin, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
}

void setup() {
  Serial.begin(9600);
  setupOutputs();

  calibrateLightSensor();
  currentPlayerColor = getColorsForPlayer(currentPlayer);

  Serial.println("STARTING...");
}

void loop() {
  int brightness = getBrightness();

// minLight ---timing---|----passing----|---paused---maxLight

  if (brightness < maxLight * 0.05) {
    //    facedown | players turn
    timingSeq();
  } else if (brightness > maxLight * 0.95) {
    //    faceup | pause
    pausedSeq();
  } else {
     //    passing?
   passingSeq();
  }
  



  
//  if (brightness > maxLight * 0.90) {
//    //    faceup | pause
//    pausedSeq();
////  } else if (!wasPaused && brightness > maxLight * 0.15 && getBrightness() + maxLight * 0.05 > lastPassingSensorValue) {
//  } else if (!wasPaused && brightness > maxLight * 0.30) {
//    //    passing?
//   passingSeq();
//    
//  } else if (!wasTiming && minLight - getBrightness() < maxLight * 0.15) {
//    //    facedown | players turn
//    timingSeq();
//  }

  lastPassingSensorValue = getBrightness();
  Serial.print("current: ");
  Serial.print(getBrightness());
  Serial.print(" max: ");
  Serial.println(maxLight);
}

void timingSeq(){
  Serial.print("Timing ");
    
    if (wasPassing) {
      Serial.println("| New Player");
      nextPlayer();
      currentPlayerColor = getColorsForPlayer(currentPlayer);
      lightPlayerColor(currentPlayerColor);
      resumeOnPlayer = currentPlayer;
    }

    if (wasPaused) {
      Serial.println("| Resume");
//    resume timer  
    }
   
    wasPaused = false;
    wasTiming = true; 
    wasPassing = false;
}

void passingSeq(){
  wasPassing = true;
    wasPaused = false;
    wasTiming = false;
    
    
    rgbOff();
    Serial.println("Passing");
}

void pausedSeq(){
  Serial.println("Paused");
    currentPlayer = resumeOnPlayer;
    wasPaused = true;
    wasPassing = false;
    wasTiming = false;

    flashPlayerColor(currentPlayerColor, 100);
}

