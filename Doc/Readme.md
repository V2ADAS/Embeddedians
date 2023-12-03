# C File Templates

Welcome to the C File Templates repository! Here you will find templates for both `.c` and `.h` files that you can use as a starting point for your embedded C projects. The templates are designed to provide standard structure and a naming conventions, helping you to write clean and organized code.

## Type of Files

| File                       | Description                                                                                                                                      |
| -------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------ |
| `PREFIX_ModuleName.c`      | Implementation file for _ModuleName_. Never add `typedef` or `#define` macros in this file. Use the `PREFIX_ModuleName_int.h` for that instead. |
| `PREFIX_ModuleName.h`      | Public interface. It includes all the _ModuleName_ public declarations.                                                                          |
| `PREFIX_ModuleName_Private.h` | Private header. It includes all the _ModuleName_ private declarations (e.g. configuration macros). 
| `PREFIX_ModuleName_config.h` | public header. It includes all the _ModuleName_ configrations.
                    |

## Naming Conventions & Coding Style

### Prefixes

- The prefix for the module should consist of 2 to 4 capitalized letters that indicate its place within the software architecture.
- Here are some examples that you can use:

  | Prefix  | Description                | Example             |
  | ------- | -------------------------- | ------------------- |
  | **APP** | Application layer          | APP_SystemManager.c |
  | **MCAL**| MCAL Abs Layer             | M_GPIO.h            |
  | **HAL** | Hardware Abstraction Layer | H_STM32L4xx.h       |

### Functions

- Function names should include a prefix as well.
- This should be an uppercase abbreviated version of the module it belongs (2-4 characters).
- Notice that this prefix is different from the ones use to name the module files.

  Example:

  ```c
  /** A function inside the DRV_ADC.c module */
  void ADC_StartConversion(void);
  ```

### Macros

- Macros names should also include a prefix with its module name (2-4 characters) and be declared in uppercase.

  ```c
  #define ADC_CHANNELS_NUMBER  19
  ```

- Avoid using an `_` as prefix for macros since these are usually system-defined or reserved.
- The only exception to this rule is the _inclusion guard macros_ (used to avoid recursive inclusion of header files).

  ```c
  #ifndef ___PREFIX_MODULE_NAME_H
  #define ___PREFIX_MODULE_NAME_H

  /* some code */

  #endif
  ```

### Type definitions

- **Typedef** names should also include the module name prefix and the `_t` suffix.
- This applies for both `enum` and `struct`.

  ```c
  typedef struct
  {
     /* some code */
  } ADC_ChannelConfig_t;
  ```

### Variables



```c
u8 Local_u8BatteryVoltage_uV = 0;

u8 Global_u8BatteryVoltage_uV = 0;
```



### Comments

- Only use the `/** */` sequence for comment blocks. This will be later used by _Doxygen_ for self-documentation.
- Use `/* */` for "on-line" comments. Avoid breaking an "on-line" comment into multiple lines.

  ```c
  /* AVOID THIS */
  uint8_t lMotorCurrent_mA = 0; /* This variable stores the last ADC
  value of the motor current in mA. */

  /* DO THIS*/
  /* This variable stores the last ADC value of the motor current in mA. */
  uint8_t lMotorCurrent_mA = 0;
  ```


