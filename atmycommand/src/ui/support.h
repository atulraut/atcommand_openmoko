/*
 * support.h 
 *
 * Header file for support.c
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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

/*
 * Standard gettext macros.
*/
#ifdef ENABLE_NLS
#  include <libintl.h>
#  undef _
#  define _(String) dgettext (PACKAGE, String)
#  define Q_(String) g_strip_context ((String), gettext (String))
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define Q_(String) g_strip_context ((String), (String))
#  define N_(String) (String)
#endif

enum
{
  COL_AT_COMMAND = 0,
  COL_OUTPUT,
  NUM_COLS
};

/* Use structure for creating Progress bar */
typedef struct _ProgressData 
{
  GtkWidget *window;
  GtkWidget *pbar;
  int timer;
  gboolean activity_mode;
} ProgressData;

/*  For Run Menu Icon use  */
#define GTK_STOCK_EXECUTE          "gtk-execute"

GtkWidget *temp_vbox_Global;

/*  Creating window  */
GtkWidget* ui_create_window (void);

/*  To add items to tree structure  */
GtkTreeModel *ui_create_and_fill_model (void);

/*  Creating tree like structure view  */
GtkWidget *ui_create_view_and_model (void);

/*  Create frame  */
GtkWidget *  ui_create_frame ();

/*  Create Menubar  */
GtkWidget * ui_create_menubar (GtkWidget *window );

/*  Standard window-creating stuff  */
void ui_combine_widget (GtkWidget *window);

/* Progress bar time period setting */
gboolean progress_timeout( gpointer data );

/* Use to detroy progress bar */
void destroy_progress( GtkWidget *widget, ProgressData *pdata);
