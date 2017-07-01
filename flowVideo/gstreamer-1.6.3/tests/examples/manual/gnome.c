
/*** block a  from ../../../docs/manual/appendix-integration.xml ***/
#include <gtk/gtk.h>
#include <gst/gst.h>

static gchar **cmd_filenames = NULL;

static GOptionEntries cmd_options[] = {
  /* here you can add command line options for your application. Check
   * the GOption section in the GLib API reference for a more elaborate
   * example of how to add your own command line options here */

  /* at the end we have a special option that collects all remaining 
   * command line arguments (like filenames) for us. If you don&apos;t
   * need this, you can safely remove it */
  { G_OPTION_REMAINING, 0, 0, G_OPTION_ARG_FILENAME_ARRAY, &cmd_filenames,
    "Special option that collects any remaining arguments for us" },

  /* mark the end of the options array with a NULL option */
  { NULL, }
};

/* this should usually be defined in your config.h */
#define VERSION "0.0.1"

gint
main (gint argc, gchar **argv)
{
  GOptionContext *context;
  GOptionGroup *gstreamer_group, *gtk_group;
  GError *err = NULL;

  context = g_option_context_new ("gtk-demo-app");

  /* get command line options from GStreamer and add them to the group */
  gstreamer_group = gst_init_get_option_group ();
  g_option_context_add_group (context, gstreamer_group);
  gtk_group = gtk_get_option_group (TRUE);
  g_option_context_add_group (context, gtk_group);

  /* add our own options. If you are using gettext for translation of your
   * strings, use GETTEXT_PACKAGE here instead of NULL */
  g_option_context_add_main_entries (context, cmd_options, NULL);

  /* now parse the commandline options, note that this already
   * calls gtk_init() and gst_init() */
  if (!g_option_context_parse (ctx, &argc, &argv, &err)) {
    g_print ("Error initializing: %s\n", err->message);
    exit (1);
  }

  /* any filenames we got passed on the command line? parse them! */
  if (cmd_filenames != NULL) {
    guint i, num;

    num = g_strv_length (cmd_filenames);
    for (i = 0; i < num; ++i) {
      /* do something with the filename ... */
      g_print ("Adding to play queue: %s\n", cmd_filenames[i]);
    }

    g_strfreev (cmd_filenames);
    cmd_filenames = NULL;
  }

/*** block b  from ../../../docs/manual/appendix-integration.xml ***/
  return 0;

/*** block c  from ../../../docs/manual/appendix-integration.xml ***/
}
