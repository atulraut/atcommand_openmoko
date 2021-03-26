/*
 * support.c 
 *
 * Used by main.c for to call related funcitons of AT Commands.
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
#include <ui/support.h>
#include <ui/callbacks.h>
#include <at/atcmd.h>

GtkTreeStore  *g_treestore;
GtkTreeIter g_toplevel_gsm0707, g_child_gsm0707 [ATCMD_TOTAL];

static gchar const *GS_LEFT_COLUMN_TITLE 	= "Command" ;
static gchar const *GS_RIGHT_COLUMN_TITLE 	= "Output" ;
static gchar const *GS_GSM_0707 		= "GSM 07.07";
static gchar const *GS_RUN_TITLE		= "Run";
static gchar const *GS_CLEAR_LOGS_TITLE		= "Clear logs";
static gchar const *GS_SETTINGS_TITLE		= "Settings";
static gchar const *GS_LOG_TITLE		= "View Log";
static gchar const *GS_QUIT_TITLE		= "Quit";
static gchar const *GS_ABOUT_TITLE		= "About";
static gchar const *GS_FILE_TITLE		= "File";
static gchar const *GS_HELP_TITLE		= "Help";
static gchar const *GS_FRAME_TITLE		= "Frame for AMC";

extern amc_item_t *g_run;

extern void log_clear_logs (void);

/* Create window  */
GtkWidget * 
ui_support_create_window (void)
{
  GtkWidget *window = NULL; 	

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), GS_LEFT_COLUMN_TITLE);	
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW (window), HWINDOW_SIZE, VWINDOW_SIZE);

  g_signal_connect (GTK_OBJECT (window), "delete_event", G_CALLBACK (ui_interface_delete_event), NULL);
  g_signal_connect (GTK_OBJECT (window), "destroy", G_CALLBACK (ui_callback_destroy), NULL);	 	

  return window;
}

/*  To add items to tree structure  */
GtkTreeModel *
ui_support_create_and_fill_model (void)
{
  gint i;
  GSList *local_list;
  amc_entry_t *local_amc_entry;

  g_treestore = gtk_tree_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_STRING); 

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
	
  return GTK_TREE_MODEL (g_treestore);
}

/*  Creating tree like structure view  */
GtkWidget *
ui_support_create_view_and_model (void)
{
  GtkWidget *view;
  GtkTreeModel *model;
  GtkTreeViewColumn *col;
  GtkCellRenderer *renderer;

  view = gtk_tree_view_new ();

  /* AT Command column */
  col = gtk_tree_view_column_new ();
  gtk_tree_view_column_set_title (col, GS_LEFT_COLUMN_TITLE);

  gtk_tree_view_append_column (GTK_TREE_VIEW (view), col);
  renderer = gtk_cell_renderer_text_new ();

  gtk_tree_view_column_pack_start (col, renderer, TRUE);
  gtk_tree_view_column_add_attribute (col, renderer, "text", COL_AT_COMMAND);
  gtk_tree_view_column_set_resizable (col, TRUE);
	
  /* Output column */
  col = gtk_tree_view_column_new ();
  gtk_tree_view_column_set_title (col, GS_RIGHT_COLUMN_TITLE);

  gtk_tree_view_append_column (GTK_TREE_VIEW (view), col);
  renderer = gtk_cell_renderer_text_new ();

  gtk_tree_view_column_pack_start (col, renderer, TRUE);
  gtk_tree_view_column_add_attribute (col, renderer, "text", COL_OUTPUT);
  gtk_tree_view_column_set_resizable (col, TRUE);

  /* Set 'weight' property of the cell renderer to bold print (we want all last names in bold) */
  g_object_set (renderer, "weight", PANGO_WEIGHT_BOLD, "weight-set", TRUE, NULL);

  model = ui_support_create_and_fill_model ();

  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);
  g_object_unref (model); /* Destroy model automatically with view */
  gtk_tree_selection_set_mode (gtk_tree_view_get_selection (GTK_TREE_VIEW (view)), 
			       GTK_SELECTION_NONE);

  return view;
}

/*  Create Menubar  */
GtkWidget * 
ui_support_create_menubar (GtkWidget *window)
{
  GtkWidget *f_menu;
  GtkWidget *h_menu;
  GtkWidget *menu_bar;
  GtkWidget *root_menu;
  GtkWidget *help_menu;    
  GtkWidget *runtest_menu_item;
  GtkWidget *clearlogs_menu_item;
  GtkWidget *about_menu_item;
  GtkWidget *settings_menu_item;
  GtkWidget *log_menu_item;
  GtkWidget *exit_menu_item;	
	
  f_menu = gtk_menu_new ();
  h_menu = gtk_menu_new ();
	
  /* Create the menu items */
  runtest_menu_item   	= gtk_menu_item_new_with_label (GS_RUN_TITLE);	
  clearlogs_menu_item 	= gtk_menu_item_new_with_label (GS_CLEAR_LOGS_TITLE);
  settings_menu_item   	= gtk_menu_item_new_with_label (GS_SETTINGS_TITLE);
  log_menu_item		= gtk_menu_item_new_with_label (GS_LOG_TITLE);
  exit_menu_item      	= gtk_menu_item_new_with_label (GS_QUIT_TITLE);
  about_menu_item     	= gtk_menu_item_new_with_label (GS_ABOUT_TITLE);

  /* Add menu items to the menu    */
  gtk_menu_shell_append (GTK_MENU_SHELL (f_menu), runtest_menu_item);    
  gtk_menu_shell_append (GTK_MENU_SHELL (f_menu), clearlogs_menu_item);    
  gtk_menu_shell_append (GTK_MENU_SHELL (f_menu), settings_menu_item);
  gtk_menu_shell_append (GTK_MENU_SHELL (f_menu), log_menu_item);	
  gtk_menu_shell_append (GTK_MENU_SHELL (f_menu), exit_menu_item);    
  gtk_menu_shell_append (GTK_MENU_SHELL (h_menu), about_menu_item);

  /* We do need to show menu items    */
  gtk_widget_show (runtest_menu_item);
  gtk_widget_show (clearlogs_menu_item);
  gtk_widget_show (about_menu_item);
  gtk_widget_show (settings_menu_item);
  gtk_widget_show (log_menu_item);
  gtk_widget_show (exit_menu_item);

  /* The root and help menu will displayed on the menu bar */
  root_menu = gtk_menu_item_new_with_label (GS_FILE_TITLE);
  help_menu = gtk_menu_item_new_with_label (GS_HELP_TITLE);
  gtk_widget_show (root_menu);
  gtk_widget_show (help_menu);

  /* Submenu */
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (root_menu), f_menu);
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (help_menu), h_menu);		

  /* Create a menu-bar to hold the menus and add it to our main window */
  menu_bar = gtk_menu_bar_new ();

  /* Finally we append the menu-item to the menu-bar  */
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), root_menu);
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), help_menu);	

  /* Attach the callback functions to the activate signal */
  g_signal_connect_swapped (G_OBJECT (runtest_menu_item), "activate", 
			    G_CALLBACK (ui_callback_menuitem_run_response), (gpointer) GS_RUN_TITLE);
  g_signal_connect_swapped (G_OBJECT (clearlogs_menu_item), "activate", 
			    G_CALLBACK (log_clear_logs), (gpointer)GS_CLEAR_LOGS_TITLE);							 
  g_signal_connect_swapped (G_OBJECT (about_menu_item), "activate", 
			    G_CALLBACK (ui_callback_about_clicked), (gpointer) window);
  g_signal_connect_swapped (G_OBJECT (settings_menu_item), "activate", 
			    G_CALLBACK (ui_callback_settings_clicked), (gpointer) GS_SETTINGS_TITLE);
g_signal_connect_swapped (G_OBJECT (log_menu_item), "activate", 
				  G_CALLBACK (ui_callback_viewlog_clicked), (gpointer) window);
  /* Attach the Quit menu item to our exit function */
  g_signal_connect_swapped (G_OBJECT (exit_menu_item), "activate", 
			    G_CALLBACK (ui_callback_destroy), (gpointer) GS_QUIT_TITLE);		
  gtk_widget_show_all (menu_bar);

  return  menu_bar;
}

/*  Create frame  */
GtkWidget *  
ui_support_create_frame (void)
{
  GtkWidget *frame;

  /* Create a Frame */
  frame = gtk_frame_new (NULL);

  /* Set the frame's label */
  gtk_frame_set_label (GTK_FRAME (frame), GS_FRAME_TITLE);

  /* Align the label at the right of the frame */
  gtk_frame_set_label_align (GTK_FRAME (frame), 1.0, 0.0);

  /* Set the style of the frame */
  gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_ETCHED_OUT);
  gtk_widget_show (frame);	

  return frame;
}

/*  Standard window-creating stuff  */
void 
ui_support_combine_widget (GtkWidget *window)
{
  GtkWidget *vBox,  *temp_vbox,  *menuBar, *frame;
	
  menuBar = ui_support_create_menubar (window);
  frame   = ui_support_create_frame ();

  vBox             = gtk_vbox_new (FALSE,0);	
  temp_vbox        = gtk_vbox_new (FALSE,0);
  temp_vbox_Global = temp_vbox;
	
  gtk_box_pack_start (GTK_BOX(vBox),  menuBar, FALSE, TRUE, 0);
  gtk_widget_show (menuBar);	

  gtk_box_pack_start (GTK_BOX (vBox), temp_vbox_Global, TRUE, TRUE, 0);
  gtk_widget_show (temp_vbox_Global);
  gtk_widget_show (vBox);

  gtk_container_add (GTK_CONTAINER(window), vBox);
  gtk_widget_show (window);
}

/* Update the value of the progress bar so that we get
 * some movement */
gboolean 
progress_timeout( gpointer data )
{
  ProgressData *pdata = (ProgressData *)data;
  gdouble new_val;
  GtkProgressBar *progress;
  gdouble percent = 0.0;
		
  if (pdata->activity_mode) 
    gtk_progress_bar_pulse (GTK_PROGRESS_BAR (pdata->pbar));
  else 
    {
      // Calculate the value of the progress bar using the
      //  value range set in the adjustment object 
	  
      new_val = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (pdata->pbar)) + 0.01;
      
//      if (new_val > 1.0)
//	new_val = 0.0;
  
	while (percent <= 100.0)
	{
		gchar *message = g_strdup_printf ("%.0f%% Complete", percent);
		gtk_progress_bar_set_fraction (pdata->pbar, percent / 100.0);
		gtk_progress_bar_set_text (pdata->pbar, message);
			
		while (gtk_events_pending ())
		  gtk_main_iteration ();
	  
		g_usleep (50000);
		percent += 5.0;	    		  
  	}		
    }  
  // As this is a timeout function, return TRUE so that it
  //  continues to get called 
	g_print ("\n %f",gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (pdata->pbar)));
	if( 1.00 == gtk_progress_bar_get_fraction(pdata->pbar))
	{			
		gtk_widget_hide_all(pdata->window);
	}
	return FALSE;	
} 

/* Clean up allocated memory and remove the timer */
void 
destroy_progress( GtkWidget    *widget,
                              ProgressData *pdata)
{
    g_source_remove (pdata->timer);
    pdata->timer = 0;
    pdata->window = NULL;
    g_free (pdata);  
}

