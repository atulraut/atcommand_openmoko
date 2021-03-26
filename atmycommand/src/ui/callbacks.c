/*
 * callbacks.c 
 *
 * Used to callbacks the functions used by support.c module.  
 * 
 * Authored by Atul Raut <rauji.raut@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <glib.h>
#include <gtk/gtk.h>
#include <ui/callbacks.h>
#include <ui/interface.h>
#include <ui/support.h>
#include <at/atcmd.h>

static GtkWidget *s_view;
static GtkWidget *s_scroll_window;

static gint s_flag = 0;
static gchar const *GS_GSM_0707 	= "GSM 07.07";
static gchar const *GS_ABOUT_STRING 	= "Project started by AR India!";
static gchar const *GS_VIEWLOG_STRING 	= "Developed by AR";

extern amc_item_t 	*g_run;
extern GtkTreeStore  	*g_treestore;
extern GtkTreeIter 	g_toplevel_gsm0707, g_child_gsm0707 [ATCMD_TOTAL];

/* Called by File->Quit to quit the application */
void 
ui_callback_destroy (GtkWidget *widget, gpointer data)
{
  ll_cleanup_all_memory ();

  gtk_main_quit ();
}

/* File->Run */
void 
ui_callback_menuitem_run_response (GtkWindow *window)
{
  ProgressData *pdata;
  GtkWidget *align;
  GtkWidget *separator;
  GtkWidget *table;
  GtkWidget *button;
  GtkWidget *check;
  GtkWidget *vbox; 	
  gint i = 0;
  GSList *local_list = NULL;
  amc_entry_t *local_amc_entry = NULL;

// Allocate memory for the data that is passed to the callbacks 
  pdata = g_malloc (sizeof (ProgressData));
  
  pdata->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  gtk_window_set_resizable (GTK_WINDOW (pdata->window), TRUE);
  gtk_window_set_position (GTK_WINDOW (pdata->window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW (pdata->window), 400, 400);
		
  g_signal_connect (G_OBJECT (pdata->window), "destroy",
	              G_CALLBACK (destroy_progress),
                      (gpointer) pdata);
  gtk_window_set_title (GTK_WINDOW (pdata->window), "GtkProgressBar");
  gtk_container_set_border_width (GTK_CONTAINER (pdata->window), 0);

  vbox = gtk_vbox_new (FALSE, 5);
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 10);
  gtk_container_add (GTK_CONTAINER (pdata->window), vbox);
  gtk_widget_show (vbox);
  
  // Create a centering alignment object 
  align = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_box_pack_start (GTK_BOX (vbox), align, FALSE, FALSE, 5);
  gtk_widget_show (align);

  // Create the GtkProgressBar 
  pdata->pbar = gtk_progress_bar_new ();
  pdata->activity_mode = FALSE;

  gtk_container_add (GTK_CONTAINER (align), pdata->pbar);
  gtk_widget_show (pdata->pbar);
  gtk_widget_show (pdata->window);	

  // Add a timer callback to update the value of the progress bar 
  pdata->timer = g_timeout_add (100, progress_timeout, pdata);
  g_print("\n before fun ");
  /*if( 1.00 == gtk_progress_bar_get_fraction(pdata->pbar))
  {
	g_print("\n in fun ");
        gtk_widget_hide_all(pdata->window);
   }*/
   g_print("\n after fun ");

  if (!s_flag) /* First time, create view */
    {
      s_flag = 1;

      /* Run test, insert test results */
      atcmd_run_test (g_run->lgsmh);

      s_scroll_window = gtk_scrolled_window_new (NULL, NULL);
	
      s_view = (GtkWidget *) ui_support_create_view_and_model ();	

      gtk_box_pack_start (GTK_BOX (temp_vbox_Global), s_scroll_window, TRUE, TRUE, 0);
      gtk_widget_show (s_scroll_window);
      gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (s_scroll_window), s_view);

      gtk_widget_show (temp_vbox_Global);
      gtk_widget_show (s_view);		
    }
  else /* Second time, just update the view */
    {
      atcmd_run_test (g_run->lgsmh);

      gtk_tree_store_clear (g_treestore);

      gtk_tree_store_append (g_treestore, &g_toplevel_gsm0707, NULL);
      gtk_tree_store_set (g_treestore, &g_toplevel_gsm0707, COL_AT_COMMAND, 
			  GS_GSM_0707, COL_OUTPUT, "", -1);

      /* Update data - need to be changed */
      for (local_list=g_run->amc_list, i=0; local_list!=NULL; local_list=local_list->next, i++)
	{
	  local_amc_entry = local_list->data;

	  gtk_tree_store_append (g_treestore, &g_child_gsm0707[i], &g_toplevel_gsm0707);			
	  gtk_tree_store_set (g_treestore, &g_child_gsm0707[i], COL_AT_COMMAND, 
			      local_amc_entry->command, COL_OUTPUT, local_amc_entry->output,  -1);
	}
    }
}

/* Show "About" information */
void 
ui_callback_about_clicked (GtkMenuItem *menuitem,  GtkWindow *parent)
{
  GtkWidget *dialog, *label, *image, *hbox;
  /* Create a new dialog with one OK button. */
  dialog = gtk_dialog_new_with_buttons ("Information", parent,
                                      GTK_DIALOG_MODAL,
                                      GTK_STOCK_OK, GTK_RESPONSE_OK,
                                      NULL);
  gtk_dialog_set_has_separator (GTK_DIALOG (dialog), FALSE);
  label = gtk_label_new (GS_VIEWLOG_STRING);
  image = gtk_image_new_from_stock (GTK_STOCK_DIALOG_INFO,
                                  GTK_ICON_SIZE_DIALOG);
  hbox = gtk_hbox_new (FALSE, 5);
  gtk_container_set_border_width (GTK_CONTAINER (hbox), 10);
  gtk_box_pack_start_defaults (GTK_BOX (hbox), image);
  gtk_box_pack_start_defaults (GTK_BOX (hbox), label);
  /* Pack the dialog content into the dialog's GtkVBox. */
  gtk_box_pack_start_defaults (GTK_BOX (GTK_DIALOG (dialog)->vbox), hbox);
  gtk_widget_show_all (dialog);
  /* Create the dialog as modal and destroy it when a button is clicked. */
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);	
}

/* Settings */	
void 
ui_callback_settings_clicked (GtkMenuItem *menuitem, gpointer user_data)
{

}

ui_callback_viewlog_clicked(GtkMenuItem *menuitem, GtkWindow *parent)
{
  
}
