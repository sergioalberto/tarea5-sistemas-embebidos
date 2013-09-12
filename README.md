tarea5-sistemas-embebidos
=========================

Tarea #5 del curso de sistemas embebidos

Pasos a seguir:

1) Si su PC no le reconoce "gst-launch-0.10":

<<<<<<< .mine
$ /opt/gstreamer-sdk/bin/gst-sdk-shell
=======
luego:
- Si quieren correrlo para su PC:

make

sudo ./reproductor_mp3 cansion.pm3
>>>>>>> .r14

2) Si quiere compilarlo y ejecutarlo en su PC:
$ make
$ sudo ./reproductor_mp3 cansion.ogg

<<<<<<< .mine
3) Si quiere compilarlo para la Beagle:
$ make xBB
=======
- Si quieren correrlo para la Beagle:

make xBB

sudo ./reproductor_mp3 cansion.pm3
>>>>>>> .r14

4) Para ejecutarlo en la BeagleBoard usando el ambiente crosado

4.1) Correr con ambiente crusado:

En el archivo "boot_script.minicom", en "serverip" se pone el ip de su compu y en "ipaddr" el ip de la beagleboard
Correr con:

$ sudo minicom -S boot_script.minicom
 >> Luego poner boot

4.2) Se va a poner el ejecutable generado "reproductor_mp3" en
el file system (/home/sergio/ti-sdk-beagleboard-06.00.00.00/targetNFS/home/root) de su PC (el que va a ver la beagle).

4.3) Configurar el volumen:

amixer sset 'DAC1 Digital Fine' 100
amixer sset 'Headset' 2
amixer sset 'HeadsetL Mixer AudioL1' on
amixer sset 'HeadsetR Mixer AudioR1' on

4.4) Ejecutar

./reproductor_mp3 cansion.ogg

Nota: 
Tomen en cuenta que para este caso en el makefile el CROSS_COMPILE este hecho para mi compu, osea en el path 
dice "sergio", si quieren cambiarlo para sus pc tiene q cambiar esto.

Gracias
