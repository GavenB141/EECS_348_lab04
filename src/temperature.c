#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef enum {
  Celsius = 1,
  Fahrenheit = 2,
  Kelvin = 3
} TemperatureScale;

float celsius_to_fahrenheit (float celsius) {
  return (9.0/5.0) * celsius + 32.0;
}

float fahrenheit_to_celsius (float fahrenheit) {
  return (5.0/9.0) * (fahrenheit - 32.0);
}

float celsius_to_kelvin (float celsius) {
  return celsius + 273.15;
}

float kelvin_to_celsius (float kelvin) {
  return kelvin - 273.15;
}

float fahrenheit_to_kelvin (float fahrenheit) {
  return celsius_to_kelvin(fahrenheit_to_celsius(fahrenheit));
}

float kelvin_to_fahrenheit (float kelvin) {
  return celsius_to_fahrenheit(kelvin_to_celsius(kelvin));
}

/**
 * Convert a temperature value to another scale.
 * 
 * @param value The temperature value to convert
 * @param from The temperature scale of the input value 
 * @param to The temperature scale to convert to 
 * @return The converted value 
 */
float convert_temperature (
  float value, 
  TemperatureScale from, 
  TemperatureScale to
) {
  switch (from) {
    case Celsius: {
      switch (to) {
        case Fahrenheit: return celsius_to_fahrenheit(value);
        case Kelvin: return celsius_to_kelvin(value);
        default: return value;
      }
    }
    case Fahrenheit: {
      switch (to) {
        case Celsius: return fahrenheit_to_celsius(value);
        case Kelvin: return fahrenheit_to_kelvin(value);
        default: return value;
      }
    }
    case Kelvin: {
      switch (to) {
        case Celsius: return kelvin_to_celsius(value);
        case Fahrenheit: return kelvin_to_fahrenheit(value);
        default: return value;
      }
    }
  }
}

/**
 * Prompt the user to enter 1, 2, or 3 
 * corresponding to Celsius, Fahrenheit or Kelvin.
 * 
 * @param prompt The prompt string to display.
 */ 
TemperatureScale get_temp_scale(char * prompt) {
  static char buf[8];
  static char * end;

  // Loop until valid input has been ensured
  for (;;) {
    printf("%s", prompt);
    fgets(buf, sizeof(buf), stdin);

    int recieved = (int)strtol(buf, &end, 10);
    
    if (*end != '\n' || end == buf || recieved < 1 || recieved > 3) {
      printf("Please enter 1, 2, or 3.\n");
      continue;
    }

    return recieved;
  }
}

/**
 * Prompt the user to enter a float value until a valid one is recieved.
 * 
 * @param prompt The prompt string to display. 
 */ 
float get_float_input(char * prompt) {
  static char buf[8];
  static char * end;

  // Loop until valid input has been ensured
  for (;;) {
    printf("%s", prompt);
    fgets(buf, sizeof(buf), stdin);

    float recieved = strtof(buf, &end);

    if (*end != '\n' || end == buf) {
      printf("Please enter a valid decimal value.\n");
      continue;
    }

    return recieved;
  }
}

/**
 * Print a weather advisory based on a recieved temperature value. 
 * 
 * @param celsius the temperature value in celsius.
 */
void categorize_temperature(float celsius) {
  char * category;
  char * advisory;

  if (celsius < 0) {
    category = "Freezing";
    advisory = "Stay indoors.";
  } else if (celsius < 10) {
    category = "Cold";
    advisory = "Wear a jacket.";
  } else if (celsius < 25) {
    category = "Comfortable";
    advisory = "You should feel comfortable.";
  } else if (celsius < 35) {
    category = "Hot";
    advisory = "Dress light.";
  } else {
    category = "Extreme Heat";
    advisory = "Keep yourself cool.";
  }

  printf("Temperature category: %s\n", category);
  printf("Weather advisory: %s\n", advisory);
}

int main () {
  float value;
  TemperatureScale current, target;

  // Loop until valid input has been ensured
  for (;;) {
    // Get temperature value
    value = get_float_input("\nEnter the temperature: ");

    // Get current scale
    current = get_temp_scale(
      "Choose the current scale (1) Celsius, (2) Fahrenheit, (3) Kelvin: "
    );

    // Block negative Kelvin inputs
    if (current == Kelvin && value < 0) {
      printf("Kelvin temperatures cannot be negative. Please try again.\n");
      continue;
    }

    // Get conversion target
    target = get_temp_scale(
      "Convert to (1) Celsius, (2) Fahrenheit, (3) Kelvin: "
    );

    // Ensure different conversion target from current scale
    if (current == target) {
      printf("Please try again and select a different scale to convert to.\n");
      continue;
    }

    break;
  }

  // Convert and display
  float converted = convert_temperature(value, current, target);
  printf(
    "\nConverted temperature: %.2f %s\n", 
    converted,
    target == Celsius ? "C" : target == Kelvin ? "K" : "F"
  );

  // Print advisory
  float celsius = convert_temperature(value, current, Celsius);
  categorize_temperature(celsius);
  
  return 0;
}
