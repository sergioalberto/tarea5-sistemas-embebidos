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
	/* create elements */
	pipeline = gst_pipeline_new ("my_pipeline"); // Create a new pipeline with the given name.

	filesrc  = gst_element_factory_make ("filesrc", "my_filesource");
	decoder  = gst_element_factory_make ("mad", "my_decoder");

	sink     = gst_element_factory_make ("pulsesink", "audiosink");

	g_object_set (G_OBJECT (filesrc), "location", name, NULL);

	gst_bin_add_many (GST_BIN (pipeline), filesrc, decoder, sink, NULL);

	/* link everything together */
	if (!gst_element_link_many (filesrc, decoder, sink, NULL)) {
		g_print ("Failed to link one or more elements!\n");
		exit(0);
	}

	/* run */
  	ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE) {
		g_print ("Failed to start up pipeline!\n");
		exit(0);
	}

	g_main_loop_run (loop);

	/* clean up */
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref (pipeline);
	g_main_loop_unref (loop);
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
