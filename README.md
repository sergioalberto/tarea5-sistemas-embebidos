tarea5-sistemas-embebidos
=========================

Tarea #5 del curso de sistemas embebidos

Gente ya esta funcionando solo falta que funcione para la beagle.

Para correrlo primero digite en consola:
- /opt/gstreamer-sdk/bin/gst-sdk-shell

luego:
- Si quieren correrlo para su PC:

make

sudo ./reproductor_mp3 cansion.pm3


- Si quieren correrlo para la Beagle:

make xBB

sudo ./reproductor_mp3 cansion.pm3

Nota: 
Tomen en cuenta que para este caso en el makefile el CROSS_COMPILE este hecho para mi compu, osea en el path 
dice "sergio", si quieren cambiarlo para sus pc tiene q cambiar esto.

Gracias
