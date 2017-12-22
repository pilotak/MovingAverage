# Moving average filter
Moving average buffer filter for Mbed

**_Buffer_** type can be:
 - `uint8_t` with maximum buffer length of **16843009**
 - `uint16_t` with maximum buffer length of **65537**
 - `uint32_t` but added number can be as long as 31 bits which eaquals to maximum buffer length of **2**, 30bits number = max buffer length of **4**, etc.

**_Buffer length_**:
- "binary" length only: 2, 4, 8, 16, 32, 64, 128, etc.

# Example
```cpp
#include "mbed.h"
#include "MovingAverage.h"

 // Buffer (and added samples) will by initialised as uint8_t, total 16 samples
MovingAverage <uint8_t, 16> filter;

int main() {
    printf("result: %u\n", filter.add(255)); // insert new number and get result
    printf("result: %u\n", filter.add(6)); // insert new number and get result
    printf("result: %u\n", filter.add(9)); // insert new number and get result
    printf("result: %u\n", filter.get()); // get last result, without adding a newone

    return 0;
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
