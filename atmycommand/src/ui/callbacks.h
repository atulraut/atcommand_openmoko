/*
 * callbacks.h 
 *
 * Header file for callbacks.c
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 *
 */

#include <gtk/gtk.h>

gboolean ui_interface_delete_event (GtkWidget *widget, GdkEvent *event,  gpointer data);
void ui_callback_destroy (GtkWidget *widget, gpointer data);

void ui_callback_menuitem_run_response (GtkWindow  *);
void ui_callback_settings_clicked (GtkMenuItem *menuitem, gpointer user_data);
void ui_callback_about_clicked (GtkMenuItem *menuitem, GtkWindow *parent);
void ui_callback_viewlog_clicked(GtkMenuItem *menuitem, GtkWindow *parent);
GtkTreeModel *ui_support_create_and_fill_model (void);
