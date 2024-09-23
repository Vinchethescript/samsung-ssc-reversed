# Samsung SSC Reversed

## Overview
This repository contains a partially reverse-engineered version of the Samsung Scalable/Seamless Codec (SSC) library, which is used in the newest Samsung phones to encode audio for the Galaxy Buds. The purpose of this repository is to facilitate research and exploration of the SSC codec, despite its incomplete and non-functional state in this repository.

I highly suggest you to reverse-engineer this library from scratch, as there may be a lot of errors and mistakes in this one.

## Disclaimer
- __**This repository is for research purposes only.**__
- **Partial and Incomplete**: This repository contains only a partial reverse-engineering of the SSC library. Many functions are missing, and the code may contain numerous warnings and errors.
- **Non-Functional**: The code in this repository is unlikely to compile or work correctly. It serves as a starting point for those interested in further reverse-engineering efforts.
- **Type Errors**: Because I have few-to-no experience with ARM NEON, I couldn't really understand how to correct the ARM NEON code. As a result, the code may not work properly.
- **No Documentation**: There is no documentation available, because I couldn't understand how the encoder works. You can try to understand the code by reading the source code.
- **Comments**: Some code has been commented out because I couldn't correct it.
- **Binary Included**: A binary of the SSC encoder library is included to aid in reverse-engineering.

## License
This repository is provided for research purposes only. All rights to the original SSC library remain with Samsung. The code and binary provided here are for educational and research purposes, and should not be used for any commercial applications unless made by Samsung.
