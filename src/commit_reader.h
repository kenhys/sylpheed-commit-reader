/*
 * CommitReader -- 
 * Copyright (C) 2013 HAYASHI Kentaro
 *
 */

#ifndef __COMMIT_READER_H__
#define __COMMIT_READER_H__

#ifdef USE_WEBKITHTML
#include <webkit/webkitwebview.h>
#endif
#ifdef USE_GTKHTML
#endif

#include "sylplugin_factory.h"

#define COMMIT_READER "commit_reader"
#define COMMIT_READER_RC "commitreaderrc"

#undef PLUGIN_NAME
#define PLUGIN_NAME N_("CommitReader Plug-in")

#undef PLUGIN_DESC
#define PLUGIN_DESC N_("Support to read every commit mail, every day")

#define ENABLE_PRIVATE_BROWSING "enable-private-browsing"
#define ENABLE_IMAGES "auto-load-images"
#define ENABLE_SCRIPTS "enable-scripts"

#define ENABLE_SWITCH_TAB "switch-tab"
#define DEFAULT_FONT_SIZE "default-font-size"

#define ENABLE_HIDE_FOLDERVIEW "hide-folderview"

#define BOOL_TOSTRING(value) (value) ? "TRUE" : "FALSE"

/*#define GET_RC_BOOLEAN(keyarg) g_key_file_get_boolean(g_opt.rcfile, COMMIT_READER, keyarg, NULL)*/

typedef struct _CommitReaderOption CommitReaderOption;

struct _CommitReaderOption {
  /* General section */
  /* full path to ghostbiffrc*/
  gchar *rcpath;
  /* rcfile */
  GKeyFile *rcfile;
  
#if USE_WEBKITGTK
  WebKitWebView *html_view;
#endif
#if USE_GTKHTML
  GtkWidget *html_view;
#endif

#if USE_WEBKITGTK
  GtkWidget *private_browsing;
  gboolean private_flag;

  GtkWidget *load_image;
  gboolean image_flag;

  GtkWidget *scripts;
  gboolean script_flag;

#endif

  GtkWidget *switch_tab;
  gboolean switch_tab_flag;

  gboolean show_attach_tab_flag;
  gint attach_toolbutton_pos;

  gboolean hide_folderview_flag;

  gint font_size;

  GtkWidget *folder_entry;
  gchar *folder_path;
};
    
static void messageview_show_cb(GObject *obj, gpointer msgview,
                                MsgInfo *msginfo, gboolean all_headers);
static void exec_commit_reader_menu_cb(void);
static GtkWidget *create_preference_dialog(CommitReaderOption *option);
static GtkWidget *create_config_main_page(GtkWidget *notebook, GKeyFile *pkey);
static GtkWidget *create_config_about_page(GtkWidget *notebook, GKeyFile *pkey);
static void save_commit_reader_preference(CommitReaderOption *option);
static GtkWidget *create_htmlview(GtkNotebook *notebook);

static void messageview_change_view_type(MessageView *messageview,
                                         MessageType type);
static void load_html_to_widget(gpointer widget, gchar *html);
static gboolean is_commit_mail_address_list(MsgInfo *msginfo, char **to_list, gsize n_to_items);
static GtkWidget *create_comment_dialog(CommitReaderOption *option, MsgInfo* msginfo);
static void create_comment_input_field(void);

static void commit_comment_input_cb(GObject *obj, gpointer data);
static void commit_comment_clear_cb(GObject *obj, gpointer data);

#endif /* __COMMIT_READER_H__ */
