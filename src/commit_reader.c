/*
 * Commit Reader -- 
 * Copyright (C) 2013 HAYASHI Kentaro
 *
 */

#include "config.h"
#include <glib.h>
#include <glib/gi18n-lib.h>
#include <glib/gprintf.h>
#include <gtk/gtk.h>
#include <libintl.h>

#if defined(USE_WEBKITGTK)
#include <webkit/webkit.h>
#include <webkit/webkitwebview.h>
#elif defined(USE_GTKHTML)
#include <gtkhtml/gtkhtml.h>
#else
#error "Not Implemented any HTML features"
#endif

#include "sylmain.h"
#include "plugin.h"
#include "folder.h"
#include "procmsg.h"
#include "compose.h"
#include "alertpanel.h"
#include "foldersel.h"
#include "headerview.h"
#include "messageview.h"
#include "procheader.h"

#include "copying.h"
#include "commit_reader.h"

#include "../res/comment_edit.xpm"

static SylPluginInfo info = {
  N_(PLUGIN_NAME),
  "0.1.0",
  "HAYASHI Kentaro",
  N_(PLUGIN_DESC)
};

CommitReaderOption SYLPF_OPTION;

static void init_done_cb(GObject *obj, gpointer data);
static void app_exit_cb(GObject *obj, gpointer data);

gulong app_exit_handler_id = 0;

void plugin_load(void)
{
  gpointer mainwin;
  void *option;

  syl_init_gettext(COMMIT_READER, "lib/locale");
  g_print("sylicons plug-in loaded!\n");

  syl_plugin_add_menuitem("/Tools", NULL, NULL, NULL);
  syl_plugin_add_menuitem("/Tools",
                          _("CommitReader [commit_reader]"),
                          exec_commit_reader_menu_cb, NULL);

  mainwin = syl_plugin_main_window_get();
  syl_plugin_main_window_popup(mainwin);

  g_signal_connect_after(syl_app_get(), "init-done", G_CALLBACK(init_done_cb),
                         NULL);
  g_signal_connect(syl_app_get(), "app-exit", G_CALLBACK(app_exit_cb), NULL);

  syl_plugin_signal_connect("messageview-show",
                            G_CALLBACK(messageview_show_cb), NULL);

  option = &SYLPF_OPTION;
  sylpf_load_option_rcfile((SylPluginFactoryOption*)option,
                           COMMIT_READER_RC);
}

void plugin_unload(void)
{
  SYLPF_START_FUNC;
  SYLPF_END_FUNC;
}

SylPluginInfo *plugin_info(void)
{
  return &info;
}

gint plugin_interface_version(void)
{
    return 0x0108;
    /* return SYL_PLUGIN_INTERFACE_VERSION; */
}

static void init_done_cb(GObject *obj, gpointer data)
{
  SYLPF_START_FUNC;
  SYLPF_END_FUNC;
}

static void app_exit_cb(GObject *obj, gpointer data)
{
  SYLPF_START_FUNC;
  SYLPF_END_FUNC;
}

static void commit_comment_button_cb(GObject *obj, gpointer data)
{
  SYLPF_START_FUNC;
  SYLPF_END_FUNC;
}

static void exec_commit_reader_menu_cb(void)
{
  GtkWidget *dialog;
  gint response;
  
  SYLPF_START_FUNC;

  dialog = create_preference_dialog(&SYLPF_OPTION);
  
  gtk_widget_show_all(dialog);
  response = gtk_dialog_run(GTK_DIALOG(dialog));

  switch (response) {
  case GTK_RESPONSE_OK:
    save_commit_reader_preference(&SYLPF_OPTION);
    break;
  case GTK_RESPONSE_CANCEL:
  default:
    break;
  }

  gtk_widget_destroy(dialog);
  
  SYLPF_END_FUNC;
}

static GtkWidget *create_preference_dialog(CommitReaderOption *option)
{
  GtkWidget *vbox, *hbox;
  GtkWidget *dialog;
  GtkWidget *window;
  GtkWidget *notebook;
  gpointer mainwin;
  
  SYLPF_START_FUNC;

  mainwin = syl_plugin_main_window_get();
  window = ((MainWindow*)mainwin)->window;

  dialog = gtk_dialog_new_with_buttons(_("CommitReader"),
                                       GTK_WINDOW(window),
                                       GTK_DIALOG_MODAL,
                                       GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                       GTK_STOCK_OK, GTK_RESPONSE_OK,
                                       NULL);

  sylpf_init_preference_dialog_size(dialog);

  vbox = gtk_vbox_new(FALSE, SYLPF_BOX_SPACE);
  hbox = gtk_hbox_new(TRUE, SYLPF_BOX_SPACE);

  gtk_container_add(GTK_CONTAINER(hbox), vbox);
  gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), hbox);

  notebook = gtk_notebook_new();
  create_config_main_page(notebook, SYLPF_OPTION.rcfile);
  create_config_about_page(notebook, SYLPF_OPTION.rcfile);

  gtk_widget_show(notebook);
  
  gtk_box_pack_start(GTK_BOX(vbox), notebook, TRUE, TRUE, 0);
  
  gtk_box_set_spacing(GTK_BOX(GTK_DIALOG(dialog)->vbox), SYLPF_BOX_SPACE);

  SYLPF_RETURN_VALUE(dialog);
  
}

static GtkWidget *create_config_main_page(GtkWidget *notebook, GKeyFile *pkey)
{
  GtkWidget *vbox;
  GtkWidget *private, *image, *scripts, *switch_tab;
  GtkWidget *label;
  void *option;

  SYLPF_START_FUNC;

  if (notebook == NULL){
    return NULL;
  }
  /* startup */
  if (pkey!=NULL){
  }
  vbox = gtk_vbox_new(FALSE, 6);

#if USE_WEBKITGTK
  SYLPF_OPTION.private_browsing = gtk_check_button_new_with_label(_("Enable private browsing."));
  private = sylpf_pack_widget_with_aligned_frame(SYLPF_OPTION.private_browsing, _("Privacy"));

  SYLPF_OPTION.load_image = gtk_check_button_new_with_label(_("Enable auto load image."));
  image = sylpf_pack_widget_with_aligned_frame(SYLPF_OPTION.load_image, _("Image"));

  SYLPF_OPTION.scripts = gtk_check_button_new_with_label(_("Enable scripts."));
  scripts = sylpf_pack_widget_with_aligned_frame(SYLPF_OPTION.scripts, _("Scripting"));

#endif

  SYLPF_OPTION.switch_tab = gtk_check_button_new_with_label(_("Show HTML tab as default."));
  switch_tab = sylpf_pack_widget_with_aligned_frame(SYLPF_OPTION.switch_tab, _("HTML Tab"));

  gtk_box_pack_start(GTK_BOX(vbox), switch_tab, FALSE, FALSE, 0);

#if USE_WEBKITGTK
  gtk_box_pack_start(GTK_BOX(vbox), private, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), image, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), scripts, FALSE, FALSE, 0);
#endif

  option = &SYLPF_OPTION;
  sylpf_load_option_rcfile((SylPluginFactoryOption*)option,
                           COMMIT_READER_RC);

#if USE_WEBKITGTK
  SYLPF_OPTION.private_flag = SYLPF_GET_RC_BOOLEAN("enable-private-browsing");
  SYLPF_OPTION.image_flag = SYLPF_GET_RC_BOOLEAN("auto-load-images");
  SYLPF_OPTION.script_flag = SYLPF_GET_RC_BOOLEAN("enable-scripts");
#endif

  SYLPF_OPTION.switch_tab_flag = SYLPF_GET_RC_BOOLEAN(ENABLE_SWITCH_TAB);

#define TOGGLE_STATE(widget, state) \
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(SYLPF_OPTION.widget), SYLPF_OPTION.state)

#if USE_WEBKITGTK
  TOGGLE_STATE(private_browsing, private_flag);
  TOGGLE_STATE(load_image, image_flag);
  TOGGLE_STATE(scripts, script_flag);
#endif
  TOGGLE_STATE(switch_tab, switch_tab_flag);

#undef TOGGLE_STATE

  // TODO
  //save_option_rcfile();

  label = gtk_label_new(_("General"));
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox, label);
  gtk_widget_show_all(notebook);

  SYLPF_RETURN_VALUE(vbox);
}

static GtkWidget *create_config_about_page(GtkWidget *notebook, GKeyFile *pkey)
{
  GtkWidget *hbox, *vbox;
  GtkWidget *label;
  GtkWidget *scrolled, *tview;
  GtkTextBuffer *tbuffer;

  SYLPF_START_FUNC;

  g_return_val_if_fail(notebook != NULL, NULL);

  hbox = gtk_hbox_new(TRUE, SYLPF_BOX_SPACE);
  vbox = gtk_vbox_new(FALSE, SYLPF_BOX_SPACE);
  gtk_box_pack_start(GTK_BOX(hbox), vbox, TRUE, TRUE, SYLPF_BOX_SPACE);

  label = gtk_label_new(COMMIT_READER);
  gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, TRUE, SYLPF_BOX_SPACE);

  label = gtk_label_new(PLUGIN_DESC);
  gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, TRUE, SYLPF_BOX_SPACE);

  scrolled = gtk_scrolled_window_new(NULL, NULL);

  tbuffer = gtk_text_buffer_new(NULL);
  gtk_text_buffer_set_text(tbuffer, _(copyright), strlen(copyright));
  tview = gtk_text_view_new_with_buffer(tbuffer);
  gtk_text_view_set_editable(GTK_TEXT_VIEW(tview), FALSE);
  gtk_container_add(GTK_CONTAINER(scrolled), tview);

  gtk_box_pack_start(GTK_BOX(vbox), scrolled, TRUE, TRUE, SYLPF_BOX_SPACE);

  label = gtk_label_new(_("About"));
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), hbox, label);
  gtk_widget_show_all(notebook);

  SYLPF_RETURN_VALUE(NULL);
}

static GtkWidget *create_comment_button()
{
  GtkWidget *button;
  GdkPixbuf *pixbuf;
  GtkWidget *image;

  SYLPF_START_FUNC;

  button = gtk_button_new();

  pixbuf = gdk_pixbuf_new_from_xpm_data((const char **)comment_edit);
  image = gtk_image_new_from_pixbuf(pixbuf);
  gtk_button_set_image(GTK_BUTTON(button), image);

  g_object_set(G_OBJECT(button),
               "name", "commit-comment-button", NULL);

  g_signal_connect(G_OBJECT(button), "clicked",
                   G_CALLBACK(commit_comment_button_cb), NULL);

  SYLPF_RETURN_VALUE(button);
}

static GtkWidget *get_commit_comment_button(GtkWidget *box)
{
  GtkWidget *widget;
  GtkWidget *comment_button;
  GList *widget_list;
  int index;
  gchar *name;

  SYLPF_START_FUNC;

  comment_button = NULL;
  widget_list = gtk_container_get_children(GTK_CONTAINER(box));

  for (index = 0; index < g_list_length(widget_list); index++) {
    widget = g_list_nth_data(widget_list, index);
    if (GTK_IS_BUTTON(widget)) {
      g_object_get(G_OBJECT(widget), "name", &name, NULL);
      if (strcmp(name, "commit-comment-button") == 0) {
        comment_button = widget;
      }
      g_free(name);
    }
  }
  SYLPF_RETURN_VALUE(comment_button);
}


static void messageview_show_cb(GObject *obj, gpointer msgview,
				MsgInfo *msginfo, gboolean all_headers)
{
  MessageView *messageview;
  HeaderView *headerview;
  GtkWidget *hbox;
  GList *wl;
  gchar *msg_path;
  char **to_list;
  gsize n_to_items;
  GError *error;
  gchar *html_buf, *text_buf;
  gint i;
  MimeInfo *mimeinfo, *partial;
  GSList* hl;
  FILE *msg_file, *input = NULL;
  size_t n_size;
  GtkWidget *comment_button;
  gboolean not_found;
#if defined(USE_WEBKITGTK)
  WebKitWebSettings *settings = NULL;
#elif defined(USE_GTKHTML)
#else
#error "Not Implemented"
#endif
  
  SYLPF_START_FUNC;

  not_found = TRUE;

#if DEBUG
  g_print("[DEBUG] sylicons: %p: messageview_show (%p), all_headers: %d: %s\n",
	  obj, msgview, all_headers,
	  msginfo && msginfo->subject ? msginfo->subject : "");
#endif
  
  if (!msgview) {
    SYLPF_WARN_MSG("msgview is NULL");
    return;
  }

  messageview = (MessageView*)msgview;
  if (!messageview) {
    SYLPF_WARN_MSG("messageview is NULL");
    return;
  }

  headerview = messageview->headerview;
  if (!headerview) {
    SYLPF_WARN_MSG("headerview is NULL");
    return;
  }

  hbox = headerview->hbox;
  if (!hbox) {
    SYLPF_WARN_MSG("headerview hbox is NULL");
    return;
  }

  wl = gtk_container_get_children(GTK_CONTAINER(hbox));

  comment_button = get_commit_comment_button(hbox);

  msg_path = procmsg_get_message_file_path(msginfo);

  SYLPF_DEBUG_STR("msg_path", msg_path);

  mimeinfo = procmime_scan_message(msginfo);
  msg_file = procmsg_open_message(msginfo);

  if (SYLPF_OPTION.html_view == NULL) {
#if defined(USE_WEBKITGTK)
    SYLPF_OPTION.html_view = (WebKitWebView*)create_htmlview(GTK_NOTEBOOK(messageview->notebook));
#elif defined(USE_WEBKITGTK)
    SYLPF_OPTION.html_view = create_htmlview(GTK_NOTEBOOK(messageview->notebook));
#endif
  }

  partial = mimeinfo;
  while (partial && partial->mime_type != MIME_TEXT_HTML) {
    partial = procmime_mimeinfo_next(partial);
  }

  if (partial && partial->mime_type == MIME_TEXT_HTML) {
    
    partial->mime_type = MIME_TEXT;

    input = procmime_get_text_content(partial, msg_file, NULL);

    html_buf = calloc(partial->size+1, 1);

    n_size = fread(html_buf, partial->size, 1, input);

#if defined(USE_WEBKITGTK)
    settings = webkit_web_view_get_settings(SYLPF_OPTION.html_view);

    g_object_set(G_OBJECT(settings), ENABLE_IMAGES, SYLPF_OPTION.image_flag, NULL);
    g_object_set(G_OBJECT(settings), ENABLE_SCRIPTS, SYLPF_OPTION.script_flag, NULL);
    g_object_set(G_OBJECT(settings), ENABLE_PRIVATE_BROWSING, SYLPF_OPTION.private_flag, NULL);

    g_object_set(G_OBJECT(settings), DEFAULT_FONT_SIZE, SYLPF_OPTION.font_size, NULL);

    webkit_web_view_set_settings(SYLPF_OPTION.html_view, settings);

    webkit_web_view_load_string(SYLPF_OPTION.html_view, html_buf, NULL, NULL, "");

#elif defined(USE_GTKHTML)
    gtk_html_load_from_string(GTK_HTML(SYLPF_OPTION.html_view), html_buf, -1);
#endif

    if (SYLPF_OPTION.switch_tab_flag != FALSE) {
      gtk_notebook_set_current_page(GTK_NOTEBOOK(messageview->notebook), 2);
    }

    fclose(input);
    free(html_buf);

    if (!comment_button) {
      comment_button = create_comment_button();
      gtk_box_pack_end(GTK_BOX(hbox), comment_button, FALSE, FALSE, 0);
    }
    not_found = FALSE;
    gtk_widget_show(comment_button);
    return;
  }

  hl = procheader_get_header_list_from_file(msg_path);

  to_list = SYLPF_GET_RC_STRING_LIST(SYLPF_OPTION.rcfile,
                                     COMMIT_READER,
                                     "commit-to",
                                     &n_to_items,
                                     &error);
  g_return_if_fail(n_to_items > 0);

  if (!to_list) {
    SYLPF_WARN_MSG("key commit-to not found in rc file");
    if (comment_button) {
      gtk_widget_show(comment_button);
    }
    return;
  }

  for (i = 0; i < n_to_items; i++) {
    if (msginfo && msginfo->to && to_list[i]) {
      SYLPF_DEBUG_STR("msginfo->to", msginfo->to);
      SYLPF_DEBUG_STR("to_list[i]", to_list[i]);
      if (strcmp(msginfo->to, to_list[i]) == 0) {
        SYLPF_DEBUG_STR("matched to 'commit-to'", msginfo->to);

        text_buf = sylpf_get_text_from_message_partial(msginfo, MIME_TEXT);
        
        SYLPF_DEBUG_STR("text/plain", text_buf);

        html_buf = sylpf_format_diff2html_text(text_buf);
          
#if defined(USE_WEBKITGTK)
        settings = webkit_web_view_get_settings(SYLPF_OPTION.html_view);

        g_object_set(G_OBJECT(settings), ENABLE_IMAGES, SYLPF_OPTION.image_flag, NULL);
        g_object_set(G_OBJECT(settings), ENABLE_SCRIPTS, SYLPF_OPTION.script_flag, NULL);
        g_object_set(G_OBJECT(settings), ENABLE_PRIVATE_BROWSING, SYLPF_OPTION.private_flag, NULL);

        g_object_set(G_OBJECT(settings), DEFAULT_FONT_SIZE, SYLPF_OPTION.font_size, NULL);

        webkit_web_view_set_settings(SYLPF_OPTION.html_view, settings);

        webkit_web_view_load_string(SYLPF_OPTION.html_view, html_buf, NULL, NULL, "");

#elif defined(USE_GTKHTML)
        gtk_html_load_from_string(GTK_HTML(SYLPF_OPTION.html_view), html_buf, -1);
#else
#error "use WebKitGTK or GtkHTML"
#endif

        g_free(text_buf);

        mimeinfo = procmime_scan_message(msginfo);

        messageview_change_view_type(messageview, MVIEW_MIME);
        gtk_notebook_set_current_page(GTK_NOTEBOOK(messageview->notebook), 2);
        
        if (SYLPF_OPTION.switch_tab_flag != FALSE) {
        }
        if (!comment_button) {
          comment_button = create_comment_button();
          gtk_box_pack_end(GTK_BOX(hbox), comment_button, FALSE, FALSE, 0);
        }
        not_found = FALSE;
        gtk_widget_show(comment_button);
      }

    }
  }
  g_strfreev(to_list);

  if (not_found && comment_button) {
    gtk_widget_hide(comment_button);
  }

  SYLPF_END_FUNC;
}

static void save_commit_reader_preference(CommitReaderOption *option)
{
  void *sylpf_option;

  SYLPF_START_FUNC;

#define TOGGLE_STATE(widget) \
  gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))

#if USE_WEBKITGTK
  option->private_flag = TOGGLE_STATE(option->private_browsing);
  option->image_flag = TOGGLE_STATE(option->load_image);
  option->script_flag = TOGGLE_STATE(option->scripts);
#endif
  option->switch_tab_flag = TOGGLE_STATE(option->switch_tab);

#if USE_WEBKITGTK
  g_print("%s:%s\n", ENABLE_PRIVATE_BROWSING, BOOL_TOSTRING(option->private_flag));
  g_print("%s:%s\n", ENABLE_IMAGES, BOOL_TOSTRING(option->image_flag));
  g_print("%s:%s\n", ENABLE_SCRIPTS, BOOL_TOSTRING(option->script_flag));
#endif
  g_print("%s:%s\n", ENABLE_SWITCH_TAB, BOOL_TOSTRING(option->switch_tab_flag));

#undef TOGGLE_STATE
  
  sylpf_option = option;
  sylpf_load_option_rcfile((SylPluginFactoryOption*)sylpf_option,
                           COMMIT_READER_RC);
  
#if USE_WEBKITGTK
  SYLPF_SET_RC_BOOLEAN(ENABLE_PRIVATE_BROWSING, SYLPF_OPTION.private_flag);
  SYLPF_SET_RC_BOOLEAN(ENABLE_IMAGES, SYLPF_OPTION.image_flag);
  SYLPF_SET_RC_BOOLEAN(ENABLE_SCRIPTS, SYLPF_OPTION.script_flag);
#endif
  SYLPF_SET_RC_BOOLEAN(ENABLE_SWITCH_TAB, SYLPF_OPTION.switch_tab_flag);

  // TODO
  //save_option_rcfile();

#undef TOGGLE_STATE

  SYLPF_END_FUNC;
}

static GtkWidget *create_htmlview(GtkNotebook *notebook)
{

#if defined(USE_WEBKITGTK)
  WebKitWebView *html_widget = WEBKIT_WEB_VIEW(webkit_web_view_new());
#elif defined(USE_GTKHTML)
  GtkWidget *html_widget = gtk_html_new();
#endif
  GtkWidget *scrolled;

  SYLPF_START_FUNC;

  scrolled = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
                                 GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_container_add(GTK_CONTAINER(scrolled), GTK_WIDGET(html_widget));
  gtk_widget_show_all(GTK_WIDGET(scrolled));

  gtk_container_add(GTK_CONTAINER(notebook),
                    GTK_WIDGET(scrolled));
  gtk_notebook_set_tab_label_text(GTK_NOTEBOOK(notebook),
                                  GTK_WIDGET(scrolled), _("HTML"));

  SYLPF_RETURN_VALUE(GTK_WIDGET(html_widget));
}


/* derived from messageview.c */
static void messageview_set_mime_view_layout(MessageView *messageview)
{
  
  if (SYLPF_OPTION.attach_toolbutton_pos == 0) {
    gtk_box_set_child_packing(GTK_BOX(messageview->hbox),
                              messageview->toolbar_vbox,
                              FALSE, FALSE, 0, GTK_PACK_START);
  } else {
    gtk_box_set_child_packing(GTK_BOX(messageview->hbox),
                              messageview->toolbar_vbox,
                              FALSE, FALSE, 0, GTK_PACK_END);
  }

  if (SYLPF_OPTION.show_attach_tab_flag) {
    gtk_widget_hide(messageview->toolbar_vbox);
  } else {
    gtk_widget_show(messageview->toolbar_vbox);
  }

  gtk_notebook_set_show_tabs(GTK_NOTEBOOK(messageview->notebook),
                             SYLPF_OPTION.show_attach_tab_flag);
}

/* derived from messageview.c */
static void messageview_change_view_type(MessageView *messageview,
                                         MessageType type)
{
  GtkWidget *notebook = messageview->notebook;

  if (type == MVIEW_MIME) {
    messageview_set_mime_view_layout(messageview);
    
    gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook),
                                  messageview->current_page);
    
    if (messageview->current_page == 0) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(messageview->mime_toggle_btn), FALSE);
    } else {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(messageview->mime_toggle_btn), TRUE);
    }
  } else {
    return;
  }
  messageview->type = type;
}
