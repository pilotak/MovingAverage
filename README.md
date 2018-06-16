# Moving average filter
Moving average buffer filter for Mbed and Arduino

**_Buffer_** type can be:
 - `uint8_t` or `int8_t` with maximum buffer length of **16843009**
 - `uint16_t` or `int16_t` with maximum buffer length of **65537**
 - `uint32_t` or `int32_t` but added number can be as long as 30 bits which eaquals to maximum buffer length of **2**, 29 bits number = max buffer length of **4**, etc.

**_Buffer length_**:
- "binary" length only: 2, 4, 8, 16, 32, 64, 128, etc.

# Mbed example
```cpp
#include "mbed.h"
#include "MovingAverage.h"

 // Buffer (and added samples) will be initialised as uint8_t, total 16 samples
MovingAverage <uint8_t, 16> filter;

int main() {
    printf("result: %u\n", filter.add(255)); // insert new number and get result
    printf("result: %u\n", filter.add(6)); // insert new number and get result
    printf("result: %u\n", filter.add(9)); // insert new number and get result
    printf("result: %u\n", filter.get()); // get last result, without adding a newone

    return 0;
}
```
# Arduino example
```cpp
#include "MovingAverage.h"

 // Buffer (and added samples) will be initialised as uint8_t, total 16 samples
MovingAverage <uint8_t, 16> filter;

void setup(){
    Serial.begin(9600);
    Serial.print("result: ");
    Serial.println(filter.add(255)); // insert new number and get result
    Serial.print("result: ");
    Serial.println(filter.add(6)); // insert new number and get result
    Serial.print("result: ");
    Serial.println(filter.add(9)); // insert new number and get result
    Serial.print("result: ");
    Serial.println(filter.get()); // get last result, without adding a newone
}
void loop(){

}
```

## Output
> result: 255
> 
> result: 239
> 
> result: 224
> 
> result: 224
