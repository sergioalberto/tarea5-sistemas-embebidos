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

#include "reproducir_mp3.h"

void play(char *name){

	/* Create gstreamer elements */
	pipeline = gst_pipeline_new ("audio-player");
	source   = gst_element_factory_make ("filesrc",       "file-source");
	demuxer  = gst_element_factory_make ("decodebin",      "ogg-demuxer");
	decoder  = gst_element_factory_make ("audioresample",     "vorbis-decoder");
	conv     = gst_element_factory_make ("audioconvert",  "converter");
	sink     = gst_element_factory_make ("autoaudiosink", "audio-output");

	if (!pipeline || !source || !demuxer || !decoder || !conv || !sink) {
		g_printerr ("One element could not be created. Exiting.\n");
		exit(0);
	}

	/* Set up the pipeline */

	/* we set the input filename to the source element */
	g_object_set (G_OBJECT (source), "location", name, NULL);

	/* we add a message handler */
	bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
	bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);
	gst_object_unref (bus);

	/* we add all elements into the pipeline */
	/* file-source | ogg-demuxer | vorbis-decoder | converter | alsa-output */
	gst_bin_add_many (GST_BIN (pipeline), source, demuxer, decoder, conv, sink, NULL);

	/* we link the elements together */
	/* file-source -> ogg-demuxer ~> vorbis-decoder -> converter -> alsa-output */
	gst_element_link (source, demuxer);
	gst_element_link_many (decoder, conv, sink, NULL);
	g_signal_connect (demuxer, "pad-added", G_CALLBACK (on_pad_added), decoder);

	/* note that the demuxer will be linked to the decoder dynamically.
	The reason is that Ogg may contain various streams (for example
	audio and video). The source pad(s) will be created at run time,
	by the demuxer when it detects the amount and nature of streams.
	Therefore we connect a callback function which will be executed
	when the "pad-added" is emitted.*/


	/* Set the pipeline to "playing" state*/
	g_print ("Now playing: %s\n", name);
	gst_element_set_state (pipeline, GST_STATE_PLAYING);


	/* Iterate */
	g_print ("Running...\n");
	g_main_loop_run (loop);


	/* Out of the main loop, clean up nicely */
	g_print ("Returned, stopping playback\n");
	gst_element_set_state (pipeline, GST_STATE_NULL);

	g_print ("Deleting pipeline\n");
	gst_object_unref (GST_OBJECT (pipeline));
	g_source_remove (bus_watch_id);
	g_main_loop_unref (loop);

}

static void on_pad_added (GstElement *element, GstPad *pad, gpointer data) {

  GstPad *sinkpad;
  GstElement *decoder = (GstElement *) data;

  /* We can now link this pad with the vorbis-decoder sink pad */
  g_print ("Dynamic pad created, linking demuxer/decoder\n");

  sinkpad = gst_element_get_static_pad (decoder, "sink");

  gst_pad_link (pad, sinkpad);

  gst_object_unref (sinkpad);
}

static gboolean bus_call (GstBus *bus, GstMessage *msg, gpointer data) {

  GMainLoop *loop = (GMainLoop *) data;

  switch (GST_MESSAGE_TYPE (msg)) {

    case GST_MESSAGE_EOS:
      g_print ("End of stream\n");
      g_main_loop_quit (loop);
      break;

    case GST_MESSAGE_ERROR: {
      gchar  *debug;
      GError *error;

      gst_message_parse_error (msg, &error, &debug);
      g_free (debug);

      g_printerr ("Error: %s\n", error->message);
      g_error_free (error);

      g_main_loop_quit (loop);
      break;
    }
    default:
      break;
  }

  return TRUE;
}

int main (int argc, gchar *argv[]) {

	/* initialization */
	gst_init (&argc, &argv);
	loop = g_main_loop_new (NULL, FALSE);

	if (argc != 2) {
		g_print ("Usage: %s <mp3 filename>\n", argv[0]);
		exit(0);
	}

	play(argv[1]);

	return 0;
}
