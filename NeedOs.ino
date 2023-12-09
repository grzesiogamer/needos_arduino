int ResetPin = 4;
const int ledPin = 13;
const char *password = "needadmin"; // hasło
/*
Jeżeli chcesz zmienić hasło zjedz do funkcji sprawdzHaslo() i zmień bufor na dlugość hasła + 1
Pamiętając aby zmienić tu hasło

*/

bool isAuthenticated = false;

void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Loading...");
  delay(500);
  Serial.println("NeedOS - By BatteryGamer and Blackneeed");
  delay(100);
  Serial.println(char(169) + "Copyright 2023 - BatteryGamer, all Copyrights restricted");
  delay(1000);
  Serial.println("Loading complete...");
  Serial.print()"\n");
  Serial.print("Enter your password: ");

  digitalWrite(ResetPin, HIGH);
  pinMode(ResetPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (!isAuthenticated) {
    isAuthenticated = sprawdzHaslo(); // Sprawdź hasło tylko jeśli nie jesteśmy uwierzytelnieni
  } else {
    if (Serial.available() > 0) {
      String command = Serial.readStringUntil('\n');
      

      if (command == "flash") {
        // Kod obsługujący polecenie flash
        int flashSize = 32 * 1024; // Przykładowa operacja
        Serial.print("Dostępna pamięć flash: ");
        Serial.print(flashSize / 1024); // Konwersja na kilobajty
        Serial.println(" KB");
        Serial.println("\n");
      } else if (command == "reboot" or command == "reset" or command == "restart") {
        // Kod obsługujący polecenie reboot + reset + restart
        Serial.println("\n");
        Serial.println("Restartowanie Arduino...");
        delay(1000);
        digitalWrite(ResetPin, LOW);
        Serial.println("\n");
      } else if (command == "clr" or command == "cls") {
        // Kod obsługujący polecenie clr + cls
        Serial.println("\n");
        Serial.println("\n");
        Serial.println("\n");
      } else if (command == "readme") {
        // Kod obsługujący polecenie readme
        Serial.println("\n");
        Serial.println("NeedOS - New Operating System for your Arduino");
        Serial.println("Version 2023.12");
        Serial.println("Changelog:");
        Serial.println("-- Fixed Bugs");
        Serial.println("-- Adding VGA Support - In progress");
        Serial.println("-- Added new commands");
        Serial.println("-- Support: Arduino UNO only supported at the moment");
        Serial.println("-- Added LoginManager");
        Serial.println("\n");
      } else if (command == "help") {
        // Kod obsługujący polecenie help
        Serial.println("\n");
        Serial.println("Available Commands:");
        Serial.println("help - Display available commands");
        Serial.println("reboot - Restart the system");
        Serial.println("info - Display system information");
        Serial.println("credits - Display credits");
        Serial.println("readme - Display readme");
        Serial.println("flash - Display memory informations");
        Serial.println("\n");
      } else if (command == "info") {
        // Kod obsługujący polecenie info
        Serial.println("\n");
        Serial.println("System Information:");
        Serial.println("Version - 2023.12");
        Serial.println("\n");
      } else if (command == "credits") {
        // Kod obsługujący polecenie credits
        Serial.println("\n");
        Serial.println("Credits:");
        Serial.println("Developed by: BatteryGamer and Blackneeed");
        Serial.println("\n");
      } else {
        Serial.println("\n");
        Serial.println("Unknown command. Type \"help\" for available commands.");
        Serial.println("\n");
      }
    }
  }
}

bool sprawdzHaslo() {
  static char bufor[10]; // Zmienione na długość hasła "needadmin" + 1
  static byte index = 0;

  while (Serial.available() > 0) {
    char incomingChar = Serial.read();

    if (incomingChar == '\n' || incomingChar == '\r') {
      bufor[index] = '\0';
      index = 0;

      if (strcmp(bufor, password) == 0) {
        Serial.println("LoginManager: Password correct, Access granted.");
        digitalWrite(ledPin, HIGH); // Włącz diodę LED
        delay(500);
        digitalWrite(ledPin, LOW); // Włącz diodę LED
        Serial.println("Type \"help\" for more informations.");
        return true;
      } else {
        Serial.println("LoginManager: Incorrect password, please");
        Serial.println("try to enter the correct details again.");
      }
    } else {
      if (index < 9) {
        bufor[index] = incomingChar;
        index++;
      }
    }
  }

  return false;
}
