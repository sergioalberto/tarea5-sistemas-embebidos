//##########################################################################
//
// This program solves the server problem creating a new process for each
// connection
//
// Author: Sergio Gonzalez Q, Luis Carrillo, Angel 
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//#########################################################################

#include <gst/gst.h>

#ifndef _REPRODUCIR_MP3_H_
#define _REPRODUCIR_MP3_H_

GstStateChangeReturn ret;
GMainLoop *loop;
GstElement *pipeline, *filesrc, *decoder, *filter, *sink;

void play(char *name);

#endif /* _REPRODUCIR_MP3_H_ */
