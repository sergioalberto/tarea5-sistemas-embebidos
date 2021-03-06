//##########################################################################
//
// This program solves the server problem creating a new process for each
// connection
//
// Author: Sergio Gonzalez Q, Luis Carrillo, Angel 
// Codigo tomado de: http://gstreamer.freedesktop.org/data/doc/gstreamer/head/manual/html/chapter-helloworld.html
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

	GMainLoop *loop;

	GstElement *pipeline, *source, *demuxer, *decoder, *conv, *sink;
	GstBus *bus;
	guint bus_watch_id;

	void play(char *name);
	static void on_pad_added (GstElement *element, GstPad *pad, gpointer data);
	static gboolean bus_call (GstBus *bus, GstMessage *msg, gpointer data);

#endif /* _REPRODUCIR_MP3_H_ */
