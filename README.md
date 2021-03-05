# BoccaDellaVerita

_Program for toy with Bocca della Verità appearance_

This is the link in youtube about how it works:  https://youtu.be/Nd6taGteSHY

This is a Thingeverse repository: https://www.thingiverse.com/thing:4783896

## What is...
This devide turn on its red eyes and play a sound file when a RFID is introduced in his mouth.... This is becuase processor like Atmega328P in Arduino device. 

## Instructions...

```
First to print the model. There is a specific part for RFID and SD card reader fixed with screws.
Make holes (eyes, mouth and speakers)
Include components, according to images RFID 522, processor like Arduino UNO, SD reader, 2cm diam. speaker, LEDs and etc..
Connections according to electronic diagram.
The device program is a bocca.ino file and you can modify it with your RFIDs and your voice records stored on the SD card.
Different voice / music files are played with each RFID. The sound file is WAV PCM 8bits 48Khz.
It has been tested on 8Gb and 16Gb SD cards and works fine. However, on an old 16Mb card, the result was not correct.
```

## In bocca.ino file you MUST:
```
1.- Download libraries
2.- Include your RFIDs
3.- Change WAV files
4.- Specify seconds of each WAV file
5.- Dupplicate code for more then 3 RFID's
```

Enjoy of thing...

Oscar


### Licencia

Ha sido programada en su conjunto por Oscar Calero '2021.
```
Se puede utilizar el código sin restricciones 
```
!! El usuario debe utilizarla bajo su propio riesgo y responsabilidad. !!
