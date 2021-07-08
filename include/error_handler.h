#pragma once

#define print_error(msg) { Serial.printf("\nError: %s | %s: %d\n\n", msg, __FILE__, __LINE__); }
