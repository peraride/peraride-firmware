char url[256];
char body[256];

boolean dockUnlock(uint8_t dockId) {

  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;

    sprintf(url, "http://peraride-api.herokuapp.com/api/auth/dock/unlock?dock_id=%d.%d", 1111, dockId);

    if (http.begin(client, url)) {
      http.addHeader("Content-Type", "application/json");
      //http.addHeader("Authorization: Bearer", "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiI1ZTVmYmFkMDRmOTAyNDAwMDQ3NWY1Y2QiLCJpYXQiOjE1ODM5MDcwNDN9.Wgbj3o-rAazSYYzTkm9y6iMK1mk0MIwXkcaTzFEJ7hc");

      int httpCode = http.GET();

      if (httpCode > 0) {
        Serial.printf("GET - %d\n", httpCode);

        if (httpCode == 406) {
          Serial.println("Not accepted");
          // Not accepted
          // {"message": "Access Denied"}

          return false;

        } else if (httpCode ==  404) {
          Serial.println("Dock is empty");
          // Dock is empty
          // { "message": "Dock is Empty !", "extra": null,"errors": {"name": "APIError", "message": "Dock is Empty !","status": 404, "extra": null}}
          return false;

        } else if (httpCode == 202) {
          Serial.println("Access granted");
          // Access granted
          // {"message": "Access Granted"}
          return true;

        } else {
          // Unknown
          return false;
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        return false;
      }
      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
      ESP.restart();
      return false;
    }
  }
  return false;
}

boolean dockLock(uint8_t dockId, char* rfidCode) {

  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;

    sprintf(url, "http://peraride-api.herokuapp.com/api/auth/dock/lock");
    sprintf(body, "{\"dock_id\": \"%s.%d\",\"rfid_code\": \"%s\"}", STATION_ID, dockId, rfidCode);

    Serial.printf(">> %s >\n\t%s\n", url, body);

    if (http.begin(client, url)) {  // HTTP
      http.addHeader("Content-Type", "application/json");
      //http.addHeader("Authorization: Bearer", "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiI1ZTVmYmFkMDRmOTAyNDAwMDQ3NWY1Y2QiLCJpYXQiOjE1ODM5MDcwNDN9.Wgbj3o-rAazSYYzTkm9y6iMK1mk0MIwXkcaTzFEJ7hc");

      int httpCode = http.POST(body);

      if (httpCode > 0) {
        Serial.printf("POST - %d\n", httpCode);

        if (httpCode == 404) {
          // "message": "No User associated with user_id null",
          return false;

        } else if (httpCode == 200) {
          // {"message": "Bike Locked Successfully"}
          return true;

        } else {
          // Unknown
          return false;
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        return false;
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
      ESP.restart();
      return false;
    }
  }
  return false;
}
